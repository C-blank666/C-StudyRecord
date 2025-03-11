#include<iostream>
#include<assert.h>
using namespace std;
//类的6个默认成员函数（前五个）

//*********构造函数**********
class Date {
public:
	Date() {
		_year = 1;
		_month = 1;
		_day = 1;
	}
	/*
	Date(int year = 2, int month = 2, int day = 2){
		_year = year;
		_month = month;
		_day = day;
	*/
	Date(int year, int month, int day) {
		_year = year;
		_month = month;
		_day = day;
	}
	//特点1.构造函数的名称应与结构体的名称相同，构造函数没有返回值，不用写返回值（C++规定，没有为什么）
	//特点2.在不写构造函数时，编译器会自动生成一个默认构造函数，但是至于有没有对内置类型进行初始化取决于编译器
	//特点3.构造函数可以进行重载，但要注意重载的要求，全缺省构造函数和无参构造函数不能同时存在，因为实例化时会出现歧义

	void print() {
		cout << _year << '/' << _month << '/' << _day << endl;
	}
private:
	int _year;
	int _month;
	int _day;
};


void TestMain01() {
	Date d1;
	//Date d1();这种写法是错误的，没有传参或是全缺省构造时，都直接不加括号，这也是特点3里为什么会出现歧义的原因
	Date d2(6, 6, 6);
	//特点4.构造函数的使用体现在类在实例化的同时对构造函数传参
	//特点5.我们要知道构造函数有三个默认构造函数，它们不能同时存在，因为实例化的代码写法一样，
	//		如下：a.我们不写时编译器默认生成的构造函数 b.无参构造函数 c.全缺省构造函数 称为默认构造，默认构造的特点就是实例化时可以不传参
	//特点6.类里面的成员变量分为  内置类型  和  自定义类型  ，内置类型是系统提供的类型（int，char，double等）自定义类型是我们自己
	//		创建的类（class，struct），内置类型编译器可以调用类中的构造，而自定义类型则调用自定义类形类里面的默认构造（系统不会自动
	//		给自定义类型传参，所以调用默认构造），如果没有默认构造（特点5中的三个默认构造函数类型）可调用，则会报错
	d1.print();
	d2.print();
}

//************析构函数*************
class Stack {
	public:
		Stack(int capacity = 4) {
			_array = (int*)malloc(sizeof(int) * capacity);
			if (_array == nullptr) perror("malloc fail");
			_capacity = capacity;
			_top = 0;
		}


		void Push(int data) {
			if (_capacity == _top) {
				int newcapacity = _capacity == 0 ? 4 : _capacity * 2;
				int* tmp = (int*)realloc(_array,sizeof(int) * newcapacity);
				if (tmp == nullptr) perror("realloc fail");
				_array = tmp;
				_capacity = newcapacity;
			}
			_array[_top++] = data;
		}

		void Pop() {
			assert(_top);
			_top--;
		}

		void print() {
			for (size_t i = 0; i < _top; i++) cout << _array[i] << ' ';
			cout << endl;
		}

		~Stack() {
			cout << "~Stack" << endl;
			free(_array);
			_array = nullptr;
			_capacity = _top = 0;
		}
		//析构函数的特点
		//1.析构函数的名称和类名称一样，但需要在名称前加上‘ ~ ’符号，且析构函数也没有返回值
		//2.析构函数如果不显式的写，系统会自动生成
		

	private:
		int* _array;
		int _capacity;
		int _top;

};
class MyQueue {
public:
	~MyQueue() {
		cout << "~MyQueue" << endl;
	}
private:
	Stack StPush;
	Stack StPop;
};

void TestMain02() {
	Stack st(3);
	st.Push(1);
	st.Push(2);
	st.Push(3);
	st.Push(4);
	st.Push(4);
	st.print();
}
void TestMain03() {
	Stack st;
	MyQueue mq;
	/*
	打印：
	~MyQueue
	~Stack
	~Stack
	~Stack
	*/
	//特点3.类里面的内置类型调用该类的析构函数，而自定义类型调用它们自己的析构函数
	//特点4.类里面无论是否显式的写了析构函数，自定义类型都会调用它自己的析构函数
	//特点5.析构的顺序是后创建的对象先析构
	//特点6.我们申请资源时，可以不写析构函数，使用系统默认的析构函数即可
}


