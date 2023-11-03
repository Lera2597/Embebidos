#ifndef _LCD_H
#define _LCD_H

void lcd_init();
void lcd_clear();
void lcd_shift_init(bool fila);
void lcd_shift_screen(bool sentido,uint8_t num_shift);
void lcd_shift_cursor(bool sentido);
void lcd_display_on_off(bool display,bool cursor,bool blink);
void lcd_put_char(char *data);

/*void lcd_put_char(char *data);

typedef union {
    uint8_t WORD;
	struct {
		uint8_t BIT0 : 1;
		uint8_t BIT1 : 1;
		uint8_t BIT2 : 1;
		uint8_t BIT3 : 1;
		uint8_t BIT4 : 1;
		uint8_t BIT5 : 1;
		uint8_t BIT6 : 1;
		uint8_t BIT7 : 1;
	}BITS;
}_lcd_str;

extern volatile _lcd_str lcd_control;

#define LCD_DATA	lcd_control.WORD 
#define DB0		lcd_control.BITS.BIT0
#define DB1		lcd_control.BITS.BIT1
#define DB2		lcd_control.BITS.BIT2
#define DB3		lcd_control.BITS.BIT3
#define DB4		lcd_control.BITS.BIT4
#define DB5		lcd_control.BITS.BIT5
#define DB6		lcd_control.BITS.BIT6
#define DB7		lcd_control.BITS.BIT7*/
#endif