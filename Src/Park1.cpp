//Park1.cpp

#include "Park1.h"
#include "Auto.h"
#include "Date.h"
#include <mutex>
using std::mutex;
using std::unique_lock;
#include <cstdbool>
#include <list>
using std::list;
#include <iostream>
using std::cout;
using std::endl;
#include <algorithm>

//costruttori
Park1::Park1(int cap):capienza{cap},prossima_entrata{1900, Date::Month::jan,1 ,0 ,0},prossima_uscita{1900, Date::Month::jan,1 ,0 ,0}, /*is_entrata_aggiornata{false}, is_uscita_aggiornata{false},*/ auto_presenti(cap), numero_auto{0}, pos{auto_presenti.begin()}{}
Park1::Park1():capienza{0},prossima_entrata{1900, Date::Month::jan,1 ,0 ,0},prossima_uscita{1900, Date::Month::jan,1 ,0 ,0}, /*is_entrata_aggiornata{false}, is_uscita_aggiornata{false},*/ auto_presenti(0), numero_auto{0},pos{auto_presenti.begin()}{}
//funzioni
void Park1::aggiorna_prossima_entrata(Date d){
    unique_lock<std::mutex> mlock(mutex_);
    prossima_entrata = d;
    mio_turno_per_uscire.notify_one(); //ogni volta che aggiorno la data mando una signal all'altra thread
}
void Park1::fai_entrare_auto(Auto car){
    unique_lock<std::mutex> mlock(mutex_);
    while(prossima_entrata.is_dopo(prossima_uscita)) //faccio andare le thread in ordine cronologico
        mio_turno_per_uscire.wait(mlock);
    if(numero_auto == capienza){
        cout << car.get_data_ingresso() << ' ' << car.get_targa() << ' ' << "Non entrata. Park1 pieno" << endl;  
    }
    else {
        *pos = car; //metto l'auto nella lista. pos è nel monitor perchè entrambe le thread lo modificano
        numero_auto++; //c'è un'auto in più
        cout << (*pos).get_data_ingresso() << ' ' << (*pos).get_targa() << ' ' << "IN " << "PARK1" << endl;
        pos++;
    }
}

void Park1::aggiorna_prossima_uscita(Date d){
    unique_lock<std::mutex> mlock(mutex_);
    prossima_uscita = d;
    mio_turno_per_entrare.notify_one();
}

void Park1::fai_uscire_auto(Auto car){
    unique_lock<std::mutex> mlock(mutex_);
    while(prossima_uscita.is_dopo(prossima_entrata)) //faccio andare le thread in ordine cronologico
        mio_turno_per_uscire.wait(mlock);
    
    list <Auto>::iterator auto_da_eliminare; //cerco l'auto da eliminare
    for(auto_da_eliminare = auto_presenti.begin(); auto_da_eliminare != pos; auto_da_eliminare++){
        if((*auto_da_eliminare).get_targa() == car.get_targa())
            break;
    }

    auto_presenti.erase(auto_da_eliminare); //elimino l'auto
    numero_auto--; //c'è un'auto in meno
    pos--; //così faccio entrare le auto nella posizione corretta
    cout << car.get_data_ingresso() << ' ' << car.get_targa() << ' ' << "OUT " << "PARK1" << endl;
} //il cout è dentro alla sezione critica perchè voglio che stampi entrate e uscite in ordine 
