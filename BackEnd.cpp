#include "BackEnd.h"

BackEnd::BackEnd(QObject *parent) :
    QObject(parent)
{
}

QList<QObject*> BackEnd::scheduledTodoList()
{
  return m_scheduledTodoList;
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

bool dtcomp(TodoObject* left, TodoObject* right) {
  return left->dueDate() < right->dueDate();
}

void BackEnd::getTodos()
{
  auto const inputFile = QString::fromUtf8("dump.org");

  auto const headlines = main2(inputFile, m_userName);
  QList<TodoObject*> headlineList; // need to sort by date
  QList<QObject*> _headlineList;
  QList<QObject*> _scheduledHeadlineList;

  // loop through headlines and find todos
  for(int i = 0; i < headlines.count(); i++) {
    auto currentTodo = new TodoObject();
    currentTodo->setHeadline(headlines[i]->caption());
    headlineList.append(currentTodo);

    auto headline = headlines[i];
    auto children = headline->children();

    // check if todo has children
    if(children.length() > 0) {
      auto firstChild = children[0]->line();
      auto scheduledKeyword = QString::fromUtf8("SCHEDULED: ");
      bool isTodoScheduled = firstChild.contains(scheduledKeyword);

      // check if todo is scheduled
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

  // sort by date
  std::sort(headlineList.begin(), headlineList.end(), dtcomp);

  // store in QList<QObject*>
  for(int i = 0; i < headlineList.count(); i++) {
    // check if todo has due date
    if(headlineList[i]->dueDate().isNull()) {
      _headlineList.append(headlineList[i]);
    } else {
      auto currentTodo = headlineList[i];
      if(i > 0) {
        auto previousTodo = headlineList[i - 1];
        if(currentTodo->dueDate() > previousTodo->dueDate()) {
          auto currentDateHeadline = new TodoObject();
          currentDateHeadline->setHeadline(currentTodo->dueDate().toString());

          auto date = currentTodo->dueDate().toString();
          // currentTodo->setHeadline(headlines[i]->caption());
          _scheduledHeadlineList.append(currentDateHeadline);
        }
      }

      _scheduledHeadlineList.append(headlineList[i]);
    }
  }


  // call setter
  this->setTodoList(_headlineList);
  this->setScheduledTodoList(_scheduledHeadlineList);
}

void BackEnd::setScheduledTodoList(QList<QObject*> &todoList)
{
  if (todoList == m_scheduledTodoList)
    return;

  m_scheduledTodoList = todoList;
  emit scheduledTodoListChanged();
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
