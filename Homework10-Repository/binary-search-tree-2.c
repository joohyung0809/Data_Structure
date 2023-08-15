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
	printf("[----- [������] [2019023028] -----]\n");

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

	// Ʈ���� ������� ���� ���
	if (*h != NULL)
		freeBST(*h);

	// ��� ��带 ����� �ܰ�
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	// ��Ʈ��尡 �� ����
	(*h)->right = *h;
	(*h)->key = -9999;

	top = -1;

	front = rear = -1;

	return 1;
}

// �� �Լ��� �޴����� z�� ������ �� ����Ǵ� �Լ��Դϴ�. Binary Search Tree�� �����մϴ�. 
// Node������ ���������͸� �Լ����ڷ� �޾Ƽ� ����մϴ�
// �׸��� *h !=  NULL�� ��� ��, Ʈ���� ������� �ʴٸ� Ʈ���� �Ҵ�� ��� ��� �޸𸮸� �����մϴ�.
// �������� ����带 ����µ� *h�� �����Ҵ� �Ͽ� ����ϴ�.
// �׸��� ��Ʈ ��尡 �� ������ (*h)->left�� NULL�� �ʱ�ȭ�մϴ�. 
// (*h)->right�� *h�� �ڽ��� ����Ű�� �ϰ� (*h)->key�� -9999�� ������ ���� �ݴϴ�.
// ���������� ���ð� ť�� �̿��ϴ� �ڵ��̱� ������ top�� front�� rear�� -1�� �ʱⰪ�� �����մϴ�.



void recursiveInorder(Node* ptr)
{
	if (ptr) {
		recursiveInorder(ptr->left);
		printf(" [%d] ", ptr->key);
		recursiveInorder(ptr->right);
	}
}

// �� �Լ��� �޴� r�� ������ �� �����ϴ� �Լ��Դϴ�. Inorder������� ��带 ��ȸ�ϴµ� recursive����� �̿��մϴ�.
// ptr�� ���� �ִ� ���� ���ǿ� �ִ� ����Լ����� �����մϴ�.
// ptr->left�� ���� recursiveInorder()�Լ��� ����ϰ� key�� print�� �� ptr->right�� recursiveInorder()�Լ��� ����մϴ�. 


void iterativeInorder(Node* node)
{
	for (;;) // for loop��
	{
		for (; node; node = node->left)
			push(node); // ���ÿ� ����
		node = pop(); // ���ÿ��� ����

		if (!node) break; // ������ ������ ��� (top<0�� �ܿ� node�� NULL���� ����)
		printf(" [%d] ", node->key);

		node = node->right;
	}
}

// �� �Լ��� �޴� t�� ������ �� ����Ǵ� �Լ��Դϴ�. Inorder������� ��带 ��ȸ�ϴµ� iterative����� �̿��մϴ�.
// �̶� iterative����� stack�� �����ϴ� ������� ��ȸ�մϴ�. ��ȸ�ϸ鼭 �ٽ� ���ư� ���� ������ ����ϱ� ���ؼ��Դϴ�.
// �Լ��� ���캸�� for loop�� �����ϰ� �ֽ��ϴ�. for loop �ȿ��� node�� �����ϸ� node�� ���ÿ� �����մϴ�.
// �׸��� node�� node->left�� �̵���ŵ�ϴ�. �׸��� node�� NULL�̶�� for���� ���� ���ÿ��� �����մϴ�. 
// ���ÿ� ���� ��ġ�� ����� key���� ����մϴ�. �׸��� node�� node�� ���������� �̵���ŵ�ϴ�.
// �� �ܰ踦 ���� �ݺ��ϴٰ� node�� ���� ���ٸ� break�� ����Ͽ� ���ѹݺ����� �����ϴ�.


