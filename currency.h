#ifndef CURRENCY_H
#define CURRENCY_H

#include <QString>

class Currency {
public:
  Currency(QString, QString, double);
  ~Currency();
  const QString getFrom();
  const QString getTo();
  double getRate();

private:
  QString from;
  QString to;
  double rate;
};

#endif // CURRENCY_H
