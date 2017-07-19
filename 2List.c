#include <stdlib.h>
#include <stdio.h>

typedef struct _listNode{
   int number; 
   struct _listNode* next;
} listNode;

#define MAX_NODE_NUM 100000

static listNode* graph[MAX_NODE_NUM]; 
static long int res; 
static long int arrayRes[MAX_NODE_NUM];
static long int counter = 0;


listNode* insertIntoList (listNode* list, int number){
  	listNode* new = malloc(sizeof(listNode));
  	if(new == NULL){
    	fprintf (stderr, "Allocation failed.\n");
    	exit (EXIT_FAILURE);
  	}
  	new->number = number;
  	new->next = list;
 	return new;
}
void deleteList(listNode* list){
	if(list){ 
		deleteList(list->next); 
	    free(list);
	}
}
void printList(listNode* list){
  	if(list){ 
  		printf("%d ",list->number);
  		printList(list->next); 
  	}
}

void DFS(int i, int visited[], long int priceRoad){
	listNode* neighbour;
	visited[i] = 1;
	for(neighbour = graph[i]; neighbour != NULL; neighbour = neighbour->next){
		if (!visited[neighbour->number]){
			res += priceRoad;
			DFS(neighbour->number, visited, priceRoad);
		}
	}
}

int main(){
	int i;
	int visited[MAX_NODE_NUM];

	int input, in;
	scanf("%d", &input);

	int numCity, numRoad;
	long int priceLib, priceRoad;

	for(in = 0; in < input; in++){
		res = 0;
		scanf("%d%d%li%li", &numCity, &numRoad, &priceLib, &priceRoad);

		for(i = 0; i < numCity; i++){
			visited[i] = 0;
			graph[i] = NULL;
		}

		for(i = 0; i < numRoad; i++){
			int first, second;
			scanf("%d%d", &first, &second);
			graph[first-1] = insertIntoList(graph[first-1], second-1);
			graph[second-1] = insertIntoList(graph[second-1], first-1);
		}

		if(priceLib <= priceRoad){
			res = priceLib*numCity;
			arrayRes[counter] = res;
			counter++;
		}
		else{
			res += priceLib;
			DFS(0, visited, priceRoad);
			for(i = 0; i < numCity; i++){
				if(!visited[i]){
					res += priceLib;
					DFS(i, visited, priceRoad);
				}
			}
			arrayRes[counter] = res;
			counter++;
		}

		for(i = 0; i < numCity; i++)
			deleteList(graph[i]);
	}

	for(i = 0; i < counter; i++)
		printf("%li\n", arrayRes[i]);

    return 0;
}