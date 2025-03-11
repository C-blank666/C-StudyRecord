#include<iostream>
#include<vector>
using namespace std;
//class Student {
//public:
//	void identity() {
//		//...
//	}
//	void study() {
//		//...
//	}
//private:
//	string _name;
//	int _age;
//	string _tel;
//	string _address;
//
//	string stuid;//学号
//};
//class Teacher {
//public:
//	void identity() {
//		//...
//	}
//	void work() {
//		//...
//	}
//private:
//	string _name;
//	int _age;
//	string _tel;
//	string _address;
//
//	string title;//职称
//};
//可以看到两个具有相似特点的类分别写出后有很多的相同成员，显得十分冗余，这时便可以用继承解决
//如下：
class Person {
public:
	
	void identity() {
		cout << _name << endl;
		cout << _age << endl;
		cout << _tel << endl;
		cout << _adress << endl;
	}
protected://这里是protected限定符
	string _name;
	int _age;
	string _tel;
	string _adress;//首先写出父类（也叫做基类），父类的特点是拥有两个子类（也叫做派生类）的共同成员以便继承
};//父类

class Student :public Person {
public:
	Student(string name, int age, string tel, string adress) {
		_name = name;
		_age = age;
		_tel = tel;
		_adress = adress;
	}
	void Study() {
		cout << _name << endl;
		cout << _age << endl;
		cout << _tel << endl;
		cout << _adress << endl;
	}
private:
	string _stuid;
};//         继承方式 
//               ↓
class Teacher :public Person {
public:
	Teacher(string name, int age, string tel, string adress) {
		_name = name;
		_age = age;
		_tel = tel;
		_adress = adress;
	}
	void work() {
		cout << _name << endl;
		cout << _age << endl;
		cout << _tel << endl;
		cout << _adress << endl;
	}
private:
	string _title;
};
void test01() {
	Student s("王振",22, "19712797997", "中国郑州");
	s.identity();
	s.Study();
	Teacher t("李佳佳", 22, "19712797997", "中国郑州");
	t.identity();
	t.work();
}//可以看到子类成功的继承了父类的成员函数和成员变量
//两个子类的继承方式都是public即父类的所有可继承成员到了子类也是public限定符所修饰的
//同理继承方式是protected即父类的所有可继承成员到了子类也是protected限定符所修饰的
//继承方式是private即父类的所有可继承成员到了子类也是private限定符所修饰的

//但父类中的限定符修饰也会影响成员的继承，如果成员被private修饰，那么无论什么继承方式，子类都不能访问
//所以Person中的成员变量是用protected修饰的，这种修饰能保证子类可以访问，但类外不能访问，可以说protected限定符就是专门为继承准备的
//且父类成员在继承的过程中，成员的修饰限定权只会缩小不会放大，比如：父类的protected成员用public的方式继承到子类，该成员
//还是protected成员，如果用private的方式继承，那么就是private成员
//与类的修饰限定符规则类似，继承方式在不写时，如果是class则默认私有继承，struct则默认公有继承


//继承类模板


template<class T>
class My_Stack :protected vector<T> {//protected的继承方式能防止vector类中的成员泄露
public:
	void push(const T& data) {
		vector<T>::push_back(data);
	}
	void pop() {
		vector<T>::pop_back();
	}
	const T& top() {
		return vector<T>::back();
	}
	bool empty() {
		return vector<T>::empty();
	}
	int size() {
		return vector<T>::size();
	}
};//类模板继承
//我们可以看到继承类模板时，我们所使用的父类成员要在前面加上类名，原因是模板的实例化是按需实例化的，只有在前面加上类名才会实例化并访问
void test02() {
	My_Stack<int> M_st;
	M_st.push(1);
	M_st.push(2);
	M_st.push(3);
	M_st.push(4);
	while (M_st.size()) {
		cout << M_st.top() << " ";
		M_st.pop();
	}
}


