// main.cpp
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "widget.hpp"

int main(int argc, char *argv[])
{
  QGuiApplication app(argc, argv);

	Widget w;
	w.show();
  
	return app.exec();
}

