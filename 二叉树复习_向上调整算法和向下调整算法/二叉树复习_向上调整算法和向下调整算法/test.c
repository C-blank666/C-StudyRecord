#include"Heap.h"
void test01() {
	HP hp;
	HPInit(&hp);
	HPPush(&hp, 12);
	HPPush(&hp, 20);
	HPPush(&hp, 4);
	HPPush(&hp, 3);
	HPPush(&hp, 33);
	HPPush(&hp, 2);
	HPPush(&hp, 1);
	HPDestroy(&hp);
}
void test02() {
	HP hp;
	HPInit(&hp);
	HPDataType arr[] = { 12,23,33,13,34,199,34,1,3 };
	for (size_t i = 0; i < sizeof(arr); i++)
	{
		HPPush(&hp, arr[i]);
	}
}
int main() {
	//test01();
	test02();
	return 0;
}