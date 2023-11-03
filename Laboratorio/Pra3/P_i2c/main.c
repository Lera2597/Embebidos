#include <stdio.h>
#include <string.h>


#include "pico/stdlib.h"
#include "hardware/i2c.h"

#define I2C_PORT i2c0

static int addr = 0xD6;
uint8_t chipID[1];
uint8_t reg = 0x00;
// Initialise Accelerometer Function
void accel_init(void){
    // Check to see if connection is correct
    sleep_ms(1000); // Add a short delay to help BNO005 boot up
    //uint8_t reg = 0x00;
    //uint8_t chipID[1];    
    i2c_write_blocking(I2C_PORT, addr, &reg, 1, true);
    i2c_read_blocking(I2C_PORT, addr, chipID, 1, false);

    if(chipID[0] != 0){
        while(1){
            printf("Chip ID Not Correct - Check Connection!\n");
            sleep_ms(500);
        }
    }

}

int main(void){
    
    stdio_init_all(); // Initialise STD I/O for printing over serial
    sleep_ms(2000);
    /*
    // Configure the I2C Communication
    i2c_init(i2c_default, 115200);
    gpio_set_function(PICO_DEFAULT_I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(PICO_DEFAULT_I2C_SDA_PIN);
    gpio_pull_up(PICO_DEFAULT_I2C_SCL_PIN);
    sleep_ms(5000);
    // Call accelerometer initialisation function
    accel_init();
    uint8_t con=0;
    reg=0x14;
    */
   printf("paso.\n");
    char a[4]="carro";
    char b[4]={5,6,7,8};
    uint8_t lon_a=strlen(a);
    uint8_t lon_b=strlen(b);
    printf("%zu.\n",lon_a); 
    printf("%zu.\n",lon_b); 
    uint8_t c[lon_a+lon_b];
    uint8_t con=0;
    for(uint8_t i=0;i<lon_a;i++){
        c[con]=a[i];
        con++;
    }
    for(uint8_t i=0;i<lon_b;i++){
        c[con]=b[i];
        con++;
    }
    //strcat(parte1,parte2);

    //uint8_t union_1[]= {parte1,parte2};
    //printf("paso.\n");

    for (int i=0;i<strlen(c);i++){
        printf("%d.\n",c[i]);  
        sleep_ms(100);
    }

    /*
    // Infinite Loop
    while(1){
        
        if(con==10){
            i2c_write_blocking(I2C_PORT, addr, &reg, 1, true);
            reg++;
            con=0;
        }
        else{
            i2c_read_blocking(I2C_PORT, addr, chipID, 1, false);
            printf("dato: %d\n",chipID[0]);
            sleep_ms(200);
            con++;
        }
    }*/
}