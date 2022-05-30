#pragma once
#include <vector>
#include "Observer.h"

using namespace std;

class Subject
{
protected:
	vector<Observer*> observers;

	void notify();

public:
	void attach(Observer*);
	void detach(Observer*);
};