void levelOrder(Node* ptr)
{

	if (!ptr) return; // Ʈ���� ����ִ� ���

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

// �� �Լ��� �޴� l�� ������ �� ����Ǵ� �Լ��Դϴ�. levelOrder��ȸ �� ���� ������� ��ȸ�մϴ�.
// �̶� ���� ���� ��ȸ�� ť�� ����մϴ�. 
// Ʈ���� ����ִٸ� �Լ��� �����մϴ�. �׷��� �ʴٸ� enQueue�Լ��� ����Ͽ� ť�� ���� ��� ��ġ�� �ֽ��ϴ�.
// �׸��� ptr�� ������ ������ ���� �������� ����˴ϴ�. 
// ���� ptr�� deQueue���� return�� ���� �־��ݴϴ�. �׷��� ptr�� NULL�̸� �ݺ����� Ż���ϰ� �׷��� �ʴٸ� ���� ���ǹ��� �����մϴ�.
// ptr�� �����ϸ� ���� ptr�� key���� ����ϰ�, ptr�� left�� �����ϸ� ptr�� left�� enQueue()�ϰ� , ptr�� right�� �����ϸ� ptr�� right�� enQueue()�մϴ�.

int insert(Node* head, int key)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->key = key;
	newNode->left = NULL;
	newNode->right = NULL;

	// ��� ��常 �ִ� ���
	if (head->left == NULL) {
		head->left = newNode;
		return 1;
	}

	Node* n = head->left;
	Node* parentNode = NULL;

	while (n != NULL) {

		// ���� ���� �־����� ���� 
		if (n->key == key) return 1;

		// �ݺ����� ���� �θ��尡 �ڽ� ��� ��� �����
		parentNode = n;

		//key ���� ���Ͽ� ���� �ִ� n�� Ű���� �Է¹��� Ű ������ ������ ������ �� �ܴ̿� �������� ����.(NULL�� ����)
		if (n->key < key)
			n = n->right;
		else
			n = n->left;
	}

	// �ݺ����� ������ �θ���� ���Ͽ� ���������� ������ �������� ������ ����
	if (parentNode->key > key)
		parentNode->left = newNode;
	else
		parentNode->right = newNode;
	return 1;
}

// �� �Լ��� ����Ž��Ʈ���� Ư���� �°� �Է��� key���� �˸��� ��ġ�� ������ �ϴ� �Լ��Դϴ�.
// ���� newNode������ �����Ҵ��Ͽ� ���ο� ��尡 �� ������ �Ҵ��մϴ�.
// �׸��� �� ����� key���� �Է¹��� ���� �ְ�, ������ ��ũ�� NULL�� �����մϴ�.
// �������� head->left == NULL�� ��� ��, ����常 �ִ� ��� ��Ʈ��忡 ���ο� ��尡 ���� �ϸ� �˴ϴ�.
// �׷��� head->left�� newNode�� �ְ� �Լ��� ������׽��ϴ�.
// ����常 �ִ� ��찡 �ƴ϶�� Node* ������ n�� parentNode�� �����Ͽ� ���� head->left�� NULL�� ����Ű�� �߽��ϴ�.
// �̶� parentNode�� ���� ���� �̵��ϴ� n�� �θ��带 ����Ű�� ���� �����߽��ϴ�.

// ���� �Է��� ���� ã�� ���� Ʈ���� Ž���ϱ� ���� �ݺ����� �����Ͽ� parentNode = n�� ���ݴϴ�.
// �׸��� ���� ������ �̵��ϴ� n�� key���� �Է¹��� Ű���� ���Ͽ� ������ ������, ũ�� ���� ���� �̵��� �� �ֵ��� �߽��ϴ�.
// ����Ʈ������ �θ��庸�� ������ �������� ũ�� ���������� �����ϱ� ���ؼ��Դϴ�.
// Ȥ�ó� ���� ���� �ԷµǴ� ���� �����ϱ� ���� �׷��� ��� �Լ��� �������� �߽��ϴ�.
// ���������� �ݺ����� ������ �θ���� ���Ͽ� ���������� ������ �������� ������ �����ϴ� �ڵ带 �ۼ��߽��ϴ�.
// �ռ� ����ߵ��� �θ����� key����  ���Ͽ� ��� ��ġ�� �����ϱ� �����Դϴ�.


// ���忡 ����Ʈ���� Ư���� �����ϰڽ��ϴ�. �� ���� �ִ� �� ���� �ڽĳ�带 �����ϴ�.
// ���� ����Ʈ���� ������ ����Ʈ���� ������ �� ������, 0���� ��带 ���� �� �ֽ��ϴ�.
// �׷��� ����Ʈ���� �����̰ų� ��Ʈ�� ���� ����Ʈ��, ������ ����Ʈ�� �� ���� �и��� ���� Ʈ���� ���� �� ����� ���� �������� ������ �� �ֽ��ϴ�.
// �� �ҽ��ڵ忡�� ������ ���� ����Ʈ���� �θ��庸�� ū �ڽĳ��� ������, ������ �������� �ִ� ������ �߰��� ����Ž��Ʈ���� ������ ���Դϴ�.

