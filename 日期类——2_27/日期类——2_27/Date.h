#pragma once
#include<iostream>
#include<assert.h>
using namespace std;

class Date {

	//友元函数
	friend ostream& operator<<(ostream& out, const Date& d);
	friend istream& operator>>(istream& in,  Date& d);


public:
	Date(int year = 2025, int month = 2, int day = 27) {
		_year = year;
		_month = month;
		_day = day;
		if (!chackDate()) {
			cout << "日期错误" << endl;
			cout << _year << "年" << _month << "月" << _day << "日" << endl;
		}
	}
	bool chackDate() {
		if (_month < 0 || _month>12 || _day<0 || _day>GetMonthDay(_year, _month))
			return false;
		else
			return true;
	}
	bool operator==(const Date& d);
	bool operator!=(const Date& d);
	bool operator<(const Date& d);
	bool operator>(const Date& d);
	bool operator>=(const Date& d);
	bool operator<=(const Date& d);

	

	int GetMonthDay(int year,int month) {
		assert(month > 0 && month < 13);
		static int MonthDay[13] = { -1, 31, 28, 31, 30, 31, 30,
31, 31, 30, 31, 30, 31 };
		if ((month == 2) && ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))) {
			return 29;
		}
		return MonthDay[month];
	}
	void print() {
		cout << _year << '/' << _month << '/' << _day << endl;
	}


	Date& operator+=(const int& day);
	Date operator+(const int& day) {
		Date tmp = *this;
		tmp += day;
		return tmp;
	}
	Date& operator-=(const int& day);
	Date operator-(const int day) {
		Date tmp = *this;
		*this -= day;
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
	int operator-(const Date& d);

private:
	int _year;
	int _month;
	int _day;
};
