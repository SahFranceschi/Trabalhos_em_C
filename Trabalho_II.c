/*****************************************************************************
*                                                                            *
* Nome do Programa: Lista de contatos                                        *
*                                                                            *
* Autor: Sarah Franceschi                                                    *
* Data: 07/11/2017                                                           *
* Linguagem de Implementação: C                                              *
*                                                                            *
******************************************************************************/ 


/**********************
 *     Includes       *
 **********************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

/************************
 *   Definindo Struct   *
 ************************/

struct data {

	int dia;
	int mes;
	int ano;
};

typedef struct data data;

struct dados_pessoais {

	char nome[30];
	char telefone[20];
	data aniversario;
};

typedef struct dados_pessoais dados;


/***********************
 *      Protótipos     *
 ***********************/


void flush_in(void);
//Função para limpar o buffer de entrada no Unix/Linux.

int menu(void);
//Imprime o menu.

void add_contato(dados *contatos, int *num_contatos);
//Adiciona os contatos a lista.

void imprimir_contato(dados *contatos);

int pesquisar_contato(dados *contatos, int *num_contatos);
//Pesquisa por nome.

void imprimir_lista(dados *contatos, int *num_contatos);

void busca_por_letra(dados *contatos, int *num_contatos);

void busca_por_data(dados *contatos, int *num_contatos);


/***********************
 *   Função Principal  *
 ***********************/

int main() {

	setlocale(LC_ALL, "Portugueese");

	int option;
	dados *contatos;
	int total_contatos = 0;
	char opcao_salvar;
	FILE *fp;

	printf("\nDeseja carregar os dados do arquivo?(s/n) ");
	opcao_salvar = getchar();
	flush_in();

	if(opcao_salvar == 's' || opcao_salvar == 'S') {

		if((fp = fopen("Lista_de_Contatos.dat", "rb")) == NULL) {

			fprintf(stderr, "\nNão foi possível abrir o arquivo Lista_de_Contatos.dat.\n");
		}

		else {

			fread(&total_contatos, sizeof(int), 1, fp);
			contatos = (dados*)malloc(total_contatos * sizeof(dados));
			fread(contatos, sizeof(dados), total_contatos, fp);

		}
	}

	while((option = menu()) != 6) {

		switch(option) {

			case 1: {

				//Adicionar contato(s);
				int n_contatos;
				dados *ptr_temp;
				printf("Quantos contatos deseja armazenar? ");
				scanf("%d", &n_contatos);
				flush_in();

				if(total_contatos == 0) {

					contatos = (dados*)malloc(n_contatos * sizeof(dados));

					if (contatos == NULL) {

						fprintf(stderr, "\nMemória insuficiente\n\n");
					}

					else {

						for(int i = 0; i < n_contatos; i++) {

							add_contato(&contatos[total_contatos], &total_contatos);
						}
					}
				}

				else {

					ptr_temp = (dados*)realloc(contatos, n_contatos + total_contatos * sizeof(dados));

					if(ptr_temp == NULL) {

						fprintf(stderr, "\nNão foi possivel alocar a memória.\n");
					}

					else {

						contatos = ptr_temp;

						for(int i = 0; i < n_contatos; i++) {

							add_contato(&contatos[total_contatos], &total_contatos);

						}

					}
				}
				
			}
				break;

			case 2:

				//Pesquisar contato;
				pesquisar_contato(contatos, &total_contatos);
				break;

			case 3:

				//Listar contato;
				imprimir_lista(contatos, &total_contatos);
				break;

			case 4:

				//Listar contato por determinada letra;
				busca_por_letra(contatos, &total_contatos);
				break;

			case 5:

				//Imprimir aniversariantes de determinado mes;
				busca_por_data(contatos, &total_contatos);
				break;

			default:

				printf("\nOpção inválida. Por favor, escolha uma das opções acima.\n");

		}
	}

	printf("\n\n");

	printf("\nDeseja salvar os contatos?(s/n) \n");
	opcao_salvar = getchar();
	flush_in();

	if(opcao_salvar == 's' || opcao_salvar == 'S') {

		if((fp = fopen("Lista_de_Contatos.dat", "wb")) == NULL) {

			fprintf(stderr, "\nNão foi possível salvar no arquivo Lista_de_Contatos.dat.\n");
		}

		else {

			fwrite(&total_contatos, sizeof(int), 1, fp);
			fwrite(contatos, sizeof(dados), total_contatos, fp);
			fclose(fp);
		}
	}

	if(total_contatos > 0) {

		free(contatos);
	}

	return 0;
}

