/*
 * HT16K33A.h
 *
 *  Created on: Feb 25, 2025
 *      Author: josue
 */

#ifndef INC_HT16K33A_H_
#define INC_HT16K33A_H_

#include "stm32f3xx_hal.h" // NEEDED FOR I2C

/*
 * DEFINES
 */

#define HT16K33A_ADDR_1 	0x70
#define HT16K33A_ADDR_2 	0x71
#define HT16K33A_ADDR_3 	0x72
#define HT16K33A_ADDR_4 	0x73
#define HT16K33A_ADDR_5 	0x74
#define HT16K33A_ADDR_6 	0x75
#define HT16K33A_ADDR_7 	0x76
#define HT16K33A_ADDR_8 	0x77

/*
 * COMMANDS
 */

#define HT16K33A_COMMAND_SYSTEM_SETUP(S) 							(0x20 | (S != 0))
#define HT16K33A_COMMAND_ROWINT_SETUP 								 0xA0
#define HT16K33A_COMMAND_DISPLAY_SETUP(B1, B0, D) 					(0x80 | ((B1 != 0) << 2) | ((B0 != 0) << 1) | (D != 0))
#define HT16K33A_COMMAND_DISPLAY_SETUP_S(B, D) 						(0x80 | ((B & 0x3) << 1) | (D != 0))
#define HT16K33A_COMMAND_DISPLAY_DIMMING_SETUP(P3, P2, P1, P0)		(0xE0 | ((P3 != 0) << 3) | ((P2 != 0) << 2) | ((P1 != 0) << 1) | (P0 != 0))

#define HT16K33A_COMMAND_ROW_ADDR_POINTER(An) 						(An)

/*
 * SHORTCUTS
 */

#define HT16K33A_STAND_BY			0x0
#define HT16K33A_POWER_ON			0x1
#define HT16K33A_DISPLAY_ON 		0x1
#define HT16K33A_DISPLAY_OFF 		0x0
#define HT16K33A_BLINKING_OFF 		0x0
#define HT16K33A_BLINKING_2Hz 		0x1
#define HT16K33A_BLINKING_1Hz 		0x2
#define HT16K33A_BLINKING_halfHz	0x3

#define HT16K33A_ROW0_ADDR 			0x00
#define HT16K33A_ROW1_ADDR 			0x02
#define HT16K33A_ROW2_ADDR 			0x04
#define HT16K33A_ROW3_ADDR 			0x06
#define HT16K33A_ROW4_ADDR 			0x08
#define HT16K33A_ROW5_ADDR 			0x0A
#define HT16K33A_ROW6_ADDR 			0x0C
#define HT16K33A_ROW7_ADDR 			0x0E

/*
 * SENSOR STRUCT
 */

typedef struct {
	I2C_HandleTypeDef* i2c_handle;
	uint8_t addr;

} HT16K33A_t;

/*
 * INITIALIZATION
 */

HAL_StatusTypeDef HT16K33A_Init (HT16K33A_t *device, I2C_HandleTypeDef *i2c_handle, uint8_t dev_addr);

/*
 * LED FUNCTIONS
 */

HAL_StatusTypeDef HT16K33A_SetRow (HT16K33A_t *device, uint8_t row, uint8_t map);
HAL_StatusTypeDef HT16K33A_SetColumn (HT16K33A_t *device, uint8_t col, uint8_t map);
HAL_StatusTypeDef HT16K33A_SetSingle (HT16K33A_t *device, uint8_t row, uint8_t col, uint8_t value);
HAL_StatusTypeDef HT16K33A_SetAll (HT16K33A_t *device, uint8_t *data);

/*
 * LOW LEVEL FUNCTIONS
 */

HAL_StatusTypeDef HT16K33A_Byte_WriteCommand (HT16K33A_t* device, uint8_t command);
HAL_StatusTypeDef HT16K33A_Byte_WriteData (HT16K33A_t* device, uint8_t command, uint8_t* data);
HAL_StatusTypeDef HT16K33A_Page_WriteData (HT16K33A_t* device, uint8_t command, uint8_t* data, uint8_t size);

HAL_StatusTypeDef HT16K33A_Byte_ReadData (HT16K33A_t* device, uint8_t command, uint8_t* data);
HAL_StatusTypeDef HT16K33A_Page_ReadData (HT16K33A_t* device, uint8_t command, uint8_t* data, uint8_t size);

#endif /* INC_HT16K33A_H_ */
