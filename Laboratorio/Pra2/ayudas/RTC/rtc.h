#ifndef _RTC_H
#define _RTC_H

extern volatile uint8_t alarm_req;

void rtc_alarm_init(datetime_t *t);

#endif