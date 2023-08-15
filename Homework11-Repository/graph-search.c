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
	printf("[----- [������] [2019023028] -----]");
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
			for (int i = 0; i < MAX_GRAPH_SIZE; i++) //�迭 �ʱ�ȭ
			{
				visited[i] = FALSE;
			}
			int dfsroot;
			printf("what number do you want to set as the root node in DFS : ");
			scanf("%d", &dfsroot);
			depthFirst(head, dfsroot);
			break;
		case 'b': case 'B':
			for (int i = 0; i < MAX_GRAPH_SIZE; i++) //�迭 �ʱ�ȭ
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
		h[i].key = -9999; // -9999�� ���� ������ �ǹ�
		h[i].link = NULL;
	}
	
	return h;
}

// �� �Լ��� �޴����� z�� ������ �� ����Ǵ� �Լ��Դϴ�. �׷��� ��� �迭�� �����մϴ�.
// ��� �迭�� NULL�� �ƴ϶�� ��带 ���� �ʱ�ȭ�մϴ�. �׸��� 10���� graphVertex�� �迭�� �����Ҵ� �޽��ϴ�.
// �������� ������ key�� -9999�� �ʱ�ȭ�ϰ� link�� NULL�� �ʰ�ȭ�մϴ�.
// ���������� h�� �����Ͽ� �����Ҵ� �� �迭�� ��ȯ�մϴ�.



int InsertVertex(graphVertex* h, int key) // �迭�� key�� ������ ��
{
	if(h[key].key != -9999) // -9999�� �ƴϸ� �̹� vertex�� ��
	{
		printf("�̹� �����ϴ� vertex�Դϴ�.");
		return 1;
	}

	h[key].key = key;
	return 1;
}

// �� �Լ��� �޴����� v�� ������ �����ϴ� �Լ��Դϴ�. vertex 1���� �����մϴ�.
// ó���� ��� �迭�� key���� -9999�� �ʱ�ȭ �߱� ������ h[key].key���� -9999�� ��쿡�� vertex�� �����մϴ�.
// h[key].key�� -9999�� �ƴ϶�� �ش� vertex�� �̹� �����Ѵٴ� �޽����� ����մϴ�.
// ����� vertex 1���� ������ h[key].key = key�� �̿��ϸ� �˴ϴ�.

