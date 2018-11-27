/*
 * screen.c
 *
 *  Created on: 15 de nov de 2018
 *      Author: evandro
 */
#include "screen.h"

/**
 * Funções locais
 */
static void screen_header(void);
static void screen_line(void);
static void screen_clear(void);
static void screen_jump_line(uint8_t number_line);
static void screen_putchar(char ch,uint8_t number_ch);
static uint8_t screen_calc_number_char(char *txt);
static void sreen_show_data(void);
static int screen_read_string(char s[], int max);
static void sreen_print_half_price(void);
static void screen_chairs_available(void);

/**
 * Variavel Global "Biblioteca de String"
 */
const char* txt[NUMBER_STRING] =
{
	/* 00 */"Projeto PIM IV",
	/* 01 */"Tema:",
	/* 02 */"Objetivo Geral:",
	/* 03 */"Desenvolvimento de um sistema em linguagem C.",
	/* 04 */"Desenvolver um sistema em linguagem C para venda de ingressos de teatro.",
	/* 05 */"Ticket Sale",
	/* 06 */"Digite o nome do Teatro:",
	/* 07 */"Digite o nome do Espetaculo:",
	/* 08 */"Digite a data do Espetaculo (dd/mm/aa):",
	/* 09 */"Digite o valor do ingresso (R$ rr.ss):",
	/* 10 */"Digite o numero de ingresso disponivel:",
	/* 11 */"Data Invalida",
	/* 12 */"Valor do Ingresso Fora dos Limites",
	/* 13 */"Numero de Ingresso Fora dos Limites",
	/* 14 */"Deseja Iniciar a Venda dos Ingresso?",
	/* 15 */"Digite; S (para Sim) ou N (para Nao):",
	/* 16 */"Espetaculo:",
	/* 17 */"Teatro:",
	/* 18 */"Data Espetaculo:",
	/* 19 */"Informe a Idade do Cliente:",
	/* 20 */"Idade Isenta de Pagamento",
	/* 21 */"Cliente contemplado com Meia-Entrada",
	/* 22 */"Aluno da Rede Publica de Ensino?",
	/* 23 */"Letra Invalida",
	/* 24 */"Criança contemplada com gratuidade",
	/* 25 */"Estudante?",
	/* 26 */"Professor da Rede Publica de Ensino?",
	/* 27 */"Ingresso sem Desconto",
	/* 28 */"Informações sobre o Cliente",
	/* 29 */"Idade Invalida",
	/* 30 */"Ingresso Esgotados",
	/* 31 */"Detalhe do Ingresso Vendido",
	/* 32 */"Valor do Ingresso R$:",
	/* 33 */"Numero da Poltrona:",
	/* 34 */"Informação do Espetaculo",
	/* 35 */"Deseja Encerrar a Venda de Ingresso",
	/* 36 */"Poltronas em Verde estão Disponiveis",
	/* 37 */"Digite o numero da poltrona Disponivel",
	/* 38 */"Numero Invalido",
	/* 39 */"Poltrona Indisponivel",
	/* 40 */"Selecione a Poltrona",
	/* 41 */"Ingresso tipo Cortesia",
	/* 42 */"Ingresso tipo Meia-Entrada",
	/* 43 */"Ingresso tipo Interira",
	/* 44 */"Data da Venda:",
	/* 45 */"Fechamento do Caixa",
	/* 46 */"Ingressos Vendidos:",
	/* 47 */"Ingressos Disponivel:",
	/* 48 */"Saldo em Caixa R$:",
	/* 49 */"Obrigado por utilizar o Software",
};

/**
 * Função que apresenta informações inicial do software
 */
