/*
 * controller.h
 *
 *  Created on: 27 de nov de 2019
 *      Author: Jessen
 */

#ifndef MYLIBS_CONTROLLER_H_
#define MYLIBS_CONTROLLER_H_

void setRpmX(int rpm);
void setRpmY(int rpm);
void setRpmZ(int rpm);
void setRpmS(int rpm);
void stepX(int steps);
void stepY(int steps);
void stepZ(int steps);
void stepS(int steps);
void interpolation(int x, int y, int z);

#endif /* MYLIBS_CONTROLLER_H_ */
