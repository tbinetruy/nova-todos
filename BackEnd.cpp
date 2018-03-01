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

    auto headline = headlines[i];
    auto children = headline->children();
    if(children.length() > 0) {
      auto firstChild = children[0]->line();
      auto scheduledKeyword = QString::fromUtf8("SCHEDULED: ");
      bool isTodoScheduled = firstChild.contains(scheduledKeyword);

      if(isTodoScheduled) {
        firstChild.remove(0, firstChild.indexOf(scheduledKeyword) + scheduledKeyword.length());
        auto year = firstChild.midRef(1, 4).toInt();
        auto month = firstChild.midRef(6, 2).toInt();
        auto day = firstChild.midRef(9, 2).toInt();

        auto todoDueDate = QDate(year, month, day);

        currentTodo->setDueDate(todoDueDate);
      }
    }
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
