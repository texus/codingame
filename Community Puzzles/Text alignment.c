#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{
    char alignment[8];
    fgets(alignment, 8, stdin);
    int N;
    scanf("%d", &N); fgetc(stdin);
    
    char lines[N][257];
    
    for (int i = 0; i < N; i++) {
        char text[257];
        fgets(text, 257, stdin);
        strcpy(lines[i], text);
        
        if (lines[i][strlen(lines[i])-1] == '\n')
            lines[i][strlen(lines[i])-1] = 0;
    }

    int length = 0;
    for (int i = 0; i < N; i++) {
        int len = strlen(lines[i]);
        if (len > length)
            length = len;
    }

    if (strcmp("LEFT\n", alignment) == 0) {
        for (int i = 0; i < N; i++) {
            printf("%s\n", lines[i]);
        }
    }
    else if (strcmp("RIGHT\n", alignment) == 0) {
        for (int i = 0; i < N; i++) {
            int len = strlen(lines[i]);
            for (int j = 0; j < length - len; ++j) {
                printf(" ");
            }
            printf("%s\n", lines[i]);
        }
    }
    else if (strcmp("CENTER\n", alignment) == 0) {
        for (int i = 0; i < N; i++) {
            int len = strlen(lines[i]);
            for (int j = 0; j < (length - len)/2; ++j) {
                printf(" ");
            }
            printf("%s\n", lines[i]);
        }
    }
    else if (strcmp("JUSTIFY", alignment) == 0) {
        for (int i = 0; i < N; i++) {
            int words = 1;
            int len = strlen(lines[i]);
            for (int j = 0; j < len; ++j) {
                if (lines[i][j] == ' ')
                    words++;
            }

            if (words > 1) {
                int spacesRequired = length - len + words-1;
                float spaceWidth = spacesRequired / (words-1);
                float totalSpace = 0;
                int spacesPlaced = 0;
                for (int j = 0; j < len; ++j) {
                    if (lines[i][j] == ' ') {
                        totalSpace += spaceWidth;
                        for (int k = spacesPlaced; k < (int)(totalSpace); ++k) {
                            spacesPlaced++;
                            printf(" ");
                        }
                    }
                    else {
                        printf("%c", lines[i][j]);
                    }
                }
                printf("\n");
            }
            else {
                printf("%s\n", lines[i]);
            }
        }
    }
}