int InsertEdge(graphVertex* head, int onekey, int otherkey)
{
	// �׷����� ���� ���� ��尡 ���� ���
	if(head[onekey].key == -9999 || head[otherkey].key == -9999)
	{
		printf("the vertex that you wrote not exist in Graph.\n");
		return 1;
	}
	// �̹� ������ �ִ� ��� (����� �����̶� ���ʸ� �˻� ���ָ� ��)
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

	// �� ������ ���� ��� ó�� ������ ���� ����
	graphVertex* first = (graphVertex*)malloc(sizeof(graphVertex));
	first->key = onekey;
	first->link = NULL;
	// �� ��° ������ ���� ����
	graphVertex* second = (graphVertex*)malloc(sizeof(graphVertex));
	second->key = otherkey;
	second->link = NULL;

	graphVertex* follow = head[onekey].link;
	graphVertex* prev =  &head[onekey];

	// �ƹ��͵� ��ũ �� �Ǿ� �ִ� ���� �ֱ�
	if (head[onekey].link == NULL)
	{
		head[onekey].link = second;
	}
	else
	{
		// ó�� ���� ����
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
		// �� ��° ���� ����
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
// �� �Լ��� �޴� e�� ������ �� ����Ǵ� �Լ��Դϴ�. vertex�� ���� edge�� �����մϴ�.
// ���� head[onekey].key == -9999 �̰ų� head[otherkey].key == -9999�� ��� �ش� vertex�� ���� ���Դϴ�.
// �׷��� ���� �Է��� vertex�� �׷����� �������� �ʴ´ٴ� �޽����� ����մϴ�.
// �� head[onekey].link�� key�� onekey�� ���ٸ� �ش� edge�� �̹� �����Ѵٴ� ���Դϴ�.
// �׷��� �̹� �ش� edge�� �����Ѵٴ� �޽����� ����մϴ�.
// �������� onekey�� otherkey�� ���� vertex fisrt, second�� �����Ҵ� �޽��ϴ�.
// �̶� ù ��� �迭�� ��������� �ٷ� �� ��� �迭�� link�� �̾��ݴϴ�.
// �׷��� �ʴٸ� �����ؼ� �����ؾ��մϴ�. �����ϱ� ���ؼ��� follow�� prev�� �̿��մϴ�.
// follow�� onekeyȤ�� otherkey���� Ŀ�� ������ �´ٸ� �� �տ� firstȤ�� second�� �־��ְ� �ݺ����� Ż���մϴ�.
// �� �� follow�� ������� prev�� link�� firstȤ�� second�� �־��ָ� �ϼ��˴ϴ�.


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

// �� �Լ��� �޴����� p�� ������ �� ����Ǵ� �Լ��Դϴ�. ��������Ʈ�� ���� �׷����� ���¸� ����մϴ�.
// for���� ���� vertex�� ������ ��� �迭�� ����մϴ�.
// �� �ȿ��� �ݺ����� ���� ������ ���迭�� ����� ����Ʈ�� key���� ����մϴ�.



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

// �� �Լ��� �޴����� d�� ������ �� ����Ǵ� �Լ��Դϴ�. �Է¹��� vertex�� �������� ���� �켱 Ž���� �����մϴ�.
// DFS�� �� vertex�� ���ٸ� �ش� �޽����� ����ϵ��� �߽��ϴ�.
// �̸� �����ϱ� ���ؼ��� �湮�� Ȯ���� visited �迭�� ���� �湮�ߴ��� ���θ� üũ�մϴ�.
// vertex���� ���鼭 Ȯ���� p�� �����Ͽ� p�� NULL�� �ƴѵ��� p�� p->link�� �̵��ϰ� visited�迭���� �ش� �ε����� FALSEE���� üũ�մϴ�.
// �׸��� FALSE��� �ٽ� depthFirst ����Ͽ� ����Լ��� �����մϴ�.


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
	enQueue(key); // �Է¹��� key�� ������ ť�� �� ���·� �����ؾ���
	int parent;
	
	graphVertex* follow = &head[key];
	while(front != rear) // ������ �� ������� ����
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

// �� ����� �޴����� b�� ������ �� ����Ǵ� �Լ��Դϴ�. ���� �켱 Ž���� �����մϴ�.
// BFS�� �� vertex�� ���ٸ� �ش� �޽����� ����ϵ��� �߽��ϴ�.
// DFS��İ� �Ȱ��� �� �Լ��� �湮 ���θ� Ȯ���� visited�迭�� �ʿ��մϴ�.
// ���迭�� ��ȯ�� follow�� �����ϰ� followr�� NULL�̵� �� ���� follow�� �������� ���� �湮ó�� �� ����ϰ� ť�� �ֽ��ϴ�.
// �� �湮���� ���� ��忡�� �� �ڵ尡 ����ǰ� �մϴ�. �̶� follow�� ���� deQueue�� ���� ���� ���� �ش��ϴ� ��� �迭�� key���Դϴ�.
// �� follow�� ���� ������ ��� ����� ������ ��� �ٲپ��ݴϴ�.


int deQueue()
{
	if (front == rear) {
		// printf("\n....Now Queue is empty!!\n" );
		return 0;
	}
	front = (front + 1) % MAX_GRAPH_SIZE;
	return queue[front];
}

// �� �Լ��� BFS����� ����� �� ���ÿ��� �ش� vertex���� ������ �� ����մϴ�.
// deQueue���� front == rear�� ť�� �� ���̹Ƿ� ������ ���� �����ϴ�. �׷��� �ش� �޽����� ����ϰ� �Լ��� �����մϴ�.
// �׷��� �ʴٸ� front = (front + 1) % MAX_GRAPH_SIZE�� ��ⷯ ������ ����Ͽ� front�� ���� �����մϴ�.
// �׸��� ������ front�� �̿��Ͽ� queue[front]�� ��ȯ�մϴ�.

void enQueue(int key)
{
	rear = (rear + 1) % MAX_GRAPH_SIZE;
	if (front == rear) {
		// printf("\n....Now Queue is full!!\n");
		return;
	}
	queue[rear] = key;
}
// �� �Լ��� BFS����� ����� �� ���ÿ� �ش� vertex���� ������ �� ����մϴ�.
// enQueue���� front == rear�� ť�� �� �� ���̹Ƿ� ä�� ������ �����ϴ�. �׷��� �ش� �޽����� ����ϰ� �Լ��� �����մϴ�.
// �׷��� �ʴٸ� rear = (rear + 1) % MAX_GRAPH_SIZE�� ��ⷯ ������ ����Ͽ� rear�� ���� �����մϴ�.
// �׸��� ������ rear�� �̿��Ͽ� queue[rear]�� key���� �ֽ��ϴ�.

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

// �� �Լ��� q�� ������ �� ����Ǵ� �Լ��Դϴ�. graph�� �Ҵ�� �޸𸮵��� ��� �����մϴ�.
// ������ ��� �迭�� ����Ǿ��ִ� edge���� �ݺ����� ���� �����Ͽ� ��� �����մϴ�.
// �׸��� ���������� head�� �����ϸ� ���� �޸𸮰� �����˴ϴ�.