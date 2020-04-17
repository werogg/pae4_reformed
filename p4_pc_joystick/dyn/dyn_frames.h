/*
 * hal_uart.h
 *
 *  Created on: 18 mar. 2020
 *      Author: droma
 */

#ifndef DYN_FRAMES_H_
#define DYN_FRAMES_H_

#include <stdint.h>
#include <stdbool.h>

typedef uint8_t uint8_t;

typedef struct RxReturn {
	uint8_t StatusPacket[32];
	uint8_t idx;
	bool time_out;
	bool tx_err;
} RxReturn;

/* funcions per canviar el sentit de les comunicacions */
void Sentit_Dades_Rx(void);
void Sentit_Dades_Tx(void);
void TxUAC2(uint8_t bTxdData);

void Activa_Timer_TimeOut();
void Reset_Timeout();
bool TimeOut(uint16_t cnt);

//TxPacket()  3 paràmetres: ID del Dynamixel, Mida dels paràmetres, Instruction byte. torna la mida del "Return packet"
uint8_t TxPacket(uint8_t bID, uint8_t bParameterLength, uint8_t bInstruction,
		const uint8_t * Parametros);
struct RxReturn RxPacket(void);

struct RxReturn RxTxPacket(uint8_t bID, uint8_t bParameterLength, uint8_t bInstruction,
		const uint8_t *Parametros);

#endif /* DYN_FRAMES_H_ */

