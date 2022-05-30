#include "UI.h"
#include "TestsMain.h"
#include "Lab_10.h"
#include <QtWidgets/QApplication>

void startApp(int argc, char* argv[])
{
	LocatarValidator locatarVal;
	FileRepositoryLocatari repoLocatari = FileRepositoryLocatari("LocatariStore.csv");
	NotificationList notifList;
	ServiceLocatar srvLocatari{ repoLocatari, notifList, locatarVal };
	//UI console{ srvLocatari };
	//console.run();
	QApplication a(argc, argv);
	Lab_10GUI gui{ srvLocatari };
	gui.show();

	a.exec();
}

int main(int argc, char* argv[])
{
	testAll();
	startApp(argc, argv);

	return 0;
}
