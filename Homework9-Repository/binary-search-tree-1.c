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
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->key = key;
	newNode->left = newNode->right = NULL;
	//head��常 �ִ� ���
	if (head->left == NULL) {
		head->left = newNode;
		return 1;
	}
	Node* n = head->left;
	Node* parentNode = NULL;
	while (n != NULL) {

		// ���� ���� �� �־��ش� �� ������
		if (n->key == key) {
			return 1;
		}

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

				// ���ǿ� �ɸ� ��尡 ��Ʈ ����� ���
				if (parentNode == head)
					head->left = NULL;

				if (parentNode->left == ptr) // ���ǿ� �ɸ� ��尡 ������ ���
					parentNode->left = NULL;
				else // ���ǿ� �ɸ� ��尡 �������� ���
					parentNode->right = NULL;

				free(ptr);
			}
			else {
				printf("the node [%d] is not a leaf \n", ptr->key);
			}
			return 1;
		}

		parentNode = ptr;

		// Ʈ���� ��ȸ�ϴ� ptr�� key���� �Է¹��� ���� ���Ͽ� ptr�� �̵���Ŵ
		if (ptr->key < key)
			ptr = ptr->right;
		else
			ptr = ptr->left;


	}

	printf("Cannot find the node for key [%d]\n ", key);

	return 1;

}

// �� �Լ��� �Է¹��� ���� Ʈ�� ���� ������忡 �ִٸ� �����ϴ� �Լ��Դϴ�.
// ���� head == NULL�� ���� head->left == NULL�� ��쿡�� ������ ���� ���⿡ ���� �޽����� ����ϰ� �Լ��� �����մϴ�.
// ������ ���� �ִ� Ʈ����� ��ȸ�� ���� Node* ������ n�� parentNode�� �����Ͽ� ���� head->left�� NULL�� ����Ű�� �߽��ϴ�.
// �̶� parentNode�� ���� ���� �̵��ϴ� n�� �θ��带 ����Ű�� ���� �����߽��ϴ�.

// �������� Ʈ���� ��ȸ�ϱ� ���� �ݺ����� �����մϴ�. �� �ȿ��� parentNode = ptr�� �־� �������� �����̴� ptr�� parentNode�� ���󰡰� �մϴ�.
// ����� ptr�� key���� �Է¹��� Ű���� ���Ͽ� ������ ������, ũ�� ���� ���� �̵��� �� �ֵ��� �߽��ϴ�.
// �ݺ��� ������ ������ ���� key���� ã�� �� �ϸ� ã�� �� ���ٴ� �޽����� ����մϴ�.

// �ݺ����� �����ϴ� ptr�� key���� �Է¹��� key���� ���� ��� ���� ���ǹ��� �����մϴ�. 
// �� ���ǿ��� ptr->left == NULL �׸��� ptr->right == NULL�� ��찡 ��������� ����Դϴ�.
// �� ��찡 �������� �ʴ´ٸ� �� key�� ���� ���� ������尡 �ƴ϶�� �޽����� ����մϴ�.
// �̶� parentNode == head�� ���� ��Ʈ��� �ϳ��� �ִٴ� ���Դϴ�. �̷��� ��� head->left�� NULL�� ������ݴϴ�.
// parentNode->left�� ptr�̶�� parentNode�� ���� �ڽĳ�尡 ��������̹Ƿ� parentNode->left�� NULL�� ������ݴϴ�.
// �� ���� ���� parentNode�� ������ �ڽĳ�尡 ��������̹Ƿ� parentNode->right�� NULL�� ������ݴϴ�.
// �� �۾��� ������ �Ҵ�Ǿ��� �޸𸮸� �����ϱ� ���� ptr�� free()�Լ��� ���� �޸� �����մϴ�.


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
