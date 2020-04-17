/*
 * dyn_sensor.c
 *
 *  Created on: 18 mar. 2020
 *      Author: droma
 *
 * TODO: High-level functions like "distance_wall_front", etc
 * TODO: Generate another file for motors, with functions like "move_forward", etc
 */
#include "dyn/dyn_app_sensor.h"

/**
 * Read IR sensor
 *
 * Read the IR sensor value contained on the device registry
 *
 * @param[in] id Device ID
 * @param[in] direction Sensor direction (IR_LEFT, IR_RIGHT, IR_CENTER)
 * @param[out] readed_value Pointer where the readed value will be stored
 * @return Error code to be treated at higher levels
 */
int read_ir_sensor(uint8_t id, enum ir_sensor_direction direction, uint8_t *readed_value)
{
	return dyn_read_data(id, direction, 0x01, readed_value);
}

/**
 * Read luminosity sensor
 *
 * Read the luminosity sensor value contained on the device registry
 *
 * @param[in] id Device ID
 * @param[in] direction Sensor direction (LUMINOSITY_LEFT, LUMINOSITY_RIGHT, LUMINOSITY_CENTER)
 * @param[out] readed_value Pointer where the readed value will be stored
 * @return Error code to be treated at higher levels
 */
int read_luminosity_sensor(uint8_t id, enum luminosity_sensor_direction direction, uint8_t *readed_value)
{
	return dyn_read_data(id, direction, 0x01, readed_value);
}

/**
 * Read sound sensor
 *
 * Read the sound sensor value contained on the device registry
 *
 * @param[in] id Device ID
 * @param[out] readed_value Pointer where the readed value will be stored
 * @return Error code to be treated at higher levels
 */
int read_sound_sensor(uint8_t id, uint8_t *readed_value)
{
	return dyn_read_data(id, 0x23, 0x01, readed_value);

}

/**
 * Read obstacle detection flag
 *
 * Read the obstacle detection flag contained on the device registry
 *
 * @param[in] id Device ID
 * @param[out] readed_value Pointer where the readed value will be stored
 * @return Error code to be treated at higher levels
 */
int read_obstacle_detection_flag(uint8_t id, uint8_t *readed_value)
{
	return dyn_read_data(id, 0x20, 0x01, readed_value);
}

/**
 * Read obstacle detected compare value
 *
 * Read the obstacle detected compare value contained on the device
 * registry
 *
 * @param[in] id Device ID
 * @param[out] readed_value Pointer where the readed value will be stored
 * @return Error code to be treated at higher levels
 */
int read_obstacle_detected_compare_value(uint8_t id, uint8_t *readed_value)
{
	return dyn_read_data(id, 0x14, 0x01, readed_value);
}

/**
 * Read luminosity detection flag
 *
 * Read the luminosity detection flag contained on the device registry
 *
 * @param[in] id Device ID
 * @param[out] readed_value Pointer where the readed value will be stored
 * @return Error code to be treated at higher levels
 */
int read_luminosity_detection_flag(uint8_t id, uint8_t *readed_value)
{
	return dyn_read_data(id, 0x21, 0x01, readed_value);
}

/**
 * Write obstacle detected compare value
 *
 * Write a value on the obstacle detected compare value of a specified device
 *
 * @param[in] id Device ID
 * @param[in] direction_value Value to be stored
 * @return Error code to be treated at higher levels
 */
int write_obstacle_detected_compare_value(uint8_t id, uint8_t detection_value)
{
	uint8_t params[1];
	params[0] = detection_value;

	return dyn_write_data(id, 0x14, 1, params);
}
