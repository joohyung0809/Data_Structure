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
    printf("[----- [������]  [2019023028] -----]\n");

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

// �� ���� �Լ��� �����ϰ� ���� �Լ��� ���� ����⸦ �ο��Ͽ� ����� �� �ְ� �ϴ� �Լ��Դϴ�.

/* create a 2d array whose size is row x col using malloc() */
int** create_matrix(int row, int col)
{
    /* check pre conditions */
    if (row <= 0 || col <= 0) {
        printf("Check the sizes of row and col!\n");
        return NULL;
    }

    int** matrix = (int**)malloc(sizeof(int*) * row);
    for (int i = 0; i < row; i++)            // ���� ũ�⸸ŭ �ݺ�
    {
        matrix[i] = (int*)malloc(sizeof(int) * col);    // (int�� ũ�� * col)��ŭ ���� �޸� �Ҵ�. �迭�� ����
    }

    /* check post conditions */
    if (matrix == NULL) {
        printf("Memory Allocation Failed/\n");
        return NULL;
    }

    return matrix;
}

// int** create_matrix(int row, int col) �Լ��� row�� colũ�⿡ �ش��ϴ� ����� ���� �޸� �Ҵ����� �����ϴ� �Լ��Դϴ�.
// ���� �޸� �Ҵ��� ���� malloc�Լ��� ����Ͽ����ϴ�.
// �Լ��� �ڼ��� ���캸�� ���� row�� �ش��ϴ� ��ŭ malloc�Լ��� ȣ���Ͽ� ���� �޸� �Ҵ��� �߽��ϴ�.
// �������� for���� ��ġ�鼭 row 1���� col��ŭ malloc�Լ��� ȣ���Ͽ� ���� �޸� �Ҵ��� �߽��ϴ�.
// �׷��� �ϸ� main�Լ����� ���� row, col�� ���� �ش��ϴ� ����� ������ �Ҵ� �˴ϴ�.
// �������� ���������� �Է°� ������� �߻��ϴ� �Ϳ� ����Ͽ� ������ ���� �ڵ带 �ۼ��߽��ϴ�.
// �Լ��� ó���� row�� col�� 0���� �۰ų� ���� ��� �� ���������� �Է°��� �ԷµǸ� NULL�� return�ϰ� �߽��ϴ�.
// �׸��� ����� ������ �ڿ� NULL ���� ������ NULL�� return�ϰ� �߽��ϴ�.
// �̻��� ���� ��� matrix�� return�մϴ�.

