#include "NotificationList.h"
#include <algorithm>
#include <random>
#include <fstream>

void NotificationList::adaugaApartament(const Locatar& apartament)
{
	for (auto& ap : elements)
		if (ap == apartament)
			throw RepositoryException("Apartamentul este deja pe lista de notificari.\n");

	elements.push_back(apartament);
	notify();
}
void NotificationList::emptyList() noexcept
{
	elements.clear();
	notify();
}


void NotificationList::addRandomApartments(vector<Locatar> allApartments, unsigned int count)
{
	std::shuffle(allApartments.begin(), allApartments.end(), std::default_random_engine(std::random_device{}()));

	while (this->elements.size() < count && allApartments.size() > 0)
	{
		this->elements.push_back(allApartments.back());
		allApartments.pop_back();
	}

	notify();
}

vector<Locatar> NotificationList::getAllApartments()
{
	return this->elements;
}

int NotificationList::getSize() const noexcept
{
	return this->elements.size();
}

void NotificationList::writeAllToFile(string path)
{
	std::ofstream fout(path);


	if (!fout.is_open()) throw ContainerException("Fisierul " + path + " nu poate fi deschis.\n");

	for (auto& loc : this->elements)
	{
		fout << loc.getApartament() << "," << loc.getNumeProprietar() << "," << loc.getTipApartament() << "," << loc.getSuprafata() << std::endl;
	}

	fout.close();
}
