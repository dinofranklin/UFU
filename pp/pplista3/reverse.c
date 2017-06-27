#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse(char *str, int len, int i);

int main(){
    char str[1000];
    printf("Digite sua string: ");
    scanf("%[^\n]", str);
    printf("Sua string invertida: \n");
    reverse(str, strlen(str), 0);
    printf("\n");
    return 0;
}

void reverse(char *str, int len, int i){
    if(i == len-1){
        printf("%c", str[i]);
    }
    else{
        reverse(str, len, i+1);
        printf("%c", str[i]);
    }
    return;
}
