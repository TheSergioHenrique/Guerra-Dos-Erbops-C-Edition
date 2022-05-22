
void carregarConfiguracaoInicial()
{
    system("mode con:cols=120 lines=30");
    system("color 09");
    setlocale(LC_ALL, "Portuguese");
    printf("\e[?25l");
    srand(time(0));
}

void carregarTela(char urlTela[])
{
    system("cls");
    FILE *tela;
    tela = fopen(urlTela, "r");

    if (tela == NULL)
    {
        printf("Não foi possível iniciar o joguinho. :(");
        exit(1);
    }

    char fileReader;
    do
    {
        char fileReader = fgetc(tela);
        if (fileReader == EOF)
            break;
        printf("%c", fileReader);
    } while (fileReader != EOF);
}

void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void desenharBarco(Barco barco)
{
    char barcoImg[2][10] = {
        {'_', '_', '/', '_', '|', '_', '\\', '_', '_'},
        {'\\', '_', 'o', '_', 'o', '_', 'o', '_', '/'}};
    for (int i = 0; i < 2; i++)
    {
        int xDoBarco = barco.x;
        for (int j = 0; j < 10; j++)
        {
            gotoxy(xDoBarco, barco.y);
            printf("%c", barcoImg[i][j]);
            xDoBarco += 1;
        }
        barco.y += 1;
    }
}

void desenharAlvo(Barco alvo)
{
    if (!alvo.ativo)
        return;
    char alvoImg[1][8] = {
        {'\\', '_', '-', '_', '-', '_', '/'}};
    int xDoAlvo = alvo.x;
    for (int j = 0; j < 8; j++)
    {
        gotoxy(xDoAlvo, alvo.y);
        printf("%c", alvoImg[0][j]);
        xDoAlvo += 1;
    }
    alvo.y += 1;
}

void apagarBarco(Barco barco)
{
    gotoxy(barco.x, barco.y);
    puts("                \n               ");
}

int gerarOndas()
{
    gotoxy(LIMITE / 120 + 20, 5);
    gotoxy(LIMITE / 120 + 7, 7);
    printf("              `'-.,_)     `'-.,_)  `   `'-.,_)            `'-.,_)`        `'-.,_)");
    gotoxy(LIMITE / 120 + 17, 11);
    printf("                   `'-.,_)            `'-.,_)        `'-.,_)   `'-.,_)        `'-.,_)");
    gotoxy(LIMITE / 120 + 9, 15);
    printf("            `'-.,_)           '-.,_)`'-.,_)`         `'-.,_)`       `'-.,_)");
    gotoxy(LIMITE / 120 + 12, 19);
    printf("                 `'-.,_)              `'-.,_)     `'-.,_)       `'-.,_)         `'-.,_)");
    gotoxy(LIMITE / 120 + 10, 23);
    printf("                           `'-.,_)     '-.,_)       `'-.,_)`'-.,_)     `'-.,_) ");
}

float solve2(float a, float b, float c, float x)
{
    return a * x * x + b * x + c;
}

void exibirDificuldade()
{
    gotoxy(LIMITE - 20, 1);
    char *dificuldadeStr;
    switch (dificuldade)
    {
    case FACIL:
        dificuldadeStr = "Facil";
        break;
    case MEDIO:
        dificuldadeStr = "Medio";
        break;
    case DIFICIL:
        dificuldadeStr = "Dificil";
        break;
    }
    printf("Dificuldade: %s", dificuldadeStr);
}