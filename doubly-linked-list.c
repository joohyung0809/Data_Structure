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
 /* 필요한 헤더파일 추가 if necessary */


typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;



typedef struct Head {
	struct Node* first;
}headNode;

/* 함수 리스트 */

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
	printf("[----- [오주형][2019023028] ----- ]\n");

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

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if (*h != NULL)
		freeList(*h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (headNode*)malloc(sizeof(headNode));
	(*h)->first = NULL;
	return 1;
}

// 이 함수는 메뉴에서 z를 눌렀을 때 사용하는 함수입니다. headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제합니다.
// 그렇지 않다면 headNode에 대한 메모리를 할당하여 리턴하여 앞으로 node를 사용할 수 있게 만듭니다.
// 함수를 자세히 살펴보면 headnode 구조체 포인터 변수 h를 사용합니다.
// 먼저 headNode가 NULL이 아니면 h를 freeList함수를 통해 메모리를 모두 해제합니다.
// 그렇지 않다면 temp의 메모리를 동적으로 할당합니다. 이는 headNode에 대한 메모리를 할당했고 temp->first를 NULL값으로 초기화 한 후 리턴했습니다.

// 워드에 이 함수를 자세히 살펴보면 매개변수를 double포인터로 받고 있습니다. single 포인터의 값을 바꾸기 위해 doeble포인터 매개변수를 받은 것입니다.
// 그래서 
/* note: initialize는 이중포인터를 매개변수로 받음
		 lab3의 initialize와 차이점을 이해 할것 */

int freeList(headNode* h) {
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
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

// 이 함수는 메뉴에서 q를 눌렀을 때 사용하는 함수입니다. h와 연결된 listNode 메모리 와 headNode를 해제합니다.
// 함수를 자세히 살펴보면 headnode 구조체 포인터 변수 h를 사용합니다.
// 함수 처음에 listnode구조체 형태의 p와 prev를 선언하여 p는 first로 prev는 NULL로 넣어둡니다.
// 이때 p는 모든 노드에 접근하는 역할을 합니다. 그리고 prev는 p가 node를 돌면 그 값을 받아 free로 해제합니다.
// 그래서 반복문을 통해 모든 노드를 접근하여 메모리를 해제한 후 마지막으로 headNode인 h를 해제합니다.

// 워드에
/* note: freeList는 싱글포인터를 매개변수로 받음
-initialize와 왜 다른지 이해 할것
- 이중포인터를 매개변수로 받아도 해제할 수 있을 것 */




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

// 이 함수는 메뉴 p를 눌렀을 때 사용하는 함수입니다. 리스트 노드들의 내용을 출력합니다.
// 함수를 자세히 살펴보면  headnode 구조체 포인터 변수 h를 사용합니다. 
// 함수의 처음에 노드의 개수를 셀 i와 listNode형태의 p를 선언합니다.
// 다음으로 h == NULL인 경우 즉, headNode가 비어있는 경우 비어있다는 메시지를 출력합니다.
// 그렇지 않다면 p에 h->first값을 넣고, p가 다음노드로 이동하며 반복문을 이용하여 list의 모든 노드에 접근합니다.
// 반복문 안에서 노드의 키에 접근하여 출력합니다. 동시에 p는 다음 노드로 이동하고, i는 값을 계속 늘려줍니다.
// 마지막으로 i값을 이용하여 list의 노드 개수를 출력합니다.

// 워드에 이 함수는 singly linked list와 다르지 않습니다. 왜냐하면 이 리스트 노드들의 link가 두 개로 늘어난 것이지 노드 값의 개수는 변함이 없기 때문입니다.
// 따라서 노드의 값과 개수를 출력하는 doubly linked list에서 printList함수는 singly linked list와 다르지 않습니다.



/**
 * list에 key에 대한 노드하나를 추가
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

// 이 함수는 메뉴 n을 눌렀을 때 실행하는 함수입니다. 입력받은 key값을 가장 마자막에 삽입합니다.
// 함수를 자세히 살펴보면 headnode 구조체 포인터 변수 h와 key값을 함수 인자로 사용하고 있습니다.
// 함수 처음에 입력한 key를 넣을 node의 메모리를 동적으로 할당합니다. 그리고 key값엔 입력받은 값을 넣고 두 link에 모두 NULL을 넣어줍니다.
// 다음으로 h->first가 NULL 값인지 즉, 첫 번째 노드에 아무것도 없는지 확인하고 만약 그렇다면 h->first에 node를 넣어 node를 첫번째 값으로 바꿔줍니다.
// 그렇지 앟다면 listnode구조체 형태의 포인터 변수 n을 first로 넣어둡니다. 이때 n은 list를 모두 확인하여 마지막 노드가 어디인지 확인하는 역할을 합니다.
// 그래서 n의 rlink가 NULL값을 가지기 전까지 즉, n이 가장 마지막 노드가 될 때 까지 n = n->rlink를 통해 n을 계속 다음 노드로 이동하게 합니다.
// 그리고 반복문이 끝난다면 n이 가장 마자막 노드인 상태이므로 n의 rlink를 node로 할당하면 node가 가장 마지막에 삽입될 수 있습니다.
// 마지막으로 node의 llink가 정해지지 않았기에 n으로 정해주면 node가 마지막 노드에 놓여 이어집니다.

// 워드에 처음에 insertFirst와 달리 두 link에 NULL을 넣은 이유는 마지막 노드로 들어가기에 rlink는 NULL이고,
// llink는 아직 마지막에서 두 번째 노드에 접근하지 않았기에 당장 할당할 수 없기 때문입니다.


/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {

	if (h->first == NULL)
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first;
	listNode* trail = NULL;

	/* 노드가 하나만 있는 경우, 즉 first node == last node인  경우 처리 */
	if (n->rlink == NULL) {
		h->first = NULL;
		free(n);
		return 0;
	}

	/* 마지막 노드까지 이동 */
	while (n->rlink != NULL) {
		trail = n;
		n = n->rlink;
	}

	/* n이 삭제되므로, 이전 노드의 링크 NULL 처리 */
	trail->rlink = NULL;
	free(n);

	return 0;
}

