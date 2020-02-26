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

	char *programexec;
	qint64 pid;
	Monitor m;
	QString text;
	QStringList arguments;
	QProcess vc_process;

	arguments << "--debug-level=veryhigh";

#if defined(BUILD_ARM)
	programexec = "libvotecnode-android.so";
#endif
#if defined(BUILD_X86)
	programexec = argv[1];
#endif

	vc_process.setProgram(programexec);
	vc_process.setArguments(arguments);
	//vc_process.setStandardErrorFile("errorlog.txt");
	//vc_process.setStandardOutputFile("outputlog.txt");
	vc_process.start();

	pid = vc_process.processId();
	qDebug() << "PID : " << pid;

	m.setPid(pid);
	text = QString("Execute program %1").arg(programexec);
	m.setProgramStatus(text);

	if (vc_process.waitForStarted(5000)) {
		text = QString("Process after waitForStarted true");
		m.setProgramStatus(text);
	} else {
		text = QString("Process after waitForStarted false");
		m.setProgramStatus(text);
	}

	QObject::connect(&vc_process, SIGNAL(finished(int,QProcess::ExitStatus)), &m, SLOT(finished(int,QProcess::ExitStatus)));
  QObject::connect(&vc_process, SIGNAL(readyReadStandardOutput()), &m, SLOT(readyReadStandardOutput()));
  QObject::connect(&vc_process, SIGNAL(readyReadStandardError()), &m, SLOT(readyReadStandardError()));
  QObject::connect(&vc_process, SIGNAL(started()), &m, SLOT(started()));
	QObject::connect(&vc_process, SIGNAL(errorOccurred(QProcess::ProcessError)), &m, SLOT(errorOccurred(QProcess::ProcessError)));
  QObject::connect(&vc_process, SIGNAL(stateChanged(QProcess::ProcessState)), &m, SLOT(stateChanged(QProcess::ProcessState)));

//	if (vc_process.waitForFinished()) {
//		text = QString("Process after waitForFinished true");
//		m.setProgramStatus(text);
//	} else {
//		text = QString("Process after waitForFinished false");
//		m.setProgramStatus(text);
//	}
 
	return app.exec();
}

