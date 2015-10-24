#include <stdio.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>
#define MAX 10

int vertexes = 0;

// ------------------------------------------------

int loadFile(int graphMatrix[][MAX]){

    char fileName[50];

    printf("Podaj nazwe pliku: \n");
    scanf("%s",fileName);

    FILE *file;

    if ((file=fopen(fileName, "r"))==NULL){
        printf ("\nNie moge otworzyc pliku '%s' !\n", fileName);
        return 0;
    }
    else{
        char c;
        int counterRows = 0;
        int counterCols = 0;

        while((c = fgetc(file)) != EOF){
            if(isdigit(c)){
                c = c - '0';
                graphMatrix[counterRows][counterCols] = c;
                counterCols ++;
            }
            else if(c == '\n'){
                counterCols = 0;
                counterRows ++;
            }

                vertexes = counterRows + 1;
        }

        fclose(file);

        return 1;
    }
}

// ------------------------------------------------

void cycleSearch(int graphMatrix[][MAX]){

    srand(time(NULL));
    int r = rand() % vertexes;
    int tableneighbor[MAX] = {-1};
    int tablecycle[MAX] = {-1};
    int counter = 0;
    int neighborcounter = -1;
    int i,j,k;

    tablecycle[0] = r;

    printf("\n dodano do sciazki: %d   \n", tablecycle[counter]);

    while(neighborcounter != 0){
        neighborcounter = 0;
        k = 1;
        for(i=0; i<vertexes; i++){
            if(tablecycle[counter] != i){
                if(graphMatrix[tablecycle[counter]][i]){
                    for(j=0; j <= counter; j++){
                       /* printf("\n porownanie: tablecycle[j] %d - %d graphMatrix[tablecycle[counter]][i]  \n", tablecycle[j],i );*/
                        if(tablecycle[j] == i){
                            k = 0;
                        }
                    }
                    if(k){
                       /* printf("\n pozytywny sasiad: %d   \n", i);*/
                        tableneighbor[neighborcounter] = i;
                        neighborcounter ++;
                    }
                }
            }
            k = 1;
        }

        if(neighborcounter > 1){
            r = rand() % neighborcounter;
            counter ++;
           /* printf("\n wybrany sasiad sasiad: %d , gdzie r: %d   \n", tableneighbor[r], r)*/
            tablecycle[counter] = tableneighbor[r];
        }
        else if(neighborcounter == 1){
            counter ++;
            tablecycle[counter] = tableneighbor[0];
        }
        else if(neighborcounter == 0){
            for(j=0; j < counter; j++){
                if(graphMatrix[tablecycle[j]][tablecycle[counter]]){
                    counter ++;
                    tablecycle[counter] = tablecycle[j];
                    j = counter +1;
                }
            }
        }

        printf("\n dodano do sciazki: %d   \n", tablecycle[counter]);
    }
}

// ------------------------------------------------

int main(){

    int fileRead = 0;
    char menu = 'o';
    char fileName[20];
    int graphMatrix[MAX][MAX];
    int i,j,number;

    while(fileRead != 1){
        fileRead = loadFile(graphMatrix);
    }

    while(menu != 'q'){

        printf("\n ------ MENU ------ \n");
        printf("1) Znajdz cykl -  c \n");
        printf("2) Wczytaj dane z pliku -  w \n");
        printf("3) Zakoncz  -  q \n\n");
        scanf("%s",&menu);

        switch(menu){

            case 'c':
                cycleSearch(graphMatrix);
                break;

            case 'w':
                fileRead = loadFile(graphMatrix);
                break;

            case 'q':
                printf("Dziekuje. \n");
                break;
        }
    }

    return 0;

}
