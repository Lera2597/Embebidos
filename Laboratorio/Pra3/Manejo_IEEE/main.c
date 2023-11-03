#include <stdio.h>
#include "pico/stdlib.h"

void ieee(int p_int,float p_dec);

typedef union {
	uint16_t WORD;		// Acceso a todo el registro
	struct {
		uint16_t BIT0	:1;	  									
		uint16_t BIT1	:1;	  									
		uint16_t BIT2	:1;		  								
		uint16_t BIT3	:1;	  								
		uint16_t BIT4	:1;	  									
		uint16_t BIT5	:1;	  							
		uint16_t BIT6	:1;	  									
		uint16_t BIT7   :1;   									
		uint16_t BIT8	:1;   								
		uint16_t BIT9   :1;   									
		uint16_t BIT10  :1;   							
		uint16_t BIT11  :1;   							
		uint16_t BIT12  :1;   							
		uint16_t BIT13  :1;   							
		uint16_t BIT14  :1;   									
		uint16_t BIT15  :1;   								
	} BITS;
} ieee_16;

volatile ieee_16 _ieee;
#define r_ieee	         _ieee.WORD;
#define ieee_b0	    	_ieee.BITS.BIT0;
#define ieee_b1	    	_ieee.BITS.BIT1;
#define ieee_b2	    	_ieee.BITS.BIT2;
#define ieee_b3	    	_ieee.BITS.BIT3;
#define ieee_b4	    	_ieee.BITS.BIT4;
#define ieee_b5	    	_ieee.BITS.BIT5;
#define ieee_b6	    	_ieee.BITS.BIT6;
#define ieee_b7	    	_ieee.BITS.BIT7;
#define ieee_b8	    	_ieee.BITS.BIT8;
#define ieee_b9	    	_ieee.BITS.BIT9;
#define ieee_b10		_ieee.BITS.BIT10;
#define ieee_b11		_ieee.BITS.BIT11;
#define ieee_b12		_ieee.BITS.BIT12;
#define ieee_b13		_ieee.BITS.BIT13;
#define ieee_b14		_ieee.BITS.BIT14;
#define ieee_b15		_ieee.BITS.BIT15;

int main() {
    // STDIO: inicialización de USB-UART para entrada/salida
    stdio_init_all();
    sleep_ms(500);
    printf("paso1.\n");
    ieee(7,31);
    printf("paso2.\n");
    return 0;
}

void ieee(int p_int,float p_dec){
    // ***************** binarizamos el numero entero*********
    uint8_t bin[10];
    uint8_t i=0;
    uint8_t index_last1=0;
    while(p_int != 0){
        bin[i]=p_int % 2;
        if (bin[i]){
            index_last1 = i
        }
        p_int= p_int/2;
        i++;
    }
    // ***************** binarizamos el numero flotante*********
    //float  p_dec;
    int carry = 0;
    while(p_dec > 1){
        p_dec= p_dec/10;
    }
    for (uint8_t i=0;i<5;i++){
        carry = (int)(p_dec*2);
        sleep_ms(100);
        printf("cerry: %d.\n",carry);

        p_dec = p_dec*2 -carry;
        if(p_dec==0){
            break;
        }
    }
    //agregamos los bits a la mantiza
    uint8_t t_mantisa= 10; 
    while()


}