// 이 함수는 메뉴 e를 눌렀을 때 사용하는 함수입니다. 마지막에 위치한 노드를 삭제합니다.
// 함수를 자세히 살펴보면  headnode 구조체 포인터 변수 h를 사용합니다.
// 먼저  h->first가 NULL인지 즉, 첫번째 노드가 비어있는 경우 비어있다는 메시지를 출력합니다.
// 그렇지 않다면 listNode형태의 n과 trail을 선언하여 각각 h->fitst, NULL을 넣어줍니다. 이때 n은 삭제할 노드, trail은 삭제할 노드의 전 노드입니다.
// 다음으로 n->rlink = NULL인 경우 즉 노드가 하나만 있는 경우는 h->first = NULL로 만들어 삭제하고 n을 해제합니다.
// 마지막 노드이자 첫 번째 노드를 없애고 메모리를 해제해야 하기 때문입니다.
// 그렇지 않다면 n->rlink가 NULL이 아닌 동안 즉, n이 계속해서 다음 노드로 이동하면서 n이 마지막 노드가 될 때까지 반복문을 실행합니다.
// 반복문에서 trail은 계속해서 n을 따라오고, n은 계속해서 다음 노드로 이동합니다.
// 반복문을 빠져나오면 n이 마지막 노드라는 의미입니다. 이때 trail->rlink = NULL을 통해 마지막 노드의 전 노드의 link를 끊습니다.
// 삭제되는 노드 n이 없어지므로 그 이전 노드 trail의 rlink를 NULL 처리 하는 것입니다.
// 그리고 삭제할 노드를 가리키고 있는 n을 해제시켜주면 마지막 노드 삭제가 실행되었다고 할 수 있습니다.


