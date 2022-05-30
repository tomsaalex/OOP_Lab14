#include "NotificationListCRUD.h"
#include <QLineEdit>
#include <QMessageBox>



void NotificationsListWindow::initGUIComponents()
{
	//Setting up the main widget.
	mainLayout = new QHBoxLayout();
	setLayout(mainLayout);
	setAttribute(Qt::WA_DeleteOnClose);

	//Setting up the secondary widget.

	leftLayout = new QVBoxLayout();
	rightLayout = new QVBoxLayout();

	leftWidget = new QWidget();
	rightWidget = new QWidget();

	mainLayout->addWidget(leftWidget);
	mainLayout->addWidget(rightWidget);

	leftWidget->setLayout(leftLayout);
	rightWidget->setLayout(rightLayout);

	//Filling out the left widget

	listLabel1 = new QLabel("Lista de notificari a cladirii.");
	//notifTable = new QTableWidget(0, 2);

	notifTableModel = new CustomTableModel(srvLocatari.getAllNotifList());
	notifTableView = new QTableView();
	

	leftLayout->addWidget(listLabel1);
	leftLayout->addWidget(notifTableView);

	//Filling out the right widget

	notifListForm = new QFormLayout();
	notifListFormWidget = new QWidget();
	notifListFormWidget->setLayout(notifListForm);
	rightLayout->addWidget(notifListFormWidget);

	clearNotifListButton = new QPushButton("Sterge lista de notificari");

	addToNotifListButton = new QPushButton("Notifica apartament");
	apartmentToNotify = new QLineEdit();
	apartmentToNotify->setValidator(new QIntValidator());

	generateRandomNotifList = new QPushButton("Generate Random List");
	numberOfApartments = new QLineEdit();
	numberOfApartments->setValidator(new QIntValidator());

	printNotifListToFile = new QPushButton("Printeaza in fisier lista de notificari");
	printFilePathBox = new QLineEdit();

	rightLayout->addWidget(clearNotifListButton);

	//notifListForm->addRow(apartmentToNotify, addToNotifListButton);
	notifListForm->addRow(numberOfApartments, generateRandomNotifList);
	//notifListForm->addRow(printFilePathBox, printNotifListToFile);
}

void NotificationsListWindow::connectSignalSlots()
{
	srvLocatari.getNotifList().attach(this);

	QObject::connect(addToNotifListButton, &QPushButton::clicked, this, &NotificationsListWindow::NotifyApartment);
	QObject::connect(clearNotifListButton, &QPushButton::clicked, this, &NotificationsListWindow::ClearNotifList);
	QObject::connect(generateRandomNotifList, &QPushButton::clicked, this, &NotificationsListWindow::GenerateRandomNotifList);
	QObject::connect(printNotifListToFile, &QPushButton::clicked, this, &NotificationsListWindow::PrintNotifListToFile);
}

/*void NotificationsListWindow::reloadList(vector<Locatar> locatari)
{
	notifTable->clear();
	notifTable->setRowCount(locatari.size());
	notifTable->setColumnCount(2);
	int i = 0;
	for (const auto& loc : locatari)
	{
		string data1 = std::to_string(loc.getApartament());
		string data2 = loc.getNumeProprietar();
		QTableWidgetItem* item = new QTableWidgetItem(QString::fromStdString(data1));
		QTableWidgetItem* item2 = new QTableWidgetItem(QString::fromStdString(data2));

		item->setData(Qt::UserRole, loc.getApartament());
		item2->setData(Qt::UserRole, loc.getApartament());
		//notifTable->setRowCount(notifTable->rowCount());

		//notifTable->insertRow(notifTable->rowCount());
		notifTable->setItem(i, 0, item);
		notifTable->setItem(i++, 1, item2);
	}
}
*/
void NotificationsListWindow::NotifyApartment()
{
	bool ok;
	int apartmentID = apartmentToNotify->text().toInt(&ok);
	if (ok == false)
	{
		QMessageBox::warning(this, "InvalidArgumentException", "Numarul de apartament dat este invalid");
		return;
	}
	try {
		srvLocatari.addToNotifList(apartmentID);
	}
	catch (RepositoryException re)
	{
		QMessageBox::warning(this, "RepositoryException", QString::fromStdString(re.getMessage()));
	}
	//reloadList(srvLocatari.getAllNotifList());
	notifTableModel->setElements(srvLocatari.getAllNotifList());
}

void NotificationsListWindow::ClearNotifList()
{
	this->srvLocatari.clearNotifList();
	//reloadList(srvLocatari.getAllNotifList());
	notifTableModel->setElements(srvLocatari.getAllNotifList());
}

void NotificationsListWindow::GenerateRandomNotifList()
{
	this->ClearNotifList();

	bool ok;
	int apCount = numberOfApartments->text().toInt(&ok);

	if (ok == false)
	{
		QMessageBox::warning(this, "InvalidArgumentException", "Numarul de apartamente dat este invalid");
		return;
	}

	this->srvLocatari.generateRandomNotifList(apCount);
	//reloadList(srvLocatari.getAllNotifList());
	notifTableModel->setElements(srvLocatari.getAllNotifList());
}

void NotificationsListWindow::PrintNotifListToFile()
{
	try {
		this->srvLocatari.writeNotifListToFile(printFilePathBox->text().toStdString());
	}
	catch (ContainerException ce)
	{
		QMessageBox::warning(this, "ContainerException", QString::fromStdString(ce.getMessage()));
	}
}