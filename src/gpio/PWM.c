#include<stdio.h>
#include <pigpiod_if2.h>

int main (void){

int pi = pigpio_start(0,0);
int i;

set_mode(pi,5,PI_OUTPUT);

for(i=0;i<255;i++){

        set_PWM_dutycycle(pi,5,i+5);
        time_sleep(0.1);

}

pigpio_stop(pi);

return 0;

}

