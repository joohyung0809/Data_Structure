/* postfix.c
 *
 *  Data Structures, Homework #5
 *  Department of Computer Science at Chungbuk National University
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_STACK_SIZE 10
#define MAX_EXPRESSION_SIZE 20

 /* stack 내에서 우선순위, lparen = 0 가장 낮음 */
typedef enum {
	lparen = 0,  /* ( 왼쪽 괄호 */
	rparen = 9,  /* ) 오른쪽 괄호*/
	times = 7,   /* * 곱셈 */
	divide = 6,  /* / 나눗셈 */
	plus = 5,    /* + 덧셈 */
	minus = 4,   /* - 뺄셈 */
	operand = 1 /* 피연산자 */
} precedence;

char infixExp[MAX_EXPRESSION_SIZE];   	/* infix expression을 저장하는 배열 */
char postfixExp[MAX_EXPRESSION_SIZE];	/* postfix로 변경된 문자열을 저장하는 배열 */
char postfixStack[MAX_STACK_SIZE];	/* postfix로 변환을 위해 필요한 스택 */
int evalStack[MAX_STACK_SIZE];		/* 계산을 위해 필요한 스택 */

int postfixStackTop = -1;  /* postfixStack용 top */
int evalStackTop = -1;	   /* evalStack용 top */

int evalResult = 0;	   /* 계산 결과를 저장 */

void postfixpush(char x);
char postfixPop();
void evalPush(int x);
int evalPop();
void getInfix();
precedence getToken(char symbol);
precedence getPriority(char x);
void charCat(char* c);
void toPostfix();
void debug();
void reset();
void evaluation();

