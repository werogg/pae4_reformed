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
	uint8_t first_byte = (uint8_t) (speed & 0xff); // Extract first byte from 16bit
	uint8_t second_byte = (uint8_t) (speed >> 8); // Extract second byte from 16bit
	uint8_t params[2];
	params[0] = first_byte;
	params[1] = second_byte;

	return dyn_write_data(id, 0x20, 2, params); // Write those bytes in the registry
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
	int error_code = dyn_read_data(id, 0x20, 2, temp_readed_value); // Read registry 0x20 and store it on temp_readed_value

	*readed_value = temp_readed_value[1] << 8 | temp_readed_value[0];

	return error_code;
}

/**
 * Check if a module is in wheel mode
 *
 * Reads the value of all the limit angles and if all of them are
 * zero
 *
 * @param[in] id Device ID
 * @param[out] pointer where the boolean value will be stored
 * @return Error code to be treated at higher levels
 */
int read_move_continue(uint8_t id, uint8_t* is_wheel_mode)
{
	int error_code, i;
	uint8_t temp_readed_value[4];

	error_code = dyn_read_data(id, 0x06, 4, temp_readed_value); // Read 4 bytes from address 0x06

	*is_wheel_mode = 1;

	for (i = 0; i < 4; i++)
	{
		if (temp_readed_value[i] != 0) *is_wheel_mode = 0; // Check if all limit angles are set to 0
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

	return dyn_write_data(id, 0x06, 4, params); // Write 0 in 4 addresses from 0x06
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
	uint8_t speed_h;
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
 * Go left with 2 modules
 *
 * Makes left wheel to stop and right wheel to rotate in a specified speed to
 * make a left rotation.
 *
 * @param[in] id_left_wheel Device ID
 * @param[in] id_right_wheel Device ID
 * @param[in] speed Angular speed  value from 0 to 1024 at which the modules will rotate at
 */
int move_left(uint8_t id_left_wheel, uint8_t id_right_wheel, unsigned int speed)
{
	return move_wheel(id_left_wheel, ROTATE_RIGHT, 0) | move_wheel(id_right_wheel, ROTATE_RIGHT, speed);
}

/**
 * Go right with 2 modules
 *
 * Makes right wheel to stop and left wheel to rotate in a specified speed to
 * make a right rotation.
 *
 * @param[in] id_left_wheel Device ID
 * @param[in] id_right_wheel Device ID
 * @param[in] speed Angular speed  value from 0 to 1024 at which the modules will rotate at
 */
int move_right(uint8_t id_left_wheel, uint8_t id_right_wheel, unsigned int speed)
{
	return move_wheel(id_left_wheel, ROTATE_LEFT, speed) | move_wheel(id_right_wheel, ROTATE_LEFT, 0);
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


