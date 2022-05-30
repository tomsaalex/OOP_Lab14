#pragma once
#include <QAbstractTableModel>
#include "Locatar.h"
#include <vector>

class CustomTableModel: public QAbstractTableModel
{ 
private:
	std::vector<Locatar> locatari;
public:
	CustomTableModel(std::vector<Locatar> loc) : locatari{ loc } {};

	int rowCount(const QModelIndex& = QModelIndex()) const override;
	int columnCount(const QModelIndex& = QModelIndex()) const override;

	QVariant data(const QModelIndex&, int role = Qt::DisplayRole) const override;
	void setElements(std::vector<Locatar> locs);

	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

};

