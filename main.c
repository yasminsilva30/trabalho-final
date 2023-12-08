#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char proprietario[50];
  char combustivel[20];
  char modelo[50];
  char cor[20];
  char chassi[20];
  int ano;
  char placa[8];
} Veiculo;

typedef struct No {
  Veiculo veiculo;
  struct No *proximo;
} itemLista;

itemLista *inicializarLista() { return NULL; }

itemLista *adicionarVeiculo(itemLista *lista, Veiculo veiculo) {
  itemLista *novoRegistro = (itemLista *)malloc(sizeof(itemLista));
  novoRegistro->veiculo = veiculo;
  novoRegistro->proximo = lista;
  return novoRegistro;
}

void listarProprietariosAnoDiesel(itemLista *lista) {
  printf("\n Proprietarios de carros do ano de 2010 ou posterior e movidos a diesel: \n");

  itemLista *atual = lista;

  while (atual != NULL) {
    if (atual->veiculo.ano >= 2010 &&
        strcmp(atual->veiculo.combustivel, "diesel") == 0) {
      printf("%s\n", atual->veiculo.proprietario);
    }

    atual = atual->proximo;
  }
}

void listarPlacasLetraJ(itemLista *lista) {
  printf("\n Placas que comecam com a letra J e terminam com 0, 2, 4 ou 7 e seus respectivos proprietarios: \n");

  itemLista *atual = lista;

  while (atual != NULL) {
    if (atual->veiculo.placa[0] == 'J' &&
        (atual->veiculo.placa[7] == '0' || atual->veiculo.placa[7] == '2' ||
         atual->veiculo.placa[7] == '4' || atual->veiculo.placa[7] == '7')) {
      printf("Placa: %s, Proprietario: %s\n", atual->veiculo.placa,
             atual->veiculo.proprietario);
    }

    atual = atual->proximo;
  }
}

void listarModeloCorPlacasVogalSomaPar(itemLista *lista) {
  printf("\n Modelo e cor dos veiculos cujas placas tem como segunda letra uma vogal e a soma dos valores numericos eh par: ");

  itemLista *atual = lista;

  while (atual != NULL) {
    char segundaLetraPlaca = tolower(atual->veiculo.placa[1]);

    if ((segundaLetraPlaca == 'a' || segundaLetraPlaca == 'e' || segundaLetraPlaca == 'i' || segundaLetraPlaca == 'o' || segundaLetraPlaca == 'u') &&
        ((atual->veiculo.placa[2] - '0') + (atual->veiculo.placa[3] - '0') +
         (atual->veiculo.placa[4] - '0') + (atual->veiculo.placa[5] - '0') +
         (atual->veiculo.placa[6] - '0') + (atual->veiculo.placa[7] - '0')) % 2 == 0) {
      printf("\n Modelo: %s / Cor: %s \n", atual->veiculo.modelo, atual->veiculo.cor);
    }

    atual = atual->proximo;
  }
}

void trocarProprietarioSemDigitoZero(itemLista *lista) {
  printf("\n Troca de proprietario para carros com placas sem nenhum digito igual a zero: ");

  char novoProprietario[50];
  char chassiTroca[20];

  printf("\n Digite o novo proprietario: \n");
  scanf(" %[^\n]", novoProprietario);

  printf("\n Digite o numero do chassi para troca: \n");
  scanf(" %[^\n]", chassiTroca);

  itemLista *atual = lista;

  while (atual != NULL) {
    if (strcasecmp(atual->veiculo.chassi, chassiTroca) == 0 && strchr(atual->veiculo.placa, '0') == NULL) {
      strcpy(atual->veiculo.proprietario, novoProprietario);
      printf("\n Troca realizada com sucesso \n");
      return;
    }

    atual = atual->proximo;
  }

  printf("\n Carro nao encontrado ou placa contem digito zero \n");

}

void liberarLista(itemLista *lista) {
  itemLista *atual = lista;
  itemLista *proximo;

  while (atual != NULL) {
    proximo = atual->proximo;
    free(atual);
    atual = proximo;
  }
}

int main() {
  itemLista *listaVeiculos = inicializarLista();
  int opcao;

  do {
    printf("\n Menu: \n");
    printf("\n 1 - Adicionar Veiculo");
    printf("\n 2 - Listar Proprietarios de carros do ano de 2010 ou posterior e movidos a diesel");
    printf(\n 3 - Listar placas que comecam com J e terminam com 0, 2, 4 ou 7");
    printf("\n 4 - Listar modelo e cor de veiculos com placas que tem segunda letra vogal e soma dos valores numericos par");
    printf("\n 5 - Trocar proprietario com numero do Chassi");
    printf("\n 6 - Sair \n");

    printf("\n Escolha uma opcao: ");
    scanf("%d", &opcao);

    switch (opcao) {
    case 1: {
      Veiculo novoVeiculo;

      printf("\n Digite os dados do novo veiculo: \n");
      printf("\n Proprietario: ");
      scanf(" %[^\n]", novoVeiculo.proprietario);

      printf("\n Combustivel (alcool/diesel/gasolina): ");
      scanf(" %[^\n]", novoVeiculo.combustivel);

      printf("\n Modelo: ");
      scanf(" %[^\n]", novoVeiculo.modelo);

      printf("\n Cor: ");
      scanf(" %[^\n]", novoVeiculo.cor);

      printf("\n Numero chassi: ");
      scanf(" %[^\n]", novoVeiculo.chassi);

      printf("\n Ano: ");
      scanf("%d", &novoVeiculo.ano);

      printf("\n Placa: ");
      scanf(" %[^\n]", novoVeiculo.placa);

      listaVeiculos = adicionarVeiculo(listaVeiculos, novoVeiculo);
      break;
    }
    case 2:
      listarProprietariosAnoDiesel(listaVeiculos);
    break;

    case 3:
      listarPlacasLetraJ(listaVeiculos);
    break;
    
    case 4:
      listarModeloCorPlacasVogalSomaPar(listaVeiculos);
    break;

    case 5:
      trocarProprietarioSemDigitoZero(listaVeiculos);
    break;

    case 6:
      printf("\n Fim do programa \n");
    break;

    default:
      printf("\n Opcao invalida. Tente novamente \n");
    }
  } while (opcao != 6);

  liberarLista(listaVeiculos);

  return 0;

}
