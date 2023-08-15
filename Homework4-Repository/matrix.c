#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Method Declaration */
int** create_matrix(int row, int col);
void print_matrix(int** matrix, int row, int col);
int free_matrix(int** matrix, int row, int col);
int fill_data(int** matrix, int row, int col);
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col);
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col);
int transpose_matrix(int** matrix, int** matrix_t, int row, int col);
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col);

int main()
{

    char command;
    printf("[----- [오주형]  [2019023028] -----]\n");

    int row, col;
    srand(time(NULL));

    printf("Input row and col : ");
    scanf("%d %d", &row, &col);
    int** matrix_a = create_matrix(row, col);
    int** matrix_b = create_matrix(row, col);
    int** matrix_a_t = create_matrix(col, row);

    printf("Matrix Created.\n");

    if (matrix_a == NULL || matrix_b == NULL) { return -1; }

    do {
        printf("----------------------------------------------------------------\n");
        printf("                     Matrix Manipulation                        \n");
        printf("----------------------------------------------------------------\n");
        printf(" Initialize Matrix   = z           Print Matrix        = p \n");
        printf(" Add Matrix          = a           Subtract Matrix     = s \n");
        printf(" Transpose matrix_a  = t           Multiply Matrix     = m \n");
        printf(" Quit                = q \n");
        printf("----------------------------------------------------------------\n");

        printf("Command = ");
        scanf(" %c", &command);

        switch (command) {
        case 'z': case 'Z':
            printf("Matrix Initialized\n");
            fill_data(matrix_a, row, col);
            fill_data(matrix_b, row, col);
            break;
        case 'p': case 'P':
            printf("Print matrix\n");
            printf("matrix_a\n");
            print_matrix(matrix_a, row, col);
            printf("matrix_b\n");
            print_matrix(matrix_b, row, col);
            break;
        case 'a': case 'A':
            printf("Add two matrices\n");
            addition_matrix(matrix_a, matrix_b, row, col);
            break;
        case 's': case 'S':
            printf("Subtract two matrices \n");
            subtraction_matrix(matrix_a, matrix_b, row, col);
            break;
        case 't': case 'T':
            printf("Transpose matrix_a \n");
            printf("matrix_a\n");
            transpose_matrix(matrix_a, matrix_a_t, col, row);
            print_matrix(matrix_a_t, col, row);
            break;
        case 'm': case 'M':
            printf("Multiply matrix_a with transposed matrix_a \n");
            transpose_matrix(matrix_a, matrix_a_t, col, row);
            multiply_matrix(matrix_a, matrix_a_t, row, col);
            break;
        case 'q': case 'Q':
            printf("Free all matrices..\n");
            free_matrix(matrix_a_t, col, row);
            free_matrix(matrix_a, row, col);
            free_matrix(matrix_b, row, col);
            break;
        default:
            printf("\n       >>>>>   Concentration!!   <<<<<     \n");
            break;
        }

    } while (command != 'q' && command != 'Q');

    return 1;
}

// 위 메인 함수는 실행하고 싶은 함수에 각각 단축기를 부여하여 실행될 수 있게 하는 함수입니다.

/* create a 2d array whose size is row x col using malloc() */
int** create_matrix(int row, int col)
{
    /* check pre conditions */
    if (row <= 0 || col <= 0) {
        printf("Check the sizes of row and col!\n");
        return NULL;
    }

    int** matrix = (int**)malloc(sizeof(int*) * row);
    for (int i = 0; i < row; i++)            // 세로 크기만큼 반복
    {
        matrix[i] = (int*)malloc(sizeof(int) * col);    // (int의 크기 * col)만큼 동적 메모리 할당. 배열의 가로
    }

    /* check post conditions */
    if (matrix == NULL) {
        printf("Memory Allocation Failed/\n");
        return NULL;
    }

    return matrix;
}

