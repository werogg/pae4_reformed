/*
 * hal_dyn.c
 *
 *  Created on: 18 mar. 2020
 *      Author: droma
 *
 * This file implements the different dynamixel instructions
 */

#include "dyn/dyn_instr.h"
#include "dyn/dyn_frames.h"

/**
 * Single/Multi-byte read instruction
 *
 * This function sends a read instruction for a single address positon
 * to a given dynamixel module.
 *
 * @param[in] module_id Id of the dynamixel module
 * @param[in] reg_address Address of the first registry to read
 * @param[in] reg_address_length Length of the address we want to read
 * @param[out] readed_value Pointer where the readed value will be stored
 * @return Error code to be treated at higher levels
 */
int dyn_read_data(uint8_t module_id, uint8_t reg_address, uint8_t reg_address_length, uint8_t *readed_value)
{

	struct RxReturn response;

	uint8_t bLength = 0x04;
	uint8_t bInstruction = DYN_INSTR__READ;
	uint8_t bParameters[2];
	bParameters[0] = reg_address;
	bParameters[1] = reg_address_length;

	response = RxTxPacket(module_id, bLength, bInstruction, bParameters);

	int i;
	for (i = 0; i < reg_address_length; i++)
	{
		readed_value[i] = response.StatusPacket[5 + i];
	}


	return (response.tx_err < 1) | response.time_out;

}

/**
 * Single/Multi-byte write instruction
 *
 * This function sends a write instruction starting at a given address position
 * with a given length for a dynamixel module.
 *
 * @param[in] module_id Id of the dynamixel module
 * @param[in] reg_address Address of the first registry to write
 * @param[in] params Array of parameters of the write instruction
 * @return Error code to be treated at higher levels
 */
int dyn_write_data(uint8_t module_id, uint8_t reg_address, int params_length, uint8_t *params)
{

	uint8_t bParams[params_length+1];
	struct RxReturn response;

	uint8_t bLength = params_length+1;
	uint8_t bInstruction = DYN_INSTR__WRITE;
	bParams[0] = reg_address;

	int i;
	for (i = 1; i < params_length + 1; i++)
	{
		bParams[i] = params[i-1];
	}

	response = RxTxPacket(module_id, bLength, bInstruction, bParams);

	return (response.tx_err < 1) | response.time_out;

}


