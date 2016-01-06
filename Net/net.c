#include <stdio.h>
#include <string.h>
#define MAX 20

int vertexes = 0;

char fileName[50];
int flowMatrix[MAX][MAX];
int marks[MAX][2];
int maxFlow = 0;

//  ------------------------------------------------------

void printGraph(int flowMatrix[][MAX]){

    int i,j;

    printf("\n\nGraph:\n");

    for(j=0; j < vertexes; j++){
        for(i=0; i < vertexes; i++){
            printf("%d ",flowMatrix[j][i]);
        }
        printf("\n");
    }
}

// ------------------------------------------------

void printMinCut(){

    int i,j,k;
    int counterX = 0;
    int counterY = 0;
    int X[MAX] = {0};
    int Y[MAX] = {0};

    printf("\nMinimal Cut \n");

    for(i=0; i<vertexes; i++){ // sort marked to X, unmarked to y
        if(marks[i][0] != -1){
            X[counterX] = i;
            counterX ++;
        }
        else{
            Y[counterY] = i;
            counterY ++;
        }
    }

    printGraph(flowMatrix);
    printf("\n");

    for(i=0; i<counterX; i++){
        for(j=0; j<counterY; j++){
            if(flowMatrix[Y[j]][X[i]] && X[i] < Y[j]){ // always flow to source
                printf("(%d,%d) ", X[i], Y[j]);
            }
        }
    }

    printf("\nX = {");
    for(i=0; i<counterX; i++){
        printf(" %d ", X[i]);
    }
    printf("}\n");

    printf("V/X = {");
    for(i=0; i<counterY; i++){
        printf(" %d ", Y[i]);
    }
    printf("}\n\n");
}

// ------------------------------------------------

int loadFile(){

    FILE *file;

    int checkData = 1;

    if ((file=fopen(fileName, "r"))==NULL){
        printf ("\nNie moge otworzyc pliku '%s' !\n", fileName);
        return 0;
    }
    else{

        int i,j;

        fscanf(file, "%d", &vertexes);

        for(i=0; i<vertexes; i++){

            marks[i][0] = -1;    // delete marks in array
            marks[i][1] = 0;

            for(j=0; j<vertexes; j++){
                fscanf(file, "%d", &flowMatrix[i][j]);

                if(i == vertexes - 1 && flowMatrix[i][j] != 0){
                    printf ("\nNie nieprawidlowa siec w pliku '%s' !\n", fileName);
                    return 0;
                }
            }
        }

        fclose(file);

        checkData = markGraph(1);

        if(checkData){
            maxFlow = 0;

            for(i=0; i<vertexes; i++){
                marks[i][0] = -1;    // delete marks in array
                marks[i][1] = 0;
            }

            return 1;
        }
        else{
            printf ("\nNie nieprawidlowa siec w pliku '%s' !\n", fileName);
            return 0;
        }
    }
}

// ------------------------------------------------

void flowGraphFix(int L[], int counter){

    int i;

    printf("-------------------------------\n");

    int x = L[counter-1];
    int y = marks[L[counter-1]][0];

    int flow = marks[L[counter-1]][1];

    while(y != -2){  // go from 't' to 's' by marks

        flowMatrix[x][y] += flow;
        flowMatrix[y][x] -= flow;
        counter --;
        x = y;
        y = marks[x][0];
        
    }

    for(i=0; i<vertexes; i++){
        marks[i][0]= -1;
        marks[i][1]= 0;
    }

    maxFlow += flow;  // inc maxFlow
}

// ------------------------------------------------

int markGraph(int flag){

    printGraph(flowMatrix);
    int L[MAX] = {0};
    int counterL;
    int pointerL;
    int i = 0;

    L[0] = 0;   // add 's' to stack
    counterL = 1; // inc counter
    pointerL = 0;// set pointer to 's'
    marks[0][0] = -2;
    marks[0][1] = 1000000;

    printf("\nMark 0 = (-1,+inf) \n");

    while(L[pointerL] != vertexes - 1){

        for(i=0; i<vertexes; i++){
            if(flowMatrix[L[pointerL]][i] && i != L[pointerL]){  // search for capacity in matrix

                if(marks[i][0] == -1){  // if not marked

                    marks[i][0] = L[pointerL];

                    if(flowMatrix[L[pointerL]][i] < marks[L[pointerL]][1]){ // for [-1,+inf] inf always bigger
                        marks[i][1] = flowMatrix[L[pointerL]][i];
                    }
                    else{
                        marks[i][1] = marks[L[pointerL]][1];
                    }

                    if(L[pointerL] < i)
                        printf("Mark %d = (%d+,%d) \n", i, marks[i][0],marks[i][1]); // add + mark
                    else
                        printf("Mark %d = (%d-,%d) \n", i, marks[i][0],marks[i][1]); // add - mark

                    L[counterL] = i;
                    counterL ++;
                }
            }
        }

        if(counterL == pointerL + 1){ // if 't' not marked return 0;
            return 0;
        }
        else{
            pointerL++;
        }
    }

    if(flag == 0)
        flowGraphFix(L,counterL);  // fix flow graph after marking
    
    return 1;
}

// ------------------------------------------------

int FFA(){

    int status = markGraph(0);

    while(status){  // while 't' in L stack continue 
        status = markGraph(0);
    }
}

// ------------------------------------------------

int main(){

    printf("Podaj nazwe pliku: \n");
    scanf("%s",fileName);

    loadFile();
    FFA();
    printMinCut();
    printf("Max flow: %d \n\n", maxFlow);

    return 0;

}