int main()
{
	char command;
	printf("[----- [오주형] [2019023028] -----]\n\n");

	do {
		printf("----------------------------------------------------------------\n");
		printf("               Infix to Postfix, then Evaluation               \n");
		printf("----------------------------------------------------------------\n");
		printf(" Infix=i,   Postfix=p,  Eval=e,   Debug=d,   Reset=r,   Quit=q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command) {
		case 'i': case 'I':
			getInfix();
			break;
		case 'p': case 'P':
			toPostfix();
			break;
		case 'e': case 'E':
			evaluation();
			break;
		case 'd': case 'D':
			debug();
			break;
		case 'r': case 'R':
			reset();
			break;
		case 'q': case 'Q':
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	return 1;
}

void postfixPush(char x)
{
	postfixStack[++postfixStackTop] = x;
}

char postfixPop()
{
	char x;
	if (postfixStackTop == -1)
		return '\0';
	else {
		x = postfixStack[postfixStackTop--];
	}
	return x;
}

void evalPush(int x)
{
	evalStack[++evalStackTop] = x;
}

int evalPop()
{
	if (evalStackTop == -1)
		return -1;
	else
		return evalStack[evalStackTop--];
}


void getInfix()
{
	printf("Type the expression >>> ");
	scanf("%s", infixExp);
}

// 이 함수는 infix 표현을 scanf로 입력받아 infixExp의 배열에 저장하는 함수입니다.
// infixExp는 위에서 정의했듯이 infix 표현을 저장하는 배열입니다.

precedence getToken(char symbol)
{
	switch (symbol) {
	case '(': return lparen;
	case ')': return rparen;
	case '+': return plus;
	case '-': return minus;
	case '/': return divide;
	case '*': return times;
	default: return operand;
	}
}

precedence getPriority(char x)
{
	return getToken(x);
}

/* 문자하나를 전달받아, postfixExp에 추가*/
void charCat(char* c)
{
	if (postfixExp == '\0')
		strncpy(postfixExp, c, 1);
	else
		strncat(postfixExp, c, 1);
}


void toPostfix()
{
	char* exp = infixExp; /* infixExp의 문자 하나씩을 읽기위한 포인터 */
	char x; /* 문자하나를 임시로 저장하기 위한 변수 */

	/* exp를 증가시켜가면서, 문자를 읽고 postfix로 변경 */
	while (*exp != '\0')
	{
		if (getPriority(*exp) == lparen)
		{
			postfixPush(*exp);
		}
		else if (getPriority(*exp) == rparen)
		{
			while ((x = postfixPop()) != '(')
			{
				charCat(&x);
			}
		}
		else if (getPriority(*exp) == operand)
		{
			x = *exp;
			charCat(&x);
		}
		else
		{
			while (getPriority(postfixStack[postfixStackTop]) >= getPriority(*exp))  
			{
				x = postfixPop();
				charCat(&x);
			}
			postfixPush(*exp);
		}
		exp++;
	}

	while (postfixStackTop != -1)
	{
		x = postfixPop();
		charCat(&x);
	}
}

// 이 함수는 메뉴 p를 누르면 실행됩니다. infix 표현을 담고 있는 infixExp의 문자를 하나씩 읽어가면서 stack을 이용하여 postfix로 변경하는 함수입니다.
// 함수를 자세히 살펴보겠습니다.
// 먼저 infixExp 배열을 하나씩 읽기 위해 exp라는 포인터 변수를 선언했습니다. 
// 그리고 이 문자 하나를 저장하기 위해 char형의 x를 선언했습니다.
 
// 이제 반복문을 이용하여 문자가 \0이 아닌 동안 infix를 postfix 형태로 바꾸는 코드를 if문을 통해 작성했습니다
// 첫번째 조건은 *exp가 '('일 때입니다. infix 표현에서 '(' 괄호는 가장 우선순위가 높지만 postfix 표현에서는 가장 낮습니다.
// 그래서 *exp가 '('라면 postfixPush() 사용하여 그 값을 postfixStack[++postfixStackTop]에 저장합니다.
// 두번째 조건은 nfix가 ')'일 때입니다. ')' 나왔다는 것은 앞에 '(' 나왔다는 것이기에
// 지금까지 들어갔던 수들을 postfixPop으로 빼내서 '('이 나오기 전까지 charCat 함수를 반복합니다.
// 참고로 charCat함수는 postfixExp에 들어있는 값이 없으면 함수 인자에 담긴 값을 postfixExp로 strncpy하고, 그렇지 않으면 strncat으로 결합합니다.
// 세번째 조건은 *exp가 operand일 때입니다. 이때는 바로 charCat함수를 사용해서 postfixExp로 보내주면 됩니다.
// 마지막 조건은 그 이외의 조건 즉, 연산자가 들어왔을 때 입니다.
// 이때는 *exp와 postfixStack[postfixStackTop]의 우선순위를 비교해야 합니다. 즉 postfixStack에서 top에 있는 연산자와 비교한다는 것입니다.
// *exp가 더 작은 경우에만 charCat함수를 사용하여 postfixExp로 보내주고, 그 조건을 빠져나오면 postfixPush(*exp);를 통해 postfixStack[++postfixStackTop]에 저장합니다.
// 한 차례 if문을 다 검사하면 exp의 값을 1늘려줘서 infixExp의 모든 위치에 접근할 수 있게 합니다.
// 마지막으로 변경된 postfix는 postFixExp에 저장하기 위해 postfixStackTop 가 -1이 아닌 동안 x에 postfixPop()을 해준 값을 넣고
// charCat함수로 postfixExp배열에 갑을 모두 저장합니다.


void debug()
{
	printf("\n---DEBUG\n");
	printf("infixExp =  %s\n", infixExp);
	printf("postExp =  %s\n", postfixExp);
	printf("eval result = %d\n", evalResult);

	printf("postfixStack : "); 
	for (int i = 0; i < MAX_STACK_SIZE; i++)
		printf("%c  ", postfixStack[i]);

	printf("\n");
}

// 이 함수는 메뉴 d를 누르면 출력됩니다. 스택의 현재 상태를 나타내는 함수입니다.
// 첫번째로 infixExp 배열을 출력하고 두번째로 postfixExp 배열을 출력하고 세번째로 evalResult 값을 출력합니다.
// 각각 infix 표현, postfix표현, 계산 결과값을 의미합니다.
// 마지막으로 지금까지 스택에 들어갔던 것을 출력합니다. 이는 for문을 이용하여 MAX_STACK_SIZE만큼 반복합니다.
// postfixStack[i]를 이용하여 스택에 들어있는 모든 값을 출력할 수 있습니다.

void reset()
{
	infixExp[0] = '\0';
	postfixExp[0] = '\0';

	for (int i = 0; i < MAX_STACK_SIZE; i++)
		postfixStack[i] = '\0';

	postfixStackTop = -1;
	evalStackTop = -1;
	evalResult = 0;
}

// 이 함수는 메뉴 r를 누르면 출력됩니다. 현재 입력된 상태를 초기화하는 함수입니다.
// 첫번째로 infixExp 배열을 초기화하고 두번째로 postfixExp 배열을 초기화합니다.
// 세번째로 postfixStack에 들어있는 모든 값을 초기화합니다. 이를 위해서 for문을 사용했습니다.
// MAX_STACK_SIZE 만큼 반복하면서 postfixStack[i]를 이용하여 스택의 모든 값에 접근하여 초기화를 했습니다.
// 마지막으로 postfixStackTop과 evalStackTop을 -1로 초기화했고, evalResult를 0으로 초기화 했습니다.

void evaluation()
{
	int element1, element2;
	char symbol;
	int length = strlen(postfixExp);
	evalStackTop = -1;

	for (int i = 0; i < length; i++)
	{
		symbol = postfixExp[i];
		if (getToken(symbol) == operand)
		{
			evalPush(symbol - '0'); // char형을 int로 바꿔주기 위해 -'0'
		}
		else
		{
			element2 = evalPop();
			element1 = evalPop();
			switch (getToken(symbol)) {
			case plus: evalPush(element1 + element2); break;
			case minus: evalPush(element1 - element2); break;
			case times: evalPush(element1 * element2); break;
			case divide: evalPush(element1 / element2); break;
			default: break;
			}
		}
	}
	evalResult = evalPop();
}

// 이 함수는 메뉴 e를 누르면 출력됩니다. postfix표현으로 바뀐 수식을 계산하는 함수입니다.
// 먼저 피연산자 element1, element2를 선언하고, getToken함수에서 사용할 symbol을 선언했습니다.
// 그리고 for문을 사용해야하는데 postfixExp의 길이만큼 반복해야 하기에 strlen를 사용하여 length를 정의했습니다.
// 다음으로 계산하는 코드를 살펴보겠습니다.
// for문을 이용하여 postfixExp를 한 자리씩 접근하여 그 값을 symbol에 넣었습니다.
// 그리고 symbol이 operand라면 evalPush를 사용하여 evalStack[++evalStackTop]에 저장합니다.
// operand가 아닌 경우 연산을 수행해야되기 때문에 evalPop()을 이용하여 넣어두었던 피연산자를 가져옵니다.
// 이때 symbol이 operand가 아니었으니 plus, minus, times, divide인지 확인하여 연산한 후 evalPush를 사용하여 evalStack에 다시 저장합니다.
// 연산이 모두 끝나면 결과가 evalStack에 저장되어 있을테니, 마지막으로 evalResult에 evalPop() 함수를 사용하여 결과값을 저장합니다.