#include "funcoes.h"
#include "estruturas.h"

/**
 * A program exemplifying the use of Doxygen comments in C.
 * @file ex.c
 * @author ist1109512
 * Corpo das Funções do projeto
 * 
 * q - Termina o programa libertando toda a memória
 * p - Responsavel por Criar um parque e Listar a capacidade e os lugares de cada parque
 * e - Responsavel pela Entrada de cada carro
 * s - Responsavel pela Saida de cada carro
 * v - Lista todos os Registos de entradas e saidas de um carro em especifico
 * f - Mostra o resumo de faturação diária de um parque de estacionamento ou entao mostra todos os valores fatorados por um parque num certo dia
 * r - Elimina um Parque e todos a informação relacionada com esse parque
*/




char data_inicial[DATA] ="00-00-0000"; char horas_inicias[HORAS] = "00:00"; char nome[BUFSIZ] = "nome"; char matricula[MATRICULA] = "matric";
char nome_saida[BUFSIZ] = "nome"; char matricula_saida[MATRICULA] = "matric";

/**
 * @brief Calcula o número de parques na lista encadeada.
 * 
 * @param listaParques Ponteiro para o primeiro nó da lista de parques.
 * @return O número de parques na lista.
 */
int numero_de_parques(NoParque* listaParques) {
    int contador = 1; // Inicializado como 1 para incluir o parque vazio, se a lista estiver vazia
    NoParque* atual = listaParques;
    
    while (atual != NULL) {
        contador++;
        atual = atual->prox;
    }

    return contador;
}



/**
 * @brief Valida se um novo parque pode ser adicionado à lista de parques.
 * 
 * Verifica se o parque já existe na lista, se a capacidade é válida,
 * se os valores de custo são válidos e se o número máximo de parques
 * não foi excedido.
 * 
 * @param aColocar Informações do parque a ser validado.
 * @param listaParques Ponteiro para o primeiro nó da lista de parques.
 * @return 1 se o parque for válido, 0 caso contrário.
 */
int validacao_parques(parque aColocar, NoParque* listaParques) {
    int estado = VERDADEIRO; // Assume que o parque é válido por padrão
    int valido = numero_de_parques(listaParques);
    NoParque* atual = listaParques;
    while (atual != NULL) {
        if (strcmp(atual->parque.nome, aColocar.nome) == NULO) {
            printf("%s: parking already exists.\n", aColocar.nome);
            return NULO; // O parque já existe na lista, portanto, é inválido
        }
        atual = atual->prox;
    }

    // Verifica outras condições de validação
    if (aColocar.capacidade <= 0) {
        printf("%d: invalid capacity.\n", aColocar.capacidade);
        return NULO; // Capacidade inválida, portanto, o parque é inválido
    } else if (aColocar.x <= NULO || aColocar.y <= NULO || aColocar.z <= NULO ||
               !(aColocar.x < aColocar.y) || !(aColocar.y < aColocar.z) ||
               !(aColocar.x < aColocar.z)) {
        printf("invalid cost.\n");
        return NULO; // Custo inválido, portanto, o parque é inválido
    }
    else if ( valido > PARQUESMAX)
    {
        printf("too many parks.\n");
        return NULO;
    }
    else{
        estado = VERDADEIRO;
    }
    

    return estado;
}


/**
 * @brief Compara duas datas e horas no formato "dia-mês-ano" e "hora:minuto".
 * 
 * Compara as datas e horas fornecidas como argumento e retorna VERDADEIRO se a data e hora atual
 * forem maiores do que a data e hora anterior, NULO se forem menores e IGUAL se forem iguais.
 * 
 * @param anterior Data e hora anterior no formato "dia-mês-ano" e "hora:minuto".
 * @param atual Data e hora atual no formato "dia-mês-ano" e "hora:minuto".
 * @param anterior_horas Hora e minuto da data anterior.
 * @param atual_horas Hora e minuto da data atual.
 * @return VERDADEIRO se a data e hora atual forem maiores, NULO se forem menores, IGUAL se forem iguais.
 */
int compara_horas(char anterior[DATA], char atual[DATA], char anterior_horas[HORAS], char atual_horas[HORAS]) {
    int ano_anterior = NULO, mes_anterior = NULO, dia_anterior = NULO, hora_anterior = NULO, minuto_anterior = NULO;
    int ano_atual = NULO, mes_atual = NULO, dia_atual = NULO, hora_atual = NULO, minuto_atual = NULO;

    // Converter as datas e horas para inteiros
    sscanf(anterior, "%d-%d-%d", &dia_anterior, &mes_anterior, &ano_anterior);
    sscanf(atual, "%d-%d-%d", &dia_atual, &mes_atual, &ano_atual);
    sscanf(anterior_horas, "%d:%d", &hora_anterior, &minuto_anterior);
    sscanf(atual_horas, "%d:%d", &hora_atual, &minuto_atual);

    
    // Tratamento da informação
    if (ano_atual > ano_anterior){return VERDADEIRO;}

    else if(ano_atual < ano_anterior){return NULO;}

    else if(ano_atual == ano_anterior && mes_atual > mes_anterior) {return VERDADEIRO;}

    else if(ano_atual == ano_anterior && mes_atual < mes_anterior) {return NULO;}

    else if(ano_atual == ano_anterior && mes_anterior == mes_atual && dia_atual > dia_anterior) {return VERDADEIRO;}

    else if(ano_atual == ano_anterior && mes_anterior == mes_atual && dia_atual < dia_anterior) {return NULO;}

    // Caso as datas Sejam iguais Comparamos então as horas

    int soma1 = ano_atual + mes_atual + dia_atual;
    int soma2 = ano_anterior + mes_anterior + dia_anterior;

    if (soma1 == soma2){
        int soma_horaAtual = hora_atual*minutoMax + minuto_atual;
        int soma_horaAnterior = hora_anterior*minutoMax + minuto_anterior;

        if (soma_horaAtual > soma_horaAnterior) {return VERDADEIRO;}

        else if(soma_horaAtual == soma_horaAnterior){
            return IGUAL; // Valor definido para a função tratamento de entrada
        }
        else{
            return NULO;
        }
    }
    return soma1>soma2;
}


/**
 * @brief Verifica se uma matrícula está no formato válido.
 * 
 * Verifica se a matrícula fornecida está no formato válido, onde deve conter uma combinação
 * de letras e números alternados e separados por um hífen. Retorna VERDADEIRO se a matrícula é válida
 * e NULO caso contrário.
 * 
 * @param a Matrícula a ser verificada.
 * @return VERDADEIRO se a matrícula é válida, NULO caso contrário.
 */
int verificaMatricula(char a[MATRICULA]){
  int soma_numeros = NULO, soma_letras = NULO, valida = NULO; 

  for (int i = NULO; i < MATRICULA; i++)
  {
    if (a[i] != '-' )
    {
        
      if (digito_par(a[i],a[i+1])){
        soma_numeros++;
      }
      else if(islower(a[i]) && !(isdigit(a[i]))){// caso minusculas
        soma_letras = NULO;
        soma_numeros = NULO;
        break;
      }
      else if((isdigit(a[i]) && isupper(a[i+1])) || (isupper(a[i]) && isdigit(a[i+1]))){// Caso letra numero e numero letra
        soma_letras = NULO;
        soma_numeros = NULO;
        break;
      }
      else if(letra_par(a[i],a[i+1])){
        soma_letras++;
      }
    }
  }
  if (soma_letras >= VERDADEIRO && soma_numeros >= VERDADEIRO){
    valida = VERDADEIRO;
  }
  
  return valida;
}


/**
 * @brief Verifica se um carro está presente em algum parque.
 * 
 * Verifica se um carro está presente em algum parque da lista fornecida.
 * Retorna o número de ocorrências do parque onde o carro está presente.
 * 
 * @param Lista Ponteiro para a lista de parques.
 * @param carro Veículo a ser verificado.
 * @return O número de ocorrências do parque onde o carro está presente.
 *         Retorna 0 se o parque não existe na lista.
 *         Retorna NULO se o parque está cheio.
 */
int existe_carro(NoParque *Lista, veiculo carro){ //////////////// USAR COMP EM VEZ DE PARQUES MAX

    NoParque *atual = Lista;
    int cont = NULO;

    while (atual != NULL)
    {
        if (strcmp(atual->parque.nome,carro.nome) == NULO){
            cont++;
            if (atual->parque.capacidade - atual->parque.numCarros == NULO){
                printf("%s: parking is full.\n", carro.nome);
                return NULO;
            }
        }
        
    atual = atual->prox;
    }
    if (!cont){
        printf("%s: no such parking.\n", carro.nome);
    }
    return cont;
    
}

