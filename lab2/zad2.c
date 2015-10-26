#include <stdio.h>
#include <ctype.h>
#define MAX 10

int vertexes = 0;
int tableDegree[MAX] = {0};

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
        int degree = 0;

        while((c = fgetc(file)) != EOF){
            if(isdigit(c)){
                c = c - '0';
                graphMatrix[counterRows][counterCols] = c;
                degree += c;
                counterCols ++;
            }
            else if(c == '\n'){
                counterCols = 0;
                tableDegree[counterRows] = degree;
                degree = 0;
                counterRows ++;
            }

            vertexes = counterRows + 1;
        }
        tableDegree[counterRows] = degree;
        fclose(file);

        return 1;
    }
}

// ------------------------------------------------

void printGraph(int graphMatrix[][MAX]){

    int i,j;

    printf("\n\nGraf:\n");

    for(j=0; j < vertexes; j++){
        for(i=0; i < vertexes; i++){
            printf("%d ",graphMatrix[j][i]);
        }

        printf("     degree : %d ", tableDegree[j]);
        printf("\n");
    }
}


// ------------------------------------------------

void cycleSearch(int graphMatrix[][MAX]){

    int fathertable[MAX][2] = {-2};
    int leaftable[MAX][2] = {0};
    int leaftablepom[MAX][2] = {0};
    int fatherindexes[MAX] = {0};
    int graphcenter[2] = {0};
    int root = 0; // ukorzeniam drzewo
    int diameter = 0;
    int tableindex = 0;
    int i,j,k;

    fathertable[0][0] = root;
    fathertable[0][1] = -1;

    k=0;

    // tworzenie tablicy ojców
    while(k != vertexes){
        for(i=0; i<vertexes; i++){
            if(fathertable[k][0] != i){
                if(graphMatrix[fathertable[k][0]][i]){
                    tableindex ++;
                    fathertable[tableindex][0] = i;
                    fathertable[tableindex][1] = fathertable[k][0];
                    fatherindexes[i] = tableindex;
                    graphMatrix[fathertable[k][0]][i] = 0;
                    graphMatrix[i][fathertable[k][0]] = 0;
                }
            }
        }
        k++;
    }

    // przepisanie z tablicy ojcow do tablicy lisci aby na niej dzialac
    for(i=tableindex; i>=0; i--){
            leaftable[i][0] = fathertable[i][0];
            leaftable[i][1] = fathertable[i][1];
            leaftablepom[i][0] = fathertable[i][0];
            leaftablepom[i][1] = fathertable[i][1];
    }

    // tworzenie tablicy lisci
   while(tableindex != 1){
        j = 0;
        for(i=tableindex; i>=diameter; i--){
            if(tableDegree[leaftable[i][1]] - 1 == 1){

                leaftablepom[j][0] = fathertable[fatherindexes[leaftable[i][1]]][0];
                leaftablepom[j][1] = fathertable[fatherindexes[leaftable[i][1]]][1];

                if(leaftable[j][1] != -1)
                    diameter ++;

                j++;
            }
        }

        // przepisanie z tablicy pomocniczej do tablicy lisci

        for(i=tableindex; i>diameter; i--){
            leaftable[i][0] = leaftablepom[tableindex-i][0];
            leaftable[i][1] = leaftablepom[tableindex-i][1];
        }

        // znalezienie wierzcholka ktory jest centrum
        if(tableindex - diameter == 1){
            graphcenter[0] = leaftable[tableindex][0];

            if(leaftable[tableindex][1] == -1)
                graphcenter[1] = 0;
            else
                graphcenter[1] = leaftable[tableindex][1];

            tableindex = 1;
        }
   }

    printf("\n srednica grafu: %d  \n", diameter);
    printf("\n centrum to wierzcholek: %d  lub  %d \n", graphcenter[0], graphcenter[1]);
    printGraph(graphMatrix);
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

