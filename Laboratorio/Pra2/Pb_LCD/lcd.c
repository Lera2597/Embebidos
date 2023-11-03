#include <stdio.h>
#include "pico/stdlib.h"

#include "lcd.h"
//#include "timer.h"

const uint8_t D0= 16;
const uint8_t D1 = 17;
const uint8_t D2 = 18;
const uint8_t D3 = 19;
const uint8_t D4= 20;
const uint8_t D5 = 21;
const uint8_t D6 = 22;
const uint8_t D7 = 26;
const uint8_t RS = 27;
const uint8_t E = 28;
uint8_t pines[10] = {16,17,18,19,20,21,22,26,27,28};


void lcd_clear(){
    gpio_put(D0,1);
    gpio_put(D1,0);
    gpio_put(D2,0);
    gpio_put(D3,0);
    gpio_put(D4,0);
    gpio_put(D5,0);
    gpio_put(D6,0);
    gpio_put(D7,0);
    gpio_put(RS,0);
    gpio_put(E,1); 
    sleep_ms(10);
    gpio_put(E,0);
}
/*Forzar el cursor al principio de la primera línea*/
void lcd_shift_init(bool fila){
    gpio_put(D0,0);
    gpio_put(D1,0);
    gpio_put(D2,0);
    gpio_put(D3,0);

    gpio_put(D4,0);
    gpio_put(D5,0);
    gpio_put(D6,fila);
    gpio_put(D7,1);
    gpio_put(RS,0);
    gpio_put(E,1); 
    sleep_ms(10);
    gpio_put(E,0);
    sleep_ms(10);
}

/*Despalzar Pantalla*/
void lcd_shift_screen(bool sentido, uint8_t num_shift){
    for(int i=0;i<num_shift;i++){
        gpio_put(D0,0);
        gpio_put(D1,0);
        gpio_put(D2,sentido); 
        gpio_put(D3,1);  

        gpio_put(D4,1);
        gpio_put(D5,0);
        gpio_put(D6,0);
        gpio_put(D7,0);

        gpio_put(RS,0);
        gpio_put(E,1); 
        sleep_ms(10);
        gpio_put(E,0);
    }
    sleep_ms(10);
}
/*Despalzar cursor*/
void lcd_shift_cursor(bool sentido){
    gpio_put(D0,0);
    gpio_put(D1,0);
    gpio_put(D2,sentido); 
    gpio_put(D3,0);  

    gpio_put(D4,1);
    gpio_put(D5,0);
    gpio_put(D6,0);
    gpio_put(D7,0);

    gpio_put(RS,0);
    gpio_put(E,1); 
    sleep_ms(10);
    gpio_put(E,0); 
    sleep_ms(10);  
}
/*Set Display*/
void lcd_display_on_off(bool display,bool cursor,bool blink){
    // Parpadeo o no  
    gpio_put(D0,blink);
    gpio_put(D1,cursor);
    gpio_put(D2,display);
    gpio_put(D3,1);
    gpio_put(D4,0);
    gpio_put(D5,0);
    gpio_put(D6,0);
    gpio_put(D7,0);
    gpio_put(RS,0);
    gpio_put(E,1); 
    sleep_ms(10);
    gpio_put(E,0);
}
/*inicializacion del LCD*/
void lcd_init(){

    for(int i=0;i<10;i++){
        gpio_init(pines[i]);
        gpio_set_dir(pines[i], GPIO_OUT);
    }
    //Function set
    gpio_put(D0,0);
    gpio_put(D1,0);
    gpio_put(D2,1);
    gpio_put(D3,1);
    gpio_put(D4,1);
    gpio_put(D5,1);
    gpio_put(D6,0);
    gpio_put(D7,0);
    gpio_put(RS,0);
    gpio_put(E,1); 
    sleep_ms(10);
    gpio_put(E,0);

    // Display ON/OFF Control
    lcd_display_on_off(1,1,1);

    //Clear display
    lcd_clear();

    //Entry Mode Set  
    //Desplazamiento o no del curso luego de un intro caracter
    gpio_put(D0,0);
    gpio_put(D1,1);
    gpio_put(D2,1);
    gpio_put(D3,0);
    gpio_put(D4,0);
    gpio_put(D5,0);
    gpio_put(D6,0);
    gpio_put(D7,0);
    gpio_put(RS,0);
    gpio_put(E,1); 
    sleep_ms(10);
    gpio_put(E,0);
    //sleep_ms(10);


}
/*Escribe caractares en el Display*/
void lcd_put_char(char *data){
    uint8_t i=0;
    while (*(data+i) != '\0') {
        int decimal= (long)*(data+i);//Obtenemos el codigo ascii
        for (int j=0;j<8;j++){
            gpio_put(pines[j],decimal % 2);
           // printf("Bit:%d.\n",decimal % 2);
            decimal /= 2;
            //sleep_ms(10);
        }
        gpio_put(RS,1);
        gpio_put(E,1); 
        sleep_ms(10);
        gpio_put(E,0);
        i++;
        if(i>15){
            sleep_ms(1000);
            lcd_shift_screen(0,1);
            
        }
    }
}