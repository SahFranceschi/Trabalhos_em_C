/*****************************************************************************
*                                                                            *
* Nome do Programa: Cadastro de funcionarios                                 *
*                                                                            *
* Autor: Sarah Franceschi                                                    *                                                    
* Data: 24/08/2017                                                           *
* Linguagem de Implementação: C                                              *
*                                                                            *
******************************************************************************/ 

/********************************
 *   Incluindo as bibliotecas   * 
 ********************************/

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <locale.h>

/*************************************
 *   Definindo o tamanho da struct   *
 *************************************/

#define SIZE 20

/************************
 *   Definindo Struct   *
 ************************/

struct cadastro_de_funcionarios {

	char nome[20];
	int cpf[11];
	int num_pecas;
	float salario;
};

typedef struct cadastro_de_funcionarios cad;

/******************************
 *   Protótipos das funções   *
 ******************************/

void flush_in(void);
//Função para limpar o buffer de entrada no Unix/Linux.

int menu(void);
//Função que imprime o menu.

void ler_cpf(cad *s_ptr);
//Função que lê CPF.

bool verificando_cpf(cad *s_ptr);
//Função que recebe o CPF da função ler_cpf() e verifica se este é válido ou não.

float calcular_salario(cad *s_ptr);
//Função que calcula o salário de cada funcionário com base no número de peças produzidas.

void registrar_funcionario(cad *s_ptr, int *total_funcionario);
//Função que cadastra os dados (nome, número de peças produzidas...) de cada funcionário.

void mostrar_funcionarios(cad *s_ptr, int total_funcionario);
//Função que imprime na tela os funcionários cadastrados.  

void remover_funcionario(cad *s_ptr, int *total_funcionario);
//Função que remove um funcionário de acordo com o código referente a este.

void folha_de_pagamento(cad *s_ptr, int total_funcionario);
//Função que mostra os dados de cada funcionário e o total da folha de pagamento.

void maior_salario(cad *s_ptr, int total_funcionario);
//Função que mostra os dados do funcionário  que possui o maior salário.

void menor_salario(cad *s_ptr,int total_funcionario);
//Função que mostra o funcionário,e seus dados,que possui o menor salário.

int total_pecas(cad *s_ptr, int total_funcionario);
//Função que retorna o total de peças fabricadas pelos funcionários.

/*******************************
 *    Inicio da função main    *
 *******************************/

int main() {

	setlocale(LC_ALL, "Portuguese");

	cad registros[SIZE];
	int option, total_funcionario = 0;

	while ((option = menu()) != 7) {

		switch (option) {

			case 1:
			// Cadastrar funcionario.

				if(total_funcionario < SIZE) {

					registrar_funcionario(&registros[total_funcionario], &total_funcionario);
				}

				break;

			case 2:
			//Remover funcionario.

				remover_funcionario(registros, &total_funcionario);

				break;

			case 3:
			//Mostrar folha de pagamento.

				printf("\n\nFolha de Pagamento: \n\n");
				folha_de_pagamento(registros, total_funcionario);

				break;

			case 4:
			//Mostrar funcionário com maior salário.

				maior_salario(registros, total_funcionario);

				break;

			case 5:
			//Mostrar funcionário com menor salário.

				menor_salario(registros, total_funcionario);

				break;

			case 6:
			//Mostrar o total de peças fabricadas. 

				printf("\nTotal de peças fabricadas: %d", total_pecas(registros, total_funcionario));

				break;

			default:

				printf("\nOpção inválida :(");
		}
	}	

	return 0;	
}

/**********************************
 *    Implementando as funções    *
 **********************************/


void flush_in(void) {

	char ch;

   while( (ch = fgetc(stdin)) != EOF && ch != '\n' ); 
}


