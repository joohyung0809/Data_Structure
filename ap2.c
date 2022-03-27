#include <stdio.h>
#include <stdlib.h>
void main()
{
	int list[5];
	int* plist[5];
	list[0] = 10;
	list[1] = 11;
	plist[0] = (int*)malloc(sizeof(int));
	printf("----- [오주형]  [2019023028] -----\n");
	printf("list[0] \t= %d\n", list[0]);
	printf("address of list \t= %p\n", list);
	printf("address of list[0] \t= %p\n", &list[0]);
	printf("address of list + 0 \t= %p\n", list + 0);
	printf("address of list + 1 \t= %p\n", list + 1);
	printf("address of list + 2 \t= %p\n", list + 2);
	printf("address of list + 3 \t= %p\n", list + 3);
	printf("address of list + 4 \t= %p\n", list + 4);
	printf("address of list[4] \t= %p\n", &list[4]);
	free(plist[0]);
}
// ap2.c 소스코드에서는 배열들의 주소값출력에 대한 코드입니다.
// 주소값 출력하는 부분을 보면 list, &list[0], list + 0의 값이 모두 같은 값이 나옵니다.
// 즉, list의 이름은 list의 첫번째 값의 주소와 같다는 것을 알 수 있습니다.
// 추가로 배열의 이름(list)에 값을 더하여 출력하면, 더한 값만큼 다음 값의 주소를 출력합니다.