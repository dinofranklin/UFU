#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char mat[8][5] = {"abc","def","ghi","jkl","mno","pqrs","tuv","wxyz"};

int valid(char num[10]);
void tecladonum(char num[10], int pos, char str[10]);

int main(){
    int pos = 0;
    char num[10], str[10];

    do{
        printf("Digite a sequencia numerica: ");
        scanf("%s", num);
        fflush(stdin);
    }while(valid(num));

    str[strlen(num)] = '\0';
    printf("Palavras possiveis: \n");
    tecladonum(num,pos,str);
    printf("\n");
    return 0;
}

void tecladonum(char num[10], int pos, char str[10]){
    int i;

    for(i = 0; i < strlen(mat[num[pos]-'0'-2]); ++i){

        str[pos] = mat[num[pos]-'0'-2][i];

        if(pos == strlen(num)-1) printf("%s ", str);
        else tecladonum(num,pos+1,str);
    }
    return;
}

int valid(char num[10]){
    int i;
    for(i = 0; i < strlen(num); ++i){
        if(num[i] <= '1' || num[i] > '9'){
            printf("Informe uma sequencia valida!\n");
            return 1;
        }
    }
    return 0;
}
