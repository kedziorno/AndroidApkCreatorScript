// main.cpp
#include <QApplication>
#include <QDebug>
#include <QProcess>
#include <QStringList>
#include "widget.hpp"
#include "monitor.hpp"

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

	qint64 pid;
	QProcess vc_process;
	vc_process.setProgram("libvotecnode-android.so");
	QStringList arguments;
	arguments << "--debug-level=veryhigh";
	vc_process.setArguments(arguments);
	vc_process.start();
	pid = vc_process.processId();
	qDebug() << "PID : " << pid;

	Monitor m;
	m.setPid(pid);

	QObject::connect(&vc_process, SIGNAL(finished(int,QProcess::ExitStatus)), &m, SLOT(finished(int,QProcess::ExitStatus)));
  QObject::connect(&vc_process, SIGNAL(readyReadStandardOutput()), &m, SLOT(readyReadStandardOutput()));
  QObject::connect(&vc_process, SIGNAL(started()), &m, SLOT(started()));
  
	return app.exec();
}

