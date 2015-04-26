#include "control_widget.h"

ControlWidget::ControlWidget(QWidget *parent) : QWidget(parent)
{
    addRowButton = new QPushButton(tr("Добавить"), this);
    deleteRowButton = new QPushButton(tr("Удалить"), this);
    searchLineEdit = new QLineEdit(this);
    searchButton = new QPushButton(tr("Поиск"), this);

    searchLineEdit->setPlaceholderText(tr("Искать..."));

    QGridLayout *layout = new QGridLayout(this);
    layout->addWidget(addRowButton, 0, 0);
    layout->addWidget(deleteRowButton, 0, 1);
    layout->addWidget(searchLineEdit, 0, 2);
    layout->addWidget(searchButton, 0, 3);
    setLayout(layout);

    connect(searchLineEdit, SIGNAL(returnPressed()), searchButton, SLOT(click()));
}
