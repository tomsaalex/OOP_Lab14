#include "UI.h"
#include <iostream>
#include <string>
#include "Exception.h"
#include "Utils.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;

void UI::Print_Main_Menu() const
{
	cout << endl;
	cout << "----------------------------------------------------------------------------------\n";
	cout << "----------------------------------------------------------------------------------\n";
	cout << "Lista comenzi pentru management cladire:\n\n";
	cout << "add_loc - Aduaga un locatar nou in lista\n";
	cout << "rem_loc - Sterge un locatar din lista\n";
	cout << "print_all - Afiseaza intreaga lista de locatari\n";
	cout << "cauta_ap - Cauta un apartament in lista si afiseaza daca a fost gasit sau nu\n";
	cout << "edit_loc - Editeaza un apartament din repo.\n";
	cout << "exit - Inchide aplicatia\n";
	cout << "----------------------------------------------------------------------------------\n";
	cout << "Lista comenzi pentru management lista de notificare\n\n";
	cout << "notify_ap - Adauga un apartament deja existent in lista de notificare.\n";
	cout << "clear_notifications - Goleste liste de notificare.\n";
	cout << "gen_rnd_notif - Genereaza o lista de notifiare aleatoare.\n";
	cout << "print_notif - Afiseaza lista de apartamente notificate.\n";
	cout << "print_notif_to_file - Scrie intr-un fisier lista de apartamente notificate.\n";
	cout << "----------------------------------------------------------------------------------\n";
	cout << "----------------------------------------------------------------------------------\n";

	cout << endl;
}

void UI::Print_All_Locatari() const
{
	const vector<Locatar>& locatari = this->srv_locatar.getAll();

	if (locatari.size() == 0)
	{
		cout << "Lista de locatari este goala.\n\n";
		return;
	}

	cout << "Lista de locatari este urmatoarea: \n";
	for (const auto& l : locatari)
	{
		cout << l.locatarToString() << endl;
	}

	cout << '\n';
}

void UI::Add_Locatar()
{
	int apartament{ -1 };
	string apartamentString, suprafataString;
	string numeLocatar;
	string tipApartament;
	float suprafata{ -1 };


	while (true)
	{
		try
		{
			cout << "Introduceti numarul apartamentului: ";
			getline(cin, apartamentString);

			apartament = std::stoi(apartamentString);
			break;
		}
		catch (std::invalid_argument ia)
		{
			cout << "Nu se accepta decat valori numerice pentru apartament.\n\n";
		}
	}

	cout << "Introduceti numele locatarului: ";
	getline(cin, numeLocatar);
	cout << "Introduceti tipul apartamentului: ";
	getline(cin, tipApartament);

	while (true)
	{
		try
		{
			cout << "Introduceti suprafata apartamentului: ";
			getline(cin, suprafataString);
			suprafata = std::stof(suprafataString);
			break;
		}
		catch (std::invalid_argument ia)
		{
			cout << "Nu se accepta decat valori numerice pentru suprafata.\n\n";
		}
	}

	try {
		this->srv_locatar.ServiceAdauga(apartament, numeLocatar, tipApartament, suprafata);
		cout << "Adaugarea a fost realizata cu succes!\n\n";
	}
	catch (ValidationException ve)
	{
		cout << ve.getMessage() << "\n\n";
	}
	catch (RepositoryException re)
	{
		cout << re.getMessage() << "\n\n";
	}
}

void UI::Remove_Locatar()
{
	string apartamentString;
	int apartament{ -1 };


	while (true)
	{
		try
		{
			cout << "Introduceti numarul apartamentului pe care vreti sa il stergeti: ";
			getline(cin, apartamentString);

			apartament = std::stoi(apartamentString);
			break;
		}
		catch (std::invalid_argument ia)
		{
			cout << "Nu se accepta decat valori numerice pentru apartament.\n\n";
		}
	}

	try {
		this->srv_locatar.ServiceRemove(apartament);
		cout << "Eliminarea a fost realizata cu succes!\n\n";
	}
	catch (RepositoryException re)
	{
		cout << re.getMessage() << "\n\n";
	}

}

