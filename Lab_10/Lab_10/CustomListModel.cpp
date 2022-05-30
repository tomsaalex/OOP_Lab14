#include "CustomListModel.h"

int CustomListModel::rowCount(const QModelIndex& parent) const
{
	return locatari.size();
}

int CustomListModel::columnCount(const QModelIndex& parent) const
{
	return 1;
}

QVariant CustomListModel::data(const QModelIndex& index, int role) const
{
	if (role == Qt::DisplayRole)
	{
		int ap = locatari[index.row()].getApartament();
		//setData(index, ap, Qt::UserRole);
		return QString("Ap. %1 - %2").arg(ap).arg(QString::fromStdString(locatari[index.row()].getNumeProprietar()));
	}
	else if (role == Qt::UserRole)
	{
		return locatari[index.row()].getApartament();
	}
	return QVariant();
}

void CustomListModel::setElements(std::vector<Locatar> locs)
{
	locatari = locs;
	auto topLeft = createIndex(0, 0);
	auto bottomRight = createIndex(locs.size(), 0);

	QModelIndex index;
	int ap;

	for (int i = 0; i < locs.size(); i++)
	{
		index = createIndex(i, 0);
		ap = locs[index.row()].getApartament();
		setData(index, ap, Qt::UserRole);
		QString dataGot = data(index, Qt::UserRole).toString();
	}

	emit dataChanged(topLeft, bottomRight);
}
