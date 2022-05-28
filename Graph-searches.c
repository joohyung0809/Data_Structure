/*
 * Graph Searches
 *
 * Data Structures
 *
 * School of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct vertex {
	int key;
	struct vertex* link;
} graphVertex;

typedef struct edge {
	int key;
	struct edge* link;
} graphEdge;

/*for Graph head*/
#define MAX_GRAPH_SIZE 10
graphVertex* array[MAX_GRAPH_SIZE];


int initializeGraph(); /* make the head list */

int InsertVertex(int key);  /* insert a Vertex to the Graph */
int InsertEdge(int key);  /* insert a Edge to the Graph */

int depthFirst(); /* Depth First Search */
int breathFirst(); /* Breath First Search */

void printGraph(); /* print Graph */
int freeGraph(Node* head); /* free all memories allocated to the graph */

// void freeNode(Node* ptr);


int main()
{
	printf("[----- [¿ÀÁÖÇü] [2019023028] -----]");
	char command;
	int key;
	int nodenum;
	Node* head = NULL;
	Node* ptr = NULL;

	do {
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Graph Searches                               \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize Graph     = z                                       \n");
		printf(" Insert Vertex        = v      Insert Edge                  = e \n");
		printf(" Depth First Search   = d      Breath First Search          = b \n");
		printf(" Print Graph          = p      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command) {
		case 'z': case 'Z':
			initializeGraph();
			break;
		case 'q': case 'Q':
			freeGraph(head);
			break;
		case 'v': case 'V':
			printf("Your vertex = ");
			scanf("%d", &key);
			InsertVertex(head, key);
			break;
		case 'e': case 'E':
			printf("What vertex do you want link = ");
			scanf("%d", &key);
			break;
		case 'd': case 'D':
			depthFirst();
			break;
		case 'b': case 'B':
			breathFirst();
			break;
		case 'p': case 'P':
			printGraph();
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	return 1;
}

