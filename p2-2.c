#include <stdio.h>
void print1(int* ptr, int rows);
int main()
{
	printf("----- [������]  [2019023028] -----\n");
	int one[] = { 0, 1, 2, 3, 4 };
	printf("one = %p\n", one);
	printf("&one = %p\n", &one);
	printf("&one[0] = %p\n", &one[0]);
	printf("\n");
	print1(&one[0], 5);
	return 0;
}
void print1(int* ptr, int rows)
{/* print out a one-dimensional array using a pointer */
	int i;
	printf("Address \t Contents\n");
	for (i = 0; i < rows; i++)
		printf("%p \t %5d\n", ptr + i, *(ptr + i));
	printf("\n");
}
// p2-2.c �ҽ��ڵ忡���� �迭�� �ּҰ� �񱳿� �迭�� �ּҿ� ���������� �����ͷ� ǥ���ϴ� ����� �˾ƺ��� �ڵ��Դϴ�.
// one�̶�� �迭�� �ּҸ� ǥ���ϴ� ����� �迭�� �̸�(one)�� ����ϰų�, &�� ���̰ų�
// &one[0]�� �Է��մϴ�. �迭�� �̸��̳� &�� �ٿ��� ����ϴ� ���� �迭�� ù��° ���� �ּҰ��̱� �����Դϴ�.
// 
// �������� �迭�� �������� �����ͷ� ��Ÿ���� ����� ���� �˾ƺ��ҽ��ϴ�.
// print1(&one[0], 5)�� ���� �����͸� �� �� �ְ� �߽��ϴ�.
// ptr�� Ư�� ���� ���ϸ� ���Ѹ�ŭ �迭�� �ּҰ��� ��µ˴ϴ�.
// �׸��� �̰Ϳ� *���� ���̸� �迭�� �������� ����� �� �ֽ��ϴ�. �ּҿ� *�� ���̸� ���� ���� �ҷ����� �����Դϴ�.
