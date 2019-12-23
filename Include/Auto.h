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
		bool get_is_entrata() const {return is_entrata;}
		void auto_non_entrata(){is_entrata = false;}
	private:
		string targa;
		Date data_ingresso;
		bool is_entrata;
};

#endif
