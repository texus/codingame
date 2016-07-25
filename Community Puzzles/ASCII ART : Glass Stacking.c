#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void drawFirstRow(int count, int spaces)
{
    for (int i = 0; i < spaces; ++i) {
        printf(" ");
    }
    
    for (int i = 0; i < count-1; ++i) {
        printf(" *** ");
        printf(" ");
    }
    printf(" *** ");
    
    for (int i = 0; i < spaces; ++i) {
        printf(" ");
    }

    printf("\n");
}

void drawMiddleRow(int count, int spaces)
{
    for (int i = 0; i < spaces; ++i) {
        printf(" ");
    }
    
    for (int i = 0; i < count-1; ++i) {
        printf(" * * ");
        printf(" ");
    }
    printf(" * * ");
    
    for (int i = 0; i < spaces; ++i) {
        printf(" ");
    }

    printf("\n");
}

void drawLastRow(int count, int spaces)
{
    for (int i = 0; i < spaces; ++i) {
        printf(" ");
    }
    
    for (int i = 0; i < count-1; ++i) {
        printf("*****");
        printf(" ");
    }
    printf("*****");
    
    for (int i = 0; i < spaces; ++i) {
        printf(" ");
    }

    printf("\n");
}

void drawGlasses(int count, int glassesInBottomRow)
{
    int width = glassesInBottomRow*5 + (glassesInBottomRow-1);
    int spaces = (width - (count*5 + (count-1))) / 2;

    drawFirstRow(count, spaces);
    drawMiddleRow(count, spaces);
    drawMiddleRow(count, spaces);
    drawLastRow(count, spaces);
}

int main()
{
    int N;
    scanf("%d", &N);

    int glassesUsed = 0;
    int glassesInBottomRow = 0;
    for (int i = 1; i < N; ++i) {
        glassesUsed += i;
        if (glassesUsed > N) {
            glassesUsed -= i;
            glassesInBottomRow = i-1;
            break;
        }
    }
    
    if (glassesInBottomRow == 0) {
        glassesUsed = 1;
        glassesInBottomRow = 1;
    }
    
    for (int i = 1; i <= glassesInBottomRow; ++i) {
        drawGlasses(i, glassesInBottomRow);
    }
}
