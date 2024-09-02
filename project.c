#include "estruturas.h"
#include "funcoes.h"

int main(){

    int* pComp = (int*)malloc(sizeof(int)),*numParques = (int*)malloc(sizeof(int));
    char escolha[BUFSIZ];

    NoParque *ListaParques = NULL;
    NoListaEntradas *Primeiro_No = NULL;
    NoListaEntradas *ListaCarro = NULL;

    while (1) {
        
        fgets(escolha, BUFSIZ, stdin);
        switch (escolha[0]) {

        case 'q':
            free(pComp);free(numParques);
            return 0;
        case 'p':
            case_p(escolha,&ListaParques,pComp,numParques);
            break;
        case 'e':
            case_e(escolha,ListaParques,pComp,&Primeiro_No,&ListaCarro);
            break;
        case 's':
            case_s(escolha,Primeiro_No,ListaParques,&ListaCarro);
            break;
        case 'v':
           case_v(escolha,Primeiro_No);
            break;
        case 'f':
           case_f(escolha,Primeiro_No,ListaParques);
           break;
        case 'r':
           case_r(escolha,&ListaParques,Primeiro_No,ListaCarro);
           break;
        default:
            free(pComp);free(numParques);
            return 0;
        }
    }
    return 0;
}
