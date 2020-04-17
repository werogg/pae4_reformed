/*
 * dyn_sensor.h
 *
 *  Created on: 18 mar. 2020
 *      Author: droma
 */

#ifndef DYN_MOTOR_H_
#define DYN_MOTOR_H_

#include "dyn_frames.h"

int read_moving_speed(uint8_t id, uint16_t* readed_value);

int write_moving_speed(uint8_t id, uint16_t speed);

#endif /* DYN_MOTOR_H_ */
