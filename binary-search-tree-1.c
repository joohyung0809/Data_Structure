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

typedef struct node {
	int key;
	struct node* left;
	struct node* right;
} Node;

int initializeBST(Node** h);

/* functions that you have to implement */
void inorderTraversal(Node* ptr);	  /* recursive inorder traversal */
void preorderTraversal(Node* ptr);    /* recursive preorder traversal */
void postorderTraversal(Node* ptr);	  /* recursive postorder traversal */
int insert(Node* head, int key);  /* insert a node to the tree */
int deleteLeafNode(Node* head, int key);  /* delete the leaf node for the key */
Node* searchRecursive(Node* ptr, int key);  /* search the node for the key */
Node* searchIterative(Node* head, int key);  /* search the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */
void freeNode(Node* ptr);


int main()
{
	printf("[----- [오주형] [2019023028] -----]");
	char command;
	int key;
	Node* head = NULL;
	Node* ptr = NULL;

	do {
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete leaf Node             = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
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
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key);
			if (ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key);
			if (ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I':
			inorderTraversal(head->left);
			break;
		case 'p': case 'P':
			preorderTraversal(head->left);
			break;
		case 't': case 'T':
			postorderTraversal(head->left);
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

	// 헤드 노드를 만드는 과정
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;
	(*h)->right = *h;
	(*h)->key = -9999;
	return 1;
}

// 이 함수는 Binary Search Tree의 헤드노드를 세팅하는 함수입니다.
// 함수를 자세히 살펴보면 헤드 노드로 쓰일 h를 이중 포인터로 받았습니다.
// 즉 *h의 값을 바꿀 수 있다는 의미입니다.
// 코드를 보면 if문이 지나고 헤드노드를 만드는데 이때 *h의 왼쪽 링크는 Binary Search Tree의 루트 노드로 사용합니다.
// 그리고 헤드 노드만 생성하는 것이기에 *h의 오른쪽 링크는 다시 자신을 가리키게 만들고 key에는 -9999를 넣어 세팅합니다.


void inorderTraversal(Node* ptr)
{
	if (ptr) {
		inorderTraversal(ptr->left);
		printf(" [%d] ", ptr->key);
		inorderTraversal(ptr->right);
	}
}

// 이 함수는 inorder 방식의 트리 순회 방식을 만든 함수입니다.
// 함수의 인자는 Node* 형태의 ptr변수를 사용했습니다.
// if(ptr)인 경우 즉, ptr에 값이 있다면 계속 아래의 순환 구조를 반복합니다.
// 그 순서는 왼쪽 트리, 루트노드, 오른쪽 트리 순서이기 때문에 위처럼 코드를 작성합니다.
// 왼쪽을 전부 탐색후 그 중간에 key의 값을 호출하는 코드를 작성합니다. 그리고 오른쪽을 탐색하면 inorder 방식의 순회방식을 만들 수 있습니다. 

void preorderTraversal(Node* ptr)
{
	if (ptr) {
		printf(" [%d] ", ptr->key);
		preorderTraversal(ptr->left);
		preorderTraversal(ptr->right);
	}
}

// 이 함수는 preorder 방식의 트리 순회 방식을 만든 함수입니다.
// 함수의 인자는 Node* 형태의 ptr변수를 사용했습니다.
// if(ptr)인 경우 즉, ptr에 값이 있다면 계속 아래의 순환 구조를 반복합니다.
// 그 순서는 루트노드, 왼쪽 트리, 오른쪽 트리 순서이기 때문에 위처럼 코드를 작성합니다.
// 먼저 처음 위치한 곳이 루트이기 때문에 출력하고, 왼쪽 오른쪽 순서로 다시 순회하면 preorder 방식의 순회방식을 만들 수 있습니다.


void postorderTraversal(Node* ptr)
{
	if (ptr) {
		postorderTraversal(ptr->left);
		postorderTraversal(ptr->right);
		printf(" [%d] ", ptr->key);
	}
}

// 이 함수는 postorder 방식의 트리 순회 방식을 만든 함수입니다.
// 함수의 인자는 Node* 형태의 ptr변수를 사용했습니다.
// if(ptr)인 경우 즉, ptr에 값이 있다면 계속 아래의 순환 구조를 반복합니다.
// 그 순서는  왼쪽 트리, 오른쪽 트리, 루트노드 순서이기 때문에 위처럼 코드를 작성합니다.
// 먼저 왼쪽과 오른쪽 순서로 순회한 후 루트 노드를 순회하면 posteorder 방식의 순회방식을 만들 수 있습니다.


int insert(Node* head, int key)
{

}

int deleteLeafNode(Node* head, int key)
{

}

Node* searchRecursive(Node* ptr, int key)
{
	if (ptr == NULL)
		return NULL;

	if (ptr->key < key)
		ptr = searchRecursive(ptr->right, key);
	else if (ptr->key > key)
		ptr = searchRecursive(ptr->left, key);

	return ptr;
}

// 이 함수는 입력한 key값을 가진 노드의 주소를 재귀방식으로 찾아내는 함수입니다.
// 이는 트리를 순회하면서 노드를 찾는데 ptr의 key가 입력받은 key보다 작으면 함수인자를 오른쪽 링크로 받아 재귀함수를 호출합니다.
// 그렇지 않고 ptr의 key가 입력받은 key보다 크면 함수인자를 왼쪽 링크로 받아 재귀함수를 호출합니다.
// 그렇게 계속 탐색해가다가 ptr의 key값이 입력받은 key값과 같아지는 경우 ptr을 return합니다.
// ptr이 NULL이라면 NULL을 return합니다. 이 뜻은 트리를 탐색했음에도 일치하는 key값이 없는 경유 NULL을 return한다는 것입니다.

Node* searchIterative(Node* head, int key)
{
	Node* ptr = head->left;

	while (ptr != NULL)
	{
		if (ptr->key == key)
			return ptr;

		if (ptr->key < key) {
			ptr = ptr->right;
		}
		else {
			ptr = ptr->left;
		}
	}

	return NULL;

}

// 이 함수는 입력한 key값을 가진 노드의 주소를 순차방식으로 찾아내는 함수입니다.
// 함수 처음에 ptr이라는 변수를 선언하여 헤드노드로 둡니다.
// 그리고 ptr이 NULL이 될 때까지 ptr의 위치를 이동시킵니다. 
// 이때 이동시키는 기준은 현재 ptr 위치의 key값과 입력받은 값과 비교하여 정합니다.
// ptr의 key값이 입력받은 값보다 작으면 오른쪽, 그렇지 않다면 왼쪽으로 이동합니다. 
// 이렇게 반복문을 실행하다가 ptr의 key값이 입력받은 값과 일치하면 ptr을 retun합니다.


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
