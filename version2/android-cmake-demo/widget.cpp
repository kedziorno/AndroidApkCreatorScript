#include "widget.hpp"
#include "ui_widget.h"

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

void Widget::setProgramStatus(QByteArray &string) {
	ui->textProgramStatus->setText(string);
}

Widget::~Widget()
{
	delete ui;
}
