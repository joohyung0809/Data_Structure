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
	QueueType *cQ = createQueue(); // Queue�� ���� �޸� �Ҵ����� ����
	element data;
	char command;
	printf("\n[----- [������] [2019023028] -----]\n");

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

// �� �Լ��� main�Լ��� ���۵Ǹ鼭 ȣ��˴ϴ�.
// cQ��� ������ ����� QueueType�� ���� �޸� �Ҵ��� �̿��Ͽ� ������ �Ҵ� �޾ҽ��ϴ�.
// �̶� �Ҵ��� �޸� ũ��� QueueType��ŭ ������ ����� ���� QueueType���� �������ݴϴ�. 
// �׸��� cQ�� front�� rear�� ���� �ʱ⼼�� ���ֱ� ������ 0���� ��������ϴ�.

int freeQueue(QueueType *cQ)
{
    if(cQ == NULL) return 1;
    free(cQ);
    return 1;
}

// �� �Լ��� �޴� �Է� �ڵ忡�� q�� ������ ��쿡 ����˴ϴ�. ���� �޸� �Ҵ��� �ߴ� ť�� �޸𸮸� �����ϴ� ���Դϴ�.
// �Լ��� �ڼ��� ���캸�� QueueType ����ü ������ cQ�� �Լ� ���ڷ� ����մϴ�.
// cQ�� �޸� �Ҵ��� ���� ���� ��츦 ���� ó���߰�, �Ҵ��� �Ǿ� �ִٸ� free �Լ��� ����Ͽ� �޸𸮸� �����߽��ϴ�.


element getElement()
{
	element item;
	printf("Input element = ");
	scanf(" %c", &item);
	return item;
}

// �� �Լ��� �޴� �Է� �ڵ忡�� i�� ������ ��쿡 ����˴ϴ�. �Է��� �����͸� �Է� �޴� �κ��Դϴ�.
// item �̶�� ������ �����߰�, scanf �Լ��� ����Ͽ� ���� �Է¹޾� item�� ��ȯ�߽��ϴ�.
// �̴� enQueue() �Լ����� element item���ڷ� ���˴ϴ�.


int isEmpty(QueueType *cQ)
{
	if (cQ->rear == cQ->front) {
		printf("Circular Queue is empty!");
		return 1;
	}
	else return 0;

}

// �� �Լ��� cQ�� ����ִ��� ��, ���� ť�� ����ִ��� Ȯ���ϴ� �Լ��Դϴ�.
// �Լ��� �ڼ��� ���캸�� QueueType ����ü ������ cQ�� �Լ� ���ڷ� ����մϴ�.
// �� cQ ���� rear���� front ���� ���ؼ� �� ���� ���ٸ� ���� ť�� ����ִٰ� �ؼ��� �� �ֽ��ϴ�.
// �׷��� ����ִٸ� return 1�� ��ȯ�ϰ� �׷��� �ʴٸ� 0�� ��ȯ�մϴ�.
// �� ������ �ٸ� �Լ����� isEmpty() �Լ��� ���� ���� ������ ��츦 ������ Ȱ���ϰ� �ֱ� �����Դϴ�.

int isFull(QueueType *cQ)
{
	if ((cQ->rear + 1) % MAX_QUEUE_SIZE == cQ->front) { 
		printf("Circular Queue is full!");
		return 1;
	}
	else return 0;
}

// �� �Լ��� cQ�� ����ִ��� ��, ���� ť�� ����ִ��� Ȯ���ϴ� �Լ��Դϴ�.
// ���� ť������ ť�� ������� ���� ���� ä�������� ���� �����ؾ��մϴ�.
// �̸� �������� ������ front�� rear���� ������ �� ���� ��찡 ������ ������ ť�� ���� �ϳ��� ����δ� ����� ����մϴ�.
// ��, rear ���� front �ٷ� �������� �ۿ� ���� �� �ϰ� ����� ���Դϴ�.
// �Լ��� �ڼ��� ���캸�� isEmpty �Լ��� ���������� QueueType ����ü ������ cQ�� �Լ� ���ڷ� ����մϴ�.
// ������ ����ߵ��� rear�� front���� �ٷ� ���� �ִٸ� �� ���� full�̶�� �����ؾ� �մϴ�.
// �� ��츦 �����Ϸ��� cQ�� rear ���� 1�� ���� ���� MAX_QUEUE_SIZE�� ���� �� �� ������ ���� ���մϴ�.
// �׸��� �� ������ ���� cQ�� front���� ���Ͽ� ���ٸ� ���� ť�� ��� ä���� �ִٰ� �ؼ��� �� �ֽ��ϴ�.


void enQueue(QueueType *cQ, element item)
{
	if (isFull(cQ)) return;
	else {
		cQ->rear = (cQ->rear + 1) % MAX_QUEUE_SIZE;
		cQ->queue[cQ->rear] = item;
	}
}

