#include "TestsService.h"
#include "ServiceLocatari.h"
#include <assert.h>
#include "Exception.h"
#include "Utils.h"
#include <unordered_map>

#include <iostream>
using namespace std;
void testServiceAdauga()
{
	RepositoryLocatar repoLocatar;
	LocatarValidator locatarVal;
	NotificationList notifList;
	ServiceLocatar srv_locatar{ repoLocatar, notifList, locatarVal };
	assert(srv_locatar.getLength() == 0);
	srv_locatar.ServiceAdauga(1, "Vasile Vasilescu", "Hotel", 100);
	assert(srv_locatar.getLength() == 1);

	try { srv_locatar.ServiceAdauga(1, "Vasile Vasilescu", "Hotel", 100); assert(false); }
	catch (RepositoryException re) { assert(re.getMessage() == "Element duplicat\n"); }

	try { srv_locatar.ServiceAdauga(-1, "Vasile Vasilescu", "Hotel", 100); assert(false); }
	catch (ValidationException ve) { assert(ve.getMessage() == "Numar apartament invalid\n"); }
	try { srv_locatar.ServiceAdauga(1, "", "Hotel", 100); assert(false); }
	catch (ValidationException ve) { assert(ve.getMessage() == "Nume proprietar invalid\n"); }

	try { srv_locatar.ServiceAdauga(1, "validNume", "", 100); assert(false); }
	catch (ValidationException ve) { assert(ve.getMessage() == "Tip apartament invalid\n"); }

	try { srv_locatar.ServiceAdauga(1, "validNume", "validTip", -1); assert(false); }
	catch (ValidationException ve) { assert(ve.getMessage() == "Suprafata invalida\n"); }
}

void testServiceRemove()
{
	RepositoryLocatar repoLocatar;
	LocatarValidator locatarVal;
	NotificationList notifList;
	ServiceLocatar srvLocatar{ repoLocatar, notifList, locatarVal };
	srvLocatar.ServiceAdauga(1, "Ion Ionescu", "Vila", 200);
	srvLocatar.ServiceAdauga(2, "Ion Ionescu2", "Vila2", 300);
	srvLocatar.ServiceAdauga(3, "Ion Ionescu3", "Vila3", 400);

	assert(srvLocatar.getLength() == 3);

	srvLocatar.ServiceRemove(1);
	assert(srvLocatar.getLength() == 2);

	srvLocatar.ServiceRemove(2);
	assert(srvLocatar.getLength() == 1);

	srvLocatar.ServiceRemove(3);
	assert(srvLocatar.getLength() == 0);

	try { srvLocatar.ServiceRemove(1); assert(false); }
	catch (RepositoryException re) {
		assert(re.getMessage() == "Element inexistent\n");
	}
}


void testServiceEdit()
{
	RepositoryLocatar repoLocatar;
	LocatarValidator locatarVal;
	NotificationList notifList;
	ServiceLocatar srv_locatar{ repoLocatar, notifList, locatarVal };


	srv_locatar.ServiceAdauga(1, "Vasile Vasilescu", "Hotel", 100);
	vector<Locatar> fullExtraction = srv_locatar.getAll();
	assert(fullExtraction.at(0).getNumeProprietar() == "Vasile Vasilescu");

	srv_locatar.ServiceEdit(1, "Ion Ionescu", "Acoperis", 340);


	fullExtraction = srv_locatar.getAll();

	assert(fullExtraction.at(0).getNumeProprietar() == "Ion Ionescu");
	assert(fullExtraction.at(0).getTipApartament() == "Acoperis");
	assert(fullExtraction.at(0).getSuprafata() == 340);
}

void testGetAllService()
{
	RepositoryLocatar repoLocatari;
	LocatarValidator locatarVal;
	NotificationList notifList;
	ServiceLocatar srvLocatari{ repoLocatari, notifList, locatarVal };
	srvLocatari.ServiceAdauga(1, "ap", "tip", 20);
	srvLocatari.ServiceAdauga(2, "ap2", "tip2", 40);

	Locatar lt = Locatar(1, "ap", "tip", 20);
	Locatar lt2 = Locatar(2, "ap2", "tip2", 40);

	vector<Locatar> elems = srvLocatari.getAll();

	assert(elems.size() == 2);
	assert(elems.at(0) == lt);
	assert(elems.at(1) == lt2);
}

