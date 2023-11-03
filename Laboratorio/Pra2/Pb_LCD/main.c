#include <stdio.h>
#include "pico/stdlib.h"

#include "lcd.h"
//#include "timer.h"
char fil1[] = "  Mi Dayanita Te amo";
//char fil2[] = "    Te Amo";
int main() {
    // STDIO: inicialización de USB-UART para entrada/salida
    stdio_init_all();
    lcd_init();
    sleep_ms(50);
    lcd_put_char(fil1);
    //lcd_shift_init(1);
    //lcd_put_char(fil2);
    sleep_ms(5000);
    lcd_display_on_off(1,0,0);
    //lcd_shift_screen(0,5);
    //lcd_shift_init(0);
    //lcd_shift_cursor(1);
    while (true) {
        // Entrar en modo de bajo consumo
        //__asm volatile ("wfi");

    }
 
    return 0;
}