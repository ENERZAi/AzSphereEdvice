//! Copyright (c) Enerzai. All rights reserved.
//! This project is not an open source. 
//! It cannot be used & viewed without permissions from Enerzai corp.
//! Written by Justin Kim

#ifndef GPIO_CONTROL_H
#define GPIO_CONTROL_H
#include <stdint.h>

void InitLED();

void SetRed(char val);

void SetGreen(char val);

void SetBlue(char val);

void Error();

#endif