void UI::Edit_Locatar()
{
	int apartament{ -1 };
	string apartamentString, suprafataString;
	string numeLocatar;
	string tipApartament;
	float suprafata{ -1 };


	while (true)
	{
		try
		{
			cout << "Introduceti numarul apartamentului pe care vreti sa il editati: ";
			getline(cin, apartamentString);

			apartament = std::stoi(apartamentString);
			break;
		}
		catch (std::invalid_argument ia)
		{
			cout << "Nu se accepta decat valori numerice pentru apartament.\n\n";
		}
	}

	cout << "Introduceti noul nume al locatarului: ";
	getline(cin, numeLocatar);
	cout << "Introduceti noul tip al apartamentului: ";
	getline(cin, tipApartament);

	while (true)
	{
		try
		{
			cout << "Introduceti noua suprafata a apartamentului: ";
			getline(cin, suprafataString);
			suprafata = std::stof(suprafataString);
			break;
		}
		catch (std::invalid_argument ia)
		{
			cout << "Nu se accepta decat valori numerice pentru suprafata.\n\n";
		}
	}

	try {
		this->srv_locatar.ServiceEdit(apartament, numeLocatar, tipApartament, suprafata);
	}
	catch (ValidationException ve)
	{
		cout << ve.getMessage() << "\n\n";
	}
	catch (RepositoryException re)
	{
		cout << re.getMessage() << "\n\n";
	}

	cout << "Editarea a fost realizata cu succes.\n\n";
}


void UI::Cauta_Apartament() const
{
	int apartament{ -1 };
	string apartamentString;

	while (true)
	{
		try
		{
			cout << "Introduceti numarul apartamentului pe care vreti sa il cautati:\n";
			getline(cin, apartamentString);
			apartament = std::stoi(apartamentString);
			break;
		}
		catch (std::invalid_argument ia)
		{
			cout << "Nu se accepta decat valori numerice pentru apartament.\n\n";
		}
	}

	if (this->srv_locatar.search(apartament))
		cout << "Apartamentul cu numarul " + std::to_string(apartament) + " se afla in lista de locatari.\n\n";
	else
		cout << "Apartamentul cu numarul " + std::to_string(apartament) + " NU se afla in lista de locatari.\n\n";

}

void UI::Filter_List()
{
	string criterium;
	bool loop = false;

	string textValue = "";
	float lowerBoundValue{ -1 }, upperBoundValue{ -1 };

	do {
		loop = false;
		cout << "Introduceti criteriul dupa care doriti sa filtrati (tip apartament / suprafata): ";
		getline(cin, criterium);

		if (criterium != "tip apartament" && criterium != "suprafata")
		{
			cout << "Criteriul dat nu a fost recunoscut\n";
			loop = true;
		}
	} while (loop);

	if (criterium == "tip apartament")
	{
		cout << "Introduceti tipul de apartament dupa care doriti sa filtrati: ";
		getline(cin, textValue);
	}
	else if (criterium == "suprafata")
	{
		cout << "Introduceti marginea inferioara a intervalului pentru suprafete: ";
		cin >> lowerBoundValue;
		cout << "Introduceti marginea superioara a intervalului pentru suprafete: ";
		cin >> upperBoundValue;

		getchar();
	}

	vector<Locatar> filteredRepo = this->srv_locatar.ServiceFilter(criterium, textValue, lowerBoundValue, upperBoundValue);

	if (filteredRepo.size() == 0)
	{
		cout << "Nu exista elemente in lista care sa respecte criteriul dat.\n";
		return;
	}

	cout << "Elementele din lista care respecta criteriul dat sunt: \n";

	for (const auto& l : filteredRepo)
	{
		cout << l.locatarToString() << endl;
	}

	cout << endl;
}
//TODO finish this
void UI::Sort_List()
{
	int criterium;
	string order;
	cout << "Introduceti criteriul dupa care vreti sa sortati (nume proprietar, suprafata, tip apartament + suprafata)";
	
	bool loop = false;

	do {
		loop = false;
		cout << "Introduceti criteriul dupa care doriti sa filtrati (nume proprietar - 1 / suprafata - 2 / tip apartament + suprafata - 3): ";
		cin >> criterium;

		if (criterium < 1 || criterium > 3)
		{
			cout << "Criteriul dat nu a fost recunoscut\n";
			loop = true;
		}
	} while (loop);

	do {
		loop = false;
		cout << "Sortati descrescator? (Y/N) ";
		getline(cin, order);

		if (order != "Y" && order != "N")
		{
			cout << "Raspunsul nu a fost recunoscut\n";
			loop = true;
		}
	} while (loop);
	
	bool reversed = false;
	if (order == "Y")
		reversed = true;



	vector<Locatar> sortedList = this->srv_locatar.ServiceSort(reversed, criterium);
}