/* print matrix whose size is row x col */
void print_matrix(int** matrix, int row, int col)
{
    /* check pre conditions */
    if (row <= 0 || col <= 0) {
        printf("Check the sizes of row and col!\n");
        return;
    }

    for (int i = 0; i < row; i++)    // ���� ũ�⸸ŭ �ݺ�
    {
        for (int j = 0; j < col; j++)    // ���� ũ�⸸ŭ �ݺ�
        {
            printf("%3d ", matrix[i][j]);      // 2���� �迭�� �ε����� �ݺ����� ���� i, j�� ����
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

// void print_matrix(int** matrix, int row, int col) �Լ��� �ռ� �����ߴ� ����� ������ ����ϴ� �Լ��Դϴ�.
// ���⼭�� �ܼ��� ���� for���� ���� ��ü ����� ���� ǥ���߽��ϴ�.
// �Լ��� �ڼ��� ���캸�� matrix[i][j]�� ���� 2���� �迭�� 2�� for���� ���� ��ü ���� �� ������ �� �ְ� ��������ϴ�.
// �������� ���������� �Է°� ������� �߻��ϴ� �Ϳ� ����Ͽ� ������ ���� �ڵ带 �ۼ��߽��ϴ�.
// �Լ��� ó���� row�� col�� 0���� �۰ų� ���� ��� �� ���������� �Է°��� �ԷµǸ� return ���� ������ �߽��ϴ�.
// �׸��� ����� ��� �غ� ��ģ �ڿ� NULL ���� ������ return���� ������ �߽��ϴ�.



/* free memory allocated by create_matrix() */
int free_matrix(int** matrix, int row, int col)
{
    /* Check pre conditions */
    if (row <= 0 || col <= 0) {
        printf("Check the size of row and col!\n");
        return -1;
    }

    for (int i = 0; i < row; i++)    // ���� ũ�⸸ŭ �ݺ�
    {
        free(matrix[i]);                  // 2���� �迭�� ���� ���� �޸� ����
    }

    free(matrix);    // 2���� �迭�� ���� ���� �޸� ����
    return 1;
}

//int free_matrix(int** matrix, int row, int col)�Լ��� �ռ� malloc���� �����Ҵ��� �޸𸮸� �����ϴ� �Լ��Դϴ�.
// �� ������� ��Ŀ� ���� �־��� ����̳�, ����� ������ ���� ���Ӱ� ������ ����� �޸𸮸� free�Լ��� ���� �����մϴ�.
// �Լ��� �ڼ��� ���캸�� for������ matrix[i]�� ���� �޸𸮸� �����մϴ�.
// �̶� ���� for������ �����ؾ��Ѵٰ� ������ �� �ִµ� 2���� �迭�� ��� ���� ������ �޸𸮸� �����ص� ��� �����˴ϴ�.
// �������� ���������� �Է°� ������� �߻��ϴ� �Ϳ� ����Ͽ� ������ ���� �ڵ带 �ۼ��߽��ϴ�.
// �Լ��� ó���� row�� col�� 0���� �۰ų� ���� ��� �� ���������� �Է°��� �ԷµǸ� return ���� -1�� �ǵ��� �߽��ϴ�.
// �׸��� free�� ���� �޸𸮰� �����Ǹ� ��ó�� �˻��� ����� ���⿡ �˻� ���� return ���� 1�� �ǵ��� �߽��ϴ�.


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

// int fill_data(int** matrix, int row, int col) �Լ��� create_matrix�Լ��� ������� ��Ŀ�
// 0~19������ ���� �������� �ο��ϴ� �Լ��Դϴ�. 
// �� rand()�Լ��� 2�� for���� �־� ����� ��� ���� �����Ͽ� ���� �Ҵ��ϵ��� �߽��ϴ�.
// �Լ��� �ڼ��� ���캸�� matrix[i][j]�� 2�� for���� �־� ����� ��� ���� �����մϴ�. 
// �׸��� rand() % 20; ���� ��Ŀ� ���� �Ҵ��մϴ�.
// ���⼭ % 20�̶�� ���� 0~19�� ���� �ǹ��մϴ�. �� %�ڿ� ���� ���ڿ��� -1�� ����ŭ�� ���� �Ҵ�˴ϴ�.
// �������� ���������� �Է°� ������� �߻��ϴ� �Ϳ� ����Ͽ� ������ ���� �ڵ带 �ۼ��߽��ϴ�.
// �Լ��� ó���� row�� col�� 0���� �۰ų� ���� ��� �� ���������� �Է°��� �ԷµǸ� return ���� -1�� �ǵ��� �߽��ϴ�.
// �׸��� ����� ���� �Ҵ�� �ڿ� NULL ���� ������ return���� -1�� �ǵ��� �߽��ϴ�.
// �̻��� ���� ��� 1�� return�մϴ�.


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

// int addition_matrix(int** matrix_a, int** matrix_b, int row, int col)�Լ��� ����� ������ �����ϴ� �Լ��Դϴ�.
// ����� ������ �����ϱ� ���� 2�� for���� �̿��Ͽ� ��� ����� ���� �����Ͽ� �� ������ ���߽��ϴ�.
// �Լ��� �ڼ��� ���캸�� int** matrix_sum = create_matrix(row, col);�� ����Ͽ� ���� ������ ������ ����� �����մϴ�.
// matrix_a[i][j] + matrix_b[i][j]�� 2�� for���� �־� ��� a�� b�� �� ���� ���Ͽ�  matrix_sum[i][j]�� �ֽ��ϴ�.
// �������� ���������� �Է°� ������� �߻��ϴ� �Ϳ� ����Ͽ� ������ ���� �ڵ带 �ۼ��߽��ϴ�.
// �Լ��� ó���� row�� col�� 0���� �۰ų� ���� ��� �� ���������� �Է°��� �ԷµǸ� return ���� -1�� �ǵ��� �߽��ϴ�.
// �׸���  �� ��ĵ��� NULL ���� ������ return���� -1�� �ǵ��� �߽��ϴ�.
// �̻��� ���� ��� 1�� return�մϴ�.

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

// int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col)�Լ��� ����� ���� ������ �����ϴ� �Լ��Դϴ�.
// ����� ������ �����ϱ� ���� 2�� for���� �̿��Ͽ� ��� ����� ���� �����Ͽ� �� ������ �����ϴ�.
// �Լ��� �ڼ��� ���캸�� int** matrix_sub = create_matrix(row, col);�� ����Ͽ� ���� ������ ������ ����� �����մϴ�.
// matrix_a[i][j] - matrix_b[i][j]�� 2�� for���� �־� ��� a�� b�� �� ���� ����  matrix_sub[i][j]�� �ֽ��ϴ�.
// �������� ���������� �Է°� ������� �߻��ϴ� �Ϳ� ����Ͽ� ������ ���� �ڵ带 �ۼ��߽��ϴ�.
// �Լ��� ó���� row�� col�� 0���� �۰ų� ���� ��� �� ���������� �Է°��� �ԷµǸ� return ���� -1�� �ǵ��� �߽��ϴ�.
// �׸���  �� ��ĵ��� NULL ���� ������ return���� -1�� �ǵ��� �߽��ϴ�.
// �̻��� ���� ��� 1�� return�մϴ�.

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

// int transpose_matrix(int** matrix, int** matrix_t, int row, int col) �Լ��� ����� ��ġ ������ �����ϴ� �Լ��Դϴ�.
// ����� ��ġ �����ϱ� ���� 2�� for���� �̿��Ͽ� ��� ����� ���� �����Ͽ� �� ������ ��ġ�߽��ϴ�.
// �Լ��� �ڼ��� ���캸�� 2�� for���� matrix_t[i][j] = matrix[j][i];�� �־� matrix ����� ��ġ�� ���� matrix_t�� �־����ϴ�.
// �������� ���������� �Է°� ������� �߻��ϴ� �Ϳ� ����Ͽ� ������ ���� �ڵ带 �ۼ��߽��ϴ�.
// �Լ��� ó���� row�� col�� 0���� �۰ų� ���� ��� �� ���������� �Է°��� �ԷµǸ� return ���� -1�� �ǵ��� �߽��ϴ�.
// �׸���  �� ��ĵ��� NULL ���� ������ return���� -1�� �ǵ��� �߽��ϴ�.
// �̻��� ���� ��� 1�� return�մϴ�.

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

// int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col)�Լ��� ����� �� ������ �����ϴ� �Լ��Դϴ�.
// ����� ���� �����ϱ� ���� 2�� for���� ����Ͽ� matrix_a�� i��, matrix_t�� j���� ���� ��� �����Ͽ� ���߽��ϴ�.
// ����� ����  A�� i���� �� ���а� B�� j���� �����Ǵ� ������ ���� ��� ���� �Ͱ� �����ϴ�.
// �Լ��� �ڼ��� ���캸�� int** matrix_axt = create_matrix(row, col);�� ����Ͽ� ���� ������ ������ ����� �����մϴ�.
//  matrix_a[i][k] * matrix_t[k][j];�� 2�� for���� �־� ���� ���ϰ�, temp�� ����ؼ� �� ���� ���� ����Ͽ� ����� ���� �����߽��ϴ�.
// i�� ������  for���� 1�� ����� �� matrix_axt[i][j] = temp;�� �̿��Ͽ� ����� ���� ������ ����� ��Ŀ� temp���� �ֽ��ϴ�.
// �������� ���������� �Է°� ������� �߻��ϴ� �Ϳ� ����Ͽ� ������ ���� �ڵ带 �ۼ��߽��ϴ�.
// �Լ��� ó���� row�� col�� 0���� �۰ų� ���� ��� �� ���������� �Է°��� �ԷµǸ� return ���� -1�� �ǵ��� �߽��ϴ�.
// �׸���  �� ��ĵ��� NULL ���� ������ return���� -1�� �ǵ��� �߽��ϴ�.
// �̻��� ���� ��� 1�� return�մϴ�.
