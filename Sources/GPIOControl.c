//! Copyright (c) Enerzai. All rights reserved.
//! This project is not an open source. 
//! It cannot be used & viewed without permissions from Enerzai corp.
//! Written by Justin Kim

#include <GPIOControl.h>
#include <os_hal_gpio.h>

void InitLED()
{
	mtk_os_hal_gpio_set_direction(8, 1);
	mtk_os_hal_gpio_set_direction(9, 1);
	mtk_os_hal_gpio_set_direction(10, 1);

}
void SetRed(char val)
{
	mtk_os_hal_gpio_set_output(8, val);
}

void SetGreen(char val)
{
	mtk_os_hal_gpio_set_output(9, val);
}

void SetBlue(char val)
{
	mtk_os_hal_gpio_set_output(10, val);
}

void Error()
{
	SetGreen(1);
	SetBlue(1);
	printf("Error occured ! - halting the execution.. \n");
	while (1)
	{
		SetRed(0);
	}
}