#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "graph.h"

#if defined(_WIN32) || defined(_WIN64)
    const char* CLEAR = "cls";
#else
#ifdef __linux
    const char* CLEAR = "clear";
#endif
#endif

#define and &&
#define not !
#define or ||
#define MAXBUFFER 1000

char buffer[MAXBUFFER];

//FUNCTION DECLARATIONS.
int menu();
int get_int(int *ans);
int write_and_scan(char *msg, int *ans);
int get_string(char *str, int size);
int read_stations(Graph **metro, char *filename);
int read_connections(Graph *metro, char *filename);
void read_file(Graph **metro);


//AUXILIARY FUNCTINOS.
void make_aux(Graph **metro);
void addstation_aux(Graph *metro);
void addconnection_aux(Graph *metro);
void rmstation_aux(Graph *metro);
void rmconnection_aux(Graph *metro);
void verify_aux(Graph *metro);
void traveltime_aux(Graph *metro);
void print_aux(Graph *metro);
void free_aux(Graph **metro);
void added_aux(Graph *metro);
void degree_aux(Graph *metro);
void reachable_aux(Graph *metro);
void optimal_aux(Graph *metro);
void travel_aux(Graph *metro);


int main(){
    int op;
    Graph *metro = NULL;

    while(true){
        op = menu();

        if(op == 1) make_aux(&metro);
        else if(op ==  2) read_file(&metro);
        else if(op ==  3) addstation_aux(metro);
        else if(op ==  4) addconnection_aux(metro);
        else if(op ==  5) rmconnection_aux(metro);
        else if(op ==  6) rmstation_aux(metro);
        else if(op ==  7) verify_aux(metro);
        else if(op ==  8) traveltime_aux(metro);
        else if(op ==  9) print_aux(metro);
        else if(op == 10) added_aux(metro);
        else if(op == 11) degree_aux(metro);
        else if(op == 12) optimal_aux(metro);
        else if(op == 13) travel_aux(metro);
        else if(op == 14) reachable_aux(metro);
        else if(op == 15) free_aux(&metro);
        else if(op == 16) break;
        else printf("ERROR: Something went terribly wrong!\n");

        printf("Press ENTER to go back to the menu!\n");
        fgets(buffer, MAXBUFFER, stdin);
    }
    
    free_graph(&metro);
    printf("Goodbye... \n");
    return 0;
}



//AUXILIARY FUNCTION TO MAKE GRAPH
void make_aux(Graph **metro){
    int max;
    if(not metro){
        printf("ERROR: INVALID GRAPH ADDRESS!\n");
        return;
    }

    if(not write_and_scan("Type the maximum number of nodes: ", &max)){
        return;
    }

    *metro = make_graph(max);
    if(not *metro){
        printf("ERROR: NO MEMORY AVAILABLE\n");
    }
    return;
}



//AUXILIARY TO ADD STATION.
void addstation_aux(Graph *metro){
    int id, wait, flag;
    char name[100];

    if(not write_and_scan("Type the id (number) of the station: ", &id)){
        return;
    }
    
    printf("Type the name of the station: ");
    fgets(buffer, MAXBUFFER, stdin);
    if(not get_string(name, 100)){
        printf("ERROR: NOT VALID INPUT OR STRING OVERFLOW!\n");
        return;
    }

    if(not write_and_scan("Type the wait time of the station: ", &wait)){
        return;
    }

    flag = insert_station(metro, id, wait, name);
    
    if(flag == 1) printf("The station was successfully added on the graph!\n");
    else if(not flag) printf("The station is already in the graph!\n");
    else printf("Sorry! Invalid graph or station id!\n");
    return;
}



