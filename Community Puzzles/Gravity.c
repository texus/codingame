#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main()
{
    int width;
    int height;
    scanf("%d%d", &width, &height);
    
    char map[height][width+1];

    for (int i = 0; i < height; i++) {
        char line[257];
        scanf("%s", line);
        
        strcpy(map[i], line);
    }

    if (height > 1) {
        for (int k = 0; k < height-1; ++k) {
            for (int i = 0; i < height-1; ++i) {
                for (int j = 0; j < width; ++j) {
                    if (map[i][j] == '#' && map[i+1][j] == '.') {
                        map[i+1][j] = '#';
                        map[i][j] = '.';
                    }
                }
            }
        }
    }
    
    for (int i = 0; i < height; i++) {
        printf("%s\n", map[i]);
    }
}