// �� �Լ��� �޴� �Է� �ڵ忡�� i�� ������ ��쿡 ����˴ϴ�. ť ���� ���� �Է��ϴ� �Լ��Դϴ�.
// �Լ��� �ڼ��� ���캸�� QueueType ����ü ������ cQ�� �Է��� ���� item�� ���ڷ� �����߽��ϴ�.
// �׸��� if�Լ��� �������� isFull�Լ��� ����Ͽ� ť�� ��� ä���� �ִ��� Ȯ���մϴ�. 
// �� �Լ��� if���� ����ϱ� ���� isFull �Լ��� return���� 1�� 0���� ������ ���Դϴ�.
// �׷��� ť�� ��� ä���� ���� �ʴٸ� rear�� ���� ����, �Է��� ���� item�� �־��ݴϴ�.
// �̶� rear�� +1�� �ؼ� �ø��� �ʽ��ϴ�.
// ������ ����ť�� �����ϱ� ���� rear���� MAX_QUEUE_SIZE ���� �Ǿ��� �� �ٽ� 0�� �Ǿ�� �ϱ� �����Դϴ�. 


void deQueue(QueueType *cQ, element *item) 
{
	if (isEmpty(cQ)) return;
	else {
		cQ->front = (cQ->front + 1) % MAX_QUEUE_SIZE;
		*item = cQ->queue[cQ->front];
		return;
	}
}

// �� �Լ��� �޴� �Է� �ڵ忡�� d�� ������ ��쿡 ����˴ϴ�. ť ���� ���� ���ִ� �Լ��Դϴ�.
// ����� ���� ���Ű� �� ���� ���� ���� ���Դ� �����Ͱ� ���� ���� �����ϴ�.
// �̸� FIFO(First-In_First_Out)�����̶�� �θ��ϴ�.
// �Լ��� �ڼ��� ���캸�� QueueType ����ü ������ cQ�� ���� �����͸� ������ �� �ִ� *item�� ���ڷ� �����߽��ϴ�.
// �׸��� if�Լ��� �������� isEmpty�Լ��� ����Ͽ� ����ִ� ť���� Ȯ���մϴ�.. 
// �� �Լ��� if���� ����ϱ� ���� isEmpty �Լ��� return���� 1�� 0���� ������ ���Դϴ�.
// �׷��� ť�� ������� �ʴٸ� front�� ���� ������ �ű�� *item�� ����� front�� ����Ű�� �����͸� �ֽ��ϴ�.
// �׷��� �ϸ� ť���� �� ���� *item�� Ȱ���Ͽ� ȣ���� �� �ֽ��ϴ�.
// �̶� front�� ���� +1�ؼ� �ø��� �ʽ��ϴ�.
// ������ enQueue���� ����ߵ��� ����ť�� �����ϱ� ���� front ���� MAX_QUEUE_SIZE ���� �Ǿ��� �� �ٽ� 0�� �Ǿ�� �ϱ� �����Դϴ�. 



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

// �� �Լ��� �޴� �Է� �ڵ忡�� p�� ������ ��쿡 ����˴ϴ�. ���� Queue�� �� �ִ� �����͸� ����ϴ� �Լ��Դϴ�.
// �Լ��� �ڼ��� ���캸�� QueueType ����ü ������ cQ�� ���ڷ� ����߽��ϴ�.
// ���⼭�� front�� rear���̿� ��ġ�� ���� cQ���� queue�� �ε��� ���� Ȱ���ؼ� �����͸� ȣ���߽��ϴ�.
// �̶� �߿��� ���� first�� last�� ���Դϴ�.
// ���� first�� ���캸�� cQ�� front�� 1�� ���ϰ� MAX_QUEUE_SIZE�� ���� ���������� ���ֽ��ϴ�.
// ����ť������ first�� �ڸ��� �� �ڸ� �Ҵ� �ϰ� �־ first�� ù��° ���� �ٷ� �տ� ��ġ�� �ֽ��ϴ�.
// �׷��� ���� ����� ���� 1�� ���� �� ������ ���Դϴ�,
// �������� last�� ���캸�� cQ�� rear�� 1�� ���ϰ� MAX_QUEUE_SIZE�� ���� ���������� ���ֽ��ϴ�.
// �׷��� �� last���� while���� ���ǹ��� ����Ͽ� ���ǿ� �´� queue�� �ε��� ���� ����ϴ� ���Դϴ�.


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

// �� �Լ��� �޴� �Է� �ڵ忡�� b�� ������ ��쿡 ����˴ϴ�. ���� Queue�� ���°� ��� ����ϴ� �Լ��Դϴ�.
// �����͵��� ��� ��ġ�ϰ� �ִ���, front�� rear�� ��ġ�� ������� Ȯ�� �� �� �ֽ��ϴ�.
// �Լ��� �ڼ��� ���캸�� QueueType ����ü ������ cQ�� ���ڷ� ����߽��ϴ�.
// for���� �ݺ��ϸ鼭 cQ�� front�� i�� ���ٸ� i�� ���� front��� ������ ����ϰ� ���� �ݺ����� ������� �����ϴ�.
// �ݺ��� �ȿ��� front�� ��ġ�� ã�Ƴ��� if���� �����ϴ� ���ÿ�, queue�ȿ� �ִ� �����͸� ȣ���մϴ�.
// �����ϸ� i�� 0���� MAX_QUEUE_SIZE���� �����ϴ� front�� ���� i�� ���ٸ� front��ġ�� i��� ������ ����ϰ�
// �׷��� �ʴٸ� ť �ȿ� �ִ� �������� ��ġ�� i��°��� ������ ����մϴ�.
// ���������� for���� ������ front�� rear�� ��ġ�� ������� �����Ͽ� ����մϴ�.
