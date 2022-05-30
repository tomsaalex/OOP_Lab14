#pragma once

#include "FileRepositoryLocatari.h"
#include "Validation.h"
#include "NotificationList.h"
#include "Undo.h"
#include <unordered_map>

using std::unique_ptr;

class ServiceLocatar {
private:
	//Not sure how this works considering you need a file repo, must investigate.
	RepositoryLocatar& repoLocatari;
	LocatarValidator& locatarValidator;
	NotificationList& notifList;
	vector<unique_ptr<ActiuneUndo>> undoList;
public:
	//Custom class constructor for ServiceLocatar objects.
	ServiceLocatar(RepositoryLocatar& repoParam, NotificationList& notificationList, LocatarValidator& locatarVal) noexcept : repoLocatari{ repoParam }, notifList{ notificationList }, locatarValidator{ locatarVal } {}

	//Function that manages adding elements to a service.
	void ServiceAdauga(const int& apartamentParam, const string& numeProprietarParam, const string& tipApartamentParam, const float& suprafataParam);
	
	//Function that manages removing elements from a service.
	void ServiceRemove(const int& apartament);

	//Function for editing a locatar from a service.
	void ServiceEdit(const int& apartament, string numeProprietar, string tipApartament, float suprafata);

	//Function that returns all elements in a service's repo as a vector.
	const vector<Locatar> getAll()  noexcept;

	//Function that returns all elements in a service's repo that match a given criterium.
	vector<Locatar> ServiceFilter(string criterium, string text_value, float real_criterium_lower, float real_criterium_upper);

	//Function that returns all the elements in a service's repo sorted based on a given criterium.
	vector<Locatar> ServiceSort(bool reversed, int criterium);

	void ServiceUndo();

	//Getter for service size.
	int getLength() noexcept;

	//Function for checking if an element is in the service's repository.
	bool search(const int& apartament);

	//Generates stats about the ownership of apartments in this building.
	std::unordered_map<std::string, int> generateOwnershipStatistics();

	//Adds apartment to notification list.
	void addToNotifList(int apartmentID);

	//Empties notification list.
	void clearNotifList() noexcept;

	//Creates a random notification list for testing purposes using existing apartments.
	void generateRandomNotifList(int apartmentCount);

	//Returns an std vector with all of the notified apartments in the list.
	vector<Locatar> getAllNotifList();

	//Returns the locatar from repoLocatari that has the corresponding apartment.
	Locatar getLocatar(int apartament);

	NotificationList& getNotifList() const;

	//Writes all the notified apartments to file.
	void writeNotifListToFile(string filePath);
};