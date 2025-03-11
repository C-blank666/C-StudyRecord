#pragma once
#include<iostream>
#include<assert.h>
using namespace std;
//const成员函数
/*
*1. const修饰成员函数成员函数时直接将const添加在成员函数之后即可
*2. const修饰的成员函数本质上修饰的是形参this指针，隐含的this形参是这样的（以Date为例）： Date* const this  可以
*   可以看出这里的const修饰单独是this指针，防止改变指向。而const修饰的成员函数形参this效果如下：const Date* const this 
*	即又用const修饰了this指针的指向的内容。
* 3.这样修饰是为了防止传参是传的的是const修饰的this类类型地址 如 const Date d 这里const修饰的是内容
* 4.const修饰成员函数的原则是应加尽加，但也不代表所有函数都要加，如果函数对成员变量进行了修改，就不要加const。
* 5.其次当声明变量分离时，声明和变量都要加上const修饰
*	如下以日期类为例。
*/
class Date {

	//友元函数
	friend ostream& operator<<(ostream& out, const Date& d);
	friend istream& operator>>(istream& in,  Date& d);


public:
	Date(int year = 2025, int month = 2, int day = 27)  {//不能加const函数，因为构造函数要修改日期
		_year = year;
		_month = month;
		_day = day;
		if (!chackDate()) {
			cout << "日期错误" << endl;
			cout << _year << "年" << _month << "月" << _day << "日" << endl;
		}
	}
	bool chackDate() const{//可以加，内容没有对成员变量的修改
		if (_month < 0 || _month>12 || _day<0 || _day>GetMonthDay(_year, _month))
			return false;
		else
			return true;
	}
	bool operator==(const Date& d)const;
	bool operator!=(const Date& d)const;
	bool operator<(const Date& d)const;
	bool operator>(const Date& d)const;
	bool operator>=(const Date& d)const;
	bool operator<=(const Date& d)const;

	

	int GetMonthDay(int year, int month) const {
		assert(month > 0 && month < 13);
		static int MonthDay[13] = { -1, 31, 28, 31, 30, 31, 30,
31, 31, 30, 31, 30, 31 };
		if ((month == 2) && ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))) {
			return 29;
		}
		return MonthDay[month];
	}
	void print() const{
		cout << _year << '/' << _month << '/' << _day << endl;
	}


	Date& operator+=(const int& day);//不可以加，因为修改了成员变量
	Date operator+(const int& day) const {//可以加，*this没有被改变
		Date tmp = *this;
		tmp += day;
		return tmp;
	}
	Date& operator-=(const int& day);
	Date operator-(const int day) const{
		Date tmp = *this;
		tmp -= day;
		return tmp;
	}
	Date& operator++() {
		*this += 1;
		return *this;
	}
	Date operator++(int) {
		Date tmp = *this;
		*this += 1;
		return tmp;
	}
	int operator-(const Date& d)const;

	Date* operator&() {
		return this;
	}
	const Date* operator&()const {
		return this;
	}//第六个默认成员函数，取地址运算符重载，这个也是编译器可以默认生成的（默认生成的就够了），分为普通的和const修饰的，编译器会自动匹配

private:
	int _year;
	int _month;
	int _day;
};
