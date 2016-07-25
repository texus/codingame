#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main()
{
    char brackets[1024];
    int index = 0;
    
    char expression[2049];
    scanf("%s", expression);

    int i = 0;
    while (expression[i] != 0) {
        if (expression[i] == '(' || expression[i] == '[' || expression[i] == '{') {
            brackets[index] = expression[i];
            index++;
        }
        else {
            if (expression[i] == ')') {
                if (index == 0) { printf("false\n"); return; }
                if (brackets[index-1] != '(') { printf("false\n"); return; }
                index--;
            }
            else if (expression[i] == ']') {
                if (index == 0) { printf("false\n"); return; }
                if (brackets[index-1] != '[') { printf("false\n"); return; }
                index--;
            }
            else if (expression[i] == '}') {
                if (index == 0) { printf("false\n"); return; }
                if (brackets[index-1] != '{') { printf("false\n"); return; }
                index--;
            }
        }
        ++i;
    }
    
    if (index == 0)
        printf("true\n");
    else
        printf("false\n");
}
