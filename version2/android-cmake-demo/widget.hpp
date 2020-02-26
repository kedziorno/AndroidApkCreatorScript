#ifndef WIDGET_HPP
#define WIDGET_HPP

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
	Q_OBJECT

public:
	Widget(QWidget *parent = nullptr);
	void setOutput(QByteArray &string);
	void setPid(QByteArray &string);
	void setProgramStatus(QByteArray &string, bool append);

	~Widget();

private:
	Ui::Widget *ui;
};
#endif // WIDGET_HPP
