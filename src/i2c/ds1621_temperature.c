
#include <stdio.h>
#include <unistd.h>
#include <pigpiod_if2.h>

//Déclarer les varables

#define DS1621_I2C_BUS 1
#define DS1621_SLAVE_ADDR 0x48
#define DS1621_ACCESS_CONFIG 0xAC
#define DS1621_START_CONVERT 0xEE
#define DS1621_READ_TEMPERATURE 0xAA
#define DS1621_ONE_SHOT 0x01
#define DS1621_DONE 0x80

int main(){

    int handle;
    int temp;

    float temperature_celsius;

    char temp_msb, temp_lsb;

    // Lancer PIGPIO

    int pi = pigpio_start(0,0);

    // Ouverture I2C

    handle = i2c_open(pi, 1, DS1621_SLAVE_ADDR, 0);

    // Lancer la conversion

    i2c_write_byte(pi, handle, DS1621_START_CONVERT);

    // Attendre 500 ms

    time_sleep(0.005);

    // Lire la température

    i2c_write_byte(pi, handle, DS1621_READ_TEMPERATURE);

    temp_msb = i2c_read_byte(pi, handle);
    temp_lsb = i2c_read_byte(pi, handle);

    // Combinaison des octets de température en une valeur de 16 bits
    temp = (temp_msb << 8) | temp_lsb;

    // Décalage de 7 bits à droite pour éliminer les bits inutilisés
    temp = temp >> 7;

    // Conversion de la température en degrés Celsius
    temperature_celsius = temp * 0.5;

    printf("Temperature: %.2f °C\n", temperature_celsius);

    // Fermer I2C / Fermer pigpio

    i2c_close(pi, handle);

    pigpio_stop(pi);

    return 0;
}
