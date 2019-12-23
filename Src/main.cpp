//main.cpp

#include <fstream>
using std::ifstream;
#include <iostream>
using std::cout;
using std::endl;
#include <sstream>
using std::istringstream;
#include <string>
using std::string;
#include <thread>
using std::thread;
#include "Park1.h"
#include "Park2.h"
#include "Auto.h"
#include "Date.h"


#define CAP1 3
#define CAP2 2

Park1 parcheggio_1(CAP1);
Park2 parcheggio_2(CAP2);
mutex semaphore;

void gestione_accessi_P1(Date fine_simulaz){
    // open a file in read mode. APERTURA ESEGUITA IN CONCORRENZA
    ifstream infile;
    infile.open("../../input_files/parcheggioUnoIngresso.txt");
   	
    if (!infile.is_open()) {
        cout << "error opening the input file\n";
        exit(EXIT_FAILURE);
    }

    string line;
    while (getline(infile, line)){
        istringstream iss(line);
        int yy, mm, dd, hh, minmin;
        string t;
        if (!(iss >> t >> yy >> mm >> dd >> hh >> minmin)) { break; } // error
        //adesso ha spacchettato le informazioni dell'auto. Converto il mese
        Date d_ingr{yy, mm, dd, hh, minmin};
        if(d_ingr.is_dopo(fine_simulaz))
            break;
        Auto car{t, d_ingr};
        //inizio della sezione critica
        //parcheggio_1.aggiorna_prossima_entrata(d_ingr);
        parcheggio_1.fai_entrare_auto(car);
        semaphore.lock();
        if(car.get_is_entrata())
            cout << car.get_data_ingresso() << ' ' << car.get_targa() << ' ' << "IN " << "PARK1" << endl;
        else 
            cout << car.get_data_ingresso() << ' ' << car.get_targa() << ' ' << "Non entrata. Park1 pieno" << endl;
        semaphore.unlock();
    }
    parcheggio_1.set_entrate_finite();
    /*parcheggio_1.set_finite_auto_che_entrano(); //Mi serve perchè va in deadlock perchè una thread non fa più la signal sull'altra
    while(parcheggio_1.get_finite_auto_che_escono() == false)
        parcheggio_1.signal_su_uscite_rimaste();*/
}

void gestione_uscite_P1(Date fine_simulaz){
    // open a file in read mode. APERTURA ESEGUITA IN CONCORRENZA
    ifstream infile;
    infile.open("../../input_files/parcheggioUnoUscita.txt");
   	
    if (!infile.is_open()) {
        cout << "error opening the input file\n";
        exit(EXIT_FAILURE);
    }
    
    string line;
    while (getline(infile, line)){
        istringstream iss(line);
        int yy, mm, dd, hh, minmin;
        string t;
        if (!(iss >> t >> yy >> mm >> dd >> hh >> minmin)) { break; } // error
        //adesso ha spacchettato le informazioni dell'auto
        Date d_usc{yy, mm, dd, hh, minmin};
        if(d_usc.is_dopo(fine_simulaz))
            break;
        Auto car{t, d_usc};
        //inizio della sezione critica
        //parcheggio_1.aggiorna_prossima_uscita(d_usc);
        parcheggio_1.fai_uscire_auto(car);
        semaphore.lock(); //Per mutua esclusione tra parcheggio_1 e parcheggio_2 nell'uso del cout 
        cout << car.get_data_ingresso() << ' ' << car.get_targa() << ' ' << "OUT " << "PARK1" << endl;
        semaphore.unlock();
    }
    parcheggio_1.set_uscite_finite();
    /*parcheggio_1.set_finite_auto_che_escono();
    while(parcheggio_1.get_finite_auto_che_entrano() == false)
        parcheggio_1.signal_su_entrate_rimaste();*/
}

