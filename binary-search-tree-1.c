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
	printf("[----- [������] [2019023028] -----]");
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

	// Ʈ���� ������� ���� ���
	if (*h != NULL)
		freeBST(*h);

	// ��� ��带 ����� ����
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;
	(*h)->right = *h;
	(*h)->key = -9999;
	return 1;
}

// �� �Լ��� Binary Search Tree�� ����带 �����ϴ� �Լ��Դϴ�.
// �Լ��� �ڼ��� ���캸�� ��� ���� ���� h�� ���� �����ͷ� �޾ҽ��ϴ�.
// �� *h�� ���� �ٲ� �� �ִٴ� �ǹ��Դϴ�.
// �ڵ带 ���� if���� ������ ����带 ����µ� �̶� *h�� ���� ��ũ�� Binary Search Tree�� ��Ʈ ���� ����մϴ�.
// �׸��� ��� ��常 �����ϴ� ���̱⿡ *h�� ������ ��ũ�� �ٽ� �ڽ��� ����Ű�� ����� key���� -9999�� �־� �����մϴ�.


void inorderTraversal(Node* ptr)
{
	if (ptr) {
		inorderTraversal(ptr->left);
		printf(" [%d] ", ptr->key);
		inorderTraversal(ptr->right);
	}
}

// �� �Լ��� inorder ����� Ʈ�� ��ȸ ����� ���� �Լ��Դϴ�.
// �Լ��� ���ڴ� Node* ������ ptr������ ����߽��ϴ�.
// if(ptr)�� ��� ��, ptr�� ���� �ִٸ� ��� �Ʒ��� ��ȯ ������ �ݺ��մϴ�.
// �� ������ ���� Ʈ��, ��Ʈ���, ������ Ʈ�� �����̱� ������ ��ó�� �ڵ带 �ۼ��մϴ�.
// ������ ���� Ž���� �� �߰��� key�� ���� ȣ���ϴ� �ڵ带 �ۼ��մϴ�. �׸��� �������� Ž���ϸ� inorder ����� ��ȸ����� ���� �� �ֽ��ϴ�. 

void preorderTraversal(Node* ptr)
{
	if (ptr) {
		printf(" [%d] ", ptr->key);
		preorderTraversal(ptr->left);
		preorderTraversal(ptr->right);
	}
}

// �� �Լ��� preorder ����� Ʈ�� ��ȸ ����� ���� �Լ��Դϴ�.
// �Լ��� ���ڴ� Node* ������ ptr������ ����߽��ϴ�.
// if(ptr)�� ��� ��, ptr�� ���� �ִٸ� ��� �Ʒ��� ��ȯ ������ �ݺ��մϴ�.
// �� ������ ��Ʈ���, ���� Ʈ��, ������ Ʈ�� �����̱� ������ ��ó�� �ڵ带 �ۼ��մϴ�.
// ���� ó�� ��ġ�� ���� ��Ʈ�̱� ������ ����ϰ�, ���� ������ ������ �ٽ� ��ȸ�ϸ� preorder ����� ��ȸ����� ���� �� �ֽ��ϴ�.


void postorderTraversal(Node* ptr)
{
	if (ptr) {
		postorderTraversal(ptr->left);
		postorderTraversal(ptr->right);
		printf(" [%d] ", ptr->key);
	}
}

// �� �Լ��� postorder ����� Ʈ�� ��ȸ ����� ���� �Լ��Դϴ�.
// �Լ��� ���ڴ� Node* ������ ptr������ ����߽��ϴ�.
// if(ptr)�� ��� ��, ptr�� ���� �ִٸ� ��� �Ʒ��� ��ȯ ������ �ݺ��մϴ�.
// �� ������  ���� Ʈ��, ������ Ʈ��, ��Ʈ��� �����̱� ������ ��ó�� �ڵ带 �ۼ��մϴ�.
// ���� ���ʰ� ������ ������ ��ȸ�� �� ��Ʈ ��带 ��ȸ�ϸ� posteorder ����� ��ȸ����� ���� �� �ֽ��ϴ�.


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

// �� �Լ��� �Է��� key���� ���� ����� �ּҸ� ��͹������ ã�Ƴ��� �Լ��Դϴ�.
// �̴� Ʈ���� ��ȸ�ϸ鼭 ��带 ã�µ� ptr�� key�� �Է¹��� key���� ������ �Լ����ڸ� ������ ��ũ�� �޾� ����Լ��� ȣ���մϴ�.
// �׷��� �ʰ� ptr�� key�� �Է¹��� key���� ũ�� �Լ����ڸ� ���� ��ũ�� �޾� ����Լ��� ȣ���մϴ�.
// �׷��� ��� Ž���ذ��ٰ� ptr�� key���� �Է¹��� key���� �������� ��� ptr�� return�մϴ�.
// ptr�� NULL�̶�� NULL�� return�մϴ�. �� ���� Ʈ���� Ž���������� ��ġ�ϴ� key���� ���� ���� NULL�� return�Ѵٴ� ���Դϴ�.

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

// �� �Լ��� �Է��� key���� ���� ����� �ּҸ� ����������� ã�Ƴ��� �Լ��Դϴ�.
// �Լ� ó���� ptr�̶�� ������ �����Ͽ� ������ �Ӵϴ�.
// �׸��� ptr�� NULL�� �� ������ ptr�� ��ġ�� �̵���ŵ�ϴ�. 
// �̶� �̵���Ű�� ������ ���� ptr ��ġ�� key���� �Է¹��� ���� ���Ͽ� ���մϴ�.
// ptr�� key���� �Է¹��� ������ ������ ������, �׷��� �ʴٸ� �������� �̵��մϴ�. 
// �̷��� �ݺ����� �����ϴٰ� ptr�� key���� �Է¹��� ���� ��ġ�ϸ� ptr�� retun�մϴ�.


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
