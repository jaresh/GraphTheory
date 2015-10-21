#include <stdio.h>
#include <ctype.h>
#define MAX 10

int vertexes = 0;
int maxDegree = 0;
int minDegree = MAX;
int tableDegree[MAX] = {0};
int sortDegree[MAX] = {0};
int odd = 0;
int even = 0;

// ------------------------------------------------

void sortArray(int * sortarray, int numbers){

    int i,j,a;

    for(j=0; j<numbers; ++j){
        for(i= j+1; i<numbers; ++i){
            if (sortarray[i] > sortarray[j])
            {
                a =  sortarray[i];
                sortarray[i] = sortarray[j];
                sortarray[j] = a;
            }
        }
    }
}

// ------------------------------------------------

void calculateDegrees(int graphMatrix[][MAX]){

    int i,j;
    int counter = 0;
    even = 0;
    odd = 0;
    minDegree = MAX;
    maxDegree = 0;

    for(j=0; j<vertexes; j++){
        for(i=0; i<vertexes; i++){
            counter = counter + graphMatrix[j][i];
        }
        sortDegree[j] = counter;
        tableDegree[j] = counter;

        if(minDegree > counter)
            minDegree = counter;
        if(maxDegree < counter)
            maxDegree = counter;

        if(counter%2 == 0)
            even ++;
        else
            odd ++;

        counter = 0;
    }

    sortArray(sortDegree, vertexes);
}

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

        calculateDegrees(graphMatrix);
        fclose(file);

        return 1;
    }
}

// ------------------------------------------------

void deleteVertex(int graphMatrix[][MAX]){

    int i,j;
    int ni = 0;
    int nj = 0;
    int number = MAX + 1;

    while(number >= vertexes){
        printf("Podaj wierzcholek do usuniecia: \n");
        scanf("%d",&number);
        if(number > vertexes)
            printf("Nieprawidlowa liczba! \n");
    }

    for( j = 0; j < vertexes-1; j++){

        if(j == number)
            nj++;

        for( i = 0; i < vertexes-1; i++){
            if(i == number)
                ni++;
            graphMatrix[j][i] = graphMatrix[j+nj][i+ni];
        }

       ni = 0;
    }

    vertexes --;
    calculateDegrees(graphMatrix);
}

// ------------------------------------------------

void addVertex(int graphMatrix[][MAX]){

    int i,j;
    int newVertex[vertexes];
    int counterDegree = 0;
    char c, falseChar;

    scanf("%c",&falseChar); // lapanie znaku nowej lini

    for(i=0; i < vertexes; i++){
        printf("Podaj krawedz %d: \n",i+1);
        scanf("%c",&c);
        scanf("%c",&falseChar); // lapanie znaku nowej lini
        newVertex[i] = c - '0';
    }

    for(i=0; i < vertexes; i++){
        printf("%d: %d\n",i,newVertex[i]);
    }

    vertexes ++;

    for( i = 0; i < vertexes-1; i++){
        graphMatrix[vertexes-1][i] = newVertex[i];
    }
    for( j = 0; j < vertexes-1; j++){
        printf("dane: %d \n", newVertex[(vertexes-j)-2]);
        graphMatrix[j][vertexes-1] = newVertex[j];
    }

    graphMatrix[vertexes-1][vertexes-1] = 0; // dodanie 0 jako ze nie moze byc z samym soba

    calculateDegrees(graphMatrix);
}

// ------------------------------------------------

void addDeleteEdge(int graphMatrix[][MAX], int type){

    int one = 0;
    int two = 0;
    int good = 1;

    while(good){
        printf("Podaj pierwszy wierzcholek: \n");
        scanf("%d",&one);
        printf("Podaj drugi wierzcholek: \n");
        scanf("%d",&two);

        if(one == two || two >= vertexes || one >= vertexes){
            good = 1;
            printf("Nieprawidlowe liczby! \n");
        }
        else
            good = 0;
    }

    printf("\n %d  %d \n", graphMatrix[one][two], graphMatrix[two][one]);

    if(type){
        if(graphMatrix[one][two] == 0 && graphMatrix[two][one] == 0){
            graphMatrix[one][two] = 1;
            graphMatrix[two][one] = 1;
            printf("\nDodano ! \n");
        }
        else
            printf("Krawedz juz istnieje! \n");
    }
    else{
        if(graphMatrix[one][two] == 1 && graphMatrix[two][one] == 1){
            graphMatrix[one][two] = 0;
            graphMatrix[two][one] = 0;
            printf("\nUsunieto ! \n");
        }
        else
            printf("Krawedz nie istnieje! \n");
    }

    calculateDegrees(graphMatrix);

}

// ------------------------------------------------

void showVertexDegree(){

    int number = MAX + 1;

    while(number >= vertexes){
        printf("Podaj wierzcholek: \n");
        scanf("%d",&number);
        if(number < vertexes)
            printf("\nStopien wierzcholka wynosi: %d\n",tableDegree[number]);
        else
            printf("Nieprawidlowa liczba! \n");
    }
}


// ------------------------------------------------

void printGraph(int graphMatrix[][MAX]){

    int i,j;

    printf("\n\nGraf:\n");
    printf("\nMaksymalny stopien: %d\n", maxDegree);
    printf("\nMinimalny stopien: %d\n", minDegree);
    printf("\nParzyste stopnie: %d\n", even);
    printf("\nNieparzyste stopnie: %d\n", odd);
    printf("\nCiag stopni: ");

    for(j=0; j < vertexes; j++){
        printf("%d ", sortDegree[j]);
    }

    printf("\n\n");

    for(j=0; j < vertexes; j++){
        for(i=0; i < vertexes; i++){
            printf("%d ",graphMatrix[j][i]);
        }
        printf("\n");
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
        printf("1) Wypisz macierz grafu  -  p \n");
        printf("2) Dodaj wierzcholek  -  a \n");
        printf("3) Usun wirzcholek  -  d \n");
        printf("4) Dodaj krawedz  -  k \n");
        printf("5) Usun krawedz  -  u \n");
        printf("6) Wypisz stopien wierzcholka -  s \n");
        printf("8) Wczytaj dane z pliku -  w \n");
        printf("10) Zakoncz  -  q \n\n");
        scanf("%s",&menu);

        switch(menu){
            case 'p':
                printGraph(graphMatrix);
                break;

            case 'a':
                addVertex(graphMatrix);
                break;

            case 'd':
                deleteVertex(graphMatrix);
                break;

            case 'k':
                addDeleteEdge(graphMatrix, 1);
                break;

            case 'u':
                addDeleteEdge(graphMatrix, 0);
                break;

            case 's':
                showVertexDegree();
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
