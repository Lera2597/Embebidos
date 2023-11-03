#ifndef _GETVALUE_H
#define _GETVALUE_H

#define MIN_DELAY_VALUE 200
#define MAX_DELAY_VALUE 1500
#define MIN_TEMPERATURA_VALUE 0
#define MAX_TEMPERATURA_VALUE 149
#define MIN_VOLTAGE_VALUE 0
#define MAX_VOLTAGE_VALUE 3
#define ENTER           13

uint32_t GetValueFromTerminal(void);
void ShowMenuInTerminal(void);
uint32_t GetValueMenu(void);
void ShowVariables(float variable1, uint32_t variable2);
void ErrorMenu(void);
void ChangeVariables(void);

#endif