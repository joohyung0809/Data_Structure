#include <stdio.h>
#include <stdlib.h>
void main()
{
	int list[5];
	int* plist[5] = { NULL, };
	plist[0] = (int*)malloc(sizeof(int));
	list[0] = 1;
	list[1] = 100;
	*plist[0] = 200;
	printf("----- [오주형]  [2019023028] -----\n");
	printf("value of list[0] = %d\n", list[0]);
	printf("address of list[0] = %p\n", &list[0]);
	printf("value of list = %p\n", list);
	printf("address of list (&list) = %p\n", &list);
	printf("----------------------------------------\n\n");
	printf("value of list[1] = %d\n", list[1]);
	printf("address of list[1] = %p\n", &list[1]);
	printf("value of *(list+1) = %d\n", *(list + 1));
	printf("address of list+1 = %p\n", list + 1);
	printf("----------------------------------------\n\n");
	printf("value of *plist[0] = %d\n", *plist[0]);
	printf("&plist[0] = %p\n", &plist[0]);
	printf("&plist = %p\n", &plist);
	printf("plist = %p\n", plist);
	printf("plist[0] = %p\n", plist[0]);
	printf("plist[1] = %p\n", plist[1]);
	printf("plist[2] = %p\n", plist[2]);
	printf("plist[3] = %p\n", plist[3]);
	printf("plist[4] = %p\n", plist[4]);
	free(plist[0]);
}

// ap1 소스코드는 1차원 배열의 주소갑과 실제값을 어떻게 구하는지 알아보는 코드입니다.
// 배열의 값을 알아내고 싶으면 [] 안에 인덱스 값을 넣어서 출력하면 됩니다.
// 배열의 주소값은 &를 붙여 출력하면 됩니다. 이때 배열의 이름만 붙인다면 배열의 첫번째 값의 주소가 출렵됩니다.
// 또한, 배열의 이름 자체도 배열의 첫번째 값의 주소입니다.
//
// 다음으로 배열에 포인터를 써서 실제 값에 접근할 수 있습니다.
// *(list + 1)와 같이 list에 일정 값을 더하고 포인터를 이용하면 실제 값에 접근할 수 있습니다.
//
// 다음은 포인터 배열의 주소값과 실제값을 구하는 것입니다.
// 위에서 *plist[0]에 200을 넣었으므로 *plist[0]의 값은 200이 나옵니다.
// 포인터 배열에서도 주소값을 구하고 싶을 때는 &를 붙여서 출력합니다.
// 이것 또한 배열의 이름만 붙이거나, 배열의 이름자체를 출력해도 배열의 첫번째 값의 주소가 출력됩니다.
// 포인터 배열에 *를 붙이지 않고 배열의 값들을 출력해보면 주소값이 나옵니다. 
// 여기에서 plist[0]의 값만 주소가 할당된 이유는 malloc함수로 plist[0]만 메모리 할당을 해주었기 때문입니다.
// 참고로 malloc함수로 할당한 메모리 사용이 끝나면 free함수로 반드시 없애주어야 메모리의 낭비가 이루어지지 않습니다.