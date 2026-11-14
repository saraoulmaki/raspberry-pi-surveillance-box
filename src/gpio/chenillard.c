#include<stdio.h>
#include <pigpiod_if2.h>

#define BP1 27
#define BP2 17

int main (void){

int pi = pigpio_start(0,0);
int i,j,k;

int tab[8] = {5,6,12,13,16,19,20,21};

for(k=0;k<8;k++){
        set_mode(pi,tab[i],PI_OUTPUT);
}


for(j=0;j<=1;j++){
        for(i=0;i<8;i++){
                gpio_write(pi, tab[i], PI_HIGH);
                time_sleep(0.1); // 100ms
                gpio_write(pi,tab[i], PI_LOW);
        }
}

pigpio_stop(pi);

return 0;

}


