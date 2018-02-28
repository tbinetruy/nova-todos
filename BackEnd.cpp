#include "BackEnd.h"

BackEnd::BackEnd(QObject *parent) :
    QObject(parent)
{
  m_todoList.append("foo");
  m_todoList.append("bar");
}

QStringList BackEnd::todoList()
{
  return m_todoList;
}

QString BackEnd::todoCount()
{
  return m_todoCount;
}

QString BackEnd::userName()
{
    return m_userName;
}

void BackEnd::countTodos()
{
  auto const inputFile = QString::fromUtf8("todos.org");

  auto const todoCount = main2(inputFile, m_userName);

  this->setTodoCount(QString::number(todoCount));
}

void BackEnd::setTodoList(QStringList &todoList)
{
  if (todoList == m_todoList)
    return;

  m_todoList = todoList;
  emit todoListChanged();
}

void BackEnd::setUserName(const QString &userName)
{
    if (userName == m_userName)
        return;

    m_userName = userName;
    emit userNameChanged();
}


void BackEnd::setTodoCount(const QString &todoCount)
{
  if (todoCount == m_todoCount)
    return;

  m_todoCount = todoCount;
  emit todoCountChanged();
}