//AUXILIARY TO ADD CONNECTION.
void addconnection_aux(Graph *metro){
    int v1, v2, travel, flag;
    char name[100];

    if(not write_and_scan("Type the id (number) of the first station: ", &v1)){
        return;
    }

    if(not write_and_scan("Type the id (number) of the second station: ", &v2)){
        return;
    }

    printf("Type the name of the line that connects the stations: ");
    fgets(buffer, MAXBUFFER, stdin);
    if(not get_string(name, 100)){
        printf("ERROR: NOT VALID INPUT OR STRING OVERFLOW!\n");
        return;
    }

    if(not write_and_scan("Type the travel time of the connection: ", &travel)){
        return;
    }

    flag = insert_connection(metro, v1, v2, name, travel);

    if(flag == 1) printf("The connection was succesfully added!\n");
    else if(not flag) printf("There is already a connection between between the stations!\n");
    else printf("Sorry! Invalid graph or station id or no memory available!\n");
    return;
}



//AUXILIARY TO REMOVE STATION.
void rmstation_aux(Graph *metro){
    int v, flag;

    if(not write_and_scan("Type the id (number) of the station: ", &v)){
        return;
    }
    flag = remove_station(metro, v);
    
    if(flag == 1) printf("The station was succesfully removed!\n");
    else if(not flag) printf("There is no station!\n");
    else printf("Sorry! Invalid graph or station id!\n");
    return;
}



//AUXILIARY TO REMOVE CONNECTION.
void rmconnection_aux(Graph *metro){
    int v1, v2, flag;

    if(not write_and_scan("Type the id (number) of the first station: ", &v1)){
        return;
    }
    if(not write_and_scan("Type the id (number) of the second station: ", &v2)){
        return;
    }
    flag = remove_connection(metro, v1, v2);

    if(flag == 1) printf("The connection was succesfully removed!\n");
    else if(not flag) printf("There is no connection!\n");
    else printf("Sorry! Invalid graph or station id!\n");
    return;
}



//AUXILIARY TO VERIFY CONNECTION.
void verify_aux(Graph *metro){
    int v1, v2, flag;

    if(not write_and_scan("Type the id (number) of the first station: ", &v1)){
        return;
    }
    if(not write_and_scan("Type the id (number) of the second station: ", &v2)){
        return;
    }
    flag = verify_connection(metro, v1, v2);

    if(flag == 1) printf("There is a connection between stations %d and %d!\n", v1, v2);
    else if(not flag) printf("There is no connection between stations %d and %d!\n", v1, v2);
    else printf("Sorry! Invalid graph or station id!\n");
    return;
}



//AUXILIARY TO TRAVEL TIME.
void traveltime_aux(Graph *metro){
    int v1, v2, flag;

    if(not write_and_scan("Type the id (number) of the first station: ", &v1)){
        return;
    }
    if(not write_and_scan("Type the id (number) of the second station: ", &v2)){
        return;
    }
    flag = verify_connection(metro, v1, v2);

    if(flag < -1) printf("There is no connection between stations %d and %d!\n", v1, v2);
    else printf("The travel time between stations %d and %d is %d!\n", v1, v2, flag);
    return;
}



//AUXILIARY TO PRINT GRAPH
void print_aux(Graph *metro){
    
    if(not metro){
        printf("You have not made a graph yet!\n");
        return;
    }

    print_graph(metro);
}



//AUXILIARY TO FREE
void free_aux(Graph **metro){
    free_graph(metro);
    printf("Graph successfully removed and erased!\n");
    return;
}



//AUXILIARY TO ADDED VERTEX.
void added_aux(Graph *metro){
    int ad;
    ad = added_vertex(metro);
    if(ad == -1){
        printf("Sorry! Not a valid graph!\n");
        return;
    }
    printf("The number of added stations is %d\n", ad);
    return;
}



//AUXILIARY TO DEGREE OF.
void degree_aux(Graph *metro){
    int deg, v;
    if(not write_and_scan("Type the id (number) of the station: ", &v)){
        return;
    }

    deg = degree_of(metro, v);
    if(deg == -1){
        printf("Sorry! Invalid graph or vertex id!\n");
        return;
    }
    printf("The degree of station %d is %d\n", v, deg);
    return;
}



//AUXILIARY TO REACHABLE.
void reachable_aux(Graph *metro){
    int v, min;

    if(not write_and_scan("Type the id (number) of the start station: ", &v)){
        return;
    }

    if(not write_and_scan("Type the maximum number of minutes: ", &min)){
        return;
    }

    if(reachable(metro, v, min) == -1){
        printf("Sorry! Invalid graph or vertex id!\n");
    }
    return;
}



