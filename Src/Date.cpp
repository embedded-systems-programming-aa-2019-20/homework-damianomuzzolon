//Date.cpp

#include <ostream>
using std::ostream;
#include <iostream>
using std::cerr;
#include "Date.h"

// helper functions

// check for valid date and initialise
Date::Date(int yy, int mm, int dd, int hh, int minmin)
	:y{yy}, m{mm}, d{dd}, h{hh}, min{minmin}
{
	if (m<1 || m>12 || d<1 || d>31)  {
		cerr << "invalid date\n";
		exit(1);
	}
	if (h<0 || h>23 || min<0 || min>59){
		cerr << "Invalid hour/minutes\n";
		exit(1);
	}

}

const Date& default_date()
{
	static Date dd{2001,1,1,0,0};   // start of 21st century
	return dd;
}

Date::Date()
	:y{default_date().year()},
	m{default_date().month()},
	d{default_date().day()},
	h{default_date().hour()},
	min{default_date().minutes()}
{
}

// return year
int Date::year() const
{
	return y;
}

// return month
int Date::month() const
{
	return m;
}

// return day of month
int Date::day() const
{
	return d;
}

int Date::hour() const
{
	return h;
}

int Date::minutes() const
{
	return min;
}

bool Date::is_dopo(Date date){ //la data è dopo date?
	if(y > date.year())
		return true;
	else if(y == date.year() && m > date.month())
		return true;
	else if(y == date.year() && m == date.month() && d > date.day())
		return true;
	else if(y == date.year() && m == date.month() && d == date.day() && h > date.hour())
		return true;
	else if(y == date.year() && m == date.month() && d == date.day() && h == date.hour() && min > date.minutes())
		return true;
	return false; //ha cercato se una data è dopo date, se arriva alla fine degli if è perchè non è dopo date
}

void Date::set_data(Date data_da_settare){
	y = data_da_settare.year();
	m = data_da_settare.month();
	d = data_da_settare.day();
	h = data_da_settare.hour();
	min = data_da_settare.minutes();
}

// operators
ostream& operator<<(ostream& os, const Date& d)
{
	return os << '(' << d.year()
		<< ',' << d.month()
		<< ',' << d.day()
		<< ',' << d.hour()
		<< ':' << d.minutes()
		<< ')';
}
