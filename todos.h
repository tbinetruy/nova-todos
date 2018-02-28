#ifndef TODOS
#define TODOS

#include <QCoreApplication>
#include <QFile>
#include <QTextStream>

#include <Parser.h>
#include <Headline.h>
#include <FindElements.h>

QList<QSharedPointer<OrgMode::Headline>> main2(QString inputFile, QString todoState);

#endif
