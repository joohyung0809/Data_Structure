/*
 * singly linked list
 *
 *  Data Structures
 *  School of Computer Science
 *  at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>

 /* �ʿ��� ������� �߰� */

typedef struct Node {
	int key;
	struct Node* link;
} listNode;

typedef struct Head {
	struct Node* first;
}headNode;


/* �Լ� ����Ʈ */
headNode* initialize(headNode* h);
int freeList(headNode* h);

int insertFirst(headNode* h, int key);
int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);

int deleteFirst(headNode* h);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);

int main()
{
	char command;
	int key;
	headNode* headnode = NULL;
	printf("[----- [������][2019023028] ----- ]\n");

	do {
		printf("----------------------------------------------------------------\n");
		printf("                     Singly Linked List                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command) {
		case 'z': case 'Z':
			headnode = initialize(headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	return 1;
}

headNode* initialize(headNode* h) {

	/* headNode�� NULL�� �ƴϸ�, freeNode�� ȣ���Ͽ� �Ҵ�� �޸� ��� ���� */
	if (h != NULL)
		freeList(h);

	/* headNode�� ���� �޸𸮸� �Ҵ��Ͽ� ���� */
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	return temp;
}

// �� �Լ��� �޴����� z�� ������ �� ����ϴ� �Լ��Դϴ�. headNode�� NULL�� �ƴϸ�, freeNode�� ȣ���Ͽ� �Ҵ�� �޸� ��� �����մϴ�.
// �׷��� �ʴٸ� headNode�� ���� �޸𸮸� �Ҵ��Ͽ� �����Ͽ� ������ node�� ����� �� �ְ� ����ϴ�.
// �Լ��� �ڼ��� ���캸�� headnode ����ü ������ ���� h�� ����մϴ�.
// ���� headNode�� NULL�� �ƴϸ� h�� freeList�Լ��� ���� �޸𸮸� ��� �����մϴ�.
// �׷��� �ʴٸ� temp�� �޸𸮸� �������� �Ҵ��մϴ�. �̴� headNode�� ���� �޸𸮸� �Ҵ��߰� temp->first�� NULL������ �ʱ�ȭ �� �� �����߽��ϴ�.


int freeList(headNode* h) {
	/* h�� ����� listNode �޸� ����
	 * headNode�� �����Ǿ�� ��.
	 */
	listNode* p = h->first;

	listNode* prev = NULL;
	while (p != NULL) {
		prev = p;
		p = p->link;
		free(prev);
	}
	free(h);
	return 0;
}

// �� �Լ��� �޴����� q�� ������ �� ����ϴ� �Լ��Դϴ�. h�� ����� listNode �޸� �� headNode�� �����մϴ�.
// �Լ��� �ڼ��� ���캸�� headnode ����ü ������ ���� h�� ����մϴ�.
// �Լ� ó���� listnode����ü ������ p�� prev�� �����Ͽ� p�� first�� prev�� NULL�� �־�Ӵϴ�.
// �̶� p�� ��� ��忡 �����ϴ� ������ �մϴ�. �׸��� prev�� p�� node�� ���� �� ���� �޾� free�� �����մϴ�.
// �׷��� �ݺ����� ���� ��� ��带 �����Ͽ� �޸𸮸� ������ �� ���������� headNode�� h�� �����մϴ�.



/**
 * list ó���� key�� ���� ����ϳ��� �߰�
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->link = h->first;

	h->first = node;

	return 0;
}

// �� �Լ��� �޴����� f�� ������ �� ����ϴ� �Լ��Դϴ�. key���� �Է¹޾Ƽ� ���� �տ� �����մϴ�.
// �Լ��� �ڼ��� ���캸�� headnode ����ü ������ ���� h�� key���� �Լ� ���ڷ� ����ϰ� �ֽ��ϴ�.
// �Լ� ó���� �Է��� key�� ���� node�� �޸𸮸� �������� �Ҵ��մϴ�. 
// �׸��� key���� �Է¹��� ���� �ְ� link���� h->first�� �־� ���� ó�� ������ �ٲ��ݴϴ�.
// �������� h->first�� node�� �Ҵ��մϴ�. �̷��� �ϸ� �Է¹��� node�� ���� ó���� ��ġ�մϴ�.


/* ����Ʈ�� �˻��Ͽ�, �Է¹��� key���� ū���� ������ ��� �ٷ� �տ� ���� */
int insertNode(headNode* h, int key) {
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->link = NULL;

	if (h->first == NULL)
	{
		h->first = node;
		return 0;
	}

	listNode* n = h->first;
	listNode* trail = h->first;  //trail�� ������� ������ ����

	/* key�� �������� ������ ��ġ�� ã�´� */
	while (n != NULL) {
		if (n->key >= key) {  //�Է¹��� ���� ���� ������ �� ���� ���

			/* ù ��� ���ʿ� �����ؾ��� ��� ���� �˻� */
			if (n == h->first) {  // �Է¹��� ���� ���� ������ �� ���� ��찡 ù ��° ����� ���
				h->first = node; 
				node->link = n;  
			}
			else { /* �Է� ���� ���� ���� ������ �� ���� ��찡 �߰��̰ų� ������ ����� ��� */
				node->link = n;
				trail->link = node;
			}
			return 0;
		}

		/* �ݺ����� ����� ������ �����ϴ� �ڵ� */
		trail = n; 
		n = n->link; 
	}

	/* ������ ������ ã�� ���� ��� , �������� ���� */
	trail->link = node; 
	return 0;
}

// �� �Լ��� �޴����� i�� ������ �� ����ϴ� �Լ��Դϴ�. key���� �Է¹޾Ƽ� key���� ū���� ������ ��� �ٷ� �տ� �����մϴ�.
// �Լ��� �ڼ��� ���캸�� headnode ����ü ������ ���� h�� key���� �Լ� ���ڷ� ����ϰ� �ֽ��ϴ�.
// �Լ� ó���� �Է��� key�� ���� node�� �޸𸮸� �������� �Ҵ��մϴ�. �׸��� key���� �Է¹��� ���� �ְ� link���� NULL�� �־��ݴϴ�.
// �������� h->first�� NULL���� ��, ù��° ���� ����ִ��� Ȯ���մϴ�. ����ִ� ���� Ȯ���ߴٸ� ù��° ������ node�� �־��ִ� �۾��� �մϴ�.

// ���� ù��° ���� ������� �ʴٸ� listnode����ü ������ n,�� trail������ �����Ͽ� ��� first�� �־�Ӵϴ�.
// �̶� n�� node�� �� ��ġ�� ���İ�, trail�� node�� �� ��ġ�� ���������� �����߽��ϴ�.
// �������� �ݺ����� �����ϴµ�, ���� �ڵ带 ���� �ݺ����� �� ������trail = n;, n = n->link; �ڵ尡 �ݺ��˴ϴ�.
// �ٽ� ���� �ڵ带 ���캸�� n�� ���� ������ �̵��ϴٰ� NULL���� ������ ������ �ݺ����� �����մϴ�. 
// �׸��� n�� ���� ������ �̵��ϸ鼭 �Է¹��� key�� ���� ����ؼ� �����ִ� ������ �մϴ�. 
// �̶� �Է¹��� ���� ������ ������ ���� ��쿡 ù ��� ����, �߰��̰ų� �������� ��츦 ������ �����մϴ�.
// node�� ù ��° ��� �������� ���� ��� h->first �� node�� �ǰ�, node�� link �� n���� �����մϴ�.
// node�� �߰��̳� �������� ���� ��� node�� link�� n, n�� ����ؼ� ������� trail�� link�� node�� �Ӵϴ�.
// �̷��� �ϸ� trail�� n���̿� node�� ���� �� �ְ� �˴ϴ�. 
// ���������� while���� ���� �������� �Է¹��� ���� ���������� ���� ��찡 ���� ���� trail�� link�� node�� �־� ���� ���� ��带 �����մϴ�.


/**
 * list�� key�� ���� ����ϳ��� �߰�
 */
int insertLast(headNode* h, int key) {
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->link = NULL;

	if (h->first == NULL) {
		h->first = node;
		return 0;
	}
	listNode* n = h->first;
	while (n->link != NULL) { 
		n = n->link;
	}
	n->link = node;
	return 0;
}

// �� �Լ��� �޴� n�� ������ �� �����ϴ� �Լ��Դϴ�. �Է¹��� key���� ���� ���ڸ��� �����մϴ�.
// �Լ��� �ڼ��� ���캸�� headnode ����ü ������ ���� h�� key���� �Լ� ���ڷ� ����ϰ� �ֽ��ϴ�.
// �Լ� ó���� �Է��� key�� ���� node�� �޸𸮸� �������� �Ҵ��մϴ�. �׸��� key���� �Է¹��� ���� �ְ� link���� NULL�� �־��ݴϴ�.
// �������� h->first�� NULL ������ ��, ù ��° ��忡 �ƹ��͵� ������ Ȯ���ϰ� �׷��ٸ� h->first�� node�� �־� node�� ù��° ������ �ٲ��ݴϴ�.
// �׷��� �۴ٸ� listnode����ü ������ n�� first�� �־�Ӵϴ�. �̶� n�� list�� ��� Ȯ���Ͽ� ������ ��尡 ������� Ȯ���ϴ� ������ �մϴ�.
// �׷��� n�� link�� NULL���� ������ ������ ��, n�� ���� ������ ��尡 �� �� ���� n = n->link�� ���� n�� ��� ���� ���� �̵��ϰ� �մϴ�.
// �׸��� �ݺ����� �����ٸ� n�� ���� ���ڸ� ����� �����̹Ƿ� n�� link�� node�� �Ҵ��ϸ� node�� ���� �������� ���Ե� �� �ֽ��ϴ�.


/**
 * list�� ù��° ��� ����
 */
int deleteFirst(headNode* h) {

	if (h->first == NULL)
	{
		printf("nothing to delete.\n");
		return 0;
	}
	listNode* n = h->first;

	h->first = n->link;
	free(n);

	return 0;
}

// �� �Լ��� �޴� t�� ������ �� �����ϴ� �Լ��Դϴ�. list�� ù��° ��带 �����մϴ�.
// �Լ��� �ڼ��� ���캸��  headnode ����ü ������ ���� h�� ����մϴ�.
// ���� h->first�� NULL���� ��, ù��° ��尡 ����ִ� ��� ����ִٴ� �޽����� ����մϴ�.
// �׷��� �ʴٸ� listNode ������n�� �����Ͽ� h->first�� �ֽ��ϴ�. �׸��� h->first�� n->link�� �ű�ϴ�.
// �׷��� n ���� ���� h->first�� �˴ϴ�. �׸��� n�� free�Լ��� �����ϸ� �ٽ� h->first�� ó�� ��尡 �˴ϴ�.
// �׸��� n�� ������Ƿ� list�� ù��° ��尡 �����˴ϴ�.

/**
 * list���� key�� ���� ��� ����
 */
int deleteNode(headNode* h, int key) {

	if (h->first == NULL)
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first;
	listNode* trail = NULL;

	/* key�� �������� ������ ��ġ�� ã�´� */
	while (n != NULL) {
		if (n->key == key) {
			/* ù ��带 �����ؾ��ϴ� ��� */
			if (n == h->first) {
				h->first = n->link;
			}
			else { /* �߰��� ���ų� �������� �����ؾ��ϴ� ��� */
				trail->link = n->link;
			}
			free(n);
			return 0;
		}

		trail = n;
		n = n->link;
	}

	/* ã�� �� �Ѱ�� */
	printf("cannot find the node for key = %d\n", key);
	return 0;

}

// �� �Լ��� �޴����� d�� ������ �� ����ϴ� �Լ��Դϴ�. key���� �Է¹޾Ƽ� �� ���� ���� key���� ���� ��带 �����մϴ�..
// �Լ��� �ڼ��� ���캸�� headnode ����ü ������ ���� h�� key���� �Լ� ���ڷ� ����ϰ� �ֽ��ϴ�.
// �Լ� ó���� h->first�� NULL���� ��, ù��° ���� ����ִ� ��� ����ִٴ� �޽����� ����մϴ�.
// ������� �ʴٸ� listNode������ n�� trail�� �����Ͽ� ���� h->fitst�� NULL�� �־��ݴϴ�.
// �̶� n�� ������ ���, trail�� ������ ����� �� ��带 ����ŵ�ϴ�.
// �������� �ݺ����� �����ϴµ�, ���� �ڵ带 ���� �ݺ����� �� ������trail = n;, n = n->link; �ڵ尡 �ݺ��˴ϴ�.
// �ٽ� ���� �ڵ带 ���캸�� n�� NULL�� �ƴ� ���� ��, n�� ��� ��带 �� �����ϴ� ���� �ݺ����� �����մϴ�.
// n�� ��带 �ϳ��� �����ϴ� ���� n->key�� �Է¹��� key�� ���� ���� ���, ù ��° ��带 �����ϴ� ���� �߰��̰ų� �������� ��츦 �����ݴϴ�.
// �Է¹��� ���� ù ��° ����� key���� ���� ��� h->first�� n->link�� �ϰ� ���ǹ��� �������� n�� ������Ű�� ù��° ���� �������ϴ�.
// �Է¹��� ���� �߰��̳� ������ ����� key���� ���� ��� trail->link�� n->link�� �ϰ� ���ǹ��� �������� n�� ������Ű�� ���ϴ� ��尡 ������ϴ�..
// ���������� �ݺ����� ��� ���Ƶ� ��ġ�ϴ� key���� ���� ��� ã�� �� ���ٴ� �޽����� ����մϴ�.


/**
 * list�� ������ ��� ����
 */
int deleteLast(headNode* h) {
	if (h->first == NULL) {
		printf("nothing to delete\n");
		return 0;
	}

	listNode* n = h->first;
	listNode* trail = NULL;

	if (n->link == NULL) { //����: ��尡 �� ������ �ִ� ��� 
		h->first = NULL;
		free(n);
	}

	while (n->link != NULL) {
		trail = n;
		n = n->link;
	}
	trail->link = NULL;
	free(n);

	return 0;
}

// �� �Լ��� �޴� e�� ������ �� ����ϴ� �Լ��Դϴ�. �������� ��ġ�� ��带 �����մϴ�.
// �Լ��� �ڼ��� ���캸��  headnode ����ü ������ ���� h�� ����մϴ�.
// ����  h->first�� NULL���� ��, ù��° ��尡 ����ִ� ��� ����ִٴ� �޽����� ����մϴ�.
// �׷��� �ʴٸ� listNode������ n�� trail�� �����Ͽ� h->fitst�� �־��ݴϴ�. �̶� n�� ������ ���, trail�� ������ ����� �� ����Դϴ�.
// �������� ��尡 �� ������ �ִ� ��� h->first = NULL�� ����� �����ϰ� n�� �����մϴ�.
// �׷��� �ʴٸ� n->link�� NULL�� ���� ��, n�� ����ؼ� ���� ���� �̵��ϸ鼭 n�� ������ ��尡 �� ������ �ݺ����� �����մϴ�.
// �ݺ��������� trail�� ����ؼ� n�� �������, n�� ����ؼ� ���� ���� �̵��մϴ�.
// �ݺ����� ���������� n�� ������ ����� �ǹ��Դϴ�. �̶� trail->link = NULL�� ���� ������ ����� �� ����� link�� �����ϴ�.
// �׸��� ������ ��带 ����Ű�� �ִ� n�� ���������ָ� ������ ��尡 ������ϴ�.


/**
 * ����Ʈ�� ��ũ�� �������� �� ��ġ
 */
int invertList(headNode* h) {


	if (h->first == NULL) {
		printf("nothing to invert...\n");
		return 0;
	}
	listNode* n = h->first;
	listNode* trail = NULL;
	listNode* middle = NULL;

	while (n != NULL) {
		trail = middle;
		middle = n;
		n = n->link;
		middle->link = trail;
	}

	h->first = middle;

	return 0;
}

// �� �Լ��� �޴� r�� ������ �� ����ϴ� �Լ��Դϴ�. ����Ʈ�� ��ũ�� ������ ���ġ�մϴ�.
// �Լ��� �ڼ��� ���캸��  headnode ����ü ������ ���� h�� ����մϴ�.
// ����  h->first�� NULL���� ��, ù��° ��尡 ����ִ� ��� ����ִٴ� �޽����� ����մϴ�.
// �׷��� �ʴٸ� listNode������ n, trail, middle�� �����Ͽ� n���� h->fitst�� trail�� middle���� NULL�� �־��ݴϴ�.
// �̶� ������ n, middle, trail ������ �̾����ϴ�. �ݺ����� ���鼭 ��� �� ���� ���� ���� �̵��ϸ鼭 middle->link�� trail�� �־��ݴϴ�.
// �׸��� �ٽ� ���� ���� �Ƶ��� �� n�� NULL�� �� ������ �ݺ��ϸ� ��� ����� link������ ���������ϴ�. 
// ���������� h->first�� ���� middle�� ���־� �������մϴ�.


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if (h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while (p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->link;
		i++;
	}

	printf("  items = %d\n", i);
}

// �� �Լ��� �޴� p�� ������ �� ����ϴ� �Լ��Դϴ�. ����Ʈ ������ ������ ����մϴ�.
// �Լ��� �ڼ��� ���캸��  headnode ����ü ������ ���� h�� ����մϴ�. 
// �Լ��� ó���� ����� ������ �� i�� listNode������ p�� �����մϴ�.
// �������� h == NULL�� ��� ��, headNode�� ����ִ� ��� ����ִٴ� �޽����� ����մϴ�.
// �׷��� �ʴٸ� p�� h->first���� �ְ�, p�� �������� �̵��ϸ� �ݺ����� �̿��Ͽ� list�� ��� ��忡 �����մϴ�.
// �ݺ��� �ȿ��� ����� Ű�� �����Ͽ� ����մϴ�. ���ÿ� p�� ���� ���� �̵��ϰ�, i�� ���� ��� �÷��ݴϴ�.
// ���������� i���� �̿��Ͽ� list�� ��� ������ ����մϴ�.