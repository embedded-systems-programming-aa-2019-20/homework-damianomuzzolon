//Auto.cpp

#include <ostream>
#include <string>
using std::string;
#include "Auto.h"
#include "Date.h"

//costruttori 
Auto::Auto(string t, Date d):targa{t}, data_ingresso{d}, is_entrata{true} {} //ipotesi: formato date corretto
Auto::Auto():targa{"00XXX00"}, data_ingresso{1900, 1, 1, 0, 0}, is_entrata{true}{}

