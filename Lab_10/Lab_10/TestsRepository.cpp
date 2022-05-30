#include "TestsRepository.h"
#include <assert.h>
#include "Exception.h"
#include <iostream>

void testRemoveLocatar()
{
	RepositoryLocatar repoLocatar;
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

	try { repoLocatar.removeLocatar(1);	assert(false); }
	catch (RepositoryException re) {
		assert(re.getMessage() == "Element inexistent\n");
	}
}

void testEditLocatar()
{
	RepositoryLocatar repo;
	Locatar lt = Locatar(1, "Ion", "Cocioaba", 200);

	repo.adaugaLocatar(lt);

	repo.editLocatar(1, "Titel", "Mansion", 450);
	vector<Locatar> extracted = repo.getAll();

	assert(extracted.at(0).getNumeProprietar() == "Titel");
	assert(extracted.at(0).getSuprafata() == 450);
	assert(extracted.at(0).getTipApartament() == "Mansion");
}

void testAdaugaLocatar()
{
	RepositoryLocatar repo;
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

void testGetLocatar()
{
	RepositoryLocatar repoLocatari;
	Locatar lt = Locatar(1, "ap", "tip", 20);
	Locatar lt2 = Locatar(2, "ap2", "tip2", 40);

	repoLocatari.adaugaLocatar(lt);
	repoLocatari.adaugaLocatar(lt2);

	Locatar& gotElem = repoLocatari.getLocatar(1);
	assert(gotElem.getApartament() == 1);

	gotElem = repoLocatari.getLocatar(2);
	assert(gotElem.getApartament() == 2);

	try { gotElem = repoLocatari.getLocatar(3); assert(false); }
	catch (RepositoryException re)
	{
		assert(re.getMessage() == "Element inexistent\n");
	}

}

void testGetAll()
{
	RepositoryLocatar repoLocatari;
	Locatar lt = Locatar(1, "ap", "tip", 20);
	Locatar lt2 = Locatar(2, "ap2", "tip2", 40);

	repoLocatari.adaugaLocatar(lt);
	repoLocatari.adaugaLocatar(lt2);

	vector<Locatar> elems = repoLocatari.getAll();

	assert(elems.size() == 2);
	assert(elems.at(0) == lt);
	assert(elems.at(1) == lt2);
}

void testSearchRepository()
{
	RepositoryLocatar repoLocatar;
	Locatar lt = Locatar(1, "Ion", "Condo", 200);
	Locatar lt2 = Locatar(2, "Maria", "Cocioaba", 500);
	repoLocatar.adaugaLocatar(lt);

	assert(repoLocatar.search(1) == true);
	assert(repoLocatar.search(2) == false);
}


void runAllRepoTests()
{
	testAdaugaLocatar();
	testEditLocatar();
	testRemoveLocatar();
	testGetLocatar();
	testGetAll();
	testSearchRepository();
}