#include <stdio.h>
#include <string.h>
#include <math.h>

int main()
{
    int ROUNDS;
    scanf("%d", &ROUNDS);
    int CASH;
    scanf("%d", &CASH); fgetc(stdin);
    for (int i = 0; i < ROUNDS; i++) {
        int BET = ceil(CASH / 4.f);
        
        char PLAY[1025];
        fgets(PLAY, 1025, stdin);
        
        int BALL = atoi(strtok(PLAY, " "));
        char* CALL = strtok(NULL, " ");
        
        if (strcmp(CALL, "PLAIN") == 0)
        {
            int NUMBER = atoi(strtok(NULL, " "));
            if (NUMBER == BALL) {
                CASH += 35 * BET;
                continue;
            }
        }
        else if (strcmp(CALL, "EVEN\n") == 0)
        {
            if ((BALL != 0) && (BALL % 2 == 0)) {
                CASH += BET;
                continue;
            }
        }
        else if (strcmp(CALL, "ODD\n") == 0)
        {
            if (BALL % 2 != 0) {
                CASH += BET;
                continue;
            }
        }

        CASH -= BET;
    }

    printf("%d\n", CASH);
}
