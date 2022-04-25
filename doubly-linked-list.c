/*
 *  doubly-linked-list.c
 *
 *  Doubly Linked List
 *
 *  Data Structures
 *  Department of Computer Science
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>
 /* �ʿ��� ������� �߰� if necessary */


typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;



typedef struct Head {
	struct Node* first;
}headNode;

/* �Լ� ����Ʈ */

int initialize(headNode** h);
int freeList(headNode* h);
int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);
int insertFirst(headNode* h, int key);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int deleteFirst(headNode* h);
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
		printf("                     Doubly Linked  List                        \n");
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
			initialize(&headnode);
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


int initialize(headNode** h) {

	/* headNode�� NULL�� �ƴϸ�, freeNode�� ȣ���Ͽ� �Ҵ�� �޸� ��� ���� */
	if (*h != NULL)
		freeList(*h);

	/* headNode�� ���� �޸𸮸� �Ҵ��Ͽ� ���� */
	*h = (headNode*)malloc(sizeof(headNode));
	(*h)->first = NULL;
	return 1;
}

// �� �Լ��� �޴����� z�� ������ �� ����ϴ� �Լ��Դϴ�. headNode�� NULL�� �ƴϸ�, freeNode�� ȣ���Ͽ� �Ҵ�� �޸� ��� �����մϴ�.
// �׷��� �ʴٸ� headNode�� ���� �޸𸮸� �Ҵ��Ͽ� �����Ͽ� ������ node�� ����� �� �ְ� ����ϴ�.
// �Լ��� �ڼ��� ���캸�� headnode ����ü ������ ���� h�� ����մϴ�.
// ���� headNode�� NULL�� �ƴϸ� h�� freeList�Լ��� ���� �޸𸮸� ��� �����մϴ�.
// �׷��� �ʴٸ� temp�� �޸𸮸� �������� �Ҵ��մϴ�. �̴� headNode�� ���� �޸𸮸� �Ҵ��߰� temp->first�� NULL������ �ʱ�ȭ �� �� �����߽��ϴ�.

// ���忡 �� �Լ��� �ڼ��� ���캸�� �Ű������� double�����ͷ� �ް� �ֽ��ϴ�. single �������� ���� �ٲٱ� ���� doeble������ �Ű������� ���� ���Դϴ�.
// �׷��� 
/* note: initialize�� ���������͸� �Ű������� ����
		 lab3�� initialize�� �������� ���� �Ұ� */

