#ifndef BACKEND_H
#define BACKEND_H

#include <iostream>
#include <QObject>
#include <QString>
#include <QStringRef>
#include <QDate>
#include <QtAlgorithms>
#include "todos.h"
#include "TodoObject.h"

class BackEnd : public QObject
{
  Q_OBJECT
    Q_PROPERTY(QString userName READ userName WRITE setUserName NOTIFY userNameChanged)
    Q_PROPERTY(QString todoCount READ todoCount WRITE setTodoCount NOTIFY todoCountChanged)
    Q_PROPERTY(QList<QObject*> todoList READ todoList WRITE setTodoList NOTIFY todoListChanged)
    Q_PROPERTY(QList<QObject*> scheduledTodoList READ scheduledTodoList WRITE setScheduledTodoList NOTIFY scheduledTodoListChanged)

public:
    explicit BackEnd(QObject *parent = nullptr);

    QString userName();
    QString todoCount();
    QList<QObject*> todoList();
    QList<QObject*> scheduledTodoList();
    void setUserName(const QString &userName);
    void setTodoCount(const QString &todoCount);
    void setTodoList(QList<QObject*> &list);
    void setScheduledTodoList(QList<QObject*> &list);
    Q_INVOKABLE void getTodos();

signals:
    void userNameChanged();
    void todoCountChanged();
    void todoListChanged();
    void scheduledTodoListChanged();

private:
    QString m_userName;
    QString m_todoCount;
    QList<QObject*> m_todoList;
    QList<QObject*> m_scheduledTodoList;
};

#endif // BACKEND_H
