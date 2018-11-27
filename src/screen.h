/*
 * tela.h
 *
 *  Created on: 15 de nov de 2018
 *      Author: evandro
 */

#ifndef SCREEN_H_
#define SCREEN_H_

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <unistd.h>
#include <time.h>
#include "application.h"

#define NUMBER_STRING		50
#define NUMBER_CHAR			112			// Numeros de caracteres
#define TIME_SCREEN_HOME 	3			// Segundos
/* Regular Colors */
#define COLOR_BLACK			"\e[0;30m"	// Black
#define COLOR_RED			"\e[0;31m"	// Red
#define COLOR_GREEN			"\e[0;32m"	// Green
#define COLOR_YELLOW		"\e[0;33m"	// Yellow
#define COLOR_BLUE			"\e[0;34m"	// Blue
#define COLOR_PURPLE		"\e[0;35m"	// Purple
#define COLOR_CYAN			"\e[0;36m"	// Cyan
#define COLOR_WRITE			"\e[0;37m"	// White
#define COLOR_RESET			"\e[0m"		// Reset
/* Background */
#define BACKGROUND_BLACK	"\e[40m"	// Black
#define BACKGROUND_RED		"\e[41m"	// Red
#define BACKGROUND_GREEN    "\e[42m"	// Green
#define BACKGROUND_YELLOW	"\e[43m"	// Yellow
#define BACKGROUND_BLUE		"\e[44m"	// Blue
#define BACKGROUND_PURPLE	"\e[45m"	// Purple
#define BACKGROUND_CYAN		"\e[46m"	// Cyan
#define BACKGROUND_WRITE	"\e[47m"	// White
/* Bold */
#define BOLD_BLACK			"\e[1;30m"	// Black
#define BOLD_RED			"\e[1;31m"	// Red
#define BOLD_GREEN			"\e[1;32m"	// Green
#define BOLD_YELLOW			"\e[1;33m"	// Yellow
#define BOLD_BLUE			"\e[1;34m"	// Blue
#define BOLD_PURPLE			"\e[1;35m"	// Purple
#define BOLD_CYAN			"\e[1;36m"	// Cyan
#define BOLD_WRITE			"\e[1;37m"	// White

void screen_home(void);
void screen_config_init(void);
//void screen_start_ticket_sales(void);
bool screen_start_ticket_sales(void);
//void screen_app(void);
bool screen_ticket_sales(void);

void screen_show_ticket_details(uint8_t type);

void screen_close_ticket_sale(void);

void screen_selected_chairs(void);

void screen_end_of_ticket_sale(void);

#endif /* SCREEN_H_ */
