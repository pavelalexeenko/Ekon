#include "control_widget.h"

ControlWidget::ControlWidget(QWidget *parent) :
    QWidget(parent)
  , searchType(SearchType::SEARCH)
  , addRowButton(new QPushButton(tr("Добавить"), this))
  , deleteRowButton(new QPushButton(tr("Удалить"), this))
  , searchLineEdit(new QLineEdit(this))
  , searchButton(new QPushButton(tr("Поиск"), this))
  , filterButton(new QPushButton(tr("Фильтровать"), this))
{
    searchLineEdit->setPlaceholderText(tr("Искать..."));

    QGridLayout *layout = new QGridLayout(this);
    layout->addWidget(addRowButton, 0, 0);
    layout->addWidget(deleteRowButton, 0, 1);
    layout->addWidget(searchLineEdit, 0, 2);
    layout->addWidget(searchButton, 0, 3);
    layout->addWidget(filterButton, 0, 4);
    setLayout(layout);


    connect(addRowButton, SIGNAL(clicked()), this, SIGNAL(addRow()));
    connect(deleteRowButton, SIGNAL(clicked()), this, SIGNAL(removeRow()));

    connect(searchLineEdit, SIGNAL(textChanged(QString)), this, SLOT(setSearchType()));
    connect(searchLineEdit, SIGNAL(returnPressed()), this, SLOT(setSearchType()));

    connect(searchButton, SIGNAL(clicked()), this, SLOT(search()));
    connect(filterButton, SIGNAL(clicked()), this, SLOT(filter()));
}


void ControlWidget::search()
{
    qDebug() << __FUNCTION__;

    searchType = SEARCH;
    emit search(searchLineEdit->text().trimmed());
}

void ControlWidget::filter()
{
    qDebug() << __FUNCTION__;

    searchType = FILTER;
    emit filter(searchLineEdit->text().trimmed());
}

void ControlWidget::setSearchType()
{
    qDebug() << __FUNCTION__;

    switch(searchType)
    {
    case SEARCH:
        search();
        break;
    case FILTER:
        filter();
        break;
    default:
        break;
    }
}
