#include <stdio.h>
#include <pigpio.h>

#define LED5 5 // Correspond a la GPIO de la LED0
#define LED6 6 // Correspond a la GPIO de la LED0
#define LED12 12 // Correspond a la GPIO de la LED0
#define LED13 13 // Correspond a la GPIO de la LED0
#define LED16 16 // Correspond a la GPIO de la LED0
#define LED19 19 // Correspond a la GPIO de la LED0
#define LED20 20 // Correspond a la GPIO de la LED0
#define LED21 21 // Correspond a la GPIO de la LED0

#define BP1 27
#define BP2 17

int main (void){

        if (gpioInitialise() <0 ) { // On initialise la bibliothèque
                return -1;
        }

gpioSetMode(LED5, PI_OUTPUT); // On configure la GPIO en sortie
gpioSetMode(LED6, PI_OUTPUT); // On configure la GPIO en sortie
gpioSetMode(LED12, PI_OUTPUT); // On configure la GPIO en sortie
gpioSetMode(LED16, PI_OUTPUT); // On configure la GPIO en sortie
gpioSetMode(LED19, PI_OUTPUT); // On configure la GPIO en sortie
gpioSetMode(LED20, PI_OUTPUT); // On configure la GPIO en sortie
gpioSetMode(LED21, PI_OUTPUT); // On configure la GPIO en sortie
gpioSetMode(LED13, PI_OUTPUT); // On configure la GPIO en sortie

gpioSetMode(BP1, PI_INPUT); // On configure la GPIO en sortie
gpioSetMode(BP2, PI_INPUT); // On configure la GPIO en sortie

while(1){

while((gpioRead(BP1)==0) && (gpioRead(LED5) == 0)){
        gpioWrite(LED5,1); // ON
}

while((gpioRead(BP2)==0) && (gpioRead(LED6) == 0)){
        gpioWrite(LED6,1); // ON
}

while(gpioRead(BP2)==1 && gpioRead(BP1)==1){

gpioWrite(LED5,0); 
gpioWrite(LED6,0); 

return 0;

}

gpioTerminate();

return 0;

}




