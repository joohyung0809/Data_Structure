#include <stdio.h>
struct student {
	char lastName[13]; /* 13 bytes */
	int studentId; /* 4 bytes */
	short grade; /* 2 bytes */
};
int main()
{
	printf("----- [������]  [2019023028] -----\n");
	struct student pst;
	printf("size of student = %ld\n", sizeof(struct student));
	printf("size of int = %ld\n", sizeof(int));
	printf("size of short = %ld\n", sizeof(short));
	return 0;
}
// padding.c �ҽ��ڵ忡���� ����ü�� ����鿡 �Ҵ�ǰ� �ִ� �޸� ũ�⿡ ���� �˾ƺ��� �ڵ��Դϴ�.
// ����ü�� ���� �� �� char�� 13�� int�� 1�� short�� 1���� ���� �߽��ϴ�.
// char���� 1���� 1byte, int���� 1���� 4bytes, short���� 1���� 2bytes�Դϴ�.
// �׷��� �Ի�����δ� 19bytes�� ���;� �մϴ�. ������ struct Student�� ũ�⸦ ������� �� 24bytes�� ���Խ��ϴ�.
// �̴� �޸𸮰� 4, 8, 16 ���� ����� �Ҵ�Ǿ� ����� padding bytes������ ����� �˴ϴ�.
// ��, lastName[13]�� 13bytes�� 3bytes�� padding bytes�� �����, short grade�� 2bytes�� padding bytes�� ����ϴ�.
// ���� struct Student�� �Ҵ�� �޸𸮴� padding bytes���� ��ģ 24bytes�� �˴ϴ�.