#pragma once
#include "Locatar.h"
#include <vector>

using std::vector;

class RepositoryLocatar {
protected:
	vector<Locatar> elements;
public:
	RepositoryLocatar() noexcept : elements{} {}
	virtual ~RepositoryLocatar() = default;
	//Function for adding to a repo.
	virtual void adaugaLocatar(const Locatar&);

	//Function for removing from a repo.
	virtual void removeLocatar(const int&);

	//Function for editing a locatar from the repo.
	virtual void editLocatar(const int&, string numeProprietar, string tipApartament, float suprafata);

	//Function for getting a locatar from a repo.
	virtual Locatar& getLocatar(const int&);

	//Getter for repository size.
	virtual int getSize();

	//Function that returns all elements in the repo as a vector.
	virtual const vector<Locatar> getAll();

	//Function for checking if an element exists in the repo.
	virtual bool search(const int&);
};