// int** create_matrix(int row, int col) 함수는 row와 col크기에 해당하는 행렬을 동적 메모리 할당으로 생성하는 함수입니다.
// 동적 메모리 할당을 위해 malloc함수를 사용하였습니다.
// 함수를 자세히 살펴보면 먼저 row에 해당하는 만큼 malloc함수를 호출하여 동적 메모리 할당을 했습니다.
// 다음으로 for문을 거치면서 row 1개당 col만큼 malloc함수를 호출하여 동적 메모리 할당을 했습니다.
// 그렇게 하면 main함수에서 받은 row, col의 값에 해당하는 행렬의 공간이 할당 됩니다.
// 다음으로 비정상적인 입력과 결과값이 발생하는 것에 대비하여 다음과 같은 코드를 작성했습니다.
// 함수의 처음에 row와 col이 0보다 작거나 같은 경우 즉 비정상적인 입력값이 입력되면 NULL을 return하게 했습니다.
// 그리고 행렬이 생성된 뒤에 NULL 값을 가지면 NULL을 return하게 했습니다.
// 이상이 없는 경우 matrix를 return합니다.

/* print matrix whose size is row x col */
void print_matrix(int** matrix, int row, int col)
{
    /* check pre conditions */
    if (row <= 0 || col <= 0) {
        printf("Check the sizes of row and col!\n");
        return;
    }

    for (int i = 0; i < row; i++)    // 세로 크기만큼 반복
    {
        for (int j = 0; j < col; j++)    // 가로 크기만큼 반복
        {
            printf("%3d ", matrix[i][j]);      // 2차원 배열의 인덱스에 반복문의 변수 i, j를 지정
        }
        printf("\n");
    }
    printf("\n");
    /* check post conditions */
    if (matrix == NULL) {
        printf("Memory Allocation Failed/\n");
        return;
    }

    return;
}

// void print_matrix(int** matrix, int row, int col) 함수는 앞서 생성했던 행렬의 값들을 출력하는 함수입니다.
// 여기서는 단순히 이중 for문을 통해 전체 행렬의 값을 표현했습니다.
// 함수를 자세히 살펴보면 matrix[i][j]와 같이 2차원 배열을 2중 for문을 통해 전체 값에 다 접근할 수 있게 만들었습니다.
// 다음으로 비정상적인 입력과 결과값이 발생하는 것에 대비하여 다음과 같은 코드를 작성했습니다.
// 함수의 처음에 row와 col이 0보다 작거나 같은 경우 즉 비정상적인 입력값이 입력되면 return 값이 없도록 했습니다.
// 그리고 행렬이 출력 준비를 마친 뒤에 NULL 값을 가지면 return값을 없도록 했습니다.



/* free memory allocated by create_matrix() */
int free_matrix(int** matrix, int row, int col)
{
    /* Check pre conditions */
    if (row <= 0 || col <= 0) {
        printf("Check the size of row and col!\n");
        return -1;
    }

    for (int i = 0; i < row; i++)    // 세로 크기만큼 반복
    {
        free(matrix[i]);                  // 2차원 배열의 가로 공간 메모리 해제
    }

    free(matrix);    // 2차원 배열의 세로 공간 메모리 해제
    return 1;
}

//int free_matrix(int** matrix, int row, int col)함수는 앞서 malloc으로 동적할당한 메모리를 해제하는 함수입니다.
// 즉 만들어진 행렬에 값을 넣었던 행렬이나, 행렬의 연산을 통해 새롭게 생성된 행렬의 메모리를 free함수를 통해 해제합니다.
// 함수를 자세히 살펴보면 for문으로 matrix[i]를 돌며 메모리를 해제합니다.
// 이때 이중 for문으로 해제해야한다고 생각할 수 있는데 2차원 배열의 경우 가로 공간의 메모리만 해제해도 모두 해제됩니다.
// 다음으로 비정상적인 입력과 결과값이 발생하는 것에 대비하여 다음과 같은 코드를 작성했습니다.
// 함수의 처음에 row와 col이 0보다 작거나 같은 경우 즉 비정상적인 입력값이 입력되면 return 값이 -1이 되도록 했습니다.
// 그리고 free를 통해 메모리가 해제되면 후처리 검사할 행렬이 없기에 검사 없이 return 값이 1이 되도록 했습니다.


/* assign random values to the given matrix */
int fill_data(int** matrix, int row, int col)
{
    /* Check pre conditions */
    if (row <= 0 || col <= 0) {
        printf("Check the size of row and col!\n");
        return -1;
    }

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            matrix[i][j] = rand() % 20;
        }
    }

    /* Check post conditions */
    if (matrix == NULL) {
        printf("Memory Allocation Failed.\n");
        return -1;
    }
    return 1;
}

