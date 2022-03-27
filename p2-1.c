#include <stdio.h>
#define MAX_SIZE 100
float sum(float [], int);
float input[MAX_SIZE], answer;
int i;
void main(void)
{
	printf("----- [오주형]  [2019023028] -----\n");
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
// p2-1.c 소스코드에서는 사용자 정의 함수를 사용한 후 배열들의 주소값 변화를 파악하는 코드입니다.
// float sum 함수에서 input이 float list[]로, MAX_SIZE가 int n으로 사용되었습니다.
// 즉, sum함수가 호출 시 input은 주소를 담고 있고 주소가 sum함수의 list에 복사됩니다.
// 그래서 list값을 출력하면 input의 주소가 출력되는 것입니다.
// 이는 call by reference로 input의 주소를 list가 받아 input배열을 list를 통해 접근합니다.
// n은 call by value로 값을 그대로 n에 복사합니다. n이 변경 되어도 caller의 값은 변하지 않습니다.
// 마지막으로 float tempsum에서 i를 0부터 n(MAX_SIZE) 까지 반복하여 i값을 tempsum에 계속 더한 후 tempsum을 반환합니다.
// 그래서 main함수에서 answer에 반환된 tempsum(4950)이 float형으로 들어가게 됩니다.