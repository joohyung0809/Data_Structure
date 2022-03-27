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
	printf("----- [오주형]  [2019023028] -----\n");
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

// struct.c 소스코드는 구조체에 값을 입력하는 방법과, 구조체의 구조를 치환할 수 있는지
// 구조체 선언할 때 typedef를 쓰면 어떤 것이 다른지, 그리고 구조의 동등성 검사가 가능한지 알아보는 코드입니다.
// 먼저 구조체에 값을 입력하려면 main함수에서 선언한 구조체 이름과 그 안의 내용을 .과 함께 써주면 됩니다.
// 즉 st1.lastName, st2.studentId와 같은 형태로 구조체에 값을 입력하면 됩니다.
// 그리고 구조체의 치환 즉, 똑같은 구조체를 =을 통해 만들 수 있습니다.
// 하지만 ==을 통해 구조체 구조가 동등한지 검사하는 방법은 불가능합니다.
// /* not working */ 부분을 주석처리 하지 않고 실행하면 에러가 발생하는 것으로 이를 증명할 수 있습니다.
// 마지막으로 struct 대신 typedef를 사용하면 main함수에서 구조체 이름을 만들 때 struct를 작성하지 않아도 됩니다.
// 위처럼 struct student1 형태는 main함수에서 struct student1 st1으로 선언했지만
// typedef struct{} student2 형태는 struct 없이 student2 st2로 선언할 수 있다는 점이 차이점입니다.