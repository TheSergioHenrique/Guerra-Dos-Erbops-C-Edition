
typedef struct
{
    int x, y;
    bool ativo;
    unsigned long time;
} Barco;

typedef struct
{
    float A, B, C;
} Traj;

typedef struct
{
    char img[1];
    int x, y;
    bool ativo;
    Traj traj;
} Bala;
