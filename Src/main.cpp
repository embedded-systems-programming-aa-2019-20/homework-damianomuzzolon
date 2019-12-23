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
#include "Auto.h"
#include "Date.h"


#define CAP1 10

Park1 parcheggio_1(CAP1);

void gestione_accessi_P1(){
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
        Auto car{t, d_ingr};
        //inizio della sezione critica
        //parcheggio_1.aggiorna_prossima_entrata(d_ingr);
        parcheggio_1.fai_entrare_auto(car);
    }
    parcheggio_1.set_entrate_finite();
    /*parcheggio_1.set_finite_auto_che_entrano(); //Mi serve perchè va in deadlock perchè una thread non fa più la signal sull'altra
    while(parcheggio_1.get_finite_auto_che_escono() == false)
        parcheggio_1.signal_su_uscite_rimaste();*/
}

void gestione_uscite_P1(){
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
        Auto car{t, d_usc};
        //inizio della sezione critica
        //parcheggio_1.aggiorna_prossima_uscita(d_usc);
        parcheggio_1.fai_uscire_auto(car);
    }
    parcheggio_1.set_uscite_finite();
    /*parcheggio_1.set_finite_auto_che_escono();
    while(parcheggio_1.get_finite_auto_che_entrano() == false)
        parcheggio_1.signal_su_entrate_rimaste();*/
}


int main(){
    cout << "Inizio main. Creazione delle thread" << endl;
    //creo le thread
    thread entrata_auto_in_park_1{gestione_accessi_P1};
    thread uscita_auto_in_park_1{gestione_uscite_P1};
    //il main attende che finiscano le thread
    entrata_auto_in_park_1.join();
    uscita_auto_in_park_1.join();
    //stampo la lista delle auto
    parcheggio_1.print_lista_auto();
    
    return 0;
}