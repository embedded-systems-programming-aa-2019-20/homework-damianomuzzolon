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

//costruttori
Park1::Park1(int cap):capienza{cap},prossima_entrata{1900, Date::Month::jan,1 ,0 ,0},prossima_uscita{1900, Date::Month::jan,1 ,0 ,0}, /*is_entrata_aggiornata{false}, is_uscita_aggiornata{false},*/ auto_presenti(cap) {}
Park1::Park1():capienza{0},prossima_entrata{1900, Date::Month::jan,1 ,0 ,0},prossima_uscita{1900, Date::Month::jan,1 ,0 ,0}, /*is_entrata_aggiornata{false}, is_uscita_aggiornata{false},*/ auto_presenti{1} {}
