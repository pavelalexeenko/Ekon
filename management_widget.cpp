#include "management_widget.h"

ManagementWidget::ManagementWidget(QWidget *parent) : QWidget(parent)
{
    tablesWidget = new TablesWidget(this);

    addRowButton = new QPushButton(tr("Добавить"), this);
    deleteRowButton = new QPushButton(tr("Удалить"), this);

    searchLineEdit = new QLineEdit(this);
    searchButton = new QPushButton(tr("Поиск"), this);

    searchLineEdit->setPlaceholderText(tr("Искать..."));

    QGridLayout *layout = new QGridLayout(this);
    layout->addWidget(tablesWidget, 0, 0, 1, 4);
    layout->addWidget(addRowButton, 1, 0);
    layout->addWidget(deleteRowButton, 1, 1);
    layout->addWidget(searchLineEdit, 1, 2);
    layout->addWidget(searchButton, 1, 3);
    setLayout(layout);

    connect(searchButton, SIGNAL(clicked()), this, SLOT(search()));
    connect(addRowButton, SIGNAL(clicked()), tablesWidget, SLOT(addRow()));
    connect(searchLineEdit, SIGNAL(returnPressed()), this, SLOT(search()));
}

void ManagementWidget::updateLayout()
{
    tablesWidget->updateLayout();
}

void ManagementWidget::refresh()
{
    tablesWidget->refresh();
}

void ManagementWidget::search()
{
    tablesWidget->search(searchLineEdit->text());
}

