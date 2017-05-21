#include <stdio.h>
#include <stdlib.h>

int main(){
   int yr, i;
   double sa, st, aux;
   char name[30];
   sa = 90000.00;
   st = 150000.00;

   printf("Digite o nome: ");
   scanf("%[^\n]", name);
   printf("Digite a quantidade de anos trabalhados: ");
   scanf("%d", &yr);

   for(i = 1; i <= yr; ++i){
      aux = sa;
      sa += aux*0.08; //Cálculo do acréscimo da inflação.
      if(i%4 == 0) sa += aux*0.04; //Cálculo do acréscimo quadrienal.
      if(sa > st){ // Verifica se o salário atual já chegou ao teto salarial.
         sa = st;
         break; // Se sim, nenhuma iteração a mais é requerida.
      }
   }

   printf("%s trabalha por %d anos. Salario atual: R$ %.2lf / ano\n", name, yr, sa);

   return 0;
}
