#include "Validation.h"
#include "Exception.h"
#include <string>

bool LocatarValidator::isLocatarValid(const Locatar& lt) const {
	string errorMessage = "";
	if (lt.getApartament() < 1) errorMessage += "Numar apartament invalid\n";
	if (lt.getNumeProprietar().length() == 0) errorMessage += "Nume proprietar invalid\n";
	if (lt.getTipApartament().length() == 0) errorMessage += "Tip apartament invalid\n";
	if (lt.getSuprafata() <= 0) errorMessage += "Suprafata invalida\n";

	if(errorMessage.length() > 0)
		throw ValidationException(errorMessage);
	
	return true;
}