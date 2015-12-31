#include <stdio.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>
#define MAX 10

int vertexes = 0;
int tableDegree[MAX] = {0};

//  ------------------------------------------------------

void printGraph(int graphMatrix[][MAX]){

    int i,j;

    printf("\n\nGraf:\n");

    for(j=0; j < vertexes; j++){
        for(i=0; i < vertexes; i++){
            printf("%d ",graphMatrix[j][i]);
        }
        printf("     %d ", tableDegree[j]);
        printf("\n");
    }
}

// ------------------------------------------------

void loadFile(int graphMatrix[][MAX]){

    FILE *file;

    file=fopen("dane3.txt", "r");

    char c;
    int counterRows = 0;
    int counterCols = 0;
    int degree = 0;

    while((c = fgetc(file)) != EOF){
        if(isdigit(c)){
            c = c - '0';
            graphMatrix[counterRows][counterCols] = c;
            degree = degree + c;
            counterCols ++;
        }
        else if(c == '\n'){
            counterCols = 0;
            tableDegree[counterRows] = degree;
            degree = 0;
            counterRows ++;
        }

        tableDegree[counterRows] = degree;

        vertexes = counterRows + 1;
		vertexes = 7;
    }


    fclose(file);
}

// ------------------------------------------------

void findEuler(int graphMatrix[][MAX]){

    loadFile(graphMatrix);
	printGraph(graphMatrix);

    int stos[MAX] = {0}; // stos pusty
    int stosCounter = 0;
    int euler[MAX] = {0};
    int eulerCounter = 0;
    int edge[MAX];
    int edgeCounter = 0;
    int i=0;

    srand(time(NULL));
    int r = rand() % vertexes;
    int u = r; // dowolny wierzcholek startowy

    euler[eulerCounter] = u + 1; // Euler <= u
    eulerCounter ++;
    do{  
        if(tableDegree[u] > 0){ // istnieje krawedz wychodzaca z wierzcholka u
            for(i=0; i<vertexes; i++){
                if(graphMatrix[u][i]){
                    edge[edgeCounter] = i;
                    edgeCounter ++;
                }
            }
            r = rand() % edgeCounter;
            stos[stosCounter] = u; // wybierz dowolna krawedz, stos <= u
            graphMatrix[edge[r]][stos[stosCounter]] = 0;
            graphMatrix[stos[stosCounter]][edge[r]] = 0; // usun krawedz {u,v}
            tableDegree[stos[stosCounter]] --;
            tableDegree[edge[r]] --;
            u = edge[r]; // u = v
            stosCounter ++;

            for(i=0; i<edgeCounter; i++){
                edge[i] = 0;
            }
            edgeCounter = 0;
        }
        else{
            u = stos[stosCounter-1];
            stosCounter --;
            euler[eulerCounter] = u + 1;
            eulerCounter ++;
        }
    }while(stosCounter > 0);

    printf("\n Cykl Eulera \n\n");

    for(i=0; i<eulerCounter; i++){
        printf(" %d",euler[i]);
    }

    /*if(eulerCounter != 10)
        findEuler(graphMatrix);
    */
    
}

// ------------------------------------------------

int main(){

    char menu = 'o';
    int graphMatrix[MAX][MAX];
    int i,j,number;

    while(menu != 'q'){

        printf("\n ------ MENU ------ \n");
        printf("1) Znajdz cykl eulera -  c \n");
        printf("2) Wczytaj dane z pliku -  w \n");
        printf("3) Zakoncz  -  q \n\n");
        scanf("%s",&menu);

        switch(menu){

            case 'c':
                findEuler(graphMatrix);
                break;

            case 'w':
                loadFile(graphMatrix);
                break;

            case 'q':
                printf("Dziekuje. \n");
                break;
        }
    }

    return 0;

}