int menu(void) {

	int option;


	printf("\n\n**********************************************************\n");
	printf("                             MENU                              ");
	printf("\n**********************************************************\n");		
	printf("*             Digite 1 para registrar funcionário        *\n");
	printf("**********************************************************");
	printf("\n*         Digite 2 para remover funcionário              *\n");
	printf("**********************************************************");
	printf("\n*           Digite 3 para ver a folha de pagamento       *\n");
	printf("**********************************************************");
	printf("\n*             Digite 4 para ver o maior salário          *\n");
	printf("**********************************************************");
	printf("\n*          Digite 5 para ver o menor salário             *\n");
	printf("**********************************************************");
	printf("\n*    Digite 6 para saber o total de peças fabricadas     *\n");
	printf("**********************************************************");
	printf("\n*                  Digite 7 para sair                    *\n");
	printf("**********************************************************\n\n");



	printf("\nOpção: ");
	scanf("%d",&option);
	flush_in();

	return option;
}


void ler_cpf(cad *s_ptr) {

	/*************************************************************
	 * O CPF é armazenado em uma variável unsigned long long     *
	 * (tamanho necessário para o tamanho do CPF) e é "quebrado" *
	 * de dígito em dígito e armazenado no campo CPF da struct.  *
	 *************************************************************/

	unsigned long long cpf;
	int i;

	scanf("%llu", &cpf);
	flush_in();

	for(i = 10; i >= 0; i--) {

		s_ptr->cpf[i] = cpf % 10;
		cpf /= 10; 
	}


	printf("\n");

}


bool verificando_cpf(cad *s_ptr) {

	int i, j, soma = 0;
	int resto_divisao, digito1, digito2;

	for(i = 0, j = 10; i < 9; i++, j--) {

		soma += ((*s_ptr).cpf[i]) * j;
	}

	resto_divisao = soma % 11;

	if(resto_divisao < 2) {

		digito1 = 0;
	}

	else {

		digito1 = 11 - resto_divisao;
 	}

	soma = 0;
	resto_divisao = 0;

	for (i = 0, j = 11; i < 10; i++, j--) {

		soma += ((*s_ptr).cpf[i]) * j;
	}

	resto_divisao = soma % 11;

	if(resto_divisao < 2) {

		digito2 = 0;
	}

	else {

		digito2 = 11 - resto_divisao;
	}

	if((*s_ptr).cpf[9] == digito1 && (*s_ptr).cpf[10] == digito2) {

		return true;
	}

	else {

		return false;
	}

}


float calcular_salario(cad *s_ptr) {

	if(s_ptr->num_pecas <= 30) {

		return 937.00;
	}

	else if((s_ptr->num_pecas > 30) && (s_ptr->num_pecas <= 45)) {

		return (((s_ptr->num_pecas - 30)*(937*0.03)) + 937.00);
	}

	else {

		return (((s_ptr->num_pecas - 30)*(937*0.05)) + 937.00);
	}
}


void registrar_funcionario(cad *s_ptr, int *total_funcionario) {

	printf("\nDigite o nome completo do funcionário: ");
	fgets(s_ptr->nome, sizeof(s_ptr->nome), stdin);
	s_ptr->nome[strcspn(s_ptr->nome, "\n")] = '\0'; //Removendo o caracter \n

	do{

		printf("\nDigite o CPF: ");
		ler_cpf(s_ptr);

	} while(verificando_cpf(s_ptr) == false);

	do{
		printf("Digite o número de peças feitas por este funcionário: ");
		scanf("%d", &s_ptr->num_pecas);
		flush_in();

	} while(s_ptr->num_pecas < 0);

	s_ptr->salario = calcular_salario(s_ptr);

	(*total_funcionario)++;  
}


void mostrar_funcionarios(cad *s_ptr, int total_funcionario) {

	int i, j;

	printf("\nFuncionarios \n\n");

	printf("-------------------------------------------------\n");
	printf("|  CÓDIGO  |     CPF     |         NOME         |\n");
	printf("-------------------------------------------------\n");

	/*******************************************************
	 * Para imprimir a tabela centralizada, precisei       *
	 * fazer um "hack", pois o printf não dá suporte       *
	 * para a centralização de strings (só justificação    *
	 * para esquerda ou direita).                          *
	 * O maior problema foi centralizar o nome, pois não   *
	 * sabemos com antecedencia o seu tamanho.             *
	 *******************************************************/

	for(i = 0; i < total_funcionario; i++, s_ptr++) {

		printf("|    %02d    |", i+1);
		printf(" ");
		for(j = 0; j < 11; j++) {

			printf("%d", s_ptr->cpf[j]);

		}
		printf(" |");

		printf("%*s", (22 / 2) + (int)(strlen(s_ptr->nome) / 2), s_ptr->nome);
		
		if (strlen(s_ptr->nome) % 2 == 0) {

			printf("%*c", ((22 - (int)strlen(s_ptr->nome)) / 2), ' ');

		}

		else {

			printf("%*c", ((22 - (int)strlen(s_ptr->nome)) / 2) + 1, ' ');
		}
		
		printf("|\n");
		printf("-------------------------------------------------\n");
	}
}

