/*
 *  doubly circular linked list
 *
 *  Data Structures
 *
 *  Department of Computer Science
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>

typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

/* 함수 리스트 */
int initialize(listNode** h);
int freeList(listNode* h);
int insertLast(listNode* h, int key);
int deleteLast(listNode* h);
int insertFirst(listNode* h, int key);
int deleteFirst(listNode* h);
int invertList(listNode* h);

int insertNode(listNode* h, int key);
int deleteNode(listNode* h, int key);

void printList(listNode* h);



int main()
{
	char command;
	int key;
	listNode* headnode=NULL;
	printf("[----- [오주형] [2019023028] -----]\n");

	do{
		printf("----------------------------------------------------------------\n");
		printf("                  Doubly Circular Linked List                   \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
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

	}while(command != 'q' && command != 'Q');

	return 1;
}


int initialize(listNode** h) {

	/* headNode가 NULL이 아니면, freeList를 호출하여 할당된 메모리 모두 해제 */
	if(*h != NULL)
		freeList(*h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (listNode*)malloc(sizeof(listNode));
	(*h)->rlink = *h;
	(*h)->llink = *h;
	(*h)->key = -9999;
	return 1;
}

// 이 함수는 메뉴 z를 눌렀을 때 실행되는 함수입니다. 헤드노드의 메모리를 할당하여 리턴합니다.
// 함수를 자세히 살펴보면 함수 매개변수를 이중 포인터로 받고 있습니다.
// *h != NULL인 경우 즉, 헤드노드가 NULL이 아닌 경우 freeList를 호출하여 메모리를 모두 해제합니다.
// 그렇지 않다면 헤드노드에 대한 메모리를 listnode 형태로 할당받습니다. 
// 그리고 *h의 rlink와 llink를 *h로 할당받습니다. 그렇게 하면 자신을 가리키는 형태가 만들어집니다.
// 마지막으로 *h의 key값은 -9999를 넣어 초기화하니다.

/* 메모리 해제 */
int freeList(listNode* h){
	if(h->rlink == h)
	{
		free(h);
		return 1;
	}

	listNode* p = h->rlink;

	listNode* prev = NULL;
	while(p != NULL && p != h) {
		prev = p;
		p = p->rlink;
		free(prev);
	}
	free(h);
	return 0;
}

// 이 함수는 메뉴에서 q를 눌렀을 때 사용하는 함수입니다. 할당된 메모리들을 해제합니다.
// 함수를 자세히 살펴보면 headnode 구조체 포인터 변수 h를 사용합니다.
// 먼저 h의 rlink가 h인 경우 즉, h한 개의 노드만 있는 경우 free(h)를 하여 메모리를 해제합니다.
// 여러 개의 노드가 있는 경우 listnode구조체 형태의 p와 prev를 선언하여 p는 first로 prev는 NULL로 넣어둡니다.
// 이때 p는 모든 노드에 접근하는 역할을 합니다. 그리고 prev는 p가 node를 돌면 그 값을 받아 free로 해제합니다.
// 그래서 반복문을 통해 모든 노드를 접근하여 메모리를 해제한 후 마지막으로 headNode인 h를 해제합니다. 



void printList(listNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->rlink;

	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}
	printf("  items = %d\n", i);


	/* print addresses */
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);

	i = 0;
	p = h->rlink;
	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
		p = p->rlink;
		i++;
	}

}

// 이 함수는 메뉴 p를 눌렀을 때 사용하는 함수입니다. 리스트 노드들의 내용과 주소값을 출력합니다.
// 함수를 자세히 살펴보면  headnode 구조체 포인터 변수 h를 사용합니다. 
// 함수의 처음에 노드의 개수를 셀 i와 listNode형태의 p를 선언합니다.
// p != NULL 그리고 p != h인 동안 p의 값을 다음 노드로 넘기면서 p의 값을 출력합니다. 동시에 노드 개수인 i도 증가시킵니다.
// 그리고 노드들의 주소값을 출력하기 위해 값을 출력했던 것처럼 반복문 안에서 노드를 다음 값으로 보내며 주소값을 출력합니다.