void testSearchService()
{
	RepositoryLocatar repoLocatar;
	LocatarValidator locatarVal;
	NotificationList notifList;
	ServiceLocatar srvLocatar{ repoLocatar, notifList, locatarVal };
	srvLocatar.ServiceAdauga(1, "Ion", "Condo", 200);

	assert(srvLocatar.search(1) == true);
	assert(srvLocatar.search(2) == false);
}

void testServiceFilter()
{
	RepositoryLocatar repoLocatar;
	LocatarValidator locatarValid;
	NotificationList notifList;
	ServiceLocatar srvLocatar{ repoLocatar, notifList, locatarValid };

	srvLocatar.ServiceAdauga(1, "Light", "Condo", 100);
	srvLocatar.ServiceAdauga(2, "Edward", "Condo", 160);
	srvLocatar.ServiceAdauga(3, "Dante", "Cocioaba", 200);
	srvLocatar.ServiceAdauga(4, "Lelouch", "Homeless", 300);

	vector<Locatar> filtered1 = srvLocatar.ServiceFilter("suprafata", "", 150, 250);
	assert(filtered1.size() == 2);
	assert(filtered1.at(0).getApartament() == 2);
	assert(filtered1.at(1).getApartament() == 3);

	vector<Locatar> filtered2 = srvLocatar.ServiceFilter("suprafata", "", 310, 310);
	assert(filtered2.size() == 0);

	vector<Locatar> filtered3 = srvLocatar.ServiceFilter("tip apartament", "Condo", -1, -1);
	assert(filtered3.size() == 2);
	assert(filtered3.at(0).getApartament() == 1);
	assert(filtered3.at(1).getApartament() == 2);

	vector<Locatar> filtered4 = srvLocatar.ServiceFilter("tip apartament", "Homeless", -1, -1);
	assert(filtered4.size() == 1);
	assert(filtered4.at(0).getApartament() == 4);
}

void testServiceSort()
{
	RepositoryLocatar repoLocatar;
	LocatarValidator locatarValid;
	NotificationList notifList;
	ServiceLocatar srvLocatar{ repoLocatar, notifList, locatarValid };

	srvLocatar.ServiceAdauga(1, "Light", "Condo", 100);
	srvLocatar.ServiceAdauga(2, "Edward", "Condo", 160);
	srvLocatar.ServiceAdauga(3, "Dante", "Cocioaba", 200);
	srvLocatar.ServiceAdauga(4, "Lelouch", "Homeless", 300);

	//Sortare dupa nume proprietar

	vector<Locatar> sorted3 = srvLocatar.ServiceSort(false, 1);
	assert(sorted3.size() == 4);
	assert(sorted3.at(0).getNumeProprietar() == "Dante");
	assert(sorted3.at(1).getNumeProprietar() == "Edward");
	assert(sorted3.at(2).getNumeProprietar() == "Lelouch");
	assert(sorted3.at(3).getNumeProprietar() == "Light");


	vector<Locatar> sorted4 = srvLocatar.ServiceSort(true, 1);
	assert(sorted4.size() == 4);
	assert(sorted4.at(0).getNumeProprietar() == "Light");
	assert(sorted4.at(1).getNumeProprietar() == "Lelouch");
	assert(sorted4.at(2).getNumeProprietar() == "Edward");
	assert(sorted4.at(3).getNumeProprietar() == "Dante");

	//Sortare dupa suprafata

	vector<Locatar> sorted1 = srvLocatar.ServiceSort(false, 2);
	assert(sorted1.size() == 4);
	assert(sorted1.at(0).getApartament() == 1);
	assert(sorted1.at(1).getApartament() == 2);
	assert(sorted1.at(2).getApartament() == 3);
	assert(sorted1.at(3).getApartament() == 4);

	vector<Locatar> sorted2 = srvLocatar.ServiceSort(true, 2);
	assert(sorted2.size() == 4);
	assert(sorted2.at(0).getApartament() == 4);
	assert(sorted2.at(1).getApartament() == 3);
	assert(sorted2.at(2).getApartament() == 2);
	assert(sorted2.at(3).getApartament() == 1);

	//Sortare dupa tip apartament + suprafata

	vector<Locatar> sorted5 = srvLocatar.ServiceSort(false, 3);
	assert(sorted5.size() == 4);
	assert(sorted5.at(0).getTipApartament() == "Cocioaba");
	assert(sorted5.at(1).getTipApartament() == "Condo");
	assert(sorted5.at(1).getSuprafata() == 100);
	assert(sorted5.at(2).getTipApartament() == "Condo");
	assert(sorted5.at(2).getSuprafata() == 160);
	assert(sorted5.at(3).getTipApartament() == "Homeless");

	vector<Locatar> sorted6 = srvLocatar.ServiceSort(true, 3);
	assert(sorted6.size() == 4);
	assert(sorted6.at(0).getTipApartament() == "Homeless");
	assert(sorted6.at(1).getTipApartament() == "Condo");
	assert(sorted6.at(1).getSuprafata() == 160);
	assert(sorted6.at(2).getTipApartament() == "Condo");
	assert(sorted6.at(2).getSuprafata() == 100);
	assert(sorted6.at(3).getTipApartament() == "Cocioaba");
}

