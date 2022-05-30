#include "Undo.h"

void UndoAdauga::doUndo()
{
	this->repo.removeLocatar(this->addedApartment.getApartament());
}

void UndoSterge::doUndo()
{
	this->repo.adaugaLocatar(this->removedLocatar);
}

void UndoModifica::doUndo()
{
	this->repo.editLocatar(this->modifiedLocatar.getApartament(), this->modifiedLocatar.getNumeProprietar(), this->modifiedLocatar.getTipApartament(), this->modifiedLocatar.getSuprafata());
}
