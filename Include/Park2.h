//Park2.h

#ifndef PARK2_H
#define PARK2_H

#include <mutex>
using std::mutex;
#include <list>
using std::list;
#include <cstdbool>
#include <condition_variable>
using std::condition_variable;
#include "Auto.h"
#include "Date.h"

class Park2{
	public:
		//costruttori
		Park2();
		Park2(int cap);
		//getter
		Date get_prossima_entrata() const {return prossima_entrata;}
		Date get_prossima_uscita() const {return prossima_uscita;}
		list<Auto> get_auto_presenti() const {return auto_presenti;}
		//bool get_is_uscita_aggiornata() const {return is_uscita_aggiornata;}
		//bool get_is_entrata_aggiornata() const {return is_entrata_aggiornata;}
		int get_numero_auto() const {return numero_auto;}
		//bool get_finite_auto_che_entrano() {return finite_auto_che_entrano;}
		//bool get_finite_auto_che_escono() {return finite_auto_che_escono;}

		//funzioni
		//void aggiorna_prossima_entrata(Date d);
		void fai_entrare_auto(Auto &car);
		//void aggiorna_prossima_uscita(Date d);
		void fai_uscire_auto(Auto car);
		void print_lista_auto();
		void set_uscite_finite();
		void set_entrate_finite();
		//void signal_su_uscite_rimaste();//eseguita in concorrenza
		//void signal_su_entrate_rimaste();//eseguita in concorrenza
		//void set_finite_auto_che_escono(){ finite_auto_che_escono = true;}
		//void set_finite_auto_che_entrano(){ finite_auto_che_entrano = true;}
	private:
		list<Auto> auto_presenti;
		int capienza;
		Date prossima_entrata;
		Date prossima_uscita;
		int numero_auto;
		bool uscite_sono_finite;
		bool entrate_sono_finite;
		//bool finite_auto_che_escono;
		//bool finite_auto_che_entrano;
		//bool is_entrata_aggiornata;
		//bool is_uscita_aggiornata;
		list<Auto>::iterator pos;

		mutex mutex_;
		condition_variable mio_turno_per_uscire;
		condition_variable mio_turno_per_entrare;
};

#endif
