/* ------------------------------------------------------------------------------
 *  This program allows us a simulation on creating variables in C;
 *  Authors: Ian Barcelos and Uillian Ludwig
 *  Copyright: GNU GPL
 *  Description: Variable Management in C
 *  Version: 3.0 (29/06/2017)
------------------------------------------------------------------------------
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Mapping de cada novo tipo de variável criado:
#define CHAR 0
#define INT 1
#define FLOAT 2
#define VECTOR_CHAR 3
#define VECTOR_INT 4
#define VECTOR_FLOAT 5
#define MATRIX_CHAR 6
#define MATRIX_INT 7
#define MATRIX_FLOAT 8

// Definição de cada espaço ocupado pelos tipos primitivos:
#define SIZE_CHAR 1
#define SIZE_INT 4
#define SIZE_FLOAT 4

typedef struct{
    char nome[30]; // contém o nome da variável;
    char* inicio; // aponta para a posição inicial da variável no vetor memória;
    int tipo; // armazena o tipo da variável no vetor memória;
    //int vetLength;
    //int matLength;
} Variavel;

Variavel *createVariable(char *nome, char *proximaMemoriaDisponivel, int tipo){
    Variavel *variavel = malloc(sizeof(Variavel));
    strcpy(variavel->nome, nome); // faz a cópia do nome da variável para o nome;
    variavel->inicio = proximaMemoriaDisponivel; // aponta pro início da memória;
    variavel->tipo = tipo;
    //variavel->vetLength = vetLength;
    //variavel->matLength = matLength;
    //printf("Variable %s created at: %p\n", nome, proximaMemoriaDisponivel);
    return variavel;
}

/*Método criado para receber um variável que contem seus atributos, junto com o
valor que foi setado pelo usuário para ser inserido dentro da memória;
*/
void setVariable(Variavel *variavel, void *valor){ // void = qualquer tipo de ponteiro;
    //recebe um char no valor por parametro, dá um cast pro início do conteúdo da
    //memória e depois é inserido um valor com cast para o mesmo tipo informado:
    switch(variavel->tipo){
        case CHAR:
        *(variavel->inicio) = *((char*) valor);// pega o conteúdo do ponteiro valor que foi dado e faz o cast;
        break;

        case INT: //transformar ponteiro de char para ponteiro de int;
        *((int*)variavel->inicio) = *((int*)valor);
        //*((int*)variavel->inicio) = *((int*) valor); // pega o conteúdo do ponteiro valor que foi dado e faz o cast;
        break;

        case FLOAT: //transformar ponteiro de char para ponteiro de float;
        *((float*)variavel->inicio) = *((float*) valor); // pega o conteúdo do ponteiro valor que foi dado e faz o cast;
        break;
    }
}
/*
Função criada para percorrer a lista de variáveis e encontrar o nome dela:
Iguala duas strings com o strcmp, sendo ambas iguais...retorna a posição da variavel;
*/
Variavel *getVariable(Variavel *listaDeVariaveis[], char *nome, int qtdVariaveis){
    int i;
    for(i = 0; i < qtdVariaveis; i++){
        if (strcmp(nome, listaDeVariaveis[i]->nome) == 0 ) { // strcmp equal == 0;
            return listaDeVariaveis[i];
        }
    }
    return NULL;
}

// Função para printar uma variável:
void printVariable(Variavel *variavel){ // variavel aponta para a struct, -> me dá o valor do inicio e o conteúdo dela.
    switch(variavel->tipo){
        case CHAR:
        printf("Nome: %s Tipo: %d Valor: %c\n", variavel->nome, variavel->tipo, *(variavel->inicio));
        break;

        case INT:
        printf("Nome: %s Tipo: %d Valor: %d\n", variavel->nome, variavel->tipo, *((int*)variavel->inicio));
        break;

        case FLOAT:
        printf("Nome: %s Tipo: %d Valor: %f\n", variavel->nome, variavel->tipo, *((float*)variavel->inicio));
        break;
    }
}

// Função para printar toda a lista de variáveis:
void printAllVariables(Variavel *listaDeVariaveis[], int qtdVariaveis){
    int i;
    for(i = 0; i < qtdVariaveis; i++){
        //*(*listaDeVariaveis) = *listaDeVariaveis[i];  < -- gambiarra sinistra
        //printVariable(*listaDeVariaveis);
        printVariable(listaDeVariaveis[i]);
    }
}

// Função criada para setar de acordo com 'define',o valor que remete a cada tipo:
int getSize(int tipo){
    if(tipo == CHAR) {
        return SIZE_CHAR;
    } else if(tipo == INT){
        return SIZE_INT;
    } else if(tipo == FLOAT){
        return SIZE_FLOAT;
    }
}

