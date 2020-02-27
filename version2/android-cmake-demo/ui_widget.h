#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QTextEdit>
#include <QtCore/QSize>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
	QGridLayout *centralWidget;
	QVBoxLayout *verticalLayout;
	QTextEdit *textOutput;
	QTextEdit *textPid;
	QTextEdit	*textProgramStatus;
    
  void setupUi(QWidget *Widget) {
		if (Widget->objectName().isEmpty())
		    Widget->setObjectName(QString::fromUtf8("votecnode"));
		Widget->resize(320, 480);

		centralWidget = new QGridLayout(Widget);

		textOutput = new QTextEdit();
		textPid = new QTextEdit();
		textProgramStatus = new QTextEdit();
		textOutput->setFontPointSize(8);
		textPid->setFontPointSize(8);
		textProgramStatus->setFontPointSize(8);
		textOutput->setReadOnly(true);
		textPid->setReadOnly(true);
		textProgramStatus->setReadOnly(true);

		centralWidget->setRowStretch(0, 2);
		centralWidget->setRowStretch(1, 2);
		centralWidget->setRowStretch(2, 1);

		centralWidget->addWidget(textOutput,0,0);
		centralWidget->addWidget(textProgramStatus,1,0);
		centralWidget->addWidget(textPid,2,0);

		Widget->setLayout(centralWidget);

		retranslateUi(Widget);

		QMetaObject::connectSlotsByName(Widget);
  } // setupUi

  void retranslateUi(QWidget *Widget) {
      Widget->setWindowTitle("votecnode");
  } // retranslateUi
};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
