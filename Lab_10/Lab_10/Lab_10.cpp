#include "Lab_10.h"
#include <qlineedit.h>
#include <QtWidgets/QMessageBox>
#include <unordered_map>
#include <QCloseEvent>
#include "NotificationListCRUD.h"
#include <QGraphicsView>
#include <QMovie>


using namespace std;
void Lab_10GUI::initGUIComponents()
{
	//RegEx setup

	realNumberField = QRegularExpression("^[0-9][0-9.]*$");
	realNumberFieldValidator = new QRegularExpressionValidator(realNumberField);

	naturalNumberField = QRegularExpression("^[0-9]*$");
	naturalNumberFieldValidator = new QRegularExpressionValidator(naturalNumberField);


	//Setting up separate window.
	
	//notifListWindows = new NotificationsListWindow(srvLocatari);
	//notifListWindowReads = new NotificationsListReadOnlyWindow(srvLocatari);

	//Setting up the layout for the main window;
	mainLayout = new QHBoxLayout();
	setLayout(mainLayout);

	//Setting up the main widgets.
	leftWidget = new QWidget();
	rightWidget = new QWidget();
	dynamicButtonsWidget = new QWidget();

	//Setting up the layouts of the main widgets.
	leftVBox = new QVBoxLayout();
	rightBox = new QFormLayout();
	dynamicButtonsLayout = new QVBoxLayout();

	leftWidget->setLayout(leftVBox);
	rightWidget->setLayout(rightBox);
	dynamicButtonsWidget->setLayout(dynamicButtonsLayout);

	//Placing the main widgets on the main window;
	mainLayout->addWidget(leftWidget);
	mainLayout->addWidget(rightWidget);
	mainLayout->addWidget(dynamicButtonsWidget);
	
	//Initializing components for the left widget.
	locatariListTitleLabel = new QLabel("Lista tuturor apartamentelor:");
	//locatariGUIList = new QListWidget();
	locatariListView = new QListView();
	listModel = new CustomListModel(srvLocatari.getAll());

	sortingOptionsWidget = new QWidget();
	filteringOptionsWidget = new QWidget();
	
	reverseSortButton = new QCheckBox("Inverseaza sortarea");
	btnSortByName = new QPushButton("Sorteaza dupa nume");
	btnSortBySurface = new QPushButton("Sorteaza dupa suprafata");
	btnSortBy2Criteria = new QPushButton("Sorteaza dupa tip apartament si suprafata");


	filterList = new QPushButton("Filtreaza lista");
	filterNum1 = new QLineEdit();
	filterNum2 = new QLineEdit();
	filterText = new QLineEdit();
	filteringCombo = new QComboBox();
	filteringCombo->addItem("Filtru suprafata");
	filteringCombo->addItem("Filtru tip apartament");


	//Initializing the horizontal boxes for containing all the sorting and filtering buttons.
	sortingOptionsLayout = new QHBoxLayout();
	filteringOptionsLayout = new QHBoxLayout();

	sortingOptionsWidget->setLayout(sortingOptionsLayout);
	filteringOptionsWidget->setLayout(filteringOptionsLayout);

	//Filling out the left widget.

	leftVBox->addWidget(locatariListTitleLabel);
	leftVBox->addWidget(locatariListView);
	
	leftVBox->addWidget(sortingOptionsWidget);
	leftVBox->addWidget(filteringOptionsWidget);

	sortingOptionsLayout->addWidget(reverseSortButton);
	sortingOptionsLayout->addWidget(btnSortByName);
	sortingOptionsLayout->addWidget(btnSortBySurface);
	sortingOptionsLayout->addWidget(btnSortBy2Criteria);

	filteringOptionsLayout->addWidget(filteringCombo);
	filteringOptionsLayout->addWidget(filterNum1);
	filteringOptionsLayout->addWidget(filterNum2);
	filteringOptionsLayout->addWidget(filterText);
	filteringOptionsLayout->addWidget(filterList);

	filterNum1->setValidator(realNumberFieldValidator);
	filterNum2->setValidator(realNumberFieldValidator);



	//Hiding the QLineEdit that the user mustn't see at the start.
	filterText->hide();

	//Initializing components for the right widget

	operationButtonsLayout = new QHBoxLayout();

	txtApartament = new QLineEdit();
	txtNumeProprietar = new QLineEdit();
	txtTipApartament = new QLineEdit();
	txtSuprafata = new QLineEdit();

	txtSuprafata->setValidator(realNumberFieldValidator);
	txtApartament->setValidator(naturalNumberFieldValidator);

	btnAdaugaLocatar = new QPushButton("Adauga locatar");
	btnEditeazaLocatar = new QPushButton("Editeaza locatar");
	btnStergereLocatar = new QPushButton("Sterge locatar");
	btnUndo = new QPushButton("Undo");

	QLabel searchBoxLabel = QLabel("Nr apartament");
	searchBox = new QLineEdit();
	searchBox->setValidator(new QIntValidator());
	initSearchButton = new QPushButton("Cauta locatar");

	centeredButtonLayout = new QVBoxLayout();

	//Filling out the right widget.

	operationButtonsLayout->addWidget(btnAdaugaLocatar);
	operationButtonsLayout->addWidget(btnStergereLocatar);
	operationButtonsLayout->addWidget(btnEditeazaLocatar);
	operationButtonsLayout->addWidget(btnUndo);

	rightBox->addRow(new QLabel("Numar apartament"), txtApartament);
	rightBox->addRow(new QLabel("Nume proprietar"), txtNumeProprietar);
	rightBox->addRow(new QLabel("Tip apartament"), txtTipApartament);
	rightBox->addRow(new QLabel("Suprafata"), txtSuprafata);
	rightBox->addRow(operationButtonsLayout);

	rightBox->addRow(searchBox, initSearchButton);
	rightBox->addRow(centeredButtonLayout);


	//Initializing the button for the notification list window

	notifListDisplayButton = new QPushButton("Lista de notificari");
	centeredButtonLayout->addWidget(notifListDisplayButton);

	readNotifListDisplayButton = new QPushButton("Lista de notificari read-only");
	centeredButtonLayout->addWidget(readNotifListDisplayButton);

	cosGroupLayout = new QFormLayout();
	cosGroup = new QGroupBox();
	cosGroup->setTitle("Operatii pe cos");
	centeredButtonLayout->addWidget(cosGroup);
	cosGroup->setLayout(cosGroupLayout);

	clearNotifListButton = new QPushButton("Goleste lista de notificari");
	addToNotifListButton = new QPushButton("Notifica apartament");
	apartmentToNotify = new QLineEdit();
	generateRandomNotifList = new QPushButton("Generate random notification list");
	numberOfApartments = new QLineEdit();
	printNotifListToFile = new QPushButton("Print notifications list to file");
	printFilePathBox = new QLineEdit();

	cosGroupLayout->addRow(apartmentToNotify, addToNotifListButton);
	cosGroupLayout->addRow(numberOfApartments, generateRandomNotifList);
	cosGroupLayout->addRow(printFilePathBox, printNotifListToFile);

}

