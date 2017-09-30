#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

int main(){
    int v, op, w, v1, v2, a;
    Graph *g;
    do{
        op = menu();
        if(op == 1){
            printf("Digite o numero de vertices: ");
            scanf("%d", &v);
            g = make_graph(v);
            if(g!=NULL) printf("Grafo criado com sucesso!\n");
            else printf("Erro! Tente novamente!\n");
        }
        else if(op == 2){
            printf("Digite os vertices e o peso da aresta (v1, v2, w): ");
            scanf("%d %d %d", &v1, &v2, &w);
            a = insert_edge(g,v1,v2,w);
            if(a==-1) printf("Grafo Inexistente ou vertices invalidos!\n");
            else if(a == 0) printf("A aresta ja existe!\n");
            else printf("Aresta inserida com sucesso!\n");
        }
        else if(op == 3){
            print_graph(g);
        }
        else if(op == 4){
            printf("Digite os vertices (v1, v2):");
            scanf("%d %d", &v1, &v2);
            a = verify_edge(g,v1,v2);
            if(a==-1) printf("Grafo Inexistente ou vertices invalidos!\n");
            else if(a == 0) printf("A aresta nao existe!\n");
            else printf("A aresta existe!\n");
        }
        else if(op == 5){
            printf("Digite os vertices (v1,v2):");
            scanf("%d %d", &v1, &v2);
            a = remove_edge(g,v1,v2);
            if(a==-1) printf("Grafo Inexistente ou vertices invalidos!\n");
            else if(a == 0) printf("A aresta nao existe!\n");
            else printf("Aresta removida com sucesso!\n");    
        }
        else if(op == 6){
            printf("Digite os vertices (v1,v2):");
            scanf("%d %d", &v1, &v2);
            a = consult_edge(g,v1,v2,&w);
            if(a==-1) printf("Grafo Inexistente ou vertices invalidos!\n");
            else if(a == 0) printf("A aresta nao existe!\n");
            else printf("A aresta tem peso %d!\n", w);    
        }
        else if(op == 7 || op == 8){
            free_graph(&g);
        }
        else{
            printf("Opcao Invalida!!!\n");
        }
    }while(op != 8);
    return 0;
}

int menu(){
    int op;
    printf("Grafo Ponderado Direcionado - Lista de Adjacencia.\n");
    printf("[1]. Criar Grafo.\n");
    printf("[2]. Inserir Aresta.\n");
    printf("[3]. Mostrar Grafo.\n");
    printf("[4]. Verificar Aresta.\n");
    printf("[5]. Remover Aresta.\n");
    printf("[6]. Consultar Aresta.\n");
    printf("[7]. Liberar Grafo.\n");
    printf("[8]. Sair.\n");
    scanf("%d", &op);
    return op;
}