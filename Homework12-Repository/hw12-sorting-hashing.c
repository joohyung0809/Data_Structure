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

/* �ʿ信 ���� �Լ� �߰� ���� */
int initialize(int **a);
int freeArray(int *a);
void printArray(int *a);

int selectionSort(int *a);
int insertionSort(int *a);
int bubbleSort(int *a);
int shellSort(int *a);
/* recursive function���� ���� */
int quickSort(int *a, int n);


/* hash code generator, key % MAX_HASH_TABLE_SIZE */
int hashCode(int key);

/* array a���� �� hash table�� �����. */
int hashing(int *a, int **ht);

/* hash table���� key�� ã�� hash table�� index return */
int search(int *ht, int key);


int main()
{
	printf("[----- [������] [2019023028] -----]\n");
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

	/* array�� NULL�� ��� �޸� �Ҵ� */
	if(*a == NULL) {
		temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*a = temp;  /* �Ҵ�� �޸��� �ּҸ� ���� --> main���� �迭�� control �Ҽ� �ֵ��� ��*/
	} else
		temp = *a;

	/* �������� �迭�� ������ ���� */
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		temp[i] = rand() % MAX_ARRAY_SIZE;

	return 0;
}

// �� �Լ��� �޴� z�� ������ �� ����Ǵ� �Լ��Դϴ�. �迭�� ����� �� �ȿ� ���� �������� ���� �ο��մϴ�.
// ���ڷ� ���� �迭�� NULL�� ���� MAX_ARRAY_SIZE��ŭ �����Ҵ��� �޾� temp�� �ְ� temp�� *a�� �־��ݴϴ�.
// �̴� �޸��� �ּҸ� ������ ���Դϴ�.
// �������� ���ڷ� ���� �迭�� NULL�� �ƴ϶�� *a�� temp�� �ֽ��ϴ�.
// ���������� ���� �迭�� ���� �������� �ο� �մϴ�.

int freeArray(int *a)
{
	if(a != NULL)
		free(a);
	return 0;
}

// �� �Լ��� �޴� q�� ������ �� ����Ǵ� �Լ��Դϴ�. ������� �迭�� �޸𸮸� �����մϴ�.
// �Լ� ���ڷ� ���� ���� NULL�� �ƴ϶�� �װ��� �����Ҵ� �����ϰ� �Լ��� ��Ĩ�ϴ�.


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

// �� �Լ��� �޴� p�� ������ �� ����Ǵ� �Լ��Դϴ�. ���� �迭�� ���¸� ����մϴ�.
// ���ڷ� ���� �迭�� NULL�̸� print�� ���� ���� �޽����� ����ϰ� �׷��� �ʴٸ� �Ʒ� �ڵ�� �Ѿ�ϴ�.
// ù ��° �ݺ��������� i�� MAX_ARRAY_SIZE��ŭ �ݺ��ϸ鼭 �� i���� print�մϴ�.
// ���� �ݺ��������� i�� MAX_ARRAY_SIZE��ŭ �ݺ��ϸ鼭 �迭�� i��° ���� ����մϴ�.


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
// �� �Լ��� �޴� s�� ������ �� ����Ǵ� �Լ��Դϴ�. �迭�� ���������� �����մϴ�.
// �ڵ带 ���캸�� ���ĵǱ� ���� �迭�� ���� ����մϴ�. �׸��� �ݺ����� �����մϴ�.
// ���� ���� �迭�� ���� ã�� ���� ���������� ���ĵ� ���� ���� ������ �ּҰ��� ã���ϴ�.
// �� �ּҰ��� ã���� �� ��ȯ�ϴ� ���� min���� �۾����� ���� min�� minindex�� �����մϴ�.
// �迭 ��ȸ �� ���ŵ� min�� minindex�� �̿��Ͽ� �迭�� �����մϴ�.
// �� ������ MAX_ARRAY_SIZE��ŭ �ݺ��ϸ� ���� �迭�� ���ĵ˴ϴ�.


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