/**
 * @brief Verifica se um parque com o nome especificado existe na lista de parques.
 * 
 * Verifica se um parque com o nome especificado existe na lista de parques fornecida.
 * Retorna o número de ocorrências do parque na lista.
 * 
 * @param Lista Ponteiro para a lista de parques.
 * @param automovel Veículo com o nome do parque a ser verificado.
 * @return O número de ocorrências do parque na lista.
 *         Retorna 0 se o parque não existe na lista.
 */
int existe_Parque(NoParque* Lista,veiculo automovel){

    NoParque *atual = Lista;
    int cont = NULO;

    while (atual != NULL)
    {
        if (strcmp(atual->parque.nome,automovel.nome) == NULO){
            cont++;
        }
        
    atual = atual->prox;
    }
    if (!cont){
        printf("%s: no such parking.\n", automovel.nome);
    }
    return cont;

}


/**
 * @brief Verifica se uma hora especificada é válida.
 * 
 * Verifica se uma hora especificada no formato "hora:minuto" é válida,
 * ou seja, se está dentro do intervalo permitido (0-23 horas e 0-59 minutos).
 * 
 * @param b String contendo a hora no formato "hora:minuto".
 * @return Retorna VERDADEIRO se a hora é válida, caso contrário retorna NULO.
 */
int hora_valida(char b[HORAS]){

  
    int hora = NULO, minuto = NULO; 

    sscanf(b,"%d:%d",&hora,&minuto);


    if (hora >= NULO && hora < diaMax && minuto >= NULO && minuto < minutoMax){
        return VERDADEIRO;
    }else{
        return NULO;
    }
}

/**
 * @brief Verifica se o veículo tem uma entrada válida no registo.
 * 
 * Verifica se um veículo tem uma entrada válida no registo de entradas, 
 * comparando a matrícula do veículo com as matrículas registradas.
 * 
 * @param Registo Ponteiro para o início do registo de entradas.
 * @param Carro Veículo a ser verificado.
 * @return Retorna VERDADEIRO se o veículo tem uma entrada válida, caso contrário retorna NULO.
 */
int verifica_saida(NoListaEntradas *Registo, veiculo Carro) {
    
    int cont = NULO;
    NoListaEntradas *atual = Registo;
    while (atual != NULL) {
        
        if (strcmp(atual->Entrada.Matricula, Carro.Matricula) == NULO) {
            cont++;
        }

        atual = atual->prox;
    }

    if (!cont){
        printf("%s: invalid vehicle exit.\n", Carro.Matricula);
        return NULO;
    }else{
        return VERDADEIRO;
    }

}

/**
 * @brief Verifica se uma data e hora são válidas.
 * 
 * Verifica se uma data e hora são válidas, considerando os limites de cada mês e
 * a validade da hora fornecida.
 * 
 * @param a String representando a data no formato "dia-mês-ano".
 * @param b String representando a hora no formato "hora:minuto".
 * @return Retorna VERDADEIRO se a data e hora forem válidas, caso contrário retorna NULO.
 */
int data_valida(char a[DATA], char b[HORAS]){

    int dia = NULO, mes = NULO, ano = NULO;
    int valido = hora_valida(b);
    sscanf(a,"%d-%d-%d",&dia,&mes,&ano);

    int meses[]={31,28,31,30,31,30,31,31,30,31,30,31};
    
    if (mes == NULO){return NULO;}

    if (ano == NULO){return NULO;}

    if (meses[mes - 1] == MesMax){

        if (dia > NULO &&  dia <= MesMax && valido){
            return VERDADEIRO;
        }
    }
    else if(meses[mes - 1] == MesMaximo){
        if (dia > NULO && dia <= MesMaximo && valido){
            return VERDADEIRO;
        }
    }
    else if(meses[mes - 1]== FevereiroMAX){
        if (dia > NULO && dia <= FevereiroMAX && valido){
            return VERDADEIRO;
        }
    }
    else{
        return NULO;
    }
    return NULO;    
}


/**
 * @brief Realiza o tratamento da entrada de um veículo no parque.
 * 
 * Verifica se os dados de entrada do veículo são válidos, considerando a hora
 * e a data de entrada anteriores, o estado do veículo e a validade da nova data
 * e hora de entrada.
 * 
 * @param hora_anterior String representando a hora de entrada anterior no formato "hora:minuto".
 * @param automovel Estrutura contendo os dados do veículo de entrada.
 * @param data_anterior String representando a data de entrada anterior no formato "dia-mês-ano".
 * @param nome Nome do veículo que entrou anteriormente no parque.
 * @param matri Matrícula do veículo que entrou anteriormente no parque.
 * @return Retorna VERDADEIRO se os dados de entrada forem válidos, caso contrário retorna NULO.
 */
int tratamento_entrada(char hora_anterior[HORAS], veiculo automovel, char data_anterior[DATA], char nome[BUFSIZ],char matri[MATRICULA]) {
    
    int valido = compara_horas(data_anterior,automovel.data,hora_anterior,automovel.tempos);

    if (valido && data_valida(automovel.data,automovel.tempos) && strcmp(matri,automovel.Matricula) != NULO){
        return VERDADEIRO;
    }else if(valido == IGUAL && data_valida(automovel.data,automovel.tempos) && strcmp(nome,automovel.nome) == NULO && strcmp(matri,automovel.Matricula)!= NULO){
        
        return VERDADEIRO;
    }
    else if(valido && data_valida(automovel.data,automovel.tempos) && strcmp(matri,automovel.Matricula) == NULO && !automovel.estado){
        return VERDADEIRO;
    }
    else{
        return NULO;
    }

}


/**
 * @brief Realiza o tratamento da saída de um veículo do parque.
 * 
 * Verifica se os dados de saída do veículo são válidos, considerando a hora
 * e a data de saída anteriores, o estado do veículo e a validade da nova data
 * e hora de saída.
 * 
 * @param hora_anterior String representando a hora de saída anterior no formato "hora:minuto".
 * @param automovel Estrutura contendo os dados do veículo que está saindo do parque.
 * @param data_anterior String representando a data de saída anterior no formato "dia-mês-ano".
 * @param nome Nome do veículo que saiu anteriormente do parque.
 * @param matri Matrícula do veículo que saiu anteriormente do parque.
 * @return Retorna VERDADEIRO se os dados de saída forem válidos, caso contrário retorna NULO.
 */
int tratamento_saida(char hora_anterior[HORAS], veiculo automovel, char data_anterior[DATA], char nome[BUFSIZ],char matri[MATRICULA]) {

    

    int valido = compara_horas(data_anterior,automovel.data_saida,hora_anterior,automovel.tempo_saida);
    
    if (valido && data_valida(automovel.data_saida,automovel.tempo_saida) && strcmp(matri,automovel.Matricula) != NULO){
        return VERDADEIRO;
    }else if(valido == IGUAL && data_valida(automovel.data_saida,automovel.tempo_saida) && strcmp(nome,automovel.nome) == NULO && strcmp(matri,automovel.Matricula)!= NULO){
        return VERDADEIRO;
    }
    else if(valido && data_valida(automovel.data_saida,automovel.tempo_saida)  && automovel.estado){
        return VERDADEIRO;
    }
    else{
        return NULO;
    }

}

/**
 * @brief Compara dois registros de entrada de veículos para determinar a ordem.
 * 
 * Compara os nomes dos veículos e, em caso de igualdade, compara as datas e horas
 * de entrada para determinar a ordem entre os registros.
 * 
 * @param a Ponteiro para o primeiro registro de entrada de veículo.
 * @param b Ponteiro para o segundo registro de entrada de veículo.
 * @return Retorna VERDADEIRO se o registro 'a' deve vir antes de 'b' na ordem, caso contrário retorna NULO.
 */
int compara_ord(NoListaEntradas *a, NoListaEntradas *b){
    
    if (a == NULL || b == NULL) return NULO;

    if (strcmp(a->Entrada.nome, b->Entrada.nome) > NULO) {
        return VERDADEIRO; 
    } else if (strcmp(a->Entrada.nome, b->Entrada.nome) == NULO && compara_horas(b->Entrada.data, a->Entrada.data, b->Entrada.tempos, a->Entrada.tempos)) {
        return VERDADEIRO;
    } else {
        return NULO; // 'a' vem antes de 'b'
    }

}

/**
 * @brief Troca os registros de entrada de veículos entre dois nós da lista.
 * 
 * Esta função troca os registros de entrada de veículos armazenados nos nós 'a' e 'b'
 * da lista ligada, permitindo reordenar os registros conforme necessário.
 * 
 * @param a Ponteiro para o primeiro nó da lista contendo o registro 'a'.
 * @param b Ponteiro para o segundo nó da lista contendo o registro 'b'.
 */
