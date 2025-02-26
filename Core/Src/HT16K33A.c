/*
 * HT16K33A.c
 *
 *  Created on: Feb 25, 2025
 *      Author: josue
 */

#include "HT16K33A.h"

/*
 * INITIALIZATION
 */

// FOR INIT FUNCTION CLEAR ALL RAM DATA BEFORE LED DISPLAY COMMAND IS ACTIVATED
uint8_t HT16K33A_Init (HT16K33A_t *device, I2C_HandleTypeDef *i2c_handle, uint8_t dev_addr) {
	return 0;
}

/*
 * LED FUNCTIONS
 */

HAL_StatusTypeDef HT16K33A_SetRow (HT16K33A_t *device, uint8_t row) {
	return HAL_OK;
}

HAL_StatusTypeDef HT16K33A_SetColumn (HT16K33A_t *device, uint8_t col) {
	return HAL_OK;
}

HAL_StatusTypeDef HT16K33A_SetSingle (HT16K33A_t *device, uint8_t row, uint8_t col) {
	return HAL_OK;
}

HAL_StatusTypeDef HT16K33A_SetAll (HT16K33A_t *device, uint8_t *data) {
	return HAL_OK;
}

/*
 * LOW LEVEL FUNCTIONS
 */
// FOR WRITE USE HAL_I2C_Master_Transmit AND FOR READ WRITE, CHECK IF THE COMMAND IS WRITABLE OR READABLE

HAL_StatusTypeDef HT16K33A_Byte_WriteCommand (HT16K33A_t* device, uint8_t command) {
	return HAL_OK;
}

HAL_StatusTypeDef HT16K33A_Byte_WriteData (HT16K33A_t* device, uint8_t reg, uint8_t* data) {
	return HAL_OK;
}

HAL_StatusTypeDef HT16K33A_Page_WriteData (HT16K33A_t* device, uint8_t reg, uint8_t* data) {
	return HAL_OK;
}

HAL_StatusTypeDef HT16K33A_Byte_ReadData (HT16K33A_t* device, uint8_t reg, uint8_t* data) {
	return HAL_OK;
}
HAL_StatusTypeDef HT16K33A_Page_ReadData (HT16K33A_t* device, uint8_t reg, uint8_t* data) {
	return HAL_OK;
}
