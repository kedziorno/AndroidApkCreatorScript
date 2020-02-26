#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
	QWidget *centralWidget;
	QVBoxLayout *verticalLayout;
	QTextEdit *textOutput;
	QTextEdit *textPid;
	QTextEdit	*textProgramStatus;
    
  void setupUi(QWidget *Widget) {
		if (Widget->objectName().isEmpty())
		    Widget->setObjectName(QString::fromUtf8("votecnode"));
		Widget->resize(320, 480);

		centralWidget = new QWidget(Widget);
		verticalLayout = new QVBoxLayout(centralWidget);
		textOutput = new QTextEdit(centralWidget);
		textPid = new QTextEdit(centralWidget);
		textProgramStatus = new QTextEdit(centralWidget);

		verticalLayout->addWidget(textOutput);
		verticalLayout->addWidget(textPid);
		verticalLayout->addWidget(textProgramStatus);

		retranslateUi(Widget);

		QMetaObject::connectSlotsByName(Widget);
  } // setupUi

  void retranslateUi(QWidget *Widget) {
      Widget->setWindowTitle(QApplication::translate("Widget", "Widget", nullptr));
  } // retranslateUi
};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