int freeList(headNode* h) {
	/* h�� ����� listNode �޸� ����
	 * headNode�� �����Ǿ�� ��.
	 */
	listNode* p = h->first;

	listNode* prev = NULL;
	while (p != NULL) {
		prev = p;
		p = p->rlink;
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

// ���忡
/* note: freeList�� �̱������͸� �Ű������� ����
-initialize�� �� �ٸ��� ���� �Ұ�
- ���������͸� �Ű������� �޾Ƶ� ������ �� ���� �� */




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
		p = p->rlink;
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

// ���忡 �� �Լ��� singly linked list�� �ٸ��� �ʽ��ϴ�. �ֳ��ϸ� �� ����Ʈ ������ link�� �� ���� �þ ������ ��� ���� ������ ������ ���� �����Դϴ�.
// ���� ����� ���� ������ ����ϴ� doubly linked list���� printList�Լ��� singly linked list�� �ٸ��� �ʽ��ϴ�.



/**
 * list�� key�� ���� ����ϳ��� �߰�
 */
int insertLast(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->rlink = NULL;
	node->llink = NULL;

	if (h->first == NULL)
	{
		h->first = node;
		return 0;
	}

	listNode* n = h->first;
	while (n->rlink != NULL) {
		n = n->rlink;
	}
	n->rlink = node;
	node->llink = n;
	return 0;
}

// �� �Լ��� �޴� n�� ������ �� �����ϴ� �Լ��Դϴ�. �Է¹��� key���� ���� ���ڸ��� �����մϴ�.
// �Լ��� �ڼ��� ���캸�� headnode ����ü ������ ���� h�� key���� �Լ� ���ڷ� ����ϰ� �ֽ��ϴ�.
// �Լ� ó���� �Է��� key�� ���� node�� �޸𸮸� �������� �Ҵ��մϴ�. �׸��� key���� �Է¹��� ���� �ְ� �� link�� ��� NULL�� �־��ݴϴ�.
// �������� h->first�� NULL ������ ��, ù ��° ��忡 �ƹ��͵� ������ Ȯ���ϰ� ���� �׷��ٸ� h->first�� node�� �־� node�� ù��° ������ �ٲ��ݴϴ�.
// �׷��� �۴ٸ� listnode����ü ������ ������ ���� n�� first�� �־�Ӵϴ�. �̶� n�� list�� ��� Ȯ���Ͽ� ������ ��尡 ������� Ȯ���ϴ� ������ �մϴ�.
// �׷��� n�� rlink�� NULL���� ������ ������ ��, n�� ���� ������ ��尡 �� �� ���� n = n->rlink�� ���� n�� ��� ���� ���� �̵��ϰ� �մϴ�.
// �׸��� �ݺ����� �����ٸ� n�� ���� ���ڸ� ����� �����̹Ƿ� n�� rlink�� node�� �Ҵ��ϸ� node�� ���� �������� ���Ե� �� �ֽ��ϴ�.
// ���������� node�� llink�� �������� �ʾұ⿡ n���� �����ָ� node�� ������ ��忡 ���� �̾����ϴ�.

// ���忡 ó���� insertFirst�� �޸� �� link�� NULL�� ���� ������ ������ ���� ���⿡ rlink�� NULL�̰�,
// llink�� ���� ���������� �� ��° ��忡 �������� �ʾұ⿡ ���� �Ҵ��� �� ���� �����Դϴ�.


/**
 * list�� ������ ��� ����
 */
int deleteLast(headNode* h) {

	if (h->first == NULL)
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first;
	listNode* trail = NULL;

	/* ��尡 �ϳ��� �ִ� ���, �� first node == last node��  ��� ó�� */
	if (n->rlink == NULL) {
		h->first = NULL;
		free(n);
		return 0;
	}

	/* ������ ������ �̵� */
	while (n->rlink != NULL) {
		trail = n;
		n = n->rlink;
	}

	/* n�� �����ǹǷ�, ���� ����� ��ũ NULL ó�� */
	trail->rlink = NULL;
	free(n);

	return 0;
}

// �� �Լ��� �޴� e�� ������ �� ����ϴ� �Լ��Դϴ�. �������� ��ġ�� ��带 �����մϴ�.
// �Լ��� �ڼ��� ���캸��  headnode ����ü ������ ���� h�� ����մϴ�.
// ����  h->first�� NULL���� ��, ù��° ��尡 ����ִ� ��� ����ִٴ� �޽����� ����մϴ�.
// �׷��� �ʴٸ� listNode������ n�� trail�� �����Ͽ� ���� h->fitst, NULL�� �־��ݴϴ�. �̶� n�� ������ ���, trail�� ������ ����� �� ����Դϴ�.
// �������� n->rlink = NULL�� ��� �� ��尡 �ϳ��� �ִ� ���� h->first = NULL�� ����� �����ϰ� n�� �����մϴ�.
// ������ ������� ù ��° ��带 ���ְ� �޸𸮸� �����ؾ� �ϱ� �����Դϴ�.
// �׷��� �ʴٸ� n->rlink�� NULL�� �ƴ� ���� ��, n�� ����ؼ� ���� ���� �̵��ϸ鼭 n�� ������ ��尡 �� ������ �ݺ����� �����մϴ�.
// �ݺ������� trail�� ����ؼ� n�� �������, n�� ����ؼ� ���� ���� �̵��մϴ�.
// �ݺ����� ���������� n�� ������ ����� �ǹ��Դϴ�. �̶� trail->rlink = NULL�� ���� ������ ����� �� ����� link�� �����ϴ�.
// �����Ǵ� ��� n�� �������Ƿ� �� ���� ��� trail�� rlink�� NULL ó�� �ϴ� ���Դϴ�.
// �׸��� ������ ��带 ����Ű�� �ִ� n�� ���������ָ� ������ ��� ������ ����Ǿ��ٰ� �� �� �ֽ��ϴ�.


/**
 * list ó���� key�� ���� ����ϳ��� �߰�
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->rlink = node->llink = NULL;

	if (h->first == NULL)
	{
		h->first = node;
		return 1;
	}

	node->rlink = h->first;
	node->llink = NULL;

	listNode* p = h->first;
	p->llink = node;
	h->first = node;

	return 0;
}

// �� �Լ��� �޴����� f�� ������ �� ����ϴ� �Լ��Դϴ�. key���� �Է¹޾Ƽ� ���� �տ� �����մϴ�.
// �Լ��� �ڼ��� ���캸�� headnode ����ü ������ ���� h�� key���� �Լ� ���ڷ� ����ϰ� �ֽ��ϴ�.
// �Լ� ó���� �Է��� key�� ���� node�� �޸𸮸� �������� �Ҵ��մϴ�. 
// �׸��� node�� key���� �Է¹��� ���� �ְ� node�� rlink�� llink�� NULL�� �ʱ�ȭ �մϴ�.
// �������� h->first�� NULL�� �� ��, ó���� ������� �� h->first = node�� ���� node�� ó������ �����ϴ�.
// �׷��� �ʴٸ� node�� rlink�� h->first��, node�� llink�� NULL�� �����ϴ�.
// �̷��� �ϸ� node�� ���� ���� ������ ���Խ��ϴ�. 
// ������ node�� h->first�� ���°� ������ �ʾұ⿡ �� ��°�� �ְ�, �� ��° ����� llink�� �ƹ��͵� ����Ű�� �ʰ� �˴ϴ�.
// �̸� �ذ��ϱ� ���� listNode ������ ������ ���� p�� h->first�� ����� p�� llink�� node�� �����, h->first�� node�� ����� �˴ϴ�.

// ���忡 ���⼭ link�� �� ���� ������ doubly linked list�̱� ������ ������ ������ ����ü�� ���� ���ʰ� ���������� ��� ������ �� �ִ� ��带 ������� �����Դϴ�.

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
	h->first = n->rlink;

	free(n);

	return 0;
}

// �� �Լ��� �޴� t�� ������ �� �����ϴ� �Լ��Դϴ�. list�� ù��° ��带 �����մϴ�.
// �Լ��� �ڼ��� ���캸��  headnode ����ü ������ ���� h�� ����մϴ�.
// ���� h->first�� NULL���� ��, ù��° ��尡 ����ִ� ��� ����ִٴ� �޽����� ����մϴ�.
// �׷��� �ʴٸ� listNode ������ ������ ���� n�� �����Ͽ� h->first�� �ֽ��ϴ�. �� ���¸� n�� ���� ó���� �ִ� ����Դϴ�.
// �׸��� h->first�� n->rlink�� �ű�ϴ�. �׷��� n�� ���� ���� h->first�� �˴ϴ�. �׸��� n�� free�Լ��� �����ϸ� �ٽ� h->first�� ó�� ��尡 �˴ϴ�.
// �̷��� �ϸ� ����� ù ��° ���� ������ϴ�.


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
		n = n->rlink;
		middle->rlink = trail;
		middle->llink = n;
	}

	h->first = middle;

	return 0;
}

// �� �Լ��� �޴� r�� ������ �� ����ϴ� �Լ��Դϴ�. ����Ʈ�� ��ũ�� ������ ���ġ�մϴ�.
// �Լ��� �ڼ��� ���캸��  headnode ����ü ������ ���� h�� ����մϴ�.
// ����  h->first�� NULL���� ��, ù��° ��尡 ����ִ� ��� ����ִٴ� �޽����� ����մϴ�.
// �׷��� �ʴٸ� listNode������ n, trail, middle�� �����Ͽ� n���� h->fitst��, trail�� middle���� NULL�� �־��ݴϴ�.
// �̶� ������ n, middle, trail ������ �̾����ϴ�. �������� �ݺ����� ���� ��� �� ĭ�� ���� ���� �̵��ϸ鼭 middle->rlink�� trail�� �־��ݴϴ�.
// ���� middle->llink ���� n�� �־��ݴϴ�. 
// �׸��� �ٽ� ���� ���� �̵��� �� n�� NULL�� �� ������ �ݺ��ϸ� ��� ����� link������ ���������ϴ�. 
// ���������� �ݺ����� ������ h->first�� ���� middle�� ���־� �������մϴ�.

//���忡 �ݺ��� ù 3���� �������� �̵�, �������� ���ִ� ���� �����̶� ���� ���� ��


/* ����Ʈ�� �˻��Ͽ�, �Է¹��� key���� ū���� ������ ��� �ٷ� �տ� ���� */
int insertNode(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->llink = node->rlink = NULL;

	if (h->first == NULL)
	{
		h->first = node;
		return 0;
	}

	listNode* n = h->first;

	/* key�� �������� ������ ��ġ�� ã�´� */
	while (n != NULL) {
		if (n->key >= key) {
			/* ù ��� ���ʿ� �����ؾ��� ��� ���� �˻� */
			if (n == h->first) {
				insertFirst(h, key);
			}
			else { /* �߰��̰ų� �������� ��� */
				node->rlink = n;
				node->llink = n->llink;
				n->llink->rlink = node;
			}
			return 0;
		}

		n = n->rlink;
	}

// �� �Լ��� �޴����� i�� ������ �� ����ϴ� �Լ��Դϴ�. key���� �Է¹޾Ƽ� key���� ū���� ������ ��� �ٷ� �տ� �����մϴ�.
// �Լ��� �ڼ��� ���캸�� headnode ����ü ������ ���� h�� key���� �Լ� ���ڷ� ����ϰ� �ֽ��ϴ�.
// �Լ� ó���� �Է��� key�� ���� node�� �޸𸮸� �������� �Ҵ��մϴ�. �׸��� key���� �Է¹��� ���� �ְ� llink�� rlink���� NULL�� �־��ݴϴ�.
// �������� h->first�� NULL���� ��, ù��° ���� ����ִ��� Ȯ���մϴ�. ����ִ� ���� Ȯ���ߴٸ� ù��° ������ node�� �־��ִ� �۾��� �մϴ�.

// ���� ù��° ���� ������� �ʴٸ� listnode����ü ������ n�� �����Ͽ� first�� �־�Ӵϴ�.
// �̶� n�� ���� �� ��ġ�� ���� ��ġ�� �����߽��ϴ�.
// �������� �ݺ����� �����ϴµ�, ���� �ڵ带 ���� �ݺ����� �� ������ n = n->rlink; �ڵ尡 �ݺ��˴ϴ�.
// �ٽ� ���� �ڵ带 ���캸�� n�� ���� ������ �̵��ϴٰ� NULL���� ������ ������ �ݺ����� �����մϴ�. 
// �׸��� n�� ���� ������ �̵��ϸ鼭 �Է¹��� key�� ���� ����ؼ� �����ִ� ������ �մϴ�. 
// �̶� �Է¹��� ���� ������ ������ ���� ��쿡 ù ��� ����, �߰��̰ų� �������� ��츦 ������ �����մϴ�.
// node�� ù ��° ��� �������� ���� ��� insertFirst()�Լ��� �̿��մϴ�.
// node�� �߰��̳� �������� ���� ��� node�� rlink�� n���� llink�� n->llink�� �Ӵϴ�.
// �ٽ� ����ϸ� ����ؼ� �����ϴ� n�� �߰��̳� �������� ���� �Ѵٸ� �Է� ��� node�� ���������δ� n, �������δ� n�� llink�� �ֽ��ϴ�.
// �̷��� �ϸ� node�� ���ʰ��� �̾����ִ� �� ���� �� �̾����ֽ��ϴ�. �׷��� ���������� n->llink->rlink = node;�� ���� �̾��ݴϴ�.
// 
// ���忡 trail ���� �� �� ������ ������ �����ʰ� ���� ��� link�� ������ �ֱ⿡ ������ ���鿡 ��� ������ �� �ֱ� �����Դϴ�.
// �ݺ������� ����Ǵ� n = n->rlink; �ڵ�� n�� ����ؼ� ���� ���� �Ѿ�ٴ� �ǹ��Դϴ�.

	/* ������ ������ ã�� ���� ���, �������� ���� */
	insertLast(h, key);
	return 0;
}


/**
 * list���� key�� ���� ��� ����
 */
int deleteNode(headNode* h, int key) {

	if (h->first == NULL)
	{
		printf("nothing to delete.\n");
		return 1;
	}

	listNode* n = h->first;

	while (n != NULL) {
		if (n->key == key) {
			if (n == h->first) { /* ù ���° ��� �ΰ�� */
				deleteFirst(h);
			}
			else if (n->rlink == NULL) { /* ������ ����� ��� */
				deleteLast(h);
			}
			else { /* �߰��� ��� */
				n->llink->rlink = n->rlink;
				n->rlink->llink = n->llink;
				free(n);
			}
			return 1;
		}

		n = n->rlink;
	}

	/* ã�� �� �Ѱ�� */
	printf("cannot find the node for key = %d\n", key);
	return 1;
}

// �� �Լ��� �޴����� d�� ������ �� ����ϴ� �Լ��Դϴ�. key���� �Է¹޾Ƽ� �� ���� ���� key���� ���� ��带 �����մϴ�..
// �Լ��� �ڼ��� ���캸�� headnode ����ü ������ ���� h�� key���� �Լ� ���ڷ� ����ϰ� �ֽ��ϴ�.
// �Լ� ó���� h->first�� NULL���� ��, ù��° ���� ����ִ� ��� ����ִٴ� �޽����� ����մϴ�.
// ������� �ʴٸ� listNode���� n�� �����Ͽ� ���� h->fitst�� �־��ݴϴ�.
// �̶� n�� ������ ����� �����߽��ϴ�.
// �������� �ݺ����� �����ϴµ�, ���� �ڵ带 ���� �ݺ����� �� ������ n = n->rlink; �ڵ尡 �ݺ��˴ϴ�.
// �ٽ� ���� �ڵ带 ���캸�� n�� NULL�� �ƴ� ���� ��, n�� ��� ��带 �� �����ϴ� ���� �ݺ����� �����մϴ�.
// n�� ��带 �ϳ��� �����ϴ� ���� n->key�� �Է¹��� key�� ���� ���� ���, ù ��°, ������, �߰� 3���� ��츦 ���������ϴ�.
// ���� �Է¹��� ���� ù ��° ����� key���� ���� ��� deleteFirst()�Լ��� ����Ͽ� ó�� ����� ���� �����մϴ�.
// �������� �Է¹��� ���� ������ ����� key���� ���� ��� deleteLast()�Լ��� ����Ͽ� ������ ����� ���� �����մϴ�.
// ���������� �Է¹��� ���� ��ġ�ϴ� ��尡 �߰��� ��� n->llink->rlink = n->rlink;�� n->rlink->llink = n->llink;�� �����մϴ�.
// �̸� �����ϸ� n�� rlink�� �� ���� rlink��, n�� llink�� �������� llink�� �ֽ��ϴ�. 
// �׸��� free(n)�� ���� n�� �޸� ������ �Ͽ� ��带 ������� ����ϴ�.
// ���� ã�� ���ߴٸ� key�� ���� ã�� �� ���ٴ� �޽����� ����մϴ�.

// ���忡 trail ���� �� �� ������ ������ �����ʰ� ���� ��� link�� ������ �ֱ⿡ ������ ���鿡 ��� ������ �� �ֱ� �����Դϴ�.
// �ݺ������� ����Ǵ� n = n->rlink; �ڵ�� n�� ����ؼ� ���� ���� �Ѿ�ٴ� �ǹ��Դϴ�.