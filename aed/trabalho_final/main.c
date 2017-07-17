#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include "game.h"
#include "list.h"
#include "queue.h"
#include "stack.h"

int main(){
    int i;
    char orig, dest;
    system("cls");
    printf("Bem-vindo ao Jogo de Percorrer o Mapa.\n");
    List **map = make_lists();
    do{
        clear_map(map);
        make_map(map, &orig, &dest);
    }while(verify_map(map, orig, dest));

    CQueue *plyrs = make_cqueue();
    make_players(plyrs, orig);

    system("cls");
    printf("Iniciar o jogo? \n");
    system("pause");

    srand(time(NULL));
    while(true){
        play_the_game(map, plyrs);
        //system("pause");
        if(winner(plyrs, dest)) break;
    }

    printf("Obrigado por jogar!!!\n");
    system("pause");

    destroy_game(map, plyrs);

    return 0;
}
