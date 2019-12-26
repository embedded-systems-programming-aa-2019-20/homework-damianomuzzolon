//Park.h

#ifndef PARK_H
#define PARK_H

#include <mutex>
using std::mutex;
#include <list>
using std::list;
#include <cstdbool>
#include <condition_variable>
using std::condition_variable;
#include "Auto.h"
#include "Date.h"

class Park{
	public:
		//costruttori
		Park();
		Park(int cap);
		//getter
		Date get_prossima_entrata() const {return prossima_entrata;}
		Date get_prossima_uscita() const {return prossima_uscita;}
		list<Auto> get_auto_presenti() const {return auto_presenti;}
		int get_numero_auto() const {return numero_auto;}

		//funzioni
		void fai_entrare_auto(Auto& car); //riferimento perchè modifica car dicendo se può o non può entrare (bool is_entrata)
		void fai_uscire_auto(Auto car);
		void print_lista_auto();
		void set_uscite_finite();
		void set_entrate_finite();
	
	private:
		list<Auto> auto_presenti;
		int capienza;
		Date prossima_entrata;
		Date prossima_uscita;
		int numero_auto;
		bool uscite_sono_finite;
		bool entrate_sono_finite;

		mutex mutex_;
		condition_variable mio_turno_per_uscire;
		condition_variable mio_turno_per_entrare;
};

#endif