/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(listNode* h, int key) {
	listNode* node = (listNode*)malloc(sizeof(listNode*));
	node->key = key;
	node->llink = NULL;
	node->rlink = NULL;
	
	if(h == NULL){ 
		return -1; 
	}
	// h만 존재하는 경우
	if(h->rlink == h){
		h->rlink = node;
		h->llink = node;
		node->rlink = h;
		node->llink = h;
	}
	else{ // 여러 개의 노드가 있는 경우
		h->llink->rlink = node;
		node->llink = h->llink;
		h->llink = node;
		node->rlink = h;
	}

	return 1;
}

// 이 함수는 n을 눌렀을 때 실행하는 함수입니다. 입력받은 key값을 가장 마자막에 삽입합니다.
// 함수를 자세히 살펴보면 h와 key값을 함수 인자로 사용하고 있습니다.
// 함수 처음에 입력한 key를 넣을 node의 메모리를 동적으로 할당합니다. 그리고 key값엔 입력받은 값을 넣고 두 link에 모두 NULL을 넣어줍니다.
// 다음으로 h가 NULL 값인지 즉, 값을 넣을 공간이 생성됐는지 확인하고 만약 생성되지 않았다면 return -1을 하고 함수를 종료합니다.
// 그렇지 앟다면 h만 존재하는 경우와 여러 노드가 존재하는 경우를 나누어 생각합니다.
// h만 존재한다면 h의 rlink와 h의 llink를 node로 넣고, node의 rlink와 node의 llink를 h로 넣습니다.
// 그러면 h다음으로 첫 번째 노드인 node가 생성됩니다.
// 하지만 노드가 여러 개라면 h의 llink의 rlink를 node로 node의 llink를 h의 llink로
// h의 llink를 node로, node의 rlink를 h로 둡니다. 그러면 h바로 전으로 node가 들어오게 됩니다.
// 그러면 원형 형태의 특성에 따라 마지막 노드로 들어갑니다.

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(listNode* h) {
	if (h==NULL || h->llink == h){
		printf("empty list\n");
		return 0;
	}
	
	listNode* removenode = h->llink;
	removenode->llink->rlink = h;
	h->llink = removenode->llink;
	free(removenode);

	return 1;
}

// 이 함수는 메뉴 e를 눌렀을 때 사용하는 함수입니다. 마지막에 위치한 노드를 삭제합니다.
// 함수를 자세히 살펴보면 listnode형태의 헤드노드인 h를 사용합니다.
// 먼저 h == NULL이거나 혹은 h의 llink가 h인 경우에는 생성이 안 되었거나 값이 헤드만 있는 것이므로 
// list가 비어있다는 메시지를 출력합니다.
// 그렇지 않다면 listnode형태의 removenode를 생성합니다. 이는 삭제할 노드를 가리킵니다.
// 마지막 값을 삭제하는 것이므로 removenode를 h의 llink라고 둡니다. 원형 리스트의 특성에 의해 removenode는 마지막 값이 됩니다.
// 그리고 removenode의 llink의 rlink를 h로 두고, h의 llink를 removenode의 llink로 둡니다.
// 그렇게 되면 마지막 노드에 이어진 link가 사라지고 남은 노드끼리 이어지게 됩니다.
// 마지막으로 removenode의 메모리를 해제하면 마지막 노드가 사라집니다.


int insertFirst(listNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->rlink = NULL;
	node->llink = NULL;


	node->rlink = h->rlink;
	h->rlink->llink = node;
	node->llink = h;
	h->rlink = node;


	return 1;
}

// 이 함수는 메뉴에서 f를 눌렀을 때 사용하는 함수입니다. key값을 입력받아서 가장 앞에 삽입합니다.
// 함수를 자세히 살펴보면 listnode형태의 헤드노드 h와 key값을 함수 인자로 사용하고 있습니다.
// 함수 처음에 입력한 key를 넣을 node의 메모리를 동적으로 할당합니다. 
// 그리고 node의 key값엔 입력받은 값을 넣고 node의 rlink와 llink를 NULL로 초기화 합니다.
// 첫 노드에 들어가야 하므로 node의 rlink는 h의 rlink로, h의 rlink의 llink는 node로
// node의 llink는 h로, h의 rlink는 node로 둡니다. 이렇게 하면 node가 h의 다음으로 오게 됩니다.


