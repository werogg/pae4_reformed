/*
 * dyn_sensor.h
 *
 *  Created on: 18 mar. 2020
 *      Author: droma
 */

#ifndef DYN_SENSOR_H_
#define DYN_SENSOR_H_

#include "dyn_instr.h"

enum ir_sensor_direction
{
	IR_LEFT = 0x1a,
	IR_CENTER = 0x1b,
	IR_RIGHT = 0x1c
};

enum luminosity_sensor_direction
{
	LUMINOSITY_LEFT = 0x1d,
	LUMINOSITY_CENTER = 0x1e,
	LUMINOSITY_RIGHT = 0x1f
};

int read_ir_sensor(uint8_t id, enum ir_sensor_direction direction, uint8_t *readed_value);
int read_luminosity_sensor(uint8_t id, enum luminosity_sensor_direction direction, uint8_t *readed_value);
int read_sound_sensor(uint8_t id, uint8_t *readed_value);
int read_obstacle_detection_flag(uint8_t id, uint8_t *readed_value);
int read_obstacle_detected_compare_value(uint8_t id, uint8_t *readed_value);
int read_luminosity_detection_flag(uint8_t id, uint8_t *readed_value);

int write_obstacle_detected_compare_value(uint8_t id, uint8_t detection_value);

#endif /* DYN_SENSOR_H_ */