void troca(NoListaEntradas *a, NoListaEntradas *b){

    veiculo temp = a->Entrada;
    a->Entrada = b->Entrada;
    b->Entrada = temp;

}

/**

*@brief Verifica se a entrada de um veículo é válida.
*Esta função verifica se a matrícula do veículo já está presente na lista de entradas.
*@param Lista Ponteiro para o ponteiro da lista de entradas.
*@param Automovel O veículo cuja entrada está sendo validada.
*@return Retorna VERDADEIRO se a entrada do veículo for válida e NULO caso contrário.
*/
int Entrada_Valida(NoListaEntradas** Lista, veiculo Automovel){
    NoListaEntradas *atual = *Lista;

    while (atual != NULL)
    {
        if (strcmp(atual->Entrada.Matricula,Automovel.Matricula) == NULO){
            printf("%s: invalid vehicle entry.\n",Automovel.Matricula);
            return NULO;

        }
        atual = atual->prox;
    }
    return VERDADEIRO; 

}


/**

*@brief Compara duas entradas para ordenação pela data e hora de saída.
*Esta função compara duas entradas de veículos com base em suas datas e horas
*de saída.
*@param atual Ponteiro para a entrada atual na comparação.
*@param prox Ponteiro para a entrada seguinte na comparação.
*@return Retorna um valor VERDADEIRO se a entrada seguinte for mais recente que
*a atual,
**/
int compara_F(NoListaEntradas *atual, NoListaEntradas *prox) {

    if (atual == NULL && prox == NULL)return NULO;


    if (strcmp(atual->Entrada.data_saida, "") != 0 && strcmp(prox->Entrada.data_saida, "") != 0 && strcmp(atual->Entrada.tempo_saida,"")!= 0 &&
    strcmp(prox->Entrada.tempo_saida,"") != 0){

        if (strcmp(atual->Entrada.data_saida, "") != NULO && strcmp(prox->Entrada.data_saida, "") != NULO) {
            return compara_horas(prox->Entrada.data_saida, atual->Entrada.data_saida, prox->Entrada.tempo_saida, atual->Entrada.tempo_saida);
        }
        return NULO;
    }
    return NULO;
}


/**

*@brief Verifica se um parque com o nome especificado existe na lista de parques.
*Esta função verifica se um parque com o nome especificado existe na lista de parques.
*@param Lista Ponteiro para o início da lista de parques.
*@param nome Nome do parque a ser verificado.
*@return Retorna VERDADEIRO se o parque existir na lista, caso contrário retorna NULO.
*Além disso, imprime uma mensagem de erro se o parque não for encontrado.
*/
int verifica_Parque(NoParque* Lista, char* nome){

    NoParque *atual = Lista;

    while (atual != NULL)
    {
        if (strcmp(atual->parque.nome,nome) == NULO){
            return VERDADEIRO;
        }
    atual = atual->prox;
    }
    printf("%s: no such parking.\n",nome);
    return NULO;

}


/**
*@brief Compara duas datas.
*Esta função compara duas datas no formato "dia-mês-ano".
*@param data A primeira data a ser comparada.
*@param ultima_data A segunda data a ser comparada.
*@return Retorna VERDADEIRO se a primeira data for posterior à segunda data,
*caso contrário retorna NULO.
*/
int compara_datas(char data[DATA], char ultima_data[DATA]){
    
    int dia = NULO, mes = NULO, ano = NULO;
    int dia2 = NULO ,mes2 = NULO,ano2 = NULO;
    sscanf(data,"%d-%d-%d",&dia,&mes,&ano);
    sscanf(ultima_data,"%d-%d-%d",&dia2,&mes2,&ano2);

    if (ano > ano2){
        return VERDADEIRO;
    }
    else if(ano == ano2 && mes  > mes2){return VERDADEIRO;}

    else if (ano == ano2 && mes == mes2 && dia > dia2){return VERDADEIRO;}
    else{
        return NULO;
    }

}

/**
*@brief Verifica se uma data é válida.
*Esta função verifica se uma data no formato "dia-mês-ano" é válida.
*@param data A data a ser verificada.
*@return Retorna VERDADEIRO se a data for válida, caso contrário retorna NULO.
*/
int data_F(char data[DATA]){

    int dia = NULO, mes = NULO, ano = NULO;
    
    sscanf(data,"%d-%d-%d",&dia,&mes,&ano);

    int meses[]={31,28,31,30,31,30,31,31,30,31,30,31};
    
    if (mes == NULO){return NULO;}

    if (ano == NULO){return NULO;}

    if (meses[mes - 1] == MesMax){

        if (dia > NULO &&  dia <= MesMax){
            return VERDADEIRO;
        }
    }
    else if(meses[mes - 1] == MesMaximo){
        if (dia > NULO && dia <= MesMaximo){
            return VERDADEIRO;
        }
    }
    else if(meses[mes - 1]== FevereiroMAX){
        if (dia > NULO && dia <= FevereiroMAX){
            return VERDADEIRO;
        }
    }
    else{
        return NULO;
    }
    return NULO;
}


/**
*@brief Realiza o tratamento de uma data para verificação.
*Esta função verifica se uma data no formato "dia-mês-ano" é válida e se é posterior à última data registrada.
*@param data A data a ser verificada.
*@param ultima_data A última data registrada.
*@return Retorna VERDADEIRO se a data for válida e posterior à última data, caso contrário retorna NULO.
*/
int tratamento_F(char data[DATA],char ultima_data[DATA]){

    
    if (data_F(data) && !compara_datas(data,ultima_data)){
        return VERDADEIRO;
    }
    printf("invalid date.\n");
    return NULO;
}




//////////////////////////////////////////////////////////CALCULO VALOR ///////////////////////////////////////////////////////////////////7

/**

*@brief Calcula o número de dias entre duas datas.
*Esta função calcula o número de dias entre duas datas, especificadas pelos meses e dias de entrada e saída.
*@param mes_entrada O mês de entrada.
*@param mes_saida O mês de saída.
*@param dia_entrada O dia de entrada.
*@param dia_saida O dia de saída.
*@return Retorna o número de dias entre as duas datas.
*/
int calculo_dias(int mes_entrada, int mes_saida,int dia_entrada, int dia_saida){
    
  
    int soma_dias = 0;
    int estado = 1;
        

        for (int mes_atual = mes_entrada; mes_atual  < mes_saida; mes_atual++)
        {
            
            if (mes_atual == 1 || mes_atual == 3 || mes_atual == 5 || mes_atual == 7 || mes_atual == 8 || mes_atual == 10 || mes_atual == 12 ){
                soma_dias += 31;
                if (dia_entrada > dia_saida && estado){
                    soma_dias -= 31; // Caso nao chegue a passar totalmente o ultimo mes (Exemplo: 11-03-2024 e 09-04-2024 )
                    estado = 0;
                }
            }
            else if(mes_atual == 4 || mes_atual == 6 || mes_atual == 9 || mes_atual == 11){
                soma_dias += 30;
                if (dia_entrada > dia_saida && estado){
                    soma_dias -= 30;
                    estado = 0;
                }
            }
            else{
                soma_dias += 28;
                if (dia_entrada > dia_saida && estado){
                    soma_dias -= 28;
                    estado = 0;
                }
            }
        }
    
    return soma_dias;
}

/**

*@brief Calcula o número de dias entre duas datas, considerando horas de entrada e saída.
*Esta função calcula o número de dias entre duas datas, especificadas pelos dias e meses de entrada e saída,
considerando também as horas de entrada e saída. Se as horas de entrada forem maiores que as horas de saída,
subtrai um dia do cálculo final.
*@param dia_entrada O dia de entrada.
*@param dia_saida O dia de saída.
*@param mes_entrada O mês de entrada.
*@param mes_saida O mês de saída.
*@param horas_entrada As horas de entrada.
*@param horas_saida As horas de saída.
*@return Retorna o número de dias entre as duas datas, considerando as horas de entrada e saída.
*/
int calculo_d(int dia_entrada,int dia_saida, int mes_entrada, int mes_saida,int horas_entrada, int horas_saida){
    
    int num_dias = 0;

        for ( int mes_atual = mes_entrada; mes_atual < mes_saida; mes_atual++)
        {
            
            if (mes_atual == mes_saida - 1){
                if (mes_atual == 1 || mes_atual == 3 || mes_atual == 5 || mes_atual == 7 || mes_atual == 8 || mes_atual == 10 || mes_atual == 12 ){
                    num_dias = 31 - dia_entrada + dia_saida;

                }
                else if(mes_atual == 4 || mes_atual == 6 || mes_atual == 9 || mes_atual == 11){
                    num_dias = 30 - dia_entrada + dia_saida;
                }
                else if(mes_atual == 2){
                    num_dias = 28 - dia_entrada + dia_saida;
                }

            }
        }

        if (horas_entrada > horas_saida){
            return num_dias-1;
            
        }
        else{
            return num_dias;
        }
}