void testAddToNotifList()
{
	RepositoryLocatar repoLocatar;
	LocatarValidator locatarValid;
	NotificationList notifList;
	ServiceLocatar srvLocatar{ repoLocatar, notifList, locatarValid };

	srvLocatar.ServiceAdauga(1, "Ion", "Condo", 100);
	srvLocatar.ServiceAdauga(2, "Ion2", "Condo2", 200);
	srvLocatar.ServiceAdauga(3, "Ion3", "Condo3", 300);
	srvLocatar.ServiceAdauga(4, "Ion4", "Condo4", 400);
	srvLocatar.ServiceAdauga(5, "Ion5", "Condo5", 500);

	srvLocatar.addToNotifList(1);
	try { srvLocatar.addToNotifList(1); assert(false); }
	catch (RepositoryException re)
	{
		assert(re.getMessage() == "Apartamentul este deja pe lista de notificari.\n");
	}

	srvLocatar.addToNotifList(2);
	srvLocatar.addToNotifList(3);
	srvLocatar.addToNotifList(4);
	srvLocatar.addToNotifList(5);
	assert(srvLocatar.getAllNotifList().size() == 5);
}

void testAddClearNotifList()
{
	RepositoryLocatar repoLocatar;
	LocatarValidator locatarValid;
	NotificationList notifList;
	ServiceLocatar srvLocatar{ repoLocatar, notifList, locatarValid };

	srvLocatar.ServiceAdauga(1, "Ion", "Condo", 100);
	srvLocatar.ServiceAdauga(2, "Ion2", "Condo2", 200);
	srvLocatar.ServiceAdauga(3, "Ion3", "Condo3", 300);
	srvLocatar.ServiceAdauga(4, "Ion4", "Condo4", 400);
	srvLocatar.ServiceAdauga(5, "Ion5", "Condo5", 500);

	srvLocatar.addToNotifList(1);
	srvLocatar.addToNotifList(2);
	srvLocatar.addToNotifList(3);
	srvLocatar.addToNotifList(4);
	srvLocatar.addToNotifList(5);

	assert(srvLocatar.getAllNotifList().size() == 5);
	srvLocatar.clearNotifList();

	assert(srvLocatar.getAllNotifList().size() == 0);
}

void testGenerateRandomNotifList()
{
	RepositoryLocatar repoLocatar;
	LocatarValidator locatarValid;
	NotificationList notifList;
	ServiceLocatar srvLocatar{ repoLocatar, notifList, locatarValid };

	srvLocatar.ServiceAdauga(1, "Ion", "Condo", 100);
	srvLocatar.ServiceAdauga(2, "Ion2", "Condo2", 200);
	srvLocatar.ServiceAdauga(3, "Ion3", "Condo3", 300);
	srvLocatar.ServiceAdauga(4, "Ion4", "Condo4", 400);
	srvLocatar.ServiceAdauga(5, "Ion5", "Condo5", 500);

	srvLocatar.generateRandomNotifList(3);

	vector<Locatar> completeList = srvLocatar.getAll();
	vector<Locatar> extractedList = srvLocatar.getAllNotifList();

	assert(extractedList.size() == 3);
	assert(std::count(completeList.begin(), completeList.end(), extractedList.at(0)) == 1);
	assert(std::count(completeList.begin(), completeList.end(), extractedList.at(1)) == 1);
	assert(std::count(completeList.begin(), completeList.end(), extractedList.at(2)) == 1);
}

