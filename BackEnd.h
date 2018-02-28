#ifndef BACKEND_H
#define BACKEND_H

#include <iostream>
#include <QObject>
#include <QString>
#include "todos.h"

class BackEnd : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString userName READ userName WRITE setUserName NOTIFY userNameChanged)
    Q_PROPERTY(QString todoCount READ todoCount WRITE setTodoCount NOTIFY todoCountChanged)
    Q_PROPERTY(QStringList todoList READ todoList WRITE setTodoList NOTIFY todoListChanged)

public:
    explicit BackEnd(QObject *parent = nullptr);

    QString userName();
    QString todoCount();
    QStringList todoList();
    void setUserName(const QString &userName);
    void setTodoCount(const QString &todoCount);
    void setTodoList(QStringList &list);
    Q_INVOKABLE void countTodos();

signals:
    void userNameChanged();
    void todoCountChanged();
    void todoListChanged();

private:
    QString m_userName;
    QString m_todoCount;
    QStringList m_todoList;
};

#endif // BACKEND_H
