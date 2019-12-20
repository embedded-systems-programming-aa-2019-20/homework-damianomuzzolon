//Test_auto.cpp

#include <iostream>
using std::cout;
using std::endl;
#include "Auto.h"
#include "Date.h"

int main(){
	string targa1{"FC162ZN"};
	Date data1{2019, Date::Month::dec, 20, 21, 18};

	//test costruttori
	Auto kia{targa1, data1};
	Auto lancia;
	cout << kia.get_targa() << ' ' << kia.get_data_ingresso() << endl;
	cout << lancia.get_targa() << ' ' << lancia.get_data_ingresso() << endl;

	return 0;
}
