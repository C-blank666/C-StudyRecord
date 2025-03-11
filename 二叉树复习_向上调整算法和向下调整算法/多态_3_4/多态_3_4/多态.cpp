#include<iostream>
using namespace std;
//多态
//多态分为静态和动态，静态是指编译时多态，动态是指运行时多态
// 多态是一个继承关系下的类对象，去调用同一函数，产生了不同的行为
//这里只讨论运行时多态
//多态的条件
//1.必须是基类的指针或引用去调用虚函数
//2.调用的函数必须是虚函数，且完成了函数重写/函数覆盖
//多态举例：
class Person {
public:
	virtual void BuyTicket() {
		cout << "票价：成人票价" << endl;
	}
};
class Student :public Person {
public:
	virtual void BuyTicket() {
		cout << "票价：儿童票价" << endl;
	}
};
void func(Person* tmp) {//这里有个关键点，正如多态条件一所说，必须是基类的引用或指针调用虚函数，这里的
	//父类能接受子类也引用了上节基类和派生类之间的转换的知识


	//如果是p调用父类的BuyTicket()	
	//如果是s调用子类的BuyTicket()
	//这里调用同一函数却产生了不同的行为，这就是多态
	tmp->BuyTicket();
}
void test01() {
	//创建具有继承关系的不同类对象
	Person p;
	Student s;
	//向同一基类类型传地址
	func(&p);
	func(&s);
}


//虚函数的要求：函数前用virtual修饰，必须是成员函数，且不能是静态函数
//virtual void test(){
//  ...否则编译报错
//}

//虚函数的重写/覆盖
/*
*  在派生类中有和基类完全一样的虚函数（函数名相同，参数列表相同，返回值相同），称为虚函数的重写。
*  如果基类的虚函数已经被virtual修饰，子类的重写虚函数可以不写virtual，因为子类继承了父类虚函数的虚性，但也同时也继承了一些父
*  类虚函数的性质（如不同的缺省值），并不安全，所以平时重写虚函数时还是要加上virtual
*/

//虚析构函数的重写
//当父类的析构函数是虚函数时，不论子类的析构函数是否虚函数，都与父类构成重写，虽然析构函数的函数名一样，但编译器会将析构函数名同一
//处理为 destructor() 
//原因，当子类对象以父类类型出现时，将会按照父类类型进行析构，这时子类如果申请了资源，就无法释放，造成内存泄露，而如果
//子类对父类的析构函数进行了重写，父类型的子类对象会传给子类析构函数，进而进行析构。
class A {
public:
	virtual ~A() {
		cout << "~A()" << endl;
	}
};
class B :public A {
public:
	~B() {
		delete[] _a;
		_a = nullptr;
		cout << "~B()" << endl;
	}
private:
	int* _a = new int[10];
};
void test02() {
	A* a = new A;
	A* b = new B;

	delete a;
	delete b;
}
//override
//override可以检查程序员写的重写函数是否构成重写，
class Car {
public:
	virtual void Drive()
	{}
};
class Benz :public Car {
public:
	virtual void Drive() override  { cout << "Benz-舒适" << endl; }
};
//final
//final 可以防止函数被重写

//纯虚函数
//当给类中包含纯虚函数，那么这个类被称为抽象类，纯虚函数没有函数体，且不能被实例化，如果派生类继承抽象函数后没有重写纯虚函数，那么派生类也是抽象函数
//抽象函数在某中程度上强制了派生类重写纯虚函数，因为不写不能被实例化。
class C {
public:
	virtual void test() = 0;
};
class D :public C {
public:
	virtual void test() {
		cout << "D重写纯虚函数" << endl;
	}
};
class E :public C {
public:
	virtual void test() {
		cout << "E重写纯虚函数" << endl;
	}
};
void test03() {
	C* d = new D;
	C* e = new E;

	d->test();
	e->test();
}
int main() {
	test01();
	test03();
	return 0;
}
