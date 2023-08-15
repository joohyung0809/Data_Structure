#include <stdio.h>
int main()
{
	printf("[----- [������]  [2019023028] -----]\n");
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

//lab2-2������ ó�� ���� ���� �� �� ������ ��ȭ�� �ָ� ���� �ּҰ� ��� ���ϴ��� �˾ƺ��� ���Դϴ�.

//ptr = &i�ϱ� ������ i�� ���� �ּҿ��� ó�� ���� ���� �� ���� ����, ptr�� ������ ���� �ƹ��͵� ������� �ʰ� �ּҸ� �Ҵ� �Ǿ��ֽ��ϴ�.
 
//ptr = &i�ϰ� ������ ptr���� i�� �ּҰ��� ���� ���ÿ� *ptr�� ���� i�� ���� 1234�� ���ϴ�. �̶� ptr�� �ּҴ� ó�� �Ҵ�� �״���Դϴ�.
 
//�������� dptr = &ptr�� �ϸ� ���� ������ ������ dptr�� ptr�� �ּҰ� ���ϴ�.
// ���� dptr�� �ּҴ� ó�� ���� �� �� �Ҵ�� ���� ����, dptr�� ���� ptr�� �ּҰ� ���ϴ�.
//�׸��� *dptr�� ptr�� �� ��, i�� �ּҰ� ����, **dptr�� *ptr�� �� ��, i�� ���� ���ϴ�.
 
//�������� *ptr�� 7777�� ������, *ptr�� i�� ����Ű�� �����鼭 ���ÿ� **dptr�� ����Ű�� �ִ� ���̹Ƿ� i�� **dptr ��� 7777�� �ٲ�ϴ�.
//�������� **dptr 8888�� ������, **dptr�� *ptr�� ����Ű��, *ptr�� i�� ����Ű�⿡ *ptr�� i��� 8888�� �ٲ�ϴ�.
//�̸� ���� ���踦 ������ �ִ� ������ �����ͺ����� �� �� ���� ���� �ٲ� ��� �ٲ�ٴ� ���� �˰� �Ǿ����ϴ�.