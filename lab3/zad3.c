#include <stdio.h>
#include <stdlib.h>
#define MAX 10

int wallsNum = 0;
int vertexesNum = 0;
int halfedgesNum = 0;

// ----------------------- STRUCTURES -----------------------

typedef struct HalfEdge{
  int halfEdgeID[2];
}HalfEdge;

typedef struct Wall {
  int wallID;
}Wall;

typedef struct Vertex{
  int coordinates[2];
  int vertexID;
}Vertex;

typedef struct VertexInfo{
  Vertex *infoOf;
  HalfEdge *incEdge;
}VertexInfo;

typedef struct WallInfo{
  int inCounter;
  Wall *infoOf;
  HalfEdge *out;
  HalfEdge *in[MAX-1];
}WallInfo;

typedef struct HalfEdgeInfo{
  HalfEdge *infoOf;
  Vertex *start;
  HalfEdge *twinEdge;
  Wall *incWall;
  HalfEdge *next;
  HalfEdge *past;
}HalfEdgeInfo;

Vertex *Vertexes[MAX/2];
Wall *Walls[MAX/2];
HalfEdge *HalfEdges[MAX];
VertexInfo *VertexesInfo[MAX/2];
WallInfo *WallsInfo[MAX/2];
HalfEdgeInfo *HalfEdgesInfo[MAX];

// ----------------------- FUNCTIONS -----------------------

Vertex * addVertex(int coordinate1, int coordinate2, int ID){

  Vertex *tmp; 
  tmp = (Vertex*)malloc(sizeof(Vertex));
  tmp -> coordinates[0] = coordinate1;
  tmp -> coordinates[1] = coordinate2;
  tmp -> vertexID = ID;

  vertexesNum ++;

  return tmp;

}

Wall * addWall(int ID){

  Wall *tmp; 
  tmp = (Wall*)malloc(sizeof(Wall));
  tmp -> wallID = ID;

  wallsNum ++;

  return tmp;

}

HalfEdge * addHalfEdge(int ID1, int ID2){

  HalfEdge *tmp; 
  tmp = (HalfEdge*)malloc(sizeof(HalfEdge));
  tmp -> halfEdgeID[0] = ID1;
  tmp -> halfEdgeID[1] = ID2;

  halfedgesNum ++;

  return tmp;

}

VertexInfo * addVertexInfo(Vertex * newVertex, HalfEdge * newHalfEdge){
  VertexInfo *tmp;
  size_t size = sizeof(Vertex) + sizeof(HalfEdge);
  tmp = (VertexInfo*)malloc(size);
  tmp -> infoOf = newVertex;
  tmp -> incEdge = newHalfEdge;

  return tmp;
}

HalfEdgeInfo * addHalfEdgeInfo(HalfEdge * halfe,Vertex * newVertex, HalfEdge * newEdge1,Wall * newWall,HalfEdge * newEdge2,HalfEdge * newEdge3){
  
  HalfEdgeInfo *tmp;
  size_t size = sizeof(Vertex) + (sizeof(HalfEdge)*4) + sizeof(Wall);
  tmp = (HalfEdgeInfo*)malloc(size);
  tmp -> infoOf = halfe;
  tmp -> start = newVertex;
  tmp -> twinEdge = newEdge1;
  tmp -> incWall = newWall;
  tmp -> next = newEdge2;
  tmp -> past = newEdge3;

  return tmp;
}

WallInfo * addWallInfo(Wall * newWall, HalfEdge **newEdge, int counter){
  
  int i;

  WallInfo *tmp;
  size_t size = (sizeof(HalfEdge)*MAX) + sizeof(Wall) + sizeof(int);
  tmp = (WallInfo*)malloc(size);
  tmp -> infoOf = newWall;
  tmp -> out = newEdge[0];

  printf("Counter in WallInfo: %d \n", counter);

  for(i=0; i<counter; i++){
    tmp -> in[i] = newEdge[i+1];
  }

  tmp -> inCounter = counter;

  return tmp;
}

