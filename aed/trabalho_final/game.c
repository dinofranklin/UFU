#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>
#include "game.h"

void make_map(List **map, char *orig, char *dest){
    int i, n;
    char a, b;
    printf("Criando seu mapa!\n");
    printf("Digite quantas estradas existem entre as cidades:\n");
    scanf("%d", &n);
    printf("Agora digite as %d ligacoes entre as cidades (A B - Ha uma estrada de A par B):\n", n);
    for(i = 0; i < n; ++i){
        printf("Estrada %d: ", i+1);
        getchar();
        scanf("%c %c", &a, &b);
        a = toupper(a);
        b = toupper(b);
        add_city(map[a-'A'], b);
    }
    printf("Digite a cidade de origem: ");
    getchar();
    scanf("%c", &a);
    printf("Digite a cidade de destino: ");
    getchar();
    scanf("%c", &b);
    *orig = toupper(a);
    *dest = toupper(b);
    return;
}

void bfs(List **map, int seen[], int beg){
    int i, t, size;
    ++seen[beg];
    size = list_size(map[beg]);
    for(i = 0; i < size; ++i){
        t = list_position(map[beg], i+1) - 'A';
        if(!seen[t]){
            bfs(map, seen, t);
        }
    }
    return;
}

int verify_map(List **map, char orig, char dest){
    int i;
    int seen[LSIZE];
    for(i = 0; i < LSIZE; ++i){
        seen[i] = 0;
    }
    bfs(map, seen, orig-'A');
    if(!seen[dest-'A'] || orig == dest){
        printf("Erro: Seu mapa nao e valido!\n");
        printf("Digite uma mapa valido:\n");
        printf("1- As cidades de origem e de destino sao diferentes.\n");
        printf("2- Ha pelo menos um caminho ligando as cidades de origem e de destino.\n");
        system("pause");
        system("cls");
        return 1;
    }
    else{
        printf("Mapa validado com sucesso!\n");
        return 0;
    }
}

void clear_map(List **map){
    int i;
    for(i = 0; i < LSIZE; ++i){
        while(list_size(map[i])){
            remove_city(map[i]);
        }
    }
    printf("Mapa limpo com sucesso!\n");
    return;
}

void make_players(CQueue *plyrs, char orig){
    int i, n;
    char name[NSIZE];
    system("cls");
    printf("Agora vamos criar os jogadores!\n");
    printf("Digite o numero de jogadores: ");
    scanf("%d", &n);
    for(i = 0; i < n; ++i){
        printf("Digite o nome do jogador %d: ", i+1);
        getchar();
        scanf("%[^\n]", name);
        enqueue(plyrs, name);
        push(plyrs->last->path, orig);
    }
    printf("Seus jogadores foram criados com sucesso!\n");
    return;
}

bool winner(CQueue *plyrs, char dest){
    if(top(plyrs->current->path) == dest){
        printf("\nParabens!!!\n");
        printf("O jogador %s e o vencedor!\n", front(plyrs));
        return true;
    }
    else{
        update_cqueue(plyrs);
        return false;
    }
}

bool verify_path(List *l, Player *p){
    int i, pos;
    for(i = 0; i < list_size(l); ++i){
        pos = list_position(l, i+1);
        if(!p->visited[pos-'A']){
            return true;
        }
    }
    return false;
}

void backtrack(Player *p){
    pop(p->path);
    printf("%s retrocede para %c\n", p->name, top(p->path));
    return;
}

char random_city(List *l, Player *p){
    int r, t;
    char c;
    while(true){
        t = list_size(l);
        r = rand()%t;
        c = list_position(l, r+1);
        if(!p->visited[c-'A']){
            return c;
        }
    }
}

void update_player(Player *p, char city){
    push(p->path, city);
    printf("%s avanca para %c\n", p->name, city);
    p->visited[city-'A'] = true;
    return;
}

void play_the_game(List **map, CQueue *plyrs){
    char c = top(plyrs->current->path);
    if(verify_path(map[c-'A'], plyrs->current)){
        c = random_city(map[c-'A'], plyrs->current);
        update_player(plyrs->current, c);
    }
    else{
        backtrack(plyrs->current);
    }
    return;
}

void destroy_game(List **map, CQueue *plyrs){
    destroy_cqueue(plyrs);
    destroy_lists(map);
    return;
}
