#include "TodoObject.h"

TodoObject::TodoObject(QObject *parent) :
  QObject(parent)
{
}

QString TodoObject::headline() {
  return m_headline;
}

QDate TodoObject::dueDate() {
  return m_dueDate;
}

void TodoObject::setHeadline(const QString &headline) {
  m_headline = headline;
  emit headlineChanged();
}

void TodoObject::setDueDate(const QDate &dueDate) {
  m_dueDate = dueDate;
  emit dueDateChanged();
}
