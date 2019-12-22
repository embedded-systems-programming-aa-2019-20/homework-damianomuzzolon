//Park1.h

#ifndef PARK1_H
#define PARK1_H

#include <mutex>
using std::mutex;
#include <list>
using std::list;
#include <cstdbool>
#include "Auto.h"
#include "Date.h"

class Park1{
	public:
		//costruttori
		Park1();
		Park1(int cap);
		//getter
		Date get_prossima_entrata() const {return prossima_entrata;}
		Date get_prossima_uscita() const {return prossima_uscita;}
		list<Auto> get_auto_presenti() const {return auto_presenti;}
		//bool get_is_uscita_aggiornata() const {return is_uscita_aggiornata;}
		//bool get_is_entrata_aggiornata() const {return is_entrata_aggiornata;}
	private:
		list<Auto> auto_presenti;
		int capienza;
		Date prossima_entrata;
		Date prossima_uscita;

		//bool is_entrata_aggiornata;
		//bool is_uscita_aggiornata;

		mutex mutex_;
};

#endif
