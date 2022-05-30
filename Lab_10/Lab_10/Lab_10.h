#pragma once

#include "ui_Lab_10.h"
#include <qlabel.h>
#include <qwidget.h>
#include <qboxlayout.h>
#include "ServiceLocatari.h"
#include <qlistwidget.h>
#include <qtablewidget.h>
#include <qpushbutton.h>
#include <QCheckBox>
#include <QComboBox>
#include <vector>
#include <QtWidgets/qformlayout.h>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QGroupBox>
#include "NotificationsListReadOnlyWindow.h"
#include <QPointer>
#include "CustomTableModel.h"
#include "CustomListModel.h"


class Lab_10GUI : public QWidget {
private:
    ServiceLocatar& srvLocatari;
    QHBoxLayout* mainLayout;
    
    //New Stuff
    QWidget* leftWidget;
    QWidget* rightWidget;
    QWidget* dynamicButtonsWidget;

    QVBoxLayout* leftVBox;
    QFormLayout* rightBox;
    QVBoxLayout* dynamicButtonsLayout;
    QHBoxLayout* operationButtonsLayout;
    
    QLabel* locatariListTitleLabel;
    //QListWidget* locatariGUIList;
    QListView* locatariListView;
    CustomListModel* listModel;

    QWidget* sortingOptionsWidget;
    QWidget* filteringOptionsWidget;


    QHBoxLayout* sortingOptionsLayout;
    QHBoxLayout* filteringOptionsLayout;
    QVBoxLayout* centeredButtonLayout;

    QPushButton* btnSortByName;
    QPushButton* btnSortBySurface;
    QPushButton* btnSortBy2Criteria;
    QCheckBox* reverseSortButton;

    QPushButton* filterList;
    QLineEdit* filterNum1;
    QLineEdit* filterNum2;
    QLineEdit* filterText;
    QComboBox* filteringCombo;

    QLineEdit* txtApartament;
    QLineEdit* txtNumeProprietar;
    QLineEdit* txtTipApartament;
    QLineEdit* txtSuprafata;
    
    QPushButton* btnAdaugaLocatar;
    QPushButton* btnEditeazaLocatar;
    QPushButton* btnStergereLocatar;
    QPushButton* btnUndo;
    QPushButton* notifListDisplayButton;
    QPushButton* readNotifListDisplayButton;
    
    //

    QPushButton* clearNotifListButton;
    QPushButton* addToNotifListButton;
    QLineEdit* apartmentToNotify;
    QPushButton* generateRandomNotifList;
    QLineEdit* numberOfApartments;
    QPushButton* printNotifListToFile;
    QLineEdit* printFilePathBox;

    //

    QGroupBox* cosGroup;
    QFormLayout* cosGroupLayout;


    QLineEdit* searchBox;
    QPushButton* initSearchButton;

    QRegularExpression realNumberField;
    QRegularExpression naturalNumberField;
    QRegularExpressionValidator* realNumberFieldValidator;
    QRegularExpressionValidator* naturalNumberFieldValidator;

    //NotificationsListReadOnlyWindow* notifListWindowRead;
    //NotificationsListWindow* notifListWindow;
    
    vector<QPointer<QWidget>> allOpenWindows;

    vector<QPushButton*> dynamicButtons;



    //Function that manages the initialization of GUI components.
    void initGUIComponents();
    
    //Function that generates the connections between slots and signals.
    void connectSignalSlots();

    //Function that manages the reloading of locatar objects from memory.
    //void reloadList(const std::vector<Locatar>& locatari);

    //Function that manages the addition of locatar objects.
    void addNewLocatar();

    //Function that manages the editing of locatar objects.
    void editLocatar();

    //Function that manages the deletion of locatar objects.
    void stergeLocatar();

    //Function that manages the undo operation.
    void undoChanges();

    //Function that adds buttons dynamically at runtime.
    void addDynamicButtonsStartup(const std::vector<Locatar>&);
    
    //Function that looks up a locatar in the list and presents it.
    void SearchLocatar();

    void closeEvent(QCloseEvent* event);
    
    void tractor();

    void NotifyApartment();

    void ClearNotifList();

    void GenerateRandomNotifList();

    void PrintNotifListToFile();

    //void adaugaButoane(const std::vector<Locatar>& locatari);
public:
    Lab_10GUI(ServiceLocatar& srv_loc) : srvLocatari{ srv_loc } {
        initGUIComponents();
        locatariListView->setModel(listModel);
        connectSignalSlots();
        //reloadList(srvLocatari.getAll());
        listModel->setElements(srvLocatari.getAll());
        addDynamicButtonsStartup(srvLocatari.getAll());
        tractor();
        //adaugaButoane(srvLocatari.getAll());
    }
};