/*
 * Graph Search
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

/* for graph visited */
#define FALSE 0
#define TRUE 1
int visited[MAX_GRAPH_SIZE] ={0};

/* for queue */
int queue[MAX_GRAPH_SIZE] = {0};
int front = -1;
int rear = -1;

int deQueue();
void enQueue(int key);




graphVertex* initializeGraph(graphVertex* h); /* make the head list */

int InsertVertex(graphVertex* head, int key);  /* insert a Vertex to the Graph */
int InsertEdge(graphVertex* head, int key, int otherkey);  /* insert a Edge to the Graph */

int depthFirst(graphVertex* head, int key); /* Depth First Search */
int breathFirst(graphVertex* head, int key); /* Breath First Search */

void printGraph(graphVertex* head); /* print Graph */

void removeGraph(graphVertex* head); /* remove Graph */




int main()
{
	printf("[----- [오주형] [2019023028] -----]");
	char command;
	int key;
	int onekey;
	int otherkey;
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
			head = initializeGraph(head);
			break;
		case 'q': case 'Q':
			removeGraph(head);
			break;
		case 'v': case 'V':
			printf("Insert Your vertex(0~9) = ");
			scanf("%d", &key);
			InsertVertex(head, key);
			break;
		case 'e': case 'E':
			printf("What vertex do you want link(choose two vertex) = ");
			scanf("%d %d", &onekey, &otherkey);
			InsertEdge(head, onekey, otherkey);
			break;
		case 'd': case 'D':
			for (int i = 0; i < MAX_GRAPH_SIZE; i++) //배열 초기화
			{
				visited[i] = FALSE;
			}
			int dfsroot;
			printf("what number do you want to set as the root node in DFS : ");
			scanf("%d", &dfsroot);
			depthFirst(head, dfsroot);
			break;
		case 'b': case 'B':
			for (int i = 0; i < MAX_GRAPH_SIZE; i++) //배열 초기화
			{
				visited[i] = FALSE;
			}
			int bfsroot;
			printf("what number do you want to set as the root node in BFS : ");
			scanf("%d", &bfsroot);
			breathFirst(head, bfsroot);
			break;
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

graphVertex* initializeGraph(graphVertex* h) {

	if(h != NULL)
	{
		removeGraph(h);
	}
	h = (graphVertex*)malloc(sizeof(graphVertex) * MAX_GRAPH_SIZE);
	for (int i = 0; i < MAX_GRAPH_SIZE; i++)
	{
		h[i].key = -9999; // -9999는 값이 없음을 의미
		h[i].link = NULL;
	}
	
	return h;
}

// 이 함수는 메뉴에서 z를 눌렀을 때 실행되는 함수입니다. 그래프 헤드 배열을 생성합니다.
// 헤드 배열이 NULL이 아니라면 헤드를 먼저 초기화합니다. 그리고 10개의 graphVertex형 배열을 동적할당 받습니다.
// 다음으로 각각의 key에 -9999로 초기화하고 link는 NULL로 초가화합니다.
// 마지막으로 h를 리턴하여 동적할당 한 배열을 반환합니다.



int InsertVertex(graphVertex* h, int key) // 배열의 key에 넣으면 됨
{
	if(h[key].key != -9999) // -9999가 아니면 이미 vertex가 들어간
	{
		printf("이미 존재하는 vertex입니다.");
		return 1;
	}

	h[key].key = key;
	return 1;
}

// 이 함수는 메뉴에서 v를 누르면 실행하는 함수입니다. vertex 1개를 삽입합니다.
// 처음에 헤드 배열의 key들을 -9999로 초기화 했기 때문에 h[key].key값이 -9999인 경우에만 vertex를 삽입합니다.
// h[key].key이 -9999가 아니라면 해당 vertex가 이미 존재한다는 메시지를 출력합니다.
// 참고로 vertex 1개를 삽입은 h[key].key = key를 이용하면 됩니다.

int InsertEdge(graphVertex* head, int onekey, int otherkey)
{
	// 그래프에 내가 적은 노드가 없는 경우
	if(head[onekey].key == -9999 || head[otherkey].key == -9999)
	{
		printf("the vertex that you wrote not exist in Graph.\n");
		return 1;
	}
	// 이미 에지가 있는 경우 (양방향 연결이라 한쪽만 검사 해주면 됨)
	graphVertex* check = head[onekey].link;
	while(check != NULL)
	{
		if(check->key == otherkey)
		{
			printf("The edges are already linked\n");
			return 1;
		}
		check = check->link;
	}

	// 위 오류가 없는 경우 처음 연결할 에지 생성
	graphVertex* first = (graphVertex*)malloc(sizeof(graphVertex));
	first->key = onekey;
	first->link = NULL;
	// 두 번째 연결할 에지 생성
	graphVertex* second = (graphVertex*)malloc(sizeof(graphVertex));
	second->key = otherkey;
	second->link = NULL;

	graphVertex* follow = head[onekey].link;
	graphVertex* prev =  &head[onekey];

	// 아무것도 링크 안 되어 있는 곳에 넣기
	if (head[onekey].link == NULL)
	{
		head[onekey].link = second;
	}
	else
	{
		// 처음 에지 연결
		while (follow != NULL)
		{
			if(follow->key > otherkey)
			{
				second->link = follow;
				break;
			}
			prev = follow;
			follow = follow->link;
		}
		prev->link = second;
	}	

	if (head[otherkey].link == NULL)
	{
		head[otherkey].link = first;
	}

	else
	{
		// 두 번째 에지 연결
		follow = head[otherkey].link;
		prev = &head[otherkey];
		while (follow != NULL)
		{
			if(follow->key > onekey)
			{
				first->link = follow;
				break;
			}
			prev = follow;
			follow = follow->link;
		}
		prev->link = first;
	}

	return 1;	
}
// 이 함수는 메뉴 e를 눌렀을 때 실행되는 함수입니다. vertex들 간의 edge를 생성합니다.
// 먼저 head[onekey].key == -9999 이거나 head[otherkey].key == -9999인 경우 해당 vertex가 없는 것입니다.
// 그래서 내가 입력한 vertex가 그래프에 존재하지 않는다는 메시지를 출력합니다.
// 또 head[onekey].link의 key가 onekey와 같다면 해당 edge가 이미 존재한다는 뜻입니다.
// 그래서 이미 해당 edge가 존재한다는 메시지를 출력합니다.
// 다음으로 onekey와 otherkey를 갖는 vertex fisrt, second를 동적할당 받습니다.
// 이때 첫 헤드 배열이 비어있으면 바로 그 헤드 배열의 link와 이어줍니다.
// 그렇지 않다면 정렬해서 삽입해야합니다. 정렬하기 위해서는 follow와 prev를 이용합니다.
// follow가 onekey혹은 otherkey보다 커진 순간이 온다면 그 앞에 first혹은 second를 넣어주고 반복문을 탈출합니다.
// 그 후 follow를 따라오던 prev의 link에 first혹은 second를 넣어주면 완성됩니다.


void printGraph(graphVertex* head)
{	
	for (int i = 0; i < MAX_GRAPH_SIZE; i++)
	{
		if(head[i].key == i)
		{
			printf("\n [%d] :", head[i].key);
			graphVertex* follow = head[i].link;
			while(follow != NULL)
			{
				printf(" -> [%d]", follow->key);
				follow = follow->link;
			}
		}
	}
}

// 이 함수는 메뉴에서 p를 눌렀을 때 실행되는 함수입니다. 인접리스트로 만든 그래프의 상태를 출력합니다.
// for문을 통해 vertex가 생성된 헤드 배열을 출력합니다.
// 그 안에서 반복문을 통해 각각의 헤드배열에 연결된 리스트의 key값을 출력합니다.



int depthFirst(graphVertex* head, int key)
{
	if(head == NULL)
	{
		printf("No vertex to do DFS\n");
		return 1;
	}
	if(head[key].link == NULL)
	{
		printf("The vertex that you choose is not exist in graph\n");
		return 1;
	}

	graphVertex* p = &head[key];
	printf(" [%d] ", p->key);
	visited[p->key] = TRUE;
	while(p != NULL)
	{
		if(visited[p->key] == FALSE)
		{
			depthFirst(head, p->key);
		}
		p = p->link;
	}
	return 1;
}

// 이 함수는 메뉴에서 d를 눌렀을 때 실행되는 함수입니다. 입력받은 vertex를 기준으로 깊이 우선 탐색을 진행합니다.
// DFS를 할 vertex가 없다면 해당 메시지를 출력하도록 했습니다.
// 이를 시행하기 위해서는 방문을 확인할 visited 배열을 만들어서 방문했는지 여부를 체크합니다.
// vertex들을 돌면서 확인할 p를 선언하여 p가 NULL이 아닌동안 p는 p->link로 이동하고 visited배열에서 해당 인덱스가 FALSEE인지 체크합니다.
// 그리고 FALSE라면 다시 depthFirst 사용하여 재귀함수를 구현합니다.


int breathFirst(graphVertex* head, int key)
{
	if(head == NULL)
	{
		printf("No vertex to do BFS\n");
		return 1;
	}
	if(head[key].link == NULL)
	{
		printf("The vertex that you choose is not exist in graph\n");
		return 1;

	}
	printf(" [%d] ",key); 
	visited[key] = TRUE;
	enQueue(key); // 입력받은 key는 무조건 큐에 들어간 상태로 시작해야함
	int parent;
	
	graphVertex* follow = &head[key];
	while(front != rear) // 스택이 다 사라지면 끝내
	{
		parent = deQueue();
		follow = head[parent].link;
		while(follow != NULL)
		{
			if(visited[follow->key] == 0)
			{
				printf(" [%d] ",follow->key);
				visited[follow->key] = 1;
				enQueue(follow->key);
			}
			follow = follow->link;
		}
	}

}

// 이 험수는 메뉴에서 b를 눌렀을 때 실행되는 함수입니다. 넓이 우선 탐색을 진행합니다.
// BFS를 할 vertex가 없다면 해당 메시지를 출력하도록 했습니다.
// DFS방식과 똑같이 이 함수도 방문 여부를 확인할 visited배열이 필요합니다.
// 헤드배열을 순환할 follow를 선언하고 followr가 NULL이될 때 까지 follow가 지나가는 곳을 방문처리 후 출력하고 큐에 넣습니다.
// 단 방문하지 않은 노드에만 이 코드가 실행되게 합니다. 이때 follow의 값은 deQueue를 통해 받은 값에 해당하는 헤드 배열의 key값입니다.
// 이 follow의 값을 스택이 모두 사라질 때까지 계속 바꾸어줍니다.


int deQueue()
{
	if (front == rear) {
		// printf("\n....Now Queue is empty!!\n" );
		return 0;
	}
	front = (front + 1) % MAX_GRAPH_SIZE;
	return queue[front];
}

// 이 함수는 BFS방식을 사용할 때 스택에서 해당 vertex값을 제거할 때 사용합니다.
// deQueue에서 front == rear면 큐가 빈 것이므로 제거할 것이 없습니다. 그래서 해당 메시지를 출력하고 함수를 종료합니다.
// 그렇지 않다면 front = (front + 1) % MAX_GRAPH_SIZE의 모듈러 연산을 사용하여 front의 값을 조정합니다.
// 그리고 조정된 front를 이용하여 queue[front]를 반환합니다.

void enQueue(int key)
{
	rear = (rear + 1) % MAX_GRAPH_SIZE;
	if (front == rear) {
		// printf("\n....Now Queue is full!!\n");
		return;
	}
	queue[rear] = key;
}
// 이 함수는 BFS방식을 사용할 때 스택에 해당 vertex값을 삽입할 때 사용합니다.
// enQueue에서 front == rear면 큐가 다 찬 것이므로 채울 공간이 없습니다. 그래서 해당 메시지를 출력하고 함수를 종료합니다.
// 그렇지 않다면 rear = (rear + 1) % MAX_GRAPH_SIZE의 모듈러 연산을 사용하여 rear의 값을 조정합니다.
// 그리고 조정된 rear를 이용하여 queue[rear]에 key값을 넣습니다.

void removeGraph(graphVertex* head)
{
	graphVertex* follow = NULL;
	graphVertex* prev = NULL;

	for (int i =0; i <MAX_GRAPH_SIZE; i++)
	{
		follow = head[i].link;
		while(follow != NULL)
		{
			prev = follow;
			follow = follow->link;
			free(prev);
		}
	}
	free(head);
}

// 이 함수는 q를 눌렀을 때 실행되는 함수입니다. graph에 할당된 메모리들을 모두 해제합니다.
// 순서는 헤드 배열에 연결되어있는 edge들을 반복문을 통해 접근하여 모두 해제합니다.
// 그리고 마지막으로 head를 해제하면 전부 메모리가 해제됩니다.