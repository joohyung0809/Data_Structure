#include <stdio.h>

struct student1 {
	char lastName;
	int studentId;
	char grade;
};
typedef struct {
	char lastName;
	int studentId;
	char grade;
} student2;
int main() {
	printf("----- [������]  [2019023028] -----\n");
	struct student1 st1 = { 'A', 100, 'A' };
	printf("st1.lastName = %c\n", st1.lastName);
	printf("st1.studentId = %d\n", st1.studentId);
	printf("st1.grade = %c\n", st1.grade);
	student2 st2 = { 'B', 200, 'B' };
	printf("\nst2.lastName = %c\n", st2.lastName);
	printf("st2.studentId = %d\n", st2.studentId);
	printf("st2.grade = %c\n", st2.grade);
	student2 st3;
	st3 = st2;
	printf("\nst3.lastName = %c\n", st3.lastName);
	printf("st3.studentId = %d\n", st3.studentId);
	printf("st3.grade = %c\n", st3.grade);
	/* equality test */
	if (st3 == st2) /* not working */
		printf("equal\n");
	else
		printf("not equal\n");
	return 0;
}

// struct.c �ҽ��ڵ�� ����ü�� ���� �Է��ϴ� �����, ����ü�� ������ ġȯ�� �� �ִ���
// ����ü ������ �� typedef�� ���� � ���� �ٸ���, �׸��� ������ ��� �˻簡 �������� �˾ƺ��� �ڵ��Դϴ�.
// ���� ����ü�� ���� �Է��Ϸ��� main�Լ����� ������ ����ü �̸��� �� ���� ������ .�� �Բ� ���ָ� �˴ϴ�.
// �� st1.lastName, st2.studentId�� ���� ���·� ����ü�� ���� �Է��ϸ� �˴ϴ�.
// �׸��� ����ü�� ġȯ ��, �Ȱ��� ����ü�� =�� ���� ���� �� �ֽ��ϴ�.
// ������ ==�� ���� ����ü ������ �������� �˻��ϴ� ����� �Ұ����մϴ�.
// /* not working */ �κ��� �ּ�ó�� ���� �ʰ� �����ϸ� ������ �߻��ϴ� ������ �̸� ������ �� �ֽ��ϴ�.
// ���������� struct ��� typedef�� ����ϸ� main�Լ����� ����ü �̸��� ���� �� struct�� �ۼ����� �ʾƵ� �˴ϴ�.
// ��ó�� struct student1 ���´� main�Լ����� struct student1 st1���� ����������
// typedef struct{} student2 ���´� struct ���� student2 st2�� ������ �� �ִٴ� ���� �������Դϴ�.