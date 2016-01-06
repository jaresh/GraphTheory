#include <stdio.h>
#include <string.h>
#define MAX 20

int vertexes = 0;

int flowMatrix[MAX][MAX];
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

int loadFile(){

    FILE *file;

    char fileName[50];
    int checkData = 1;

    printf("Podaj nazwe pliku: \n");
    scanf("%s",fileName);

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

        checkData = residualGraph(1);

        if(checkData){
            maxFlow = 0;
            memset(marked, 0, sizeof marked);

            for(i=0; i<vertexes; i++){
                marks[i][0] = -1;    // delete marks in array
                marks[i][1] = 0;
            }

            markedCounter = 0;
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

    markedCounter = 0; // marked delete because not end of algorithm

    for(i=0; i<counter; i++){
         printf("Mark %d = (%d,%d) \n",i , marks[i][0],marks[i][1]);
    }

    int x = L[counter-1];
    int y = marks[L[counter-1]][0];

    int flow = marks[L[counter-1]][1];

    while(y != -2){  // go from 't' to 's' by marks

        if(marks[x][1] > 0){
            flowMatrix[y][x] -= flow;
            flowMatrix[x][y] += flow;
            
            counter --;
            x = y;
            y = marks[x][0];
        }
        else{
            flowMatrix[x][y] += flow;
            flowMatrix[y][x] -= flow;
            
            counter --;
            x = y;
            y = marks[x][0];
        }
        
    }

    for(i=0; i<vertexes; i++){
        marks[i][0]= -1;
        marks[i][1]= 0;
    }

  //  printGraph(flowMatrix);

    maxFlow += flow;  // inc maxFlow

  //  printf("Max flow: %d \n\n", maxFlow);
}

// ------------------------------------------------

int residualGraph(int flag){

    printGraph(flowMatrix);
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
            if(flowMatrix[L[pointerL]][i] && i != L[pointerL]){  // search for + marks

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

                    //printf(" i :  %d \n",i);
                    //printf("Add mark+ = (%d,%d) \n", marks[i][0],marks[i][1]);
                    marked[markedCounter] = i;
                    markedCounter ++;

                    L[counterL] = i;
                    counterL ++;

                    if(i == vertexes - 1){
                        i = vertexes;
                    }
                }
            }

            else if(flowMatrix[i][L[pointerL]] < 0 && i != L[pointerL]){  // search for - marks

                if(marks[i][0] == -1){
                    marks[i][0] = L[pointerL];

                    if(flowMatrix[i][L[pointerL]] < marks[L[pointerL]][1]){
                        marks[i][1] = flowMatrix[i][L[pointerL]] * -1;
                    }
                    else{
                        marks[i][1] = marks[L[pointerL]][1] * -1;
                    }

                    //printf(" i :  %d \n",i);
                    //printf("Add mark - = (%d,%d) \n", marks[i][0],marks[i][1]);
                    marked[markedCounter] = i;
                    markedCounter ++;

                    L[counterL] = i;
                    counterL ++;
                }
            }
        }

        if(counterL == pointerL + 1){ // if 't' not marked return 0;
            status = 0;
            return 0;
        }
        else{
            pointerL++;
        }
        

        //printf("Point now: %d \n", L[pointerL]);
    }

    if(flag == 0)
        flowGraphFix(L,counterL);  // fix flow graph after marking
    
    return 1;
}

// ------------------------------------------------

int FFA(){

    printGraph(flowMatrix);

    int status = 1;

    status = residualGraph(0);

    while(status){  // while 't' in L stack continue 
        status = residualGraph(0);
    }
}

// ------------------------------------------------

int main(){

    loadFile();
    FFA();
    printMinCut();
    printf("Max flow: %d \n\n", maxFlow);

    return 0;

}
