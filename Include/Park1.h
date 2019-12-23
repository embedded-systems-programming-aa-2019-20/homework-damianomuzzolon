//Park1.h

#ifndef PARK1_H
#define PARK1_H

#include <mutex>
using std::mutex;
#include <list>
using std::list;
#include <cstdbool>
#include <condition_variable>
using std::condition_variable;
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
		int get_numero_auto() const {return numero_auto;}
		//funzioni
		void aggiorna_prossima_entrata(Date d);
		void fai_entrare_auto(Auto car);
		void aggiorna_prossima_uscita(Date d);
		void fai_uscire_auto(Auto car);
	private:
		list<Auto> auto_presenti;
		int capienza;
		Date prossima_entrata;
		Date prossima_uscita;
		int numero_auto;
		//bool is_entrata_aggiornata;
		//bool is_uscita_aggiornata;
		list<Auto>::iterator pos;

		mutex mutex_;
		condition_variable mio_turno_per_uscire;
		condition_variable mio_turno_per_entrare;
};

#endif
