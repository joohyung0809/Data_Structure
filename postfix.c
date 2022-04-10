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

 /* stack ������ �켱����, lparen = 0 ���� ���� */
typedef enum {
	lparen = 0,  /* ( ���� ��ȣ */
	rparen = 9,  /* ) ������ ��ȣ*/
	times = 7,   /* * ���� */
	divide = 6,  /* / ������ */
	plus = 5,    /* + ���� */
	minus = 4,   /* - ���� */
	operand = 1 /* �ǿ����� */
} precedence;

char infixExp[MAX_EXPRESSION_SIZE];   	/* infix expression�� �����ϴ� �迭 */
char postfixExp[MAX_EXPRESSION_SIZE];	/* postfix�� ����� ���ڿ��� �����ϴ� �迭 */
char postfixStack[MAX_STACK_SIZE];	/* postfix�� ��ȯ�� ���� �ʿ��� ���� */
int evalStack[MAX_STACK_SIZE];		/* ����� ���� �ʿ��� ���� */

int postfixStackTop = -1;  /* postfixStack�� top */
int evalStackTop = -1;	   /* evalStack�� top */

int evalResult = 0;	   /* ��� ����� ���� */

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
	printf("[----- [������] [2019023028] -----]\n\n");

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

// �� �Լ��� infix ǥ���� scanf�� �Է¹޾� infixExp�� �迭�� �����ϴ� �Լ��Դϴ�.
// infixExp�� ������ �����ߵ��� infix ǥ���� �����ϴ� �迭�Դϴ�.

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

/* �����ϳ��� ���޹޾�, postfixExp�� �߰�*/
void charCat(char* c)
{
	if (postfixExp == '\0')
		strncpy(postfixExp, c, 1);
	else
		strncat(postfixExp, c, 1);
}