void screen_home(void)
{
	char txt_aux[NUMBER_CHAR] = {0};

	screen_header();
	screen_line();
	screen_jump_line(1);

	screen_putchar(' ', screen_calc_number_char((char*)txt[0]) ); // escreve espaço em branco
	printf(BOLD_BLUE"%s",txt[0]);
	screen_putchar(' ', screen_calc_number_char((char*)txt[0]) ); // escreve espaço em branco
	screen_jump_line(1);

	screen_putchar(' ', screen_calc_number_char((char*)txt[3]) ); // escreve espaço em branco
	printf(BOLD_BLUE"%s"COLOR_RESET" %s",txt[1],txt[3]);
	screen_putchar(' ', screen_calc_number_char((char*)txt[3]) ); // escreve espaço em branco
	screen_jump_line(1);

	strncat(txt_aux,txt[2],strlen(txt[2]));
	strncat(txt_aux,txt[4],strlen(txt[4]));
	screen_putchar(' ', screen_calc_number_char((char*)txt_aux) ); // escreve espaço em branco
	printf(BOLD_BLUE"%s"COLOR_RESET" %s",txt[2],txt[4]);
	screen_jump_line(2);

	screen_line();
	screen_jump_line(1);

	sleep(TIME_SCREEN_HOME);
}

/**
 * Função que o usuario informa os detalhes da venda
 */
void screen_config_init(void)
{
    int var =0;
	char txt_aux[NUMBER_CHAR];// = {0};
	info_t info = {0};

	screen_header();
	screen_line();
	screen_jump_line(1);

	screen_putchar(' ', screen_calc_number_char((char*)txt[34]) ); // escreve espaço em branco
	printf(BOLD_BLUE"%s"COLOR_RESET,txt[34]);
	screen_putchar(' ', screen_calc_number_char((char*)txt[34]) ); // escreve espaço em branco
	screen_jump_line(1);

	printf(BOLD_BLUE"%s "COLOR_RESET,txt[6]);
	screen_read_string((char*)info.txt_teatro,100);

	printf(BOLD_BLUE"%s "COLOR_RESET,txt[7]);
	screen_read_string((char*)info.txt_espetaculo,100);

	REPITA_DATA:
	printf(BOLD_BLUE"%s "COLOR_RESET,txt[8]);
	screen_read_string((char*)txt_aux,100);
	// função converte string p/ number int
	application_string_date(txt_aux,(date_t*)&info.data);
	// função que valida data recebida
	if(application_check_date((date_t)info.data)==false)
	{
		// caso da data seja invalida repita
		printf(BOLD_RED"%s "COLOR_RESET,txt[11]);
		screen_jump_line(1);
		goto REPITA_DATA;
	}

	REPITA_VALOR:
	printf(BOLD_BLUE"%s "COLOR_RESET,txt[9]);
	//scanf("%f",&info.valor_ingresso);
	if(scanf("%f",&info.valor_ingresso) == 0)
	{
		// caracter invalido
		getchar();
		screen_jump_line(1);
		goto REPITA_VALOR;
	}
	// função que checa o valor
	if((info.valor_ingresso < MIN_TICKET_VALUE)||(info.valor_ingresso > MAX_TICKET_VALUE))
	{
		// caso o valo esteja fora dos limites, repita
		printf(BOLD_RED"%s "COLOR_RESET,txt[12]);
		screen_jump_line(1);
		goto REPITA_VALOR;
	}

	REPITA_TICKET:
	printf(BOLD_BLUE"%s "COLOR_RESET,txt[10]);
	//scanf("%d",&var);
	if(scanf("%d",&var) == 0)
	{
		screen_jump_line(1);
		getchar();
		goto REPITA_TICKET;
	}
	// função que checa o numero de ingresso
	if((var < MIN_TICKET)||(var > MAX_TICKET))
	{
		// Caso o valor de ingresso estaja fora dos limites
		printf(BOLD_RED"%s "COLOR_RESET,txt[13]);
		screen_jump_line(1);
		getchar();
		goto REPITA_TICKET;
	}
	info.numero_ingresso = (uint16_t)(var);

	screen_jump_line(1);
	application_param_config_set(info);
	screen_line();
}