/***********************************
 *    Implementando as funções     *
 ***********************************/


void flush_in(void) {

	char ch;

   while((ch = fgetc(stdin)) != EOF && ch != '\n'); 
}



int menu(void) {

	int option;


	printf("\n\n**************************************************************\n");
	printf("                               MENU                              ");
	printf("\n**************************************************************\n");		
	printf("*               Digite 1 para adicionar contato(s)           *\n");
	printf("**************************************************************");
	printf("\n*         Digite 2 para pesquisar contato pelo nome          *\n");
	printf("**************************************************************");
	printf("\n*                Digite 3 para listar contatos               *\n");
	printf("**************************************************************");
	printf("\n*   Digite 4 para listar contatos com determinada letra      *\n");
	printf("**************************************************************");
	printf("\n* Digite 5 para imprimir aniversariantes de determinado mês  *\n");
	printf("**************************************************************");
	printf("\n*                    Digite 6 para sair                      *\n");
	printf("**************************************************************");


	printf("\nOpção: ");
	scanf("%d",&option);
	flush_in();

	return option;
}

void add_contato(dados *contatos, int *num_contatos) {

	printf("\n*******************************************\n");
	printf("Nome: ");
	fgets(contatos->nome, sizeof(contatos->nome), stdin);
	contatos->nome[strcspn(contatos->nome, "\n")] = '\0';

	printf("Telefone: ");
	fgets(contatos->telefone, sizeof(contatos->telefone), stdin);
	contatos->telefone[strcspn(contatos->telefone, "\n")] = '\0';

	printf("Data de nascimento (DD/MM/AAAA): ");
	scanf("%2d/%2d/%4d", &contatos->aniversario.dia, &contatos->aniversario.mes,
		&contatos->aniversario.ano);
	flush_in();
	printf("*******************************************\n");

	(*num_contatos)++;

}

void imprimir_contato(dados *contatos) {

	printf("\n*******************************************");

	printf("\nNome: %s", contatos->nome);
	printf("\nTelefone: %s", contatos->telefone);
	printf("\nData de nascimento: %02d/%02d/%04d\n", contatos->aniversario.dia, 
		contatos->aniversario.mes, contatos->aniversario.ano);

}

void pesquisar_contato(dados *contatos, int *num_contatos) {

	char nome_busca[30];

	printf("\nInsira o nome desejado: ");
	fgets(nome_busca, sizeof(nome_busca), stdin);
	nome_busca[strcspn(nome_busca, "\n")] = '\0';

	for(int i = 0; i < (*num_contatos); i++) {

		if(strcmp(nome_busca, contatos[i].nome) == 0) {

			imprimir_contato(&contatos[i]);
			return;
		}
	}

	printf("\nNenhum contato encontrado.\n");
}

void imprimir_lista(dados *contatos, int *num_contatos) {

	for(int i = 0; i < (*num_contatos); i++) {

		imprimir_contato(&contatos[i]);

	}
}


void busca_por_letra(dados *contatos, int *num_contatos) {

	char letra_busca;

	printf("\nInsira a letra: ");
	letra_busca = getchar();
	flush_in();

	for(int i = 0; i < (*num_contatos); i++) {

		if(contatos[i].nome[0] == letra_busca) {

			imprimir_contato(&contatos[i]);
		}
	}


}

void busca_por_data(dados *contatos, int *num_contatos) {

	int mes_busca;

	printf("\nInsira o mes desejado: ");
	scanf("%2d", &mes_busca);

	for(int i = 0; i < (*num_contatos); i++) {
		
		if(mes_busca == contatos[i].aniversario.mes) {

			imprimir_contato(&contatos[i]);

		}

		
	}
}
