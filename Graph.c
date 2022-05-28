/*
 * Binary Search Tree #1
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

/*for Graph head*/
#define MAX_GRAPH_SIZE 10


int initializeGraph(graphVertex* head); /* make the head list */

int InsertVertex(graphVertex* head, int key);  /* insert a Vertex to the Graph */
int InsertEdge(graphVertex* head, int key, int otherkey);  /* insert a Edge to the Graph */

// int depthFirst(); /* Depth First Search */
// int breathFirst(); /* Breath First Search */

void printGraph(graphVertex* head); /* print Graph */



int main()
{
	printf("[----- [오주형] [2019023028] -----]");
	char command;
	int key;
	graphVertex* head = NULL;

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
			initializeGraph(head);
			break;
		case 'q': case 'Q':
			free(head);
			break;
		case 'v': case 'V':
			printf("Your vertex(0~9) = ");
			scanf("%d", &key);
			InsertVertex(head, key);
			break;
		case 'e': case 'E':
			printf("What vertex do you want link(choose two vertex) = ");
			int otherkey;
			scanf("%d %d", &key, &otherkey);
			InsertEdge(head, key, otherkey);
			break;
		// case 'd': case 'D':
		// 	depthFirst();
		// 	break;
		// case 'b': case 'B':
		// 	breathFirst();
		// 	break;
		case 'p': case 'P':
			printGraph(head);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	return 1;
}

int initializeGraph(graphVertex* h) {

	if(h != NULL)
	{
		free(h);
	}
	graphVertex* head = (graphVertex*)malloc(sizeof(graphVertex) * MAX_GRAPH_SIZE);
	for (int i = 0; i < MAX_GRAPH_SIZE; i++)
	{
		head[i].key = -9999; // -9999는 값이 없음을 의미
		head[i].link = NULL;
	}
	
	return 1;
}



int InsertVertex(graphVertex* head, int key) // 배열의 key에 넣으면 됨
{
	if(head[key].key != -9999) // 입력한 key번째 배열에 연결된 vertex가 있으면 못 집어넣음
	{
		printf("이미 존재하는 vertex입니다.");
		return 1;
	}

	head[key].key = key;
	return 1;
}

int InsertEdge(graphVertex* head, int onekey, int otherkey)
{
	// 그래프에 내가 적은 노드가 없는 경우
	if(head[onekey].key == -9999 || head[otherkey].key == -9999)
	{
		printf("the vertex that you wrote not exist in Graph.\n");
		return 1;
	}
	// 처음 연결할 에지 생성
	graphVertex* first = (graphVertex*)malloc(sizeof(graphVertex));
	first->key = onekey;
	first->link = NULL;
	// 처음 에지 연결
	graphVertex* follow = &head[onekey];
	while(follow->link != NULL)
	{
		follow = follow->link;
	}
	follow->link = first;
	// 두 번째 연결할 에지 생성
	graphVertex* second = (graphVertex*)malloc(sizeof(graphVertex));
	second->key = onekey;
	second->link = NULL;
	// 두 번째 에지 연결
	follow = &head[otherkey];
	while(follow->link == NULL)
	{
		follow = follow->link;
	}
	follow->link = second;

	return 1;
}

void printGraph(graphVertex* head)
{	
	for (int i = 0; i < MAX_GRAPH_SIZE; i++)
	{
		if(head[i].key == i)
		{
			printf("[%d] : ", head[i].key);
			graphVertex* follow = head[i].link;
			while(follow != NULL)
			{
				printf("-> [%d] ", follow->key);
				follow = follow->link;
			}
		}
	}
	

}


