/*
 * singly linked list
 *
 *  Data Structures
 *  School of Computer Science
 *  at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>

 /* 필요한 헤더파일 추가 */

typedef struct Node {
	int key;
	struct Node* link;
} listNode;

typedef struct Head {
	struct Node* first;
}headNode;


/* 함수 리스트 */
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
	printf("[----- [오주형][2019023028] ----- ]\n");

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

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if (h != NULL)
		freeList(h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	return temp;
}

// 이 함수는 메뉴에서 z를 눌렀을 때 사용하는 함수입니다. headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제합니다.
// 그렇지 않다면 headNode에 대한 메모리를 할당하여 리턴하여 앞으로 node를 사용할 수 있게 만듭니다.
// 함수를 자세히 살펴보면 headnode 구조체 포인터 변수 h를 사용합니다.
// 먼저 headNode가 NULL이 아니면 h를 freeList함수를 통해 메모리를 모두 해제합니다.
// 그렇지 않다면 temp의 메모리를 동적으로 할당합니다. 이는 headNode에 대한 메모리를 할당했고 temp->first를 NULL값으로 초기화 한 후 리턴했습니다.


int freeList(headNode* h) {
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
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

// 이 함수는 메뉴에서 q를 눌렀을 때 사용하는 함수입니다. h와 연결된 listNode 메모리 와 headNode를 해제합니다.
// 함수를 자세히 살펴보면 headnode 구조체 포인터 변수 h를 사용합니다.
// 함수 처음에 listnode구조체 형태의 p와 prev를 선언하여 p는 first로 prev는 NULL로 넣어둡니다.
// 이때 p는 모든 노드에 접근하는 역할을 합니다. 그리고 prev는 p가 node를 돌면 그 값을 받아 free로 해제합니다.
// 그래서 반복문을 통해 모든 노드를 접근하여 메모리를 해제한 후 마지막으로 headNode인 h를 해제합니다.



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->link = h->first;

	h->first = node;

	return 0;
}

// 이 함수는 메뉴에서 f를 눌렀을 때 사용하는 함수입니다. key값을 입력받아서 가장 앞에 삽입합니다.
// 함수를 자세히 살펴보면 headnode 구조체 포인터 변수 h와 key값을 함수 인자로 사용하고 있습니다.
// 함수 처음에 입력한 key를 넣을 node의 메모리를 동적으로 할당합니다. 
// 그리고 key값엔 입력받은 값을 넣고 link에는 h->first를 넣어 가장 처음 값으로 바꿔줍니다.
// 다음으로 h->first에 node를 할당합니다. 이렇게 하면 입력받은 node가 가장 처음에 위치합니다.


/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
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
	listNode* trail = h->first;  //trail은 따라오는 자취라고 생각

	/* key를 기준으로 삽입할 위치를 찾는다 */
	while (n != NULL) {
		if (n->key >= key) {  //입력받은 값이 기존 값보다 더 작은 경우

			/* 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 */
			if (n == h->first) {  // 입력받은 값이 기존 값보다 더 작은 경우가 첫 번째 노드인 경우
				h->first = node; 
				node->link = n;  
			}
			else { /* 입력 받은 값이 기존 값보다 더 작은 경우가 중간이거나 마지막 노드인 경우 */
				node->link = n;
				trail->link = node;
			}
			return 0;
		}

		/* 반복문이 실행될 때마다 실행하는 코드 */
		trail = n; 
		n = n->link; 
	}

	/* 마지막 노드까지 찾지 못한 경우 , 마지막에 삽입 */
	trail->link = node; 
	return 0;
}

// 이 함수는 메뉴에서 i를 눌렀을 때 사용하는 함수입니다. key값을 입력받아서 key보다 큰값이 나오는 노드 바로 앞에 삽입합니다.
// 함수를 자세히 살펴보면 headnode 구조체 포인터 변수 h와 key값을 함수 인자로 사용하고 있습니다.
// 함수 처음에 입력한 key를 넣을 node의 메모리를 동적으로 할당합니다. 그리고 key값엔 입력받은 값을 넣고 link에는 NULL을 넣어줍니다.
// 다음으로 h->first가 NULL인지 즉, 첫번째 값이 비어있는지 확인합니다. 비어있는 것을 확인했다면 첫번째 값으로 node를 넣어주는 작업을 합니다.

