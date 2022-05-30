#include "TestsDomain.h"
#include "Locatar.h"
#include <iostream>
#include <sstream>

void testCreateLocatar()
{
		Locatar lt = Locatar(1, "Ion Ionescu", "Condo", 20);

		assert(lt.getApartament() == 1);
		assert(lt.getNumeProprietar() == "Ion Ionescu");
		assert(lt.getTipApartament() == "Condo");
		assert(lt.getSuprafata() == 20);
}

void testLocatarToString()
{
	Locatar lt = Locatar(1, "Ion Ionescu", "Condo", 20);

	assert(lt.locatarToString() == "Apartament: 1, Nume Locatar: Ion Ionescu, Tip apartament: Condo, Suprafata: 20.00");
}

void runAllDomainTests()
{
	testCreateLocatar();
	testLocatarToString();
}