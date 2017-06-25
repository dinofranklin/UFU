#include <stdio.h>
#include <stdlib.h>

int main(){
   int x, y, s, aux;

   do{
      printf("Digite x e y positivos: ");
      scanf("%d %d", &x, &y);
   }while(x <= 0 || y <= 0);

   aux = s = x;
   while(aux != 0){
      s *= aux%10;
      aux /= 10;
   }
   if(s == y) printf("%d eh semente de %d\n", x, y);
   else printf("%d nao eh semente de %d\n", x, y);

   return 0;
}
