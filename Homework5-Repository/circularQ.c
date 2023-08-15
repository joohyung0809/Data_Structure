/* circularQ.c
 *
 *  Data Structures, Homework #5
 *  Department of Computer Science at Chungbuk National University
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 4

typedef char element;
typedef struct {
	element queue[MAX_QUEUE_SIZE];
	int front, rear;
}QueueType;


QueueType *createQueue();
int freeQueue(QueueType *cQ);
int isEmpty(QueueType *cQ);
int isFull(QueueType *cQ);
void enQueue(QueueType *cQ, element item);
void deQueue(QueueType *cQ, element* item);
void printQ(QueueType *cQ);
void debugQ(QueueType *cQ);
element getElement();

int main(void)
{
	QueueType *cQ = createQueue(); // Queue를 동적 메모리 할당으로 받음
	element data;
	char command;
	printf("\n[----- [오주형] [2019023028] -----]\n");

	do{
		printf("\n-----------------------------------------------------\n");
		printf("                     Circular Q                   \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Debug=b,   Quit=q \n");
		printf("------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'i': case 'I':
			data = getElement();
			enQueue(cQ, data);
			break;
		case 'd': case 'D':
			deQueue(cQ, &data);
			break;
		case 'p': case 'P':
			printQ(cQ);
			break;
		case 'b': case 'B':
			debugQ(cQ);
			break;
		case 'q': case 'Q':
   	        freeQueue(cQ);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');


	return 1;
}

QueueType *createQueue()
{
	QueueType *cQ;
	cQ = (QueueType *)malloc(sizeof(QueueType));
	cQ->front = 0;
	cQ->rear = 0;
	return cQ;
}

// 이 함수는 main함수가 시작되면서 호출됩니다.
// cQ라는 변수를 만들어 QueueType을 동적 메모리 할당을 이용하여 공간을 할당 받았습니다.
// 이때 할당할 메모리 크기는 QueueType만큼 공간을 만들기 위해 QueueType으로 지정해줍니다. 
// 그리고 cQ의 front와 rear의 값을 초기세팅 해주기 위히여 0으로 만들었습니다.

int freeQueue(QueueType *cQ)
{
    if(cQ == NULL) return 1;
    free(cQ);
    return 1;
}

// 이 함수는 메뉴 입력 코드에서 q를 눌렀을 경우에 실행됩니다. 동적 메모리 할당을 했던 큐의 메모리를 해제하는 것입니다.
// 함수를 자세히 살펴보면 QueueType 구조체 변수로 cQ를 함수 인자로 사용합니다.
// cQ가 메모리 할당이 되지 않은 경우를 따로 처리했고, 할당이 되어 있다면 free 함수를 사용하여 메모리를 해제했습니다.


element getElement()
{
	element item;
	printf("Input element = ");
	scanf(" %c", &item);
	return item;
}

// 이 함수는 메뉴 입력 코드에서 i를 눌렀을 경우에 실행됩니다. 입력할 데이터를 입력 받는 부분입니다.
// item 이라는 변수를 선언했고, scanf 함수를 사용하여 값을 입력받아 item을 반환했습니다.
// 이는 enQueue() 함수에서 element item인자로 사용됩니다.


int isEmpty(QueueType *cQ)
{
	if (cQ->rear == cQ->front) {
		printf("Circular Queue is empty!");
		return 1;
	}
	else return 0;

}

// 이 함수는 cQ가 비어있는지 즉, 원형 큐가 비어있는지 확인하는 함수입니다.
// 함수를 자세히 살펴보면 QueueType 구조체 변수로 cQ를 함수 인자로 사용합니다.
// 이 cQ 안의 rear값과 front 값을 비교해서 그 값이 같다면 원형 큐가 비어있다고 해석할 수 있습니다.
// 그래서 비어있다면 return 1을 반환하고 그렇지 않다면 0을 반환합니다.
// 이 이유는 다른 함수에서 isEmpty() 함수를 참인 경우와 거짓인 경우를 나누어 활용하고 있기 때문입니다.

int isFull(QueueType *cQ)
{
	if ((cQ->rear + 1) % MAX_QUEUE_SIZE == cQ->front) { 
		printf("Circular Queue is full!");
		return 1;
	}
	else return 0;
}

// 이 함수는 cQ가 비어있는지 즉, 원형 큐가 비어있는지 확인하는 함수입니다.
// 원형 큐에서는 큐가 비어있을 때와 전부 채워져있을 때를 구별해야합니다.
// 이를 구별하지 않으면 front와 rear값이 같으면 두 가지 경우가 나오기 때문에 큐의 공간 하나를 비워두는 방법을 사용합니다.
// 즉, rear 값은 front 바로 직전까지 밖에 오지 못 하게 만드는 것입니다.
// 함수를 자세히 살펴보면 isEmpty 함수와 마찬가지로 QueueType 구조체 변수로 cQ를 함수 인자로 사용합니다.
// 위에서 언급했듯이 rear가 front값의 바로 전에 있다면 그 경우는 full이라고 생각해야 합니다.
// 이 경우를 구현하려면 cQ의 rear 값에 1을 더한 것을 MAX_QUEUE_SIZE로 나눈 후 그 나머지 값을 구합니다.
// 그리고 그 나머지 값과 cQ의 front값을 비교하여 같다면 원형 큐가 모두 채워져 있다고 해석할 수 있습니다.


void enQueue(QueueType *cQ, element item)
{
	if (isFull(cQ)) return;
	else {
		cQ->rear = (cQ->rear + 1) % MAX_QUEUE_SIZE;
		cQ->queue[cQ->rear] = item;
	}
}

// 이 함수는 메뉴 입력 코드에서 i를 눌렀을 경우에 실행됩니다. 큐 안의 값을 입력하는 함수입니다.
// 함수를 자세히 살펴보면 QueueType 구조체 변수로 cQ와 입력할 값인 item을 인자로 설정했습니다.
// 그리고 if함수의 조건으로 isFull함수를 사용하여 큐가 모두 채워져 있는지 확인합니다. 
// 이 함수를 if문에 사용하기 위해 isFull 함수의 return값을 1과 0으로 설정한 것입니다.
// 그래서 큐가 모두 채워져 있지 않다면 rear의 다음 값에, 입력할 값인 item을 넣어줍니다.
// 이때 rear에 +1을 해서 늘리지 않습니다.
// 이유는 원형큐를 구현하기 위해 rear값이 MAX_QUEUE_SIZE 값이 되었을 때 다시 0이 되어야 하기 때문입니다. 


void deQueue(QueueType *cQ, element *item) 
{
	if (isEmpty(cQ)) return;
	else {
		cQ->front = (cQ->front + 1) % MAX_QUEUE_SIZE;
		*item = cQ->queue[cQ->front];
		return;
	}
}

// 이 함수는 메뉴 입력 코드에서 d를 눌렀을 경우에 실행됩니다. 큐 안의 값을 없애는 함수입니다.
// 참고로 값이 제거가 될 때는 가장 먼저 들어왔던 데이터가 가장 먼저 나갑니다.
// 이를 FIFO(First-In_First_Out)형식이라고 부릅니다.
// 함수를 자세히 살펴보면 QueueType 구조체 변수로 cQ와 빠진 데이터를 저장할 수 있는 *item을 인자로 설정했습니다.
// 그리고 if함수의 조건으로 isEmpty함수를 사용하여 비어있는 큐인지 확인합니다.. 
// 이 함수를 if문에 사용하기 위해 isEmpty 함수의 return값을 1과 0으로 설정한 것입니다.
// 그래서 큐가 비어있지 않다면 front를 다음 값으로 옮기고 *item에 변경된 front가 가리키는 데이터를 넣습니다.
// 그렇게 하면 큐에서 뺀 값을 *item을 활용하여 호출할 수 있습니다.
// 이때 front의 값을 +1해서 늘리지 않습니다.
// 이유는 enQueue에서 언급했듯이 원형큐를 구현하기 위해 front 값이 MAX_QUEUE_SIZE 값이 되었을 때 다시 0이 되어야 하기 때문입니다. 



void printQ(QueueType *cQ)
{
	int i, first, last;

	first = (cQ->front + 1)%MAX_QUEUE_SIZE;
	last = (cQ->rear + 1)%MAX_QUEUE_SIZE;

	printf("Circular Queue : [");

	i = first;
	while(i != last){
		printf("%3c", cQ->queue[i]);
		i = (i+1)%MAX_QUEUE_SIZE;

	}
	printf(" ]\n");
}

// 이 함수는 메뉴 입력 코드에서 p를 눌렀을 경우에 실행됩니다. 현재 Queue에 들어가 있는 데이터를 출력하는 함수입니다.
// 함수를 자세히 살펴보면 QueueType 구조체 변수로 cQ를 인자로 사용했습니다.
// 여기서는 front와 rear사이에 위치한 값을 cQ에서 queue의 인덱스 값을 활용해서 데이터를 호출했습니다.
// 이때 중요한 것은 first와 last의 값입니다.
// 먼저 first를 살펴보면 cQ의 front에 1을 더하고 MAX_QUEUE_SIZE로 나눈 나머지값이 들어가있습니다.
// 원형큐에서는 first의 자리를 한 자리 할당 하고 있어서 first는 첫번째 값의 바로 앞에 위치해 있습니다.
// 그래서 값을 출력을 위해 1을 더한 후 연산한 것입니다,
// 다음으로 last를 살펴보면 cQ의 rear에 1을 더하고 MAX_QUEUE_SIZE로 나눈 나머지값이 들어가있습니다.
// 그래서 이 last값을 while문의 조건문에 사용하여 조건에 맞는 queue의 인덱스 값을 출력하는 것입니다.


void debugQ(QueueType *cQ)
{

	printf("\n---DEBUG\n");
	for(int i = 0; i < MAX_QUEUE_SIZE; i++)
	{
		if(i == cQ->front) {
			printf("  [%d] = front\n", i);
			continue;
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]);

	}
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear);
}

// 이 함수는 메뉴 입력 코드에서 b를 눌렀을 경우에 실행됩니다. 현재 Queue의 상태가 어떤지 출력하는 함수입니다.
// 데이터들이 어디에 위치하고 있는지, front와 rear의 위치는 어디인지 확인 할 수 있습니다.
// 함수를 자세히 살펴보면 QueueType 구조체 변수로 cQ를 인자로 사용했습니다.
// for문을 반복하면서 cQ의 front가 i와 같다면 i의 값이 front라는 내용을 출력하고 남은 반복문을 실행없이 끝냅니다.
// 반복문 안에서 front의 위치를 찾아내는 if문을 실행하는 동시에, queue안에 있는 데이터를 호출합니다.
// 정리하면 i가 0부터 MAX_QUEUE_SIZE까지 증가하는 front의 값이 i와 같다면 front위치가 i라는 내용을 출력하고
// 그렇지 않다면 큐 안에 있는 데이터의 위치가 i번째라는 내용을 출력합니다.
// 마지막으로 for문이 끝나고 front와 rear의 위치가 어디인지 정리하여 출력합니다.