/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(listNode* h) {
	if (h == NULL || h->rlink == h)
	{
		printf("nothing to delete.\n");
		return 0;
	}
	listNode* removenode = h->rlink;
	
	h->rlink = removenode -> rlink;
	removenode->rlink->llink = h;
	free(removenode);

	return 1;

}

// 이 함수는 메뉴 t를 눌렀을 때 실행하는 함수입니다. list의 첫번째 노드를 삭제합니다.
// 함수를 자세히 살펴보면 listnode형태의 헤드노드 h를 사용합니다.
// h == NULL 혹은 h->rlink == h인 경우 즉, 공간이 할당되지 않거나, h노드만 있는 경우 삭제할 노드가 없다는 메시지를 출력합니다.
// 그렇지 않다면 삭제할 노드를 가리키는 removenode를 생성하여 h의 rlink 즉 첫 번쨰 노드를 넣습니다.
// 그리고 h의 rlink에 removenode의 rlink를, removenode의 rlink의 llink에 h를 넣습니다.
// 그러면 removenode를 제외한 노드들이 연결됩니다.
// 마지막으로 removenode를 free해주면 첫 번째 노드가 삭제됩니다.

/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(listNode* h) {


	if(h->rlink == h || h == NULL) {
		printf("nothing to invert...\n");
		return 0;
	}
	listNode *n = h->rlink;
	listNode *trail = h;
	listNode *middle = h;

	/* 최종 바뀔 링크 유지 */
	h->llink = h->rlink;

	while(n != NULL && n != h){
		trail = middle;
		middle = n;
		n = n->rlink;
		middle->rlink = trail;
		middle->llink = n;
	}

	h->rlink = middle;

	return 0;
}

// 이 함수는 메뉴 r를 눌렀을 때 사용하는 함수입니다. 리스트의 링크를 역순을 재배치합니다.
// 함수를 자세히 살펴보면 listnode형태의 헤드노드 h를 사용합니다. 
// h == NULL 혹은 h->rlink == h인 경우 즉, 공간이 할당되지 않거나, h노드만 있는 경우 뒤집을 노드가 없다는 메시지를 출력합니다.
// 그렇지 않다면 listnode형태의 n과 trail과 middle을 만듭니다. 그리고 h의 llink에 h의 rlink를 넣습니다.
// 그리고 n이 NULL이 아닌 경우와 n이 h가 아닌 동안 반복문을 실행합니다.
// 반복문에서는 trail에 middle을 middle에 n을 그리고 n은 다음 노드로 이동합니다.
// 그리고 middle의 rlink를 trail로 넣고, middle의 llink를 n으로 넣습니다.
// 그렇게 되면 middle의 두 link가 원래 가리키던 방향과 반대를 가리키게 됩니다.
// 그렇게 반복문이 끝나고 h의 rlink를 middle로 넣으면 h의 두 link도 반대 방향을 가리키게 됩니다.


/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(listNode* h, int key) {

	if(h == NULL){
		return -1;
	} 

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->llink = node->rlink = NULL;

	if (h->rlink == h)
	{
		insertFirst(h, key);
		return 1;
	}

	listNode* n = h->rlink;

	/* key를 기준으로 삽입할 위치를 찾는다 */
	while(n != NULL && n != h) {
		if(n->key >= key) {
			/* 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 */
			if(n == h->rlink) {
				insertFirst(h, key);
			} 
			else { /* 중간이거나 마지막인 경우 */
				node->rlink = n;
				node->llink = n->llink;
				n->llink->rlink = node;
				n->llink = node;
			}
			return 0;
		}

		n = n->rlink;
	}

	/* 마지막 노드까지 찾지 못한 경우, 마지막에 삽입 */
	insertLast(h, key);
	return 0;
}

