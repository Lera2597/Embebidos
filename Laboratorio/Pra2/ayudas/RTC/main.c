#include <stdio.h>
#include "pico/stdlib.h"

#include "pico/util/datetime.h"

#include "rtc.h"
 
int main() {
    stdio_init_all();
    printf("Hello RTC!\n");
 
    char datetime_buf[256];
    char *datetime_str = &datetime_buf[0];
 
    // Start on Friday 5th of June 2020 15:45:00
    datetime_t t = {
            .year  = 2020,
            .month = 06,
            .day   = 05,
            .dotw  = 5, // 0 is Sunday, so 5 is Friday
            .hour  = 15,
            .min   = 45,
            .sec   = 00
    };
    // Start on Friday 5th of June 2020 15:45:00
    datetime_t alarma = {
            .year  = 2020,
            .month = 06,
            .day   = 05,
            .dotw  = 5, // 0 is Sunday, so 5 is Friday
            .hour  = 15,
            .min   = 46,
            .sec   = 00
    }; 
 
    // Start the RTC
    rtc_init();
    rtc_set_datetime(&t);
    rtc_alarm_init(&alarma);
 
    // Print the time
    while (true) {
        if(alarm_req){
            alarm_req=false;
            printf("alarma activada.\n");
        }
        rtc_get_datetime(&t);
        datetime_to_str(datetime_str, sizeof(datetime_buf), &t);
        printf("\r%s      ", datetime_str);
        sleep_ms(100);
    }
 
    return 0;
}