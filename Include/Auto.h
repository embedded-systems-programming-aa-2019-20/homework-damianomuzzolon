//Auto.h

#ifndef AUTO_H
#define AUTO_H

#include <ostream>
#include <string>
using std::string;
#include "Date.h"

class Auto{
	public:
		//costruttori
		Auto();
		Auto(string targa, Date data_ingresso);
		//getter
		string get_targa() const {return targa;}
		Date get_data_ingresso() const {return data_ingresso;}
	private:
		string targa;
		Date data_ingresso;
};

#endif
