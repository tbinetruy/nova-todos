#include "BackEnd.h"

BackEnd::BackEnd(QObject *parent) :
    QObject(parent)
{
}

QList<QObject*> BackEnd::todoList()
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

void BackEnd::getTodos()
{
  auto const inputFile = QString::fromUtf8("dump.org");

  auto const headlines = main2(inputFile, m_userName);
  QList<QObject*> headlineList;

  for(int i = 0; i < headlines.count(); i++) {
    auto currentTodo = new TodoObject();
    currentTodo->setHeadline(headlines[i]->caption());

    headlineList.append(currentTodo);
  }

  this->setTodoList(headlineList);
}

void BackEnd::setTodoList(QList<QObject*> &todoList)
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
