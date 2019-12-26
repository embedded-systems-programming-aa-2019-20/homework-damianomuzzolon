//Park.cpp

#include "Park.h"
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
Park::Park(int cap):capienza{cap},prossima_entrata{1900,1,1,0,0},prossima_uscita{1900,1,1,0,0}, auto_presenti(0), numero_auto{0},uscite_sono_finite{false}, entrate_sono_finite{false}{}
Park::Park():capienza{0},prossima_entrata{1900,1,1,0,0},prossima_uscita{1900,1,1,0,0}, auto_presenti(0), numero_auto{0},entrate_sono_finite{false},uscite_sono_finite{false}{}

//funzioni
void Park::fai_entrare_auto(Auto& car){
    unique_lock<std::mutex> mlock(mutex_);
    prossima_entrata.set_data(car.get_data_ingresso());
    mio_turno_per_uscire.notify_one();
    mlock.unlock();
    unique_lock<std::mutex> mxlock(mutex_);
    while(prossima_entrata.is_dopo(prossima_uscita) && !uscite_sono_finite) //faccio andare le thread in ordine cronologico
        mio_turno_per_entrare.wait(mxlock);
    if(numero_auto == capienza){
        car.auto_non_entrata();
    } else {
        auto_presenti.push_back(car);
        numero_auto++; //c'è un'auto in più
    }
}

void Park::fai_uscire_auto(Auto car){
    unique_lock<std::mutex> mlock(mutex_);
    prossima_uscita.set_data(car.get_data_ingresso()); //ATTENZIONE: in car c'è la data di uscita
    mio_turno_per_entrare.notify_one();
    mlock.unlock();
    unique_lock<std::mutex> mxlock(mutex_);
    while(prossima_uscita.is_dopo(prossima_entrata) && !entrate_sono_finite) //faccio andare le thread in ordine cronologico
        mio_turno_per_uscire.wait(mxlock);
    
    list <Auto>::iterator auto_da_eliminare; //cerco l'auto da eliminare
    for(auto_da_eliminare = auto_presenti.begin(); auto_da_eliminare != auto_presenti.end(); auto_da_eliminare++){
        if((*auto_da_eliminare).get_targa() == car.get_targa())
            break;
    }

    auto_presenti.erase(auto_da_eliminare); //elimino l'auto
    numero_auto--; //c'è un'auto in meno
} 

void Park::set_uscite_finite(){
    unique_lock<std::mutex> mlock(mutex_);
    uscite_sono_finite = true;
    mio_turno_per_entrare.notify_one();
}

void Park::set_entrate_finite(){
    unique_lock<std::mutex> mlock(mutex_);
    entrate_sono_finite = true;
    mio_turno_per_uscire.notify_one();
}

void Park::print_lista_auto(){
    list<Auto>::iterator index = auto_presenti.begin();
    for(int i = 0; i < get_numero_auto(); ++i){
        cout << (*index).get_data_ingresso() << ' ' << (*index).get_targa() << endl;
        ++index;
    }
}