#include <stdio.h>
#include <ctype.h>
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

int cycleSearch(int graphMatrix[][MAX]){

    int tablecycle[MAX] = {0};
    int counter = -1;
    int i,j,k;

    for(j=0; j<vertexes; j++){
        for(i=0; i<vertexes; i++){
            if(j != i){
                if(graphMatrix[j][i]){
                    counter ++;
                    tablecycle[counter] = i;
                }
            }
        }

        for(k=0; k < counter; k++){
            for(i=k; i< counter; i++){
               if(graphMatrix[tablecycle[i]][tablecycle[i+1]])
                return 1;
            }
        }

        counter = -1;
    }
    return 0;
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
        printf("1) Znajdz cykl C3 -  c \n");
        printf("2) Wczytaj dane z pliku -  w \n");
        printf("3) Zakoncz  -  q \n\n");
        scanf("%s",&menu);

        switch(menu){

            case 'c':
                number = cycleSearch(graphMatrix);

                if(number)
                    printf("\n Graf posiada cykl C3! \n");
                else
                    printf("\n Graf nie posiada cyklu! \n");
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