int main(){
    char memoria[5000];
    char *proxima = memoria;
    Variavel *listaDeVariaveis[100]; // Vetor de Structs(nome,posição,tipo);
    int qtdVariaveis = 0;

    // Variáveis auxiliares:
    char comando[32];
    Variavel *variavel;
    char nome [32];
    int tipo;
    int i;
    char c;
    float f;

    printf("Supported types: FLOAT, INT and CHAR\n");
    printf("Comandos possíveis:\n");
    printf("- CREATE_TYPE $VAR_NAME$\n- SET VAR $value$\n- PRINT $VAR_NAME$\n- PRINT_ALL\n\n");
    printf("-> Examples:\nCREATE_CHAR c\nSET c k\nPRINT c\n");
    printf("Please type your command:\n");

    while(1){
        scanf(" %s",comando);//

        if (strcmp(comando,"CREATE_CHAR") == 0) {
            scanf("%s",nome);
            variavel = getVariable(listaDeVariaveis,nome, qtdVariaveis);
            if(variavel != NULL){
                printf("Variable already created\n");
            }else{
                variavel = createVariable(nome, proxima, CHAR);
                listaDeVariaveis[qtdVariaveis] = variavel;
                proxima = proxima + getSize(variavel->tipo);
                qtdVariaveis++; // contador de quantas variáveis tem a cada inserção no vetor;
                printf("Variable was created with sucess.\n");
            }

        } else if (strcmp(comando,"CREATE_INT") == 0) {
            scanf("%s",nome);
            variavel = getVariable(listaDeVariaveis,nome, qtdVariaveis);
            if(variavel != NULL){
                printf("Variable already created\n");
            }else{
                variavel = createVariable(nome, proxima, INT);
                listaDeVariaveis[qtdVariaveis] = variavel;
                proxima = proxima + getSize(variavel->tipo);
                qtdVariaveis++;
                printf("Variable was created with sucess.\n");
            }

        } else if (strcmp(comando,"CREATE_FLOAT") == 0) {
            scanf("%s",nome);
            variavel = getVariable(listaDeVariaveis,nome, qtdVariaveis);
            if(variavel != NULL){
                printf("Variable already created\n");
            }else{
                variavel = createVariable(nome, proxima, FLOAT);
                listaDeVariaveis[qtdVariaveis] = variavel;
                proxima = proxima + getSize(variavel->tipo);
                qtdVariaveis++;
                printf("Variable was created with sucess.\n");
            }

        } else if (strcmp(comando,"SET") == 0) {
            scanf("%s",nome);
            variavel = getVariable(listaDeVariaveis,nome, qtdVariaveis); // percorre;
            if(variavel != NULL){
                //variavel->tipo;
                if (variavel->tipo == CHAR){
                    scanf(" %c", &c );
                    setVariable(variavel, &c); // alterar;
                    printf("Variable was set with sucess.\n");
                } else if(variavel->tipo == INT){
                    scanf(" %d", &i );
                    setVariable(variavel, &i);
                    printf("Variable was set with sucess.\n");
                } else if(variavel->tipo == FLOAT){
                    scanf(" %f", &f );
                    setVariable(variavel, &f);
                    printf("Variable was set with sucess.\n");
                }
            }else{
                printf("Variavel não existente.\n");
            }
        } else if (strcmp(comando,"PRINT") == 0) {
            scanf("%s",nome);
            variavel = getVariable(listaDeVariaveis,nome, qtdVariaveis); // percorre;
            printVariable(variavel); // imprimir;
        } else if (strcmp(comando,"PRINT_ALL") == 0) {
            printAllVariables(listaDeVariaveis,qtdVariaveis); //imprimir lista de todas as variáveis;
        }

    }

    return 0;
}

/*
// Criação de variáveis estaticamente sem leitura do usuário:
char *c = malloc(sizeof(char));
*c = 'c';
float pr = 9.2123;
int qty = 4234;

variavel = createVariable("letter", proxima, CHAR);
listaDeVariaveis[qtdVariaveis] = variavel;
proxima = proxima + getSize(variavel->tipo);
qtdVariaveis++;

Variavel *temp = getVariable(listaDeVariaveis, "letter");
setVariable(temp, c);
printVariable(temp);

variavel = createVariable("price", proxima, FLOAT);
listaDeVariaveis[qtdVariaveis] = variavel;
proxima = proxima + getSize(variavel->tipo);
qtdVariaveis++;

temp = getVariable(listaDeVariaveis, "price");
setVariable(temp, &pr);
printVariable(temp);

variavel = createVariable("qty", proxima, INT);
listaDeVariaveis[qtdVariaveis] = variavel;
proxima = proxima + getSize(variavel->tipo);
qtdVariaveis++;

temp = getVariable(listaDeVariaveis, "qty");
setVariable(temp, &qty);
printVariable(temp);

printf("\n");
printAllVariables(listaDeVariaveis,qtdVariaveis);
*/