void Lab_10GUI::connectSignalSlots() {

	QObject::connect(btnSortByName, &QPushButton::clicked, [&]() {
		//reloadList(srvLocatari.ServiceSort(reverseSortButton->isChecked(), 1));
		listModel->setElements(srvLocatari.ServiceSort(reverseSortButton->isChecked(), 1));
	});

	QObject::connect(btnSortBySurface, &QPushButton::clicked, [&]() {
		//reloadList(srvLocatari.ServiceSort(reverseSortButton->isChecked(), 2));
		listModel->setElements(srvLocatari.ServiceSort(reverseSortButton->isChecked(), 2));
	});

	QObject::connect(btnSortBy2Criteria, &QPushButton::clicked, [&]() {
		//reloadList(srvLocatari.ServiceSort(reverseSortButton->isChecked(), 3));
		listModel->setElements(srvLocatari.ServiceSort(reverseSortButton->isChecked(), 3));
	});

	QObject::connect(notifListDisplayButton, &QPushButton::clicked, [&]() {
		auto notifListWindow = new NotificationsListWindow(srvLocatari);
		allOpenWindows.push_back(notifListWindow);
		notifListWindow->show();
	});

	QObject::connect(readNotifListDisplayButton, &QPushButton::clicked, [&]() {
		auto notifListWindowRead = new NotificationsListReadOnlyWindow(srvLocatari);
		allOpenWindows.push_back(notifListWindowRead);

		notifListWindowRead->show();
	});

	QObject::connect(initSearchButton, &QPushButton::clicked, this, &Lab_10GUI::SearchLocatar);

	QObject::connect(filteringCombo, &QComboBox::currentIndexChanged, [&]() {
		if (filteringCombo->currentIndex() == 0)
		{
			filterText->hide();
			filterText->setText("");
			
			filterNum1->setText("");
			filterNum2->setText("");
			filterNum1->show();
			filterNum2->show();
		}
		else if (filteringCombo->currentIndex() == 1)
		{
			filterNum1->hide();
			filterNum2->hide();
			filterNum1->setText("");
			filterNum2->setText("");

			filterText->setText("");
			filterText->show();
		}
	});

	QObject::connect(filterList, &QPushButton::clicked, [&]() {
		if (filteringCombo->currentIndex() == 0)
		{
			float lowerBound = 0;
			float upperBound = 0;
			try {
				lowerBound = stod(filterNum1->text().toStdString());
				upperBound = stod(filterNum2->text().toStdString());
			}
			catch (invalid_argument ia)
			{
				QMessageBox::warning(this, "InvalidArgumentException", "Una dintre marginile intervalului nu este un numar real valid");
				return;
			}
			//reloadList(srvLocatari.ServiceFilter("suprafata", "", lowerBound, upperBound));
			listModel->setElements(srvLocatari.ServiceFilter("suprafata", "", lowerBound, upperBound));
			
		}
		else if (filteringCombo->currentIndex() == 1)
		{
			//reloadList(srvLocatari.ServiceFilter("tip apartament", filterText->text().toStdString(), 0, 0));
			listModel->setElements(srvLocatari.ServiceFilter("tip apartament", filterText->text().toStdString(), 0, 0));
		}
	});

	QObject::connect(btnAdaugaLocatar, &QPushButton::clicked, this, &Lab_10GUI::addNewLocatar);
	QObject::connect(btnEditeazaLocatar, &QPushButton::clicked, this, &Lab_10GUI::editLocatar);
	QObject::connect(btnStergereLocatar, &QPushButton::clicked, this, &Lab_10GUI::stergeLocatar);
	QObject::connect(btnUndo, &QPushButton::clicked, this, &Lab_10GUI::undoChanges);

	QObject::connect(locatariListView->selectionModel(), &QItemSelectionModel::selectionChanged, [&]() {
		auto selected = locatariListView->selectionModel()->selectedIndexes();
		if (selected.empty())
		{
			txtApartament->setText("");
			txtNumeProprietar->setText("");
			txtTipApartament->setText("");
			txtSuprafata->setText("");
		}
		else
		{
			auto selectedItem = selected.at(0);
			auto apartament = selectedItem.data(Qt::UserRole).toString();
			auto numeProprietar = QString::fromStdString(srvLocatari.getLocatar(apartament.toInt()).getNumeProprietar());
			auto tipApartament = QString::fromStdString(srvLocatari.getLocatar(apartament.toInt()).getTipApartament());
			auto suprafata = QString::number(srvLocatari.getLocatar(apartament.toInt()).getSuprafata());
			txtApartament->setText(apartament);
			txtNumeProprietar->setText(numeProprietar);
			txtSuprafata->setText(suprafata);
			txtTipApartament->setText(tipApartament);
		}
	});

	/*QObject::connect(listModel->, &QListWidget::itemSelectionChanged, [&]() {
		auto selected = locatariGUIList->selectedItems();
		if (selected.isEmpty())
		{
			txtApartament->setText("");
			txtNumeProprietar->setText("");
			txtTipApartament->setText("");
			txtSuprafata->setText("");
		}
		else
		{
			auto selectedItem = selected.at(0);
			auto apartament = selectedItem->data(Qt::UserRole).toString();
			auto numeProprietar = QString::fromStdString(srvLocatari.getLocatar(apartament.toInt()).getNumeProprietar());
			auto tipApartament = QString::fromStdString(srvLocatari.getLocatar(apartament.toInt()).getTipApartament());
			auto suprafata = QString::number(srvLocatari.getLocatar(apartament.toInt()).getSuprafata());
			txtApartament->setText(apartament);
			txtNumeProprietar->setText(numeProprietar);
			txtSuprafata->setText(suprafata);
			txtTipApartament->setText(tipApartament);
		}
	});*/


	QObject::connect(addToNotifListButton, &QPushButton::clicked, this, &Lab_10GUI::NotifyApartment);
	QObject::connect(clearNotifListButton, &QPushButton::clicked, this, &Lab_10GUI::ClearNotifList);
	QObject::connect(generateRandomNotifList, &QPushButton::clicked, this, &Lab_10GUI::GenerateRandomNotifList);
	QObject::connect(printNotifListToFile, &QPushButton::clicked, this, &Lab_10GUI::PrintNotifListToFile);

}


