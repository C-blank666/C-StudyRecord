#include"Heap.h"
void HPInit(HP* php) {
	assert(php);
	php->arr = NULL;
	php->capacity = php->size = 0;
}
void HPDestroy(HP* php) {
	assert(php);
	if (php->arr) {
		free(php->arr);
		php->arr = NULL;
	}
	php->capacity = php->size = 0;
}
void Swap(HPDataType* x, HPDataType* y) {
	HPDataType tmp = *x;
	*x = *y;
	*y = tmp;
}
void AdJustUp(int child, HPDataType* arr) {
	int parent = (child - 1) / 2;
	while (child > 0) {
		if (arr[child] < arr[parent]) {
			Swap(&arr[child], &arr[parent]);
			child = parent;
			parent = (child - 1) / 2;
		}
		else {
			break;
		}
	}
}
void HPPush(HP* php, HPDataType x) {
	assert(php);
	if (php->capacity == php->size) {
		int newCapacity = php->capacity == 0 ? 4 : php->capacity * 2;
		HPDataType* tmp = (HPDataType*)realloc(php->arr, sizeof(HPDataType) * newCapacity);
		if (tmp == NULL) {
			perror("realloc fail");
			exit(1);
		}
		php->arr = tmp;
		php->capacity = newCapacity;
	}
	php->arr[php->size] = x;
	AdJustUp(php->size,php->arr);
	++php->size;
}