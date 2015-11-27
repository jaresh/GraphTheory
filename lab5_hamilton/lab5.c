#include <stdio.h>
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
    printf("\n");
}

// ------------------------------------------------

void loadFile(int graphMatrix[][MAX]){

    FILE *file;

    file=fopen("dane2.txt", "r");

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
    }

    vertexes = counterRows;

    fclose(file);
}

// ------------------------------------------------

void hamiltonAlg(int graphMatrix[][MAX], int stos[MAX], int removed, int stosCounter){

    int i,j;
    int candidate = -1;
    int u = stos[stosCounter];

    // search for candidate

    for(i=0; i<vertexes; i++){
        if(i != u && i > removed && graphMatrix[u][i]){
            candidate = -1;
            for(j=0; j<=stosCounter; j++){
                if(stos[j] == i){
                    candidate = -2;
                    j = stosCounter + 1; 
                }
            }
            if(candidate != -2){
                candidate = i;
                i = vertexes;
            }     
        }
    }

    

    if(candidate == -2 || candidate == -1){
        printf("Nie znaleziono wierzcholka dla: %d \n", u+1);
        removed = stos[stosCounter];
        stos[stosCounter] = -1;
        stosCounter --;
    }
    else{
        printf("Dodaje na stos: %d      dla %d\n", candidate+1, u+1);
        stosCounter ++;
        stos[stosCounter] = candidate;
    }

    printf("-------------------------\n");

    if(stos[0] == -1)
        printf("\n Graf nie ma drogi hamiltona. \n");
    else if(stosCounter != vertexes - 1)
        hamiltonAlg(graphMatrix, stos, removed, stosCounter);
    else{
        printf("\nDroga Hamiltona: \n");
        for(i=0; i<= stosCounter; i++){
            printf("%d  ",stos[i]+1);
        }
    }    
}

// ------------------------------------------------

void findHamilton(int graphMatrix[][MAX]){

    loadFile(graphMatrix);
    printGraph(graphMatrix);

    int stos[MAX] = {-1}; // stos pusty
    int stosCounter = 0;
    int v = 0;
    int removed = -1;

    stos[0] = v;

    // initialize recursive algorithm
    hamiltonAlg(graphMatrix, stos, removed, stosCounter);
    
}

// ------------------------------------------------

int main(){

    char menu = 'o';
    int graphMatrix[MAX][MAX] = {{0,0}};
    int i,j,number;

    while(menu != 'q'){

        printf("\n ------ MENU ------ \n");
        printf("1) Znajdz sciezke hamiltona -  c \n");
        printf("2) Wczytaj dane z pliku -  w \n");
        printf("3) Zakoncz  -  q \n\n");
        scanf("%s",&menu);

        switch(menu){

            case 'c':
                findHamilton(graphMatrix);
                break;

            case 'q':
                printf("Dziekuje. \n");
                break;
        }
    }

    return 0;

}
