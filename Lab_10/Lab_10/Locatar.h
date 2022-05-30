#pragma once

#include <string>

using std::string;

class Locatar {
private:
	int apartament;
	string numeProprietar;
	string tipApartament;
	float suprafata;
public:
	Locatar() : apartament{ -1 }, numeProprietar{ "" }, tipApartament{ "" }, suprafata{ 0 }{}

	//Custom constructor for Locatar objects.
	Locatar(int apartamentParam, string numeProprietarParam, string tipApartamentParam, float suprafataParam) : apartament{ apartamentParam }, numeProprietar{ numeProprietarParam }, tipApartament{ tipApartamentParam }, suprafata{suprafataParam} {}
	
	// Copy constructor for Locatar objects.
	Locatar(const Locatar&);
	
	// Default destructor for Locatar objects.
	~Locatar() = default;

	// Default move constructor for Locatar objects.
	Locatar(Locatar&&) = default;

	// I'm actually not 100% sure what these 2 are....
	Locatar& operator=(const Locatar&) = default;
	Locatar& operator=(Locatar&&) = default;

	// Gives us a string representing the object.
	string locatarToString() const;
	
	// Gives us a string representing the object in CSV format.
	string locatarToCSV() const;

	// Defining the equality operator for Locatar type objects.
	bool operator ==(const Locatar&) const noexcept;

	//Getter for apartament field.
	int getApartament() const noexcept;
	
	//Getter for nume proprietar field.
	string getNumeProprietar() const;
	
	//Getter for nume proprietar field.
	string getTipApartament() const;
	
	// Getter for suprafata field
	float getSuprafata() const noexcept(true);
	
	//Setter for apartament field.
	void setApartament(const int& apartament) noexcept;

	//Setter for nume proprietar field.
	void setNumeProprietar(const string& numeProprietar);

	//Setter for tip apartament field.
	void setTipApartament(const string& tipApartament);

	//Setter for suprafata field.
	void setSuprafata(const float& suprafata) noexcept;
	
};
