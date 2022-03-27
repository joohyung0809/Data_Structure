#include <stdio.h>
#define MAX_SIZE 100
float sum(float [], int);
float input[MAX_SIZE], answer;
int i;
void main(void)
{
	printf("----- [������]  [2019023028] -----\n");
	for(i=0; i < MAX_SIZE; i++)
		input[i] = i;
	/* for checking call by reference */
	printf("address of input = %p\n", input);
	answer = sum(input, MAX_SIZE);
	printf("The sum is: %f\n", answer);
}
float sum(float list[], int n)
{
	printf("value of list = %p\n", list);
	printf("address of list = %p\n\n", &list);
	int i;
	float tempsum = 0;
	for(i = 0; i < n; i++)
		tempsum += list[i];
	return tempsum;
}
// p2-1.c �ҽ��ڵ忡���� ����� ���� �Լ��� ����� �� �迭���� �ּҰ� ��ȭ�� �ľ��ϴ� �ڵ��Դϴ�.
// float sum �Լ����� input�� float list[]��, MAX_SIZE�� int n���� ���Ǿ����ϴ�.
// ��, sum�Լ��� ȣ�� �� input�� �ּҸ� ��� �ְ� �ּҰ� sum�Լ��� list�� ����˴ϴ�.
// �׷��� list���� ����ϸ� input�� �ּҰ� ��µǴ� ���Դϴ�.
// �̴� call by reference�� input�� �ּҸ� list�� �޾� input�迭�� list�� ���� �����մϴ�.
// n�� call by value�� ���� �״�� n�� �����մϴ�. n�� ���� �Ǿ caller�� ���� ������ �ʽ��ϴ�.
// ���������� float tempsum���� i�� 0���� n(MAX_SIZE) ���� �ݺ��Ͽ� i���� tempsum�� ��� ���� �� tempsum�� ��ȯ�մϴ�.
// �׷��� main�Լ����� answer�� ��ȯ�� tempsum(4950)�� float������ ���� �˴ϴ�.