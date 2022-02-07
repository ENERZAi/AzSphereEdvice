//! Copyright (c) Enerzai. All rights reserved.
//! This project is not an open source. 
//! It cannot be used & viewed without permissions from Enerzai corp.
//! Written by Justin Kim

#include <BMI160.h>
#include <stdint.h>
#include "printf.h"

const int isu= 2;


bool InitBMI160()
{
	if (mtk_os_hal_i2c_ctrl_init(isu) != 0 || mtk_os_hal_i2c_speed_init(isu, I2C_SCL_200kHz) != 0)
	{
		printf("I2C initialization failure\n");
	}
	
	printf("I2C Initialized");
	uint8_t reg = ACC_SET_PMU_MODE | 0x01;
	uint8_t packet[] = { (uint8_t)CMD, (uint8_t)reg };
	if (mtk_os_hal_i2c_write(isu, (uint16_t)(BMI160_ADDR_PULLUP), packet, 2) != 0)
	{
		printf("InitBMI160 - I2C write failure\n");
		return false;
	}
	

	enum AccRange range = SENS_2G;
	enum AccUnderSampling us = ACC_US_OFF;
	enum AccBandWidthParam bwp = ACC_BWP_2;
	enum AccOutputDataRate odr = ACC_ODR_11;

	uint8_t data[3];
	data[0] = ACC_CONF;
	data[1] = ((us << ACC_US_POS) | (bwp << ACC_BWP_POS) |
		(odr << ACC_ODR_POS));
	data[2] = range;

	if (mtk_os_hal_i2c_write(isu, (uint16_t)(BMI160_ADDR_PULLUP), data, 2) != 0)
	{
		printf("InitBMI160 - I2C write failure\n");
		return false;
	}
	return true;
}

bool ReadBMI160(uint8_t* data)
{
	uint8_t reg = 18;
	if (mtk_os_hal_i2c_write_read(isu, (uint16_t)(BMI160_ADDR_PULLUP), &reg, data, 1, 6) < 0)
	{
		return false;
	}
	return true;
}

bool GetSensorData(float* xData, float* yData, float* zData)
{
	uint8_t localData[6];
	static int16_t lastXRaw;
	static int16_t lastYRaw;
	static int16_t lastZRaw;
	int16_t xRaw = 0;
	int16_t yRaw = 0;
	int16_t zRaw = 0;

	do {
		if (!ReadBMI160(localData))
			return false;

		xRaw = (localData[1] << 8) | localData[0];
		yRaw = (localData[3] << 8) | localData[2];
		zRaw = (localData[5] << 8) | localData[4];
	} while (lastXRaw == xRaw && lastYRaw == yRaw && lastZRaw == zRaw);

	lastXRaw = xRaw;
	lastYRaw = yRaw;
	lastZRaw = zRaw;

	float xScaled = (xRaw / SENS_2G_LSB_PER_G);
	float yScaled = (yRaw / SENS_2G_LSB_PER_G);
	float zScaled = (zRaw / SENS_2G_LSB_PER_G);

	*xData = xScaled;
	*yData = yScaled;
	*zData = zScaled;

	return true;
}

bool FillSensorData(float* dataBuffer, int size)
{
	for (int i = 0; i < size; ++i)
	{
		float x, y, z;
		if (!GetSensorData(&x, &y, &z))
			return false;
		dataBuffer[3 * i] = x;
		dataBuffer[3 * i + 1] = y;
		dataBuffer[3 * i + 2] = z;
	}
	return true;
}
