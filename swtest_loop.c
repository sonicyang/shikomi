#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <wiringPi.h>

int SW_PIN[] = {0, 7};

int main(int argc, char* argv[]) {
	if (argc < 2) {
		printf("Usage: %s SW_Number \n", argv[0]);
		return -1;
	}

	int sw_num = atoi(argv[1]);
    int sw_val;

	if (sw_num > 1) {
		printf("Error: SW_Number must be specified from 0 to 1\n");
		return -1;
	}

	if (wiringPiSetup() == -1) {
		printf("Error: setup failed.\n");
		return -1;
	}

	pinMode(SW_PIN[sw_num], INPUT);

    while(1) {
        sw_val = digitalRead(SW_PIN[sw_num]);

        printf("SW: %d\n", sw_val);

        usleep(100000);
    }

	return 0;

}