void remover_funcionario(cad *s_ptr, int *total_funcionario) {

	int i, codigo_remocao;

	mostrar_funcionarios(s_ptr, *total_funcionario);

	do { 

	printf("\nEntre com o código do funcionário (%d ~ %d) ou um número negativo para sair: ",
	 1, *total_funcionario);
	scanf("%d", &codigo_remocao);
	flush_in();

	} while(codigo_remocao > *total_funcionario);

	if (codigo_remocao > 0) {

		s_ptr[codigo_remocao - 1] = s_ptr[(*total_funcionario) - 1];

		/**************************************************
	 	* (codigo_remocao - 1) => (-1) devido ao codigo  *
	 	* que se inicia com o número 1, porém a posição  *
	 	* se inicia com 0.                               *
	 	**************************************************/

		(*total_funcionario)--;

	}
}


void folha_de_pagamento(cad *s_ptr, int total_funcionario) {

	int i,j;
	float total_salario = 0;

	for(i = 0; i < total_funcionario; i++, s_ptr++) {

		printf("\n\nFuncionário %d:",i + 1);
		printf("\nNome: %s", s_ptr->nome);
		printf("\nCPF: ");

		for(j = 0; j < 11; j++) {

			printf("%d", s_ptr->cpf[j]);

		}

		printf("\nSalário: R$ %.2f\n", s_ptr->salario);

		total_salario += s_ptr->salario;
	}

	printf("\nTotal da folha de pagamento: R$ %.2f", total_salario);
}


void maior_salario(cad *s_ptr, int total_funcionario) {

	int i, max_num_pecas;
	float max_salario = 0;
	char max_nome[20];
	int max_cpf[11];


	for(i = 0; i < total_funcionario; i++, s_ptr++) {

		if(s_ptr->salario > max_salario) {

			max_salario = s_ptr->salario;
			strcpy(max_nome, s_ptr->nome);
			memcpy(max_cpf, s_ptr->cpf, sizeof(max_cpf));
			max_num_pecas = s_ptr->num_pecas;
		}
	}

	printf("\nNome: %s", max_nome);
	printf("\nCPF: ");

	for(i = 0; i < 11; i++) {

		printf("%d", max_cpf[i]);

	}

	printf("\nSalário: R$ %.2f", max_salario);
	printf("\nTotal de peças fabricadas: %d", max_num_pecas);
}


void menor_salario(cad *s_ptr, int total_funcionario) {

	int i, min_num_pecas;
	float min_salario = s_ptr->salario;
	char min_nome[20];
	int min_cpf[11];

	for(i = 0; i < total_funcionario; i++, s_ptr++) {

		if(s_ptr->salario <= min_salario) {

			min_salario = s_ptr->salario;
			strcpy(min_nome, s_ptr->nome);
			memcpy(min_cpf, s_ptr->cpf, sizeof(min_cpf));
			min_num_pecas = s_ptr->num_pecas;
		}
	}

	printf("\nNome: %s", min_nome);
	printf("\nCPF: ");

	for(i = 0; i < 11; i++) {

		printf("%d", min_cpf[i]);

	}

	printf("\nSalário: R$ %.2f", min_salario);
	printf("\nTotal de peças fabricadas: %d", min_num_pecas);

}


int total_pecas(cad *s_ptr, int total_funcionario) {

	int i, n_pecas = 0;

	for(i = 0; i < total_funcionario; i++, s_ptr++) {

		n_pecas += s_ptr->num_pecas;
	}

	return n_pecas;
}
