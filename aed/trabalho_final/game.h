#ifndef GAME_H
#define GAME_H

#include "list.h"
#include "stack.h"
#include "queue.h"

void make_map(List **l, char *orig, char *dest);

void dfs(List **map, int seen[], int beg);

int verify_map(List **map, char orig, char dest);

void clear_map(List **map);

void make_players(CQueue *plyrs, char orig);

bool winner(CQueue *plyrs, char dest);

bool verify_path(List *l, Player *p);

void backtrack(Player *p);

char random_city(List *l, Player *p);

void update_player(Player *p, char city);

void play_the_game(List **map, CQueue *plyrs);

void destroy_game(List **map, CQueue *plyrs);

#endif
