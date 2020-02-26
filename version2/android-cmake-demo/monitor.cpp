#include <QtCore/QtCore>
#include <QProcess>
#include "monitor.hpp"
#include "widget.hpp"

Monitor::Monitor(QObject *parent) :
    QObject(parent)
{
	w = new Widget();
	w->show();
}

void Monitor::setPid(qint64 pid) {
	QString pidS = QString::number(pid);
	QByteArray pidText;
	pidText.append(pidS);
	w->setError(pidText);
}

void Monitor::error(QProcess::ProcessError error)
{
  qDebug() << "Error: " << error;
}

void 	Monitor::finished(int exitCode, QProcess::ExitStatus exitStatus)
{
  qDebug() << "Finished: " << exitCode;
  qApp->exit();
}

void 	Monitor::readyReadStandardError()
{
  qDebug() << "ReadyError";
}

void 	Monitor::readyReadStandardOutput()
{
  qDebug() << "ReadyOutput";
  QProcess *p = (QProcess *)sender();
  QByteArray buf_output = p->readAllStandardOutput();
	w->setOutput(buf_output);
}

void 	Monitor::started()
{
  qDebug() << "Proc Started";
}

