#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int main()
{
    int N;
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        char xY[16];
        scanf("%s", xY);

        int X = atoi(strtok(xY, "/"));
        int Y = atoi(strtok(NULL, "/"));
        
        int negative = 0;
        if (X < 0) {
            X = -X;
            negative ^= 1;
        }
        if (Y < 0) {
            Y = -Y;
            negative ^= 1;
        }

        if (Y == 0) {
            printf("DIVISION BY ZERO");
        }
        else if (X == 0) {
            printf("0");
        }
        else {
            if (negative)
                printf("-");
            
            int integer = X / Y;
            if (integer != 0) {
                printf("%d", integer);
                
                if (X % Y)
                    printf(" ");
            }
            
            if (X % Y) {
                X -= integer * Y;
                
                int divisorFound = 1;
                while (divisorFound) {
                    divisorFound = 0;
                    int maxDivisor = fmin(X, Y);
                    for (int j = maxDivisor; j > 1; j--) {
                        if ((X % j == 0) && (Y % j == 0)) {
                            X /= j;
                            Y /= j;
                            divisorFound = 1;
                            break;
                        }
                    }
                }
                
                printf("%d/%d", X, Y);
            }
        }
        printf("\n");
    }

    return 0;
}
