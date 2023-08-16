#ifndef MONEY_H
#define MONEY_H

#include <QString>

class Money {
public:
  Money(QString, QString, QString);
  ~Money();
  const QString getCommand();
  const QString getSymbol();
  const QString getName();

private:
  QString command;
  QString symbol;
  QString name;
};

#endif // MONEY_H
