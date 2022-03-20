#include <stdio.h>

int main()
{
	char charType;
	int integerType;
	float floatType;
	double doubleType;
	printf("[-----[오주형]  [2019023028] -----]\n");
	printf("Size of char: %ld byte\n",sizeof(charType));
	printf("Size of int: %ld bytes\n",sizeof(integerType));
	printf("Size of float: %ld bytes\n",sizeof(floatType));
	printf("Size of double: %ld bytes\n",sizeof(doubleType));
	printf("-----------------------------------------\n");
	printf("Size of char: %ld byte\n",sizeof(char));
	printf("Size of int: %ld bytes\n",sizeof(int));
	printf("Size of float: %ld bytes\n",sizeof(float));
	printf("Size of double: %ld bytes\n",sizeof(double));
	printf("-----------------------------------------\n");
	printf("Size of char*: %ld byte\n",sizeof(char*));
	printf("Size of int*: %ld bytes\n",sizeof(int*));
	printf("Size of float*: %ld bytes\n",sizeof(float*));
	printf("Size of double*: %ld bytes\n",sizeof(double*));
	return 0;

	//이번 lab2-1에서는 각 자료형에 할당되는 메모리 크기에 대해 알아보는 과제입니다.
	//char로 정의된 charType 즉 char 타입의 크기는 1byte이다.
	//int로 정의된 integerType 즉 int 타입의 크기는 4bytes이다.
	//float으로 정의된 floatType 즉 float 타입의 크기는 4bytes이다.
	//double로 정의된 doubleType 즉 double 타입의 크기는 8bytes이다.
	//마지막 출력된 4줄은 전부 포인터 변수의 크기를 구하는 것이기에 모두 4bytes가 나온다.
	

}