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

int write_moving_speed(uint8_t id, uint16_t speed)
{
	uint8_t first_byte = (uint8_t) (speed & 0xff);
	uint8_t second_byte = (uint8_t) (speed >> 8);
	uint8_t params[2];
	params[0] = first_byte;
	params[1] = second_byte;

	return dyn_write_data(id, 0x20, 2, params);
}

int read_moving_speed(uint8_t id, uint16_t* readed_value)
{
	uint8_t temp_readed_value[2];
	int error_code = dyn_read_data(id, 0x20, 2, temp_readed_value);

	*readed_value = temp_readed_value[1] << 8 | temp_readed_value[0];

	return error_code;
}


