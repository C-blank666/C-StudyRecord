#include<iostream>
#include<assert.h>
using namespace std;
//类和对象基础演示 
class Stack {
public:
	void Init(int capacity=4) {
		_capacity = capacity;
		_array = (int*)malloc(sizeof(int) * _capacity);
		if (_array == nullptr) perror("malloc fail");
		_top = 0;
	}
	void Push(int data) {
		if (_capacity == _top) {
			int* tmp = (int*)realloc(_array, sizeof(int) * _capacity * 2);
			if (tmp == nullptr) perror("realloc fail");
			_array = tmp;
			_capacity *= 2;
		}
		_array[_top++] = data;
	}
	void Pop() {
		assert(_top);
		_top--;
	}
	int top() {
		assert(_top);
		return _array[_top - 1];
	}
	void destroy() {
		free(_array);
		_array = nullptr;
		_capacity = _top = 0;
	}
	void print() {
		for (size_t i = 0; i < _top; i++)
			cout << _array[i] << ' ';
		cout << endl;
	}
private:
	int* _array;
	int _capacity;
	int _top;
};
void TestMain01() {
	Stack s;
	//类的示例化
	/*
	* 1.类实例化后才会有空间的存储，实例化的类主要存储的是成员变量，同一类实例化共用一套成员函数（实例化后的成员函数与对象的内存无关
	*   这时的成员函数存储在代码段）
	* 2.类实例化后的大小计算和c语言中的结构体大小计算一样，都是通过成员变量的对其数来确定它们在内存上的位置
	*/
	s.Init();
	s.Push(1);
	s.Push(2);
	s.Push(3);
	s.Push(4);
	s.Push(5);
	s.Push(6);
	s.Push(7);
	s.Push(8);
	s.Push(9);
	s.Push(10);
	s.Pop();
	cout << s.top() << endl;
	s.print();
	s.destroy();
}
//测试成功
/*
* 关于类的几个关键点
* 1.类的关键词可以是class也可以是struct 
* 2.类中不仅可以定义变量，也可以定义函数。这里的变量叫做成员变量，函数叫做成员方法
* 3.类中的public,protect,private是类的访问修饰限定符public是允许类外访问的，private是私人的不允许类外访问
* 4.struct定义类时，成员默认是public的，而class定义类时，成员默认是private，但日常还是显式的加上访问修饰限定符要好
* 5.定义在类中的成员函数默认是inline函数.
*/

class Date {
public:
	void Init(int year, int month, int day) {
		_year = year;
		_month = month;
		_day = day;
	}
	void Print() {
		cout << _year << '/' << _month << '/' << _day << endl;
	}
private:
	int _year;
	int _month;
	int _day;
};
void TestMain02() {
	Date d1;
	Date d2;


	d1.Init(2025, 1, 1);
	d2.Init(2024, 2, 2);


	d1.Print();
	d2.Print();//两个实例化后的变量调用的明明是代码段的同一个函数，为什么两个print()打印的结果不一样
	//这里引出  *****this指针*****
	/*
	* 1.之所以打印结果不一样是因为类中成员函数形参的开头永远都隐含了一个形参 Date* const this 
	*	如 “void Init(Date* const this, int year, int month, int day)”  “void Print(Date* const this)”等
	* 2.其次实例化后的变量在传参时也隐形的传了变量的地址
	*   如  “d1.Print(&d1)” “ d2.Print(&d2)” “d1.Init(&d1,2025,1,1)”等。 
	* 3.this指针不能显式的出现在成员函数的形参位置，也不能显式的对类实例化后的变量传地址，
	*	但可以在成员函数内部使用this指针进行解引用等操作（一般不显式的写出）
	*/
}


int main() {
	//TestMain01();
	TestMain02();
	return 0;
}