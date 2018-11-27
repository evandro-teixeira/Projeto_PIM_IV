/*
 * application.c
 *
 *  Created on: 16 de nov de 2018
 *      Author: Evandro Teixeira
 */
#include "application.h"

/**
 * Variaveis Globais
 */
static info_t 			system_config 					= {0};
static bool 			system_flag_exit 				= false;
static uint16_t 		system_number_ticket 			= 0;
static type_ticket_t	system_type_ticket 				= ticket_free;
static bool 			system_chair[MAX_CHAIR_NUMBER] 	= {false};
static uint8_t 			system_number_chair 			= 0;
static float 			system_cash_balance 			= 0;

/**
 * Função que executa aplicação "Venda de Ingresso"
 */
void application_run(void)
{
	// Apresenta tela inicial
	screen_home();

	// Tela de configuração inicial
	screen_config_init();

	// pega numero de ingresso disponivel para venda
	system_number_ticket = application_param_config_get().numero_ingresso;

	//Checa se o usuario quer iniciar a vendas de ingredo
	if(screen_start_ticket_sales() == true)
	{
		// Loop de Venda de Ingresso
		do
		{
			// Executa o processo de venda de ingresso
			// Checa se a venda foi concluida
			if(screen_ticket_sales() == true)
			{
				// processo de escolha da poltrona
				screen_selected_chairs();
				// imprime detalhes da venda
				screen_show_ticket_details( (uint8_t)application_type_ticket_get() );

				// Decrementa o numero de ingresso disponivel
				system_number_ticket--;

				// checa se usuario deseja encerrar a venda
				if(system_number_ticket > 0)
				{
					// verifica se o usuario deseja encerrar as vendas
					screen_close_ticket_sale();
				}
			}
		}while((application_exit_get() == false)&&(system_number_ticket != 0));
	}
	//else
	//{
		// Processo de encerramento das vendas
		screen_end_of_ticket_sale();
	//}
}

/**
 * Função que acumula o saldo de venda de ingresso
 */
void application_increases_cash_balance(float cash)
{
	system_cash_balance += cash;
}

/**
 * Função que retorna o saldo de venda de ingresso
 */
float application_cash_balance_get(void)
{
	return system_cash_balance;
}

/**
 * função que set numero da poltrona vendida
 */
void application_number_chair_set(uint8_t number)
{
	system_number_chair = number;
}

/**
 * função que retorna o numero da poltrona vendida
 */
uint8_t application_number_chair_get(void)
{
	return system_number_chair;
}

/**
 * funçaõ que set a posição da poltrona vendida
 */
void application_chair_finder_set(uint8_t chair)
{
	system_chair[chair] = true;
}

/**
 * função retorna o status da poltrona
 */
bool application_chair_finder_get(uint8_t chair)
{
	return system_chair[chair];
}

/**
 * função que retorna o tipo da venda
 */
type_ticket_t application_type_ticket_get(void)
{
	return system_type_ticket;
}

/**
 * função que set o tipo da venda
 */
void application_type_ticket_set(type_ticket_t type)
{
	system_type_ticket = type;
}

/**
 * função que retorna data e hora atual
 */
info_time_t application_time_get(void)
{
	time_t t = time(NULL);
	struct tm temp = *localtime( &t );
	info_time_t info;

	info.sec 	= (uint8_t)(temp.tm_sec);
	info.min 	= (uint8_t)(temp.tm_min);
	info.hour 	= (uint8_t)(temp.tm_hour);
	info.mday 	= (uint8_t)(temp.tm_mday);
	info.sday 	= (uint8_t)(temp.tm_wday);
	info.mon 	= (uint8_t)(temp.tm_mon);
	info.year	= (uint16_t)(temp.tm_year + 1900);

	return info;
}

/**
 * função que retorna o numero de ingresso disponiveis para venda
 */
uint16_t application_number_ticket(void)
{
	return system_number_ticket;
}

