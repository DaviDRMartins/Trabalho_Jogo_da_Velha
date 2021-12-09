#include <stdio.h>
#include <stdlib.h>

char jogo[3][3];
char jogador1[256], jogador2[256];

void iniciarMatriz() {
    int i,j;
    for(i = 0; i < 3; i++) {
        for(j = 0; j < 3; j++) {
            jogo[i][j] = ' ';
        }
    }
}

int eValido(char letra) {
    if(letra == 'x' || letra == 'O')
        return 1;
    else
        return 0;
}

int coordenadaEhValida(int x, int y) {
    if(x >= 0 && x < 3) {
        if(y >= 0 && y < 3)
            return 1;
    }
    else{
        printf("\nCOORDENADA INVALIDA, digite outra coordenada\n\n");
        return 0;
    }
}

int posicaoValida(int x, int y) {
    if(jogo[x][y] != 'x' && jogo[x][y] != 'O'){
        return 1;
    }
    else{
        printf("\nCOORDENADA INVALIDA, digite outra coordenada\n\n");
        return 0;
    }
}

int ganhouLinhas() {
    int i, j, igual = 1;
    for(i = 0; i < 3; i++) {
        for(j = 0; j < 2; j++) {
            if(eValido(jogo[i][j]) && jogo[i][j] == jogo[i][j+1])
                igual++;
        }
        if(igual == 3)
            return 1;
        igual = 1;
    }
    return 0;
}

int ganhouColunas() {
    int i, j, igual = 1;
    for(i = 0; i < 3; i++) {
        for(j = 0; j < 2; j++) {
            if(eValido(jogo[j][i]) && jogo[j][i] == jogo[j+1][i])
                igual++;
        }
        if(igual == 3)
            return 1;
        igual = 1;
    }
    return 0;
}

int venceuDiagonalPrincipal() {
    int i, igual = 1;
    for(i = 0; i < 2; i++) {
        if(eValido(jogo[i][i]) && jogo[i][i] == jogo[i+1][i+1])
            igual++;
    }
    if(igual == 3)
        return 1;
    else
        return 0;
}

int venceuDiagonalSecundaria() {
    int i, igual = 1;
    for(i = 0; i < 2; i++) {
        if(eValido(jogo[i][3-i-1]) && jogo[i][3-i-1] == jogo[i+1][3-i-2])
            igual++;
    }
    if(igual == 3)
        return 1;
    else
        return 0;
}

void imprimir() {
    int linha, coluna;

    printf("\n\t    0  1  2\n");
    for(linha = 0; linha < 3; linha++) {
        printf("\t%d ", linha);
        for(coluna = 0; coluna < 3; coluna++) {
            if(coluna < 2)
                printf(" %c |", jogo[linha][coluna]);
            else
                printf(" %c ", jogo[linha][coluna]);
        }
        if(linha < 2)
            printf("\n\t   ---------\n");
    }
}

void jogar() {
    int x, y, valida, jogadas = 0, ganhou = 0, ordem = 1;

    do {
        do {
            imprimir();
            printf("\nDigite a coordenada da linha que deseja jogar: ");
            scanf("%d", &x);
            printf("\nDigite a coordenada da coluna que deseja jogar: ");
            scanf("%d", &y);
            valida = coordenadaEhValida(x, y);
            if(valida == 1)
                valida += posicaoValida(x, y);
        } while(valida != 2);
        if(ordem == 1)
            jogo[x][y] = 'x';
        else
            jogo[x][y] = 'O';
        jogadas++;
        ordem++;
        if(ordem == 3)
            ordem = 1;
        ganhou += ganhouLinhas();
        ganhou += ganhouColunas();
        ganhou += venceuDiagonalPrincipal();
        ganhou += venceuDiagonalSecundaria();
    } while(ganhou == 0 && jogadas < 9);

    if(ganhou != 0) {
        imprimir();
        if(ordem - 1 == 1)
            printf("\nVencedor: %sParabens :)\n\n", jogador1);
        else
            printf("\nVencedor: %sParabens :)\n\n", jogador2);
    } else
        printf("\nEMPATE, todo mundo perdeu :(\n\n");
}

int main(void) {

    int continuar;

    printf("Digite o nome do Jogador 1: ");
    fgets(jogador1, 256, stdin);
    printf("Digite o nome do Jogador 2: ");
    fgets(jogador2, 256, stdin);

    do {
        iniciarMatriz();
        jogar();
        printf("Deseja jogar novamente?\n1 - Sim\n2 - Nao\n");
        scanf("%d", &continuar);
    } while(continuar == 1);

    return 0;
}