#include <stdio.h>
#include <string.h>

// Estrutura que representa um território
struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;
};

int main() {
    struct Territorio territorios[5];
    int cadastrados = 0;  // Contador de territórios cadastrados
    int opcao;

    do {
        printf("\n===== MENU PRINCIPAL =====\n");
        printf("1 - Cadastrar território\n");
        printf("2 - Exibir territórios cadastrados\n");
        printf("3 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); // limpa o buffer do teclado

        switch (opcao) {
            case 1:
                if (cadastrados < 5) {
                    printf("\n--- Cadastro do Território %d ---\n", cadastrados + 1);

                    printf("Digite o nome do território: ");
                    fgets(territorios[cadastrados].nome, 30, stdin);
                    territorios[cadastrados].nome[strcspn(territorios[cadastrados].nome, "\n")] = '\0';

                    printf("Digite a cor do exército: ");
                    fgets(territorios[cadastrados].cor, 10, stdin);
                    territorios[cadastrados].cor[strcspn(territorios[cadastrados].cor, "\n")] = '\0';

                    printf("Digite a quantidade de tropas: ");
                    scanf("%d", &territorios[cadastrados].tropas);
                    getchar(); // limpa o buffer após ler número

                    cadastrados++;
                    printf("\n Território cadastrado com sucesso!\n");
                } else {
                    printf("\n Limite de 5 territórios atingido!\n");
                }
                break;

            case 2:
                if (cadastrados == 0) {
                    printf("\n Nenhum território cadastrado ainda!\n");
                } else {
                    printf("\n===== LISTA DE TERRITÓRIOS =====\n");
                    for (int i = 0; i < cadastrados; i++) {
                        printf("\nTerritório %d:\n", i + 1);
                        printf("Nome: %s\n", territorios[i].nome);
                        printf("Cor do Exército: %s\n", territorios[i].cor);
                        printf("Quantidade de Tropas: %d\n", territorios[i].tropas);
                    }
                }
                break;

            case 3:
                printf("\n Encerrando o programa... Até logo!\n");
                break;

            default:
                printf("\n Opção inválida! Tente novamente.\n");
        }

    } while (opcao != 3);

    return 0;
}