int deleteNode(Node* head, int key)
{
	// ���� ��尡 ���� ���
	if (head == NULL) {
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	if (head->left == NULL) {
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	// head->left�� ��Ʈ �����
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

	// �ݺ����� �� ���������� �Է¹��� key���� ���� ���� ������ ���� ���
	if (ptr == NULL)
	{
		printf("No node for key [%d]\n ", key);
		return -1;
	}

	// �ݺ����� ������ �� �������� ��尡 ��������� ���
	if (ptr->left == NULL && ptr->right == NULL) // �������� ���ʰ� �����ʿ� ��尡 ����
	{
		if (parent != NULL) { // parent�� �����ϸ� �������� ��尡 ��Ʈ��尡 �ƴ϶�� ��
			if (parent->left == ptr)
				parent->left = NULL;
			else
				parent->right = NULL;
		}
		else {
			// parent == NULL�̸� ��Ʈ ��带 ������ �Ѵٴ� ��
			head->left = NULL;

		}

		free(ptr);
		return 1;
	}

	// �������� ����� �ڽĳ�尡 �� �� �ִ� ���
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
			// �θ��尡 NULL�̸鼭 �ڽĳ�尡 �� �� ������ ptr�� ��Ʈ����� ��
			root = child; // �ڽĳ�尡 ��Ʈ ��尡 �Ǿ�� ��
		}

		free(ptr);
		return 1;
	}


	//������ �� ��尡 �� �� �ִ� ���

	Node* candidate;
	parent = ptr;


	candidate = ptr->right;

	// ptr�������� ������ ����Ʈ���� ���� ���� ��带 �����ϱ� ���� ���� �������� ��.
	while (candidate->left != NULL)
	{
		parent = candidate;
		candidate = candidate->left;
	}

	// �ؿ��� ���� �ٲٸ� parent�� ������ Ȥ�� ������ ������⿡ �� ���� candidate�� ������ ������ �������.
	// left�� NULL�� ������ �Ա⿡ ������ NULL���̹Ƿ� ������ ���� �����
	if (parent->right == candidate)
		parent->right = candidate->right;
	else
		parent->left = candidate->right;

	
	// ptr�� key�� candidate�� key������ �ٲ�
	ptr->key = candidate->key;

	free(candidate);
	return 1;
}

// �� �Լ��� �޴� d�� ������ �� ����Ǵ� �Լ��Դϴ�. �Է��� key�� ���� ã�� �� ��带 �����մϴ�.
// �Լ��� ���ڴ� head���� �Է��� key���� ����մϴ�.
// ���� head�� NULL�̰ų� head�� left�� NULL�̸� ���� ���� �����Ƿ� ���� ��尡 ���ٴ� �޽����� ����մϴ�.
// �׶�� Node������ root, parent, ptr�� ����� ���� head->left, NULL, root�� �־��ݴϴ�. 
// ���⼭ ptr�� ��� ���� ���� �̵��ϰ� parent�� ptr�� ����ٴϸ� ptr�� �θ� ��� ������ �մϴ�.
// �������� ptr�� NULL�� �ƴϰ�, ptr->key�� key�� �ƴ� ���� �ݺ����� �����մϴ�.
// ptr->key�� key�� �ƴ϶�� parent�� ptr��ġ�� �̵��ϰ� ptr->key�� �Է¹��� ���� ���մϴ�.
// �� ��� ptr->key�� ũ�� ����, �׷��� �ʴٸ� ���������� �̵��մϴ�.
// �̵��� ������ ptr�� NULL�̶�� �ش��ϴ� key���� ���� ��尡 ���ٴ� �޽����� ����մϴ�.
// �׷��� �ʴٸ� 3���� ���� ����� ó���մϴ�.

// 1. �������� ��尡 ��������� ���
// �� ������尡 ��Ʈ��尡 �ƴ� ��� ptr�� �θ����� �����̶�� ���ʰ��� NULL�� �ٲٰ�, �������̶�� �����ʰ��� NULL�� �ٲߴϴ�.
// ��Ʈ����� ������� ������ ��Ʈ����̹Ƿ� �� ���� NULL�� �ٲߴϴ�.
// ���������� ���ǹ��� ������ ptr�� �ִ� ��ġ�� �޸� �����ϸ� �Լ��� �����մϴ�.

// 2. �������� ����� �ڽĳ�尡 �� �� �ִ� ���
// ���� Node������ child�� �� �� ����ϴ�. 
// �׷���  ptr�� ���ʿ� ���� ������ child�� ���� ������ �̵���Ű��, �����ʿ� ���� ������ child�� ������ ������ �̵���ŵ�ϴ�.
// child���� ���� �� ptr�� NULL�� �ƴϸ� ��, ��Ʈ��尡 �ƴϸ� ptr�� �ڽĳ�带 ptr�ڸ��� �̵����� ptr�� �����մϴ�.
// ptr�� NULL�̸� ��, ��Ʈ����� �� �ڽĳ�尡 ��Ʈ��尡 �ǰ� �մϴ�.

