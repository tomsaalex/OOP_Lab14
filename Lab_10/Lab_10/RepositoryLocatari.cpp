#include "RepositoryLocatari.h"
#include "Exception.h"

void RepositoryLocatar::adaugaLocatar(const Locatar& lt)
{
	for (auto& currentElement : this->elements)
		if (lt == currentElement)
			throw RepositoryException("Element duplicat\n");

	this->elements.push_back(lt);
}

void RepositoryLocatar::removeLocatar(const int& apartament)
{
	vector<Locatar>::iterator iteratorToRemovable = find_if(this->elements.begin(), this->elements.end(), [apartament](Locatar l) noexcept {return l.getApartament() == apartament; });

	if (iteratorToRemovable != this->elements.end())
	{
		this->elements.erase(iteratorToRemovable);
		return;
	}

	throw RepositoryException("Element inexistent\n");}

//TODO I actually don't like doing it like this because the function feels bloated, 
//but I cannot move the actual editing out of the repo because then 
//it becomes impossible to keep track of it to sync the file.
void RepositoryLocatar::editLocatar(const int& apartament, string numeProprietar, string tipApartament, float suprafata)
{
	//Obtinem obiectul ce trebuie editat
	Locatar& locToEdit = this->getLocatar(apartament);

	//Facem editarea
	locToEdit.setNumeProprietar(numeProprietar);
	locToEdit.setTipApartament(tipApartament);
	locToEdit.setSuprafata(suprafata);
}

Locatar& RepositoryLocatar::getLocatar(const int& apartament)
{
	vector<Locatar>::iterator iteratorToLocated = find_if(this->elements.begin(), this->elements.end(), [apartament](Locatar l) noexcept {return l.getApartament() == apartament; });
	if (iteratorToLocated != this->elements.end())
	{
		//TODO Nu inteleg eroarea. * pe iterator returneaza elementul, nu?
		return (*iteratorToLocated);
	}
	throw RepositoryException("Element inexistent\n");}


int RepositoryLocatar::getSize()
{
	return this->elements.size();
}

bool RepositoryLocatar::search(const int& apartament)
{
	vector<Locatar>::const_iterator iteratorToLocated = find_if(this->elements.begin(), this->elements.end(), [apartament](Locatar l) noexcept {return l.getApartament() == apartament; });
	if (iteratorToLocated != this->elements.end())
	{
		return true;
	}
	return false;
}

const vector<Locatar> RepositoryLocatar::getAll()
{
	vector<Locatar> repoElements;
	for (auto& currentElement : this->elements)
	{
		repoElements.push_back(currentElement);
	}

	return repoElements;
}