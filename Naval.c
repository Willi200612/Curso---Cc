#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define TAM 15

void inicializarMapa(int mapa[TAM][TAM]) {
    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++)
            mapa[i][j] = 0;
}

void imprimirMapa(int mapa[TAM][TAM], int ocultar) {
    printf("   ");
    for (int i = 0; i < TAM; i++)
        printf("%2d ", i);
    printf("\n");

    for (int i = 0; i < TAM; i++) {
        printf("%2d ", i);
        for (int j = 0; j < TAM; j++) {
            if (mapa[i][j] == -1)
                printf(" X ");
            else if (ocultar && mapa[i][j] > 0)
                printf(" . ");
            else if (mapa[i][j] == 0)
                printf(" . ");
            else
                printf(" %d ", mapa[i][j]);
        }
        printf("\n");
    }
}

int podeColocar(int mapa[TAM][TAM], int l, int c, int tamanho, char direcao) {
    if (direcao == 'H') {
        if (c + tamanho > TAM) return 0;
        for (int i = 0; i < tamanho; i++)
            if (mapa[l][c + i] != 0) return 0;
    } else {
        if (l + tamanho > TAM) return 0;
        for (int i = 0; i < tamanho; i++)
            if (mapa[l + i][c] != 0) return 0;
    }
    return 1;
}

void colocarNavio(int mapa[TAM][TAM], int l, int c, int tamanho, char direcao) {
    for (int i = 0; i < tamanho; i++) {
        if (direcao == 'H')
            mapa[l][c + i] = tamanho;
        else
            mapa[l + i][c] = tamanho;
    }
}

void posicionarNavios(int mapa[TAM][TAM], int jogador) {
    int tamanhos[] = {5, 4, 3, 2};
    int quantidades[] = {1, 2, 3, 4};

    printf("\n--- Posicionamento dos navios do Jogador %d ---\n", jogador);

    for (int i = 0; i < 4; i++) {
        int tamanho = tamanhos[i];
        int quantidade = quantidades[i];

        for (int q = 0; q < quantidade; q++) {
            int l, c;
            char direcao;
            int valido = 0;

            while (!valido) {
                printf("\nNavio tamanho %d (%d de %d)\n", tamanho, q + 1, quantidade);
                printf("Digite linha e coluna inicial (0 a 14): ");
                scanf("%d %d", &l, &c);
                printf("Direção (H para horizontal, V para vertical): ");
                scanf(" %c", &direcao);
                direcao = toupper(direcao);

                if (direcao != 'H' && direcao != 'V') {
                    printf("Direção inválida! Use H ou V.\n");
                    continue;
                }

                if (podeColocar(mapa, l, c, tamanho, direcao)) {
                    colocarNavio(mapa, l, c, tamanho, direcao);
                    imprimirMapa(mapa, 0);
                    valido = 1;
                } else {
                    printf("Posição inválida ou sobreposição!\n");
                }
            }
        }
    }
}

int atirar(int mapa[TAM][TAM], int l, int c) {
    if (l < 0 || l >= TAM || c < 0 || c >= TAM) {
        printf("Coordenada fora do mapa!\n");
        return 0;
    }

    if (mapa[l][c] == -1) {
        printf("Você já atirou aqui!\n");
        return 0;
    }

    if (mapa[l][c] == 0) {
        printf("Água! Errou o tiro.\n");
        mapa[l][c] = -1;
        return 0;
    } else {
        printf("Acertou um navio de tamanho %d!\n", mapa[l][c]);
        mapa[l][c] = -1;
        return 1;
    }
}

int verificarVitoria(int mapa[TAM][TAM]) {
    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++)
            if (mapa[i][j] > 0)
                return 0;
    return 1;
}

void limparTela() {
    system("cls");
}
int main() {
    int mapa1[TAM][TAM], mapa2[TAM][TAM];
    int vez = 1, l, c;

    inicializarMapa(mapa1);
    inicializarMapa(mapa2);

    posicionarNavios(mapa1, 1);
    limparTela();
    posicionarNavios(mapa2, 2);
    limparTela();

    while (1) {
        printf("\n--- Vez do Jogador %d ---\n", vez);
        if (vez == 1) {
            imprimirMapa(mapa2, 1);
            printf("Digite linha e coluna para atirar: ");
            scanf("%d %d", &l, &c);
            atirar(mapa2, l, c);
            if (verificarVitoria(mapa2)) {
                printf("Jogador 1 venceu!\n");
                break;
            }
        } else {
            imprimirMapa(mapa1, 1);
            printf("Digite linha e coluna para atirar: ");
            scanf("%d %d", &l, &c);
            atirar(mapa1, l, c);
            if (verificarVitoria(mapa1)) {
                printf("Jogador 2 venceu!\n");
                break;
            }
        }
        vez = (vez == 1) ? 2 : 1;
    }

    return 0;
}
