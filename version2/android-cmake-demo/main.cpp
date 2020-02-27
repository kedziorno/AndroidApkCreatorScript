// main.cpp
#include <QApplication>
#include <QDebug>
#include <QProcess>
#include <QStringList>
#include <QDir>
#include <QStandardPaths>
#include <QCoreApplication>
#include "widget.hpp"
#include "monitor.hpp"

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

#if defined(BUILD_ARM)
	QString programexec;
#endif
#if defined(BUILD_X86)
	char *programexec;
#endif
	qint64 pid;
	Monitor m;
	QString text;
	QStringList arguments;
	QProcess vc_process;

	QObject::connect(&vc_process, SIGNAL(finished(int,QProcess::ExitStatus)), &m, SLOT(finished(int,QProcess::ExitStatus)));
  QObject::connect(&vc_process, SIGNAL(readyReadStandardOutput()), &m, SLOT(readyReadStandardOutput()));
  QObject::connect(&vc_process, SIGNAL(readyReadStandardError()), &m, SLOT(readyReadStandardError()));
  QObject::connect(&vc_process, SIGNAL(started()), &m, SLOT(started()));
	QObject::connect(&vc_process, SIGNAL(errorOccurred(QProcess::ProcessError)), &m, SLOT(errorOccurred(QProcess::ProcessError)));
  QObject::connect(&vc_process, SIGNAL(stateChanged(QProcess::ProcessState)), &m, SLOT(stateChanged(QProcess::ProcessState)));

	//arguments << "--debug-level=veryhigh"; // TODO use after upgrade votecnode
	arguments << "--rpc-transp=tcp";

	QString dir_path = QDir::currentPath();
	text = QString("Current working dir is '%1'").arg(dir_path);
	m.setProgramStatus(text);
	QString appdata_path = QStandardPaths::displayName(QStandardPaths::AppDataLocation);
	text = QString("APPDATA location dir is '%1'").arg(appdata_path);
	m.setProgramStatus(text);
	QString appdir_path = QCoreApplication::applicationDirPath();
	text = QString("APPDIR location dir is '%1'").arg(appdir_path);
	m.setProgramStatus(text);
	QString appfile_path = QCoreApplication::applicationFilePath();
	text = QString("APPFILE location dir is '%1'").arg(appfile_path);
	m.setProgramStatus(text);

#if defined(BUILD_ARM)
	programexec = QString("%1/libvotecnode-android.so").arg(appdir_path);
#endif
#if defined(BUILD_X86)
	programexec = argv[1];
#endif

	vc_process.setProgram(programexec);
	vc_process.setArguments(arguments);
#if defined(WRITE_TO_FILE)
	vc_process.setStandardErrorFile("errorlog.txt");
	vc_process.setStandardOutputFile("outputlog.txt");
#endif
	vc_process.start();

	pid = vc_process.processId();
	qDebug() << "PID : " << pid;

	m.setPid(pid);

	text = QString("Execute program %1 with arguments %2").arg(programexec).arg(vc_process.arguments().join(" "));
	m.setProgramStatus(text);

	if (vc_process.waitForStarted(-1)) {
		text = QString("Process after waitForStarted true");
		m.setProgramStatus(text);
	} else {
		text = QString("Process after waitForStarted false");
		m.setProgramStatus(text);
	}

	if (vc_process.waitForFinished()) {
		text = QString("Process after waitForFinished true");
		m.setProgramStatus(text);
	} else {
		text = QString("Process after waitForFinished false");
		m.setProgramStatus(text);
	}
 
	return app.exec();
}

