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

/* you may add your own defined functions if necessary */


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

}

Node* searchIterative(Node* head, int key)
{

}


int freeBST(Node* head)
{

}
