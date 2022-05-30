#include "FileRepositoryLocatari.h"
#include "Exception.h"
#include <iostream>

using namespace std;

void FileRepositoryLocatari::writeAllToFile()
{
	std::ofstream fout(this->filePath);
	
	if (!fout.is_open()) throw ContainerException("Fisierul " + this->filePath + " nu poate fi deschis.\n");

	for (auto& loc : this->elements)
	{
		fout << loc.locatarToCSV() << std::endl;
	}

	fout.close();
}

void FileRepositoryLocatari::readAllFromFile()
{
	std::ifstream fin(this->filePath);

	if (!fin.is_open()) throw ContainerException("Fisierul " + this->filePath + " nu poate fi deschis.\n");

	const string string_delimiter = ",";
	string line;

	this->elements.clear();

	while (getline(fin, line, '\n'))
	{
		if (line.empty())
			continue;

		string tokens[4];
		int pos = 0, i = 0;

		while((pos = line.find(string_delimiter)) != string::npos)
		{
			tokens[i++] = line.substr(0, pos);
			line.erase(0, pos + string_delimiter.length());
		}
		tokens[i] = line.substr(0, pos - 1);
		const int apartament = std::stoi(tokens[0]);
		const string numeProprietar = tokens[1];
		const string tipApartament = tokens[2];
		const float suprafata = std::stof(tokens[3]);

		const Locatar loc = Locatar(apartament, numeProprietar, tipApartament, suprafata);

		this->RepositoryLocatar::adaugaLocatar(loc);
	}

	fin.close();
}

void FileRepositoryLocatari::adaugaLocatar(const Locatar& loc)
{
	this->readAllFromFile();
	this->RepositoryLocatar::adaugaLocatar(loc);
	this->writeAllToFile();
}


void FileRepositoryLocatari::removeLocatar(const int& apartament)
{
	this->readAllFromFile();
	this->RepositoryLocatar::removeLocatar(apartament);
	this->writeAllToFile();
}

void FileRepositoryLocatari::editLocatar(const int& apartament, string numeProprietar, string tipApartament, float suprafata)
{
	this->readAllFromFile();
	this->RepositoryLocatar::editLocatar(apartament, numeProprietar, tipApartament, suprafata);
	this->writeAllToFile();
}

Locatar& FileRepositoryLocatari::getLocatar(const int& apartament)
{
	this->readAllFromFile();
	return this->RepositoryLocatar::getLocatar(apartament);
}

int FileRepositoryLocatari::getSize()
{
	this->readAllFromFile();
	return this->RepositoryLocatar::getSize();
}

const vector<Locatar> FileRepositoryLocatari::getAll()
{
	this->readAllFromFile();
	return this->RepositoryLocatar::getAll();
}

bool FileRepositoryLocatari::search(const int& apartament)
{
	this->readAllFromFile();
	return this->RepositoryLocatar::search(apartament);
}