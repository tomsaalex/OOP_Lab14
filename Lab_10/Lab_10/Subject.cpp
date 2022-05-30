#include "Subject.h"

void Subject::notify()
{
	for (auto& obs : observers)
	{
		obs->update();
	}
}

void Subject::attach(Observer* obs)
{
	this->observers.push_back(obs);
}

void Subject::detach(Observer* obs)
{
	observers.erase(std::remove(observers.begin(), observers.end(), obs), observers.end());
}