void UI::Undo() 
{
	try
	{
		this->srv_locatar.ServiceUndo();
		cout << "Operatie de Undo efectuata cu succes.\n";
	}
	catch (RepositoryException re)
	{
		cout << re.getMessage();
	}
	catch (ContainerException ce)
	{
		cout << ce.getMessage();
	}
}

void UI::AddApartmentToNotifList()
{
	int apartament;
	string apString;
	
	while (true)
	{
		try
		{
			cout << "Introduceti numarul apartamentului pe care vreti sa il notificati: ";
			getline(cin, apString);

			apartament = std::stoi(apString);
			break;
		}
		catch (std::invalid_argument ia)
		{
			cout << "Nu se accepta decat valori numerice pentru apartament.\n\n";
		}
	}

	try {
		this->srv_locatar.addToNotifList(apartament);
		cout << "Lista de notificari contine " << this->srv_locatar.getAllNotifList().size() << " elemente.\n";
	}
	catch (RepositoryException re)
	{
		cout << "EXCEPTION: " << re.getMessage();
	}
}

void UI::ClearNotifList()
{
	this->srv_locatar.clearNotifList();
	cout << "Lista de notificari contine " << this->srv_locatar.getAllNotifList().size() << " elemente.\n";
}

void UI::GenerateRandomNotifList()
{
	int nrAp;
	string nrApString;
	while (true)
	{
		try
		{
			cout << "Introduceti numarul de apartamente aleatoare pe care vreti sa le notificati:";
			getline(cin, nrApString);

			nrAp = std::stoi(nrApString);
			break;
		}
		catch (std::invalid_argument ia)
		{
			cout << "Nu se accepta decat valori numerice pentru apartament.\n\n";
		}
	}
	try {
		this->srv_locatar.clearNotifList();
		this->srv_locatar.generateRandomNotifList(nrAp);
	}
	catch (RepositoryException re) 
	{
		cout << "EXCEPTION: " << re.getMessage();
	}
}

void UI::WriteNotificationListToFile()
{
	string filePath;
	cout << "Introduceti numele fisierului in care vreti sa scrieti lista de notificari: ";
	getline(cin, filePath);

	this->srv_locatar.writeNotifListToFile(filePath);
}

void UI::PrintAllNotififiedApartments()
{
	vector<Locatar> notifiedApartments = this->srv_locatar.getAllNotifList();

	if (notifiedApartments.size() == 0)
	{
		cout << "Nu exista apartamente notificate.\n";
		return;
	}

	cout << "Lista de apartamente notificate este urmatoarea:\n";
	for (auto& ap : notifiedApartments)
	{
		cout << ap.locatarToString() << endl;
	}
}

void UI::run()
{
	string cmd;
	this->Print_Main_Menu();
	while (true)
	{
		cout << "Introduceti o comanda: ";
		getline(cin, cmd);
		if (cmd == "exit")
			return;
		if (cmd == "add_loc")
			this->Add_Locatar();
		else if (cmd == "rem_loc")
			this->Remove_Locatar();
		else if (cmd == "print_all")
			this->Print_All_Locatari();
		else if (cmd == "cauta_ap")
			this->Cauta_Apartament();
		else if (cmd == "edit_loc")
			this->Edit_Locatar();
		else if (cmd == "filter_loc")
			this->Filter_List();
		else if (cmd == "sort_loc")
			this->Sort_List();
		else if (cmd == "notify_ap")
			this->AddApartmentToNotifList();
		else if (cmd == "clear_notifications")
			this->ClearNotifList();
		else if (cmd == "gen_rnd_notif")
			this->GenerateRandomNotifList();
		else if (cmd == "print_notif")
			this->PrintAllNotififiedApartments();
		else if (cmd == "print_notif_to_file")
			this->WriteNotificationListToFile();
		else if (cmd == "undo")
			this->Undo();
		else
			cout << "Comanda nu a fost recunoscuta\n";
	}
}