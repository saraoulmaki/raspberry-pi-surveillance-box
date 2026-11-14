#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <pigpiod_if2.h>

int main(int argc, char *argv[]) {

    //Déclarer les variables

    float param; // type
    float angle_pan;
    float angle_tilt;

    char temp_pan[4];   //tableau temporaire pour inverser tab_pan
    char temp_tilt[4];  //tableau temporaire pour inverser tab_tilt

    char tab_pan[4];   //angle pan dans un tab de 4 octets
    char tab_tilt[4];   //angle tilt tab dans un tab de 4 octets

    int pi, handle, commande,i,j,k;

    int checksum = 0;

    char buff[12] = {0x55,0x09};    //buffer [head,type,len, . . . . , . . . . ,checksum]
                                                          //angle pan //angle tilt
    //Lancer pigpio

    pi = pigpio_start(0,0);

    //Configurer/Ouvrir liaison série

    handle = serial_open(pi,"/dev/ttyACM0",115200,0);

    //Si il y a des arguments

    if (argc > 1) {

        printf("Il y a %d arguments : %s %s %s\n", argc, argv[1], argv[2], argv[3]);

        //Récupérer les arguments passés en paramètre

        param = strtod(argv[1], 0);
        angle_pan = strtod(argv[2], 0);
        angle_tilt = strtod(argv[3], 0);

        //Récuperation des commandes

        buff[2] = param;

        //récuperation des angles dans des tab de 4 octet

        memcpy(&tab_pan[0],&angle_pan,4);
        memcpy(&tab_tilt[0],&angle_tilt,4);

        //Les stocker dans des tab temportaires

        for(i=0;i<4;i++){
                temp_pan[i] = tab_pan[i];
                temp_tilt[i] = tab_tilt[i];
        }

        //Inverser les tab

        tab_pan[0] = temp_pan[3];
        tab_pan[1] = temp_pan[2];
        tab_pan[2] = temp_pan[1];
        tab_pan[3] = temp_pan[0];

        tab_tilt[0] = temp_tilt[3];
        tab_tilt[1] = temp_tilt[2];
        tab_tilt[2] = temp_tilt[1];
        tab_tilt[3] = temp_tilt[0];

        //Mettre les tab des angles pan et tilt dans le buffer

        memcpy(&buff[3],&tab_pan[0],4);
        memcpy(&buff[7],&tab_tilt[0],4);

    //Calcul boucle du checksum

    for(k=0;k<11;k++){
        checksum = checksum + buff[k];
    }

   buff[11] = (char)checksum;

    //Envoi de la commande sur l'UART

    commande = serial_write(pi,handle,buff,12);

}
    //Si n'il y a pas d'arguments

    else {
        printf("Veuillez passer un argument\n");
        return -1;
    }

    //Fermer pigpio et liaison serie

    serial_close(pi,handle);

    pigpio_stop(pi);

    return 0;

}