/**
 * Função que checa com o usuario se o mesmo deseja iniciar a venda de ingresso
 */
bool screen_start_ticket_sales(void)
{
	char ch = 0;

	screen_header();
	screen_line();
	screen_jump_line(1);

	REPITA:
	// pergunta ao usuario se deseja iniciar venda
	printf(BOLD_BLUE"%s "COLOR_RESET,txt[14]);
	screen_jump_line(1);
	printf(COLOR_RESET"%s "COLOR_RESET,txt[15]);
	//screen_jump_line(1);

	getchar_unlocked();
	scanf("%c",&ch);
	//scanf("%c",&ch);

	//switch( getchar_unlocked() )
	switch(ch)
	{
		case 's':
		case 'S':
			// Aguarda um 01 segundo
			sleep(1);
			// Imprimir dados do Espetaculo
			sreen_show_data();
			return true;
		break;

		case 'n':
		case 'N':
			return false;
		break;

		default:
			goto REPITA;
		break;
	}
	return false;
}

/**
 * Função que executa o processo de venda de ingresso
 */
bool screen_ticket_sales(void)
{
	char ch = 0;
	uint8_t idade = 0;

	screen_header();
	screen_line();
	screen_jump_line(1);

	screen_putchar(' ', screen_calc_number_char((char*)txt[28]) ); // escreve espaço em branco
	printf(BOLD_BLUE"%s "COLOR_RESET,txt[28]);
	screen_putchar(' ', screen_calc_number_char((char*)txt[28]) ); // escreve espaço em branco

	screen_jump_line(2);

	// checa se ainda possui ingresso disponivel para venda
	if(application_number_ticket() > 0)
	{
		int i = 0;
		printf(BOLD_BLUE"%s "COLOR_RESET,txt[19]);
		scanf("%d",&i);
		idade = (uint8_t)(i);
		screen_jump_line(1);

		if((idade >= 0)&&(idade <= 1))
		{
			// Idade isenta de pagamento
			printf(BOLD_BLUE"%s "COLOR_RESET,txt[20]);
			screen_jump_line(2);
			//screen_line();
			application_type_ticket_set(ticket_free);
			sleep(2); // aguarda 01 segundo
			return false;
		}
		else if((idade >= 2)&&(idade <= 12))
		{
			// Checa se é terca-feira
			if(application_time_get().sday == 2/* terca-deira*/)
			{
				// Checa se uma criança da rede publica
				REPITA:
				screen_jump_line(1);
				printf(BOLD_BLUE"%s "COLOR_RESET,txt[22]);
				screen_jump_line(1);
				printf(COLOR_RESET"%s "COLOR_RESET,txt[15]);

				getchar_unlocked();
				scanf("%c",&ch);

				switch(ch)
				{
					case 's':
					case 'S':
						// Criança com desconto de 100%
						printf(BOLD_BLUE"%s "COLOR_RESET,txt[24]);
						screen_jump_line(2);
						//screen_line();
						application_type_ticket_set(ticket_free);
						sleep(2); // aguarda 01 segundo
						return true;
					break;

					case 'n':
					case 'N':
						//return false;
					break;

					default:
						printf(BOLD_BLUE"%s "COLOR_RESET,txt[23]);
						screen_jump_line(1);
						ch = 0;
						goto REPITA;
					break;
				}
			}

			// Idade contemplada com meia-entrada
			sreen_print_half_price();
			sleep(2);
			return true;
		}
		else if((idade >= 13)&&(idade <= 120/* Idade Maxima Valida */))
		{
			if(idade >= 60)
			{
				// Idade contemplada com meia-entrada
				sreen_print_half_price();
				return true;
			}

			//char ch = 0;
			REPITA_0:
			screen_jump_line(1);
			// checar se é estudante
			printf(BOLD_BLUE"%s "COLOR_RESET,txt[25]);
			screen_jump_line(1);
			printf(COLOR_RESET"%s "COLOR_RESET,txt[15]);

			getchar_unlocked();
			scanf("%c",&ch);

			switch(ch)
			{
				case 's':
				case 'S':
					// Idade contemplada com meia-entrada
					sreen_print_half_price();
					sleep(2); // aguarda 01 segundo
					return true;
				break;

				case 'n':
				case 'N':
					//return false;
				break;

				default:
					printf(BOLD_BLUE"%s "COLOR_RESET,txt[23]);
					screen_jump_line(1);
					ch = 0;
					goto REPITA_0;
				break;
			}

			REPITA_1:
			screen_jump_line(1);
			// checa se é professor da rede publica
			printf(BOLD_BLUE"%s "COLOR_RESET,txt[26]);
			screen_jump_line(1);
			printf(COLOR_RESET"%s "COLOR_RESET,txt[15]);

			getchar_unlocked();
			scanf("%c",&ch);

			switch(ch)
			{
				case 's':
				case 'S':
					// Idade contemplada com meia-entrada
					sreen_print_half_price();
					sleep(2); // aguarda 01 segundo
					return true;
				break;

				case 'n':
				case 'N':
					//return false;
				break;

				default:
					printf(BOLD_BLUE"%s "COLOR_RESET,txt[23]);
					screen_jump_line(1);
					ch = 0;
					goto REPITA_1;
				break;
			}

			// Ingresso sem desconto
			printf(BOLD_BLUE"%s "COLOR_RESET,txt[27]);
			screen_jump_line(2);
			//screen_line();
			application_type_ticket_set(ticket_full);
			sleep(2); // aguarda 01 segundo
			return true;
		}
		else
		{
			// Idade invalida
			printf(BOLD_RED"%s "COLOR_RESET,txt[29]);
			screen_jump_line(2);
			screen_line();
			application_type_ticket_set(ticket_free);
			sleep(2); // aguarda 01 segundo
			return false;
		}
	}
	else
	{
		// Ingresso esgotados
		printf(BOLD_RED"%s "COLOR_RESET,txt[30]);
		screen_jump_line(2);
		screen_line();
		application_type_ticket_set(ticket_free);
		sleep(2); // aguarda 01 segundo
		return false;
	}
}

