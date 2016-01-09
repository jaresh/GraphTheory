#include <stdio.h>
#include <math.h>
#define NUMBER 5

int graphMatrix[NUMBER][NUMBER];
int graphNumber = 0;
int generated = 0;
FILE *f;

//  ------------------------------------------------------

void printToFile(){

    int i,j;

    for(j=0; j < NUMBER; j++){
        for(i=0; i < NUMBER; i++){
            fprintf(f,"%d ",graphMatrix[j][i]);
        }

        fprintf(f,"\n");
    }
}

//  ------------------------------------------------------

void printGraph(){

    int i,j;

    printf("\n\nGraph Number %d :\n", graphNumber+1);

    for(j=0; j < NUMBER; j++){
        for(i=0; i < NUMBER; i++){
            printf("%d ",graphMatrix[j][i]);
        }

        printf("\n");
    }
}

// ------------------------------------------------

void cycleSearch(){

    int tablecycleRed[NUMBER] = {0};
    int counterRed = -1;
    int tablecycleBlue[NUMBER] = {0};
    int counterBlue = -1;
    int i,j,k;
    int status = 0;

    for(j=0; j<NUMBER; j++){
        for(i=0; i<NUMBER; i++){
            if(j != i){
                if(graphMatrix[j][i] == 1){
                    counterRed ++;
                    tablecycleRed[counterRed] = i;
                }
                else if(graphMatrix[j][i] == 2){
                    counterBlue ++;
                    tablecycleBlue[counterBlue] = i;
                }
            }
        }

        for(k=0; k < counterRed; k++){
            for(i=k; i< counterRed; i++){
                if(graphMatrix[tablecycleRed[k]][tablecycleRed[i+1]] == 1){
                    status = 1;
                }  
            }
        }

        for(k=0; k < counterBlue; k++){
            for(i=k; i< counterBlue; i++){
                if(graphMatrix[tablecycleBlue[k]][tablecycleBlue[i+1]] == 2){
                    status = 1;
                }  
            }
        }

        counterRed = -1;
        counterBlue = -1;
    }

    if(!status){
        printGraph();
        fprintf(f, "\nNO CYCLE !!\n");
        graphNumber ++;
    }
}

// ------------------------------------------------

void generateMatrix(){

    int i,j,k;
    int numberTable[10]={0};

    for(i=0; i<1024; i++) { // 10 edges, 2 colors | 2^10 = 1024 posibilities
 
        // adding combinations to graph matrix

        // seed generation
        numberTable[0] = i%2;
        numberTable[1] = i/2%2;
        numberTable[2] = i/4%2;
        numberTable[3] = i/8%2;
        numberTable[4] = i/16%2;
        numberTable[5] = i/32%2;
        numberTable[6] = i/64%2;
        numberTable[7] = i/128%2;
        numberTable[8] = i/256%2;
        numberTable[9] = i/512%2;

        // printf to file
        fprintf(f,"\n------------------------------------------------");
        fprintf(f,"\nGraph Number %d :\n", i+1);

        fprintf(f, "\nseed: %d %d %d %d %d %d %d %d %d %d\n\n", numberTable[0],numberTable[1],numberTable[2],numberTable[3],numberTable[4],numberTable[5],numberTable[6],numberTable[7],numberTable[8],numberTable[9]);

        // add seed to matrix
        graphMatrix[0][1] = numberTable[0] + 1;
        graphMatrix[0][2] = numberTable[1] + 1;
        graphMatrix[0][3] = numberTable[2] + 1;
        graphMatrix[0][4] = numberTable[3] + 1;

        graphMatrix[1][0] = numberTable[0] + 1;
        graphMatrix[1][2] = numberTable[4] + 1;
        graphMatrix[1][3] = numberTable[5] + 1;
        graphMatrix[1][4] = numberTable[6] + 1;

        graphMatrix[2][0] = numberTable[1] + 1;
        graphMatrix[2][1] = numberTable[4] + 1;
        graphMatrix[2][3] = numberTable[7] + 1;
        graphMatrix[2][4] = numberTable[8] + 1;

        graphMatrix[3][0] = numberTable[2] + 1;
        graphMatrix[3][1] = numberTable[5] + 1;
        graphMatrix[3][2] = numberTable[7] + 1;
        graphMatrix[3][4] = numberTable[9] + 1;

        graphMatrix[4][0] = numberTable[3] + 1;
        graphMatrix[4][1] = numberTable[6] + 1;
        graphMatrix[4][2] = numberTable[8] + 1;
        graphMatrix[4][3] = numberTable[9] + 1;

        printToFile();

        /* 
        printGraph();
        graphNumber++;
        */
        cycleSearch();
    }
}

// ------------------------------------------------

int main(){

    int status = 1;

    f = fopen("generated.txt", "w");

    generateMatrix();

    return 0;
}