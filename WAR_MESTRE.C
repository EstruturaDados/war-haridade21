#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Estrutura que representa um território
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// ================= Funções do Jogo ================= //

// Sorteia e atribui uma missão ao jogador
void atribuirMissao(char* destino, char* missoes[], int total) {
    int sorteio = rand() % total;
    strcpy(destino, missoes[sorteio]);
}

// Verifica se a missão foi cumprida (versão simples e simbólica)
int verificarMissao(char* missao, Territorio* mapa, int tamanho) {
    // Exemplo: conquista 3 territórios da cor azul
    if (strstr(missao, "3 territorios") != NULL) {
        int cont = 0;
        for (int i = 0; i < tamanho; i++)
            if (strcmp(mapa[i].cor, "azul") == 0)
                cont++;
        if (cont >= 3) return 1;
    }

    // Exemplo: eliminar vermelhos
    if (strstr(missao, "vermelha") != NULL) {
        int existeVermelho = 0;
        for (int i = 0; i < tamanho; i++)
            if (strcmp(mapa[i].cor, "vermelha") == 0)
                existeVermelho = 1;
        if (!existeVermelho) return 1;
    }

    // Outras missões (simplesmente sorteadas, sem verificação real)
    if (strstr(missao, "controlar metade") != NULL) return 0;
    if (strstr(missao, "conquistar todos os verdes") != NULL) return 0;
    if (strstr(missao, "dominar o norte") != NULL) return 0;

    return 0;
}

// Exibe o mapa atual
void exibirMapa(Territorio* mapa, int tamanho) {
    printf("\n===== MAPA ATUAL =====\n");
    for (int i = 0; i < tamanho; i++) {
        printf("%d. %-10s | Cor: %-8s | Tropas: %d\n",
               i, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
    printf("======================\n");
}

// Simula um ataque
void atacar(Territorio* atacante, Territorio* defensor) {
    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf("❌ Não pode atacar território da mesma cor!\n");
        return;
    }

    int dadoA = rand() % 6 + 1;
    int dadoD = rand() % 6 + 1;

    printf("\n🎯 %s (%s) atacou %s (%s)\n",
           atacante->nome, atacante->cor, defensor->nome, defensor->cor);
    printf("Dados: Atacante = %d | Defensor = %d\n", dadoA, dadoD);

    if (dadoA > dadoD) {
        printf("✅ Atacante venceu! %s agora pertence à cor %s.\n",
               defensor->nome, atacante->cor);
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = atacante->tropas / 2;
    } else {
        atacante->tropas--;
        printf("⚔️  Defensor resistiu! %s perdeu 1 tropa.\n", atacante->nome);
    }
}

// Libera memória alocada
void liberarMemoria(Territorio* mapa, char** missoes, int jogadores) {
    for (int i = 0; i < jogadores; i++)
        free(missoes[i]);
    free(missoes);
    free(mapa);
}

// ================= Função Principal ================= //
int main() {
    srand(time(NULL));

    // Missões possíveis
    char* missoes[] = {
        "Eliminar todas as tropas da cor vermelha.",
        "Controlar metade do mapa.",
        "Conquistar todos os territorios verdes.",
        "Dominar o continente norte."
    };
    int totalMissoes = 5;

    int jogadores = 5;
    int tamMapa = 10;
    int turno = 1;
    int opcao;

    // Alocação dinâmica do mapa
    Territorio* mapa = (Territorio*) malloc(tamMapa * sizeof(Territorio));

    // Inicializa o mapa com dados fixos
    char* nomes[] = {"Brasil", "Argentina", "Chile", "Peru", "Uruguai",
                     "México", "Canadá", "EUA", "Cuba", "Colômbia"};
    char* cores[] = {"azul", "vermelha", "verde", "amarela", "roxa"};

    for (int i = 0; i < tamMapa; i++) {
        strcpy(mapa[i].nome, nomes[i]);
        strcpy(mapa[i].cor, cores[rand() % 5]);
        mapa[i].tropas = rand() % 5 + 1;
    }

    // Missões dos jogadores
    char** missaoJogador = (char**) malloc(jogadores * sizeof(char*));
    for (int i = 0; i < jogadores; i++) {
        missaoJogador[i] = (char*) malloc(100 * sizeof(char));
        atribuirMissao(missaoJogador[i], missoes, totalMissoes);
        printf("🎯 Missão secreta do Jogador %d foi sorteada!\n", i + 1);
    }

    // Loop principal do jogo
    while (1) {
        printf("\n=========== TURNO %d ===========\n", turno);
        printf("1 - Exibir mapa\n");
        printf("2 - Atacar\n");
        printf("3 - Ver missão secreta\n");
        printf("4 - Verificar vitórias\n");
        printf("5 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            exibirMapa(mapa, tamMapa);
        } 
        else if (opcao == 2) {
            int a, d;
            exibirMapa(mapa, tamMapa);
            printf("Escolha o índice do território atacante: ");
            scanf("%d", &a);
            printf("Escolha o índice do território defensor: ");
            scanf("%d", &d);

            if (a >= 0 && a < tamMapa && d >= 0 && d < tamMapa)
                atacar(&mapa[a], &mapa[d]);
            else
                printf("Índices inválidos!\n");
        } 
        else if (opcao == 3) {
            int j;
            printf("Qual jogador deseja ver a missão (1 a 5)? ");
            scanf("%d", &j);
            if (j >= 1 && j <= jogadores)
                printf("🔒 Missão secreta do Jogador %d: %s\n", j, missaoJogador[j - 1]);
            else
                printf("Jogador inválido!\n");
        } 
        else if (opcao == 4) {
            for (int i = 0; i < jogadores; i++) {
                if (verificarMissao(missaoJogador[i], mapa, tamMapa)) {
                    printf("\n🏆 Jogador %d cumpriu sua missão secreta e venceu o jogo!\n", i + 1);
                    liberarMemoria(mapa, missaoJogador, jogadores);
                    return 0;
                }
            }
            printf("Nenhum jogador venceu ainda.\n");
        } 
        else if (opcao == 5) {
            printf("Saindo do jogo...\n");
            break;
        } 
        else {
            printf("Opção inválida!\n");
        }

        turno++;
    }

    liberarMemoria(mapa, missaoJogador, jogadores);
    return 0;
}