int calculo_h(int dia_entrada, int dia_saida, int horas_entrada, int horas_saida,int mes_entrada, int mes_saida){
    int num_horas = 0;
    
    if (mes_entrada < mes_saida && dia_entrada > dia_saida){
        if (mes_entrada == 1 || mes_entrada == 3 || mes_entrada == 5 || mes_entrada == 7 || mes_entrada == 8 || mes_entrada == 10 || mes_entrada == 12 ){
            dia_saida += 31;
        }
        else if(mes_entrada == 4 || mes_entrada == 6 || mes_entrada == 9 || mes_entrada == 11){
            dia_saida += 30;
        }
        else if(mes_entrada == 2){
            dia_saida += 28;
        }
    }



    for (int dia_atual = dia_entrada; dia_atual < dia_saida; dia_atual++)
    {   
        if (dia_atual == dia_saida - 1){

            num_horas = 24 - horas_entrada + horas_saida;

        }
    }
    
    
    return num_horas;

}


float calcula_resto(float soma2, float val_x, float val_y, float val_z,
int mes_entrada,int mes_saida, int dia_entrada, int dia_saida,int horas_saida
,int horas_entrada,int minutos_entrada, int minutos_saida){

    int contador = NULO,res_horas = 0;
    int res_minutos = 0;
    if (dia_entrada == dia_saida){

        res_horas = abs(horas_saida - horas_entrada);
    }
    else{
        res_horas = calculo_h(dia_entrada,dia_saida,horas_entrada,horas_saida,
        mes_entrada,mes_saida);
    }

    if (res_horas >= diaMax){
        res_horas -= diaMax;
    }
    

    if (minutos_entrada > minutos_saida){
        res_horas--;
        res_minutos = minutoMax - minutos_entrada + minutos_saida;
    }
    else{
        res_minutos = (minutos_saida - minutos_entrada);
    }
   
    for (int i = 0; res_minutos > 0; i++)
    {
        res_minutos -= 15;
        contador++;
    }
    

    if (res_horas >= 1){
        if (PagamentoHora*val_x + (--res_horas)*PagamentoHora*val_y + contador*val_y >= val_z){//decrementaçao antes para comparar corretamente
            
            soma2 += val_z;
        }
        else{
            soma2 += PagamentoHora*val_x + (res_horas--)*PagamentoHora*val_y + contador*val_y;
        }
    }
    else if(res_horas == NULO){
        
        soma2 += contador*val_x;

    }
    return soma2;
}



/**

*@brief Calcula o número de horas entre duas datas, considerando horas de entrada e saída.
*Esta função calcula o número de horas entre duas datas, especificadas pelos dias, meses, horas de entrada e saída.
Se a data de entrada for anterior à data de saída e a hora de entrada for maior que a hora de saída, ajusta o número
de dias para o cálculo correto. Em seguida, calcula o número de horas entre as datas, levando em consideração o período
entre a hora de entrada e a hora de saída.
*@param dia_entrada O dia de entrada.
*@param dia_saida O dia de saída.
*@param horas_entrada As horas de entrada.
*@param horas_saida As horas de saída.
*@param mes_entrada O mês de entrada.
*@param mes_saida O mês de saída.
*@return Retorna o número de horas entre as duas datas, considerando as horas de entrada e saída.
*/
float calculo_valor(veiculo automovel, NoParque *ListaParques,NoListaEntradas* NOatual){
    
    int ano_saida , mes_saida,dia_saida,horas_saida,minutos_saida;
    int ano_entrada,mes_entrada,dia_entrada,horas_entrada,minutos_entrada;
    int res_dias = 0;
    float val_x = 0, val_y = 0,val_z = 0, soma2 = 0;
    NoParque *atual = ListaParques;
    // Conversao de strings para inteiros

    sscanf(automovel.data_saida,"%d-%d-%d",&dia_saida,&mes_saida,&ano_saida);
    sscanf(automovel.tempo_saida,"%d:%d",&horas_saida,&minutos_saida);

    sscanf(NOatual->Entrada.data,"%d-%d-%d",&dia_entrada,&mes_entrada,&ano_entrada);
    sscanf(NOatual->Entrada.tempos,"%d:%d",&horas_entrada,&minutos_entrada);

    // Encontrar o parque onde o veiculo se encontra e retirar os registos de faturacao
    while (atual != NULL)
    {
        if(strcmp(atual->parque.nome,automovel.nome) == 0){

            val_x = atual->parque.x;
            val_y = atual->parque.y;
            val_z = atual->parque.z;
            break;
        }
    atual = atual->prox;
    }
    

    //criar varios casos para cada situacao e retornar a soma final
    if (mes_entrada == mes_saida){
        if (horas_entrada > horas_saida){
            res_dias = abs(dia_entrada-dia_saida) - 1;
            
        }
        else{
            res_dias = abs(dia_entrada-dia_saida);
        }
        
        
    }
    else{
        res_dias = calculo_d(dia_entrada,dia_saida,mes_entrada,mes_saida,horas_entrada,horas_saida);
        
    }

    int n_dias = calculo_dias(mes_entrada,mes_saida,dia_entrada,dia_saida);

    
    
    float soma_valor = (ano_saida-ano_entrada)*365*val_z + (n_dias)*val_z + res_dias*val_z;
    
    

    /////////////////////////////////CALCULO DO VALOR DAS HORAS////////////////////////////////////////

    soma2 = calcula_resto(soma2,val_x,val_y,val_z,mes_entrada,mes_saida,
    dia_entrada,dia_saida,horas_saida,
    horas_entrada,minutos_entrada,minutos_saida);


    return soma2 + soma_valor;
        
}      
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/* Funções de Manipulação de Estruturas*/

/**

*@brief Cria um novo veículo.
*Esta função cria um novo veículo alocando memória dinamicamente para suas propriedades e copiando
os valores do veículo fornecido para o novo veículo criado.
*@param ptr Um ponteiro para o novo veículo a ser criado.
*@param Automovel O veículo a ser copiado para criar o novo veículo.
*/
void cria_carro(veiculo* ptr, veiculo Automovel){
    
        ptr->nome = (char*)malloc(strlen(Automovel.nome) + 1);
        if (ptr == NULL) return;

        strcpy(ptr->nome, Automovel.nome);
        strcpy(ptr->Matricula, Automovel.Matricula);  
        strcpy(ptr->data, Automovel.data);
        strcpy(ptr->tempos, Automovel.tempos);
        

}

/**

@brief Insere um novo parque na lista de parques.
*Esta função cria um novo nó para representar um parque e o insere no final da lista de parques.
*@param parque O parque a ser inserido.
*@param listaParques A lista de parques onde o novo parque será inserido.
*@param comp Um ponteiro para a variável que armazena o número de comparações.
*@return Um ponteiro para o início da lista de parques após a inserção do novo parque.
*/
NoParque* insere_parque(parque parque, NoParque* listaParques, int* comp) {
    NoParque* novoNo = (NoParque*)malloc(sizeof(NoParque));
    
    novoNo->parque = parque;
    novoNo->prox = NULL;

    if (listaParques == NULL) {
        *comp = 1;
        return novoNo;
    }

    NoParque* atual = listaParques;
    while (atual->prox != NULL) {
        atual = atual->prox;
    }
    atual->prox = novoNo;
    (*comp)++;
    return listaParques;

}

/**

*@brief Adiciona um novo veículo à lista de entradas.
*Esta função cria um novo nó para representar um veículo e o adiciona ao final da lista de entradas.
*@param inicioLista Um ponteiro para o ponteiro que aponta para o início da lista de entradas.
*@param novoVeiculo O veículo a ser adicionado à lista de entradas.
*@return Um ponteiro para o início da lista de entradas após a adição do novo veículo.
*/
NoListaEntradas **adicionar_veiculo(NoListaEntradas **inicioLista, veiculo novoVeiculo) {

    NoListaEntradas *novoNo = (NoListaEntradas*)malloc(sizeof(NoListaEntradas));
      
    if (novoNo == NULL){
        return inicioLista; // Falha ao alocar memória
    }

    novoNo->Entrada = novoVeiculo;
    novoNo->prox = NULL;
    novoNo->Entrada.estado = VERDADEIRO;

    if (*inicioLista == NULL) {
        *inicioLista = novoNo;
    }
    else {
        NoListaEntradas *atual = *inicioLista;
        while (atual->prox != NULL) {
            atual = atual->prox;
        }
        atual->prox = novoNo;
    }   
    
    return inicioLista;
}

