/*
 * application.h
 *
 *  Created on: 16 de nov de 2018
 *      Author: evandro
 */

#ifndef APPLICATION_H_
#define APPLICATION_H_


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include "screen.h"


#define MAX_TICKET_VALUE	(float)(250.00f)	// maximum ticket value
#define MIN_TICKET_VALUE	(float)(2.50f)		// minimum ticket value
#define MAX_TICKET			200					// maximum ticket
#define MIN_TICKET			1					// minimum ticket
#define MAX_CHAIR_NUMBER	MAX_TICKET 			// maximum number of seats

typedef enum
{
	ticket_free = 0,
	ticket_half,
	ticket_full,
}type_ticket_t;

typedef struct
{
	uint8_t dia;
	uint8_t mes;
	uint8_t ano;
}date_t;

typedef struct
{
	char txt_teatro[100];
	char txt_espetaculo[100];
	uint16_t numero_ingresso;
	float valor_ingresso;
	date_t data;
}info_t;

typedef struct
{
	uint8_t sec;
	uint8_t min;
	uint8_t hour;
	uint8_t mday;
	uint8_t sday;
	uint8_t mon;
	uint16_t year;
}info_time_t;


void application_run(void);
void application_param_config_set(info_t param);
info_t application_param_config_get(void);
bool application_string_date(char *txt,date_t *info);
bool application_string_int(char *txt,uint16_t *var);
bool application_check_date(date_t date);

void application_exit_set(bool flag);
bool application_exit_get(void);

uint16_t application_number_ticket(void);
info_time_t application_time_get(void);

type_ticket_t application_type_ticket_get(void);
void application_type_ticket_set(type_ticket_t type);

void application_chair_finder_set(uint8_t chair);
bool application_chair_finder_get(uint8_t chair);

void application_number_chair_set(uint8_t number);
uint8_t application_number_chair_get(void);

void application_increases_cash_balance(float cash);
float application_cash_balance_get(void);

#endif /* APPLICATION_H_ */
