#include<iostream>
using namespace std;
//初始化列表
/*
* 1.初始化列表是为类对象初始化所设计的，当类的成员变量含有自定义类型时，初始化时会调用该自定义类型的默认构造，但如果
*	该类的构造不是默认构造时（函数显式的写出并需要传参）,编译器无法调用，就会报错。这时就需要初始化列表了，初始化列表可以给其传参
* 2.初始化列表出了应用第一种自定义类型没有默认构造函数的情况，还有引用成员变量和const成员量
* 3.初始化列表的初始化顺序也有讲究，它的顺序不是初始化的顺序，初始化列表中的变量初始化的顺序是类中成员变量声明的顺序
* 4.通过初始化列表引出声明缺省值的概念，即类中成员变量声明时可以赋予一个值，如果初始化列表中没有进行初始化，那么就会传缺省值，
*	但初始化列表的优先权大于声明缺省值
* 5.无论是否显式的写初始化列表，变量都会先走初始化列表，无论初始化列表中是否显式初始化变量，变量也都会先走初始化列表
*/
class Stack {
public:
	Stack(int capacity) {
		_a = (int*)malloc(sizeof(int) * _capacity);
		if (_a == nullptr) perror("malloc fail");
		_capacity = capacity;
		_top = 0;
	}
	//.....
	~Stack() {
		free(_a);
		_a = nullptr;
		_capacity = _top = 0;
	}
private:
	int* _a;
	int _capacity;
	int _top;
};
class MyQueue {
public:
	MyQueue()
		:PushST(4)
		,PopST(5)//这里的MyQueue中的Stack类成员变量没有默认构造函数，但是通过初始化列表就可以继续传参，完成初始化
	{}
private:
	Stack PushST;
	Stack PopST;
};
class TestClass01 {
public:
	TestClass01(int& b)
		:a(1)//普通的内置类型也可以写在初始化列表中
		,st(4)//自定义类型
		,rb(b)//引用变量传参
		,n(1)//const变量传参
	{}
private:
	int a;//普通内置变量
	Stack st;//自定义变量
	int& rb;//引用变量
	const int n;//const变量
};
class TestClass02 {
public:
	TestClass02()
	{}

private:
	Stack st = 4;
};

void test01() {
	MyQueue mq;
	int b = 4;
	TestClass02 TC2;//没有报错，因为有声明缺省值
}


//类型转换
/*
* 1.C++也支持内置类型类型转换为自定义类型行，但需要构造函数有该内置类型的参数
* 2.如果不想自定义类出现类型传唤的功能，就在构造函数名前加上explicit
* 3.不同的自定义类型对象之间也可以进行类型转换，但也需要其构造函数有另一个自定义类型对象的参数
*/
class TestClass03 {
public:
	TestClass03(int a)
		:_a(a)
	{}
	TestClass03(int a, int b)
		:_a(a)
		,_b(b)
	{}
	TestClass03(const Stack& st) {

	}
private:
	int _a;
	int _b;
};
void test02() {
	TestClass03 TC = 1;//这里进行了类型转换，因为TC对象的类中构造函数含有整形类型的参数
	TestClass03 TC1 = { 1,2 };//有两个整形参数就可以用两个整形来进行类型转换
	const TestClass03& TC2 = 1;//当引用出现时要加上const修饰，因为整形1要先构造一个临时TestClass03的对象再复制拷贝给TC2,临时对象具有常性
	//这种连续构造+拷贝构造编译器会优化为直接构造
	Stack st1(3);
	TestClass03 TC3 = st1;//自定义类型之间的类型转换
}

//静态成员变量和静态成员函数
/*
* 1.静态成员变量比较特殊，因为它的位置是在静态区，静态区属于公共区域，所以当含有静态成员变量的类实例化为对象后
*	静态成员并不只属于这个对象，而是实例化的所有对象都能对其进行操作
* 2.基于特点1的特性，静态成员变量是不能被构造函数初始化的，而是遵循类内声明，类外定义
* 3.静态成员变量仍然受到成员访问限定符的约束，但静态成员变量的特性就决定了它不能像普通变量一样在限定符之下使用,所以可以提供一个
*	get函数来专门在类外访问私有的静态成员变量
* 4.静态成员函数，当get的返回值是static修饰时，就称为静态成员函数，此时的静态成员变量可以直接通过类名访问
* 5.一旦成员函数被static修饰，那么该函数将没有this指针参数
* 6.根据特点5，静态成员函数无法访问私有正常成员变量，但可以访问其他静态成员变量
* 7.非静态成员函数可以访问静态变量
*/
class TestClass04 {
public:
	TestClass04() {
		a++;
	}
	static int GetRet() {
		//b = 2;编译报错  
		return a;
	}

private:
	static int a;
	int b;
};
int TestClass04::a = 1;
void test03() {
	TestClass04 TC;
	cout << TC.GetRet() << endl;
	cout << TestClass04::GetRet() << endl;
}



int main() {
	test01();
	test02();
	test03();
	return 0;
}