void toPostfix()
{
	char* exp = infixExp; /* infixExp�� ���� �ϳ����� �б����� ������ */
	char x; /* �����ϳ��� �ӽ÷� �����ϱ� ���� ���� */

	/* exp�� �������Ѱ��鼭, ���ڸ� �а� postfix�� ���� */
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

// �� �Լ��� �޴� p�� ������ ����˴ϴ�. infix ǥ���� ��� �ִ� infixExp�� ���ڸ� �ϳ��� �о�鼭 stack�� �̿��Ͽ� postfix�� �����ϴ� �Լ��Դϴ�.
// �Լ��� �ڼ��� ���캸�ڽ��ϴ�.
// ���� infixExp �迭�� �ϳ��� �б� ���� exp��� ������ ������ �����߽��ϴ�. 
// �׸��� �� ���� �ϳ��� �����ϱ� ���� char���� x�� �����߽��ϴ�.
 
// ���� �ݺ����� �̿��Ͽ� ���ڰ� \0�� �ƴ� ���� infix�� postfix ���·� �ٲٴ� �ڵ带 if���� ���� �ۼ��߽��ϴ�
// ù��° ������ *exp�� '('�� ���Դϴ�. infix ǥ������ '(' ��ȣ�� ���� �켱������ ������ postfix ǥ�������� ���� �����ϴ�.
// �׷��� *exp�� '('��� postfixPush() ����Ͽ� �� ���� postfixStack[++postfixStackTop]�� �����մϴ�.
// �ι�° ������ nfix�� ')'�� ���Դϴ�. ')' ���Դٴ� ���� �տ� '(' ���Դٴ� ���̱⿡
// ���ݱ��� ���� ������ postfixPop���� ������ '('�� ������ ������ charCat �Լ��� �ݺ��մϴ�.
// ����� charCat�Լ��� postfixExp�� ����ִ� ���� ������ �Լ� ���ڿ� ��� ���� postfixExp�� strncpy�ϰ�, �׷��� ������ strncat���� �����մϴ�.
// ����° ������ *exp�� operand�� ���Դϴ�. �̶��� �ٷ� charCat�Լ��� ����ؼ� postfixExp�� �����ָ� �˴ϴ�.
// ������ ������ �� �̿��� ���� ��, �����ڰ� ������ �� �Դϴ�.
// �̶��� *exp�� postfixStack[postfixStackTop]�� �켱������ ���ؾ� �մϴ�. �� postfixStack���� top�� �ִ� �����ڿ� ���Ѵٴ� ���Դϴ�.
// *exp�� �� ���� ��쿡�� charCat�Լ��� ����Ͽ� postfixExp�� �����ְ�, �� ������ ���������� postfixPush(*exp);�� ���� postfixStack[++postfixStackTop]�� �����մϴ�.
// �� ���� if���� �� �˻��ϸ� exp�� ���� 1�÷��༭ infixExp�� ��� ��ġ�� ������ �� �ְ� �մϴ�.
// ���������� ����� postfix�� postFixExp�� �����ϱ� ���� postfixStackTop �� -1�� �ƴ� ���� x�� postfixPop()�� ���� ���� �ְ�
// charCat�Լ��� postfixExp�迭�� ���� ��� �����մϴ�.


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

// �� �Լ��� �޴� d�� ������ ��µ˴ϴ�. ������ ���� ���¸� ��Ÿ���� �Լ��Դϴ�.
// ù��°�� infixExp �迭�� ����ϰ� �ι�°�� postfixExp �迭�� ����ϰ� ����°�� evalResult ���� ����մϴ�.
// ���� infix ǥ��, postfixǥ��, ��� ������� �ǹ��մϴ�.
// ���������� ���ݱ��� ���ÿ� ���� ���� ����մϴ�. �̴� for���� �̿��Ͽ� MAX_STACK_SIZE��ŭ �ݺ��մϴ�.
// postfixStack[i]�� �̿��Ͽ� ���ÿ� ����ִ� ��� ���� ����� �� �ֽ��ϴ�.

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

// �� �Լ��� �޴� r�� ������ ��µ˴ϴ�. ���� �Էµ� ���¸� �ʱ�ȭ�ϴ� �Լ��Դϴ�.
// ù��°�� infixExp �迭�� �ʱ�ȭ�ϰ� �ι�°�� postfixExp �迭�� �ʱ�ȭ�մϴ�.
// ����°�� postfixStack�� ����ִ� ��� ���� �ʱ�ȭ�մϴ�. �̸� ���ؼ� for���� ����߽��ϴ�.
// MAX_STACK_SIZE ��ŭ �ݺ��ϸ鼭 postfixStack[i]�� �̿��Ͽ� ������ ��� ���� �����Ͽ� �ʱ�ȭ�� �߽��ϴ�.
// ���������� postfixStackTop�� evalStackTop�� -1�� �ʱ�ȭ�߰�, evalResult�� 0���� �ʱ�ȭ �߽��ϴ�.

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
			evalPush(symbol - '0'); // char���� int�� �ٲ��ֱ� ���� -'0'
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

// �� �Լ��� �޴� e�� ������ ��µ˴ϴ�. postfixǥ������ �ٲ� ������ ����ϴ� �Լ��Դϴ�.
// ���� �ǿ����� element1, element2�� �����ϰ�, getToken�Լ����� ����� symbol�� �����߽��ϴ�.
// �׸��� for���� ����ؾ��ϴµ� postfixExp�� ���̸�ŭ �ݺ��ؾ� �ϱ⿡ strlen�� ����Ͽ� length�� �����߽��ϴ�.
// �������� ����ϴ� �ڵ带 ���캸�ڽ��ϴ�.
// for���� �̿��Ͽ� postfixExp�� �� �ڸ��� �����Ͽ� �� ���� symbol�� �־����ϴ�.
// �׸��� symbol�� operand��� evalPush�� ����Ͽ� evalStack[++evalStackTop]�� �����մϴ�.
// operand�� �ƴ� ��� ������ �����ؾߵǱ� ������ evalPop()�� �̿��Ͽ� �־�ξ��� �ǿ����ڸ� �����ɴϴ�.
// �̶� symbol�� operand�� �ƴϾ����� plus, minus, times, divide���� Ȯ���Ͽ� ������ �� evalPush�� ����Ͽ� evalStack�� �ٽ� �����մϴ�.
// ������ ��� ������ ����� evalStack�� ����Ǿ� �����״�, ���������� evalResult�� evalPop() �Լ��� ����Ͽ� ������� �����մϴ�.