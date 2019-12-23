//Date.h 

#ifndef DATE_H
#define DATE_H

#include <ostream>

// simple Date (use Month type)
class Date {
public:
	/*enum Month {
		jan=1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
	};*/

	// constructors
	Date(int y, /*Month m*/int m, int d, int h, int min);    // check for valid date and initialise
	Date();                         // default constructor

	// const members: can't modify the object
	int year() const;
	//Month month() const;
	int month() const;
	int day() const;
	int hour() const;
	int minutes() const;
	void set_data(Date data_da_settare);
	// non-const members
	void add_year(int n);
	void add_month(int n);
	void add_day(int n);

	bool is_dopo(Date date);
private:
	int y;      // year
	//Month m;
	int m;
	int d;      // day of month
	int h;
	int min;
};

// operators
std::ostream& operator<<(std::ostream& os, const Date& d);

#endif
