import rclpy
from rclpy.node import Node
from robot_control_interfaces.msg import ArmCommand
import tkinter as tk
from tkinter import ttk

class ArmGUI(Node):
    def __init__(self):
        super().__init__('arm_gui')
        self.publisher = self.create_publisher(ArmCommand, '/cmd_arm', 10)
        
        # Create the main window
        self.root = tk.Tk()
        self.root.title("Arm Control GUI")
        self.root.geometry("600x900")
        
        # Configure root grid weights
        self.root.grid_rowconfigure(0, weight=1)
        self.root.grid_columnconfigure(0, weight=1)
        
        # Create style
        style = ttk.Style()
        style.configure('TLabel', padding=5)
        style.configure('TButton', padding=5)
        style.configure('TEntry', padding=5)
        
        # Create main frame with scrollbar
        main_frame = ttk.Frame(self.root, padding="10")
        main_frame.grid(row=0, column=0, sticky="nsew")
        
        # Configure main frame grid weights
        main_frame.grid_rowconfigure(0, weight=1)
        main_frame.grid_columnconfigure(0, weight=1)
        
        # Create canvas and scrollbar
        canvas = tk.Canvas(main_frame)
        scrollbar = ttk.Scrollbar(main_frame, orient="vertical", command=canvas.yview)
        scrollable_frame = ttk.Frame(canvas)
        
        scrollable_frame.bind(
            "<Configure>",
            lambda e: canvas.configure(scrollregion=canvas.bbox("all"))
        )
        
        canvas.create_window((0, 0), window=scrollable_frame, anchor="nw")
        canvas.configure(yscrollcommand=scrollbar.set)
        
        # Grid the canvas and scrollbar
        canvas.grid(row=0, column=0, sticky="nsew")
        scrollbar.grid(row=0, column=1, sticky="ns")
        
        # Create a container frame for all controls
        controls_frame = ttk.Frame(scrollable_frame)
        controls_frame.grid(row=0, column=0, sticky="nsew")
        
        # Configure scrollable frame grid weights
        scrollable_frame.grid_rowconfigure(0, weight=1)
        scrollable_frame.grid_columnconfigure(0, weight=1)
        
        # Configure controls frame grid weights
        controls_frame.grid_rowconfigure(8, weight=1)  # Make the last row expandable
        controls_frame.grid_columnconfigure(0, weight=1)
        
        def create_control_frame(parent, label, min_val, max_val, default_val, row, joint_num):
            frame = ttk.Frame(parent)
            frame.grid(row=row, column=0, columnspan=2, sticky="ew", pady=5)
            
            # Label
            ttk.Label(frame, text=label).grid(row=0, column=0, sticky="w")
            
            # Entry
            var = tk.StringVar(value=str(default_val))
            entry = ttk.Entry(frame, textvariable=var, width=6)
            entry.grid(row=0, column=1, padx=5)
            
            # Scale (trackbar)
            scale = ttk.Scale(frame, from_=min_val, to=max_val, orient="horizontal", 
                            variable=tk.DoubleVar(value=default_val))
            scale.grid(row=0, column=2, sticky="ew", padx=5)
            
            # Configure grid weights
            frame.grid_columnconfigure(2, weight=1)
            
            def update_entry(*args):
                var.set(str(int(scale.get())))
            
            def update_scale(*args):
                try:
                    val = int(var.get())
                    if min_val <= val <= max_val:
                        scale.set(val)
                except ValueError:
                    pass
            
            scale.configure(command=lambda *args: update_entry())
            var.trace_add("write", lambda *args: update_scale())
            
            return var, scale
        
        # Create controls
        self.joint1_var, self.joint1_scale = create_control_frame(
            controls_frame, "Joint 1 (0-1023):", 0, 1023, 300, 0, 1)
        self.joint2_var, self.joint2_scale = create_control_frame(
            controls_frame, "Joint 2 (0-1023):", 0, 1023, 300, 1, 2)
        self.joint3_var, self.joint3_scale = create_control_frame(
            controls_frame, "Joint 3 (0-1023):", 0, 1023, 500, 2, 3)
        self.base_var, self.base_scale = create_control_frame(
            controls_frame, "Base (0-180):", 0, 180, 0, 3, 4)
        self.gripper_rotate_var, self.gripper_rotate_scale = create_control_frame(
            controls_frame, "Gripper Rotate (0-270):", 0, 270, 90, 4, 5)
        self.gripper_claw_var, self.gripper_claw_scale = create_control_frame(
            controls_frame, "Gripper Claw (0-180):", 0, 180, 0, 5, 6)
        self.speed_var, self.speed_scale = create_control_frame(
            controls_frame, "Speed (1-100):", 1, 100, 30, 6, 0)  # joint_num=0 for speed
        
        # Add preset position buttons
        button_frame = ttk.Frame(controls_frame)
        button_frame.grid(row=7, column=0, columnspan=2, pady=10)
        
        ttk.Button(button_frame, text="Home Position", command=self.move_to_home).grid(row=0, column=0, padx=5)
        ttk.Button(button_frame, text="Camera View", command=self.move_to_camera).grid(row=0, column=1, padx=5)
        ttk.Button(button_frame, text="Grab Position", command=self.move_to_grab).grid(row=0, column=2, padx=5)
        
        # Send button (now sends all commands at once)
        ttk.Button(controls_frame, text="Send All Commands", command=self.send_commands).grid(
            row=8, column=0, columnspan=2, pady=20)
        
        # Add padding to all widgets
        for child in controls_frame.winfo_children():
            child.grid_configure(padx=5, pady=5)
        
        # Add padding at the bottom
        ttk.Frame(controls_frame, height=100).grid(row=9, column=0, columnspan=2)
    
    def send_commands(self):
        """Send commands for all joints"""
        try:
            # Send joint 1 command
            msg = ArmCommand()
            msg.joint_num = 1
            msg.angle = int(self.joint1_var.get())
            msg.speed = int(self.speed_var.get())
            self.publisher.publish(msg)
            
            # Send joint 2 command
            msg.joint_num = 2
            msg.angle = int(self.joint2_var.get())
            self.publisher.publish(msg)
            
            # Send joint 3 command
            msg.joint_num = 3
            msg.angle = int(self.joint3_var.get())
            self.publisher.publish(msg)
            
            # Send base command
            msg.joint_num = 4
            msg.angle = int(self.base_var.get())
            self.publisher.publish(msg)
            
            # Send gripper rotate command
            msg.joint_num = 5
            msg.angle = int(self.gripper_rotate_var.get())
            self.publisher.publish(msg)
            
            # Send gripper claw command
            msg.joint_num = 6
            msg.angle = int(self.gripper_claw_var.get())
            self.publisher.publish(msg)
            
            self.get_logger().info("Commands sent successfully")
        except ValueError as e:
            self.get_logger().error(f"Invalid input: {e}")
    
    def move_to_home(self):
        """Move arm to home position"""
        self.joint1_var.set("300")
        self.joint2_var.set("300")
        self.joint3_var.set("500")
        self.base_var.set("0")
        self.gripper_rotate_var.set("0")
        self.gripper_claw_var.set("0")
        self.send_commands()
    
    def move_to_camera(self):
        """Move arm to camera view position"""
        self.joint1_var.set("700")
        self.joint2_var.set("700")
        self.joint3_var.set("190")
        self.base_var.set("0")
        self.gripper_rotate_var.set("0")
        self.gripper_claw_var.set("0")
        self.send_commands()
    
    def move_to_grab(self):
        """Move arm to grab position"""
        self.joint1_var.set("940")
        self.joint2_var.set("850")
        self.joint3_var.set("450")
        self.base_var.set("0")
        self.gripper_rotate_var.set("0")
        self.gripper_claw_var.set("0")
        self.send_commands()
    
    def run(self):
        """Run the GUI"""
        self.root.mainloop()

def main(args=None):
    rclpy.init(args=args)
    gui = ArmGUI()
    gui.run()
    gui.destroy_node()
    rclpy.shutdown()

if __name__ == "__main__":
    main() 