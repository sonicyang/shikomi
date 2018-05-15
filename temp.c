#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>

#include <wiringPi.h>
#include <wiringPiI2C.h>

#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <signal.h>

union temparature{
    struct {
        uint8_t hi;
        uint8_t lo;
    } bytes;
    uint16_t all;
};

static volatile int keep_running = 1;

void intHandler(int dummy) {
    keep_running = 0;
}

int main(int argc, char* argv[]) {
    int dev_fd;
    union temparature data;
    int sign;
    float temp;

    signal(SIGINT, intHandler);

    dev_fd = wiringPiI2CSetup(0x48);
    if (dev_fd < 0) {
        printf("Error Initializing I2C");
        return -1;
    }

    wiringPiI2CWrite(dev_fd, 0x51);
    usleep(5000);

    while(keep_running) {

        data.all = wiringPiI2CReadReg16(dev_fd, 0xAA);
        printf("Data = 0x%x\n", data.all);

        sign = data.bytes.hi & 0x80;

        data.bytes.hi &= 0x7f;
        data.bytes.lo &= 0xf0;

        temp = (((int)data.bytes.hi << 4) + (data.bytes.lo >> 4)) / 16.0;

        if(!sign) {
            printf("%f degess C\n", temp);
        } else {
            printf("-%f degess C\n", temp);
        }

        usleep(500000);
    }

    wiringPiI2CWrite(dev_fd, 0x22);

	return 0;

}
