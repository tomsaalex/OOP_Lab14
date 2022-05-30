#include "TestNotificationList.h"
#include "NotificationList.h"
#include <assert.h>

void testAdaugaApartament()
{
	NotificationList notifList;
	Locatar loc = Locatar(1, "Ion", "Space Station", 200);
	Locatar loc2 = Locatar(2, "Ion2", "Space Station2", 300);

	assert(notifList.getSize() == 0);
	
	notifList.adaugaApartament(loc);
	assert(notifList.getSize() == 1);
	
	try {
		notifList.adaugaApartament(loc); assert(false);}
	catch (RepositoryException re)
	{
		assert(re.getMessage() == "Apartamentul este deja pe lista de notificari.\n");
	}

	notifList.adaugaApartament(loc2);
	assert(notifList.getSize() == 2);
}

void testEmptyList()
{
	NotificationList notifList;
	Locatar loc = Locatar(1, "Ion", "Space Station", 200);
	Locatar loc2 = Locatar(2, "Ion2", "Space Station2", 300);
	Locatar loc3 = Locatar(3, "Ion3", "Space Station2", 300);
	Locatar loc4 = Locatar(4, "Ion4", "Space Station2", 300);
	Locatar loc5 = Locatar(5, "Ion5", "Space Station2", 300);

	notifList.adaugaApartament(loc);
	notifList.adaugaApartament(loc2);
	notifList.adaugaApartament(loc3);
	notifList.adaugaApartament(loc4);
	notifList.adaugaApartament(loc5);

	assert(notifList.getSize() == 5);

	notifList.emptyList();

	assert(notifList.getSize() == 0);
}

void testAddRandomApartments()
{
	NotificationList notifList;
	vector<Locatar> allApartments;

	Locatar loc = Locatar(1, "Ion", "Space Station", 200);
	Locatar loc2 = Locatar(2, "Ion2", "Space Station2", 300);
	Locatar loc3 = Locatar(3, "Ion3", "Space Station2", 300);
	Locatar loc4 = Locatar(4, "Ion4", "Space Station2", 300);
	Locatar loc5 = Locatar(5, "Ion5", "Space Station2", 300);

	allApartments.push_back(loc);
	allApartments.push_back(loc2);
	allApartments.push_back(loc3);
	allApartments.push_back(loc4);
	allApartments.push_back(loc5);

	notifList.addRandomApartments(allApartments, 3);

	assert(notifList.getSize() == 3);

	vector<Locatar> extractedList = notifList.getAllApartments();

	assert(std::count(allApartments.begin(), allApartments.end(), extractedList.at(0)) == 1);
	assert(std::count(allApartments.begin(), allApartments.end(), extractedList.at(1)) == 1);
	assert(std::count(allApartments.begin(), allApartments.end(), extractedList.at(2)) == 1);
}

void testWriteAllToFile()
{
	NotificationList notifList;

	Locatar loc = Locatar(1, "Ion", "Space Station", 200);
	Locatar loc2 = Locatar(2, "Ion2", "Space Station2", 300);
	Locatar loc3 = Locatar(3, "Ion3", "Space Station3", 300);
	
	notifList.adaugaApartament(loc);
	notifList.adaugaApartament(loc2);
	notifList.adaugaApartament(loc3);

	notifList.writeAllToFile("testWriteAllToFile.csv");

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


void runAllNotificationListTests()
{
	testAdaugaApartament();
	testEmptyList();
	testAddRandomApartments();
	testWriteAllToFile();
}