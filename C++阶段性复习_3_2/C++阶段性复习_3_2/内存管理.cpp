#include<iostream>
using namespace std;
//new/delete 操作
void test01() {
	int* a = new int(1);//向内存申请一个整形大小的空间并赋值为1
	char* c = new char('a');
	cout << *a << endl;
	cout << *c << endl;
	int* n = new int[5]{ 1,2,3 };//向存申请一个大小为5个整形字节的数组空间，并分别赋值前三个元素为1，2，3后续2个编译器自动赋值为0

	for (size_t i = 0; i < 5; i++)
	{
		cout << n[i];
	}

//new向内存申请的空间也在堆区，所以同样需要销毁
	delete a, c;
	delete[] n;
	//销毁整形a，c和数组n
}
//new和delete与malloc和free真正区别在与它们为自定义类型申请空间时new会调用该类型的构造函数，而delete会调用该类型的析构函数
class A {
public:
	A(int a)
		:_a(a)
	{
		cout << "A(int)" << endl;
	}
	~A() {
		cout << "~A()" << endl;
	}
private:
	int _a;
};
class B {
public:
	B()
	{
		cout << "B()" << endl;
	}
	~B() {
		cout << "~B()" << endl;
	}
private:
};	

void test02() {
	A* aa = new A(2);//向内存申请空间的同时调用构造函数并传参，当没有默认构造函数可调用时就会报错
	B* bb = new B;
	A* aaArr = new A[3]{ 1,2,3 };//向内存申请空间储存A自定义类型数组，并分别初始化
	delete aa;
	delete bb;
	delete[] aaArr;//自定义类型数组delete时数组中有几个自定义类型对象就析构几个这里打印三个~A()

}

//模板
//模板的存在可以减轻程序员代码量
void Swap(int& a, int& b) {
	int tmp = a;
	a = b;
	b = tmp;
}//只能接收整形的交换，如果是浮点数，需要重新再写一遍函数

void Swap( double& a, double& b) {
	double tmp = a;
	a = b;
	b = tmp;
}//这样很麻烦

//用模板
template<class T>
void SwapT(T& a, T& b) {
	T tmp = a;
	a = b;
	b = tmp;
}

void test03() {
	int x = 1, y = 2;
	double m = 1.1, n = 2.2;
	SwapT(x, y);
	SwapT(m, n);//无论是整形还是浮点数都可以传
	cout << "x:" << x << " " << "y:" << y << endl;
	cout << "m:" << m << " " << "n:" << n << endl;
}
template<class T1,class T2>
void SwapT(T1& a,T2& b) {
	T1 tmp = a;
	a = (T1)b;
	b = (T2)tmp;
}//当有多个参数时，可以用多个模板参数
void test04() {
	int x = 1;
	double y = 2.2;
	SwapT(x, y);
	cout << "x:" << x << " " << "y:" << y << endl;
}
//模板函数在自动识别参数后也会将模板函数分为多个不同的参数类型的函数，但不是所有类型，只根据你所传的类型来执行这个操作
//然后来执行相应的函数，这个过程叫做模板函数的实例化
//模板函数实例化有两种方法：1.隐式实例化 2.显式实例化
template<class T>
int Add(const T& x, const T& y) {
	return x + y;
}
template<class T1,class T2>
int Add(const T1& x, const T2& y) {
	return x + y;
}
void test05() {
	int x = 1;
	double y = 2.2;
	//隐式实例化
	Add(x, (int)y);//隐式实例化，告诉编译器调用两个参数都是int的SwapT函数
	Add((double)x, y);//隐式实例化，告诉编译器调用两个参数都是double的SwapT函数
	//显式实例化
	Add<int>(x, y);//显式实例化，告诉编译器调用两个参数都是int的SwapT函数
	Add<double>(x, y); //显式实例化，告诉编译器调用两个参数都是double的SwapT函数
}
//类模板
//以栈为例
template<class T>
class Stack {
public:
	Stack(int capacity = 4)
		:_capacity(capacity)
		, _top(0)
	{
		_a = new T[capacity];
	}
	~Stack() {
		delete[] _a;
		_top = _capacity = 0;
	}
private:
	T* _a;
	int _capacity;
	int _top;
};

//类模板只能显式实例化
void test05() {
	Stack<int> st;
}
//虽然之前的typedef似乎与模板有一样的作用,但当Satck要创建多个不同类型T的时候模板的作用就发挥了，而用typedef就要重写Stack

//模板参数的匹配原则是有现成的就用，总之就是寻找最接近的模板参数或原函数

int main() {
	//test01();
	//test02();
	//test03();
	//test04();
	return 0;
}


