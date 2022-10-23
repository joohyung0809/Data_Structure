#include <stdio.h>
#include <math.h>

typedef struct algo{  // 사건과 해당 사건의 연도를 저장하기 위해 구조체 선언
    int year;
    char event[30];
}data;

typedef struct{    // 사건들의 집합을 저장하고 그 크기를 담기 위한 구조체 선언
    data heap[30];     
    int size;
}heap;

void change(data *a, data *b)  // 구조체들을 바꾸는 함수
{
   data temp = *a;
   *a = *b;
   *b = temp;
}

void Max_heapify(heap *array, int i){ // Max_heapify함수(max-heap 상태를 유지)
    int l = 2*(i+1) - 1; // i위치에서 왼쪽 자식 노드
    int r = 2*(i+1); // i위치에서 오른쪽 자식 노드
    int largest;
    if (l < array->size && array->heap[l].year > array->heap[i].year) {
        largest = l; 
    } // heap의 크기보다 l이 작고, i위치의 year값 보다 l위치의 year값이 크면 l이 가장 큰 값
    else {
        largest = i;
    } // 아니라면 i가 가장 큰 값
    if (r < array->size && array->heap[r].year > array->heap[largest].year) {
        largest = r;
    } 
// heap의 크기보다 r이 작고, 위에서 정해진 largest위치의 year값 보다 r위치의 year값이 크면 r이 가장 큰 값
    if (largest != i) {
        change(&array->heap[i], &array->heap[largest]);
        Max_heapify(array, largest);
    } // 위 조건문을 끝내고 largst가 i가 아니라면 즉, 위치 조정이 필요해졌다면 change함수를 통해 위치 바꿈.
      // 그리고 Max_heapify 함수를 재귀적으로 사용한다. (힙 전체를 max-heap으로 만들기 위해)
}


void Build_max_heap(heap *array) { // max-heap 빌딩하기
    for(int i = floor(array->size / 2); i >= 0; i--) { 
        Max_heapify(array, i); // 자식 노드를 가지고 있는 가장 마지막 인덱스부터 Max_heapify
    }
}

void Heapsort(heap *array){ //Heapsort하는 함수
    int a = array->size;
    for(int j = array->size - 1; j > 0; j--){
        change(&array->heap[0], &array->heap[j]);
        array->size--;
        Max_heapify(array, 0);
    } //Max_heapify를 해서 제일 첫번째 노드가 가장 큰 값이 오게 한다. 
    array->size = a;
}

data Maximum(heap *array) { // 힙에서 최대값 리턴
    return array->heap[0]; // max-heap 상태에서 제일 첫 번째 힙의 값을 리턴하면 최대값이 나옴.
}

data Heap_Extract_Max(heap *array) { // 힙에서 최대값을 뽑아냄 (queue의 pop기능)
    if(array->size < 1){
        printf("heap underflow."); // 크기가 1미만이면 오류 메시지 출력
    }
    data max = array->heap[0]; // 가장 큰 값인 heap구조를 담기 위해 첫번째 힙을 max에 담는다.
    array->heap[0] = array->heap[array->size - 1]; //가장 마지막 노드를 0번째로 올린다.
    array->size--; //최대값을 빼니까 size 줄어든다.
    Max_heapify(array, 0); // 가장 마지막 노드를 0번째로 올렸으니 다시 max-heap에 맞는 구조로 바꾼다.
    return max;
}

void Increase_Key(heap *array, int i, data node){ // 키값을 증가시키는 함수
    if(array->heap[i].year > node.year){
        printf("new key is smaller than current key"); // 새로운 키값이 현재 키보다 작은 경우 오류 메시지
    }
    array->heap[i] = node; //i번째 위치에 새로 입력받은 노드를 넣을 것임
    int parent = floor((i-1)/2); // i번째 노드의 부모느드를 알아내기 위해 floor함수 사용        
    while(i > 0 && array->heap[parent].year < array->heap[i].year) {  
        //새로 입력된 노드가 부모보다 큰 값을 가지면 바꾸어주어야 함      
        change(&array->heap[i], &array->heap[parent]);
        // while문에 들어왔으면 아래 값들이 갱신 되어야 함.
        i = parent; //바뀌어 지는 경우 i가 parent가 됨
        parent = floor((i-1)/2); // parent값도 갱신해야 함
    }
}

void Insert(heap *array, data node) { // 힙에 노드를 삽입하는 함수 
    array->size++;// 삽입하면 size하나 증가
    array->heap[array->size-1].year = -9999; 
    // 넣을 노드의 값을 매우 작은 값을 할당 해두어야 밑에서 Increase_Key사용할 수 있음
    Increase_Key(array, array->size-1, node); // 파라미터로 받은 node를 가장 끝 노드(size-1)에 넣는다.
}


int main() {
   FILE *file;
    heap heap;
    data node;

   file = fopen("input.txt","r");
   fscanf(file,"%d", &heap.size);
    for(int i=0;i<heap.size;i++) {
        fscanf(file,"%d", &heap.heap[i].year);
        fscanf(file,"%s", heap.heap[i].event);
    }
    Build_max_heap(&heap);


    Heapsort(&heap);
    printf("\n heap sort \n");
    for(int k=0;k < heap.size;k++) {
        printf("%d %s\n",heap.heap[k].year, heap.heap[k].event);
    }


    printf("\n삽입할 연도 :");
    scanf("%d", &node.year);
    printf("\n삽입할 사건 :");
    scanf("%s", node.event);
    Insert(&heap, node);
    printf("\n Insert 결과 Print\n");
    for(int k=0;k < heap.size;k++) {
        printf("%d %s\n",heap.heap[k].year, heap.heap[k].event);
    }


    printf("\n Maximum(최대값) Print \n");
    data temp = Maximum(&heap);
    printf("%d %s \n", temp.year, temp.event);
    

    printf("\nIncrease에 사용할 연도 :");
    scanf("%d", &node.year);
    printf("\nIncrease에 사용할 사건 :");
    scanf("%s", node.event);
    printf("\n Increase key 결과 Print \n");
    Increase_Key(&heap,2, node);
    for(int k=0;k < heap.size;k++) {
        printf("%d %s\n",heap.heap[k].year, heap.heap[k].event);
    }


    printf("\n Heap_Extract_Max 결과 Print \n");
    data temp2 = Heap_Extract_Max(&heap);
    printf("\n 뽑아낸 노드 \n");
    printf("%d %s \n\n", temp2.year, temp2.event);
    for(int k=0;k < heap.size;k++) {
        printf("%d %s\n",heap.heap[k].year, heap.heap[k].event);
    }
    

    fclose(file);
}