// �� �Լ��� �޴����� i�� ������ �� ����Ǵ� �Լ��Դϴ�. �迭�� ���������� �����մϴ�.
// �̴� ���ĵǾ� �ִ� �κ����տ� ���ο� ������ ��ġ�� ã�Ƽ� �����ϴ� ���Դϴ�.
// �ڵ带 ���캸�� ���ĵǱ� ���� �迭�� ���� ����մϴ�. �׸��� �ݺ����� �����մϴ�.
// i�� 1���� MAX_ARRAY_SIZE��ŭ �ݺ��ϴµ� t���� a[i]�� ����, j���� i�� ���� �ֽ��ϴ�.
// �� �ݺ��� �ȿ��� a[j-1] > t �׸��� j > 0�� ���� ��, �����Ϸ��� �ϴ� ���� �� �ٷ� ���� ������ �۰ų� j�� ����� �����ϴ� ���� 
// a[j]=a[j-1]�� �����ϰ� �մϴ�. �� ���� �����Ϸ��� �� ���� �ٷ� �� ���� �����Ϸ��� �ϴ� ���� �ڸ��� �ű�ٴ� ���Դϴ�.
// �̸� �����ϰ� j�� 1 ���Դϴ�. �׷��� j�� ��ġ�� �� ĭ ������ ���� �˴ϴ�.
// �� �ݺ����� �����ϴٰ� �����ϸ� a[j] = t�� �����մϴ�. �׷��� ���������� �ϼ��˴ϴ�.

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

// �� �Լ��� �޴����� b�� ������ �� ����Ǵ� �Լ��Դϴ�. �迭�� ���������� �����մϴ�.
// �ڵ带 ���캸�� ���ĵǱ� ���� �迭�� ���� ����մϴ�. �׸��� �ݺ����� �����մϴ�.
// �ݺ����� ��ø�ؼ� ���µ� a[j-1]�� a[j]���� ū ��� �� �ڸ��� ���� �ٲٸ鼭 ��� �ڸ��� ��ȯ�մϴ�.
// �ݺ����� ��� ����Ǹ� ���� ū ��ʼҰ� ������ �ڸ��� �����Ǹ鼭 �迭�� ���� ���� �˴ϴ�.


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

// �� �Լ��� �޴����� l�� ������ �� ����Ǵ� �Լ��Դϴ�. �迭�� �� ������ �����մϴ�.
// �ڵ带 ���캸�� ���ĵǱ� ���� �迭�� ���� ����մϴ�. �׸��� �ݺ����� �����մϴ�.
// h�� ���� MAX_ARRAY_SIZE/2�� ���� �ݺ����� �����ϸ鼭 h�� ����ؼ� ������ ����ϴ�.
// h�� ������ �Ǵϱ� �� ���� �ݺ������� ù ��° �ݺ����� 0���� h��ŭ �ݺ��ϰ� �� ������ i+h���� MAX_ARRAY_SIZE��ŭ �ݺ��մϴ�.
// �� �ȿ��� h�� �������� �������� �迭�� ���� ���Ͽ� �����մϴ�. ������ �ϼ��Ǹ� ���� �κ��� ���������� ���� ���� ������ �Ϸ��մϴ�.
// �̷��� �ϸ� �迭�� �� ������ �ϼ��˴ϴ�.

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

// �� �Լ��� �޴��ּ� k�� ������ �� ����Ǵ� �Լ��Դϴ�. �迭�� �� ������ �����մϴ�.
// �Լ����ڿ��� n�� MAX_ARRAY_SIZE�� ��Ÿ���ϴ�. n�� 1���� ũ�� v = a[n-1], i = -1, j = n - 1�� ���ݴϴ�.
// ���⼭ v�� �Ǻ��� ����ŵ�ϴ�. �Ǻ��� ���ʰ� �������� ������ �����Դϴ�.
// �׸��� ���ѹݺ��� �ȿ��� �Ǻ����� ���� key�� ã�� ���� ���ʿ��� ���������� �˻��ϰ�, ū key�� ã�� ���� �����ʿ��� �������� �˻��մϴ�.
// �׸��� i�� j���� ũ�ų� �������� �ݺ����� Ż���ϰ� �׷��� ������ �����ʰ� ���ʰ��� �ٲߴϴ�.
// �׸��� i�� j���� ũ�ų� �������� �ݺ����� ������ �Ǻ��� �������մϴ�.
// ���������� i�� �߽����� �ٽ� ���ʰ� �������� �����Ͽ� quckSort�� �����մϴ�.
// �׷��� �ϸ� �迭�� �� ������ �ϼ��˴ϴ�.