/**
 * list 처음에 key에 대한 노드하나를 추가
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

// 이 함수는 메뉴에서 f를 눌렀을 때 사용하는 함수입니다. key값을 입력받아서 가장 앞에 삽입합니다.
// 함수를 자세히 살펴보면 headnode 구조체 포인터 변수 h와 key값을 함수 인자로 사용하고 있습니다.
// 함수 처음에 입력한 key를 넣을 node의 메모리를 동적으로 할당합니다. 
// 그리고 node의 key값엔 입력받은 값을 넣고 node의 rlink와 llink를 NULL로 초기화 합니다.
// 다음으로 h->first가 NULL일 때 즉, 처음이 비어있을 때 h->first = node를 통해 node를 처음으로 보냅니다.
// 그렇지 않다면 node의 rlink를 h->first로, node의 llink를 NULL로 보냅니다.
// 이렇게 하면 node의 값이 가장 앞으로 들어왔습니다. 
// 하지만 node의 h->first의 상태가 변하지 않았기에 두 번째에 있고, 두 번째 노드의 llink가 아무것도 가리키지 않게 됩니다.
// 이를 해결하기 위해 listNode 형태의 포인터 변수 p를 h->first로 만들어 p의 llink를 node로 만들고, h->first를 node로 만들면 됩니다.

// 워드에 여기서 link가 두 개인 이유는 doubly linked list이기 때문에 위에서 선언한 구조체와 같이 왼쪽과 오른쪽으로 모두 접근할 수 있는 노드를 만들었기 때문입니다.

/**
 * list의 첫번째 노드 삭제
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

// 이 함수는 메뉴 t를 눌렀을 때 실행하는 함수입니다. list의 첫번째 노드를 삭제합니다.
// 함수를 자세히 살펴보면  headnode 구조체 포인터 변수 h를 사용합니다.
// 먼저 h->first가 NULL인지 즉, 첫번째 노드가 비어있는 경우 비어있다는 메시지를 출력합니다.
// 그렇지 않다면 listNode 형태의 포인터 변수 n을 선언하여 h->first를 넣습니다. 이 상태면 n이 가장 처음에 있는 노드입니다.
// 그리고 h->first를 n->rlink로 옮깁니다. 그러면 n의 다음 노드는 h->first가 됩니다. 그리고 n을 free함수로 해제하면 다시 h->first는 처음 노드가 됩니다.
// 이렇게 하면 노드의 첫 번째 값이 사라집니다.


/**
 * 리스트의 링크를 역순으로 재 배치
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

// 이 함수는 메뉴 r를 눌렀을 때 사용하는 함수입니다. 리스트의 링크를 역순을 재배치합니다.
// 함수를 자세히 살펴보면  headnode 구조체 포인터 변수 h를 사용합니다.
// 먼저  h->first가 NULL인지 즉, 첫번째 노드가 비어있는 경우 비어있다는 메시지를 출력합니다.
// 그렇지 않다면 listNode형태의 n, trail, middle을 선언하여 n에는 h->fitst을, trail과 middle에는 NULL을 넣어줍니다.
// 이때 순서는 n, middle, trail 순으로 이어집니다. 다음으로 반복문을 돌며 모두 한 칸씩 다음 노드로 이동하면서 middle->rlink에 trail을 넣어줍니다.
// 또한 middle->llink 에는 n을 넣어줍니다. 
// 그리고 다시 다음 노드로 이동한 후 n이 NULL이 될 때까지 반복하면 모든 노드의 link방향이 뒤집어집니다. 
// 마지막으로 반복문이 끝나면 h->first의 값을 middle로 해주어 마무리합니다.

//워드에 반복문 첫 3줄은 다음으로 이동, 마지막에 해주는 이유 저번이랑 같게 쓰면 됨


/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
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

	/* key를 기준으로 삽입할 위치를 찾는다 */
	while (n != NULL) {
		if (n->key >= key) {
			/* 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 */
			if (n == h->first) {
				insertFirst(h, key);
			}
			else { /* 중간이거나 마지막인 경우 */
				node->rlink = n;
				node->llink = n->llink;
				n->llink->rlink = node;
			}
			return 0;
		}

		n = n->rlink;
	}

// 이 함수는 메뉴에서 i를 눌렀을 때 사용하는 함수입니다. key값을 입력받아서 key보다 큰값이 나오는 노드 바로 앞에 삽입합니다.
// 함수를 자세히 살펴보면 headnode 구조체 포인터 변수 h와 key값을 함수 인자로 사용하고 있습니다.
// 함수 처음에 입력한 key를 넣을 node의 메모리를 동적으로 할당합니다. 그리고 key값엔 입력받은 값을 넣고 llink와 rlink에는 NULL을 넣어줍니다.
// 다음으로 h->first가 NULL인지 즉, 첫번째 값이 비어있는지 확인합니다. 비어있는 것을 확인했다면 첫번째 값으로 node를 넣어주는 작업을 합니다.