void gestione_accessi_P2(Date fine_simulaz){
    // open a file in read mode. APERTURA ESEGUITA IN CONCORRENZA
    ifstream infile;
    infile.open("../../input_files/parcheggioDueIngresso.txt");
   	
    if (!infile.is_open()) {
        cout << "error opening the input file\n";
        exit(EXIT_FAILURE);
    }

    string line;
    while (getline(infile, line)){
        istringstream iss(line);
        int yy, mm, dd, hh, minmin;
        string t;
        if (!(iss >> t >> yy >> mm >> dd >> hh >> minmin)) { break; } // error
        //adesso ha spacchettato le informazioni dell'auto. Converto il mese
        Date d_ingr{yy, mm, dd, hh, minmin};
        if(d_ingr.is_dopo(fine_simulaz))
            break;
        Auto car{t, d_ingr};
        //inizio della sezione critica
        //parcheggio_1.aggiorna_prossima_entrata(d_ingr);
        parcheggio_2.fai_entrare_auto(car);
        semaphore.lock();
        if(car.get_is_entrata())
            cout << car.get_data_ingresso() << ' ' << car.get_targa() << ' ' << "IN " << "PARK2" << endl;
        else 
            cout << car.get_data_ingresso() << ' ' << car.get_targa() << ' ' << "Non entrata. Park2 pieno" << endl;
        semaphore.unlock();
    }
    parcheggio_2.set_entrate_finite();
    /*parcheggio_1.set_finite_auto_che_entrano(); //Mi serve perchè va in deadlock perchè una thread non fa più la signal sull'altra
    while(parcheggio_1.get_finite_auto_che_escono() == false)
        parcheggio_1.signal_su_uscite_rimaste();*/
}

void gestione_uscite_P2(Date fine_simulaz){
    // open a file in read mode. APERTURA ESEGUITA IN CONCORRENZA
    ifstream infile;
    infile.open("../../input_files/parcheggioDueUscita.txt");
   	
    if (!infile.is_open()) {
        cout << "error opening the input file\n";
        exit(EXIT_FAILURE);
    }
    
    string line;
    while (getline(infile, line)){
        istringstream iss(line);
        int yy, mm, dd, hh, minmin;
        string t;
        if (!(iss >> t >> yy >> mm >> dd >> hh >> minmin)) { break; } // error
        //adesso ha spacchettato le informazioni dell'auto
        Date d_usc{yy, mm, dd, hh, minmin};
        if(d_usc.is_dopo(fine_simulaz))
            break;
        Auto car{t, d_usc};
        //inizio della sezione critica
        //parcheggio_1.aggiorna_prossima_uscita(d_usc);
        parcheggio_2.fai_uscire_auto(car);
        semaphore.lock(); //Per mutua esclusione tra parcheggio_1 e parcheggio_2 nell'uso del cout 
        cout << car.get_data_ingresso() << ' ' << car.get_targa() << ' ' << "OUT " << "PARK2" << endl;
        semaphore.unlock();
    }
    parcheggio_2.set_uscite_finite();
    /*parcheggio_1.set_finite_auto_che_escono();
    while(parcheggio_1.get_finite_auto_che_entrano() == false)
        parcheggio_1.signal_su_entrate_rimaste();*/
}



int main(){
    cout << "Inizio main. Creazione delle thread" << endl;
    Date data_fine_simulazione{2020,1,1,0,0};
    //creo le thread
    thread entrata_auto_in_park_1(gestione_accessi_P1,data_fine_simulazione);
    thread uscita_auto_in_park_1(gestione_uscite_P1,data_fine_simulazione);
    thread entrata_auto_in_park_2(gestione_accessi_P2,data_fine_simulazione);
    thread uscita_auto_in_park_2(gestione_uscite_P2,data_fine_simulazione);
    //il main attende che finiscano le thread
    entrata_auto_in_park_1.join();
    uscita_auto_in_park_1.join();
    entrata_auto_in_park_2.join();
    uscita_auto_in_park_2.join();
    //stampo la lista delle auto
    parcheggio_1.print_lista_auto();
    parcheggio_2.print_lista_auto();

    return 0;
}