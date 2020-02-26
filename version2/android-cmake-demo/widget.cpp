#include "widget.hpp"
#include "ui_widget.h"
#include <QDebug>

Widget::Widget(QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::Widget)
{
	ui->setupUi(this);
}

void Widget::setOutput(QByteArray &string) {
	ui->textOutput->setText(string);
}

void Widget::setPid(QByteArray &string) {
	ui->textPid->setText(string);
}

void Widget::setProgramStatus(QByteArray &string, bool append) {
	if (append == true) {
		ui->textProgramStatus->append("========");
		ui->textProgramStatus->append(string);
		ui->textProgramStatus->append("========");
	} else {
		ui->textProgramStatus->setText(string);
	}
	qDebug() << string;
}

Widget::~Widget()
{
	delete ui;
}
