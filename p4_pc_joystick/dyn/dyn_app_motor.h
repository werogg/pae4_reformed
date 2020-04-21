/*
 * dyn_sensor.h
 *
 *  Created on: 18 mar. 2020
 *      Author: droma
 */

#ifndef DYN_MOTOR_H_
#define DYN_MOTOR_H_

#include "dyn_frames.h"

enum rotation_direction
{
	ROTATE_LEFT,
	ROTATE_RIGHT
};

int read_moving_speed(uint8_t id, uint16_t* readed_value);

int write_moving_speed(uint8_t id, uint16_t speed);

int move_backward(uint8_t id_left_wheel, uint8_t id_right_wheel, unsigned int speed);
int move_forward(uint8_t id_left_wheel, uint8_t id_right_wheel, unsigned int speed);
int move_wheel(uint8_t id, enum rotation_direction direction, unsigned int speed);
int move_continue(uint8_t id);

#endif /* DYN_MOTOR_H_ */
