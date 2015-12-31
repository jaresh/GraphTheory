#include <stdio.h>
#define MAX 10

int vertexes = 0;

int flowMatrix[MAX][MAX];
int antiflowMatrix[MAX][MAX];
int marks[MAX][2];
int maxFlow = 0;
int marked[MAX] = {0};
int markedCounter = 0;

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
    int i,j;
    int k = 0;

    printf("\nMinimal Cut \n");

    printf("X = {");
    printf(" 0 ");
    for(j=0; j<markedCounter; j++){
        printf(" %d ", marked[j]);
    }
    printf("}\n");

    printf("V/X = {");
    for(i=1; i<vertexes; i++){
        k = 0;

        for(j=0; j<markedCounter; j++){
            if(marked[j] == i){
                k = 1;
            }
        }

        if(!k){
            printf(" %d ", i);
        }
    }
    printf("}\n\n");
}

// ------------------------------------------------

void loadFile(){

    FILE *file;

    file=fopen("dane2.txt", "r");

    int i,j;

    fscanf(file, "%d", &vertexes);

    for(i=0; i<vertexes; i++){

        marks[i][0] = -1;    // add zeros to marks array
        marks[i][1] = 0;

        for(j=0; j<vertexes; j++){
            fscanf(file, "%d", &flowMatrix[i][j]);
        }
    }

    fclose(file);
}

// ------------------------------------------------

void flowGraphFix(int L[], int counter){

    int i;

    printf("----------- flowGraphFix -----------\n");

    markedCounter = 0; // marked delete because not end of algorithm

    for(i=0; i<counter; i++){
         printf("Mark %d = (%d,%d) \n",i , marks[i][0],marks[i][1]);
    }

    int x = L[counter-1];
    int y = marks[L[counter-1]][0];

    int flow = marks[L[counter-1]][1];

    while(y != -2){

        if(marks[x][1] > 0){
            flowMatrix[y][x] -= flow;
            antiflowMatrix[x][y] += flow;
            
            counter --;
            x = y;
            y = marks[x][0];
        }
        else{
            flowMatrix[x][y] += flow;
            antiflowMatrix[y][x] -= flow;
            
            counter --;
            x = y;
            y = marks[x][0];
        }
        
    }

    for(i=0; i<vertexes; i++){
        if(marks[i][0] != -1){

        }
        marks[i][0]= -1;
        marks[i][1]= 0;
    }

    printGraph(flowMatrix);
    printGraph(antiflowMatrix);

    maxFlow += flow;

    printf("Max flow: %d \n\n", maxFlow);
}

// ------------------------------------------------

int residualGraph(){

    printf("----------- Residual-graph -----------\n");

    int L[MAX] = {0};
    int counterL;
    int pointerL;
    int i;
    int status = 1;

    L[0] = 0;   // add 's' to stack
    counterL = 1; // inc counter
    pointerL = 0;// set pointer to 's'
    marks[0][0] = -2;
    marks[0][1] = 1000000;

    while(L[pointerL] != vertexes - 1 && status){

        for(i=0; i<vertexes; i++){
            if(flowMatrix[L[pointerL]][i] && i != L[pointerL]){ 

                if(marks[i][0] == -1){

                    marks[i][0] = L[pointerL];

                    if(flowMatrix[L[pointerL]][i] < marks[L[pointerL]][1]){
                        marks[i][1] = flowMatrix[L[pointerL]][i];
                    }
                    else{
                        if(marks[L[pointerL]][1] < 0)
                            marks[i][1] = marks[L[pointerL]][1] * -1;
                        else
                            marks[i][1] = marks[L[pointerL]][1];
                    }

                    printf(" i :  %d \n",i);

                    printf("Add mark+ = (%d,%d) \n", marks[i][0],marks[i][1]);
                    marked[markedCounter] = i;
                    markedCounter ++;

                    L[counterL] = i;
                    counterL ++;

                    if(i == vertexes - 1){
                        i = vertexes;
                    }
                }
            }
        }

        for(i=0; i<vertexes; i++){
            if(antiflowMatrix[L[pointerL]][i] && i != L[pointerL]){

                if(marks[i][0] == -1){
                    marks[i][0] = L[pointerL];

                    if(antiflowMatrix[L[pointerL]][i] < marks[L[pointerL]][1]){
                        marks[i][1] = antiflowMatrix[L[pointerL]][i] * -1;
                    }
                    else{
                        marks[i][1] = marks[L[pointerL]][1] * -1;
                    }

                    printf(" i :  %d \n",i);
                    printf("Add mark - = (%d,%d) \n", marks[i][0],marks[i][1]);
                    marked[markedCounter] = i;
                    markedCounter ++;

                    L[counterL] = i;
                    counterL ++;
                }
            }
        }

        if(counterL == pointerL + 1){
            status = 0;
            return 0;
        }
        else{
            pointerL++;
        }
        

        printf("Point now: %d \n", L[pointerL]);
    }

    flowGraphFix(L,counterL);
    return 1;
}

// ------------------------------------------------

int FFA(){

    printGraph(flowMatrix);

    int status = 1;

    status = residualGraph();

    while(status){
        status = residualGraph();
    }
}

// ------------------------------------------------

int main(){

    char menu = 'o';
    int i,j,number;

    while(menu != 'q'){

        printf("\n ------ MENU ------ \n");
        printf("1) Znajdz maksymalny przeplyw -  c \n");
        printf("2) Wczytaj dane z pliku -  w \n");
        printf("3) Zakoncz  -  q \n\n");
        scanf("%s",&menu);

        switch(menu){

            case 'c':
                loadFile(flowMatrix);
                FFA(flowMatrix);
                printMinCut();
                printf("Max flow: %d \n\n", maxFlow);
                break;

            case 'w':
                loadFile(flowMatrix);
                break;

            case 'q':
                printf("Dziekuje. \n");
                break;
        }
    }

    return 0;

}