/**
 * Função que exibe o detalhe da venda do ingresso
 */
void screen_show_ticket_details(uint8_t type)
{
	info_t info = application_param_config_get();
	char txt_aux[100] = {0};
	float valor_ingresso = 0.00f;

	screen_header();
	screen_line();
	screen_jump_line(1);

	screen_putchar(' ', screen_calc_number_char((char*)txt[31]) ); // escreve espaço em branco
	printf(BOLD_BLUE"%s "COLOR_RESET,txt[31]);
	screen_putchar(' ', screen_calc_number_char((char*)txt[31]) ); // escreve espaço em branco

	screen_jump_line(1);

	printf(BOLD_BLUE"%s"COLOR_RESET" %s\n\r",txt[17],info.txt_teatro);
	printf(BOLD_BLUE"%s"COLOR_RESET" %s\n\r",txt[16],info.txt_espetaculo);
	printf(BOLD_BLUE"%s"COLOR_RESET" %2d/%2d/%d \n\r",txt[18],info.data.dia,info.data.mes,info.data.ano);

	switch(type)
	{
		case ticket_free:
			valor_ingresso = 0.00f;
			// Imprimi o tipo de ingresso
			printf(BOLD_WRITE"%s "COLOR_RESET,txt[41]);
			screen_jump_line(1);
		break;
		case ticket_half:
			valor_ingresso = application_param_config_get().valor_ingresso / 2.00f;
			// Imprimi o tipo de ingresso
			printf(BOLD_WRITE"%s "COLOR_RESET,txt[42]);
			screen_jump_line(1);
		break;
		case ticket_full:
		default:
			valor_ingresso = application_param_config_get().valor_ingresso;
			// Imprimi o tipo de ingresso
			printf(BOLD_WRITE"%s "COLOR_RESET,txt[43]);
			screen_jump_line(1);
		break;
	}

	// Imprime valor do ingresso
	printf(BOLD_BLUE"%s "COLOR_RESET"%1.2f",txt[32],valor_ingresso);
	screen_jump_line(1);
	// Imprime numero da poltrona
	printf(BOLD_BLUE"%s "COLOR_RESET"%d",txt[33],application_number_chair_get());
	screen_jump_line(1);
	// Imprime data e hora da venda
	sprintf(txt_aux," %2d/%2d/%4d %2d:%2d:%d",
			application_time_get().mday,
			application_time_get().mon,
			application_time_get().year,
			application_time_get().hour,
			application_time_get().min,
			application_time_get().sec);
	printf(BOLD_BLUE"%s"COLOR_RESET" %s\n\r"COLOR_RESET,txt[44],txt_aux);

	// Incrementa o saldo em caixa
	application_increases_cash_balance(valor_ingresso);

	screen_jump_line(1);
	screen_line();
	sleep(4);
}