/**
*@brief Escreve as informações do carro e atualiza o número de lugares disponíveis no parque.
*Esta função escreve as informações do carro especificado e atualiza o número de lugares disponíveis no parque.
*@param Parque Ponteiro para o nó do parque onde o carro está estacionado.
*@param ptr Ponteiro para a estrutura de dados do carro.
*@param ptr_Lugares Ponteiro para o número de lugares disponíveis no parque.
*@param ptr_Carro Ponteiro para o número de carros estacionados no parque.
*/
void escreve_carro(NoParque *Parque, veiculo* ptr, int* ptr_Lugares,int* ptr_Carro){

    (*ptr_Carro)++;
    *ptr_Lugares = (Parque->parque.capacidade - *ptr_Carro);
    printf("%s %d\n",ptr->nome,*ptr_Lugares);
}

/**

*@brief Remove um nó da lista ligada.
*Esta função remove o nó especificado da lista ligada.
*@param Primeiro_no Ponteiro para o ponteiro do primeiro nó da lista.
*@param No_remover Ponteiro para o nó a ser removido.
*/
void remover_no(NoListaEntradas **Primeiro_no, NoListaEntradas *No_remover){

    
    NoListaEntradas *atual = *Primeiro_no;
    NoListaEntradas *anterior = NULL;

    while (strcmp(atual->Entrada.Matricula,No_remover->Entrada.Matricula) != NULO)
    {
        
        anterior = atual;
        atual = atual->prox;
    }

    if (anterior == NULL){
        *Primeiro_no = atual->prox;
            
    }
    else{
        anterior->prox = atual->prox;
    }
    free(atual);

}

/**

*@brief Aumenta o número de lugares disponíveis em um parque.
*Esta função diminui o número de carros estacionados no parque com o nome especificado,
aumentando assim o número de lugares disponíveis.
*@param ListaParques Ponteiro para o início da lista de parques.
*@param automovel O veículo a ser removido do parque.
*/
void aumenta_lugares(NoParque* ListaParques, veiculo automovel){
    NoParque *atual = ListaParques;

    
    while (atual != NULL)
    {
        
        if(strcmp(atual->parque.nome,automovel.nome) == NULO){
            atual->parque.numCarros--;
            break;
        }
    atual = atual->prox;
    }
    
    
}

/**

*@brief Escreve os detalhes da saída de um veículo.
*Esta função escreve os detalhes da saída de um veículo estacionado, incluindo a placa do veículo,
a data e hora de entrada, a data e hora de saída e o valor a pagar.
*@param automovel O veículo que está saindo.
*@param atual O nó da lista que contém os detalhes da entrada do veículo.
*/
void escreve_saida(veiculo automovel , NoListaEntradas* atual ){

   
    if (atual->Entrada.tempos[0] >= '0' && atual->Entrada.tempos[0] <= '9' && automovel.tempo_saida[0]>= '0' && automovel.tempo_saida[0] <= '9' &&
    atual->Entrada.tempos[1] == ':' && automovel.tempo_saida[1] == ':') {
        printf("%s %s 0%s %s 0%s %.2f\n",automovel.Matricula,atual->Entrada.data,atual->Entrada.tempos,automovel.data_saida,automovel.tempo_saida,automovel.valorAPagar);
    }
    else if(automovel.tempo_saida[0]>= '0' && automovel.tempo_saida[0] <= '9' && automovel.tempo_saida[1]== ':'){
        printf("%s %s %s %s 0%s %.2f\n",automovel.Matricula,atual->Entrada.data,atual->Entrada.tempos,automovel.data_saida,automovel.tempo_saida, automovel.valorAPagar);
    }
    else if(atual->Entrada.tempos[0] >= '0' && atual->Entrada.tempos[0] <= '9' && atual->Entrada.tempos[1] == ':'){
        printf("%s %s 0%s %s %s %.2f\n",automovel.Matricula,atual->Entrada.data,atual->Entrada.tempos,automovel.data_saida,automovel.tempo_saida, automovel.valorAPagar);
    }
    else{
        printf("%s %s %s %s %s %.2f\n",automovel.Matricula,atual->Entrada.data,atual->Entrada.tempos,automovel.data_saida,automovel.tempo_saida,automovel.valorAPagar);
    }
    
}

/**

*@brief Adiciona informações de saída de um veículo estacionado.
*Esta função percorre a lista de entradas de veículos estacionados para encontrar o veículo
com a placa especificada e adiciona informações de saída a esse nó da lista.
*@param inicio O ponteiro para o início da lista de entradas.
*@param automovel O veículo que está saindo e contém as informações de saída.
*/
void adiciona_saida(NoListaEntradas *inicio, veiculo automovel){
    
    NoListaEntradas *atual = inicio;

    while (atual != NULL){
        if (strcmp(atual->Entrada.Matricula,automovel.Matricula) == NULO && atual->Entrada.estado == VERDADEIRO){
            // Adiciona informações de saida ao Nó da entrada

            strcpy(atual->Entrada.data_saida, automovel.data_saida);
            strcpy(atual->Entrada.tempo_saida, automovel.tempo_saida);
            atual->Entrada.valorAPagar = automovel.valorAPagar;
            atual->Entrada.estado = NULO; // Definir como Fora do Parque
            break;
        }
    atual = atual->prox;
    }
}

/**

*@brief Adiciona um novo parque à lista de parques, se válido.
*Esta função verifica se o parque a ser adicionado é válido usando a função validacao_parques.
*Se o parque for válido, ele é inserido na lista de parques usando a função insere_parque.
*@param aColocar O parque a ser adicionado.
*@param listaParques O ponteiro para o ponteiro para o início da lista de parques.
*@param comp O ponteiro para a variável que armazena o número de comparações realizadas.
*/
void P_args(parque aColocar, NoParque** listaParques, int* comp) {

    int valido = validacao_parques(aColocar,*listaParques);
    if (valido){
        *listaParques = insere_parque(aColocar, *listaParques, comp);
    }
    
}

/**

*@brief Mostra as informações sobre os parques de estacionamento disponíveis.
*Esta função percorre a lista de parques de estacionamento e imprime as informações de cada parque,
*incluindo o nome do parque, a capacidade total de vagas e o número de vagas disponíveis.
*@param listaParques O ponteiro para o início da lista de parques de estacionamento.
*@param Lugares O ponteiro para a variável que armazena o número de lugares disponíveis.
*/
void P_semArgs(NoParque* listaParques, int* Lugares) {
    NoParque* atual = listaParques;
    if (listaParques != NULL){
        while (atual != NULL) {
            if (atual->parque.nome != NULL && strcmp(atual->parque.nome, "") != NULO) {
                *Lugares = atual->parque.capacidade - (atual->parque.numCarros);
                printf("%s %d %d\n", atual->parque.nome, atual->parque.capacidade, *Lugares);
            }
            atual = atual->prox;
        }
    }
}

/**

*@brief Processa a saída de um veículo do estacionamento.
*Esta função busca na lista de entradas pelo veículo que está saindo do estacionamento e realiza
*as operações necessárias para registrar a saída, como calcular o valor a pagar, atualizar o estado
*do veículo e do parque, e registrar a saída na lista de entradas.
*@param Primeiro_no O ponteiro para o primeiro nó da lista de entradas.
*@param automovel_saida O veículo que está saindo do estacionamento.
*@param ListaParques O ponteiro para a lista de parques de estacionamento.
*@param ListaCarros O ponteiro para o ponteiro do início da lista de carros.
*/
void saida_carro(NoListaEntradas *Primeiro_no, veiculo automovel_saida,NoParque* ListaParques,NoListaEntradas**ListaCarros){

    NoListaEntradas *atual = Primeiro_no;
    

    while (atual != NULL) // While loop para percorrer a lista toda
    {
        if  (strcmp(atual->Entrada.Matricula, automovel_saida.Matricula) == NULO && atual->Entrada.estado == VERDADEIRO){
                    
            if (strcmp(atual->Entrada.nome, automovel_saida.nome) == NULO){

                if (compara_horas(atual->Entrada.data,automovel_saida.data_saida,atual->Entrada.tempos,automovel_saida.tempo_saida)){

                    strcpy(horas_inicias, automovel_saida.tempo_saida);
                    strcpy(data_inicial, automovel_saida.data_saida);
                    strcpy(nome, automovel_saida.nome);
                    strcpy(matricula,automovel_saida.Matricula);

                    automovel_saida.estado = NULO;
                    automovel_saida.valorAPagar = calculo_valor(automovel_saida,ListaParques,atual);
                    aumenta_lugares(ListaParques,automovel_saida);

                    escreve_saida(automovel_saida,atual);
                    remover_no(ListaCarros,atual);
                    adiciona_saida(Primeiro_no,automovel_saida);
                    
                    break;

                }
                else {printf("invalid date.\n");automovel_saida.estado = VERDADEIRO;}
            }
        }
    atual = atual->prox; //Avanca na lista ligada
    }
        
}

