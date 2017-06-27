#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double clockangle(double hr, double mn);

int main(){
    double hr, mn, ang, vld;

    vld = 1;
    do{
        printf("Digite o numero de horas e minutos: ");
        scanf("%lf %lf", &hr, &mn);
        if(hr>=24 || hr<0 || mn>=60 || mn<0){
            printf("Informe valores validos\n");
        }
        else vld = 0;
        fflush(stdin);
    }while(vld);

    if(hr>12) hr -= 12;
    ang = clockangle(hr, mn);
    printf("O angulo entre os ponteiros eh de: %.2lf\n", ang);
    return 0;
}

double clockangle(double hr, double mn){
    double at, ah, am;

    ah = hr*60 + mn*0.5;
    if(ah > 180) ah -= 180;
    am = mn*6;
    if(am > 180) am -= 180;

    at = fabs(ah-am);
    return at;
}