/**
 * Função que verifica com o usuario se o mesmo deseja encerrar a venda de ingresso
 */
void screen_close_ticket_sale(void)
{
	char ch = 0;

	screen_header();
	screen_line();
	screen_jump_line(1);

	//screen_putchar(' ', screen_calc_number_char((char*)txt[31]) ); // escreve espaço em branco

	REPITA:
	printf(BOLD_BLUE"%s "COLOR_RESET,txt[35]);
	screen_jump_line(1);
	printf(COLOR_RESET"%s "COLOR_RESET,txt[15]);

	getchar_unlocked();
	scanf("%c",&ch);

	switch(ch)
	{
		case 's':
		case 'S':
			application_exit_set(true);
		break;

		case 'n':
		case 'N':
			application_exit_set(false);
		break;

		default:
			printf(BOLD_BLUE"%s "COLOR_RESET,txt[23]);
			screen_jump_line(1);
			ch = 0;
			goto REPITA;
		break;
	}

	screen_jump_line(1);
	screen_line();
	screen_jump_line(1);
}

/**
 * Função que seleciona poltrona
 */
void screen_selected_chairs(void)
{
	//char ch = 0;
	int num = 0;

	screen_putchar(' ', screen_calc_number_char((char*)txt[40]) ); // escreve espaço em branco
	printf(BOLD_BLUE"%s "COLOR_RESET,txt[40]);
	screen_putchar(' ', screen_calc_number_char((char*)txt[40]) ); // escreve espaço em branco

	// Exibe as poltronas disponivel
	screen_chairs_available();

	screen_jump_line(2);

	RETORNA:
	// Usuario seleciona a poltrona
	printf(BOLD_BLUE"%s "COLOR_RESET,txt[37]);
	if(scanf("%d",&num) == 0)
	{
		// Numero invalido
		printf(BOLD_RED"%s "COLOR_RESET,txt[38]);
		getchar();
		screen_jump_line(1);
		goto RETORNA;
	}

	// checa se o numero digitado valido
	if(!((num >= 0)&&(num <= application_param_config_get().numero_ingresso)))
	{
		// Numero invalido
		printf(BOLD_RED"%s "COLOR_RESET,txt[38]);
		screen_jump_line(1);
		goto RETORNA;
	}
	else
	{
		// checa se a poltrona esta dispoinvel para venda
		if(application_chair_finder_get( (uint8_t)num ) == true /* Cadeira Ocupada */)
		{
			// poltrona Indisponivel
			printf(BOLD_RED"%s "COLOR_RESET,txt[39]);
			screen_jump_line(1);
			goto RETORNA;
		}
	}

	// set
	application_chair_finder_set((uint8_t)num);
	application_number_chair_set((uint8_t)num);

	screen_jump_line(2);
	screen_line();
	screen_jump_line(1);
}