void Lab_10GUI::addNewLocatar()
{
	try {
		this->srvLocatari.ServiceAdauga(txtApartament->text().toInt(), txtNumeProprietar->text().toStdString(), txtTipApartament->text().toStdString(), txtSuprafata->text().toFloat());
		//reloadList(srvLocatari.getAll());
		listModel->setElements(srvLocatari.getAll());
	}
	catch (ValidationException ve)
	{
		QMessageBox::warning(this, "ValidationException", QString::fromStdString(ve.getMessage()));
	}
	catch (RepositoryException re)
	{
		QMessageBox::warning(this, "RepositoryException", QString::fromStdString(re.getMessage()));
	}
}

void Lab_10GUI::editLocatar()
{
	try {
		this->srvLocatari.ServiceEdit(txtApartament->text().toInt(), txtNumeProprietar->text().toStdString(), txtTipApartament->text().toStdString(), txtSuprafata->text().toFloat());
		listModel->setElements(srvLocatari.getAll());
		//reloadList(srvLocatari.getAll());
	}
	catch (ValidationException ve)
	{
		QMessageBox::warning(this, "ValidationException", QString::fromStdString(ve.getMessage()));
	}
	catch (RepositoryException re)
	{
		QMessageBox::warning(this, "RepositoryException", QString::fromStdString(re.getMessage()));
	}
}