/**

*@brief Processa a entrada de um veículo no estacionamento.
*Esta função verifica se há vagas disponíveis no parque de estacionamento
*correspondente ao veículo que está entrando. Se houver vaga, o veículo é
*adicionado à lista de entradas e à lista de carros, e suas informações são
*registradas. Além disso, atualiza o número de vagas disponíveis no parque.
*@param pListaParques O ponteiro para a lista de parques de estacionamento.
*@param Automovel_entrada O veículo que está entrando no estacionamento.
*@param pLugares O ponteiro para o número de lugares disponíveis no parque.
*@param Primeiro_no O ponteiro para o ponteiro do início da lista de entradas.
*@param ListaCarro O ponteiro para o ponteiro do início da lista de carros.
*/
void entrada_carro(NoParque* pListaParques,veiculo Automovel_entrada, int* pLugares, NoListaEntradas **Primeiro_no,NoListaEntradas** ListaCarro){

    veiculo* pAutomovel = NULL;
    pAutomovel = (veiculo*)malloc(sizeof(veiculo));
    NoParque *atual = pListaParques;
    if (pAutomovel != NULL){ // Verificar que alocou corretamente a memoria
            while (atual != NULL)
            {
                if(strcmp(atual->parque.nome,Automovel_entrada.nome) == NULO){

                    int *ptr_Carro = &atual->parque.numCarros;
                    cria_carro(pAutomovel,Automovel_entrada);
                    ListaCarro = adicionar_veiculo(ListaCarro,*pAutomovel);
                    Primeiro_no = adicionar_veiculo(Primeiro_no, *pAutomovel);
                    escreve_carro(atual,pAutomovel,pLugares,ptr_Carro);
                    
                }
            atual = atual->prox;
            }
            free(pAutomovel);  
        
    } 
}

/**
 * @brief Realiza operações relacionadas ao comando 'p' (parque) no menu principal.
 * 
 * Esta função processa o comando 'p' seguido por argumentos, os quais podem incluir
 * informações sobre a capacidade e localização de um novo parque de estacionamento.
 * Se os argumentos forem fornecidos, um novo parque é adicionado à lista de parques
 * de estacionamento. Se nenhum argumento for fornecido, são exibidas informações
 * sobre todos os parques de estacionamento existentes.
 * 
 * @param escolha A string contendo a entrada do usuário para o comando 'p'.
 * @param ListaParques O ponteiro para a lista de parques de estacionamento.
 * @param ptrCarros O ponteiro para o número total de carros nos parques.
 * @param numParques O ponteiro para o número total de parques de estacionamento.
 */
void case_p(char escolha[BUFSIZ],NoParque **ListaParques, int* ptrCarros, int* numParques){
    char comando = '\0';
    parque ParqueAColocar = {0};
    char temp[BUFSIZ] = "";
    if (strlen(escolha) > 2) {
                
                if (escolha[CaracterComando] == '"') {
                    sscanf(escolha, "%c \"%[^\"]\" %d %f %f %f", &comando,
                            temp, &ParqueAColocar.capacidade,
                            &ParqueAColocar.x, &ParqueAColocar.y, &ParqueAColocar.z);
                } else {
                    sscanf(escolha, "%c %s %d %f %f %f", &comando,
                            temp, &ParqueAColocar.capacidade,
                            &ParqueAColocar.x, &ParqueAColocar.y, &ParqueAColocar.z);   
                }

                ParqueAColocar.nome = (char*)malloc(strlen(temp)+ 1);
                strcpy(ParqueAColocar.nome,temp);
                P_args(ParqueAColocar,ListaParques, numParques);
               
            } else {
                P_semArgs(*ListaParques, ptrCarros);
            }
}



/**
 * @brief Realiza operações relacionadas ao comando 'e' (entrada) no menu principal.
 * 
 * Esta função processa o comando 'e' seguido por argumentos, que representam as informações
 * de entrada de um veículo no parque de estacionamento. Os argumentos incluem o nome do parque,
 * a matrícula do veículo, a data de entrada e a hora de entrada. Se o veículo for válido e a data
 * de entrada for válida, o veículo é registrado na lista de veículos no parque.
 * 
 * @param escolha A string contendo a entrada do usuário para o comando 'e'.
 * @param pListaParques O ponteiro para a lista de parques de estacionamento.
 * @param pLugares O ponteiro para o número de lugares disponíveis no parque.
 * @param Primeiro_no O ponteiro para o primeiro nó da lista de entrada de veículos.
 * @param ListaCarro O ponteiro para a lista de veículos no parque.
 */
void case_e(char escolha[BUFSIZ],NoParque* pListaParques, int* pLugares,NoListaEntradas **Primeiro_no, NoListaEntradas** ListaCarro){
    char comando = '\0';
    veiculo automovel;
    char temp[BUFSIZ] = "";
    
    if (escolha[CaracterComando] == '"'){
        sscanf(escolha, "%c \"%[^\"]\" %s %s %s",&comando,
                temp,automovel.Matricula,automovel.data,automovel.tempos);
    }else{
        sscanf(escolha, "%c %s %s %s %s",&comando,
                temp,automovel.Matricula,automovel.data,automovel.tempos);
    }           
                
                automovel.nome = (char*)malloc(strlen(temp)+ 1);
                strcpy(automovel.nome,temp);
        if (existe_carro(pListaParques,automovel)){

                if (verificaMatricula(automovel.Matricula)){

                    if (Entrada_Valida(ListaCarro,automovel)){
                        
                        if (tratamento_entrada(horas_inicias,automovel,data_inicial,nome,matricula)){

                            automovel.estado = NULO; 
                            strcpy(horas_inicias, automovel.tempos);
                            strcpy(data_inicial, automovel.data);
                            strcpy(nome, automovel.nome);
                            strcpy(matricula,automovel.Matricula);

                            entrada_carro(pListaParques,automovel,pLugares,Primeiro_no,ListaCarro);
                        }
                        else{printf("invalid date.\n");}

                    }  
                }
                else{
                    printf("%s: invalid licence plate.\n",automovel.Matricula);
                    }
            
        }
}



/**
 * @brief Realiza operações relacionadas ao comando 's' (saída) no menu principal.
 * 
 * Esta função processa o comando 's' seguido por argumentos, que representam as informações
 * de saída de um veículo do parque de estacionamento. Os argumentos incluem o nome do parque,
 * a matrícula do veículo, a data de saída e a hora de saída. Se o veículo existir no parque, a
 * matrícula for válida e a data de saída for válida, o veículo é registrado como tendo saído do parque.
 * 
 * @param escolha A string contendo a entrada do usuário para o comando 's'.
 * @param Primeiro_No O ponteiro para o primeiro nó da lista de entrada de veículos.
 * @param ListaParques O ponteiro para a lista de parques de estacionamento.
 * @param ListaCarros O ponteiro para a lista de veículos no parque.
 */
void case_s(char escolha[BUFSIZ], NoListaEntradas *Primeiro_No, NoParque *ListaParques,NoListaEntradas** ListaCarros){

        char comando;
        veiculo automovel;
        char temp[BUFSIZ];
        
    // Tratamento Inputs

        if (escolha[CaracterComando] == '"'){
            sscanf(escolha, "%c \"%[^\"]\" %s %s %s",&comando,
                    temp,automovel.Matricula,automovel.data_saida,automovel.tempo_saida);
        }else{
            sscanf(escolha, "%c %s %s %s %s",&comando,
                    temp,automovel.Matricula,automovel.data_saida,automovel.tempo_saida);
        }
                automovel.nome = (char*)malloc(strlen(temp)+ 1);
                strcpy(automovel.nome,temp);
        

    // Verificacao inicial do input
    if (existe_Parque(ListaParques,automovel)){

        if (verificaMatricula(automovel.Matricula)){

            if (verifica_saida(*ListaCarros,automovel)){

                if (tratamento_saida(horas_inicias,automovel,data_inicial,nome_saida,matricula_saida)){
                    automovel.estado = NULO;
                    saida_carro(Primeiro_No,automovel,ListaParques,ListaCarros);
                     
                }
                else {
                printf("invalid date.\n");
                }
            }
        }
        else{
            printf("%s: invalid licence plate.\n",automovel.Matricula);
            }
    }
}