// 만약 첫번째 값이 비어있지 않다면 listnode구조체 형태의 n,과 trail변수를 선언하여 모두 first로 넣어둡니다.
// 이때 n은 node가 들어갈 위치의 이후값, trail은 node가 들어갈 위치의 이전값으로 생각했습니다.
// 다음으로 반복문을 실행하는데, 밑의 코드를 보면 반복문을 돌 때마다trail = n;, n = n->link; 코드가 반복됩니다.
// 다시 위의 코드를 살펴보면 n이 다음 값으로 이동하다가 NULL값이 나오기 전까지 반복문을 실행합니다. 
// 그리고 n이 다음 값으로 이동하면서 입력받은 key의 값과 계속해서 비교해주는 역할을 합니다. 
// 이때 입력받은 값이 기존의 값보다 작은 경우에 첫 노드 앞쪽, 중간이거나 마지막인 경우를 나누어 생각합니다.
// node가 첫 번째 노드 앞쪽으로 들어가는 경우 h->first 가 node가 되고, node의 link 는 n으로 지정합니다.
// node가 중간이나 마지막에 들어가는 경우 node의 link를 n, n을 계속해서 따라오던 trail의 link는 node로 둡니다.
// 이렇게 하면 trail과 n사이에 node가 들어올 수 있게 됩니다. 
// 마지막으로 while문을 전부 돌았지만 입력받은 값이 기존값보다 작은 경우가 없을 때는 trail의 link에 node를 넣어 가장 끝에 노드를 삽입합니다.


/**
 * list에 key에 대한 노드하나를 추가
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

// 이 함수는 메뉴 n을 눌렀을 때 실행하는 함수입니다. 입력받은 key값을 가장 마자막에 삽입합니다.
// 함수를 자세히 살펴보면 headnode 구조체 포인터 변수 h와 key값을 함수 인자로 사용하고 있습니다.
// 함수 처음에 입력한 key를 넣을 node의 메모리를 동적으로 할당합니다. 그리고 key값엔 입력받은 값을 넣고 link에는 NULL을 넣어줍니다.
// 다음으로 h->first가 NULL 값인지 즉, 첫 번째 노드에 아무것도 없는지 확인하고 그렇다면 h->first에 node를 넣어 node를 첫번째 값으로 바꿔줍니다.
// 그렇지 앟다면 listnode구조체 형태의 n을 first로 넣어둡니다. 이때 n은 list를 모두 확인하여 마지막 노드가 어디인지 확인하는 역할을 합니다.
// 그래서 n의 link가 NULL값을 가지기 전까지 즉, n이 가장 마지막 노드가 될 때 까지 n = n->link를 통해 n을 계속 다음 노드로 이동하게 합니다.
// 그리고 반복문이 끝난다면 n이 가장 마자막 노드인 상태이므로 n의 link를 node로 할당하면 node가 가장 마지막에 삽입될 수 있습니다.


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

	h->first = n->link;
	free(n);

	return 0;
}

// 이 함수는 메뉴 t를 눌렀을 때 실행하는 함수입니다. list의 첫번째 노드를 삭제합니다.
// 함수를 자세히 살펴보면  headnode 구조체 포인터 변수 h를 사용합니다.
// 먼저 h->first가 NULL인지 즉, 첫번째 노드가 비어있는 경우 비어있다는 메시지를 출력합니다.
// 그렇지 않다면 listNode 형태의n을 선언하여 h->first를 넣습니다. 그리고 h->first를 n->link로 옮깁니다.
// 그러면 n 다음 노드는 h->first가 됩니다. 그리고 n을 free함수로 해제하면 다시 h->first는 처음 노드가 됩니다.
// 그리고 n은 사라지므로 list의 첫번째 노드가 삭제됩니다.

/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {

	if (h->first == NULL)
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first;
	listNode* trail = NULL;

	/* key를 기준으로 삭제할 위치를 찾는다 */
	while (n != NULL) {
		if (n->key == key) {
			/* 첫 노드를 삭제해야하는 경우 */
			if (n == h->first) {
				h->first = n->link;
			}
			else { /* 중간인 경우거나 마지막을 삭제해야하는 경우 */
				trail->link = n->link;
			}
			free(n);
			return 0;
		}

		trail = n;
		n = n->link;
	}

	/* 찾지 못 한경우 */
	printf("cannot find the node for key = %d\n", key);
	return 0;

}