void Lab_10GUI::stergeLocatar()
{
	try {
		this->srvLocatari.ServiceRemove(txtApartament->text().toInt());
		//reloadList(srvLocatari.getAll());
		listModel->setElements(srvLocatari.getAll());
	}
	catch (RepositoryException re)
	{
		QMessageBox::warning(this, "RepositoryException", QString::fromStdString(re.getMessage()));
	}
}

void Lab_10GUI::undoChanges()
{
	try {
		srvLocatari.ServiceUndo();
		//reloadList(srvLocatari.getAll());
		listModel->setElements(srvLocatari.getAll());
	}
	catch (ContainerException ce)
	{
		QMessageBox::warning(this, "ContainerException", QString::fromStdString(ce.getMessage()));
	}
}

/*void Lab_10GUI::reloadList(const std::vector<Locatar>& locatari)
{
	locatariGUIList->clear();
	for (const auto& loc : locatari)
	{
		string data = string("Ap. ") + std::to_string(loc.getApartament()) + string(" - ") + loc.getNumeProprietar();
		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(data));
		item->setData(Qt::UserRole, loc.getApartament());
		locatariGUIList->addItem(item);
	}
}
*/

void Lab_10GUI::addDynamicButtonsStartup(const std::vector<Locatar>& locatari)
{
	bool foundAMatch;
	for (auto& loc : locatari)
	{
		foundAMatch = false;
		string numeProp = loc.getNumeProprietar();
		for (auto& but : dynamicButtons)
		{
			if (but->text().toStdString() == numeProp)
			{
				//but->text() = but->text() + "\n" + QString::fromStdString(numeProp);
				foundAMatch = true;
			}
		}
		if (!foundAMatch)
		{
			QPushButton* dmcButton = new QPushButton(QString::fromStdString(numeProp));
			dynamicButtons.push_back(dmcButton);
			dynamicButtonsLayout->addWidget(dmcButton);
			QObject::connect(dmcButton, &QPushButton::clicked, [this, dmcButton]() {
				std::unordered_map<string, int> stats = srvLocatari.generateOwnershipStatistics();
				
				qDebug() <<  stats[dmcButton->text().toStdString()];
				string data = "Exista " + to_string( stats[dmcButton->text().toStdString()]) + string(" apartamente detinute de ") + dmcButton->text().toStdString();
				QMessageBox::information(this, "Button data", QString::fromStdString(data));
			});

		}
	}
}

void Lab_10GUI::SearchLocatar()
{
	bool ok;
	int locatarID = searchBox->text().toInt(&ok);

	if (ok == false)
	{
		QMessageBox::warning(this, "InvalidArgumentException", "Apartamentul dat este invalid");
		return;
	}
	
	Locatar loc;

	try {
		loc = srvLocatari.getLocatar(locatarID);
	}
	catch (RepositoryException re)
	{
		QMessageBox::warning(this, "RepositoryException", QString::fromStdString(re.getMessage()));
	}
	vector<Locatar> locatari;
	locatari.push_back(loc);

	listModel->setElements(locatari);
	//reloadList(locatari);
}

void Lab_10GUI::closeEvent(QCloseEvent* event)
{
	for (auto& wnd : allOpenWindows)
	{
		if(!wnd.isNull())
			wnd->close();
	}
	//notifListWindows->close();
	//notifListWindowReads->close();
}

void Lab_10GUI::tractor()
{
	QMovie* movie = new QMovie("tractor.gif");
	QSize size = QSize(200, 200);
	movie->setScaledSize(size);
	QLabel* processLabel = new QLabel(this);
	processLabel->setMovie(movie);
	centeredButtonLayout->addWidget(processLabel);
	movie->start();
}


void Lab_10GUI::NotifyApartment()
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
}
	 
void Lab_10GUI::ClearNotifList()
{
	this->srvLocatari.clearNotifList();
	//reloadList(srvLocatari.getAllNotifList());
}
	 
void Lab_10GUI::GenerateRandomNotifList()
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
}
	 
void Lab_10GUI::PrintNotifListToFile()
{
	try {
		this->srvLocatari.writeNotifListToFile(printFilePathBox->text().toStdString());
	}
	catch (ContainerException ce)
	{
		QMessageBox::warning(this, "ContainerException", QString::fromStdString(ce.getMessage()));
	}
}
