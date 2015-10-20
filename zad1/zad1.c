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

void sortArray(int sortDegree[]){

    int i,j,a;

    for(j=0; j<vertexes; ++j){
        for(i= j+1; i<vertexes; ++i){
            if (sortDegree[i] > sortDegree[j])
            {
                a =  sortDegree[i];
                sortDegree[i] = sortDegree[j];
                sortDegree[j] = a;
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

    sortArray(sortDegree);
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

    while(number > vertexes){
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

    while(one == two){
        printf("Podaj pierwszy wierzcholek: \n");
        scanf("%d",&one);
        printf("Podaj drugi wierzcholek: \n");
        scanf("%d",&two);

        if(one == two)
            printf("Nieprawidlowe liczby! \n");
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

    while(number > vertexes){
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

/*void matrixMultiplication(int graphMatrix[][MAX]){

    int tabmatrix[MAX][MAX] = {0};
    int i,j,k;

    for(i=0; i<vertexes; i++){
        for(j=0; j<vertexes; j++)
        {
            tabmatrix[i][j]=0;
            for(k=0; k<vertexes; k++)
               tabmatrix[i][j]=tabmatrix[i][j]+graphMatrix[i][k]*graphMatrix[k][j];

        }
    }

     for(i=0; i<vertexes; i++){
        printf("\n");
        for(j=0; j<vertexes; j++){
            printf("%d ",tabmatrix[i][j]);
        }
    }


}*/

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
            //printf("\n Sprawdzenie: [%d,%d] %d", tablecycle[k], tablecycle[k+1], graphMatrix[tablecycle[k]][tablecycle[k+1]]);
            if(graphMatrix[tablecycle[k]][tablecycle[k+1]])
                return 1;
        }

        counter = -1;
    }
    return 0;
}

// ------------------------------------------------

int checkGraph(){

    int j,i,counter,a;
    int sum = 0;
    int newtable[MAX];
    char c, falseChar;

    scanf("%c",&falseChar); // lapanie znaku nowej lini

    printf("Podaj z ilu liczb sklada sie ciag: \n");
    scanf("%d",&counter);
    scanf("%c",&falseChar);

    for(i=0; i < counter; i++){
        printf("Podaj liczbe %d: \n",i+1);
        scanf("%c",&c);
        scanf("%c",&falseChar); // lapanie znaku nowej lini
        newtable[i] = c - '0';
    }

    for(j=0; j<counter; ++j){
        for(i= j+1; i<counter; ++i){
            if (newtable[i] > newtable[j])
            {
                a =  newtable[i];
                newtable[i] = newtable[j];
                newtable[j] = a;
            }
        }
    }

    for(i=0; i < counter; i++){
        sum = sum + newtable[i];
    }

    if(sum % 2 == 1)
        return 0;
    while(sum > 0){
        for(i=1; i < newtable[0]; i++){
            newtable[i-1] = newtable[i] - 1;
            if(newtable[i-1] < 0)
                return 0;
        }

        counter --;
        sum = 0;

        for(i=0; i < counter; i++){
            sum = sum + newtable[i];
        }

        printf("\n %d", sum);
    }

    if(sum == 0)
        return 1;
    else
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
        printf("1) Wypisz macierz grafu  -  p \n");
        printf("2) Dodaj wierzcholek  -  a \n");
        printf("3) Usun wirzcholek  -  d \n");
        printf("4) Dodaj krawedz  -  k \n");
        printf("5) Usun krawedz  -  u \n");
        printf("6) Wypisz stopien wierzcholka -  s \n");
        printf("7) Znajdz cykl C3 -  c \n");
        printf("8) Wczytaj dane z pliku -  w \n");
        printf("9) Podaj ciag do sprawdzenia (zad 3) -  g \n");
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

            case 'c':
                //matrixMultiplication(graphMatrix);
                number = cycleSearch(graphMatrix);

                if(number)
                    printf("\n Graf posiada cykl C3! \n");
                else
                    printf("\n Graf nie posiada cyklu! \n");
                break;

            case 'w':
                fileRead = loadFile(graphMatrix);
                break;

            case 'g':
                number = checkGraph();
                if(number)
                    printf("\n Ciag jest graficny! \n");
                else
                    printf("\n Ciag nie jest graficzny! \n");
                break;

            case 'q':
                printf("Dziekuje. \n");
                break;
        }
    }

    return 0;

}
