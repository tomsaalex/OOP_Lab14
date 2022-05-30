#include "ServiceLocatari.h"
#include "Utils.h"
#include <iterator>
#include <algorithm>
#include "Undo.h"

void ServiceLocatar::ServiceAdauga(const int& apartamentParam, const string& numeProprietarParam, const string& tipApartamentParam, const float& suprafataParam)
{
	//Creare locatar
	Locatar toAdd = Locatar(apartamentParam, numeProprietarParam, tipApartamentParam, suprafataParam);

	//Validare locatar
	this->locatarValidator.isLocatarValid(toAdd);

	//Inserare locatar
	this->repoLocatari.adaugaLocatar(toAdd);

	//Inserare pointer la ActiuneUndo in undoList
	this->undoList.push_back(std::make_unique<UndoAdauga>(this->repoLocatari, toAdd));
}

void ServiceLocatar::ServiceRemove(const int& apartament)
{
	Locatar toRemove = this->repoLocatari.getLocatar(apartament);
	this->repoLocatari.removeLocatar(apartament);

	//Inserare pointer la ActiuneUndo in undoList
	this->undoList.push_back(std::make_unique<UndoSterge>(this->repoLocatari, toRemove));
}

void ServiceLocatar::ServiceEdit(const int& apartament, string numeProprietar, string tipApartament, float suprafata)
{
	Locatar toModify = this->repoLocatari.getLocatar(apartament);
	this->repoLocatari.editLocatar(apartament, numeProprietar, tipApartament, suprafata);

	//Inserare pointer la ActiuneUndo in undoList
	this->undoList.push_back(std::make_unique<UndoModifica>(this->repoLocatari, toModify));
}

int ServiceLocatar::getLength() noexcept
{
	return this->repoLocatari.getSize();
}

const vector<Locatar> ServiceLocatar::getAll()  noexcept
{
	return this->repoLocatari.getAll();
}

vector<Locatar> ServiceLocatar::ServiceFilter(string criterium, string text_value, float real_criterium_lower, float real_criterium_upper)
{
	vector<Locatar> filteredRepo;
	vector<Locatar> fullRepo = this->repoLocatari.getAll();

	if (criterium == "suprafata")
	{
		copy_if(fullRepo.begin(), fullRepo.end(), std::back_inserter(filteredRepo), [real_criterium_lower, real_criterium_upper](Locatar& currentLocatar) noexcept{return currentLocatar.getSuprafata() <= real_criterium_upper && currentLocatar.getSuprafata() >= real_criterium_lower; });
	}
	else if (criterium == "tip apartament")
	{
		copy_if(fullRepo.begin(), fullRepo.end(), std::back_inserter(filteredRepo), [text_value](Locatar& currentLocatar) {return currentLocatar.getTipApartament() == text_value; });
	}

	return filteredRepo;
}

vector<Locatar> ServiceLocatar::ServiceSort(bool reversed, int criterium)
{
	vector<Locatar> repoList{ this->repoLocatari.getAll() };

	bool (*MaiMic)(const Locatar & a, const Locatar & b) = CompareLocatarsNumeCresc; // Nu conteaza ce functie dam aici. E doar ca sa nu se mai planga VS.
	if (reversed == false)
	{
		if (criterium == 1)
		{
			MaiMic = CompareLocatarsNumeCresc;
		}
		else if (criterium == 2)
		{
			MaiMic = CompareLocatarsSuprafataCresc;
		}
		else if (criterium == 3)
		{
			MaiMic = CompareLocatarsTypePlusSuprafataCresc;
		}
	}
	else
	{
		if (criterium == 1)
		{
			MaiMic = CompareLocatarsNumeDescresc;
		}
		else if (criterium == 2)
		{
			MaiMic = CompareLocatarsSuprafataDescresc;
		}
		else if (criterium == 3)
		{
			MaiMic = CompareLocatarsTypePlusSuprafataDescresc;
		}
	}

	sort(repoList.begin(), repoList.end(), MaiMic);
	return repoList;
}

void ServiceLocatar::ServiceUndo()
{
	if (this->undoList.size() < 1) throw ContainerException("Nu mai exista stari anterioare la care sa revenim.\n");
	
	this->undoList.back()->doUndo();
	this->undoList.pop_back();
}

bool ServiceLocatar::search(const int& apartament)
{
	return this->repoLocatari.search(apartament);
}

std::unordered_map<std::string, int> ServiceLocatar::generateOwnershipStatistics()
{
	std::unordered_map<std::string, int> statsMap;
	vector<Locatar> allLocatari = this->repoLocatari.getAll();

	for (auto& loc : allLocatari) 
	{
		if (statsMap.count(loc.getNumeProprietar()) == 0)
			statsMap.insert(std::make_pair(loc.getNumeProprietar(), 1));
		else
			statsMap.find(loc.getNumeProprietar()).operator*().second++;
	}

	return statsMap;
}

void ServiceLocatar::addToNotifList(int apartmentID)
{
	Locatar locToAdd = this->repoLocatari.getLocatar(apartmentID);
	this->notifList.adaugaApartament(locToAdd);
}

void ServiceLocatar::clearNotifList() noexcept
{
	this->notifList.emptyList();
}

void ServiceLocatar::generateRandomNotifList(int apartmentCount)
{
	notifList.addRandomApartments(this->repoLocatari.getAll(), apartmentCount);
}

vector<Locatar> ServiceLocatar::getAllNotifList()
{
	return this->notifList.getAllApartments();
}

Locatar ServiceLocatar::getLocatar(int apartament)
{
	return this->repoLocatari.getLocatar(apartament);
}

NotificationList& ServiceLocatar::getNotifList() const
{
	return notifList;
}

void ServiceLocatar::writeNotifListToFile(string filePath)
{
	this->notifList.writeAllToFile(filePath);
}