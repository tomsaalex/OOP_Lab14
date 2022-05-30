#pragma once
#include "RepositoryLocatari.h"
#include <fstream>

class FileRepositoryLocatari : public RepositoryLocatar
{
private:
	string filePath;
public:
	FileRepositoryLocatari(string file_path) : RepositoryLocatar(), filePath{ file_path } {}

	//Function that writes the content of the entire repository to the file.
	void writeAllToFile();

	//Function that populates the repo with the contents of a given file.
	void readAllFromFile();

	//Function that expands the addition functionality to work with files.
	void adaugaLocatar(const Locatar&) override;

	//Function that expands the removal functionality to work with files.
	void removeLocatar(const int&) override;

	//Function that expands the editing functionality to work with files.
	void editLocatar(const int&, string numeProprietar, string tipApartament, float suprafata) override;

	//Function that expands the getLocatar functionality to work with files.
	Locatar& getLocatar(const int&) override;

	//Function that expands the getSize functionality to work with files.
	int getSize() override; 

	//Function that expands the getAll functionality to work with files.
	const vector<Locatar> getAll() override; 

	//Function that expands the searching functionality to work with files.
	bool search(const int&) override;
};