void testServiceUndo()
{
	RepositoryLocatar repoLocatar;
	LocatarValidator locatarValid;
	NotificationList notifList;
	ServiceLocatar srvLocatar{ repoLocatar, notifList, locatarValid };

	srvLocatar.ServiceAdauga(1, "Ion", "Condo", 100);
	srvLocatar.ServiceAdauga(2, "Ion2", "Condo2", 200);
	srvLocatar.ServiceAdauga(3, "Ion3", "Condo3", 300);
	srvLocatar.ServiceAdauga(4, "Ion4", "Condo4", 400);
	srvLocatar.ServiceAdauga(5, "Ion5", "Condo5", 500);

	assert(srvLocatar.getLength() == 5);

	assert(srvLocatar.search(5) == true);
	srvLocatar.ServiceUndo();
	assert(srvLocatar.search(5) == false);
	assert(srvLocatar.getLength() == 4);

	assert(srvLocatar.search(3) == true);
	srvLocatar.ServiceRemove(3);
	assert(srvLocatar.search(3) == false);
	assert(srvLocatar.getLength() == 3);

	assert(repoLocatar.getLocatar(2).getNumeProprietar() == "Ion2");
	srvLocatar.ServiceEdit(2, "Connor", "Suite", 420);
	assert(repoLocatar.getLocatar(2).getNumeProprietar() == "Connor");
	srvLocatar.ServiceUndo();
	assert(repoLocatar.getLocatar(2).getNumeProprietar() == "Ion2");

	srvLocatar.ServiceUndo();
	assert(srvLocatar.getLength() == 4);

	srvLocatar.ServiceUndo();
	srvLocatar.ServiceUndo();
	srvLocatar.ServiceUndo();
	srvLocatar.ServiceUndo();

	assert(srvLocatar.getLength() == 0);
}

void testGenerateStatistics()
{
	RepositoryLocatar repoLoc;
	LocatarValidator valLoc;
	NotificationList notifList;
	ServiceLocatar srvLoc{ repoLoc, notifList, valLoc };

	srvLoc.ServiceAdauga(1, "Ion Ionescu", "Condo", 500);
	srvLoc.ServiceAdauga(2, "Ion Ionescu", "Condo", 500);
	srvLoc.ServiceAdauga(3, "Ion Ionescu", "Condo", 500);
	srvLoc.ServiceAdauga(4, "Ion Ionescu", "Condo", 500);

	srvLoc.ServiceAdauga(5, "Titel", "Condo", 500);
	srvLoc.ServiceAdauga(6, "Titel", "Condo", 500);

	srvLoc.ServiceAdauga(7, "Mitica", "Condo", 500);

	std::unordered_map<std::string, int> statsMap = srvLoc.generateOwnershipStatistics();

	assert(statsMap.find("Ion Ionescu").operator*().second == 4);
	assert(statsMap.find("Titel").operator*().second == 2);
	assert(statsMap.find("Mitica").operator*().second == 1);
	assert(statsMap.find("Achtung, baby") == statsMap.end());
}

void testWriteToFile()
{
	NotificationList notifList;
	LocatarValidator validLoc;
	RepositoryLocatar repoLoc;
	ServiceLocatar srvLoc{repoLoc, notifList, validLoc};
	Locatar loc = Locatar(1, "Ion", "Space Station", 200);
	Locatar loc2 = Locatar(2, "Ion2", "Space Station2", 300);
	Locatar loc3 = Locatar(3, "Ion3", "Space Station3", 300);

	notifList.adaugaApartament(loc);
	notifList.adaugaApartament(loc2);
	notifList.adaugaApartament(loc3);

	srvLoc.writeNotifListToFile("testWriteAllToFile.csv");

	std::ifstream fin("testWriteAllToFile.csv");

	string line;
	getline(fin, line);
	assert(line == string("1,Ion,Space Station,200"));
	getline(fin, line);
	assert(line == string("2,Ion2,Space Station2,300"));
	getline(fin, line);
	assert(line == string("3,Ion3,Space Station3,300"));
	getline(fin, line);
	assert(line.size() == 0);
	assert(fin.eof());
}

void runAllServiceTests()
{
	testServiceAdauga();
	testServiceRemove();
	testServiceEdit();
	testGetAllService();
	testSearchService();
	testServiceFilter();
	testServiceSort();
	testServiceUndo();
	testGenerateStatistics();
	testWriteToFile();

	testAddToNotifList();
	testAddClearNotifList();
	testGenerateRandomNotifList();
}
