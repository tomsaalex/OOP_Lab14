#pragma once
#include "Observer.h"
#include "CustomTableModel.h"
#include "ServiceLocatari.h"
#include <QWidget>
#include <qboxlayout.h>
#include <QLabel>
#include <QTableWidget>
#include <QFormLayout>
#include <QPushButton>

class NotificationsListWindow : public QWidget, Observer
{
private:
    ServiceLocatar& srvLocatari;

    QHBoxLayout* mainLayout;

    QWidget* leftWidget;
    QVBoxLayout* leftLayout;

    QWidget* rightWidget;
    QVBoxLayout* rightLayout;

    //QTableWidget* notifTable;

    CustomTableModel* notifTableModel;
    QTableView* notifTableView;

    QLabel* listLabel1;

    QWidget* notifListFormWidget;
    QFormLayout* notifListForm;
    QPushButton* clearNotifListButton;
    QPushButton* addToNotifListButton;
    QLineEdit* apartmentToNotify;
    QPushButton* generateRandomNotifList;
    QLineEdit* numberOfApartments;
    QPushButton* printNotifListToFile;
    QLineEdit* printFilePathBox;


    void initGUIComponents();
    void connectSignalSlots();
    //void reloadList(vector<Locatar>);
    void NotifyApartment();
    void ClearNotifList();
    void GenerateRandomNotifList();
    void PrintNotifListToFile();


    void update() override {
        //reloadList(srvLocatari.getAllNotifList());
        notifTableModel->setElements(srvLocatari.getAllNotifList());    }

public:
    NotificationsListWindow(ServiceLocatar& serviceLocatari) : srvLocatari{ serviceLocatari } {
        initGUIComponents();
        notifTableView->setModel(notifTableModel);
        connectSignalSlots();
        //reloadList(srvLocatari.getAllNotifList());
        notifTableModel->setElements(srvLocatari.getAllNotifList());
    }

    ~NotificationsListWindow()
    {
        srvLocatari.getNotifList().detach(this);
    }
};
