//Date.cpp

#include <ostream>
using std::ostream;
#include <iostream>
using std::cerr;
#include "Date.h"

// helper functions

// check for valid date and initialise
Date::Date(int yy, Month mm, int dd, int hh, int minmin)
	:y{yy}, m{mm}, d{dd}, h{hh}, min{minmin}
{
	if (m<Date::jan || m>Date::dec || d<1 || d>31)  {
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
	static Date dd{2001,Date::jan,1,0,0};   // start of 21st century
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
Date::Month Date::month() const
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

// increase the date by n years
void Date::add_year(int n)
{
	y += n;
}

// increase the date by n months
void Date::add_month(int n)
{
	// too complicated
}

// increase the Date by n days
void Date::add_day(int n)
{
	d += n;
	if (d > 31) {
		cerr << "add_day() results in invalid date\n";
		exit(1);
	}

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
