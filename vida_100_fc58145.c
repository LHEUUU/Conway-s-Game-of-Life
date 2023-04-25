#include <stdio.h>
#include <stddef.h>
#include "vida.h"
#define COLUNAS_MAX 71
#define LINHAS_FICHEIRO_MAX 27

/*

Grupo: 100

Joao Rolo, 56749
Pedro Nobre, 42524
Leonardo Brito, 58145 

*/



int celulaVive( const int submatriz[3][3], const int regra[3] )
{
    int elemento_central = submatriz[1][1];
    int maxVizinhos = regra[0];
    int minVizinhos = regra[1];
    int vizinhosParaNascer = regra[2];
    int vizinhos = 0;
    int i, j; /* contador para as linhas e colunas, respectivamente */

    for ( i = 0; i < 3; i++ ){

        for ( j = 0; j < 3; j++ ){

            if( submatriz[i][j] == 1){
                vizinhos += 1;
            }
        }
    }

    /* como o for loop acima conta o elemento central da matriz como vizinho,
    quando esta eh igual 1, temos que subtrair esse valor*/

    if ( elemento_central == 1){
        vizinhos--;
    }

    if( elemento_central == 0 ){
        if ( vizinhos == vizinhosParaNascer ){
            return 1;
        }
        else return 0;
    }
    else if( elemento_central == 1 ){
        if ( minVizinhos <= vizinhos && vizinhos <= maxVizinhos ){
            return 1;
        }
        else return 0;
    }
}

void zeraMundo( int mundo[][COLUNAS_MAX + 2], int numLinhas, int numColunas )
{
    int i, j; /* contador para as linhas e colunas, respectivamente */

    for( i = 1; i < numLinhas + 1; i++ ){

        for( j = 1; j < numColunas + 1; j++){
            mundo[i][j] = 0;
        }
    }
}

void atribuiValorCelula( int mundo[][COLUNAS_MAX + 2], int linha, int coluna,
                         int valor )
{
    mundo[linha][coluna] = valor;
}

int valorDaCelula( const int mundo[][COLUNAS_MAX + 2], int linha, int coluna )
{
    return mundo[linha][coluna];
}

void iteraMundo( int mundo[][COLUNAS_MAX + 2], int numLinhas, int numColunas,
                 int mundoAuxiliar[][COLUNAS_MAX + 2], const int regra[3] )
{
	int i, j; /*contadores para linhas, i e w, e para colunas, j e h*/

	mundoAuxiliar = mundo;

	int submatriz[3][3]; /*matriz criada para ser percorrida e haver uma 
                         contagem dos seus elementos*/

	for(i = 0; i < numLinhas; i++){

		for(j = 0; j < numColunas; j++){

			int submatriz[3][3]={{mundoAuxiliar[i-1][j-1], 
                                mundoAuxiliar[i-1][j], mundoAuxiliar[i-1][j+1]},
							    {mundoAuxiliar[i][j-1], 
                                mundoAuxiliar[i][j], mundoAuxiliar[i][j+1]},
							    {mundoAuxiliar[i+1][j-1],
                                mundoAuxiliar[i+1][j], mundoAuxiliar[i+1][j+1]}};

			celulaVive(submatriz[3][3], regra[3]);
		}
	}
}

void iteraMundoNgeracoes( int n, int mundo[][COLUNAS_MAX + 2], 
                          int numLinhas, int numColunas, 
                          int mundoAuxiliar[][COLUNAS_MAX + 2],
                          const int regra[3] )
{
    for( n = n; n > 0; n--){

		iteraMundo( mundo, numLinhas, numColunas, mundoAuxiliar, regra[3] );

    }
}

void mostraMundo( const int mundo[][COLUNAS_MAX + 2], 
                  int numLinhas, int numColunas )
{
    int i;
    int j;

    for(i = 0; i < numLinhas; i++){  /* Itera sobre o numero de linhas */
        
        for (j = 0; j < numColunas; j++){ /*Itera sobre o numero de colunas */
            
            if (mundo[i][j] == 0){
                printf(". ");
            }
            else if (mundo[i][j] == 1){
                printf("X ");
            }
            else{ 
                printf("\nOcorreu um Erro na celula[%d][%d]!"
                       "Tem um valor inesperado de %d!", i, j, mundo[i][j]);
                return;
            }
        }
        printf("\n");
    }
}

void escreveMundo( const int mundo[][COLUNAS_MAX + 2], 
                   int numLinhas, int numColunas, const char *nomeFicheiro )
{
    FILE* fptr;

    int i, j;

    fptr = fopen("mundo_escrito.txt", "w");
    
    if (fptr == NULL){ /*Abre o ficheiro e permite a sua escrita*/
        printf( "Nao foi possivel abrir o ficheiro.\n" );
    } else {
        
        for(i = 0; i < numLinhas; i++){  /* Itera sobre o numero de linhas */
            
            for (j = 0; j < numColunas; j++){ /* Itera sobre o 
                                              numero de colunas */

                if(mundo[i][j] == 0){    
                    fprintf(fptr, ". ");
                } 
                else if (mundo[i][j] == 1){
                    fprintf(fptr, "X ");
                } 
                else {
                    printf("\nOcorreu um Erro na celula[%d][%d]!"
                           "Tem um valor inesperado de %d!", i, j, mundo[i][j]);
                    return;
                }
            }
            fprintf(fptr, "\n");
        }
        fclose(fptr); /* fclose fecha o ficheiro */
    }
}

void leMundo( int mundo[LINHAS_FICHEIRO_MAX + 2][COLUNAS_MAX + 2], 
              int tamanhoMundoLido[2], const char *nomeFicheiro )
{
    int i, j;
    char c;
    int counter = 0;

    FILE* fptr; /*Formato de abrir um ficheiro */
    fptr = fopen("mundo_escrito.txt", "r");

    if (fptr == NULL) {
        puts( "Nao foi possivel abrir o ficheiro.\n" );
    } else {
        /* vamos ler enquanto for diferente de EOF */
        c = fgetc(fptr);
        i = 0;
        j = 0;
        while (c != EOF){
            if(c == '.' || c == 'X'){
                if (c == '.'){
                    mundo[i][j] = 0;
                } else {
                    mundo[i][j] = 1;
                }
                fgetc(fptr);
                j++;
                i++;
                j = 0;
            }
            c = fgetc(fptr);
        }

    }
    fclose(fptr); /* Fecha o ficheiro */
}