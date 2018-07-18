#include "stdint.h"
#include "stdint.h"
#include "example.h"
#include "example_usart.h"
#include "params.h"
#include "xnucleoihm02a1.h"

#ifndef __MOTORDRIVER_H
#define __MOTORDRIVER_H

#ifdef __cplusplus
 extern "C" {
#endif

#define FWD ((uint8_t)1)
#define REV ((uint8_t)0)

uint16_t LSFWD = GPIO_PIN_8;
uint16_t LSREV = GPIO_PIN_6;

void InitializeMotors(void);
int32_t adc_to_speed(uint16_t adcValue);
void speed_to_motor(int32_t speed);
void stop_motor(void);
void run_motor(uint8_t direction, uint32_t speed);

#endif /* __EXAMPLE_H */
