#include "CustomTableModel.h"

int CustomTableModel::rowCount(const QModelIndex& parent) const
{
	qDebug() << locatari.size();
	return locatari.size();
}

int CustomTableModel::columnCount(const QModelIndex& parent) const
{
	return 2;
}

QVariant CustomTableModel::data(const QModelIndex& index, int role) const
{
	qDebug() << "updating data";
	if (role == Qt::DisplayRole)
	{
		//return QString("Row %1 Column %2").arg(index.row() + 1).arg(index.column() + 1);
		Locatar loc = locatari[index.row()];
		if (index.column() == 0)
		{
			return QString::number(loc.getApartament());
		}
		if (index.column() == 1)
		{
			return QString::fromStdString(loc.getNumeProprietar());
		}
	}
	return QVariant{};
}

void CustomTableModel::setElements(std::vector<Locatar> locs)
{
	locatari = locs;
	auto topLeft = createIndex(0, 0);
	auto botRight = createIndex(rowCount(), columnCount());
	emit layoutChanged();
	emit dataChanged(topLeft, botRight);
}

QVariant CustomTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (role == Qt::DisplayRole) {
		if (orientation == Qt::Horizontal) {
			return QString("coloana %1").arg(section);
		}
		else {
			return QString("linie %1").arg(section);
		}
	}
	return QVariant();

}