// 이 함수는 메뉴에서 i를 눌렀을 때 사용하는 함수입니다. key값을 입력받아서 key보다 큰값이 나오는 노드 바로 앞에 삽입합니다.
// 함수를 자세히 살펴보면 listnode형태의 헤드노드 h와 key값을 함수 인자로 사용하고 있습니다.
// 먼저 h == NULL인 경우 즉, 노드를 넣을 공간이 할당 안 된 경우 함수를 종료합니다.
// 그렇지 않다면 함수 처음에 입력한 key를 넣을 node의 메모리를 동적으로 할당합니다. 그리고 key값엔 입력받은 값을 넣고 llink와 rlink에는 NULL을 넣어줍니다.
// 그리고 h의 rlink가 h 즉, h만 존재한다면 처음 노드로 입력되는 것이므로 insertFirst()함수를 사용하여 처음으로 넣어줍니다.
// 노드가 여러 개라면 모든 노드에 접근할 listnode형태의 n을 생성하고 반복문을 수행합니다.
// n != NULL 그리고 n != h인 동안 n은 계속해서 다음 노드 값으로 이동합니다.
// n이 다음 노드값으로 이동하는동안 n의 key가 입력받은 key보다 큰 경우 그때 n위치 앞에 node가 들어가야 합니다.
// 그때가 첫 노드 앞에 들어가는 경우는 insertFirst()함수를 이용하여 첫 노드로 넣습니다.
// 그 경우가 아니라면 node의 rlink를 n으로, node의 llink를 n의 llink로, n의 llink의 rlink는 node로, n의 llink도 node로 넣습니다.
// 그렇게 하면 node가 n과 그 전 노드 사이에 들어가게 됩니다.
// 마지막으로 노드 끝까지 접근했음에도 찾지 못한 경우 insertLast()함수를 이용하여 마지막에 node를 넣어줍니다.


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(listNode* h, int key) {

	if (h->rlink == h || h == NULL)
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->rlink;

	while(n != NULL && n != h) {
		if(n->key == key) {
			if(n == h->rlink) { /* 첫 노드째 노드 인경우 */
				deleteFirst(h);
			} else if (n->rlink == h){ /* 마지막 노드인 경우 */
				deleteLast(h);
			} else { /* 중간인 경우 */
				n->llink->rlink = n->rlink;
				n->rlink->llink = n->llink;
				free(n);
			}
			return 0;
		}

		n = n->rlink;
	}

	/* 찾지 못 한경우 */
	printf("cannot find the node for key = %d\n", key);
	return 0;
}

// 이 함수는 메뉴에서 d를 눌렀을 때 사용하는 함수입니다. key값을 입력받아서 그 값과 같은 key값을 가진 노드를 삭제합니다.
// 함수를 자세히 살펴보면 listnode형태의 헤드노드 h와 key값을 함수 인자로 사용하고 있습니다.
// h->rlink == h || h == NULL인 경우 즉, 공간이 할당되지 않거나, h노드만 있는 경우 삭제할 노드가 없다는 메시지를 출력합니다.
// 비어있지 않다면 listNode형태 n을 선언하여 각각 h->rlink를 넣어줍니다. n != NULL 그리고 n != h인 동안 n은 계속 다음 노드를 접근합니다.
// 그러는 동안 n의 key값이 입력받은 key값과 동일하면 n이 위치한 노드를 삭제해야 합니다.
// 그때 첫 노드인 경우, 마지막, 중간인 경우를 나누어 생각합니다.
// n == h->rlink인 경우 즉, 첫 노드의 key값이 일치할 경우 deleteFirst() 함수를 사용하여 삭제합니다.
// n->rlink == h인 경우 즉, 마지막 노드의 key값이 일치할 경우 deleteLast() 함수를 사용하여 삭제합니다. 
// 그 외의 중간인 경우 n의 llink의 rlink에 n의 rlink를 넣고, n의 rlink의 llink에 n의 llink를 넣고 n의 메몰리를 해제합니다.
// 이렇게 하면 중간에 있는 노드가 삭제 됩니다.
// 반복문이 끝나고도 일치하는 key값을 찾지 못 했다면 일치하는 key값이 없다는 메시지를 출력합니다.