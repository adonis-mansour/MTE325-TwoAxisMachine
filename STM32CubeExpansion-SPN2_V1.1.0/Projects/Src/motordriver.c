#include "stdint.h"
#include "example.h"
#include "example_usart.h"
#include "params.h"
#include "xnucleoihm02a1.h"
#include "motordriver.h"

 uint32_t Step;
 uint32_t Speed;
 uint8_t MovementPerRevolution;
 uint8_t i;
 uint8_t board, device;
 uint8_t id;
 
 uint16_t LSFWD = GPIO_PIN_8;
 uint16_t LSREV = GPIO_PIN_6;
 

// #define LSLS
// #define LSRS
  
 StepperMotorBoardHandle_t *StepperMotorBoardHandle;
 MotorParameterData_t *MotorParameterDataGlobal, *MotorParameterDataSingle;

void InitializeMotors(void)
{ 
	
  #ifdef NUCLEO_USE_USART
  USART_Transmit(&huart2, "Initial values for registers:\n\r");
  USART_PrintAllRegisterValues();
  #endif

  /* Setup each X-NUCLEO-IHM02A1 Expansion Board ******************************/
  
  /* Get the parameters for the motor connected with the 1st stepper motor driver of the 1st stepper motor expansion board */
  MotorParameterDataGlobal = GetMotorParameterInitData();
  
	// configures motors from database
  for (id = 0; id < EXPBRD_MOUNTED_NR; id++)
  {
    StepperMotorBoardHandle = BSP_GetExpansionBoardHandle(EXPBRD_ID(id));
    MotorParameterDataSingle = MotorParameterDataGlobal+(id*L6470DAISYCHAINSIZE);
    StepperMotorBoardHandle->Config(MotorParameterDataSingle);
  }
  
  #ifdef NUCLEO_USE_USART
  USART_Transmit(&huart2, "Custom values for registers:\n\r");
  USART_PrintAllRegisterValues();
  #endif

//  for (board = EXPBRD_ID(0); board <= EXPBRD_ID(EXPBRD_MOUNTED_NR-1); board++)
//  {
//    
//    for (device = L6470_ID(0); device <= L6470_ID(L6470DAISYCHAINSIZE-1); device++)
//    {
//      /* Prepare the stepper driver to be ready to perform a command */
//      StepperMotorBoardHandle->StepperMotorDriverHandle[device]->Command->PrepareHardHiZ(device);
//    }
//    
//    StepperMotorBoardHandle->Command->PerformPreparedApplicationCommand();
//  }

}

void stop_motor(void)
{
	USART_Transmit(&huart2, "Stopping Motor\n\r");
	StepperMotorBoardHandle->Command->SoftStop(board, device);
}

void run_motor(uint8_t direction, uint32_t speed)
{
	USART_Transmit(&huart2, "Running Motor.\n\r");
	USART_Transmit(&huart2, num2hex(LSFWD, WORD_F));
	if ((direction == FWD ) && (HAL_GPIO_ReadPin(GPIOB, LSFWD) == GPIO_PIN_RESET)) {
		USART_Transmit(&huart2, "FWD\n\r");
		StepperMotorBoardHandle->Command->Run(board, device, L6470_DIR_FWD_ID, speed);
	}
	else if ((direction == REV) && (HAL_GPIO_ReadPin(GPIOB, LSREV) == GPIO_PIN_RESET)) {
		USART_Transmit(&huart2, "REV\n\r");
		StepperMotorBoardHandle->Command->Run(board, device, L6470_DIR_REV_ID, speed);
	}
}