#include<string>
#include<iostream>
#include<vector>
using namespace std;

double Divide(int a, int b) {
	try {
		if (b == 0) {
			string s = "Divide by zero condition";
			throw s;
		}
		else {
			return (double)a / (double)b;
		}
	}
	//catch(const string& errmsg)
	catch (int errid) {
		cout << errid << endl;
	}
	cout << __FUNCTION__ << ':' << __LINE__ << "行执行" << endl;

}

void Func() {
	int len, time;
	cin >> len >> time;
	try {
		Divide(len,time);
	}
	//catch(const string& errmsg)
	catch (const char* errmsg) {
		cout << errmsg << endl;
	}
	cout << __FUNCTION__ << ':' << __LINE__ << "行执行" << endl;
}

void TestMain01() {
	while (1) {
		try {
			Func();
		}
		catch (const string& errmsg) {
			cout << errmsg << endl;
		}
		cout << __FUNCTION__ << ':' << __LINE__ << "行执行" << endl;
	}
}
/*
	1.当程序出现问题时，我们通过throw一个对象来引发一个异常，该对象的类型及当前的的调用链决定了
	catch的处理代码来处理异常
	2.被选中的catch是调用链中与该对象类型匹配且离异常抛出位置是最近的，根据抛出的对象的类型和内容
	程序抛出异常部分告知异常处理部分发生了什么
	3。当throw执行时，throw后面的代码将不再执行，程序的执行由throw位置直接跳到最符合的异常处理部分，catch的位置可能
	是同一函数的局部catch也可能是调用链中其他函数的catch位置，控制权由throw到了catch。这里有两个
	重要含义 a.调用链中的函数可能提前退出 b.一旦程序开始处理异常，随着throw的跳出，途中沿着调用链函数
	创建的对象都将被一一销毁。
	4.抛出异常后，这里会生成一个拷贝，因为抛出的对象是一个局部对象，所以会生成一个拷贝对象，这个拷贝
	对象会在catch语句执行后被销毁
	
*/
//栈展开
//抛出异常后，程序暂停当前函数的执⾏，开始寻找与之匹配的catch⼦句，⾸先检查throw本⾝是否
//在try块内部，如果在则查找匹配的catch语句，如果有匹配的，则跳到catch的地⽅进⾏处理。
//• 如果当前函数中没有try / catch⼦句，或者有try / catch⼦句但是类型不匹配，则退出当前函数，继续
//在外层调⽤函数链中查找，上述查找的catch过程被称为栈展开。
//• 如果到达main函数，依旧没有找到匹配的catch⼦句，程序会调⽤标准库的 terminate 函数终⽌
//程序。
//• 如果找到匹配的catch⼦句处理后，catch⼦句代码会继续执⾏。


int main() {
	TestMain01();
	return 0;
}