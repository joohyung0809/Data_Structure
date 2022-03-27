#include <stdio.h>
struct student {
	char lastName[13]; /* 13 bytes */
	int studentId; /* 4 bytes */
	short grade; /* 2 bytes */
};
int main()
{
	printf("----- [오주형]  [2019023028] -----\n");
	struct student pst;
	printf("size of student = %ld\n", sizeof(struct student));
	printf("size of int = %ld\n", sizeof(int));
	printf("size of short = %ld\n", sizeof(short));
	return 0;
}
// padding.c 소스코드에서는 구조체의 내용들에 할당되고 있는 메모리 크기에 대해 알아보는 코드입니다.
// 구조체를 선언 할 때 char형 13개 int형 1개 short형 1개를 선언 했습니다.
// char형은 1개에 1byte, int형은 1개에 4bytes, short형은 1개에 2bytes입니다.
// 그러면 게산상으로는 19bytes가 나와야 합니다. 하지만 struct Student의 크기를 출력했을 때 24bytes가 나왔습니다.
// 이는 메모리가 4, 8, 16 등의 배수로 할당되어 생기는 padding bytes때문에 생기게 됩니다.
// 즉, lastName[13]은 13bytes에 3bytes의 padding bytes가 생기고, short grade에 2bytes의 padding bytes가 생깁니다.
// 따라서 struct Student에 할당된 메모리는 padding bytes까지 합친 24bytes가 됩니다.