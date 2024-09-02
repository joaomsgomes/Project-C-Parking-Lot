#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


#define PARQUESMAX 20
#define digito_par(A,B) (isdigit(A) && isdigit(B))
#define letra_par(A,B) (isupper(A) && isupper(B))
#define MATRICULA 9
#define STRING "00-00-00"
#define DATA 11
#define HORAS 6
#define ANO 5
#define dDigito 3
#define TAMANHO 5500
#define VERDADEIRO 1
#define NULO 0
#define IGUAL 4
#define diaMax 24
#define minutoMax 60
#define MesMax 31
#define MesMaximo 30
#define FevereiroMAX 28
#define ANOMAX 365
#define PagamentoHora 4
#define CaracterComando 2


/*ESTRUTURAS*/
typedef struct 
{
    char *nome;
    int capacidade,numCarros;
    float x,y,z;
}parque ;

typedef struct NoParque {
    parque parque;
    struct NoParque* prox;
} NoParque;

typedef struct 
{
    char data[DATA], data_saida[DATA];
    char tempos[HORAS],tempo_saida[HORAS];
    char *nome,Matricula[MATRICULA];
    float valorAPagar;
    int estado; // 1 dentro 0 fora
}veiculo;


typedef struct NoListaEntradas
{
    veiculo Entrada;
    struct NoListaEntradas *prox;
} NoListaEntradas;

#endif