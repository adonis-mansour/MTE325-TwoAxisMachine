#include "stdint.h"
#ifndef __MOTORDRIVER_H
#define __MOTORDRIVER_H

#ifdef __cplusplus
 extern "C" {
#endif

#define FWD ((uint8_t)1)
#define REV ((uint8_t)0)

void InitializeMotors(void);
void stop(void);
void run(uint8_t direction, uint32_t speed);

#endif /* __EXAMPLE_H */