//Date.h 

#ifndef DATE_H
#define DATE_H

#include <ostream>

// simple Date (use Month type)
class Date {
public:
	// constructors
	Date(int y, int m, int d, int h, int min);    // check for valid date and initialise
	Date();                         // default constructor

	// const members: can't modify the object
	int year() const;
	int month() const;
	int day() const;
	int hour() const;
	int minutes() const;
	
	void set_data(Date data_da_settare);
	bool is_dopo(Date date); //dice se la data è dopo la data date
private:
	int y;      // year
	int m;
	int d;      // day of month
	int h;
	int min;
};

// operators
std::ostream& operator<<(std::ostream& os, const Date& d);

#endif
