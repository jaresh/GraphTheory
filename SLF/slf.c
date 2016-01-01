#include <stdio.h>
#include <string.h>
#define MAX 10

int vertexes = 0;

int graphMatrix[MAX][MAX];
int incidentColors[MAX][MAX];
int degreeTable[MAX] = {0};
int incidentTable[MAX] = {0};

int colors = -1;

//  ------------------------------------------------------

void printGraph(int graphMatrix[][MAX]){

    int i,j;

    printf("\n\nGraph:\n");

    for(j=0; j < vertexes; j++){
        for(i=0; i < vertexes; i++){
            printf("%d ",graphMatrix[j][i]);
        }
        //printf("| %d",degreeTable[j]);
        printf("\n");
    }
}

// ------------------------------------------------

void printColor(int color){

    switch(color){
        case 0:
            printf("Color: RED");
            break;
        case 1:
            printf("Color: BLUE");
            break;
        case 2:
            printf("Color: YELLOW");
            break;
        case 3:
            printf("Color: BLACK");
            break;
        case 4:
            printf("Color: WHITE");
            break;
        case 5:
            printf("Color: GREY");
            break;
        case 6:
            printf("Color: GREEN");
            break;
        default:
            printf("Color: MIX");
    }
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

            for(j=0; j<vertexes; j++){
                fscanf(file, "%d", &graphMatrix[i][j]);
                degreeTable[i] += graphMatrix[i][j];

                incidentColors[i][j] = -1; // fill with -1
            }
        }

        fclose(file);
        printGraph(graphMatrix);
        return 1;
    }
}

// ------------------------------------------------

int findCandidate(){

    int i;
    int max = 0;
    int incident = -1;
    int candidate;

    for(i=0; i<vertexes; i++){
        if(degreeTable[i] > max && incidentColors[i][i] == -1){  // check if without color and max degree
            max = degreeTable[i];
            if(incidentTable[i] > incident){
                candidate = i;
            }
        }
    }

    return candidate;
}

// ------------------------------------------------

int findColor(int node){
    
    int i;
    int colors[MAX] = {0};

    for(i=0; i<vertexes; i++){

        if(graphMatrix[node][i] && incidentColors[node][i] > -1){
            colors[incidentColors[node][i]] = 1;
        }
    }

    for(i=0; i<vertexes; i++){
        if(colors[i] == 0){
            return i;
        }
    }

    return 0;
}

// ------------------------------------------------

void SLF(){

    int colored = 0;
    int color = 0;
    int candidate = 0;
    int i,j;

    while(colored != vertexes){

        printf("\n----------------------\n");

        candidate = findCandidate();
        printf("Node: %d \n", candidate);

        color = findColor(candidate);
        printColor(color);

        for(i=0; i<vertexes; i++){  // mark incident 
            if(graphMatrix[candidate][i]){
                incidentColors[i][candidate] = color;
                incidentTable[i]++;
            }
        }

        incidentColors[candidate][candidate] = color; // color node

        colored ++;
    }
}

// ------------------------------------------------

int main(){

    loadFile(graphMatrix);
    SLF();
    printf("\n");
    return 0;

}