/**
 * Função que exibe o Fechamento do caixa
 */
void screen_end_of_ticket_sale(void)
{
	char txt_aux[100] = {0};
	uint8_t sold_tickets = (uint8_t)(application_param_config_get().numero_ingresso-application_number_ticket());

	screen_header();
	screen_line();
	screen_jump_line(1);

	// Fechamento do caixa
	screen_putchar(' ', screen_calc_number_char((char*)txt[45]) ); // escreve espaço em branco
	printf(BOLD_BLUE"%s "COLOR_RESET,txt[45]);
	screen_putchar(' ', screen_calc_number_char((char*)txt[45]) ); // escreve espaço em branco

	screen_jump_line(2);

	// Numero de ingresso vendidos
	printf(BOLD_BLUE"%s"COLOR_RESET" %d",txt[46],sold_tickets);
	screen_jump_line(1);

	// Numero de ingresso disponiveis para venda
	printf(BOLD_BLUE"%s"COLOR_RESET" %d",txt[47],application_number_ticket());
	screen_jump_line(1);

	// Saldo em Caixa
	printf(BOLD_BLUE"%s"COLOR_RESET" %.2f",txt[48],application_cash_balance_get());

	screen_jump_line(3);

	screen_line();
	screen_jump_line(1);
	sprintf(txt_aux,BOLD_BLUE"%s"COLOR_RESET" %s\n\r",txt[49],txt[5]);
	screen_putchar(' ', (screen_calc_number_char(txt_aux)+10) ); // escreve espaço em branco
	//printf(BOLD_BLUE"%s %s\n\r"COLOR_RESET,txt[49],txt[5]);
	printf("%s",txt_aux);
	screen_putchar(' ', (screen_calc_number_char(txt_aux)+10) ); // escreve espaço em branco

	screen_jump_line(1);
	screen_line();
	screen_jump_line(1);

	sleep(10);
}

/**
 * Função que Exibe as poltronas disponiveis
 */
static void screen_chairs_available(void)
{
	uint8_t i = 0;

	screen_jump_line(1);

	printf(BOLD_BLUE"%s "COLOR_RESET,txt[36]);
	screen_jump_line(2);

	for(i=0;i<application_param_config_get().numero_ingresso;i++)
	{
		// checa se a cadeira esta diponivel
		if(application_chair_finder_get(i) == true /* Cadeira Ocupada */)
		{
			printf(BOLD_RED"%3d "COLOR_RESET,i);
		}
		else
		{
			printf(BOLD_GREEN"%3d "COLOR_RESET,i);
		}
		//usleep(10000);
	}
	//sleep(5);
}

/**
 * função que imprime a msg "Cliente contemplado com Meia-Entrada"
 */
static void sreen_print_half_price(void)
{
	//half ticket
	printf(BOLD_BLUE"%s "COLOR_RESET,txt[21]);
	screen_jump_line(2);
	//screen_line();
	application_type_ticket_set(ticket_half);
}

/**
 * Função que exibe detalhes do espetaculo
 */
static void sreen_show_data(void)
{
	info_t info = application_param_config_get();

	screen_header();
	screen_line();
	screen_jump_line(1);


	screen_putchar(' ', screen_calc_number_char((char*)txt[34]) ); // escreve espaço em branco
	printf(BOLD_BLUE"%s"COLOR_RESET,txt[34]);
	screen_putchar(' ', screen_calc_number_char((char*)txt[34]) ); // escreve espaço em branco

	screen_jump_line(2);

	printf(BOLD_BLUE"%s"COLOR_RESET" %s\n\r",txt[17],info.txt_teatro);
	printf(BOLD_BLUE"%s"COLOR_RESET" %s\n\r",txt[16],info.txt_espetaculo);
	printf(BOLD_BLUE"%s"COLOR_RESET" %2d/%2d/%d",txt[18],info.data.dia,info.data.mes,info.data.ano);

	screen_jump_line(2);
	screen_line();

	sleep(TIME_SCREEN_HOME);
}
/**
 * Função que imprime o cabeçalho da tela
 */
