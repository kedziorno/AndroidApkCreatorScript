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

void Widget::setError(QByteArray &string) {
	ui->textError->setText(string);
}

Widget::~Widget()
{
	delete ui;
}
