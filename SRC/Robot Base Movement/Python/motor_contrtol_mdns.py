import socket
import time
from zeroconf import ServiceInfo, Zeroconf
import keyboard

# Server configuration
PORT = 3001
SERVER_IP = "192.168.247.71"
SERVER_NAME = "laptop.local"
SERVICE_TYPE = "_http._tcp.local."
TOGGLE_KEY = False


s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
try:
    s.bind(("0.0.0.0", PORT))
    print(f"Port {PORT} is available")
except socket.error as e:
    print(f"Port {PORT} in use: {e}")
s.close()


def format_speed(speed):
    """Convert speed (-255 to +255) to 4-character string (+025/-100)"""
    return f"{'+' if speed >=0 else '-'}{abs(speed):03d}"

def motor(client, L1, L2, R2, R1):
    """Send motor command in format: M+LLL+rrr+RRR+LLLE"""
    cmd = f"M{format_speed(L1)}{format_speed(L2)}{format_speed(R2)}{format_speed(R1)}E"
    client.sendall(cmd.encode())
    print(f"Sent: {cmd}")

def send_setpoint(client, angle):
    """Send setpoint command in format: S<angle>E (0-180)"""
    angle = max(0, min(180, int(angle)))  # Constrain to 0-180
    cmd = f"S{angle}E"
    client.sendall(cmd.encode())
    print(f"Setpoint: {angle}°")

def request_encoders(client):
    """Request encoder data by sending 'RE'"""
    cmd = "RE"
    client.sendall(cmd.encode())
    print("Requested encoder data")
def request_rpms(client):
    """Request encoder data by sending 'RE'"""
    cmd = "VE"
    client.sendall(cmd.encode())
    print("Requested encoder data")
    
def parse_encoder_data(data):
    """Parse encoder data in format +123-456+789-012E"""
    if len(data) >= 17 and data.endswith('E'):
        # Extract encoder values (4 encoders, each with sign and 3 digits)
        enc1 = int(data[1:4]) * (1 if data[0] == '+' else -1)
        enc2 = int(data[5:8]) * (1 if data[4] == '+' else -1)
        enc3 = int(data[9:12]) * (1 if data[8] == '+' else -1)
        enc4 = int(data[13:16]) * (1 if data[12] == '+' else -1)
        return enc1, enc2, enc3, enc4
    return None

def start_mdns_service(port):
    local_ip = "192.168.247.71"
    
    service_info = ServiceInfo(
        SERVICE_TYPE,
        f"{SERVER_NAME}.{SERVICE_TYPE}",
        addresses=[socket.inet_aton(local_ip)],
        port=port,
        server=f"{SERVER_NAME}.",
    )
    
    zeroconf = Zeroconf()
    zeroconf.register_service(service_info)
    print(f"mDNS service registered as {SERVER_NAME} on {local_ip}:{port}")
    return zeroconf

