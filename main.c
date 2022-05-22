#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <locale.h>
#include <windows.h>
#include <stdbool.h>
#include <time.h>

#include "constants.h"
#include "models.h"
#include "utils.h"

bool telaInicial();
void jogar();
bool jogoLoop();
void configuracoes();

int main()
{
    carregarConfiguracaoInicial();

    bool menuAtivo = true;
    while (menuAtivo)
    {
        menuAtivo = telaInicial();
    }

    system("cls");
    printf("\nObrigado pela sua luta contra os Erbops!\n\n");
    getch();

    return 0;
}

bool telaInicial()
{
    system("cls");
    carregarTela(TELA_INICIAL);

    int opcao = getche();
    switch (opcao)
    {
    case '1':
        printf("Seu jogo será carregado em instantes!");
        jogar();
        break;
    case '2':
        configuracoes();
        break;
    case '3':
        return false;
    }
    return true;
}

void jogar()
{
    carregarTela(TELA_JOGO);
    getch();
    system("cls");

    Barco barco, alvo;
    barco.x = 1;
    barco.y = 5;
    alvo.ativo = false;

    Bala bala;
    bala.ativo = false;
    int pontuacao = 0;

    bool jogoAtivo = true;
    while (jogoAtivo)
    {
        gerarOndas();
        jogoAtivo = jogoLoop(&barco, &bala, &alvo, &pontuacao);
        Sleep(5);
    }

    carregarTela(TELA_FIM);
    getch();
}

bool jogoLoop(Barco *barco, Bala *bala, Barco *alvo, int *pontuacao)
{

    // Ações do Teclado
    if (kbhit())
    {
        int c = getch();

        if (c == ' ' && !(*bala).ativo)
        {
            (*bala).ativo = true;
            (*bala).x = (*barco).x;
            (*bala).y = (*barco).y;
            (*bala).traj.A = 0.0009;
            (*bala).traj.B = -(*bala).traj.A * 112;
            (*bala).traj.C = (*barco).y + (*bala).traj.A * 112;
        }

        // Limpar posição anterior do *barco
        apagarBarco(*barco);
        if (c == 'w' || c == 'W')
        {
            if (((*barco).y - 1) < 5)
            {
                gotoxy(1, 0);
                printf("O Barco não pode subir mais!");
            }
            else
            {
                (*barco).y--;
            }
        }
        if (c == 's' || c == 'S')
        {
            if (((*barco).y + 1) > 27)
            {
                gotoxy(1, 0);
                printf("O Barco não pode descer mais!");
            }
            else
            {
                (*barco).y++;
            }
        }
    }

    // Verifica colisão da bala
    int xDoAlvo = (*alvo).x;
    for (int j = 0; j < 8; j++)
    {
        if (xDoAlvo + j == (*bala).x && (*alvo).y == (*bala).y)
        {
            gotoxy(LIMITE / 2 - 6, LIMITE_VERT);
            printf("Boaaa corno fi de rapariga!");
            (*alvo).ativo = false;
            apagarBarco(*alvo);
            *pontuacao += PONTOS_ACERTO;
            if (*pontuacao >= PONTOS_GANHAR)
            {
                return false;
            }
        }
    }

    // Desenha os elementos

    gotoxy(46, 1);
    printf("---<<<PONTOS>>>--- = %.3d / %d", *pontuacao, PONTOS_GANHAR);

    exibirDificuldade();

    if ((*bala).ativo)
    {
        // Limpar posição anterior da bala
        gotoxy((*bala).x, (*bala).y);
        puts(" ");

        (*bala).x += 1;
        (*bala).y = (int)solve2((*bala).traj.A, (*bala).traj.B, (*bala).traj.C, (*bala).x);

        if ((*bala).x >= 115)
        {
            (*bala).ativo = false;
        }
        else
        {
            gotoxy((*bala).x, (*bala).y);
            putchar('>');
        }
    }

    if (!(*alvo).ativo)
    {
        (*alvo).ativo = true;
        (*alvo).x = 105 + (rand() % 8);
        (*alvo).y = 5 + (rand() % 18);
        (*alvo).time = (unsigned long)time(NULL);
        tempoDeExistencia = dificuldades[dificuldade][0] + (rand() % (dificuldades[dificuldade][1] - dificuldades[dificuldade][0]));
    }

    if ((*alvo).ativo)
    {
        int tempoDoBarcoAtivo = (unsigned long)time(NULL) - (*alvo).time;
        gotoxy(1, 1);
        printf("Tempo do Alvo: %lu  ", tempoDeExistencia - tempoDoBarcoAtivo);
        if (tempoDoBarcoAtivo >= tempoDeExistencia)
        {
            (*alvo).ativo = false;
            apagarBarco(*alvo);
        }
    }

    // Desenha o barco aliado
    desenharBarco(*barco);
    // Desenha a canoa
    desenharAlvo(*alvo);
}

void configuracoes()
{
    carregarTela(TELA_CONFIGURACOES);

    int opcao = getche();
    switch (opcao)
    {
    case '1':
        dificuldade = FACIL;
        break;
        break;
    case '2':
        dificuldade = MEDIO;
        break;
        break;
    case '3':
        dificuldade = DIFICIL;
        break;
    default:
        configuracoes();
    }
}