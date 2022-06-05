/*
 * hw12-sorting-hashing.c
 *
 *  Homework 12: Sorting & Hashing
 *  Department of Computer Science at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ARRAY_SIZE 13	/* prime number */
#define MAX_HASH_TABLE_SIZE 	MAX_ARRAY_SIZE

/* 필요에 따라 함수 추가 가능 */
int initialize(int **a);
int freeArray(int *a);
void printArray(int *a);

int selectionSort(int *a);
int insertionSort(int *a);
int bubbleSort(int *a);
int shellSort(int *a);
/* recursive function으로 구현 */
int quickSort(int *a, int n);


/* hash code generator, key % MAX_HASH_TABLE_SIZE */
int hashCode(int key);

/* array a에대 한 hash table을 만든다. */
int hashing(int *a, int **ht);

/* hash table에서 key를 찾아 hash table의 index return */
int search(int *ht, int key);


int main()
{
	char command;
	int *array = NULL;
	int *hashtable = NULL;
	int key = -1;
	int index = -1;

	srand(time(NULL));

	do{
		printf("----------------------------------------------------------------\n");
		printf("                        Sorting & Hashing                       \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize       = z           Quit             = q\n");
		printf(" Selection Sort   = s           Insertion Sort   = i\n");
		printf(" Bubble Sort      = b           Shell Sort       = l\n");
		printf(" Quick Sort       = k           Print Array      = p\n");
		printf(" Hashing          = h           Search(for Hash) = e\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&array);
			break;
		case 'q': case 'Q':
			freeArray(array);
			break;
		case 's': case 'S':
			selectionSort(array);
			break;
		case 'i': case 'I':
			insertionSort(array);
			break;
		case 'b': case 'B':
			bubbleSort(array);
			break;
		case 'l': case 'L':
			shellSort(array);
			break;
		case 'k': case 'K':
			printf("Quick Sort: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			quickSort(array, MAX_ARRAY_SIZE);
			printf("----------------------------------------------------------------\n");
			printArray(array);

			break;

		case 'h': case 'H':
			printf("Hashing: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			hashing(array, &hashtable);
			printArray(hashtable);
			break;

		case 'e': case 'E':
			printf("Your Key = ");
			scanf("%d", &key);
			printArray(hashtable);
			index = search(hashtable, key);
			printf("key = %d, index = %d,  hashtable[%d] = %d\n", key, index, index, hashtable[index]);
			break;

		case 'p': case 'P':
			printArray(array);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initialize(int** a)
{
	int *temp = NULL;

	/* array가 NULL인 경우 메모리 할당 */
	if(*a == NULL) {
		temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*a = temp;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} else
		temp = *a;

	/* 랜덤값을 배열의 값으로 저장 */
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		temp[i] = rand() % MAX_ARRAY_SIZE;

	return 0;
}

// 이 함수는 메뉴 z를 눌렀을 때 실행되는 함수입니다. 배열을 만들어 그 안에 값에 랜덤으로 값을 부여합니다.
// 인자로 받은 배열이 NULL인 경우는 MAX_ARRAY_SIZE만큼 동적할당을 받아 temp에 넣고 temp를 *a에 넣어줍니다.
// 이는 메모리의 주소를 복사한 것입니다.
// 다음으로 인자로 받은 배열이 NULL이 아니라면 *a를 temp에 넣습니다.
// 마지막으로 만든 배열의 값을 랜덤으로 부여 합니다.

int freeArray(int *a)
{
	if(a != NULL)
		free(a);
	return 0;
}

// 이 함수는 메뉴 q를 눌렀을 때 실행되는 함수입니다. 만들었던 배열의 메모리를 하제합니다.
// 함수 인자로 받은 것이 NULL이 아니라면 그것을 동적할당 해제하고 함수를 마칩니다.


void printArray(int *a)
{
	if (a == NULL) {
		printf("nothing to print.\n");
		return;
	}
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("a[%02d] ", i);
	printf("\n");
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("%5d ", a[i]);
	printf("\n");
}

// 이 함수는 메뉴 p를 눌렀을 떄 실행되는 함수입니다. 현재 배열의 상태를 출력합니다.
// 인자로 받은 배열이 NULL이면 print할 것이 없는 메시지를 출력하고 그렇지 않다면 아래 코드로 넘어갑니다.
// 첫 번째 반복문에서는 i를 MAX_ARRAY_SIZE만큼 반복하면서 그 i값을 print합니다.
// 다음 반복문에서는 i를 MAX_ARRAY_SIZE만큼 반복하면서 배열의 i번째 값을 출력합니다.


int selectionSort(int *a)
{
	int min;
	int minindex;
	int i, j;

	printf("Selection Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for (i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		minindex = i;
		min = a[i];
		for(j = i+1; j < MAX_ARRAY_SIZE; j++)
		{
			if (min > a[j])
			{
				min = a[j];
				minindex = j;
			}
		}
		a[minindex] = a[i];
		a[i] = min;
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);
	return 0;
}
// 이 함수는 메뉴 s를 눌렀을 때 실행되는 함수입니다. 배열의 선택정렬을 수행합니다.
// 코드를 살펴보면 정렬되기 전의 배열을 먼저 출력합니다. 그리고 반복문을 실행합니다.
// 가장 작은 배열의 값을 찾기 위해 마지막으로 정렬된 값의 다음 값부터 최소값을 찾습니다.
// 그 최소값을 찾으면 즉 순환하는 값이 min보다 작아지는 순간 min과 minindex를 갱신합니다.
// 배열 순회 후 갱신된 min과 minindex를 이용하여 배열을 정렬합니다.
// 이 실행을 MAX_ARRAY_SIZE만큼 반복하면 전부 배열이 정렬됩니다.


int insertionSort(int *a)
{
	int i, j, t;

	printf("Insertion Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for(i = 1; i < MAX_ARRAY_SIZE; i++)
	{
		t = a[i];
		j = i;
		while (a[j-1] > t && j > 0)
		{
			a[j] = a[j-1];
			j--;
		}
		a[j] = t;
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

// 이 함수는 메뉴에서 i를 눌렀을 때 실행되는 함수입니다. 배열의 삽입정렬을 수행합니다.
// 이는 정렬되어 있는 부분집합에 새로운 원소의 위치를 찾아서 삽입하는 것입니다.
// 코드를 살펴보면 정렬되기 전의 배열을 먼저 출력합니다. 그리고 반복문을 실행합니다.
// i가 1부터 MAX_ARRAY_SIZE만큼 반복하는데 t에는 a[i]의 값을, j에는 i의 값을 넣습니다.
// 그 반복문 안에서 a[j-1] > t 그리고 j > 0인 동안 즉, 삽입하려고 하는 값이 그 바로 앞의 값보다 작거나 j가 양수를 유지하는 동안 
// a[j]=a[j-1]을 실행하게 합니다. 이 뜻은 삽입하려고 한 값의 바로 앞 값을 삽입하려고 하는 값의 자리로 옮긴다는 것입니다.
// 이를 실행하고 j를 1 줄입니다. 그러면 j의 위치는 한 칸 앞으로 오게 됩니다.
// 이 반복문을 실행하다가 종료하면 a[j] = t를 실행합니다. 그러면 삽입정렬이 완성됩니다.

int bubbleSort(int *a)
{
	int i, j, t;

	printf("Bubble Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for(i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		for (j = 1; j < MAX_ARRAY_SIZE; j++)
		{
			if (a[j-1] > a[j])
			{
				t = a[j-1];
				a[j-1] = a[j];
				a[j] = t;
			}
		}
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

// 이 함수는 메뉴에서 b를 눌렀을 때 실행되는 함수입니다. 배열의 버블정렬을 실행합니다.
// 코드를 살펴보면 정렬되기 전의 배열을 먼저 출력합니다. 그리고 반복문을 실행합니다.
// 반복문을 중첩해서 도는데 a[j-1]이 a[j]보다 큰 경우 두 자리의 값을 바꾸면서 계속 자리를 교환합니다.
// 반복문이 모두 실행되면 가장 큰 우너소가 마지막 자리로 결정되면서 배열이 버블 정렬 됩니다.


int shellSort(int *a)
{
	int i, j, k, h, v;

	printf("Shell Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for (h = MAX_ARRAY_SIZE/2; h > 0; h /= 2)
	{
		for (i = 0; i < h; i++)
		{
			for(j = i + h; j < MAX_ARRAY_SIZE; j += h)
			{
				v = a[j];
				k = j;
				while (k > h-1 && a[k-h] > v)
				{
					a[k] = a[k-h];
					k -= h;
				}
				a[k] = v;
			}
		}
	}
	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

// 이 함수는 메뉴에서 l을 눌렀을 때 실행되는 함수입니다. 배열의 셸 정렬을 실행합니다.
// 코드를 살펴보면 정렬되기 전의 배열을 먼저 출력합니다. 그리고 반복문을 실행합니다.
// h의 값을 MAX_ARRAY_SIZE/2로 놓고 반복문을 실행하면서 h를 계속해서 반으로 만듭니다.
// h가 기준이 되니까 그 안의 반복문에서 첫 번째 반복문은 0부터 h만큼 반복하고 그 다음은 i+h부터 MAX_ARRAY_SIZE만큼 반복합니다.
// 그 안에서 h를 기준으로 나누어진 배열의 값을 비교하여 정렬합니다. 정렬이 완성되면 남은 부분은 삽입정렬을 통해 남은 정렬을 완료합니다.
// 이렇게 하면 배열의 셸 정렬이 완성됩니다.

int quickSort(int *a, int n)
{
	int v, t;
	int i, j;

	if (n > 1)
	{
		v = a[n-1];
		i = -1;
		j = n - 1;

		while(1)
		{
			while(a[++i] < v);
			while(a[--j] > v);

			if (i >= j) break;
			t = a[i];
			a[i] = a[j];
			a[j] = t;
		}
		t = a[i];
		a[i] = a[n-1];
		a[n-1] = t;

		quickSort(a, i);
		quickSort(a+i+1, n-i-1);
	}


	return 0;
}

// 이 함수는 메뉴애서 k를 눌렀을 때 실행되는 함수입니다. 배열의 퀵 정렬을 실행합니다.
// 함수인자에서 n은 MAX_ARRAY_SIZE를 나타냅니다. n이 1보다 크면 v = a[n-1], i = -1, j = n - 1을 해줍니다.
// 여기서 v는 피봇을 가리킵니다. 피봇은 왼쪽과 오른쪽을 나누는 기준입니다.
// 그리고 무한반복문 안에서 피봇보다 작은 key를 찾기 위해 왼쪽에서 오른쪽으로 검사하고, 큰 key를 찾기 위해 오른쪽에서 왼쪽으로 검사합니다.
// 그리고 

int hashCode(int key) {
   return key % MAX_HASH_TABLE_SIZE;
}

int hashing(int *a, int **ht)
{
	int *hashtable = NULL;

	/* hash table이 NULL인 경우 메모리 할당 */
	if(*ht == NULL) {
		hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*ht = hashtable;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} else {
		hashtable = *ht;	/* hash table이 NULL이 아닌경우, table 재활용, reset to -1 */
	}

	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		hashtable[i] = -1;

	/*
	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		printf("hashtable[%d] = %d\n", i, hashtable[i]);
	*/

	int key = -1;
	int hashcode = -1;
	int index = -1;
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		key = a[i];
		hashcode = hashCode(key);
		/*
		printf("key = %d, hashcode = %d, hashtable[%d]=%d\n", key, hashcode, hashcode, hashtable[hashcode]);
		*/
		if (hashtable[hashcode] == -1)
		{
			hashtable[hashcode] = key;
		} else 	{

			index = hashcode;

			while(hashtable[index] != -1)
			{
				index = (++index) % MAX_HASH_TABLE_SIZE;
				/*
				printf("index = %d\n", index);
				*/
			}
			hashtable[index] = key;
		}
	}

	return 0;
}

int search(int *ht, int key)
{
	int index = hashCode(key);

	if(ht[index] == key)
		return index;

	while(ht[++index] != key)
	{
		index = index % MAX_HASH_TABLE_SIZE;
	}
	return index;
}