//***********拷贝构造************
class Date01 {
public:
	Date01(int year = 2025, int month = 2, int day = 27) {
		_year = year;
		_month = month;
		_day = day;
	}
	Date01(const Date01& d) {
		_year = d._year;
		_month = d._month;
		_day = d._day;
	}
	//拷贝构造函数
	//特点1.拷贝构造是一种特殊的构造函数，可以说它是构造函数的重载，它也和构造函数一样如果没有显式的写出，那么编译器也会默认生成拷贝构造
	//特点2.拷贝构造的第一个参数必须是其类类型对象的引用，之所以用类类型对象的引用是因为C++规定自定义类型对象在
	//		进行拷贝行为时只能调用该类的拷贝构造函数，如传值传参，传返回值等操作，那么如果参数不是引用而是单纯的
	//		只进行传值  Date01(const Date01 d) 那么这时就会再次调用该类的拷贝构造，这样就会造成无穷递归
private:
	int _year;
	int _month;
	int _day;
};


class Stack01 {
public:
	Stack01(int capacity = 4) {
		_array = (int*)malloc(sizeof(int) * capacity);
		if (_array == nullptr) perror("malloc fail");
		_capacity = capacity;
		_top = 0;
	}



	//拷贝构造
	Stack01(const Stack01& st) {
		_array = (int*)malloc(sizeof(int) * st._capacity);
		if (_array == nullptr) perror("malloc fail");
		memcpy(_array, st._array, sizeof(int) * st._capacity);
		_capacity = st._capacity;
		_top = st._top;
	}
	//特点3.对未显式写出拷贝构造函数的类，编译器会自动生成一个拷贝构造函数，但这个拷贝构造函数只能进行浅拷贝/值拷贝
	//		所以Date01类其实可以不写拷贝构造函数，但是对于Stack01这种申请了资源的类来说仅仅靠自动生成的拷贝构造是远远不够的
	//		如果强制使用编译器提供的拷贝，_array 不会申请新的空间，而是直接将st._array的地址赋值给_array这样程序结束调用析构时
	//		同一空间会被析构两次，导致程序运行崩溃。



	void Push(int data) {
		if (_capacity == _top) {
			int newcapacity = _capacity == 0 ? 4 : _capacity * 2;
			int* tmp = (int*)realloc(_array, sizeof(int) * newcapacity);
			if (tmp == nullptr) perror("realloc fail");
			_array = tmp;
			_capacity = newcapacity;
		}
		_array[_top++] = data;
	}

	void Pop() {
		assert(_top);
		_top--;
	}

	void print() {
		for (size_t i = 0; i < _top; i++) cout << _array[i] << ' ';
		cout << endl;
	}

	~Stack01() {
		cout << "~Stack" << endl;
		free(_array);
		_array = nullptr;
		_capacity = _top = 0;
	}
private:
	int* _array;
	int _capacity;
	int _top;

};

class MyQueue01 {
public:
private:
	Stack01 STPush;
	Stack01 StPop;
};//特点4.对于内置类型可以直接调用类内的拷贝构造函数，但对于自定义类型会拷贝该自定义类的拷贝构造函数



void TestMain04() {
	Date01 d1(2024,1,1);
	Date01 d2(d1);
  //Date01 d2 = d1;这样写也对


	Stack01 st1;
	st1.Push(1);
	st1.Push(2);
	st1.Push(3);
	st1.Push(4);
	st1.Push(5);
	st1.print();
	Stack01 st2(st1);
	st2.print();//拷贝成功 两个打印函数的结果一样
}

//***********运算符重载函数************

