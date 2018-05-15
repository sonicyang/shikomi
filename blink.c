#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <wiringPi.h>

int LED_PIN[] = {12, 13, 14, 11, 10};
int SW_PIN[] = {0, 7};

int main(int argc, char* argv[]) {
    int i, j, sw_val1, sw_val2;


	if (wiringPiSetup() == -1) {
		printf("Error: setup failed.\n");
		return -1;
	}

    for (i = 0; i < 5; i++){
        pinMode(LED_PIN[i], OUTPUT);
    }

    for (i = 0; i < 2; i++){
        pinMode(SW_PIN[i], INPUT);
    }

    j = 0;
    while(1) {
        sw_val2 = digitalRead(SW_PIN[1]);

        for (i = 0; i < 5; i++){
            digitalWrite(LED_PIN[i], 0);
        }
        if (sw_val2) {
            digitalWrite(LED_PIN[4 - j], 1);
        } else {
            digitalWrite(LED_PIN[j], 1);
        }
        j++;
        j = j % 5;

        sw_val1 = digitalRead(SW_PIN[0]);

        usleep(25000 * (sw_val1 + 1));
    }


	return 0;

}
