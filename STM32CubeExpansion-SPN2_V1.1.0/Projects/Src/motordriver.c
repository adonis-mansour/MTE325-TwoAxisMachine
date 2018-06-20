#include "example.h"
#include "example_usart.h"
#include "params.h"
#include "xnucleoihm02a1.h"
#include "MotorDriver.h"

void InitializeMotors(void)
{
  uint32_t Step;
  uint32_t Speed;
  uint8_t MovementPerRevolution;
  uint8_t i;
  uint8_t board, device;
  
  uint8_t id;
  
  StepperMotorBoardHandle_t *StepperMotorBoardHandle;
  MotorParameterData_t *MotorParameterDataGlobal, *MotorParameterDataSingle;
  
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