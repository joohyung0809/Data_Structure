#include <stdio.h>
int main()
{
	printf("[----- [오주형]  [2019023028] -----]\n");
	int i;
	int *ptr;
	int **dptr;
	i = 1234;
	printf("[checking values before ptr = &i] \n");
	printf("value of i == %d\n", i);
	printf("address of i == %p\n", &i);
	printf("value of ptr == %p\n", ptr);
	printf("address of ptr == %p\n", &ptr);
	ptr = &i; /* ptr is now holding the address of i */
	printf("\n[checking values after ptr = &i] \n");
	printf("value of i == %d\n", i);
	printf("address of i == %p\n", &i);
	printf("value of ptr == %p\n", ptr);
	printf("address of ptr == %p\n", &ptr);
	printf("value of *ptr == %d\n", *ptr);
	dptr = &ptr; /* dptr is now holding the address of ptr */
	printf("\n[checking values after dptr = &ptr] \n");
	printf("value of i == %d\n", i);
	printf("address of i == %p\n", &i);
	printf("value of ptr == %p\n", ptr);
	printf("address of ptr == %p\n", &ptr);
	printf("value of *ptr == %d\n", *ptr);
	printf("value of dptr == %p\n", dptr);
	printf("address of dptr == %p\n", &dptr);
	printf("value of *dptr == %p\n", *dptr);
	printf("value of **dptr == %d\n", **dptr);
	*ptr = 7777; /* changing the value of *ptr */
	printf("\n[after *ptr = 7777] \n");
	printf("value of i == %d\n", i);
	printf("value of *ptr == %d\n", *ptr);
	printf("value of **dptr == %d\n", **dptr);
	**dptr = 8888; /* changing the value of **dptr */
	printf("\n[after **dptr = 8888] \n");
	printf("value of i == %d\n", i);
	printf("value of *ptr == %d\n", *ptr);
	printf("value of **dptr == %d\n", **dptr);
	return 0;
}

//lab2-2과제는 처음 변수 선언 후 각 변수에 변화를 주면 값과 주소가 어떻게 변하는지 알아보는 것입니다.

//ptr = &i하기 전에는 i의 값과 주소에는 처음 선언 했을 때 값이 들어가고, ptr의 값에는 아직 아무것도 들어있지 않고 주소만 할당 되어있습니다.
 
//ptr = &i하고 나서는 ptr에는 i의 주소값이 들어가며 동시에 *ptr의 값은 i의 값인 1234가 들어갑니다. 이때 ptr의 주소는 처음 할당된 그대로입니다.
 
//다음으로 dptr = &ptr을 하면 이증 포인터 변수인 dptr에 ptr의 주소가 들어갑니다.
// 따라서 dptr의 주소는 처음 선언 할 때 할당된 값이 들어가고, dptr의 값은 ptr의 주소가 들어갑니다.
//그리고 *dptr은 ptr의 값 즉, i의 주소가 들어가며, **dptr은 *ptr의 값 즉, i의 값이 들어갑니다.
 
//다음으로 *ptr에 7777을 넣으면, *ptr은 i를 가리키고 있으면서 동시에 **dptr이 가리키고 있는 것이므로 i와 **dptr 모두 7777로 바뀝니다.
//다음으로 **dptr 8888을 널으면, **dptr은 *ptr을 가리키고, *ptr은 i를 가리키기에 *ptr과 i모두 8888로 바뀝니다.
//이를 통해 관계를 가지고 있는 변수와 포인터변수들 중 한 가지 값만 바뀌어도 모두 바뀐다는 것을 알게 되었습니다.