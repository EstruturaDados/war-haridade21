#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;


void cadastrarTerritorios(Territorio* mapa, int qtd);
void exibirTerritorios(Territorio* mapa, int qtd);
void atacar(Territorio* atacante, Territorio* defensor);
void liberarMemoria(Territorio* mapa);


int main() {
    srand(time(NULL)); 

    int qtd;
    printf("Digite o numero de territorios que deseja cadastrar: ");
    scanf("%d", &qtd);
    getchar(); 

    
    Territorio* mapa = (Territorio*) calloc(qtd, sizeof(Territorio));
    if (mapa == NULL) {
        printf("Erro ao alocar memoria.\n");
        return 1;
    }

    cadastrarTerritorios(mapa, qtd);

    int opcao;
    do {
        printf("\n===== MENU =====\n");
        printf("1 - Exibir territorios\n");
        printf("2 - Atacar\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                exibirTerritorios(mapa, qtd);
                break;
            case 2: {
                int iAtacante, iDefensor;
                exibirTerritorios(mapa, qtd);
                printf("\nEscolha o numero do territorio atacante: ");
                scanf("%d", &iAtacante);
                printf("Escolha o numero do territorio defensor: ");
                scanf("%d", &iDefensor);

                // Validação
                if (iAtacante < 0 || iAtacante >= qtd || iDefensor < 0 || iDefensor >= qtd) {
                    printf("Escolha invalida.\n");
                    break;
                }
                if (strcmp(mapa[iAtacante].cor, mapa[iDefensor].cor) == 0) {
                    printf("Nao e possivel atacar um territorio da mesma cor.\n");
                    break;
                }
                if (mapa[iAtacante].tropas <= 1) {
                    printf("O atacante precisa ter mais de 1 tropa para atacar.\n");
                    break;
                }

                atacar(&mapa[iAtacante], &mapa[iDefensor]);
                break;
            }
            case 0:
                printf("Encerrando o jogo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }

    } while (opcao != 0);

    liberarMemoria(mapa);
    return 0;
}


void cadastrarTerritorios(Territorio* mapa, int qtd) {
    printf("\n=== Cadastro de Territorios ===\n");
    for (int i = 0; i < qtd; i++) {
        printf("\nTerritorio %d:\n", i);
        printf("Nome: ");
        fgets(mapa[i].nome, 30, stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = '\0'; 

        printf("Cor do exercito: ");
        fgets(mapa[i].cor, 10, stdin);
        mapa[i].cor[strcspn(mapa[i].cor, "\n")] = '\0';

        printf("Quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);
        getchar();
    }
}


void exibirTerritorios(Territorio* mapa, int qtd) {
    printf("\n=== Territorios Cadastrados ===\n");
    for (int i = 0; i < qtd; i++) {
        printf("[%d] Nome: %s | Cor: %s | Tropas: %d\n", i, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}


void atacar(Territorio* atacante, Territorio* defensor) {
    printf("\n>>> BATALHA ENTRE %s (%s) E %s (%s) <<<\n",
           atacante->nome, atacante->cor, defensor->nome, defensor->cor);

    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;

    printf("%s rolou: %d\n", atacante->nome, dadoAtacante);
    printf("%s rolou: %d\n", defensor->nome, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("\n O atacante venceu!\n");
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = atacante->tropas / 2; 
        atacante->tropas = atacante->tropas / 2; 
    } else {
        printf("\n O defensor resistiu ao ataque!\n");
        atacante->tropas -= 1;
    }

    printf("\n--- Resultado apos o ataque ---\n");
    printf("%s (%s) - Tropas: %d\n", atacante->nome, atacante->cor, atacante->tropas);
    printf("%s (%s) - Tropas: %d\n", defensor->nome, defensor->cor, defensor->tropas);
}


void liberarMemoria(Territorio* mapa) {
    free(mapa);
    printf("\nMemoria liberada com sucesso!\n");
}