// int fill_data(int** matrix, int row, int col) 함수는 create_matrix함수로 만들어진 행렬에
// 0~19사이의 값을 랜덤으로 부여하는 함수입니다. 
// 이 rand()함수를 2중 for문에 넣어 행렬의 모든 값에 접근하여 값을 할당하도록 했습니다.
// 함수를 자세히 살펴보면 matrix[i][j]를 2중 for문에 넣어 행렬의 모든 값에 접근합니다. 
// 그리고 rand() % 20; 으로 행렬에 값을 할당합니다.
// 여기서 % 20이라는 뜻은 0~19의 수를 의미합니다. 즉 %뒤에 붙은 숫자에서 -1을 뺀만큼의 수가 할당됩니다.
// 다음으로 비정상적인 입력과 결과값이 발생하는 것에 대비하여 다음과 같은 코드를 작성했습니다.
// 함수의 처음에 row와 col이 0보다 작거나 같은 경우 즉 비정상적인 입력값이 입력되면 return 값이 -1이 되도록 했습니다.
// 그리고 행렬의 값이 할당된 뒤에 NULL 값을 가지면 return값이 -1이 되도록 했습니다.
// 이상이 없는 경우 1을 return합니다.


/* matrix_sum = matrix_a + matrix_b */
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col)
{
    int** matrix_sum = create_matrix(row, col);
    /* Check pre conditions */
    if (row <= 0 || col <= 0) {
        printf("Check the size of row and col!\n");
        return -1;
    }

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            matrix_sum[i][j] = matrix_a[i][j] + matrix_b[i][j];
        }
    }

    /* Check post conditions */
    if (matrix_a == NULL || matrix_b == NULL || matrix_sum == NULL) {
        printf("Memory Allocation Failed.\n");
        return -1;
    }

    print_matrix(matrix_sum, row, col);
    free_matrix(matrix_sum, row, col);
    return 1;
}

// int addition_matrix(int** matrix_a, int** matrix_b, int row, int col)함수는 행렬의 덧셈을 수행하는 함수입니다.
// 행렬의 덧셈을 수행하기 위해 2중 for문을 이용하여 모든 행렬의 값에 접근하여 그 값들을 더했습니다.
// 함수를 자세히 살펴보면 int** matrix_sum = create_matrix(row, col);을 사용하여 덧셈 연산을 적용할 행렬을 생성합니다.
// matrix_a[i][j] + matrix_b[i][j]를 2중 for문에 넣어 행렬 a와 b의 각 값을 더하여  matrix_sum[i][j]에 넣습니다.
// 다음으로 비정상적인 입력과 결과값이 발생하는 것에 대비하여 다음과 같은 코드를 작성했습니다.
// 함수의 처음에 row와 col이 0보다 작거나 같은 경우 즉 비정상적인 입력값이 입력되면 return 값이 -1이 되도록 했습니다.
// 그리고  각 행렬들이 NULL 값을 가지면 return값이 -1이 되도록 했습니다.
// 이상이 없는 경우 1을 return합니다.

/* matrix_sub = matrix_a - matrix_b */
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col)
{
    int** matrix_sub = create_matrix(row, col);
    /* Check pre conditions */
    if (row <= 0 || col <= 0) {
        printf("Check the size of row and col!\n");
        return -1;
    }

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            matrix_sub[i][j] = matrix_a[i][j] - matrix_b[i][j];
        }
    }

    /* Check post conditions */
    if (matrix_a == NULL || matrix_b == NULL || matrix_sub == NULL) {
        printf("Memory Allocation Failed.\n");
        return -1;
    }
    print_matrix(matrix_sub, row, col);
    free_matrix(matrix_sub, row, col);

    return 1;
}