void makePlanarGraph(){

    FILE *file;
    file=fopen("dane1b.txt", "r");
    char c;
    int i;

    int ID1,ID2;
    int howMuch;
    int component;
    HalfEdge *newEdge[MAX];
    Vertex *newVertex;
    Wall *newWall;// type of 'składowa' in Wall

    int j = -1; // Wall entry couter

    while((c = fgetc(file)) != EOF){

      if(c == 'v'){

        fscanf (file, "%d", &howMuch);

        for(i=0; i<howMuch; i++){
          fscanf (file, "%d", &ID1);
          fscanf (file, "%d", &ID2);

          VertexesInfo[i] = addVertexInfo(Vertexes[i], HalfEdges[((ID1 - 1)*2)+(ID2 - 1)]); 
          // np. dla (4,2) | ((4-1)*2)+(2-1) = 7

          fgetc(file);
        }
      }
      else if(c == 'h'){
        fscanf (file, "%d", &howMuch);

        for(i=0; i<howMuch; i++){
          fscanf (file, "%d", &ID1);

          newVertex = addVertex(Vertexes[ID1 - 1] -> coordinates[0], Vertexes[ID1 - 1] -> coordinates[1], Vertexes[ID1 - 1] -> vertexID);
          vertexesNum --;

          fscanf (file, "%d", &ID1);
          fscanf (file, "%d", &ID2);

          newEdge[0] = addHalfEdge(HalfEdges[((ID1 - 1)*2)+(ID2 - 1)] -> halfEdgeID[0], HalfEdges[((ID1 - 1)*2)+(ID2 - 1)] -> halfEdgeID[1]);
          halfedgesNum --;

          fscanf (file, "%d", &ID1);

          newWall = addWall(Walls[ID1-1] -> wallID);
          wallsNum --;

          fscanf (file, "%d", &ID1);
          fscanf (file, "%d", &ID2);

          newEdge[1] = addHalfEdge(HalfEdges[((ID1 - 1)*2)+(ID2 - 1)] -> halfEdgeID[0], HalfEdges[((ID1 - 1)*2)+(ID2 - 1)] -> halfEdgeID[1]);
          halfedgesNum --;

          fscanf (file, "%d", &ID1);
          fscanf (file, "%d", &ID2);

          newEdge[2] = addHalfEdge(HalfEdges[((ID1 - 1)*2)+(ID2 - 1)] -> halfEdgeID[0], HalfEdges[((ID1 - 1)*2)+(ID2 - 1)] -> halfEdgeID[1]);
          halfedgesNum --;

          HalfEdgesInfo[i] = addHalfEdgeInfo(HalfEdges[i], newVertex, newEdge[0], newWall, newEdge[1], newEdge[2]);

          fgetc(file);
        }
      }
      else if(c == 'w'){
        fscanf (file, "%d", &howMuch);
        j++;

        printf("How much: %d j:%d\n",howMuch, j);

        fscanf (file, "%d", &ID1);
        if(ID1 == 0){
          newEdge[0] = addHalfEdge(0,0);
          halfedgesNum --;
        }
        else{
          fscanf (file, "%d", &ID2);
          printf("ID1: %d, ID2: %d, \n", ID1, ID2);
          newEdge[0] = addHalfEdge(HalfEdges[((ID1 - 1)*2)+(ID2 - 1)] -> halfEdgeID[0], HalfEdges[((ID1 - 1)*2)+(ID2 - 1)] -> halfEdgeID[1]);
          halfedgesNum --;
        }

        for(i=0; i<howMuch-1; i++){

          printf("i: %d \n" , i);

          fscanf (file, "%d", &ID1);
          if(ID1 == 0){
            newEdge[i+1] = addHalfEdge(0,0);
            halfedgesNum --;
          }
          else{
            fscanf (file, "%d", &ID2);

            printf("ID1: %d, ID2: %d, \n", ID1, ID2);
            newEdge[i+1] = addHalfEdge(HalfEdges[((ID1 - 1)*2)+(ID2 - 1)] -> halfEdgeID[0], HalfEdges[((ID1 - 1)*2)+(ID2 - 1)] -> halfEdgeID[1]);
            halfedgesNum --;
          }
        }

        WallsInfo[j] = addWallInfo(Walls[j], newEdge, howMuch-1);
      }
    }

    fclose(file);
}

void loadFile(){

  FILE *file;

  file=fopen("dane1a.txt", "r");

  char c;
  int ID1,ID2,cord1,cord2;
  int howMuch;
  int i;

  while((c = fgetc(file)) != EOF){
    if(c == 'v'){
      fscanf (file, "%d", &howMuch);

      for(i=0; i<howMuch; i++){
        fscanf (file, "%d", &cord1);
        fscanf (file, "%d", &cord2);
        fscanf (file, "%d", &ID1);

        Vertexes[vertexesNum] = addVertex(cord1,cord2,ID1);
        fgetc(file);
      }
    }
    else if(c == 'h'){
      fscanf (file, "%d", &howMuch);

      for(i=0; i<howMuch; i++){
        fscanf (file, "%d", &ID1);
        fscanf (file, "%d", &ID2);

        HalfEdges[halfedgesNum] = addHalfEdge(ID1,ID2);
        fgetc(file);
      }
    }
    else if(c == 'w'){
      fscanf (file, "%d", &howMuch);

      for(i=0; i<howMuch; i++){
        fscanf (file, "%d", &ID1);

        Walls[wallsNum] = addWall(ID1);
        fgetc(file);
      }
    }
  }

  fclose(file);

  makePlanarGraph();
}

