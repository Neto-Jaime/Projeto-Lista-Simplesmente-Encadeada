#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Node *NODEPTR;

struct Consulta {
  char nome[100];
  int crm;
  int cpf;
  int dia, mes, hora;
  char especialidade[100];
};

struct Node {
  struct Consulta elem;
  NODEPTR next;
};
//TODA VEZ QUE ENCERRO O PROGRAMA ESSA FUNÇAÕ SLAVA TODO O CONTEUDO DA LISTA BEM COMO POSIÇÕES, PARA QUANDO FOR ABRIR O PROGRAMA DE NOVO SEJA LIDO O ARQUIVO ATUALIZDO
void salvar_Lista(NODEPTR inicio){
  FILE *arqbin = fopen("consultas.bin", "wb");

  if(arqbin == NULL){
    printf("Erro ao abrir o arquivo para escrita\n");
    return;
  }
  NODEPTR aux = inicio;

  while(aux != NULL){
    fwrite(&aux->elem, sizeof(struct Consulta), 1, arqbin);
    aux = aux->next;
  }
  fclose(arqbin);
  printf("Informações salvas com sucesso\n");
  printf("Obrigado por usar o sistema\n");
}



void insertAscend(struct Consulta elem, NODEPTR *inicio) {

  NODEPTR prox, ant, new_no;
  ant = NULL;
  prox = *inicio;
  while (prox != NULL && (elem.mes >= prox->elem.mes && elem.dia >= prox->elem.dia)) {
    ant = prox;
    prox = prox->next;
  }

  new_no = (NODEPTR)malloc(sizeof(struct Node));
  new_no->elem = elem;
  new_no->next = prox;
  if (ant == NULL) {
    *inicio = new_no;
  }else {
    ant->next = new_no;
  }
}
//FUNÇÃO PARA CARREGAR INICIALMENTE OS DADOS DO ARQUIVO E O ADICIONAR NA LISTA ENCADEADA COMO NA ULTIMA EXECUÇÃO
NODEPTR abrir_Lista(){
  FILE *arqbin = fopen("consultas.bin", "rb");

  if(arqbin == NULL){
    printf("Erro ao abrir arquivo para leitura\n");
    return NULL;
  }
  NODEPTR inicio = NULL;
  struct Consulta consulta;
  while(fread(&consulta, sizeof(struct Consulta), 1, arqbin) == 1){
    insertAscend(consulta, &inicio);
  }
  fclose(arqbin);
  printf("DADOS CARREGADOS...\n");
  return inicio;
}
//Função para imprimir as respectivas informçãoes de cada opção quando solicitada
void impressoes(NODEPTR *inicio){
  NODEPTR aux = *inicio;
  printf("__________________________________________");
  printf("\n Nome: %s\n CPF: %d\n CRM: %d\n Especialidade: %s\n Dia: %d\n Mes: %d\n Hora: %d\n", aux->elem.nome, aux->elem.cpf, aux->elem.crm, aux->elem.especialidade, aux->elem.dia, aux->elem.mes, aux->elem.hora);
}

void pesq_crm(NODEPTR inicio, int crm){

  NODEPTR aux = inicio;
  printf("\n\nConsultas para o CRM %d:\n", crm);
  while (aux != NULL){
    if (aux->elem.crm == crm) {
      impressoes(&aux);
    }
    aux = aux->next;
  }
}