// int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col)함수는 행렬의 뺄셈 연산을 수행하는 함수입니다.
// 행렬의 뺄셈을 수행하기 위해 2중 for문을 이용하여 모든 행렬의 값에 접근하여 그 값들을 뺐습니다.
// 함수를 자세히 살펴보면 int** matrix_sub = create_matrix(row, col);을 사용하여 뺄셈 연산을 적용할 행렬을 생성합니다.
// matrix_a[i][j] - matrix_b[i][j]를 2중 for문에 넣어 행렬 a와 b의 각 값을 빼서  matrix_sub[i][j]에 넣습니다.
// 다음으로 비정상적인 입력과 결과값이 발생하는 것에 대비하여 다음과 같은 코드를 작성했습니다.
// 함수의 처음에 row와 col이 0보다 작거나 같은 경우 즉 비정상적인 입력값이 입력되면 return 값이 -1이 되도록 했습니다.
// 그리고  각 행렬들이 NULL 값을 가지면 return값이 -1이 되도록 했습니다.
// 이상이 없는 경우 1을 return합니다.

/* transpose the matrix to matrix_t */
int transpose_matrix(int** matrix, int** matrix_t, int row, int col)
{
    /* Check pre conditions */
    if (row <= 0 || col <= 0) {
        printf("Check the size of row and col!\n");
        return -1;
    }

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            matrix_t[i][j] = matrix[j][i];
        }
    }

    /* Check post conditions */
    if (matrix == NULL || matrix_t == NULL) {
        printf("Memory Allocation Failed.\n");
        return -1;
    }

    return 1;
}

// int transpose_matrix(int** matrix, int** matrix_t, int row, int col) 함수는 행렬의 전치 연산을 수행하는 함수입니다.
// 행렬의 전치 수행하기 위해 2중 for문을 이용하여 모든 행렬의 값에 접근하여 그 값들을 전치했습니다.
// 함수를 자세히 살펴보면 2중 for문에 matrix_t[i][j] = matrix[j][i];을 넣어 matrix 행렬을 전치한 값을 matrix_t에 넣었습니다.
// 다음으로 비정상적인 입력과 결과값이 발생하는 것에 대비하여 다음과 같은 코드를 작성했습니다.
// 함수의 처음에 row와 col이 0보다 작거나 같은 경우 즉 비정상적인 입력값이 입력되면 return 값이 -1이 되도록 했습니다.
// 그리고  각 행렬들이 NULL 값을 가지면 return값이 -1이 되도록 했습니다.
// 이상이 없는 경우 1을 return합니다.

/* matrix_axt - matrix_a x matrix_t */
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col)
{
    int** matrix_axt = create_matrix(row, col);
    /* Check pre conditions */
    if (row <= 0 || col <= 0) {
        printf("Check the size of row and col!\n");
        return -1;
    }

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            int temp = 0;
            for (int k = 0; k < col; k++) {
                temp += matrix_a[i][k] * matrix_t[k][j];
            }
            matrix_axt[i][j] = temp;
        }
        
    }
    /* Check post conditions */
    if (matrix_t == NULL || matrix_axt == NULL) {
        printf("Memory Allocation Failed.\n");
        return -1;
    }

    print_matrix(matrix_axt, row, col);
    free_matrix(matrix_axt, row, col);

    return 1;
}

// int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col)함수는 행렬의 곱 연산을 수행하는 함수입니다.
// 행렬의 곱을 수행하기 위해 2중 for문을 사용하여 matrix_a의 i행, matrix_t의 j열에 값에 모두 접근하여 곱했습니다.
// 행렬의 곱은  A의 i행의 각 성분과 B의 j열의 대응되는 성분의 곱을 모두 합한 것과 같습니다.
// 함수를 자세히 살펴보면 int** matrix_axt = create_matrix(row, col);을 사용하여 곱셈 연산을 적용할 행렬을 생성합니다.
//  matrix_a[i][k] * matrix_t[k][j];를 2중 for문에 넣어 곱을 구하고, temp를 사용해서 그 곱의 합을 계산하여 행렬의 곱을 연산했습니다.
// i를 포함한  for문이 1번 실행될 때 matrix_axt[i][j] = temp;를 이용하여 행렬의 곱셈 연산이 적용될 행렬에 temp값을 넣습니다.
// 다음으로 비정상적인 입력과 결과값이 발생하는 것에 대비하여 다음과 같은 코드를 작성했습니다.
// 함수의 처음에 row와 col이 0보다 작거나 같은 경우 즉 비정상적인 입력값이 입력되면 return 값이 -1이 되도록 했습니다.
// 그리고  각 행렬들이 NULL 값을 가지면 return값이 -1이 되도록 했습니다.
// 이상이 없는 경우 1을 return합니다.
