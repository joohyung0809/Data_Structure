#include <stdio.h>
#include <stdlib.h>
void main()
{
	int list[5];
	int* plist[5];
	list[0] = 10;
	list[1] = 11;
	plist[0] = (int*)malloc(sizeof(int));
	printf("----- [������]  [2019023028] -----\n");
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
// ap2.c �ҽ��ڵ忡���� �迭���� �ּҰ���¿� ���� �ڵ��Դϴ�.
// �ּҰ� ����ϴ� �κ��� ���� list, &list[0], list + 0�� ���� ��� ���� ���� ���ɴϴ�.
// ��, list�� �̸��� list�� ù��° ���� �ּҿ� ���ٴ� ���� �� �� �ֽ��ϴ�.
// �߰��� �迭�� �̸�(list)�� ���� ���Ͽ� ����ϸ�, ���� ����ŭ ���� ���� �ּҸ� ����մϴ�.