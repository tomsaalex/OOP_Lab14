#pragma once
#include "RepositoryLocatari.h"

class ActiuneUndo
{
public:

	//Virtual function that will be overriden with the functionality needed to undo an operation
	virtual void doUndo() = 0;

	//Virtual destructor that will be overriden with the derived class'.
	virtual ~ActiuneUndo() = default;
};

class UndoAdauga: public ActiuneUndo
{
private:
	RepositoryLocatar& repo;
	Locatar addedApartment;
public:
	//Actual function that undoes an addition.
	void doUndo() override;

	//The constructor of this derived class.
	UndoAdauga(RepositoryLocatar& repository, Locatar loc) : repo{ repository }, addedApartment{ loc }{}

	//The default destructor of this class.
	~UndoAdauga() override = default;
};

class UndoSterge: public ActiuneUndo
{
private:
	RepositoryLocatar& repo;
	Locatar removedLocatar;
public:
	//Actual function that undoes a removal.
	void doUndo() override;

	//The constructor of this derived class.
	UndoSterge(RepositoryLocatar& repository, Locatar loc) : repo{ repository }, removedLocatar{ loc }{}

	//The default destructor of this class.
	~UndoSterge() override = default;
};

class UndoModifica: public ActiuneUndo
{
private:
	RepositoryLocatar& repo;
	Locatar modifiedLocatar;
public:

	//Actual function that undoes a removal.
	void doUndo() override;

	//The constructor of this derived class.
	UndoModifica(RepositoryLocatar& repository, Locatar loc) : repo{ repository }, modifiedLocatar{ loc }{}

	//The default destructor of this class.
	~UndoModifica() override = default;
};