#include <stdio.h>
#include <stdint.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>

#pragma pack(push, 1)
typedef struct {
    uint16_t distance;
    uint8_t intensity;
} LidarPoint;

typedef struct {
    uint8_t header;
    uint8_t ver_len;
    uint16_t speed;
    uint16_t start_angle;
    LidarPoint point[12];
    uint16_t end_angle;
    uint16_t timestamp;
    uint8_t crc8;
} LiDARFrame;
#pragma pack(pop)

uint8_t calcCRC8(uint8_t *data, size_t len) {
    uint8_t crc = 0;
    for (size_t i = 0; i < len; i++) {
        crc ^= data[i];
        for (int j = 0; j < 8; j++) {
            if (crc & 0x80) {
                crc = (crc << 1) ^ 0x07;
            } else {
                crc <<= 1;
            }
        }
    }
    return crc;
}

int main() {
    int fd = open("/dev/ttyUSB0", O_RDWR | O_NOCTTY);
    if (fd < 0) {
        perror("Error opening port");
        return 1;
    }

    struct termios tty;
    memset(&tty, 0, sizeof(tty));
    if (tcgetattr(fd, &tty) != 0) {
        perror("Error from tcgetattr");
        return 1;
    }

    // Set baud rate to 921600
    cfsetospeed(&tty, B921600);
    cfsetispeed(&tty, B921600);

    // 8-bit chars
    tty.c_cflag |= CS8;
    // Disable PARENB and CSTOPB
    tty.c_cflag &= ~PARENB;
    tty.c_cflag &= ~CSTOPB;
    // No flow control
    tty.c_cflag &= ~CRTSCTS;
    // Turn on READ & ignore ctrl lines
    tty.c_cflag |= CREAD | CLOCAL;
    // Turn off s/w flow ctrl
    tty.c_iflag &= ~(IXON | IXOFF | IXANY);
    // Disable any special handling of received bytes
    tty.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL);
    // Raw output mode
    tty.c_oflag &= ~OPOST;
    // Non-canonical mode
    tty.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);

    // Set read timeout
    tty.c_cc[VTIME] = 1;  // 0.1 seconds timeout
    tty.c_cc[VMIN] = 0;

    if (tcsetattr(fd, TCSANOW, &tty) != 0) {
        perror("Error from tcsetattr");
        return 1;
    }

    printf("Waiting for LiDAR data...\n");
    printf("Header  Ver  Speed  StartAng  Points[dist,int]  EndAng  Time  CRC\n");
    printf("--------------------------------------------------------------\n");

    uint8_t buffer[1024];
    size_t pos = 0;
    
    while (1) {
        uint8_t byte;
        ssize_t n = read(fd, &byte, 1);
        if (n <= 0) continue;

        buffer[pos++] = byte;

        // Look for packet header (0x54) and ver_len (0x2C)
        if (pos >= 2) {
            if (buffer[0] == 0x54 && buffer[1] == 0x2C) {
                if (pos >= sizeof(LiDARFrame)) {
                    LiDARFrame *frame = (LiDARFrame *)buffer;
                    
                    // Verify CRC
                    uint8_t calc_crc = calcCRC8(buffer, sizeof(LiDARFrame) - 1);
                    if (calc_crc == frame->crc8) {
                        printf("0x%02X  0x%02X  %4d  %4d  ", 
                               frame->header, frame->ver_len, 
                               frame->speed, frame->start_angle);
                        
                        // Print first and last point only to keep output readable
                        printf("[%d,%d]...[%d,%d]  ",
                               frame->point[0].distance, frame->point[0].intensity,
                               frame->point[11].distance, frame->point[11].intensity);
                        
                        printf("%4d  %4d  0x%02X\n",
                               frame->end_angle, frame->timestamp, frame->crc8);
                    }
                    pos = 0;  // Reset for next packet
                }
            } else {
                // If header not found, shift buffer and continue
                memmove(buffer, buffer + 1, --pos);
            }
        }

        if (pos >= sizeof(buffer)) {
            pos = 0;  // Buffer overflow protection
        }
    }

    close(fd);
    return 0;
} 