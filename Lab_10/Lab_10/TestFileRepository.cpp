#include "TestFileRepository.h"
#include <assert.h>
#include "Exception.h"
#include <iostream>
#include <fstream>

void emptyTestFile(string path)
{
	std::ofstream fout(path);
	fout.close();
}

void testWriteToReadFromFile()
{
	try { FileRepositoryLocatari repoLoc = FileRepositoryLocatari("trololololoooooool.txt");	repoLoc.readAllFromFile(); }
	catch (ContainerException ce) {
		assert(ce.getMessage() == "Fisierul trololololoooooool.txt nu poate fi deschis.\n");
	}
	emptyTestFile("testFileRepoStorageEmpty.csv");
	FileRepositoryLocatari repoLocatar = FileRepositoryLocatari("testFileRepoStorageEmpty.csv");

	Locatar lt = Locatar(1, "Ion Ionescu", "Vila", 200);
	Locatar lt2 = Locatar(2, "Ion Ionescu2", "Vila2", 300);
	Locatar lt3 = Locatar(3, "Ion Ionescu3", "Vila3", 400);

	repoLocatar.adaugaLocatar(lt);
	repoLocatar.adaugaLocatar(lt2);
	repoLocatar.adaugaLocatar(lt3);

	FileRepositoryLocatari repoLocatar2 = FileRepositoryLocatari("testFileRepoStorageEmpty.csv");
	assert(repoLocatar2.getSize() == 3);


	FileRepositoryLocatari repoLocatar3 = FileRepositoryLocatari("testFileRepoStorageBlankLine.csv");
	assert(repoLocatar3.getSize() == 0);
}

void testFileRemoveLocatar()
{
	emptyTestFile("testFileRepoStorageEmpty.csv");
	FileRepositoryLocatari repoLocatar = FileRepositoryLocatari("testFileRepoStorageEmpty.csv");
	Locatar lt = Locatar(1, "Ion Ionescu", "Vila", 200);
	Locatar lt2 = Locatar(2, "Ion Ionescu2", "Vila2", 300);
	Locatar lt3 = Locatar(3, "Ion Ionescu3", "Vila3", 400);

	repoLocatar.adaugaLocatar(lt);
	repoLocatar.adaugaLocatar(lt2);
	repoLocatar.adaugaLocatar(lt3);

	assert(repoLocatar.getSize() == 3);

	repoLocatar.removeLocatar(1);
	assert(repoLocatar.getSize() == 2);

	repoLocatar.removeLocatar(2);
	assert(repoLocatar.getSize() == 1);

	repoLocatar.removeLocatar(3);
	assert(repoLocatar.getSize() == 0);

	try { repoLocatar.removeLocatar(1); assert(false); }
	catch (RepositoryException re) {
		assert(re.getMessage() == "Element inexistent\n");
	}
}

void testFileEditLocatar()
{
	emptyTestFile("testFileRepoStorageEmpty.csv");
	FileRepositoryLocatari repo = FileRepositoryLocatari("testFileRepoStorageEmpty.csv");
	Locatar lt = Locatar(1, "Ion", "Cocioaba", 200);

	repo.adaugaLocatar(lt);

	repo.editLocatar(1, "Titel", "Mansion", 450);
	vector<Locatar> extracted = repo.getAll();

	assert(extracted.at(0).getNumeProprietar() == "Titel");
	assert(extracted.at(0).getSuprafata() == 450);
	assert(extracted.at(0).getTipApartament() == "Mansion");


	FileRepositoryLocatari repo2 = FileRepositoryLocatari("testFileRepoStorageEmpty.csv");
	repo.editLocatar(1, "Titel2", "Mansion2", 470);


	vector<Locatar> extracted2 = repo.getAll();

	assert(extracted2.at(0).getNumeProprietar() == "Titel2");
	assert(extracted2.at(0).getSuprafata() == 470);
	assert(extracted2.at(0).getTipApartament() == "Mansion2");


	vector<Locatar> extracted3 = repo2.getAll();

	assert(extracted3.at(0).getNumeProprietar() == "Titel2");
	assert(extracted3.at(0).getSuprafata() == 470);
	assert(extracted3.at(0).getTipApartament() == "Mansion2");
}

void testFileAdaugaLocatar()
{
	emptyTestFile("testFileRepoStorageEmpty.csv");
	FileRepositoryLocatari repo = FileRepositoryLocatari("testFileRepoStorageEmpty.csv");
	Locatar lt = Locatar(1, "Ion", "Cocioaba", 200);
	assert(repo.getSize() == 0);
	repo.adaugaLocatar(lt);
	assert(repo.getSize() == 1);
	try { repo.adaugaLocatar(lt); assert(false); }
	catch (RepositoryException re)
	{
		assert(re.getMessage() == "Element duplicat\n");
	}

}

void testFileGetLocatar()
{
	emptyTestFile("testFileRepoStorageEmpty.csv");
	FileRepositoryLocatari repoLocatari = FileRepositoryLocatari("testFileRepoStorageEmpty.csv");
	Locatar lt = Locatar(1, "ap", "tip", 20);
	Locatar lt2 = Locatar(2, "ap2", "tip2", 40);

	repoLocatari.adaugaLocatar(lt);
	repoLocatari.adaugaLocatar(lt2);

	Locatar& gotElem = repoLocatari.getLocatar(1);
	assert(gotElem.getApartament() == 1);

	gotElem = repoLocatari.getLocatar(2);
	assert(gotElem.getApartament() == 2);

	try { gotElem = repoLocatari.getLocatar(3);	assert(false); }
	catch (RepositoryException re)
	{
		assert(re.getMessage() == "Element inexistent\n");
	}

}

void testFileGetAll()
{
	emptyTestFile("testFileRepoStorageEmpty.csv");
	FileRepositoryLocatari repoLocatari = FileRepositoryLocatari("testFileRepoStorageEmpty.csv");
	Locatar lt = Locatar(1, "ap", "tip", 20);
	Locatar lt2 = Locatar(2, "ap2", "tip2", 40);

	repoLocatari.adaugaLocatar(lt);
	repoLocatari.adaugaLocatar(lt2);

	vector<Locatar> elems = repoLocatari.getAll();

	assert(elems.size() == 2);
	assert(elems.at(0) == lt);
	assert(elems.at(1) == lt2);
}

void testFileSearchRepository()
{
	emptyTestFile("testFileRepoStorageEmpty.csv");
	FileRepositoryLocatari repoLocatar = FileRepositoryLocatari("testFileRepoStorageEmpty.csv");
	Locatar lt = Locatar(1, "Ion", "Condo", 200);
	Locatar lt2 = Locatar(2, "Maria", "Cocioaba", 500);
	repoLocatar.adaugaLocatar(lt);

	assert(repoLocatar.search(1) == true);
	assert(repoLocatar.search(2) == false);
}

void runAllFileRepoTests()
{
	testWriteToReadFromFile();
	testFileAdaugaLocatar();
	testFileEditLocatar();
	testFileRemoveLocatar();
	testFileGetLocatar();
	testFileGetAll();
	testFileSearchRepository();
}