//基类与派生类之间的转换
//以前面Student，Person类为例
void test03() {
	Student s("李佳佳", 22, "19712797997", "中国郑州");
	Person* rp = &s;
	Person& rpp = s;//public继承的派⽣类对象 可以赋值给 基类的指针 / 基类的引⽤。这样的过程可以称为切割或切片
}

//派生类常见的4个默认成员函数
class PersonA {
public:
	PersonA(const char* name)
		:_name(name)
		,_age(22)
		,_tel("19712797997")
	{
		cout << "PersonA(const char*)" << endl;
	}
protected:
	string _name;
	int _age;
	string _tel;
};
class StudentA :public PersonA {
public:
	StudentA(const char* name = "李佳佳", const char* stuid = "202322222")
		:_stuid(stuid)
		,PersonA(name)
	{
		cout << "StudentA(const char*)" << endl;
	}

private:
	string _stuid;
};
class PersonB {
public:
	PersonB(const char* name)//没有缺省值，这时父类没有默认构造函数
		:_name(name)
		, _age(22)
		, _tel("19712797997")
	{
		cout << "PersonA(const char*)" << endl;
	}
protected:
	string _name;
	int _age;
	string _tel;
};
class StudentB :public PersonB {
public:
	StudentB(const char* name, const char* stuid = "202322222")
		:_stuid(stuid)
		,PersonB(name)//在子类的初始化列表中调用父类非默认构造
	{
		cout << "StudentA(const char*)" << endl;
	}

private:
	string _stuid;
};

void test04() {
	StudentA sa;//派生类的构造函数的规则如下：
	//系统调用两个构造1.派生类的默认构造 2.父类的默认构造 
	StudentB sb("李佳佳");
	//父类没有默认构造时，需要在子类的构造中（如在初始化列表）显式对父类构造传参
	//总结：子类构造函数必须调用父类的默认构造来初始化父类的那一部分成员，如果父类没有默认构造就用子类构造函数的初始化列表显式调用
	//		父类非默认构造
	//注意：这时初始化列表的初始化顺序有所改变，即父类显式调用优先，其次按照声明来初始化子类成员变量
}
//拷贝构造函数

class PersonC {
public:
	PersonC(const char* name = "李佳佳") :_name(name), _age(22), _tel("19712797997"){
		cout << "PersonA(const char*)" << endl;
	}
	PersonC(const PersonC& pc) {
		cout << "父类显式自定义拷贝构造" << endl;
	}
protected:
	string _name;
	int _age;
	string _tel;
};
class StudentC :public PersonC {
public:
	StudentC(const char* name, const char* stuid = "202322222")
		:_stuid(stuid)
		,PersonC(name)
	{
		cout << "StudentA(const char*)" << endl;
	}
	//当派生类需要显式自定义拷贝构造函数时
	StudentC(const StudentC& sc) :PersonC(sc) {//必须调用父类的拷贝构造，不论父类的拷贝是默认生成的还是自定义的
		//...                         ↓
	}//                          这里的sc是StudengC类型的，
	//                       但是却被当作PersonC类形来传给父类拷贝构造，这里就应用到了基类与派生类之间的转换
	//						 即将父类的那一部分切割出来进行在父类中进行拷贝构造
	/*
	* 总结一下
	* 一旦子类自定义了拷贝构造函数，不论父类是否显式自定义了拷贝构造函数，都要在子类拷贝构造中的初始化列表显式调用
	* ，否则父类会调用构造函数，造成拷贝出现误差（编译器不会报错）。如果子类没有显式定义拷贝构造，那么不论父类是否显
	* 式构造，子类都会自动调用父类的拷贝构造函数
	*/

private:
	string _stuid;
};
void test05() {
	StudentC sc1("名字","123");
	StudentC sc2(sc1);
}

