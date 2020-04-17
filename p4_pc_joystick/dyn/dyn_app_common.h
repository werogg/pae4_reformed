/*
 * dyn_motor.h
 *
 *  Created on: 18 mar. 2020
 *      Author: droma
 */

#ifndef DYN_APP_COMMON_H_
#define DYN_APP_COMMON_H_

#include <stdbool.h>
#include <stdint.h>
typedef uint8_t uint8_t;

int dyn_led_control(uint8_t id, uint8_t val);
int dyn_led_read(uint8_t id,  uint8_t *val);


#endif /* DYN_APP_COMMON_H_ */
