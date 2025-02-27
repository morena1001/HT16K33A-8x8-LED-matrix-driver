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
HAL_StatusTypeDef HT16K33A_Init (HT16K33A_t *device, I2C_HandleTypeDef *i2c_handle, uint8_t dev_addr) {
	device->i2c_handle = i2c_handle;
	device->addr = (dev_addr << 1);

	HAL_StatusTypeDef status;

	// System setup : Turn on internal system oscillator
	status = HT16K33A_Byte_WriteCommand (device, HT16K33A_COMMAND_SYSTEM_SETUP (HT16K33A_POWER_ON));
	HAL_Delay (1);
	if (status != HAL_OK)	return status;

	// INT/ROW output pin is set to ROW driver output : NO INT pin available on sensor breakout board
	status = HT16K33A_Byte_WriteCommand (device, HT16K33A_COMMAND_ROWINT_SETUP);
	HAL_Delay (1);
	if (status != HAL_OK)	return status;

	// Dimming set : Set dimming to 14/16 duty
	status = HT16K33A_Byte_WriteCommand (device, HT16K33A_COMMAND_DISPLAY_DIMMING_SETUP (1, 1, 1, 1));
	HAL_Delay (1);
	if (status != HAL_OK)	return status;

	// Reset all display RAM data
	uint8_t data[8] = {0x00};
	HT16K33A_SetAll (device, data);

	// Blinking set : Set display on, and blinking frequency off
	status = HT16K33A_Byte_WriteCommand (device, HT16K33A_COMMAND_DISPLAY_SETUP_S (HT16K33A_BLINKING_OFF, HT16K33A_DISPLAY_ON));
	HAL_Delay (1);
	return status;
}

/*
 * LED FUNCTIONS
 */

HAL_StatusTypeDef HT16K33A_SetRow (HT16K33A_t *device, uint8_t row, uint8_t map) {
	if (row > 0x7)	return HAL_ERROR;

	HAL_StatusTypeDef status = HT16K33A_Byte_WriteData (device, row, &map);
	if (status != HAL_OK)	return status;
	return HT16K33A_Byte_WriteData (device, row + 0x1, &map);
}

HAL_StatusTypeDef HT16K33A_SetColumn (HT16K33A_t *device, uint8_t col, uint8_t map) {
	if (col > 0x7)	return HAL_ERROR;

	uint8_t data[16];
	for (uint8_t i = 0; i < 8; i++) {
		data[i * 2] = (((map >> i) & 0x1) << col);
		data[(i * 2) + 1] = (((map >> i) & 0x1) << col);
	}

	return HT16K33A_Page_WriteData (device, 0x0, data, 16);
}

HAL_StatusTypeDef HT16K33A_SetSingle (HT16K33A_t *device, uint8_t row, uint8_t col, uint8_t value) {
	if (row > 0x7 || col > 0x7)		return HAL_ERROR;

	uint8_t data = (value << col);

	HAL_StatusTypeDef status = HT16K33A_Byte_WriteData(device, row, &data);
	if (status != HAL_OK)	return status;
	return HT16K33A_Byte_WriteData(device, row + 0x01, &data);
}

HAL_StatusTypeDef HT16K33A_SetAll (HT16K33A_t *device, uint8_t *data) {
	uint8_t data_2[16];
	for (uint8_t i = 0; i < 8; i++) {
		data_2[i * 2] = *(data + i);
		data_2[(i * 2) + 1] = *(data + i);
	}

	return HT16K33A_Page_WriteData (device, 0x0, data_2, 16);
}

/*
 * LOW LEVEL FUNCTIONS
 */

HAL_StatusTypeDef HT16K33A_Byte_WriteCommand (HT16K33A_t* device, uint8_t command) {
	return HAL_I2C_Master_Transmit (device->i2c_handle, device->addr, &command, 1, HAL_MAX_DELAY);
}

HAL_StatusTypeDef HT16K33A_Byte_WriteData (HT16K33A_t* device, uint8_t command, uint8_t* data) {
	return HAL_I2C_Mem_Write (device->i2c_handle, device->addr, command, I2C_MEMADD_SIZE_8BIT, data, 1, HAL_MAX_DELAY);
}

HAL_StatusTypeDef HT16K33A_Page_WriteData (HT16K33A_t* device, uint8_t command, uint8_t* data, uint8_t size) {
	return HAL_I2C_Mem_Write (device->i2c_handle, device->addr, command, I2C_MEMADD_SIZE_8BIT, data, size, HAL_MAX_DELAY);
}

HAL_StatusTypeDef HT16K33A_Byte_ReadData (HT16K33A_t* device, uint8_t command, uint8_t* data) {
	if (HAL_I2C_Master_Transmit (device->i2c_handle, device->addr, &command, 1, HAL_MAX_DELAY) != HAL_OK)
		return HAL_ERROR;

	return HAL_I2C_Master_Receive (device->i2c_handle, (device->addr | 0x1), data, 1, HAL_MAX_DELAY);
}
HAL_StatusTypeDef HT16K33A_Page_ReadData (HT16K33A_t* device, uint8_t command, uint8_t* data, uint8_t size) {
	if (HAL_I2C_Master_Transmit (device->i2c_handle, device->addr, &command, 1, HAL_MAX_DELAY) != HAL_OK)
			return HAL_ERROR;

	return HAL_I2C_Master_Receive (device->i2c_handle, (device->addr | 0x1), data, size, HAL_MAX_DELAY);
}
