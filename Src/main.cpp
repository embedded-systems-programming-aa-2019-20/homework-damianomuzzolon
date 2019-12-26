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
#include "Park.h"
#include "Auto.h"
#include "Date.h"


#define CAP1 3
#define CAP2 2

Park parcheggio_1(CAP1);
Park parcheggio_2(CAP2);
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
        
        //adesso ha spacchettato le informazioni dell'auto
        Date d_ingr{yy, mm, dd, hh, minmin};
        if(d_ingr.is_dopo(fine_simulaz))
            break;
        Auto car{t, d_ingr};

        //inizio della sezione critica
        parcheggio_1.fai_entrare_auto(car);
        semaphore.lock();              //blocco la risorsa condivisa dai due parcheggi
        if(car.get_is_entrata())
            cout << car.get_data_ingresso() << ' ' << car.get_targa() << ' ' << "IN " << "PARK1" << endl;
        else 
            cout << car.get_data_ingresso() << ' ' << car.get_targa() << ' ' << "Non entrata. Park1 pieno" << endl;
        semaphore.unlock();
    }
    parcheggio_1.set_entrate_finite();
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
        parcheggio_1.fai_uscire_auto(car);
        semaphore.lock(); //Per mutua esclusione tra parcheggio_1 e parcheggio_2 nell'uso del cout 
        cout << car.get_data_ingresso() << ' ' << car.get_targa() << ' ' << "OUT " << "PARK1" << endl;
        semaphore.unlock();
    }
    parcheggio_1.set_uscite_finite();
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
        
        //adesso ha spacchettato le informazioni dell'auto
        Date d_ingr{yy, mm, dd, hh, minmin};
        if(d_ingr.is_dopo(fine_simulaz))
            break;
        Auto car{t, d_ingr};

        //inizio della sezione critica
        parcheggio_2.fai_entrare_auto(car);
        semaphore.lock();
        if(car.get_is_entrata())
            cout << car.get_data_ingresso() << ' ' << car.get_targa() << ' ' << "IN " << "PARK2" << endl;
        else 
            cout << car.get_data_ingresso() << ' ' << car.get_targa() << ' ' << "Non entrata. Park2 pieno" << endl;
        semaphore.unlock();
    }
    parcheggio_2.set_entrate_finite();
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
        parcheggio_2.fai_uscire_auto(car);
        semaphore.lock(); //Per mutua esclusione tra parcheggio_1 e parcheggio_2 nell'uso del cout 
        cout << car.get_data_ingresso() << ' ' << car.get_targa() << ' ' << "OUT " << "PARK2" << endl;
        semaphore.unlock();
    }
    parcheggio_2.set_uscite_finite();
}



int main(){
    cout << "Inizio main. Creazione delle thread" << endl;
    
    Date data_fine_simulazione{2020,1,1,0,0};
    cout << "Verrà simulato il parcheggio fino alla data: AA MM GG HH MM " << data_fine_simulazione << endl;
    
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
    cout << endl << "Lista auto presenti nel PARCHEGGIO 1 alla fine dell'esecuzione:" << endl;
    parcheggio_1.print_lista_auto();
    cout << endl << "Lista auto presenti nel PARCHEGGIO 2 alla fine dell'esecuzione:" << endl;
    parcheggio_2.print_lista_auto();

    return 0;
}