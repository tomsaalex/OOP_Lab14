#include "Utils.h"
#include <iostream>

bool CompareLocatarsNumeCresc(const Locatar& a, const Locatar& b)
{
	return a.getNumeProprietar() < b.getNumeProprietar();
}

bool CompareLocatarsTypePlusSuprafataCresc(const Locatar& a, const Locatar& b)
{
	return (a.getTipApartament() < b.getTipApartament() || (a.getTipApartament() == b.getTipApartament() && a.getSuprafata() < b.getSuprafata()));
}

bool CompareLocatarsSuprafataCresc(const Locatar& a, const Locatar& b) noexcept
{
	return a.getSuprafata() < b.getSuprafata();
}

bool CompareLocatarsNumeDescresc(const Locatar& a, const Locatar& b)
{
	return a.getNumeProprietar() > b.getNumeProprietar();
}

bool CompareLocatarsTypePlusSuprafataDescresc(const Locatar& a, const Locatar& b)
{
	return a.getTipApartament() > b.getTipApartament() || (a.getTipApartament() == b.getTipApartament() && a.getSuprafata() > b.getSuprafata());

}

bool CompareLocatarsSuprafataDescresc(const Locatar& a, const Locatar& b) noexcept
{
	return a.getSuprafata() > b.getSuprafata();
}