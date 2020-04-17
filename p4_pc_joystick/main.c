#include <pthread.h>
#include <signal.h>
#include <assert.h>
#include <stdio.h>

#include "main.h"
#include "dyn/dyn_app_common.h"
#include "dyn/dyn_app_sensor.h"
#include "dyn/dyn_app_motor.h"
#include "dyn_test/dyn_emu.h"
#include "dyn_test/b_queue.h"
#include "joystick_emu/joystick.h"

uint8_t estado = Ninguno, estado_anterior = Ninguno, finalizar = 0;
/**
 * main.c
 */
int main(void)
{
	pthread_t tid, jid;
	uint8_t tmp;
	uint16_t sec_tmp;

	//Init semaphores for TX data handshake
	sem_init(&sem_tx_msp, 0, 0);
	sem_init(&sem_tx_cli, 0, 0);

	//Init queue for RX data
	init_queue();

	//Start thread for dynamixel module emulation
	pthread_create(&tid, NULL, dyn_emu, (void*) &tid);
	pthread_create(&jid, NULL, joystick_emu, (void*) &jid);

	//Testing some high level function
	printf("---------- MAIN: Setting LED to 0 \n");
    dyn_led_control(1, 0);
    printf("---------- MAIN: Getting LED value \n");
    dyn_led_read(1, &tmp);
    assert(tmp == 0);
    printf("---------- MAIN: Setting LED to 1 \n");
	dyn_led_control(1, 1);
	printf("---------- MAIN: Getting LED value \n");
    dyn_led_read(1, &tmp);
    assert(tmp == 1);

    // Testing IR sensor functions
    printf("\n---------- MAIN: Getting LEFT IR value\n");
    read_ir_sensor(2, IR_LEFT, &tmp);
    assert(tmp == 0xC8);
    printf("\n---------- MAIN: LEFT IR sensor status: CORRECT\n");

    printf("\n---------- MAIN: Testing CENTER IR sensor\n");
    read_ir_sensor(2, IR_CENTER, &tmp);
    assert(tmp == 0x1C);
    printf("\n---------- MAIN: CENTER IR sensor status: CORRECT\n");

    printf("\n---------- MAIN: Testing RIGHT IR sensor\n");
    read_ir_sensor(2, IR_RIGHT, &tmp);
    assert(tmp == 0x2A);
    printf("\n---------- MAIN: RIGHT IR sensor status: CORRECT\n");
    // End tests

    // Testing Luminosity sensor functions
    printf("\n---------- MAIN: Testing LEFT Luminosity sensor\n");
    read_luminosity_sensor(2, LUMINOSITY_LEFT, &tmp);
    assert(tmp == 0x7E);
    printf("\n---------- MAIN: LEFT Luminosity sensor status: CORRECT\n");

    printf("\n---------- MAIN: Testing CENTER Luminosity sensor\n");
    read_luminosity_sensor(2, LUMINOSITY_CENTER, &tmp);
    assert(tmp == 0x55);
    printf("\n---------- MAIN: CENTER Luminosity sensor status: CORRECT\n");

    printf("\n---------- MAIN: Testing RIGHT IR sensor\n");
    read_luminosity_sensor(2, LUMINOSITY_RIGHT, &tmp);
    assert(tmp == 0x29);
    printf("\n---------- MAIN: RIGHT Luminosity sensor status: CORRECT\n");
    // End tests

    // Testing Sound sensor functions
    printf("\n---------- MAIN: Testing Sound IR sensor\n");
    read_sound_sensor(2, &tmp);
    assert(tmp == 0x24);
    printf("\n---------- MAIN: Sound sensor status: CORRECT\n");
    // End test

    // Testing set obstacle detected compare value functions
    printf("\n---------- MAIN: Setting obstacle detected compare value to 111\n");
    write_obstacle_detected_compare_value(2, 0x6F);
    printf("\n---------- MAIN: Reading obstacle detected compare value\n");
    read_obstacle_detected_compare_value(2, &tmp);
    assert(tmp == 0x6F);
    printf("\n---------- MAIN: Sound sensor status: CORRECT\n");
    // End test

    // Testing set obstacle detected compare value functions
    printf("\n---------- MAIN: Setting moving speed to 1000\n");
    write_moving_speed(0, 0x3e8);
    printf("\n---------- MAIN: Reading obstacle detected compare value\n");
    read_moving_speed(0, &sec_tmp);
    assert(sec_tmp == 0x3e8);
    printf("\n---------- MAIN: Moving speed function status: CORRECT\n");
    // End test




	printf("************************\n");
	printf("Test passed successfully\n");
	printf("Pulsar 'q' para terminar, qualquier tecla para seguir\n");
	putchar('>');
	putchar(' ');
	fflush(stdout);//	return 0;

	while(estado != Quit)
	{
		Get_estado(&estado, &estado_anterior);
		if(estado != estado_anterior){
			Set_estado_anterior(estado);
			printf("estado = %d\n", estado);
			fflush(stdout);
			switch(estado){
			case Up:
				printf("Boton Up ('i') apretado\n");
				break;
			case Left:
				printf("Boton Left ('j') apretado\n");
				break;
			case Center:
				printf("Boton Center ('k') apretado\n");
				break;
			case Right:
				printf("Boton Right ('l') apretado\n");
				break;
			case Down:
				printf("Boton Down ('m') apretado\n");
				break;
			case Sw1:
				printf("Boton Sw1 ('a') apretado\n");
				break;
			case Sw2:
				printf("Boton Sw2 ('s') apretado\n");
				break;
			case Quit:
				printf("Adios!\n");
				break;
			}
			fflush(stdout);
			putchar('>');
			putchar(' ');
		}
	}
	printf("Programa terminado\n");
	//Signal the emulation thread to stop
	pthread_kill(tid, SIGTERM);
	pthread_kill(jid, SIGTERM);
	exit(0);
}
