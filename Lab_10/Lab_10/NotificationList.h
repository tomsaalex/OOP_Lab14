#pragma once
#include <vector>
#include "Locatar.h"
#include "Exception.h"
#include <fstream>
#include "Subject.h"

using std::vector;

class NotificationList: public Subject
{
private:
	vector<Locatar> elements;
public:
	NotificationList() noexcept: elements{} {}
	//NotificationList(const NotificationList& ot) :elements{ ot.elements } {}

	//Function that adds an apartment to the notification list.
	void adaugaApartament(const Locatar& apartament);

	//Function that empties the notification list.
	void emptyList() noexcept;

	//Function that adds random apartments to the notification list.
	void addRandomApartments(vector<Locatar> allApartments, unsigned int count) ;
	
	//Function that returns the length of the notification list.
	int getSize() const noexcept;

	//Writes the entire notification list content to the given file.
	void writeAllToFile(string path);

	//Function that returns an std vector of all the apartments in the notification list.
	vector<Locatar> getAllApartments();
};

