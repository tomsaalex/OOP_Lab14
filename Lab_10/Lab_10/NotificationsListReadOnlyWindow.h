#pragma once
#include <qwidget.h>
#include <QPainter>
#include "ServiceLocatari.h"
#include "Observer.h"

class NotificationsListReadOnlyWindow: public QWidget, Observer
{
private:
	ServiceLocatar& srvLocatar;
public:
	//NotificationsListReadOnlyWindow() = delete;
	//NotificationsListReadOnlyWindow(const NotificationsListReadOnlyWindow&) = delete;
	
	NotificationsListReadOnlyWindow(ServiceLocatar& srv) : srvLocatar{srv} {
		setAttribute(Qt::WA_DeleteOnClose);
		srvLocatar.getNotifList().attach(this);
	}
	
	~NotificationsListReadOnlyWindow()
	{
		srvLocatar.getNotifList().detach(this);
	}

	void update() override {
		repaint();
	}
	
	void paintEvent(QPaintEvent* ev) override {
		QPainter p{ this };

		auto locatariList = srvLocatar.getAllNotifList();

		if (locatariList.size() == 0)
			return;
		
		int x, y;
		/*
		int width = p.device()->width();
		width -= 40;
		x = 20;
		y = 20;
		
		int rectWidth = width / locatariList.size();
		
		for (auto Locatar : srvLocatar.getAllNotifList())
		{
			p.drawRect(x, y, rectWidth - rectWidth/10, 100);
			x += rectWidth;
		}
		*/
		
		for (auto Locatar : srvLocatar.getAllNotifList())
		{

			QImage image("QTtheCutie.jpg");
			x = rand() % (this->size().width() - image.size().width()) + 1;
			y = rand() % (this->size().height() - image.size().height()) + 1;

	

			p.drawImage(x, y, image);
		}
		
	}
};