// 이 함수는 메뉴에서 d를 눌렀을 때 사용하는 함수입니다. key값을 입력받아서 그 값과 같은 key값을 가진 노드를 삭제합니다..
// 함수를 자세히 살펴보면 headnode 구조체 포인터 변수 h와 key값을 함수 인자로 사용하고 있습니다.
// 함수 처음에 h->first가 NULL인지 즉, 첫번째 값이 비어있는 경우 비어있다는 메시지를 출력합니다.
// 비어있지 않다면 listNode형태의 n과 trail을 선언하여 각각 h->fitst와 NULL을 넣어줍니다.
// 이때 n은 삭제할 노드, trail은 삭제할 노드의 전 노드를 가리킵니다.
// 다음으로 반복문을 실행하는데, 밑의 코드를 보면 반복문을 돌 때마다trail = n;, n = n->link; 코드가 반복됩니다.
// 다시 위의 코드를 살펴보면 n이 NULL이 아닌 동안 즉, n이 모든 노드를 다 접근하는 동안 반복문을 실행합니다.
// n이 노드를 하나씩 접근하는 동안 n->key가 입력받은 key의 값이 같은 경우, 첫 번째 노드를 삭제하는 경우와 중간이거나 마지막인 경우를 나눠줍니다.
// 입력받은 값이 첫 번째 노드의 key값과 같은 경우 h->first를 n->link를 하고 조건문을 빠져나와 n을 해제시키면 첫번째 값이 없어집니다.
// 입력받은 값이 중간이나 마지막 노드의 key값과 같은 경우 trail->link를 n->link로 하고 조건문을 빠져나와 n을 해제시키면 원하는 노드가 사라집니다..
// 마지막으로 반복문을 모두 돌아도 일치하는 key값이 없는 경우 찾을 수 없다는 메시지를 출력합니다.


/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {
	if (h->first == NULL) {
		printf("nothing to delete\n");
		return 0;
	}

	listNode* n = h->first;
	listNode* trail = NULL;

	if (n->link == NULL) { //주의: 노드가 한 가지만 있는 경우 
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

// 이 함수는 메뉴 e를 눌렀을 때 사용하는 함수입니다. 마지막에 위치한 노드를 삭제합니다.
// 함수를 자세히 살펴보면  headnode 구조체 포인터 변수 h를 사용합니다.
// 먼저  h->first가 NULL인지 즉, 첫번째 노드가 비어있는 경우 비어있다는 메시지를 출력합니다.
// 그렇지 않다면 listNode형태의 n과 trail을 선언하여 h->fitst을 넣어줍니다. 이때 n은 삭제할 노드, trail은 삭제할 노드의 전 노드입니다.
// 다음으로 노드가 한 가지만 있는 경우 h->first = NULL로 만들어 삭제하고 n을 해제합니다.
// 그렇지 않다면 n->link가 NULL인 동안 즉, n이 계속해서 다음 노드로 이동하면서 n이 마지막 노드가 될 때까지 반복문을 실행합니다.
// 반복문에서는 trail은 계속해서 n을 따라오고, n은 계속해서 다음 노드로 이동합니다.
// 반복문을 빠져나오면 n이 마지막 노드라는 의미입니다. 이때 trail->link = NULL을 통해 마지막 노드의 전 노드의 link를 끊습니다.
// 그리고 삭제할 노드를 가리키고 있는 n을 해제시켜주면 마지막 노드가 사라집니다.


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
		n = n->link;
		middle->link = trail;
	}

	h->first = middle;

	return 0;
}

// 이 함수는 메뉴 r를 눌렀을 때 사용하는 함수입니다. 리스트의 링크를 역순을 재배치합니다.
// 함수를 자세히 살펴보면  headnode 구조체 포인터 변수 h를 사용합니다.
// 먼저  h->first가 NULL인지 즉, 첫번째 노드가 비어있는 경우 비어있다는 메시지를 출력합니다.
// 그렇지 않다면 listNode형태의 n, trail, middle을 선언하여 n에는 h->fitst을 trail과 middle에는 NULL을 넣어줍니다.
// 이때 순서는 n, middle, trail 순으로 이어집니다. 반복문을 돌면서 모두 한 간씩 다음 노드로 이동하면서 middle->link에 trail을 넣어줍니다.
// 그리고 다시 다음 노드로 아동한 후 n이 NULL이 될 때까지 반복하면 모든 노드의 link방향이 뒤집어집니다. 
// 마지막으로 h->first의 값을 middle로 해주어 마무리합니다.


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

// 이 함수는 메뉴 p를 눌렀을 때 사용하는 함수입니다. 리스트 노드들의 내용을 출력합니다.
// 함수를 자세히 살펴보면  headnode 구조체 포인터 변수 h를 사용합니다. 
// 함수의 처음에 노드의 개수를 셀 i와 listNode형태의 p를 선언합니다.
// 다음으로 h == NULL인 경우 즉, headNode가 비어있는 경우 비어있다는 메시지를 출력합니다.
// 그렇지 않다면 p에 h->first값을 넣고, p가 다음노드로 이동하며 반복문을 이용하여 list의 모든 노드에 접근합니다.
// 반복문 안에서 노드의 키에 접근하여 출력합니다. 동시에 p는 다음 노드로 이동하고, i는 값을 계속 늘려줍니다.
// 마지막으로 i값을 이용하여 list의 노드 개수를 출력합니다.