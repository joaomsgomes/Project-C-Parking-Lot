#ifndef FUNCOES_H
#define FUNCOES_H

#include "estruturas.h"


/*
* q - Termina o programa libertando toda a memória
* p - Responsavel por Criar um parque e Listar a capacidade e os lugares de cada parque
* e - Responsavel pela Entrada de cada carro
* s - Responsavel pela Saida de cada carro
* v - Lista todos os Registos de entradas e saidas de um carro em especifico
* f - Mostra o resumo de faturação diária de um parque de estacionamento ou entao mostra todos os valores fatorados por um parque num certo dia
* r - Elimina um Parque e todos a informação relacionada com esse parque
*/


/*Funções de Verificação*/


// Funçao que recebe a listaParques e calcula o número de parques adicionados e verificar se esse numero é valido
int numero_de_parques(NoParque* listaParques);

//Funcao que recebe um Parque a ListaParques e verifica se este Parque pode ser Adicionado a Lista
int validacao_parques(parque aColocar, NoParque* listaParques);

//Funcao que recebe duas datas e horas e compara as duas dizendo qual é a mais recente
int compara_horas(char anterior[DATA], char atual[DATA], char anterior_horas[HORAS], char atual_horas[HORAS]);

//Funcao que avalia se uma matricula é valida ou nao
int verificaMatricula(char a[MATRICULA]);

//Funcao que ve se um Parque existe e se esse mesmo Parque esta cheio
int existe_carro(NoParque *Lista, veiculo carro);

// Funcao semelhante a de cima criada para verificar se o Parque esta cheio nao tendo em conta os lugares
int existe_Parque(NoParque* Lista,veiculo automovel);

//Funcao Para verificar se uma hora é valida ou nao
int hora_valida(char b[HORAS]);

//Funcao que verifica se uma saida é valida ou nao, retornando erro se nao for
int verifica_saida(NoListaEntradas *Registo, veiculo Carro);

//Funcao que verifica se a data é valida recebendo a data e uma hora
int data_valida(char a[DATA], char b[HORAS]);

//Funcao que reune todas as condições de entrada de um carro e caso nao se verifiquem retornam erro
int tratamento_entrada(char hora_anterior[HORAS], veiculo automovel, char data_anterior[DATA], char nome[BUFSIZ],char matri[MATRICULA]);

//Funcao que verifica as condições para a saida de um veiculo
int tratamento_saida(char hora_anterior[HORAS], veiculo automovel, char data_anterior[DATA], char nome[BUFSIZ],char matri[MATRICULA]);

//Funcao usada para comparar a posicao de dois nós
int compara_ord(NoListaEntradas *a, NoListaEntradas *b);

//Funcao que troca os Nos caso a e b caso as condições se verifiquem
void troca(NoListaEntradas *a, NoListaEntradas *b);

//Funcao que verifica se a Entrada de um carro é valida
int Entrada_Valida(NoListaEntradas** Lista, veiculo Automovel);

//Funcao criada para o caso f usada para ordenar a lista encadeada
int compara_F(NoListaEntradas *atual, NoListaEntradas *prox);

//Funcao que verifica se um parque existe ou nao
int verifica_Parque(NoParque* Lista, char* nome);

//Funcao que compara apenas as datas sem ter em conta as horas
int compara_datas(char data[DATA], char ultima_data[DATA]);

//Funcao que diz se a data é valida(Caso F)
int data_F(char data[DATA]);

//Funcao que diz se é a data apresentada no comando é valida
int tratamento_F(char data[DATA],char ultima_data[DATA]);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* Funçoes Para Exclusivamente o Calculo do Valor da saida de Parques*/

//Funcao que calcula o número de dias passado ao longo dos meses que o carro se encontrou dentro do parque
int calculo_dias(int mes_entrada, int mes_saida,int dia_entrada, int dia_saida);

//Funcao que calcula o número de dias caso as datas se encontrem em meses diferentes
int calculo_d(int dia_entrada,int dia_saida, int mes_entrada, int mes_saida,int horas_entrada, int horas_saida);

//Funcao que calcula o número de horas que o carro passou dentro do parque  
int calculo_h(int dia_entrada, int dia_saida, int horas_entrada, int horas_saida,int mes_entrada, int mes_saida);