static void screen_header(void)
{
	char txt_aux[100] = {0}, sdia[20] = {0};

	screen_clear();
	screen_jump_line(1);
	screen_line();
	screen_jump_line(1);

	screen_putchar(' ', screen_calc_number_char((char*)txt[5]) ); // escreve espaço em branco
	printf(BOLD_BLUE"%s\n\r"COLOR_RESET,txt[5]);
	screen_putchar(' ', screen_calc_number_char((char*)txt[5]) ); // escreve espaço em branco

	screen_jump_line(1);

	switch(application_time_get().sday)
	{
		case 0:
			sprintf(sdia,"Domingo");
		break;
		case 1:
			sprintf(sdia,"Segunda-Feira");
		break;
		case 2:
			sprintf(sdia,"Terça-Feira");
		break;
		case 3:
			sprintf(sdia,"Quarta-Feira");
		break;
		case 4:
			sprintf(sdia,"Quinta-Feira");
		break;
		case 5:
			sprintf(sdia,"Sexta-Feira");
		break;
		case 6:
		default:
			sprintf(sdia,"Sabado");
		break;
	}

	sprintf(txt_aux,"%s %2d/%2d/%4d %2d:%2d:%d",
			sdia,
			application_time_get().mday,
			application_time_get().mon,
			application_time_get().year,
			application_time_get().hour,
			application_time_get().min,
			application_time_get().sec);

	screen_putchar(' ', screen_calc_number_char( txt_aux) ); // escreve espaço em branco
	printf(BOLD_BLUE"%s\n\r"COLOR_RESET,txt_aux);
	screen_putchar(' ', screen_calc_number_char( txt_aux) ); // escreve espaço em branco

	//screen_jump_line(2);
	screen_jump_line(1);
}

/**
 * função que calcula o numero de espaço em branco, para texto centralizado
 */
static uint8_t screen_calc_number_char(char *txt)
{
	uint8_t num = 0;
	num = (uint8_t)( strlen(txt) );
	return ((100 - num) / 2);
}

/**
 * função que imprimi caracter na tela
 */
static void screen_putchar(char ch,uint8_t number_ch)
{
	uint8_t i = 0;

	for(i=0;i<number_ch;i++)
		putchar(ch);
}

/**
 * função que pula linha na tela
 */
static void screen_jump_line(uint8_t number_line)
{
	uint8_t i = 0;
	for(i=0;i<number_line;i++)
		printf("\n\r");
}

/**
 * função que imprime linha na tela
 */
static void screen_line(void)
{
	uint8_t i = 0;
	for(i=0;i<NUMBER_CHAR;i++)
		putchar('*');
	printf("\n\r");
}

/**
 * função que limpa tela
 */
static void screen_clear(void)
{
	printf("\e[H\e[2J");
}


/**
 *
 *//*
static void screent_pintf_txt(char *txt_in,char *txt_out)
{
	char txt_aux[100] = {0};

	printf(BOLD_BLUE"%s "COLOR_RESET,txt[6]);
	scanf("%[a-z A-Z][^\n]s",txt_aux);
	//scanf("%[^\n]s",txt_aux);
	strcpy(txt_out,txt_aux);
	//memset(&txt_aux,0,sizeof(txt_aux));
}*/

/**
 * Função que le string com espaço
 */
static int screen_read_string(char s[], int max)
{
	int i = 0;
	char letra;

	for (i = 0; i < (max - 1); i++)
	{
		letra = fgetc(stdin);
		if ((letra == '\n') && (i == 0))
		{
			i = i - 1;
			continue;
		}
		if (letra == '\n')
			break;
		s[i] = letra;
	}

	/* Finaliza a string */
	s[i] = 0;

	return (i);
}
