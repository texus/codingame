#include <stdio.h>

int decode(char* str)
{
    int result = 0;
    int index = strlen(str);
    char lastChar = 0;
    
    while (index > 0) {
        index--;
        
        if (str[index] == 'M') {
            result += 1000;
        }
        else if (str[index] == 'D') {
            result += 500;
        }
        else if (str[index] == 'C') {
            if (lastChar == 'D' || lastChar == 'M') {
                result -= 100;
            }
            else {
                result += 100;
            }
        }
        else if (str[index] == 'L') {
            result += 50;
        }
        else if (str[index] == 'X') {
            if (lastChar == 'L' || lastChar == 'C') {
                result -= 10;
            }
            else {
                result += 10;
            }
        }
        else if (str[index] == 'V') {
            result += 5;
        }
        else if (str[index] == 'I') {
            if (lastChar == 'V' || lastChar == 'X') {
                result -= 1;
            }
            else {
                result += 1;
            }
        }
        
        lastChar = str[index];
    }
    
    return result;
}

char rom[11];
char* encode(int num)
{
    int index = 0;
    while (num > 0) {
        if (num >= 1000) {
            rom[index++] = 'M';
            num -= 1000;
        }
        else if (num >= 900) {
            rom[index++] = 'C';
            rom[index++] = 'M';
            num -= 900;
        }
        else if (num >= 500) {
            rom[index++] = 'D';
            num -= 500;
        }
        else if (num >= 400) {
            rom[index++] = 'C';
            rom[index++] = 'D';
            num -= 400;
        }
        else if (num >= 100) {
            rom[index++] = 'C';
            num -= 100;
        }
        else if (num >= 90) {
            rom[index++] = 'X';
            rom[index++] = 'C';
            num -= 90;
        }
        else if (num >= 50) {
            rom[index++] = 'L';
            num -= 50;
        }
        else if (num >= 40) {
            rom[index++] = 'X';
            rom[index++] = 'L';
            num -= 40;
        }
        else if (num >= 10) {
            rom[index++] = 'X';
            num -= 10;
        }
        else if (num >= 9) {
            rom[index++] = 'I';
            rom[index++] = 'X';
            num -= 9;
        }
        else if (num >= 5) {
            rom[index++] = 'V';
            num -= 5;
        }
        else if (num >= 4) {
            rom[index++] = 'I';
            rom[index++] = 'V';
            num -= 4;
        }
        else if (num >= 1) {
            rom[index++] = 'I';
            num -= 1;
        }
    }
    
    rom[index] = 0;
    return rom;
}

int main()
{
    char rom1[11];
    scanf("%s", rom1);
    char rom2[11];
    scanf("%s", rom2);
    
    printf("%s\n", encode(decode(rom1) + decode(rom2)));
    return 0;
}
