#include <stdio.h>
void print1(int* ptr, int rows);
int main()
{
	printf("----- [오주형]  [2019023028] -----\n");
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
// p2-2.c 소스코드에서는 배열의 주소값 비교와 배열의 주소와 실제값들을 포인터로 표현하는 방법을 알아보는 코드입니다.
// one이라는 배열의 주소를 표현하는 방법은 배열의 이름(one)을 출력하거나, &를 붙이거나
// &one[0]을 입력합니다. 배열의 이름이나 &를 붙여서 출력하는 값이 배열의 첫번째 값의 주소값이기 때문입니다.
// 
// 다음으로 배열의 실제값을 포인터로 나타내는 방법에 대해 알아보았습니다.
// print1(&one[0], 5)을 통해 포인터를 쓸 수 있게 했습니다.
// ptr에 특정 값을 더하면 더한만큼 배열의 주소값이 출력됩니다.
// 그리고 이것에 *값을 붙이면 배열의 실제값을 출력할 수 있습니다. 주소에 *을 붙이면 실제 값을 불러오기 때문입니다.