void pesq_cpf(NODEPTR inicio, int cpf){

  NODEPTR aux = inicio;
  printf("\n\nTodas as Consultas realizadas para o CPF: %d são:\n", cpf);
  while (aux != NULL) {
    if (aux->elem.cpf == cpf) {
      impressoes(&aux);
    }
    aux = aux->next;
  }
}
//Verifica se já existe consulta marcada naquele dia, mês, cpf e hora (Evitar Duplicidade)
int verificar_dia_mes(NODEPTR inicio, int dia, int mes, int cpf, int hora, int crm){

  int resultado = 0;
  NODEPTR aux = inicio;
  while (aux != NULL) {
    if ((aux->elem.dia == dia && aux->elem.mes == mes) && (aux->elem.hora == hora && aux->elem.crm == crm)) {
      resultado = 1;
    }else if(aux->elem.cpf == cpf && (aux->elem.dia == dia && aux->elem.mes == mes)){
      resultado = 2;
    }
    aux = aux->next;
  }
  return resultado;
}
// Função Cancelar Consulta recebe o primeiro elemento da lista e o cpf para comparar e cancelar a consulta
void cancelar_consulta(NODEPTR *inicio, int cpf, int crm, int dia, int mes){
// ant serve para manter o nó anterior a prox
// prox serve para auxiliar a verificar e pecorrer a lista
  NODEPTR ant, prox;
  ant = NULL;
  prox = *inicio;

  while (prox != NULL && prox->elem.cpf != cpf) {
    ant = prox;
    prox = prox->next;
  }
  printf("_____________________________________________\n");
  if(prox != NULL && prox->elem.cpf == cpf && prox->elem.crm == crm && prox->elem.dia == dia && prox->elem.mes == mes){
    impressoes(&prox);
    printf("Consulta acima, DESMARCADA!\n\n\n");
    if ( ant == NULL){
      *inicio = prox->next;
    } else{
      ant->next = prox->next;
    }
    free(prox);
  }else{
    printf("\nNão existe consulta cadastrada para a partir dos dados informado: \nCPF: %d\n CRM: %d\n Dia: %d\n Mês: %d\n", cpf, crm, dia, mes);
  }
}
  //Verifica se há consulta a partir do dia e mês, escolhido pelo usuario

void pesq_consulta(int dia, int mes, NODEPTR *inicio){
  NODEPTR aux = *inicio;
  int encontrou = 0;

  while (aux != NULL) {
    if(aux->elem.dia == dia && aux->elem.mes == mes){
      impressoes(&aux);
      encontrou = 1;

    }
    aux = aux->next;
  }
  if(!encontrou){
    printf("_______________________________________");
    printf("Não existe consulta cadastrada para o dia: %d/%d \n", dia, mes);
  }

}
//Imprime toda a lista conforme a data crescente
void imprimir_consultas(NODEPTR inicio) {
  NODEPTR aux = inicio;

  printf("\nTodas as Consultas marcadas são:\n");
  while (aux != NULL) {
    impressoes(&aux);
    aux = aux->next;
  }

}

//Faz uma verificação para saber se o cpf já existe na lista e se os nomes coincidem, caso não coinicide, o nome é adicionado
int validar_nome_cpf(NODEPTR *inicio, char nome[100], int cpf){
  NODEPTR aux = *inicio;
  int existe = 0;
  while (aux != NULL) {
    if(aux->elem.cpf == cpf && strcmp(aux->elem.nome, nome) != 0 ){
      printf("ATENÇÃO: Já existe um outro paciente com esse CPF informado:\n");
      printf("Paciente cadastrado: \nNOME: %s\nCPF: %d\n", aux->elem.nome, cpf);
      printf("___________________________\n");
      printf("Nome informado: %s\n", nome);
      printf("CPF informado: %d\n", cpf);
      existe = 1;
      break;
    }
    aux = aux->next;
  }
  return existe;
}

//Coloca o nome de todos pacientes em maiusculo, para evitar possiveis erros de digitação do usuario
void letra_Maiusculas(char nome[100]) {
  int i = 0;
  while (nome[i] != '\0') {
      nome[i] = toupper(nome[i]);
    i++;
  }
}

