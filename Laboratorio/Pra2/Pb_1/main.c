#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/util/datetime.h"

#include "gpio.h"
#include "timer.h"
#include "keyboard.h"
#include "lcd.h"

#define time_shift_ 100 //10*T_timer=10*10m=100m
//******Variables****************

uint8_t estado_stm = 0;
uint8_t estado_fecha = 0;

// Variables lcd 
bool shift =true;
int num_shift=-1;
bool deadline_shift= false;
uint8_t time_shift = time_shift_;
// variables keyboard
char key = 0;
uint8_t time_debounce = debounce;
bool init_debounce=true;
//---------------------------
// Variable para el RTC 
int16_t ano = 0;
int8_t mes = 0;
int8_t dia = 0;
int8_t dia_sem = 0;
int8_t hora = 0;
int8_t min = 0;
int8_t sec = 0;

char datetime_buf[256];
char size_fecha=0;
char *datetime_str = &datetime_buf[0]; 
bool init_cnfg = true;
int acum=0;

// *****Funciones***********
void set_datos(uint8_t estado);



int main() {
    // STDIO: inicialización de USB-UART para entrada/salida
    stdio_init_all();
    keyboard_init();// inicializamos el keyboard 
    lcd_init();
    timer_init(TIMER_PERIOD_MS);

    // Start on Friday 5th of June 2020 15:45:00
    datetime_t t = {
            .year  = 2022,
            .month = 01,
            .day   = 22,
            .dotw  = 6, // 0 is Sunday, so 5 is Friday
            .hour  = 00,
            .min   = 00,
            .sec   = 00
    };
    rtc_init();
    rtc_set_datetime(&t); 
    
    while (true) {
    
        if(gpio_req){
            //timer_init_(TIMER_PERIOD_MS);
            ///pendiente el contador de tecldo
            time_debounce = debounce;
            init_debounce=true;
            printf("paso\n");
            //start_timer = true;
            gpio_req = false;
        }
        if(timer_req){
            if(--time_shift ==0){
                deadline_shift=true;
                //printf("paso\n");

            }
            if((--time_debounce == 0) & init_debounce){
                init_debounce=false;
                key = capture_key();
                printf("tecla: %c\n",key);
            }
            
            //start_timer = false;
            timer_req = false;
        }
        if(key == 'A'){
            lcd_clear();
            shift= true;
            estado_stm ++;
            estado_fecha=0;
            init_cnfg = true;
            if(estado_stm==3){
                estado_stm = 0;
            }
            key=0;
        }
        else if (key == 'B'){
            lcd_clear();
            init_cnfg = true;
            estado_fecha ++;
            if(estado_fecha==7){
                estado_fecha = 0;
            }
            key=0;          
        }
        else{
            
        }
        switch(estado_stm){
            /*estado normal del reloj*/
            case 0:
                //printf("estado activo.\n");
                if(shift){
                    shift=false;
                    rtc_set_datetime(&t); 
                    lcd_display_on_off(1,0,0);   
                    lcd_put_char(datetime_str);
                }
                rtc_get_datetime(&t);
                datetime_to_str(datetime_str, sizeof(datetime_buf), &t);

                
                size_fecha=0;
                /*Calcula la cantidad de caracteres tiene la fecha*/
                while(*(datetime_str+size_fecha) != '\0'){
                    size_fecha++;
                }
                /*calculamos cuantas posiciones se desplaza la fecha en el display*/
                if(num_shift <0){
                    num_shift= size_fecha-16;
                    lcd_clear();

                    lcd_put_char(datetime_str);
                }
                /* Despalzamos la fecha por el display */
                if(num_shift >= 0){
                    if(deadline_shift ){
                        num_shift--;
                        lcd_shift_screen(0,1);
                        time_shift=time_shift_;
                        deadline_shift=false;
                    }
                }
                /* retornamos la Fecha al origen del display*/
                else{
                    lcd_clear();
                    lcd_put_char(datetime_str);
                    num_shift=size_fecha-16;
                }
                
            break;
            /*estado configuracion del reloj*/
            case 1:
            case 2:
                /* configuracion fecha*/
                if(estado_stm ==1 & init_cnfg==true ){
                    
                    //printf("Configuracion reloj.\n");
                    lcd_put_char("config reloj");
                    lcd_display_on_off(1,1,1);
                    lcd_shift_init(1);
                    set_datos(estado_fecha);
                    init_cnfg=false;
                    //sleep_ms(800);
                    //lcd_clear();
                    //set_datos(estado_fecha); 
                }
                /*configuracion alarma*/
                else if(estado_stm == 2 & init_cnfg==true){
                    
                    lcd_put_char("congfig alarma");
                    lcd_display_on_off(1,1,1);
                    lcd_shift_init(1);
                    set_datos(estado_fecha);
                    init_cnfg=false;
                    //sleep_ms(800);
                    //lcd_clear();
                    //set_datos(estado_fecha);
                }
                if(key >= '0' && key <= '9'){

                    acum = acum*10 + (key & 0x0F); // Convertir ASCII a INT y acumular
                }
                /*
                datetime_t t = {
                .year  = ano,
                .month = mes,
                .day   = dia,
                .dotw  = dia_sem, // 0 is Sunday, so 5 is Friday
                .hour  = hora,
                .min   = min,
                .sec   = sec,
                };
                //rtc_init();
                //rtc_set_datetime(&t);*/
            break;
            default:
            break;
        
        }
        // Entrar en modo de bajo consumo
        //__asm volatile ("wfi");

    }
 
    return 0;
}
void set_datos(uint8_t estado){
    switch (estado)
    {
    case 0:
        lcd_put_char("ano: ");

    break;
    case 1:
        //printf("Mes: .\n");
        lcd_put_char("Mes: ");
    break;
    case 2:
        //printf("Dia: .\n");
        lcd_put_char("Dia: ");
    break;
    case 3:
        //printf("Dia_semana: .\n");
        lcd_put_char("Dia semana: ");
    break;
    case 4:
        //printf("Hora: .\n");
        lcd_put_char("Hora: ");
    break;
    case 5:
        //printf("Minuto: .\n");
        lcd_put_char("Minito: ");
    break;
    case 6:
        //printf("Segundo: .\n");
        lcd_put_char("Segundo: ");
    break;  
    default:
        //printf("ERROR.\n");
        lcd_put_char("Error");
    }
}