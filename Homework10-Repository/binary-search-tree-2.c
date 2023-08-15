/*
 * Binary Search Tree #2
 *
 * Data Structures
 *
 * Department of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>



typedef struct node {
	int key;
	struct node* left;
	struct node* right;
} Node;

/* for stack */
#define MAX_STACK_SIZE 20
Node* stack[MAX_STACK_SIZE];
int top = -1;

Node* pop();
void push(Node* aNode);

/* for queue */
#define MAX_QUEUE_SIZE 20
Node* queue[MAX_QUEUE_SIZE];
int front = -1;
int rear = -1;

Node* deQueue();
void enQueue(Node* aNode);


int initializeBST(Node** h);

/* functions that you have to implement */
void recursiveInorder(Node* ptr);	  /* recursive inorder traversal */
void iterativeInorder(Node* ptr);     /* iterative inorder traversal */
void levelOrder(Node* ptr);	          /* level order traversal */
int insert(Node* head, int key);      /* insert a node to the tree */
int deleteNode(Node* head, int key);  /* delete the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */




int main()
{
	char command;
	int key;
	Node* head = NULL;
	printf("[----- [오주형] [2019023028] -----]\n");

	do {
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #2                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = i      Delete Node                  = d \n");
		printf(" Recursive Inorder    = r      Iterative Inorder (Stack)    = t \n");
		printf(" Level Order (Queue)  = l      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(head, key);
			break;
		case 'r': case 'R':
			recursiveInorder(head->left);
			break;
		case 't': case 'T':
			iterativeInorder(head->left);
			break;
		case 'l': case 'L':
			levelOrder(head->left);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {

	// 트리가 비어있지 않은 경우
	if (*h != NULL)
		freeBST(*h);

	// 헤드 노드를 만드는 단계
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	// 루트노드가 들어갈 공간
	(*h)->right = *h;
	(*h)->key = -9999;

	top = -1;

	front = rear = -1;

	return 1;
}

// 이 함수는 메뉴에서 z를 눌렀을 때 실행되는 함수입니다. Binary Search Tree를 생성합니다. 
// Node형태의 이중포인터를 함수인자로 받아서 사용합니다
// 그리고 *h !=  NULL인 경우 즉, 트리가 비어있지 않다면 트리에 할당된 모든 노드 메모리를 해제합니다.
// 다음으로 헤드노드를 만드는데 *h를 동적할당 하여 만듭니다.
// 그리고 루트 노드가 들어갈 공간인 (*h)->left를 NULL로 초기화합니다. 
// (*h)->right는 *h로 자신을 가리키게 하고 (*h)->key는 -9999로 임의의 값을 줍니다.
// 마지막으로 스택과 큐를 이용하는 코드이기 때문에 top과 front와 rear를 -1로 초기값을 세팅합니다.



void recursiveInorder(Node* ptr)
{
	if (ptr) {
		recursiveInorder(ptr->left);
		printf(" [%d] ", ptr->key);
		recursiveInorder(ptr->right);
	}
}

// 이 함수는 메뉴 r을 눌렀을 때 실행하는 함수입니다. Inorder방식으로 노드를 순회하는데 recursive방식을 이용합니다.
// ptr에 값이 있는 동안 조건에 있는 재귀함수들을 실행합니다.
// ptr->left로 먼저 recursiveInorder()함수를 사용하고 key를 print한 후 ptr->right로 recursiveInorder()함수를 사용합니다. 


void iterativeInorder(Node* node)
{
	for (;;) // for loop문
	{
		for (; node; node = node->left)
			push(node); // 스택에 삽입
		node = pop(); // 스택에서 제거

		if (!node) break; // 스택이 공백인 경우 (top<0인 겨우 node는 NULL값을 가짐)
		printf(" [%d] ", node->key);

		node = node->right;
	}
}

// 이 함수는 메뉴 t를 눌렀을 때 실행되는 함수입니다. Inorder방식으로 노드를 순회하는데 iterative방식을 이용합니다.
// 이때 iterative방식은 stack에 저장하는 방식으로 순회합니다. 순회하면서 다시 돌아갈 곳의 정보를 기억하기 위해서입니다.
// 함수를 살펴보면 for loop로 구현하고 있습니다. for loop 안에서 node가 존재하면 node를 스택에 삽입합니다.
// 그리고 node를 node->left로 이동시킵니다. 그리고 node가 NULL이라면 for문을 나와 스택에서 삭제합니다. 
// 동시에 현재 위치한 노드의 key값을 출력합니다. 그리고 node를 node의 오른쪽으로 이동시킵니다.
// 이 단계를 무한 반복하다가 node에 값이 없다면 break를 사용하여 무한반복문을 끝냅니다.


void levelOrder(Node* ptr)
{

	if (!ptr) return; // 트리가 비어있는 경우

	enQueue(ptr); 

	for (;;)
	{
		ptr = deQueue(); 
		if (ptr) {
			printf(" [%d] ", ptr->key);

			if (ptr->left)
				enQueue(ptr->left);
			if (ptr->right)
				enQueue(ptr->right);
		}
		else
			break;

	}

}

// 이 함수는 메뉴 l을 눌렀을 때 실행되는 함수입니다. levelOrder순회 즉 레벨 순서대로 순회합니다.
// 이때 레벨 순서 순회는 큐를 사용합니다. 
// 트리가 비어있다면 함수를 종료합니다. 그렇지 않다면 enQueue함수를 사용하여 큐에 현재 노드 위치를 넣습니다.
// 그리고 ptr이 존재할 때까지 무한 루프문이 실행됩니다. 
// 먼저 ptr에 deQueue에서 return한 값을 넣어줍니다. 그래서 ptr이 NULL이면 반복문을 탈출하고 그렇지 않다면 다음 조건문을 실행합니다.
// ptr이 존재하면 현재 ptr의 key값을 출력하고, ptr의 left가 존재하면 ptr의 left를 enQueue()하고 , ptr의 right가 존재하면 ptr의 right를 enQueue()합니다.

int insert(Node* head, int key)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->key = key;
	newNode->left = NULL;
	newNode->right = NULL;

	// 헤드 노드만 있는 경우
	if (head->left == NULL) {
		head->left = newNode;
		return 1;
	}

	Node* n = head->left;
	Node* parentNode = NULL;

	while (n != NULL) {

		// 같은 값은 넣어주지 않음 
		if (n->key == key) return 1;

		// 반복문을 돌며 부모노드가 자식 노드 계속 따라옴
		parentNode = n;

		//key 값을 비교하여 돌고 있는 n의 키값이 입력받은 키 값보다 작으면 오른쪽 그 이외는 왼쪽으로 간다.(NULL값 까지)
		if (n->key < key)
			n = n->right;
		else
			n = n->left;
	}

	// 반복문이 끝나고 부모노드와 비교하여 오른쪽으로 넣을지 왼쪽으로 넣을지 결정
	if (parentNode->key > key)
		parentNode->left = newNode;
	else
		parentNode->right = newNode;
	return 1;
}

// 이 함수는 이진탐색트리의 특성에 맞게 입력한 key값을 알맞은 위치에 놓도록 하는 함수입니다.
// 먼저 newNode변수를 동적할당하여 새로운 노드가 들어갈 공간을 할당합니다.
// 그리고 그 노드의 key에는 입력받은 값을 넣고, 양쪽의 링크는 NULL로 세팅합니다.
// 다음으로 head->left == NULL인 경우 즉, 헤드노드만 있는 경우 루트노드에 새로운 노드가 들어가게 하면 됩니다.
// 그래서 head->left에 newNode를 넣고 함수를 종료시켰습니다.
// 헤드노드만 있는 경우가 아니라면 Node* 형태의 n과 parentNode를 선언하여 각각 head->left와 NULL을 가리키게 했습니다.
// 이때 parentNode는 다음 노드로 이동하는 n의 부모노드를 가리키기 위해 선언했습니다.

// 이제 입력한 값을 찾기 위해 트리를 탐색하기 위해 반복문을 실행하여 parentNode = n을 써줍니다.
// 그리고 다음 값으로 이동하는 n의 key값이 입력받은 키값과 비교하여 작으면 오른쪽, 크면 왼쪽 노드로 이동할 수 있도록 했습니다.
// 이진트리에서 부모노드보다 작으면 왼쪽으로 크면 오른쪽으로 삽입하기 위해서입니다.
// 혹시나 같은 값이 입력되는 것을 방지하기 위해 그러한 경우 함수를 끝내도록 했습니다.
// 마지막으로 반복문이 끝나고 부모노드와 비교하여 오른쪽으로 넣을지 왼쪽으로 넣을지 결정하는 코드를 작성했습니다.
// 앞서 언급했듯이 부모노드의 key값과  비교하여 노드 위치를 결정하기 때문입니다.


// 워드에 이진트리의 특성을 설명하겠습니다. 한 노드는 최대 두 개의 자식노드를 가집니다.
// 왼쪽 서브트리와 오른쪽 서브트리를 구별할 수 있으며, 0개의 노드를 가질 수 있습니다.
// 그래서 이진트리를 공백이거나 루트와 왼쪽 서브트리, 오른쪽 서브트리 두 개의 분리된 이진 트리로 구성 된 노드의 유한 집합으로 정의할 수 있습니다.
// 이 소스코드에서 구현한 것은 이진트리에 부모노드보다 큰 자식노드는 오른쪽, 작으면 왼쪽으로 넣는 조건을 추가한 이진탐색트리를 구현한 것입니다.

int deleteNode(Node* head, int key)
{
	// 지울 노드가 없는 경우
	if (head == NULL) {
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	if (head->left == NULL) {
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	// head->left는 루트 노드임
	Node* root = head->left;

	Node* parent = NULL;
	Node* ptr = root;

	while ((ptr != NULL) && (ptr->key != key)) {
		if (ptr->key != key) {

			parent = ptr;	

			if (ptr->key > key)
				ptr = ptr->left;
			else
				ptr = ptr->right;
		}
	}

	// 반복문을 다 돌았음에도 입력받은 key값과 같은 값이 나오지 않은 경우
	if (ptr == NULL)
	{
		printf("No node for key [%d]\n ", key);
		return -1;
	}

	// 반복문이 끝났을 때 지워야할 노드가 리프노드인 경우
	if (ptr->left == NULL && ptr->right == NULL) // 리프노드는 왼쪽과 오른쪽에 노드가 없음
	{
		if (parent != NULL) { // parent가 존재하면 지워야할 노드가 루트노드가 아니라는 뜻
			if (parent->left == ptr)
				parent->left = NULL;
			else
				parent->right = NULL;
		}
		else {
			// parent == NULL이면 루트 노드를 지워야 한다는 뜻
			head->left = NULL;

		}

		free(ptr);
		return 1;
	}

	// 지워야할 노드의 자식노드가 한 개 있는 경우
	if ((ptr->left == NULL || ptr->right == NULL))
	{
		Node* child;
		if (ptr->left != NULL)
			child = ptr->left;
		else
			child = ptr->right;

		if (parent != NULL)
		{
			if (parent->left == ptr)
				parent->left = child;
			else
				parent->right = child;
		}
		else {
			// 부모노드가 NULL이면서 자식노드가 한 개 있으면 ptr이 루트노드인 것
			root = child; // 자식노드가 루트 노드가 되어야 함
		}

		free(ptr);
		return 1;
	}


	//지워야 할 노드가 두 개 있는 경우

	Node* candidate;
	parent = ptr;


	candidate = ptr->right;

	// ptr기준으로 오른쪽 서브트리의 가장 작은 노드를 선택하기 위해 가장 왼쪽으로 감.
	while (candidate->left != NULL)
	{
		parent = candidate;
		candidate = candidate->left;
	}

	// 밑에서 값을 바꾸면 parent의 오른쪽 혹은 왼쪽이 사라지기에 그 값을 candidate의 오른쪽 값으로 만들었음.
	// left가 NULL일 때까지 왔기에 왼쪽은 NULL값이므로 오른쪽 값을 사용함
	if (parent->right == candidate)
		parent->right = candidate->right;
	else
		parent->left = candidate->right;

	
	// ptr의 key를 candidate의 key값으로 바꿈
	ptr->key = candidate->key;

	free(candidate);
	return 1;
}

// 이 함수는 메뉴 d를 눌렀을 때 실행되는 함수입니다. 입력한 key의 값을 찾아 그 노드를 삭제합니다.
// 함수의 인자는 head노드와 입력한 key값을 사용합니다.
// 먼저 head가 NULL이거나 head의 left가 NULL이면 지울 것이 없으므로 지울 노드가 없다는 메시지를 출력합니다.
// 그라고 Node형태의 root, parent, ptr을 만들어 각각 head->left, NULL, root를 넣어줍니다. 
// 여기서 ptr은 계속 다음 노드로 이동하고 parent는 ptr을 따라다니며 ptr의 부모 노드 역할을 합니다.
// 다음으로 ptr이 NULL이 아니고, ptr->key가 key가 아닌 동안 반복문을 실행합니다.
// ptr->key가 key가 아니라면 parent를 ptr위치로 이동하고 ptr->key와 입력받은 값을 비교합니다.
// 비교 결과 ptr->key가 크면 왼쪽, 그렇지 않다면 오른쪽으로 이동합니다.
// 이동이 끝나고 ptr이 NULL이라면 해당하는 key값을 가진 노드가 없다는 메시지를 출력합니다.
// 그렇지 않다면 3가지 경우로 나누어서 처리합니다.

// 1. 지워야할 노드가 리프노드인 경우
// 그 리프노드가 루트노드가 아닌 경우 ptr이 부모노드의 왼쪽이라면 왼쪽값을 NULL로 바꾸고, 오른쪽이라면 오른쪽값을 NULL로 바꿉니다.
// 루트노드라면 헤드노드의 왼쪽이 루트노드이므로 그 곳을 NULL로 바꿉니다.
// 마지막으로 조건문이 끝나고 ptr이 있던 위치의 메모를 해제하며 함수를 종료합니다.

// 2. 지워야할 노드의 자식노드가 한 개 있는 경우
// 먼저 Node형태의 child를 한 개 만듭니다. 
// 그래서  ptr의 왼쪽에 값이 있으면 child를 왼쪽 값으로 이동시키고, 오른쪽에 값이 있으면 child를 오른쪽 값으로 이동시킵니다.
// child값을 정한 후 ptr이 NULL이 아니면 즉, 루트노드가 아니면 ptr의 자식노드를 ptr자리로 이동시켜 ptr을 삭제합니다.
// ptr이 NULL이면 즉, 루트노드라면 그 자식노드가 루트노드가 되게 합니다.

// 3. 지워야할 노드의 자식노드가 두 개 있는 경우
// 먼저 Node형태의 후보 노드 candidate를 정의합니다. 그리고 ptr의 오른쪽 서브트리의 가장 작은 값을 구하기 위해 NULL값이 나올 때 까지 왼쪽으로 계속 이동합니다.
// 그리고 parent의 right가 candidate면 parent->right = candidate->right를 하고, 그렇지 않다면 parent->left = candidate->right를 합니다.
// 다음으로 ptr의 key를 candidate의 key값으로 바꾸고, candidate의 메모리를 해제하고 함수를 종료합니다.


void freeNode(Node* ptr)
{
	if (ptr) {
		freeNode(ptr->left);
		freeNode(ptr->right);
		free(ptr);
	}
}

// 이 함수는 노드에게 할당되었던 메모리를 하제하는 함수입니다.
// Node*형태의 ptr에 값이 있다면 다시 freeNode함수를 호출하는 재귀함수 형태입니다.
// 트리 모두에 접근하기 위해 재귀함수를 사용했으며 접근하는 ptr에 free()함수를 통해 메모리 할당을 해제했습니다.

int freeBST(Node* head)
{

	if (head->left == NULL)
	{
		free(head);
		return 1;
	}

	Node* p = head->left;

	freeNode(p);

	free(head);
	return 1;
}

// 이 함수는 만들었던 Binary Search Tree를 해제하는 함수입니다.
// 이 함수에서는 처음에 head->left가 NULL이라면 즉, head만 있다면 free()함수를 이용하여 head만 해제하고 함수를 종료합니다.
// 그 외의 경우에는 Node* 형태의 p를 head의 left로 둡니다. 즉, 루트 노드로 둔 것입니다.
// 그리고 전에 만들었던 freeNode()함수를 이용하여 전체 트리를 순회하며 메모리를 해제합니다.
// 마지막으로 head노드의 메모리를 해제하고 함수를 종료합니다.


Node* pop()
{
	if (top < 0) return NULL;
	return stack[top--];
}

// 이 함수는 스택에서 값을 꺼내는 함수입니다.
// top이 < 0이라면 스택에 값이 없는 것이기에 NULL을 return하고 그렇지 않다면 stack[top]을 리턴하고 top의 값을 하나 줄입니다.

void push(Node* aNode)
{
	stack[++top] = aNode;
}

// 이 함수는 스택에 값을 넣는 함수입니다.
// 함수인자인 aNode를 top의 값을 하나 증가시킨 스택의 인덱스 위치에 넣습니다.


Node* deQueue()
{
	if (front == rear) {
		// printf("\n....Now Queue is empty!!\n" );
		return NULL;
	}

	front = (front + 1) % MAX_QUEUE_SIZE;
	return queue[front];

}

// 이 함수는 큐에서 값을 빼는 함수입니다.
// front와 rear의 값이 같으면 큐가 비어있다는 뜻이므로 비어있다는 메시지를 출력합니다.
// 그렇지 않다면 front의 값에 (front + 1) % MAX_QUEUE_SIZE한 값을 넣어줍니다.
// 그리고 queue[front]의 값을 리턴합니다.

void enQueue(Node* aNode)
{
	rear = (rear + 1) % MAX_QUEUE_SIZE;
	if (front == rear) {
		// printf("\n....Now Queue is full!!\n");
		return;
	}

	queue[rear] = aNode;
}

// 이 함수는 큐에 값을 넣는 함수입니다.
// rear의 값에 (rear + 1) % MAX_QUEUE_SIZE의 값을 넣어줍니다.
// 하지만 이때 front와 rear의 값이 같다면 큐가 다 찼다는 메시지를 출력합니다.
// 그리고 함수 인자인 aNode의 값을 queue[rear]에 넣습니다.





