/*
 * dyn_sensor.c
 *
 *  Created on: 18 mar. 2020
 *      Author: droma
 *
 * TODO: High-level functions like "distance_wall_front", etc
 * TODO: Generate another file for motors, with functions like "move_forward", etc
 */
#include "dyn/dyn_app_motor.h"
#include "dyn/dyn_instr.h"
#include <stdio.h>

/**
 * Write the moving speed value
 *
 * Write a value on the moving speed address of a specified device
 *
 * @param[in] id Device ID
 * @param[in] speed Speed value to be stored
 * @return Error code to be treated at higher levels
 */
int write_moving_speed(uint8_t id, uint16_t speed)
{
	uint8_t first_byte = (uint8_t) (speed & 0xff);
	uint8_t second_byte = (uint8_t) (speed >> 8);
	uint8_t params[2];
	params[0] = first_byte;
	params[1] = second_byte;

	return dyn_write_data(id, 0x20, 2, params);
}

/**
 * Read the moving speed value
 *
 * Read a value on the moving speed address of a specified device
 *
 * @param[in] id Device ID
 * @param[out] speed Pointer where the speed value will be stored
 * @return Error code to be treated at higher levels
 */
int read_moving_speed(uint8_t id, uint16_t* readed_value)
{
	uint8_t temp_readed_value[2];
	int error_code = dyn_read_data(id, 0x20, 2, temp_readed_value);

	*readed_value = temp_readed_value[1] << 8 | temp_readed_value[0];

	return error_code;
}

int read_move_continue(uint8_t id, bool* is_wheel_mode)
{
	int error_code, i;
	uint8_t temp_readed_value[4];

	error_code = dyn_read_data(id, 0x20, 2, temp_readed_value);

	*is_wheel_mode = true;

	for (i = 0; i < 4; i++)
	{
		if (temp_readed_value[i] != 0) *is_wheel_mode = false;
	}

	return error_code;
}

/**
 * Set the module to wheel mode
 *
 * Sets all the limit angles of a selected device to zero,
 * this way the module can continuously rotate as a wheel.
 *
 * @param[in] id Device ID
 * @return Error code to be treated at higher levels
 */
int move_continue(uint8_t id)
{
	uint8_t params[4];
	params[0] = 0;
	params[1] = 0;
	params[2] = 0;
	params[3] = 0;

	return dyn_write_data(id, 0x06, 4, params);
}

/**
 * Rotate with a specified direction and speed
 *
 * Makes a specified wheel mode module rotate to
 * a specified direction in a specified speed.
 *
 * @param[in] id Device ID
 * @param[in] direction A rotation_direction enum's value [ ROTATE_LEFT, ROTATE_RIGHT ]
 * @param[in] speed Angular speed  value from 0 to 1024 at which the module will rotate at
 *
 * @return Error code to be treated at higher levels
 */
int move_wheel(uint8_t id, enum rotation_direction direction, unsigned int speed)
{
	uint8_t speed_h, speed_l;
	uint8_t params[2];

	if (direction == ROTATE_LEFT) // Rotate left < 1024
	{
		speed_h = speed >> 8;
	}
	else // Rotate right > 1024
	{
		speed_h = (speed >> 8) + 4;
	}

	params[0] = speed;
	params[1] = speed_h;

	return dyn_write_data(id, 0x20, 2, params);
}

/**
 * Go forward with 2 modules
 *
 * Makes 2 specified modules in wheel mode to rotate in same directions to
 * go forward.
 *
 *
 * @param[in] id_left_wheel Device ID
 * @param[in] id_right_wheel Device ID
 * @param[in] speed Angular speed  value from 0 to 1024 at which the modules will rotate at
 */
int move_forward(uint8_t id_left_wheel, uint8_t id_right_wheel, unsigned int speed)
{
	return move_wheel(id_left_wheel, ROTATE_LEFT, speed) | move_wheel(id_right_wheel, ROTATE_RIGHT, speed);
}

/**
 * Go back with 2 modules
 *
 * Makes 2 specified modules in wheel mode to rotate in same directions to
 * go forward.
 *
 * @param[in] id_left_wheel Device ID
 * @param[in] id_right_wheel Device ID
 * @param[in] speed Angular speed  value from 0 to 1024 at which the modules will rotate at
 */
int move_backward(uint8_t id_left_wheel, uint8_t id_right_wheel, unsigned int speed)
{
	return move_wheel(id_left_wheel, ROTATE_RIGHT, speed) | move_wheel(id_right_wheel, ROTATE_LEFT, speed);
}

/**
 * Stop movement in 2 modules
 *
 * Makes 2 specified modules to stop rotating
 *
 * @param[in] id_left_wheel Device ID
 * @param[in] id_right_wheel Device ID
 */
int move_stop(uint8_t id_left_wheel, uint8_t id_right_wheel)
{
	return move_wheel(id_left_wheel, ROTATE_LEFT, 0) | move_wheel(id_right_wheel, ROTATE_LEFT, 0);
}


