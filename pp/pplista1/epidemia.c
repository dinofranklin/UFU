#include <stdio.h>
#include <stdlib.h>

#define DAT 20
#define MAT 5
#define YAT 2017

int main(){
   int din, min, yin, countd, dmax, vld;
   int vet[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
   double res;

   do{
      vld = 0;
      printf("Digite a data de inicio da epidemia (dd/mm/yyyy): ");
      scanf("%d%*c%d%*c%d", &din, &min, &yin);
      if(yin > YAT || (yin == YAT && min > MAT) || (yin == YAT && min == MAT && din > DAT)){
         vld = 1;
      }
      else if(min == 2){
         if(yin%400 == 0 || (yin%4 == 0 && yin%100 != 0)) dmax = 29;
         else dmax = vet[1];
         if(din > dmax) vld = 1;
      }
      else if(din > vet[min-1]) vld = 1;
   }while(vld);

   countd = 0;
   if(yin == YAT && min == MAT) countd += DAT-din;
   else{
      while(1){
         if(yin == YAT && min == MAT){
            countd += DAT;
            break;
         }

         if(min == 2 && (yin%400 == 0 || (yin%4 == 0 && yin%100 != 0))) dmax = 29;
         else dmax = vet[min-1];

         if(din) countd += dmax-din+1;
         else countd += dmax;
         din = 0;

         if(min == 12){
            min = 1;
            ++yin;
         }
         else ++min;
      }
   }

   res = (64.0*countd)-(countd*countd*countd/3.0);
   printf("Numero de pessoas atingidas: %.4lf\n", res);
   printf("Numero de dias transcorridos: %d\n", countd);

   return 0;
}