/**
 * @brief Escreve os registos de entrada e saída de um veículo.
 * 
 * Esta função escreve os registos de entrada e saída de um veículo, incluindo o nome do veículo,
 * a data e hora de entrada e a data e hora de saída. Os registos são formatados de acordo com as
 * condições especificadas, como a presença de zeros à esquerda nos horários.
 * 
 * @param atual O nó atual da lista de entrada de veículos contendo as informações de entrada e saída.
 */
void escreve_Registos(NoListaEntradas* atual){

    if (atual->Entrada.tempos[NULO] >= '0' && atual->Entrada.tempos[NULO] <= '9' && atual->Entrada.tempo_saida[NULO]>= '0' && atual->Entrada.tempo_saida[NULO] <= '9' &&
        atual->Entrada.tempos[1] == ':' && atual->Entrada.tempo_saida[1] == ':'){
    printf("%s %s 0%s %s 0%s\n", atual->Entrada.nome, atual->Entrada.data, atual->Entrada.tempos, atual->Entrada.data_saida, atual->Entrada.tempo_saida);
                    
    }
    else if(atual->Entrada.tempo_saida[NULO]>= '0' && atual->Entrada.tempo_saida[NULO] <= '9' && atual->Entrada.tempo_saida[1]== ':'){
    printf("%s %s %s %s 0%s\n", atual->Entrada.nome, atual->Entrada.data, atual->Entrada.tempos, atual->Entrada.data_saida, atual->Entrada.tempo_saida);
                    
    }
    else if(atual->Entrada.tempos[NULO] >= '0' && atual->Entrada.tempos[NULO] <= '9' && atual->Entrada.tempos[1] == ':'){
    printf("%s %s 0%s %s %s\n", atual->Entrada.nome, atual->Entrada.data, atual->Entrada.tempos, atual->Entrada.data_saida, atual->Entrada.tempo_saida);
                    
    }
    else{
        printf("%s %s %s %s %s\n", atual->Entrada.nome, atual->Entrada.data, atual->Entrada.tempos, atual->Entrada.data_saida, atual->Entrada.tempo_saida);
                    
    }
}

/**
 * @brief Escreve os registos de entrada de um veículo, excluindo a hora de saída.
 * 
 * Esta função escreve os registos de entrada de um veículo, incluindo o nome do veículo,
 * a data e hora de entrada. Os registos são formatados de acordo com as condições especificadas, 
 * como a presença de zeros à esquerda nos horários.
 * 
 * @param atual O nó atual da lista de entrada de veículos contendo as informações de entrada.
 */
void escreve_DataE(NoListaEntradas* atual){


    
    if(atual->Entrada.tempos[NULO] >= '0' && atual->Entrada.tempos[NULO] <= '9' && atual->Entrada.tempos[1] == ':'){
        printf("%s %s 0%s\n", atual->Entrada.nome, atual->Entrada.data, atual->Entrada.tempos);
                   
    }
    else{
        printf("%s %s %s\n", atual->Entrada.nome, atual->Entrada.data, atual->Entrada.tempos);
                    
    }
}


/**
 * @brief Imprime os registos de entrada de um veículo com base na matrícula especificada.
 * 
 * Esta função percorre a lista de registos de entrada de veículos e imprime os registos de entrada
 * correspondentes à matrícula especificada. Os registos são formatados de acordo com a presença
 * ou ausência da hora de saída.
 * 
 * @param matricula A matrícula do veículo para a qual se deseja imprimir os registos.
 * @param Registo O ponteiro para o início da lista de registos de entrada de veículos.
 */
void Imprime_registos(char matricula[MATRICULA], NoListaEntradas *Registo) {
    
    if (Registo == NULL){
        return;
    }
    
    NoListaEntradas *atual = Registo;
    int cont = VERDADEIRO;
    
        while (atual != NULL) {
            // Verifica se o ponteiro atual não é nulo
            
            // Verifica se a matrícula do registro atual corresponde à matrícula especificada
            if (strcmp(matricula, atual->Entrada.Matricula) == NULO) {
                if (atual->Entrada.data_saida[0] != '\0'){
                    escreve_Registos(atual);
                    cont = NULO;
                }
                else{
                    escreve_DataE(atual);
                    cont = NULO;
                }
                
            }   
            // Avança para o próximo nó na lista
            atual = atual->prox;
        }

        if (cont) {
            printf("%s: no entries found in any parking.\n", matricula);
        }

}



/**
 * @brief Ordena uma lista de registos de entrada de veículos.
 * 
 * Esta função ordena uma lista de registos de entrada de veículos com base em critérios específicos,
 * utilizando o algoritmo de ordenação Bubble Sort.
 * 
 * @param Inicio O ponteiro para o início da lista de registos de entrada de veículos.
 */
void Ordenacao_Lista(NoListaEntradas *Inicio){

    NoListaEntradas *atual = Inicio;
    
    if (atual == NULL)return;

    while (atual != NULL)
    {   
        
        NoListaEntradas *proximo = atual->prox; // Move a declaração do próximo nó para dentro do loop
        if (proximo == NULL) break; 

        while (proximo != NULL)
        {
            if (compara_ord(atual,proximo)){
                troca(atual,proximo);
            }
            proximo = proximo->prox;
        }
        
        atual = atual->prox;
    }
}

/**
 * @brief Realiza operações relacionadas à visualização de registos de entrada de veículos.
 * 
 * Esta função processa o comando 'v' para visualizar os registos de entrada de veículos
 * correspondentes a uma matrícula especificada. Os registos são ordenados e impressos.
 * 
 * @param escolha A string contendo o comando 'v' seguido pela matrícula a ser visualizada.
 * @param Primeiro_No O ponteiro para o primeiro nó da lista de registos de entrada de veículos.
 */           
void case_v(char escolha[BUFSIZ],NoListaEntradas *Primeiro_No){
        
        char comando,matricula[MATRICULA];

        // Tratamento de inputs

        sscanf(escolha,"%c %s",&comando,matricula);

        if (verificaMatricula(matricula)){
            
            if (Primeiro_No == NULL) return;
            Ordenacao_Lista(Primeiro_No);
            if (matricula[0] == '\0') return;          
            Imprime_registos(matricula,Primeiro_No);

        }
        else{
            printf("%s: invalid licence plate.\n",matricula);
        }

}



/**
 * @brief Ordena a lista de registos de entrada de veículos por data e hora de entrada.
 * 
 * Esta função ordena a lista de registos de entrada de veículos com base na data e hora de entrada,
 * utilizando o algoritmo de ordenação por seleção. A ordenação é realizada de forma ascendente.
 * 
 * @param Primeiro_No O ponteiro para o primeiro nó da lista de registos de entrada de veículos.
 */
void ordenaF(NoListaEntradas *Primeiro_No){

    NoListaEntradas *atual = Primeiro_No;

    while (atual != NULL)
    {
        NoListaEntradas *proximo = atual->prox; // Move a declaração do próximo nó para dentro do loop

        while (proximo != NULL)
        {
            if (compara_F(atual,proximo)){
                troca(atual,proximo);
            }
            proximo = proximo->prox;
        }
        
        atual = atual->prox;
    }
}

/**
 * @brief Escreve as informações de saída de um veículo formatadas.
 * 
 * Esta função escreve as informações de saída de um veículo, incluindo a matrícula, 
 * a hora de saída e o valor a pagar, em um formato específico.
 * 
 * @param atual O ponteiro para o nó atual da lista de registos de saída de veículos.
 */
void escreve_F(NoListaEntradas *atual){

    int horas = NULO, minutos = NULO;

    sscanf(atual->Entrada.tempo_saida,"%d:%d",&horas  ,&minutos);

    printf("%s %02d:%02d %.2f\n", atual->Entrada.Matricula,horas,minutos,atual->Entrada.valorAPagar);
}


/**
 * @brief Escreve as informações de saída de veículos para uma data e nome específicos.
 * 
 * Esta função escreve as informações de saída de veículos que correspondem à data especificada
 * e ao nome do parque de estacionamento, em um formato específico.
 * 
 * @param Primeiro_No O ponteiro para o primeiro nó da lista de registos de saída de veículos.
 * @param data A data específica para a qual se deseja obter os registos de saída.
 * @param nome O nome do parque de estacionamento para o qual se deseja obter os registos de saída.
 */
void F_Data(NoListaEntradas* Primeiro_No,char data[DATA],char* nome){

    NoListaEntradas *atual = Primeiro_No;
    ordenaF(Primeiro_No);
    if (data_inicial[0] != '\0' && tratamento_F(data,data_inicial)){
        
        while (atual != NULL)
        {
            if (strcmp(nome,atual->Entrada.nome) == NULO){

                if (strcmp(data,atual->Entrada.data_saida) == NULO){
                    escreve_F(atual);
                }

            }
            atual = atual->prox;
        }

    }

}


