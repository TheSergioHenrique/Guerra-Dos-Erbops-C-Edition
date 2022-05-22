#define LIMITE 120
#define LIMITE_VERT 30
#define PONTOS_GANHAR 100
#define PONTOS_ACERTO 10

#define TELA_INICIAL "telas\\inicio.txt"
#define TELA_JOGO "telas\\jogo.txt"
#define TELA_FIM "telas\\fim.txt"
#define TELA_CONFIGURACOES "telas\\configuracoes.txt"

#define FACIL 0
#define MEDIO 1
#define DIFICIL 2

int dificuldades[3][2] = {
    {15, 28},
    {10, 20},
    {5, 13}};

int dificuldade = FACIL;
int tempoDeExistencia = 0;