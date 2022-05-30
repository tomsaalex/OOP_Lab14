#pragma once
#include "ServiceLocatari.h"
#include <unordered_map>

class UI
{
private:
	ServiceLocatar& srv_locatar;
public:
	//Class constructor for UI objects.
	UI(ServiceLocatar& srvLocatar) noexcept:srv_locatar{srvLocatar} {}
	
	//Launches the program's main loop
	void run();
	
	//Function that manages the user interaction part of adding locatar objects to a list.
	void Add_Locatar();

	//Function that manages the user interaction part of removing a locatar object from a list.
	void Remove_Locatar();

	void Edit_Locatar();

	//Function that prints the main menu.
	void Print_Main_Menu() const;

	//Function that prints all the locatari in the repository.
	void Print_All_Locatari() const;
	
	//Function that checks if a locatar object is in the list or not.
	void Cauta_Apartament() const;

	//Function that handles the list filtering part of the app.
	void Filter_List();

	//Function that handles the list sorting part of the app.
	void Sort_List();

	//Function that performs the undo functionality.
	void Undo();

	//Function that manages the UI of the addition of an apartment to the notification list.
	void AddApartmentToNotifList();

	//Function that manages the UI of the removal of all apartments from the notification list.
	void ClearNotifList();

	//Function that manages the UI of the random generation of a notification list using existent apartments.
	void GenerateRandomNotifList();

	//Function that manages the UI of the generation of statistics.
	void Statistics_Apartments();

	//Function that manages the UI of the printing of the notification list to file.
	void WriteNotificationListToFile();

	//Function that manages the UI of the printing of the notification list to console.
	void PrintAllNotififiedApartments();
};