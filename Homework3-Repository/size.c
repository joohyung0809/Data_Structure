#include<stdio.h>
#include<stdlib.h>
void main()
{
	printf("----- [오주형]  [2019023028] -----\n");
	int** x;
	printf("sizeof(x) = %lu\n", sizeof(x));
	printf("sizeof(*x) = %lu\n", sizeof(*x));
	printf("sizeof(**x) = %lu\n", sizeof(**x));
}

// size.c 소스코드에서는 이중포인터가 선언되었을 때 포인터 변수와 포인터들의 크기에 대하여 알아보는 코드입니다.
// 포인터 변수, 포인터(이중 포인터 포함)는 모두 4bytes 만큼의 메모리가 할당 됩니다.