//Funcao que reune todas as funções acima descritas e retorna o valor final calcculado
float calculo_valor(veiculo automovel, NoParque *ListaParques,NoListaEntradas* NOatual);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Funcao que atribui os valores aos nós de cada automovel na entrada
void cria_carro(veiculo* ptr, veiculo Automovel);

//Funcao que insere um parque na Lista de Parques
NoParque* insere_parque(parque parque, NoParque* listaParques, int* comp);

//Funcao que cria listas encadedas e adiciona o carro criado à mesma
NoListaEntradas **adicionar_veiculo(NoListaEntradas **inicioLista, veiculo novoVeiculo);

//Funcao responsavel por dar print a entrada do carro e a diminuir os lugares do parque
void escreve_carro(NoParque *Parque, veiculo* ptr, int* ptr_Lugares,int* ptr_Carro);

//Funcao que remove um nó da Lista De carros (Lista com apenas as entradas de carros)
void remover_no(NoListaEntradas **Primeiro_no, NoListaEntradas *No_remover);

//Funcao que aumenta os lugares de um parque presente na Lista
void aumenta_lugares(NoParque* ListaParques, veiculo automovel);

//Funcao que escreve a saida de um carro no formato correto
void escreve_saida(veiculo automovel , NoListaEntradas* atual);

//Funcao que adiciona as informações de saida ao carro correto
void adiciona_saida(NoListaEntradas *inicio, veiculo automovel);

//Caso P com argumentos
void P_args(parque aColocar, NoParque** listaParques, int* comp) ;

//Caso P sem argumentos
void P_semArgs(NoParque* listaParques, int* Lugares);

//Funcao Responsavel por executar a saida do carro
void saida_carro(NoListaEntradas *Primeiro_no, veiculo automovel_saida,NoParque* ListaParques,NoListaEntradas**ListaCarros);

//Funcao Responsavel por executar a entrada do carro
void entrada_carro(NoParque* pListaParques,veiculo Automovel_entrada, int* pLugares, NoListaEntradas **Primeiro_no,NoListaEntradas** ListaCarro);

//Tratamento do Input para "p" e Central de Controlo para o resto da função
void case_p(char escolha[BUFSIZ],NoParque **ListaParques, int* ptrCarros, int* numParques);

//Tratamento do Input para "e" e Central de Controlo para o resto da funçao
void case_e(char escolha[BUFSIZ],NoParque* pListaParques, int* pLugares,NoListaEntradas **Primeiro_no, NoListaEntradas** ListaCarro);

//Tratamento do Input para "s" e Central de Controlo para o resto da função
void case_s(char escolha[BUFSIZ], NoListaEntradas *Primeiro_No, NoParque *ListaParques,NoListaEntradas** ListaCarros);

//Funcao que escreve os registos com a formatação pedida
void escreve_Registos(NoListaEntradas* atual);

//Funcao que escreve a Data no caso de ser necessário alterar a sua formatação
void escreve_DataE(NoListaEntradas* atual);

//Funcao que imprime todos os registos para o caso v
void Imprime_registos(char matricula[MATRICULA], NoListaEntradas *Registo);

void Ordenacao_Lista(NoListaEntradas *Inicio);


void case_v(char escolha[BUFSIZ],NoListaEntradas *Primeiro_No);


void ordenaF(NoListaEntradas *Primeiro_No);


void escreve_F(NoListaEntradas *atual);


void F_Data(NoListaEntradas* Primeiro_No,char data[DATA],char* nome);


void Imprime_Datas(NoListaEntradas *inicio);


void F_semData(NoListaEntradas *Primeiro_No, char *nome);


void case_f(char escolha[BUFSIZ],NoListaEntradas *Primeiro_no, NoParque* ListaParques);


void trocaR(NoParque *a, NoParque *b);


void OrdenaR(NoParque* Lista);


void Auxiliar_r(NoParque **ListaP, char *nome);


void Destroi_Registo(NoListaEntradas* Primeiro_No, char* nome);


void case_r(char escolha[BUFSIZ],NoParque** ListaParques, NoListaEntradas* Primeiro_No, NoListaEntradas *ListaCarro);

#endif