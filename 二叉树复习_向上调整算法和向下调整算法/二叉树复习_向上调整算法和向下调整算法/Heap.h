#pragma once
#include<stdio.h>
#include<assert.h>
#include<stdlib.h>
#include<stdbool.h>

typedef int HPDataType;

typedef struct Heap {
	HPDataType* arr;
	int size;
	int capacity;
}HP;

void HPInit(HP* php);
void HPDestroy(HP* php);
void HPPush(HP* php,HPDataType x);
void HPPop(HP* php);
void AdJustUp(int child,HPDataType* arr);
void AdJustDown(int parent,HPDataType* arr);
HPDataType HPTop();
bool HPEmpty();


