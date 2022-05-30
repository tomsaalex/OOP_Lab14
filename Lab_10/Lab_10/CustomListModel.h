#pragma once
#include <QAbstractListModel>
#include "Locatar.h"
#include <vector>

class CustomListModel: public QAbstractListModel
{
private:
	std::vector<Locatar> locatari;
public:
	CustomListModel(std::vector<Locatar> loc): locatari{loc}{}

	int rowCount(const QModelIndex & = QModelIndex()) const override;
	int columnCount(const QModelIndex & = QModelIndex()) const override;
	
	QVariant data(const QModelIndex& = QModelIndex(), int role = Qt::DisplayRole) const override;
	void setElements(std::vector<Locatar> locs);
};

