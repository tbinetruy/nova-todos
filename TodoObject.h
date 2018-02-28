#ifndef TODO_OBJECT
#define TODO_OBJECT

#include <QObject>
#include <QDate>

class TodoObject : public QObject
{
  Q_OBJECT
  Q_PROPERTY(QString headline READ headline WRITE setHeadline NOTIFY headlineChanged)
  Q_PROPERTY(QDate dueDate READ dueDate WRITE setDueDate NOTIFY dueDateChanged)

 public:
  explicit TodoObject(QObject *parent = nullptr);

  QString headline();
  QDate dueDate();
  void setHeadline(const QString &headline);
  void setDueDate(const QDate &dueDate);

 signals:
  void headlineChanged();
  void dueDateChanged();

 private:
  QString m_headline;
  QDate m_dueDate;
};

#endif