//赋值运算符重载函数
//子类调用父类赋值运算符重载函数的规则和子类调用父类的拷贝构造函数的规则一样
/*
当子类显式自定义赋值运算符重载函数时，不论父类的赋值运算符重载函数是否显式定义，都必须在子类赋值运算符重载函数中显式调用父类的赋值运算符重载函数
当子类默认生成赋值运算符重载函数时，不论父类的赋值运算符重载函数是否显式定义，子类赋值运算符重载函数都自动调用父类的赋值运算符重载函数
*/
class PersonD {
public:
	PersonD(const char* name)
		:_name(name)
		, _age(22)
		, _tel("19712797997")
	{
		cout << "PersonA(const char*)" << endl;
	}
	PersonD& operator=(const PersonD& pd) {
		cout << "赋值运算符重载函数" << endl;
	}
protected:
	string _name;
	int _age;
	string _tel;
};
class StudentD :public PersonD {
public:
	StudentD(const char* name = "李佳佳", const char* stuid = "202322222")
	
		:_stuid(stuid)
		, PersonD(name)
	{
		cout << "StudentA(const char*)" << endl;
	}
	StudentD& operator=(const StudentD& sd) {
		PersonD::operator=(sd);//这里的函数名后面跟了父类的类名，这里引出继承的隐藏规则，只要子类的函数名和父类相同，
		//子类使用同名函数时编译器就只认准子类中的，而屏蔽父类的，因此就算继承了也要专门在函数名前加上类名
		//就算参数不同也一样，不能说是函数重载，因为不在一个作用域
		return *this;
	}
private:
	string _stuid;
};

//析构函数
//析构函数很简单，不用我们主动去调用，我们只管写好父类和子类的析构函数，编译器会自动调用
//之所以让编译器自动调用是因为，在初始化时，编译器先初始化父类在初始化子类，那么销毁时编译器就要保证先析构子类再析构父类，所以编译器
//会自动调用，保证析构的顺序


//继承与友元
//继承的父类中如果有友元函数，那么友元函数不能被继承，如果想用父类的友元函数，就再在子类中再进行一次友元声明

//静态成员继承
class PersonE
{
public:
	string _name;
	static int _count;
};
int PersonE::_count = 0;
class StudentE : public PersonE
{
protected:
	int _stuNum;
};
void test06()
{
	PersonE pe;
	StudentE se;
	// 这⾥的运⾏结果可以看到⾮静态成员_name的地址是不⼀样的
	// 说明派⽣类继承下来了，⽗派⽣类对象各有⼀份
	cout << &pe._name << endl;
	cout << &se._name << endl;
	// 这⾥的运⾏结果可以看到静态成员_count的地址是⼀样的
	// 说明派⽣类和基类共⽤同⼀份静态成员
	cout << &pe._count << endl;
	cout << &se._count << endl;
	// 公有的情况下，⽗派⽣类指定类域都可以访问静态成员
	cout << PersonE::_count << endl;
	cout << StudentE::_count << endl;
}

//多继承问题
class PersonF {
public:
	string _name;
};
class TeacherF :public PersonF {
protected:
	string _title;
};
class StudentF :public PersonF {
protected:
	string _stuid;
};
class Admin :public StudentF,public TeacherF {
private:
	string _mainClass;
};
//C++允许多继承的存在，一个子类有一个直接父类是单继承，一个子类有一个或多个直接父类则是多继承
//多继承很容易出现棱形继承的情况，棱形继承会导致数据冗余和二义性等问题
void test07() {
	Admin a;
	cout << a.StudentF::_name << endl;//
	cout << a.TeacherF::_name<< endl;//这种棱形继承会导致出现两份父类成员，需要指定访问
	//_name是两份，有不同的地址

}
//如何解决，用虚继承
class PersonF1 {
public:
	string _name;
};
class TeacherF1 :virtual public PersonF1 {
protected:
	string _title;
};
class StudentF1 :virtual public PersonF1 {
protected:
	string _stuid;
};
class Admin1 :public StudentF1, public TeacherF1 {
private:
	string _mainClass;
};
//在继承同一父类的子类继承方式前加上virtual,这时的_name就会变成一份
void test07() {
	Admin1 a;
	cout << a._name << endl;//不用在指定类名
}

int main() {
	//test01();
	//test02();
	//test04();
	test05();
	return 0;
}