//AUXILIARY TO OPTIMAL TRAVEL.
void optimal_aux(Graph *metro){
    char name1[100], name2[100];
    
    printf("Type the name of the start station: ");
    fgets(buffer, MAXBUFFER, stdin);
    if(not get_string(name1, 100)){
        printf("ERROR: NOT VALID INPUT OR STRING OVERFLOW!\n");
        return;
    }

    printf("Type the name of the end station: ");
    fgets(buffer, MAXBUFFER, stdin);
    if(not get_string(name2, 100)){
        printf("ERROR: NOT VALID INPUT OR STRING OVERFLOW!\n");
        return;
    }


    int res = optimal_travel(metro, name1, name2);
    if(res == -1) printf("ERROR: INVALID GRAPH OR NO MEMORY AVAIABLE!\n");
    if(not res) printf("Sorry! No station found of station names are equal!\n");
    return;
}



//AUXILIARY TO TRAVEL STATIONS.
void travel_aux(Graph *metro){
    int i, n;
    char **names;
    char name[100];

    if(not write_and_scan("Type how many stations you want to travel: ", &n)) return;
    names = (char **) malloc(n*sizeof(char *));

    for(i=0; i<n; ++i){
        
        printf("Type the name of a station: ");
        fgets(buffer, MAXBUFFER, stdin);
        if(not get_string(name, 100)){
            printf("ERROR: NOT VALID INPUT OR STRING OVERFLOW!\n");
            return;
        }

        names[i] = (char *) malloc(strlen(name)*sizeof(char));
        strcpy(names[i], name);
    }

    int ans = stations_travel(metro, n, names);
    if(ans == -1){
        printf("Sorry! Invalid graph or station name not found!\n");
    }

    for(i=0; i<n; ++i) free(names[i]);
    free(names);
    return;
}



//READ THE FILES FOR THE DATA ABOUT THE GRAPH.
void read_file(Graph **metro){
    char option[100];
    free(metro);

    printf("Use default file names \"connections.txt\" and \"stations.txt\"? [Y/N]: ");
    fgets(buffer, MAXBUFFER, stdin);
    if(not get_string(option, 100)){
        printf("ERROR: NOT VALID INPUT OR STRING OVERFLOW!\n");
        return;
    }

    if(not strcmp("Y", option) or not strcmp("y", option) or not strcmp("S", option)){
        if(not read_stations(metro, "stations.txt")) return;
        read_connections(*metro, "connections.txt");    
    }

    else{
        char stfile[100], ctfile[100];

        printf("Type the name of the station file: ");
        fgets(buffer, MAXBUFFER, stdin);
        if(not get_string(stfile, 100)){
            printf("ERROR: NOT VALID INPUT OR STRING OVERFLOW!\n");
            return;
        }

        printf("Type the name of the connections file: ");
        fgets(buffer, MAXBUFFER, stdin);
        if(not get_string(ctfile, 100)){
            printf("ERROR: NOT VALID INPUT OR STRING OVERFLOW!\n");
            return;
        }

        if(not read_stations(metro, stfile)) return;
        read_connections(*metro, ctfile);
    }

    printf("Stations and connections successfully loaded!\n");
    return;
}

    

//READ A FILE FOR STATIONS DATA.
int read_stations(Graph **metro, char *filename){
    int id, wait, max;
    char name[100];

    FILE *f = fopen(filename, "r");
    if(not f){
        printf("ERROR: FILE \"%s\" DOES NOT EXIST!\n", filename);
        return 0;
    }
    
    fscanf(f, "%d", &max);
    *metro = make_graph(max);

    printf("Loading %d stations from %s...\n", max, filename);

    while(not feof(f)){
        fscanf(f, "%d", &id);
        fgetc(f); fgetc(f); 
        fscanf(f, "%[^;]s", name);
        fgetc(f);
        fscanf(f, "%d", &wait);
        insert_station(*metro, id, wait, name);
    }

    fclose(f);
    return 1;    
}