int hashCode(int key) {
   return key % MAX_HASH_TABLE_SIZE;
}

// �� �Լ��� hashing�Լ����� ���̴� �Լ��Դϴ�.
// Ȩ ��Ŷ�� %�����ڿ� ���� �����Ǵ� ���� �Լ��Դϴ�.
// �Է¹��� key ���� MAX_HASH_TABLE_SIZE�� %�����ڸ� ������ ���� �����մϴ�.
// �̶� MAX_HASH_TABLE_SIZE�� MAX_ARRAY_SIZE���� �����ϴ�.


int hashing(int *a, int **ht) // *a�� array��
{
	int *hashtable = NULL;

	/* hash table�� NULL�� ��� �޸� �Ҵ� */
	if(*ht == NULL) {
		hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*ht = hashtable;  /* �Ҵ�� �޸��� �ּҸ� ���� --> main���� �迭�� control �Ҽ� �ֵ��� ��*/
	} else {
		hashtable = *ht;	/* hash table�� NULL�� �ƴѰ��, table ��Ȱ��, reset to -1 */
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

// �� �Լ��� �޴����� h�� ������ �� ����Ǵ� �Լ��Դϴ�. �迭�� �ؽ��� �����մϴ�.
// �Լ������� �ؽ� ���̺��� NULL�� ��� hashtable ������ �迭�� ũ�⸸ŭ �����Ҵ��� �޽��ϴ�.
// NULL�� �ƴ� ��� �� ���̺��� ��Ȱ���մϴ�. �������� �ؽ� ���̺��� ���� ��� -1�� �ʱ�ȭ�մϴ�.
// ���� �迭�� �����ϴµ� 0���� MAX_ARRAY_SIZE��ŭ �ݺ��ϸ鼭 array�� ��� ���� �����ϸ鼭 key���� �ֽ��ϴ�. 
// �̶� hashCode�Լ��� hashcode������ key���� �ؽ��ڵ带 �ֽ��ϴ�.
// �� �ݺ��� �ȿ��� hashtable[hashcode] == -1 �̸� �� �ʱ�ȭ �ߴ� ������ �ִٸ� �� �ڸ��� key���� �ֽ��ϴ�.
// �׷��� ������ �����÷ΰ� �߻��� ���̹Ƿ� ó���ؾ� �մϴ�.
// ó���ϱ� ���� ���� �ε����� Ȯ���ϱ� ���� index������ ���� ���� hashcode�� �ְ� hashtable[index]���� -1�� �� �� ���� �ݺ����� �����մϴ�.
// �׷��� index ���� (++index) % MAX_HASH_TABLE_SIZE�� -1�� �� �� ���� ��� �����մϴ�
// -1�� �Ǹ� �ʱ⿡ ������ ������ �� ���̱⿡ �� �ڸ��� key���� �����ϸ� �˴ϴ�.

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

// �� �Լ��� �޴����� e�� ������ �� ����Ǵ� �Լ��Դϴ�. �Է¹��� key���� ��ġ�� Ȯ���մϴ�.
// index ������ hashCode(key)���� �ֽ��ϴ�. ht�� index ���� key���� ���ٸ� index�� �����մϴ�.
// �׷��� �ʴٸ� index�� key���� ������ �� ���� ���� ������ �ø��鼭 index ���� index % MAX_HASH_TABLE_SIZE ������ �����մϴ�.
// �׸��� key���� �������� �ݺ����� �������� �׶��� index���� �����մϴ�.