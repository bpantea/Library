#pragma once

#include "book.h"
#include "repository.h"

template<typename T>
class Undo
{
protected:
public:
	/*
	Undo function. Each undo option will override this function.
	*/
	virtual void doUndo() = 0;
};

template<typename T>
class AddUndo : public Undo<T>
{
private:
	T el;
	AbstractRepository<T>& repo;
public:
	/*
	Constructor for AddUndo.
	repo - AbstractRepository
	el - Book that was previously added.
	*/
	AddUndo(AbstractRepository<T>& repo, const T& el) : repo{ repo }, el{ el } {};

	/*
	Override undo function.
	*/
	void doUndo() override {
		repo.remove(el);
	}
};

template<typename T>
class ModifyUndo : public Undo<T>
{
private:
	AbstractRepository<T>& repo;
	T elFrom, elTo;
public:
	/*
	Constructor for ModifyUndo.
	repo - AbstractRepository
	elFrom - Book that was previously modified.
	elTo - Book that was previously modified.
	*/
	ModifyUndo(AbstractRepository<T>& repo, const T& elFrom, const T& elTo) : repo{ repo }, elFrom{ elFrom }, elTo{ elTo } {}

	/*
	Override undo function.
	*/
	void doUndo() override {
		repo.modify(elTo, elFrom);
	}
};

template<typename T>
class RemoveUndo : public Undo<T>
{
private:
	AbstractRepository<T>& repo;
	T el;
public:
	/*
	Constructor for RemoveUndo.
	repo - AbstractRepository
	el - Book that was previously removed.
	*/
	RemoveUndo(AbstractRepository<T>& repo, const T& el) : repo{ repo }, el{ el } {};

	/*
	Override undo function.
	*/
	void doUndo() override {
		repo.add(el);
	}
};