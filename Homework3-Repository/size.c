#include<stdio.h>
#include<stdlib.h>
void main()
{
	printf("----- [������]  [2019023028] -----\n");
	int** x;
	printf("sizeof(x) = %lu\n", sizeof(x));
	printf("sizeof(*x) = %lu\n", sizeof(*x));
	printf("sizeof(**x) = %lu\n", sizeof(**x));
}

// size.c �ҽ��ڵ忡���� ���������Ͱ� ����Ǿ��� �� ������ ������ �����͵��� ũ�⿡ ���Ͽ� �˾ƺ��� �ڵ��Դϴ�.
// ������ ����, ������(���� ������ ����)�� ��� 4bytes ��ŭ�� �޸𸮰� �Ҵ� �˴ϴ�.
