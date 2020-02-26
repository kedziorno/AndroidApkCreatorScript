#ifndef MONITOR_H
#define MONITOR_H

#include <QObject>
#include <QtCore/QtCore>
#include "widget.hpp"

class Monitor : public QObject
{
    Q_OBJECT
public:
    explicit Monitor(QObject *parent = 0);
		void setPid(qint64 pid);
		void setProgramStatus(QString & string);

signals:

public slots:
    void	error(QProcess::ProcessError error);
    void 	finished(int exitCode, QProcess::ExitStatus exitStatus);
    void 	readyReadStandardError();
    void 	readyReadStandardOutput();
    void 	started();
		void 	errorOccurred(QProcess::ProcessError error);
		void	stateChanged(QProcess::ProcessState newState);

private:
		Widget *w;
};

#endif // MONITOR_H
