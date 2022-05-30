#include "Locatar.h"
#include <iomanip>
#include <sstream>
#include <iostream>

int Locatar::getApartament() const noexcept
{
	return this->apartament;
}

string Locatar::getNumeProprietar() const
{
	return this->numeProprietar;
}

string Locatar::getTipApartament() const
{
	return this->tipApartament;
}


float Locatar::getSuprafata() const noexcept(true)
{
	return this->suprafata;
}

void Locatar::setNumeProprietar(const string& numeProprietarParam)
{
	this->numeProprietar = numeProprietarParam;
}

void Locatar::setTipApartament(const string& tipApartamentParam)
{
	this->tipApartament = tipApartamentParam;
}

void Locatar::setSuprafata(const float& suprafataParam) noexcept
{
	this->suprafata = suprafataParam;
}

bool Locatar::operator ==(const Locatar& lt) const noexcept{
	return this->apartament == lt.apartament;
}

Locatar::Locatar(const Locatar& ot)
{
	this->apartament = ot.apartament;
	this->numeProprietar = ot.numeProprietar;
	this->tipApartament = ot.tipApartament;
	this->suprafata = ot.suprafata;
}


string Locatar::locatarToString() const
{
	std::stringstream stream;
	stream << std::fixed << std::setprecision(2) << this->suprafata;
	std::string suprafataString = stream.str();

	string stringLocatar = "Apartament: " + std::to_string(this->apartament) + ", Nume Locatar: " + this->numeProprietar + ", Tip apartament: " + this->tipApartament + ", Suprafata: " + suprafataString;
	return stringLocatar;
}

string Locatar::locatarToCSV() const
{
	std::stringstream stream;
	stream << std::fixed << std::setprecision(2) << this->suprafata;
	std::string suprafataString = stream.str();

	string stringLocatar = std::to_string(this->apartament) + "," + this->numeProprietar + "," + this->tipApartament + "," + suprafataString;
	return stringLocatar;
}