class Date02 {
public:
	Date02(int year = 2025, int month = 2, int day = 2) {
		_year = year;
		_month = month;
		_day = day;
	}
	bool operator==(const Date02& d) {
		return (d._year == _year && d._month == _month && d._day == _day);
	}//运算符重载函数
	//特点1.运算符重载可以看成是一个具有特殊名称的函数，它也具有参数和返回值以及函数体
	//特点2.当运算符重载函数作为成员函数时，它的第一参数位一样会带有隐藏的  Date02* const this 参数
	bool operator<(const Date02& d) {
		if (_year < d._year) return true;
		else if (_year == d._year && _month < d._month) return true;
		else if (_year == d._year && _month == d._month && _day < d._day) return true;
		return false;
	}
	//特点3.运算符重载函数的参数数量和运算符的操作数数量是一样的，操作数在左边则作为第一个参数，在右边则作为第二个参数
	//特点4.运算符重载不是随便去写的也不能创造符号，比如：operator@ 也不是所有操作符都能重载的，如  .*  ::  ?:  .  sizeof 这五个
	//特点5.当重载前置++/--和后置++/--时编译器是不能靠参数和返回值来区分这两者的，此时后置++/--必须加一个int类型的占位参数，
	//		而前置++无参数，这是规定


private:
	int _year;
	int _month;
	int _day;
};
void TestMain05() {
	Date02 d1(20,2,2);
	Date02 d2;
	Date02 d3;
	cout << (d2 == d1) << endl;
	cout << (d3 == d2) << endl;
}


//***********赋值运算符重载*************
class Stack02 {
public:
	Stack02(int capacity = 4) {
		_array = (int*)malloc(sizeof(int) * capacity);
		if (_array == nullptr) perror("malloc fail");
		_capacity = capacity;
		_top = 0;
	}



	//拷贝构造
	Stack02(const Stack02& st) {
		_array = (int*)malloc(sizeof(int) * st._capacity);
		if (_array == nullptr) perror("malloc fail");
		memcpy(_array, st._array, sizeof(int) * st._capacity);
		_capacity = st._capacity;
		_top = st._top;
	}


	void Push(int data) {
		if (_capacity == _top) {
			int newcapacity = _capacity == 0 ? 4 : _capacity * 2;
			int* tmp = (int*)realloc(_array, sizeof(int) * newcapacity);
			if (tmp == nullptr) perror("realloc fail");
			_array = tmp;
			_capacity = newcapacity;
		}
		_array[_top++] = data;
	}

	void Pop() {
		assert(_top);
		_top--;
	}

	void print() {
		for (size_t i = 0; i < _top; i++) cout << _array[i] << ' ';
		cout << endl;
	}

	~Stack02() {
		free(_array);
		_array = nullptr;
		_capacity = _top = 0;
	}

	Stack02& operator=(const Stack02& st) {
		_array = (int*)malloc(sizeof(int) * st._capacity);
		if (_array == nullptr) perror("malloc fail");
		memcpy(_array, st._array, sizeof(int) * st._capacity);
		_capacity = st._capacity;
		_top = st._top;
		return *this;
	}//赋值运算符重载
	//特点1.赋值运算重载函数也是一个默认成员函数，要将它与拷贝构造区别开来，拷贝构造是指类实例化同时进行的类对象赋值操作
	//		而赋值运算符重载则是实例化后的类对象的直接赋值
	//特点2.赋值运算重载函数的参数尽量要用当前类类型的引用，返回值也建议返回当前类类型的引用，这样操作可以减少赋值拷贝，提高效率
	//特点3.赋值运算重载函数在不写时，编译器也会默认生成，但其对成员变量同样进行的是浅拷贝/值拷贝，对于自定义类型会调用它
	//		所在类的赋值重载函数，所以在有资源申请的类中赋值运算重载函数要自己写

private:
	int* _array;
	int _capacity;
	int _top;

};
void TestMain06() {
	Stack02 st1;
	st1.Push(1);
	st1.Push(1);
	st1.Push(1);
	st1.print();
	Stack02 st2;
	st2 = st1;
	st1.print();
	Stack02 st3;
	st3 = st2 = st1;
	st1.print();
	//特点4.赋值运算重载函数之所以有返回值是为了实现连续赋值的操作
}

//*****************总结*******************
//1.构造函数
//2.析构函数
//3.拷贝构造函数——>也属于构造函数
//4.运算符重载函数
//5.赋值运算重载函数——>也属于运算符重载函数，但注意不要和拷贝构造弄混了

//其中1，2，3，5 我们不写时编译器都可以默认生成







int main() {
	//TestMain01();
	//TestMain02();
	//TestMain03();
	//TestMain04();
	//TestMain05();
	TestMain06();
	return 0;
}
