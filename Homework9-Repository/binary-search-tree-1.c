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
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->key = key;
	newNode->left = newNode->right = NULL;
	//head노드만 있는 경우
	if (head->left == NULL) {
		head->left = newNode;
		return 1;
	}
	Node* n = head->left;
	Node* parentNode = NULL;
	while (n != NULL) {

		// 같은 값은 안 넣어준다 이 말이지
		if (n->key == key) {
			return 1;
		}

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

int deleteLeafNode(Node* head, int key)
{
	if (head == NULL) {
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	if (head->left == NULL) {
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	Node* ptr = head->left;
	Node* parentNode = head;

	while (ptr != NULL) {

		if (ptr->key == key) {
			if (ptr->left == NULL && ptr->right == NULL) {

				// 조건에 걸린 노드가 루트 노드인 경우
				if (parentNode == head)
					head->left = NULL;

				if (parentNode->left == ptr) // 조건에 걸린 노드가 왼쪽인 경우
					parentNode->left = NULL;
				else // 조건에 걸린 노드가 오른쪽인 경우
					parentNode->right = NULL;

				free(ptr);
			}
			else {
				printf("the node [%d] is not a leaf \n", ptr->key);
			}
			return 1;
		}

		parentNode = ptr;

		// 트리를 순회하는 ptr의 key값과 입력받은 값을 비교하여 ptr을 이동시킴
		if (ptr->key < key)
			ptr = ptr->right;
		else
			ptr = ptr->left;


	}

	printf("Cannot find the node for key [%d]\n ", key);

	return 1;

}

// 이 함수는 입력받은 값이 트리 내에 리프노드에 있다면 삭제하는 함수입니다.
// 먼저 head == NULL인 경우와 head->left == NULL인 경우에는 삭제할 값이 없기에 관련 메시지를 출력하고 함수를 종료합니다.
// 삭제할 값이 있는 트리라면 순회를 위해 Node* 형태의 n과 parentNode를 선언하여 각각 head->left와 NULL을 가리키게 했습니다.
// 이때 parentNode는 다음 노드로 이동하는 n의 부모노드를 가리키기 위해 선언했습니다.

// 다음으로 트리를 순회하기 위해 반복문을 수행합니다. 이 안에서 parentNode = ptr을 넣어 다음으로 움직이는 ptr을 parentNode가 따라가게 합니다.
// 참고로 ptr의 key값이 입력받은 키값과 비교하여 작으면 오른쪽, 크면 왼쪽 노드로 이동할 수 있도록 했습니다.
// 반복문 실행이 끝나도 같은 key값을 찾지 못 하면 찾을 수 없다는 메시지를 출력합니다.

// 반복문을 수행하다 ptr의 key값이 입력받은 key값과 같은 경우 다음 조건문을 수행합니다. 
// 위 조건에서 ptr->left == NULL 그리고 ptr->right == NULL인 경우가 리프노드인 경우입니다.
// 이 경우가 존재하지 않는다면 그 key를 가진 노드는 리프노드가 아니라는 메시지를 출력합니다.
// 이때 parentNode == head인 경우는 루트노드 하나만 있다는 뜻입니다. 이러한 경우 head->left를 NULL로 만들어줍니다.
// parentNode->left이 ptr이라면 parentNode의 왼쪽 자식노드가 리프노드이므로 parentNode->left를 NULL로 만들어줍니다.
// 그 외의 경우는 parentNode의 오른쪽 자식노드가 리프노드이므로 parentNode->right를 NULL로 만들어줍니다.
// 이 작업이 끝나면 할당되었던 메모리를 해제하기 위해 ptr을 free()함수를 통해 메모리 해제합니다.


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