void checkData(){

  int i,j,counter;

  for(i=0; i<vertexesNum; i++){
    printf("\n Vertex %d) \n", i+1);
    printf("--------------\n");
    printf(" COORDINATES: (%d,%d) \n", VertexesInfo[i] -> infoOf -> coordinates[0], VertexesInfo[i] -> infoOf -> coordinates[1]);
    printf(" ID: %d \n", VertexesInfo[i] -> infoOf -> vertexID);
    printf(" INCIDENTAL EDGE: e (%d,%d) \n", VertexesInfo[i] -> incEdge -> halfEdgeID[0],VertexesInfo[i] -> incEdge -> halfEdgeID[1]);
    printf("--------------\n");
  }

  for(i=0; i<halfedgesNum; i++){
    printf("\n Half Edge %d) \n", i+1);
    printf("--------------\n");
    printf(" ID: e(%d,%d) \n", HalfEdgesInfo[i] -> infoOf -> halfEdgeID[0], HalfEdgesInfo[i] -> infoOf -> halfEdgeID[1]);
    printf(" START: v%d \n", HalfEdgesInfo[i] -> start -> vertexID);
    printf(" TWIN EDGE: e(%d,%d) \n", HalfEdgesInfo[i] -> twinEdge -> halfEdgeID[0], HalfEdgesInfo[i] -> twinEdge -> halfEdgeID[1]);
    printf(" INCIDENTAL WALL: f%d \n", HalfEdgesInfo[i] -> incWall -> wallID);
    printf(" NEXT: e(%d,%d) \n", HalfEdgesInfo[i] -> next -> halfEdgeID[0], HalfEdgesInfo[i] -> next -> halfEdgeID[1]);
    printf(" PAST: e(%d,%d) \n", HalfEdgesInfo[i] -> past -> halfEdgeID[0], HalfEdgesInfo[i] -> past -> halfEdgeID[1]);
    printf("--------------\n");
  }

  for(i=0; i<wallsNum; i++){
    printf("\n Wall %d) \n", i+1);
    printf("--------------\n");
    printf(" ID: %d \n", WallsInfo[i] -> infoOf -> wallID);
    printf(" OUT: e(%d,%d) \n", WallsInfo[i] -> out -> halfEdgeID[0], WallsInfo[i] -> out -> halfEdgeID[1]);
    printf(" IN COUNTER: %d \n", WallsInfo[i] -> inCounter);
    printf(" IN LIST: \n");

    counter = WallsInfo[i] -> inCounter;

    for(j=0; j<counter; j++){
      printf(" %d: e(%d,%d) \n",j , WallsInfo[i] -> in[j] -> halfEdgeID[0], WallsInfo[i] -> in[j] -> halfEdgeID[1]);
    }

    printf("--------------\n");
  }

}

void checkVertex(){

  int i, ID1, ID2;
  int counter = 0;
  int vertex = 100;
  HalfEdge *searchEdge[MAX];

  while(vertex < 0 || vertex > MAX){
    printf("Podaj ID wierzcholka: \n");
    scanf("%d",&vertex);
  }

  for(i=0; i<halfedgesNum; i++){
    if(HalfEdgesInfo[i] -> start -> vertexID == vertex){
      searchEdge[counter] = HalfEdgesInfo[i] -> twinEdge;
      counter ++;
    }
  }

  printf("\nSasiednie wierzcholki to: \n");
  for(i=0; i<counter; i++){
    ID1 = searchEdge[i] -> halfEdgeID[0];
    ID2 = searchEdge[i] -> halfEdgeID[1];
    printf("v%d\n", HalfEdgesInfo[((ID1 - 1)*2)+(ID2 - 1)] -> start -> vertexID );
  }
  
}

int main(){

	int fileRead = 0;
  char menu = 'o';
  char fileName[20];

  int i,j,number;

  loadFile();

  while(menu != 'q'){

    printf("\n ------ MENU ------ \n");
    printf("1) Sprawdz dane - t \n");
    printf("2) Wyszukaj sasiednie wierzcholki - w \n");
    printf("2) Zakoncz  -  q \n\n");
    scanf("%s",&menu);

    switch(menu){

      case 't':
        checkData();
        break;

      case 'w':
        checkVertex();
        break;

      case 'q':
        printf("Dziekuje. \n");
        break;
    }
  }

  return 0;
}