int main(void) {
  //INICIALIZA "INICIO" A LISTA DA ULTIMA EXECUÇÃO, OBS: SE É A PRIEMIRA EXECUÇÃO O VALOR SERÁ NULL
  NODEPTR inicio = abrir_Lista();
  struct Consulta consulta;
  int opcao, dia, mes, cpf, crm;
  int resultado = 0, existe = 0;
  // MENU
  do {

    printf("\n\n----------------BEM VINDO----------------\n");
    printf("---------------Clinica Reis--------------\n");
    printf("1 - Cadastrar Consulta\n");
    printf("2 - Pesquisar Consulta p/ dia/mes\n");
    printf("3 - Pesquisar Consulta p/ CRM\n");
    printf("4 - Pesquisar Consulta p/ CPF\n");
    printf("5 - Cancelar Consulta\n");
    printf("6 - Imprimir todas as Consultas\n");
    printf("7 - SAIR\n");
    printf("Informe uma opcao: ");
    scanf(" %d", &opcao);
    // OPÇÕES DO MENU
    switch (opcao) {

    case 1:
      do{
        printf("Digite o nome do paciente:\n");
        scanf(" %[^\n]", consulta.nome);
        letra_Maiusculas(consulta.nome);
        printf("Digite o CPF do paciente:\n");
        scanf(" %d", &consulta.cpf);
        existe = validar_nome_cpf(&inicio, consulta.nome, consulta.cpf);
      }while(existe != 0);

      printf("Digite o CRM do médico:\n");
      scanf(" %d", &consulta.crm);
      printf("Digite a especialidade do médico:\n");
      scanf(" %[^\n]", consulta.especialidade);
      printf("Digite o dia da consulta:\n");
      scanf(" %d", &consulta.dia);
      // Verificar se o dia da consulta vai de 1 a 31
      while(consulta.dia < 1 || consulta.dia > 31){
        printf("Dia invalido, digite novamente:\n");
        scanf(" %d", &consulta.dia);
      }
      // Verificar se o mes da consulta vai de 1 a 12
      printf("Digite o mes da consulta:\n");
      scanf(" %d", &consulta.mes);
      while(consulta.mes < 1 || consulta.mes >12){
        printf("Mês invalido, digite novamente:\n");
        scanf(" %d", &consulta.mes);
      }

      printf("Digite a hora da consulta:\n");
      scanf(" %d", &consulta.hora);
      // Verificar se a ESTA ENTRE 00:00 A 23:00 (HORARIO VALIDO)
      while(consulta.hora < 0 || consulta.hora > 23){
        printf("Horario Invalido, digite um horario válido: \n");
        scanf(" %d", &consulta.hora);
      }

      // Verifica de o horario é as 12h (Almoço)
      // Verificar se a hora da consulta vai de 7h a 18h
      while(consulta.hora < 7 || consulta.hora > 18 || consulta.hora == 12){
        if(consulta.hora == 12){
            printf("Horario de almoço, digite outro horario: \n");
            scanf(" %d", &consulta.hora);
          }else{
            printf("Horario fora do expediente, digite outro horario: \n");
            scanf(" %d", &consulta.hora);
          }
        }

      resultado = verificar_dia_mes(inicio, consulta.dia, consulta.mes, consulta.cpf, consulta.hora, consulta.crm);

      if (resultado == 1){
        printf("ATENÇÃO! Ja existe uma consulta marcada nesta data: %d/%d HORA: %dh Nº de CRM: %d\n-----------\n", consulta.dia, consulta.mes, consulta.hora, consulta.crm);
        pesq_consulta(consulta.dia, consulta.mes, &inicio);

      }else if(resultado == 2){
        printf("ATENÇÃO! Ja existe uma consulta marcada neste CPF: %d no dia %d/%d\n----------\n", consulta.cpf, consulta.dia, consulta.mes);
        pesq_consulta(consulta.dia, consulta.mes, &inicio);

      }else if(resultado == 0){

        insertAscend(consulta, &inicio);

        printf("-----CONSULTA MARCADA!-----\n\n\n");
      }
      break;

    case 2:

      printf("Digite o dia da consulta: ");
      scanf(" %d", &dia);
      printf("Digite o mes da consulta: ");
      scanf(" %d", &mes);
      printf("\n\nAs consultas marcadas para o dia %d/%d são:\n", consulta.dia, consulta.mes);
      pesq_consulta(dia, mes, &inicio);
      break;
    case 3:
      printf("Digite o CRM do medico: ");
      scanf(" %d", &crm);
      pesq_crm(inicio, crm);

      break;
    case 4:
      printf("Digite o CPF para consultar: ");
      scanf(" %d", &cpf);
      pesq_cpf(inicio, cpf);

      break;
    case 5:
      printf("Digite o CPF p/ CANCELAR CONSULTA: ");
      scanf(" %d",&cpf);
      printf("Digite o CRM p/ CANCELAR CONSULTA: ");
      scanf(" %d",&crm);
      printf("Digite o DIA da p/ CANCELAR CONSULTA: ");
      scanf(" %d",&dia);
      printf("Digite o MÊS p/ CANCELAR CONSULTA: ");
      scanf(" %d",&mes);
      cancelar_consulta(&inicio,cpf, crm, dia, mes);

      break;
    case 6:
      imprimir_consultas(inicio);
      break;
    case 7:

      break;
    default:
      printf("Opcao invalida");
      break;
    }
  } while (opcao != 7);
  salvar_Lista(inicio);
  return 0;
}