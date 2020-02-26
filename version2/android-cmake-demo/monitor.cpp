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

void Monitor::setPid(qint64 pid) { // PID
	QString pidS = QString::number(pid);
	QByteArray pidText;
	pidText.append(pidS);
	w->setPid(pidText);
}

void Monitor::setProgramStatus(QString & string) { // wrapper
	QByteArray bytearray = string.toLocal8Bit();
	w->setProgramStatus(bytearray, true);
}

void Monitor::error(QProcess::ProcessError error)
{
  QString text =  QString("Signal error : error=%1").arg(error);
	setProgramStatus(text);
}

void 	Monitor::finished(int exitCode, QProcess::ExitStatus exitStatus)
{
	QString text = QString("Signal finished : exitCode=%1, exitStatus=%2").arg(exitCode).arg(exitStatus);
	setProgramStatus(text);
  qApp->exit();
}

void 	Monitor::readyReadStandardError()
{
  QString text = QString("Signal readyReadStandardError");
	setProgramStatus(text);
  QProcess *p = (QProcess *)sender();
  QByteArray buf_output = p->readAllStandardError();
	w->setOutput(buf_output);
}

void 	Monitor::readyReadStandardOutput()
{
  QString text =  QString("Signal readyReadStandardOutput");
	setProgramStatus(text);
  QProcess *p = (QProcess *)sender();
  QByteArray buf_output = p->readAllStandardOutput();
	w->setOutput(buf_output);
}

void 	Monitor::started()
{
	QString text = QString("Signal started");
	setProgramStatus(text);
  qDebug() << text;
}

void Monitor::errorOccurred(QProcess::ProcessError error) {
	QString text = QString("Signal errorOccurred : error=%1").arg(error);
	setProgramStatus(text);
}

void Monitor::stateChanged(QProcess::ProcessState newState) {
	QString text = QString("Signal stateChanged : newState=%1").arg(newState);
	setProgramStatus(text);
}
