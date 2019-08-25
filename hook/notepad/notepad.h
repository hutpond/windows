#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_notepad.h"

class notepad : public QMainWindow
{
	Q_OBJECT

public:
	notepad(QWidget *parent = Q_NULLPTR);

private:
	Ui::notepadClass ui;
};