// 만약 첫번째 값이 비어있지 않다면 listnode구조체 형태의 n을 선언하여 first로 넣어둡니다.
// 이때 n은 들어가야 할 위치의 다음 위치로 생각했습니다.
// 다음으로 반복문을 실행하는데, 밑의 코드를 보면 반복문을 돌 때마다 n = n->rlink; 코드가 반복됩니다.
// 다시 위의 코드를 살펴보면 n이 다음 값으로 이동하다가 NULL값이 나오기 전까지 반복문을 실행합니다. 
// 그리고 n이 다음 값으로 이동하면서 입력받은 key의 값과 계속해서 비교해주는 역할을 합니다. 
// 이때 입력받은 값이 기존의 값보다 작은 경우에 첫 노드 앞쪽, 중간이거나 마지막인 경우를 나누어 생각합니다.
// node가 첫 번째 노드 앞쪽으로 들어가는 경우 insertFirst()함수를 이용합니다.
// node가 중간이나 마지막에 들어가는 경우 node의 rlink를 n으로 llink를 n->llink로 둡니다.
// 다시 얘기하면 계속해서 증가하던 n이 중간이나 마지막에 들어가야 한다면 입력 노드 node의 오른쪽으로는 n, 왼쪽으로는 n의 llink를 넣습니다.
// 이렇게 하면 node와 왼쪽값이 이어져있는 것 빼고 다 이어져있습니다. 그래서 마지막으로 n->llink->rlink = node;를 통해 이어줍니다.
// 
// 워드에 trail 선언 안 한 이유는 노드들이 오른쪽과 왼쪽 모두 link를 가지고 있기에 그전의 값들에 모두 접근할 수 있기 때문입니다.
// 반복문마다 실행되는 n = n->rlink; 코드는 n이 계속해서 다음 노드로 넘어간다는 의미입니다.

	/* 마지막 노드까지 찾지 못한 경우, 마지막에 삽입 */
	insertLast(h, key);
	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
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
			if (n == h->first) { /* 첫 노드째 노드 인경우 */
				deleteFirst(h);
			}
			else if (n->rlink == NULL) { /* 마지막 노드인 경우 */
				deleteLast(h);
			}
			else { /* 중간인 경우 */
				n->llink->rlink = n->rlink;
				n->rlink->llink = n->llink;
				free(n);
			}
			return 1;
		}

		n = n->rlink;
	}

	/* 찾지 못 한경우 */
	printf("cannot find the node for key = %d\n", key);
	return 1;
}

// 이 함수는 메뉴에서 d를 눌렀을 때 사용하는 함수입니다. key값을 입력받아서 그 값과 같은 key값을 가진 노드를 삭제합니다..
// 함수를 자세히 살펴보면 headnode 구조체 포인터 변수 h와 key값을 함수 인자로 사용하고 있습니다.
// 함수 처음에 h->first가 NULL인지 즉, 첫번째 값이 비어있는 경우 비어있다는 메시지를 출력합니다.
// 비어있지 않다면 listNode형태 n을 선언하여 각각 h->fitst을 넣어줍니다.
// 이때 n은 삭제할 노드라고 생각했습니다.
// 다음으로 반복문을 실행하는데, 밑의 코드를 보면 반복문을 돌 때마다 n = n->rlink; 코드가 반복됩니다.
// 다시 위의 코드를 살펴보면 n이 NULL이 아닌 동안 즉, n이 모든 노드를 다 접근하는 동안 반복문을 실행합니다.
// n이 노드를 하나씩 접근하는 동안 n->key가 입력받은 key의 값이 같은 경우, 첫 번째, 마지막, 중간 3가지 경우를 나누었습니다.
// 먼저 입력받은 값이 첫 번째 노드의 key값과 같은 경우 deleteFirst()함수를 사용하여 처음 노드의 값을 삭제합니다.
// 다음으로 입력받은 값이 마지막 노드의 key값과 같은 경우 deleteLast()함수를 사용하여 마지막 노드의 값을 삭제합니다.
// 마지막으로 입력받은 값과 일치하는 노드가 중간인 경우 n->llink->rlink = n->rlink;와 n->rlink->llink = n->llink;를 실행합니다.
// 이를 실행하면 n의 rlink를 전 값의 rlink로, n의 llink를 다음값의 llink로 넣습니다. 
// 그리고 free(n)을 통해 n의 메모리 해제를 하여 노드를 사라지게 만듭니다.
// 값을 찾지 못했다면 key의 값을 찾을 수 없다는 메시지를 출력합니다.

// 워드에 trail 선언 안 한 이유는 노드들이 오른쪽과 왼쪽 모두 link를 가지고 있기에 그전의 값들에 모두 접근할 수 있기 때문입니다.
// 반복문마다 실행되는 n = n->rlink; 코드는 n이 계속해서 다음 노드로 넘어간다는 의미입니다.