def run_server():
    zeroconf = start_mdns_service(PORT)
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    server_socket.bind(('0.0.0.0', PORT))
    server_socket.listen(1)
    
    print(f"Server listening on port {PORT}...")
    print("Controls:")
    print("Movement: W/A/S/D/Q/E")
    print("Setpoints: 0(0°), 1(45°), 2(90°), 3(135°), 4(180°)")
    print("Speed: +/-")
    print("Encoders: R")
    print("Stop: SPACE")
    
    try:
        while True:
            client_socket, addr = server_socket.accept()
            print(f"\nConnected to ESP8266 at {addr}")
            
            try:
                V = 30  # Default speed
                client_socket.settimeout(0.1)  # Set timeout for receiving data

                while True:
                    # Check for incoming data (encoder responses)
                    try:
                        data = client_socket.recv(1024).decode().strip()
                        if data:
                            if data.startswith(('+', '-')) and data.endswith('E'):
                                # This is encoder data
                                encoders = parse_encoder_data(data)
                                if encoders:
                                    enc1, enc2, enc3, enc4 = encoders
                                    print(f"Encoders: 1:{enc1} 2:{enc2} 3:{enc3} 4:{enc4}")
                            else:
                                print(f"Received: {data}")  # Other messages
                    except socket.timeout:
                        pass  # No data received, continue

                    # Movement controls
                    if keyboard.is_pressed('i'):
                        motor(client_socket, +V, +V, -V, -V)  # Forward
                        while keyboard.is_pressed('i'): pass
                        if TOGGLE_KEY: motor(client_socket, 0,0,0,0)
                    
                    elif keyboard.is_pressed(','):
                        motor(client_socket, -V, -V, +V, +V)  # Backward
                        while keyboard.is_pressed(','): pass
                        if TOGGLE_KEY: motor(client_socket, 0,0,0,0)
                    
                    elif keyboard.is_pressed('j'):
                        motor(client_socket, +V, +V, +V, +V)  # Left
                        while keyboard.is_pressed('j'): pass
                        if TOGGLE_KEY: motor(client_socket, 0,0,0,0)
                    
                    elif keyboard.is_pressed('l'):
                        motor(client_socket, -V, -V, -V, -V)  # Right
                        while keyboard.is_pressed('l'): pass
                        if TOGGLE_KEY: motor(client_socket, 0,0,0,0)
                    
                    elif keyboard.is_pressed('u'):
                        motor(client_socket, +V, +V, 0, 0)  # Rotate left
                        while keyboard.is_pressed('u'): pass
                        if TOGGLE_KEY: motor(client_socket, 0,0,0,0)
                    
                    elif keyboard.is_pressed('o'):
                        motor(client_socket, 0, 0, -V, -V)  # Rotate right
                        while keyboard.is_pressed('o'): pass
                        if TOGGLE_KEY: motor(client_socket, 0,0,0,0)
                    
                    elif keyboard.is_pressed('m'):
                        motor(client_socket, -V, -V, 0, 0)  # Rotate left
                        while keyboard.is_pressed('m'): pass
                        if TOGGLE_KEY: motor(client_socket, 0,0,0,0)
                    
                    elif keyboard.is_pressed('.'):
                        motor(client_socket, 0, 0, V, V)  # Rotate left
                        while keyboard.is_pressed('.'): pass
                        if TOGGLE_KEY: motor(client_socket, 0,0,0,0)
                    
                    elif keyboard.is_pressed('h'):
                        motor(client_socket, V, -V, -V, V)  # Rotate left
                        while keyboard.is_pressed('h'): pass
                        if TOGGLE_KEY: motor(client_socket, 0,0,0,0)

                    elif keyboard.is_pressed(';'):
                        motor(client_socket, -V, V, V, -V)  # Rotate left
                        while keyboard.is_pressed(';'): pass
                        if TOGGLE_KEY: motor(client_socket, 0,0,0,0)

                    elif keyboard.is_pressed('y'):
                        motor(client_socket, V, 0, -V, 0)  # Rotate left
                        while keyboard.is_pressed('y'): pass
                        if TOGGLE_KEY: motor(client_socket, 0,0,0,0)

                    elif keyboard.is_pressed('p'):
                        motor(client_socket, 0, V, 0, -V)  # Rotate left
                        while keyboard.is_pressed('p'): pass
                        if TOGGLE_KEY: motor(client_socket, 0,0,0,0)

                    elif keyboard.is_pressed('/'):
                        motor(client_socket, -V, 0, V, 0)  # Rotate left
                        while keyboard.is_pressed('/'): pass
                        if TOGGLE_KEY: motor(client_socket, 0,0,0,0)

                    elif keyboard.is_pressed('n'):
                        motor(client_socket, 0, -V, 0, V)  # Rotate left
                        while keyboard.is_pressed('n'): pass
                        if TOGGLE_KEY: motor(client_socket, 0,0,0,0)
                    
                    ###################################################################################################################### 
                    
                    # Emergency stop
                    elif keyboard.is_pressed('k'):
                        motor(client_socket, 0,0,0,0)
                        while keyboard.is_pressed('k'): pass
                    
                    # Setpoint controls
                    if keyboard.is_pressed('p'):  # For custom setpoint
                        angle = input("Enter setpoint (0-180): ")
                        send_setpoint(client_socket, angle)
                        while keyboard.is_pressed('p'): pass
                    elif keyboard.is_pressed('0'):
                        send_setpoint(client_socket, 0)    # 0°
                        while keyboard.is_pressed('0'): pass
                    
                    elif keyboard.is_pressed('1'):
                        send_setpoint(client_socket, 45)   # 45°
                        while keyboard.is_pressed('1'): pass
                    
                    elif keyboard.is_pressed('2'):
                        send_setpoint(client_socket, 90)   # 90°
                        while keyboard.is_pressed('2'): pass
                    
                    elif keyboard.is_pressed('3'):
                        send_setpoint(client_socket, 135)  # 135°
                        while keyboard.is_pressed('3'): pass
                    
                    elif keyboard.is_pressed('4'):
                        send_setpoint(client_socket, 180)  # 180°
                        while keyboard.is_pressed('4'): pass

                    # Speed adjustment
                    elif keyboard.is_pressed('+'):
                        V = min(255, V+10)
                        print(f"Speed: {V}")
                        while keyboard.is_pressed('+'): pass
                    
                    elif keyboard.is_pressed('-'):
                        V = max(0, V-10)
                        print(f"Speed: {V}")
                        while keyboard.is_pressed('-'): pass
                    
                    # Encoder request
                    elif keyboard.is_pressed('r'):
                        request_encoders(client_socket)
                        while keyboard.is_pressed('r'): pass
                    elif keyboard.is_pressed('v'):
                        request_rpms(client_socket)
                        while keyboard.is_pressed('v'): pass
                    
                    # Emergency stop
                    elif keyboard.is_pressed(' '):
                        motor(client_socket, 0,0,0,0)
                        while keyboard.is_pressed(' '): pass

            except (ConnectionResetError, BrokenPipeError):
                print("Client disconnected")
            finally:
                client_socket.close()
                
    except KeyboardInterrupt:
        print("\nShutting down server...")
    finally:
        server_socket.close()
        zeroconf.unregister_all_services()
        zeroconf.close()

if __name__ == "__main__":
    run_server()
