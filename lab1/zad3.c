#include <stdio.h>
#include <ctype.h>
#define MAX 10

int vertexes = 0;

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

int checkGraph(){

    int i,counter,a;
    int sum = 0;
    int newtable[MAX];
    char c, falseChar;

    scanf("%c",&falseChar); // lapanie znaku nowej lini

    printf("Podaj z ilu liczb sklada sie ciag: \n");
    scanf("%d",&counter);
    scanf("%c",&falseChar); // lapanie znaku nowej lini

    for(i=0; i < counter; i++){
        printf("Podaj liczbe %d: \n",i+1);
        scanf("%c",&c);
        scanf("%c",&falseChar); // lapanie znaku nowej lini
        newtable[i] = c - '0';
    }

    sortArray(newtable, counter);

    for(i=0; i < counter; i++){
        sum = sum + newtable[i];
    }

    if(sum % 2 == 1)
        return 0;

    while(newtable[0] > 0){

        a = newtable[0]; // zapisuje od ilu liczb odejmujemy

        for(i=1; i < counter; i++){
            if(i <= a)
                newtable[i-1] = newtable[i] - 1;
            else
                newtable[i-1] = newtable[i];
        }

        counter --;
        sum = 0;

        sortArray(newtable, counter);

        for(i=0; i < counter; i++){
            sum = sum + newtable[i];
        }
    }

    if(sum == 0)
        return 1;
    else
        return 0;
}

// ------------------------------------------------

int main(){

    char menu = 'o';
    int graphMatrix[MAX][MAX];
    int i,j,number;

    while(menu != 'q'){

        printf("\n ------ MENU ------ \n");
        printf("1) Sprawdz czy ciag jest graficzny -  g \n");
        printf("2) Zakoncz  -  q \n\n");
        scanf("%s",&menu);

        switch(menu){

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
