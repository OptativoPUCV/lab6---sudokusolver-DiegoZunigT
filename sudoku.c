#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n)
{
   int auxi = 0;
   int auxj = 0;
   while(auxi < 9 && auxj < 9) {
      if(n->sudo[auxi][auxj] == 0) {
         auxj++;
         if(!(auxj % 9)) {
            auxj = 0;
            auxi++;
         }
         continue;
      }
      for(int i = 0; i < 9; i++) {
         if(i != auxi && n->sudo[i][auxj] == n->sudo[auxi][auxj]) {
            return 0;
         }
      }
      for(int j = 0; j < 9; j++) {
         if(j != auxj && n->sudo[auxi][j] == n->sudo[auxi][auxj]) {
            return 0;
         }
      }
      for(int i = (auxi / 3) * 3; i < ((auxi / 3) * 3) + 3; i++) {
         for(int j = (auxj / 3) * 3; j < ((auxj / 3) * 3) + 3; j++) {
            if((i != auxi || j != auxj) && n->sudo[i][j] == n->sudo[auxi][auxj]) {
               return 0;
            }
         }
      }
      auxj++;
      if(!(auxj % 9)) {
         auxj = 0;
         auxi++;
      }
    }
    return 1;
}


List* get_adj_nodes(Node* n)
{
   List* list=createList();
   for(int i = 0; i < 9; i++) {
      for(int j = 0; j < 9; j++) {
         if(n->sudo[i][j] == 0) {
            for(int aux = 1; aux < 10; aux++) {
               Node *newNode = copy(n);
               newNode->sudo[i][j] = aux;
               if(is_valid(newNode) == 1) {
                  pushBack(list, newNode);
               }
            }
            return list;
         }
      }
   }
   return list;
}


int is_final(Node* n)
{
   for(int i = 0; i < 9; i++) {
      for(int j = 0; j < 9; j++) {
         if(n->sudo[i][j] == 0) return 0;
      }
   }
   return 1;
}

Node* DFS(Node* initial, int* cont)
{
   Stack *s = createStack();
   push(s, initial);
   while(top(s)) {
      Node *n = top(s);
      pop(s);
      if(is_final(n)) {
         return n;
      }
      List *adjNodes = get_adj_nodes(n);
      while(!is_empty(adjNodes)) {
         Node *aux = front(adjNodes);
         popFront(adjNodes);
         push(s, aux);
      }
   }
   return NULL;
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/