//READ A FILE FOR CONNECTIONS DATA.
int read_connections(Graph *metro, char *filename){
    int v1, v2, wait;
    char line[100];

    FILE *f = fopen(filename, "r");
    if(not f){
        printf("ERROR: FILE \"%s\" DOES NOT EXIST!\n", filename);
        return 0;
    }
    printf("Loading connections from %s...\n", filename);

    while(not feof(f)){
        fscanf(f, "%d", &v1);
        fgetc(f);
        fscanf(f, "%d", &v2);
        fgetc(f);fgetc(f);
        fscanf(f, "%[^;]s", line);
        fgetc(f);
        fscanf(f, "%d", &wait);
        insert_connection(metro, v1, v2, line, wait);
    }

    fclose(f);
    return 1;
}



//DISPLAYS THE MENU.
int menu(){
    int op;
    while(true){
        system(CLEAR);

        printf("[01]. Make Graph.\n");
        printf("[02]. Get stations and connections from file.\n");
        printf("[03]. Add station.\n");
        printf("[04]. Add connection.\n");
        printf("[05]. Remove connection.\n");
        printf("[06]. Remove station.\n");
        printf("[07]. Verify connection.\n");
        printf("[08]. Get travel time between stations.\n");
        printf("[09]. Print graph.\n");
        printf("[10]. Number of vertex added to the graph.\n");
        printf("[11]. Get the degree of a vertex.\n");
        printf("[12]. Calculate the optimal path between two stations.\n");
        printf("[13]. Calculate a route given station names.\n");
        printf("[14]. Get stations that are reachable in a given time.\n");
        printf("[15]. Free and erase graph.\n");
        printf("[16]. Exit.\n");

        fgets(buffer, MAXBUFFER, stdin);
        if(not get_int(&op)) printf("Please type a number!\n");
        else if(op < 1 or op > 16) printf("Your number is invalid!\n");
        else return op;

        printf("Press ENTER to try again!\n");
        fgets(buffer, MAXBUFFER, stdin);
    }
}



//WRITES A STRING AND SCAN AN INTEGER.
int write_and_scan(char *msg, int *ans){
    int value;
    printf("%s", msg);
    fgets(buffer, MAXBUFFER, stdin);
    
    if(not get_int(&value)){
        printf("ERROR: Not valid input!\n");
        return 0;
    }

    *ans = value;
    return 1;
}



//FUNCTION TO EXTRACT AN INT FROM A STRING.
int get_int(int *ans){
    if(not ans) return 0;

    int i, j;
    bool tolerance, space;

    i = j = 0;
    if(buffer[i] == '\n' or buffer[i] == '\0') return 0;
    space = false;
    tolerance = true;

    while(buffer[i] != '\0' and buffer[i] != '\n'){
        if(i == MAXBUFFER) return 0;

        if(buffer[i] == ' ' and tolerance){
            i++;
            continue;
        }

        if(buffer[i] == ' ' and not tolerance){
            space = true;
            i++;
            continue;
        }

        else if(space and (buffer[i] >= '0' and buffer[i] <= '9')) return 0;
        else if(buffer[i] < '0' or buffer[i] > '9') return 0;

        tolerance = false;
        buffer[j++] = buffer[i++];
    }
    buffer[j] = '\0';

    int acm = 0;
    for(i=0; i<j; ++i){
        acm += round((buffer[i]-'0')*pow(10,j-1-i));
    }
    *ans = acm;
    return 1;
}



//EXTRACTS A STRING FROM THE BUFFER.
int get_string(char *str, int size){
    if(not str or not size) return 0;

    int i, j, notspace;
    i = j = notspace = 0;
    if(buffer[i] == '\n' or buffer[i] == '\0') return 0;

    while(buffer[i] != '\0' and buffer[i] != '\n'){
        if(j >= size) return 0; //OVERFLOW

        if(buffer[i] != ' '){
            str[j] = buffer[i];
            notspace = j;
            ++i;
            ++j;
        }
        else if(buffer[i] == ' ' and not notspace){
            ++i;
        }
        else if(buffer[i] == ' '){
            str[j] = buffer[i];
            ++i;
            ++j;
        }
    }
    str[notspace+1] = '\0';
    return 1;
}