/**
 * @brief Imprime o valor faturado em uma data específica.
 * 
 * Esta função calcula e imprime o valor total faturado em uma data específica, somando os valores
 * pagos por cada veículo que saiu do parque de estacionamento nessa data.
 * 
 * @param inicio O ponteiro para o primeiro nó da lista de registos de saída de veículos.
 */
void Imprime_Datas(NoListaEntradas *inicio){

    NoListaEntradas *atual = inicio;
    float valor_faturado = NULO;
    while (atual != NULL)
    {
        if (strcmp(inicio->Entrada.data_saida,atual->Entrada.data_saida) == NULO){
            valor_faturado += atual->Entrada.valorAPagar;
        }
        atual = atual->prox;
    }
    printf("%s %.2f\n",inicio->Entrada.data_saida,valor_faturado);
}


/**
 * @brief Imprime o valor faturado para um determinado cliente em datas separadas.
 * 
 * Esta função calcula e imprime o valor total faturado para um cliente em datas separadas,
 * somando os valores pagos por cada veículo que saiu do parque de estacionamento em diferentes
 * datas.
 * 
 * @param Primeiro_No O ponteiro para o primeiro nó da lista de registos de saída de veículos.
 * @param nome O nome do cliente para o qual se deseja calcular o valor faturado.
 */
void F_semData(NoListaEntradas *Primeiro_No, char *nome) {
    
    if (nome == NULL)return;

    // Variáveis para armazenar a data atual e o valor facturado
    char data_atual[DATA] = "";
    float valor_facturado = 0.0;
    NoListaEntradas *atual = Primeiro_No;
    ordenaF(Primeiro_No);
    
    while (atual != NULL) {
        
        if (strcmp(atual->Entrada.nome, nome) == 0) {
            
            if (strcmp(data_atual, atual->Entrada.data_saida) != 0) {
                
                if (strcmp(data_atual, "") != 0) {
                    printf("%s %.2f\n", data_atual, valor_facturado);
                }
                
                strcpy(data_atual, atual->Entrada.data_saida); //guarda data_saida
                valor_facturado = 0.0;// Reinicia o valor faturado para uma data diferente
            }
            
            valor_facturado += atual->Entrada.valorAPagar;
        }
        atual = atual->prox;
    }

    // Imprime o valor facturado para a última data
    if (strcmp(data_atual, "") != NULO) {
        printf("%s %.2f\n", data_atual, valor_facturado);
    }
}


/**
 * @brief Realiza a operação de faturação para um cliente específico em datas específicas ou em todas as datas.
 * 
 * Esta função realiza a operação de faturação para um cliente específico em datas específicas ou em todas as datas.
 * O valor faturado é impresso para cada data em que o cliente realizou uma saída do parque de estacionamento.
 * Se não forem especificadas datas, o valor faturado é calculado para todas as datas em que o cliente saiu.
 * 
 * @param escolha A escolha do utilizador contendo o comando, o nome do cliente e, opcionalmente, a data para filtrar a faturação.
 * @param Primeiro_no O ponteiro para o primeiro nó da lista de registos de saída de veículos.
 * @param ListaParques O ponteiro para a lista de parques de estacionamento.
 */
void case_f(char escolha[BUFSIZ],NoListaEntradas *Primeiro_no, NoParque* ListaParques){

    char comando, temp[BUFSIZ],data[DATA] = {0};

    if (escolha[2] == '"'){
        sscanf(escolha,"%c \"%[^\"]\" %s",&comando,temp,data);
    }else{
        sscanf(escolha,"%c %s %s",&comando,temp,data);
    }
    

    char* nome = (char*)malloc(strlen(temp)+1);
    strcpy(nome,temp);
    int tamanho = strlen(data);


    if (verifica_Parque(ListaParques,nome)){
    
        if (!tamanho){

            F_semData(Primeiro_no,nome);
        }
        else{

            F_Data(Primeiro_no,data,nome);
        }
    }

}

/**
 * @brief Troca os dados de dois nós na lista de parques de estacionamento.
 * 
 * Esta função troca os dados de dois nós na lista de parques de estacionamento.
 * 
 * @param a O primeiro nó da troca.
 * @param b O segundo nó da troca.
 */
void trocaR(NoParque *a, NoParque *b) {
    parque temp = a->parque; 
    a->parque = b->parque;    
    b->parque = temp;        
}


/**
 * @brief Ordena a lista de parques de estacionamento por ordem alfabética do nome.
 * 
 * Esta função ordena a lista de parques de estacionamento por ordem alfabética do nome,
 * utilizando o algoritmo de ordenação por seleção.
 * 
 * @param Lista O ponteiro para o primeiro nó da lista de parques de estacionamento.
 */
void OrdenaR(NoParque* Lista){

    NoParque *atual = Lista;
    
    while (atual != NULL)
    {
        NoParque *proximo = atual->prox;
        while (proximo != NULL)
        {
            if (strcmp(atual->parque.nome,proximo->parque.nome) > NULO){
                trocaR(atual,proximo);
            }
            proximo = proximo->prox;
        }
        
    atual = atual->prox;
    
    }
    
}

/**
 * @brief Remove um parque de estacionamento da lista e libera a memória alocada.
 * 
 * Esta função remove um parque de estacionamento da lista, identificado pelo nome especificado,
 * e libera a memória alocada para esse parque. A função também reordena a lista após a remoção.
 * 
 * @param ListaP O ponteiro para o ponteiro do primeiro nó da lista de parques de estacionamento.
 * @param nome O nome do parque de estacionamento a ser removido.
 */
void Auxiliar_r(NoParque **ListaP, char *nome) {
    NoParque *atual = *ListaP;
    NoParque *anterior = NULL;

    
    OrdenaR(*ListaP);

    while (atual != NULL) {
        if (strcmp(atual->parque.nome, nome) == NULO) {
            NoParque *proximo = atual->prox;
            free(atual->parque.nome);
            free(atual);

            if (anterior != NULL) {
                anterior->prox = proximo;
            } else {
                *ListaP = proximo;
            }
            atual = proximo;
        } else {
            printf("%s\n", atual->parque.nome);            
            anterior = atual;
            atual = atual->prox;
        }
    }
}


/**
 * @brief Destroi os registros de entrada de veículos associados a um determinado nome.
 * 
 * Esta função destroi os registros de entrada de veículos associados a um determinado nome na lista,
 * liberando a memória alocada para esses registros. A função remove todos os registros associados
 * ao nome especificado.
 * 
 * @param Primeiro_No O ponteiro para o primeiro nó da lista de registros de entrada.
 * @param nome O nome associado aos registros de entrada a serem destruídos.
 */
void Destroi_Registo(NoListaEntradas* Primeiro_No, char* nome){

    if (nome == NULL)return;
    NoListaEntradas* atual = Primeiro_No;
    NoListaEntradas* anterior = NULL;

    while (atual != NULL)
    {
        if (atual == NULL) break;

        if (strcmp(atual->Entrada.nome,nome) == NULO){
            if (anterior == NULL) {
                Primeiro_No = atual->prox;
            } else {
                anterior->prox = atual->prox;
            }
            free(atual->Entrada.nome);
            free(atual);
            break;
        }
        anterior = atual;
        atual = atual->prox;
    }
    
}


/**
 * @brief Remove um parque e seus registros associados.
 * 
 * Esta função remove um parque e seus registros associados, tanto na lista de parques como nos registros
 * de entrada de veículos e na lista de veículos estacionados. Ela remove todos os registros associados
 * ao nome do parque especificado.
 * 
 * @param escolha A string contendo o comando e o nome do parque a ser removido.
 * @param ListaParques O ponteiro para a lista de parques.
 * @param Primeiro_No O ponteiro para o primeiro nó da lista de registros de entrada.
 * @param ListaCarro O ponteiro para o primeiro nó da lista de veículos estacionados.
 */
void case_r(char escolha[BUFSIZ],NoParque** ListaParques, NoListaEntradas* Primeiro_No, NoListaEntradas *ListaCarro){

    //Tratamento Input

    char comando,temp[BUFSIZ];

    if (escolha[2] == '"'){
        sscanf(escolha,"%c \"%[^\"]\"",&comando,temp);
    }else{
        sscanf(escolha,"%c %s",&comando,temp);
    }

    char* nome = (char*)malloc(strlen(temp) + 1);
    strcpy(nome, temp);
    
    if (verifica_Parque(*ListaParques,nome)){

        Auxiliar_r(ListaParques,nome);
        Destroi_Registo(Primeiro_No,nome);
        Destroi_Registo(ListaCarro,nome);

    }
}

