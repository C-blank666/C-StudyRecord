#include<iostream>
#include<typeinfo>
using namespace std;
//模板进阶
//1.非类型模板参数
template<class T, size_t N = 10 >
class A {
public:
	A() {
		cout << "T类型：" << typeid(T).name() << endl;
		cout << "N:" << sizeof(_a) / 4 << endl;
	}

private:
	T _a[N];
};
void test01() {
	A<int> a;
	A<char, 100> b;
	//可以看出，非类型模板参数可以给缺省值，且只支持整形
	//与宏对比，C++的非类型模板参数可以使同一个类创建多个非类型模版参数不同的对象，充分体现了模板的特性
}
//2.特化
//	特化分为全特化和偏特化
//  特化模板可以应用在函数上，也可以应用在类上
template<class T>
bool Less(T left, T right) {
	return left < right;
}//普通模板函数
template<>
bool Less<int*>(int* left, int* right) {
	cout << "特化" << endl;
	return *left < *right;
}//特化函数模板
//即遇见类型为int*的特殊类型就调用该特化版本（这里int*的特殊性是我们自己假定的）
void test02() {
	cout << Less(1, 2) << endl;
	int x = 2;
	int y = 1;
	cout << Less(&x, &y) << endl;//同样是两个相同参数的传参，但会调用特化
}
//但正常情况下模板函数一般不使用特化，因为如果真的需要特化，直接重载一个相同的函数就可以了
//如下
//bool Less(int* left, int* right) {
//	return *left < *right;
//}

//类模板特化
//全特化

//正常类模板：
template<class T1, class T2>
class B {
public:
	B() {
		cout << "T1 T2" << endl;
	}
private:
	T1 _a;
	T2 _b;
};
//全特化
template<>
class B<int, char> {
public:
	B() {
		cout << "int char" << endl;
	}
private:
	int _a;
	char _b;
};
//偏特化，偏特化可以特殊化类模板也可以起到限制作用
template<class T>
class B<T, char> {//含有char就调用该模板，如果有更合适的模板除外
public:
	B() {
		cout << "T char" << endl;
	}
private:
	int _a;
	char _b;
};
//具有限制效果的偏特化
template<class T1,class T2>
class B<T1&,T2*>{//T1和T2的类型就是去掉所传入参数的&和*之后的类型，若传入int&和int*那么两类型就是int int
public:
	B() {
		cout << "T1和T2的类型分别是" << typeid(T1).name() << " " << typeid(T2).name() << endl;
		cout << "T1& T2*" << endl;
	}
private:
	T1 _a;
	T2 _b;
};
void test03() {
	B<char,int> b1;
	B<int, char> b2;//调用全特化，不调用偏特化是因为全特化模板的两个参数类型更符合
	B<char, char> b3;//调用偏特化
	B<int&, int*> b4;//具有限制性的偏特化，只能传引用和指针类型
}

int main() {
	//test01();
	//test02();
	test03();
	return 0;
}