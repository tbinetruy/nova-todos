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

public:
    explicit BackEnd(QObject *parent = nullptr);

    QString userName();
    QString todoCount();
    void setUserName(const QString &userName);
    void setTodoCount(const QString &todoCount);
    Q_INVOKABLE void countTodos();

signals:
    void userNameChanged();
    void todoCountChanged();

private:
    QString m_userName;
    QString m_todoCount;
};

#endif // BACKEND_H
