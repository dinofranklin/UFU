#include <stdio.h>
#include <stdlib.h>

int main(){
   int i, j, h, sxt, sip, hf;

   do{
      printf("Informe a altura: ");
      scanf("%d", &h);
      if(h%2 == 0) printf("O numero deve ser impar\n");
   }while(h%2 == 0);

   sxt = h/2;
   sip = hf = 0;
   for(i = 0; i < h; ++i){

      for(j = 0; j < sxt; ++j) printf(" ");
      printf("*");
      for(j = 0; j < sip; ++j) printf(" ");
      if(i != h-1 && i) printf("*");

      if(sxt == 0) hf = 1;

      if(hf){
         sip -= 2;
         ++sxt;
      }
      else{
         if(!sip) ++sip;
         else sip += 2;
         --sxt;
      }
      printf("\n");
   }
   return 0;
}