/**
 * função que set a "Flag" que sinaliza que o usuario que encerrar a venda de ingresso
 */
void application_exit_set(bool flag)
{
	system_flag_exit = flag;
}

/**
 * função que retorna a "Flag" que sinaliza que o usuario que encerrar a venda de ingresso
 */
bool application_exit_get(void)
{
	return system_flag_exit;
}

/**
 * função que set as informações da venda dos ingresso
 */
void application_param_config_set(info_t param)
{
	system_config = param;
}

/**
 * função que retorna as informações da venda dos ingresso
 */
info_t application_param_config_get(void)
{
	return system_config;
}

/**
 * função que formata a string com a data do espetaculo
 * e retorna a data em numero interiros
 */
bool application_string_date(char *txt,date_t *info)
{
	uint8_t state	= 0;
	uint8_t numero 	= 0;
	uint8_t multi 	= 0;
	uint8_t decimal = 0;

	if(txt != NULL)
	{
		while(*txt)
		{
			if(*txt == '/')
			{
				switch(state)
				{
					case 0:
						info->dia = numero;
					break;
					case 1:
						info->mes = numero;
					break;
					case 2:
						info->ano = numero;
					break;
					default:
					break;
				}
				state++;
				numero = 0;
				decimal = 0;
				multi = 0;
			}
			else
			{
				if(decimal == 0)
				{
					decimal = 1;
					multi = 1;
				}
				else
				{
					multi = 10;
				}
				numero *= multi;
				numero += (uint8_t)(*txt - 48);
			}
			txt++;
		}
		if(state == 2)info->ano = numero;
		return true;
	}
	else return false;
}

/**
 * função que formata string para inteiro
 */
bool application_string_int(char *txt,uint16_t *var)
{
	uint8_t numero 	= 0;
	uint8_t multi 	= 0;
	uint8_t decimal = 0;

	if(txt != NULL)
	{
		while(*txt)
		{
			if((*txt == ' ')||(*txt == '\n'))
			{
				*var = numero;
				numero = 0;
				decimal = 0;
				multi = 0;
				break;
			}
			else
			{
				if(decimal == 0)
				{
					decimal = 1;
					multi = 1;
				}
				else
				{
					multi = 10;
				}
				numero *= multi;
				numero += (uint8_t)(*txt - 48);
			}
			txt++;
		}
		return true;
	}
	else return false;
}

/**
 * Função que checa se a data é valida
 */
bool application_check_date(date_t date)
{
	if((date.ano >= 0)&&(date.ano <= 99))
	{
		switch(date.mes)
		{
			case 1:
				if((date.dia >= 1)&&(date.dia<=31)) return true;
				else return false;
			break;
			case 2:
				if((date.dia >= 1)&&(date.dia<=29)) return true;
				else return false;
			break;
			case 3:
				if((date.dia >= 1)&&(date.dia<=31)) return true;
				else return false;
			break;
			case 4:
				if((date.dia >= 1)&&(date.dia<=30)) return true;
				else return false;
			break;
			case 5:
				if((date.dia >= 1)&&(date.dia<=31)) return true;
				else return false;
			break;
			case 6:
				if((date.dia >= 1)&&(date.dia<=30)) return true;
				else return false;
			break;
			case 7:
				if((date.dia >= 1)&&(date.dia<=31)) return true;
				else return false;
			break;
			case 8:
				if((date.dia >= 1)&&(date.dia<=31)) return true;
				else return false;
			break;
			case 9:
				if((date.dia >= 1)&&(date.dia<=30)) return true;
				else return false;
			break;
			case 10:
				if((date.dia >= 1)&&(date.dia<=31)) return true;
				else return false;
			break;
			case 11:
				if((date.dia >= 1)&&(date.dia<=30)) return true;
				else return false;
			break;
			case 12:
				if((date.dia >= 1)&&(date.dia<=31)) return true;
				else return false;
			break;
			default:
				return false;
			break;
		}
	}
	else
	{
		return false;
	}
}