// 3. �������� ����� �ڽĳ�尡 �� �� �ִ� ���
// ���� Node������ �ĺ� ��� candidate�� �����մϴ�. �׸��� ptr�� ������ ����Ʈ���� ���� ���� ���� ���ϱ� ���� NULL���� ���� �� ���� �������� ��� �̵��մϴ�.
// �׸��� parent�� right�� candidate�� parent->right = candidate->right�� �ϰ�, �׷��� �ʴٸ� parent->left = candidate->right�� �մϴ�.
// �������� ptr�� key�� candidate�� key������ �ٲٰ�, candidate�� �޸𸮸� �����ϰ� �Լ��� �����մϴ�.


void freeNode(Node* ptr)
{
	if (ptr) {
		freeNode(ptr->left);
		freeNode(ptr->right);
		free(ptr);
	}
}

// �� �Լ��� ��忡�� �Ҵ�Ǿ��� �޸𸮸� �����ϴ� �Լ��Դϴ�.
// Node*������ ptr�� ���� �ִٸ� �ٽ� freeNode�Լ��� ȣ���ϴ� ����Լ� �����Դϴ�.
// Ʈ�� ��ο� �����ϱ� ���� ����Լ��� ��������� �����ϴ� ptr�� free()�Լ��� ���� �޸� �Ҵ��� �����߽��ϴ�.

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

// �� �Լ��� ������� Binary Search Tree�� �����ϴ� �Լ��Դϴ�.
// �� �Լ������� ó���� head->left�� NULL�̶�� ��, head�� �ִٸ� free()�Լ��� �̿��Ͽ� head�� �����ϰ� �Լ��� �����մϴ�.
// �� ���� ��쿡�� Node* ������ p�� head�� left�� �Ӵϴ�. ��, ��Ʈ ���� �� ���Դϴ�.
// �׸��� ���� ������� freeNode()�Լ��� �̿��Ͽ� ��ü Ʈ���� ��ȸ�ϸ� �޸𸮸� �����մϴ�.
// ���������� head����� �޸𸮸� �����ϰ� �Լ��� �����մϴ�.


Node* pop()
{
	if (top < 0) return NULL;
	return stack[top--];
}

// �� �Լ��� ���ÿ��� ���� ������ �Լ��Դϴ�.
// top�� < 0�̶�� ���ÿ� ���� ���� ���̱⿡ NULL�� return�ϰ� �׷��� �ʴٸ� stack[top]�� �����ϰ� top�� ���� �ϳ� ���Դϴ�.

void push(Node* aNode)
{
	stack[++top] = aNode;
}

// �� �Լ��� ���ÿ� ���� �ִ� �Լ��Դϴ�.
// �Լ������� aNode�� top�� ���� �ϳ� ������Ų ������ �ε��� ��ġ�� �ֽ��ϴ�.


Node* deQueue()
{
	if (front == rear) {
		// printf("\n....Now Queue is empty!!\n" );
		return NULL;
	}

	front = (front + 1) % MAX_QUEUE_SIZE;
	return queue[front];

}

// �� �Լ��� ť���� ���� ���� �Լ��Դϴ�.
// front�� rear�� ���� ������ ť�� ����ִٴ� ���̹Ƿ� ����ִٴ� �޽����� ����մϴ�.
// �׷��� �ʴٸ� front�� ���� (front + 1) % MAX_QUEUE_SIZE�� ���� �־��ݴϴ�.
// �׸��� queue[front]�� ���� �����մϴ�.

void enQueue(Node* aNode)
{
	rear = (rear + 1) % MAX_QUEUE_SIZE;
	if (front == rear) {
		// printf("\n....Now Queue is full!!\n");
		return;
	}

	queue[rear] = aNode;
}

// �� �Լ��� ť�� ���� �ִ� �Լ��Դϴ�.
// rear�� ���� (rear + 1) % MAX_QUEUE_SIZE�� ���� �־��ݴϴ�.
// ������ �̶� front�� rear�� ���� ���ٸ� ť�� �� á�ٴ� �޽����� ����մϴ�.
// �׸��� �Լ� ������ aNode�� ���� queue[rear]�� �ֽ��ϴ�.





