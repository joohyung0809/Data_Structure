#include <stdio.h>

int main()
{
	char charType;
	int integerType;
	float floatType;
	double doubleType;
	printf("[-----[������]  [2019023028] -----]\n");
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

	//�̹� lab2-1������ �� �ڷ����� �Ҵ�Ǵ� �޸� ũ�⿡ ���� �˾ƺ��� �����Դϴ�.
	//char�� ���ǵ� charType �� char Ÿ���� ũ��� 1byte�̴�.
	//int�� ���ǵ� integerType �� int Ÿ���� ũ��� 4bytes�̴�.
	//float���� ���ǵ� floatType �� float Ÿ���� ũ��� 4bytes�̴�.
	//double�� ���ǵ� doubleType �� double Ÿ���� ũ��� 8bytes�̴�.
	//������ ��µ� 4���� ������ ���� �������� ũ�⸦ ����ϴ� ������ ��� ���� ���� 4bytes�� ��Ÿ���ϴ�.

}