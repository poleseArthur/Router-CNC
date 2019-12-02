/*
 * controller.cpp
 *
 *  Created on: 27 de nov de 2019
 *      Author: Jessen
 */

#include <Stepper.h>
#include <Arduino.h>

const int stepsPerRevolution = 20;
Stepper eixoX(stepsPerRevolution, 2, 3, 4, 5);
Stepper eixoY(stepsPerRevolution, 6, 7, 8, 9);
Stepper eixoZ(stepsPerRevolution, 10, 11, 12, 13);
Stepper eixoS(stepsPerRevolution, 44, 46);

void setRpmX(int rpm){
	eixoX.setSpeed(rpm);
}

void stepX(int steps){
	eixoX.step(steps);
}

void setRpmY(int rpm){
	eixoY.setSpeed(rpm);
}

void stepY(int steps){
	eixoY.step(steps);
}

void setRpmZ(int rpm){
	eixoZ.setSpeed(rpm);
}

void stepZ(int steps){
	eixoZ.step(steps);
}

void setRpmS(int rpm){
	eixoS.setSpeed(rpm);
}

void stepS(int steps){
	eixoS.step(steps);
}



