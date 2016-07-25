#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int main()
{
    int Level;
    scanf("%d", &Level);
    int Xp;
    scanf("%d", &Xp);
    int N;
    scanf("%d", &N);

    for (int i = 0; i < N; ++i) {
        Xp -= 300;
        while (Xp <= 0) {
            Level++;
            Xp += (int)(Level * sqrt(Level) * 10);
        }
    }

    printf("%d\n", Level);
    printf("%d\n", Xp);
}
