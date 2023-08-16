#ifndef EXCHANGERATES_H
#define EXCHANGERATES_H

#include <currency.h>
#include <list>

class ExchangeRates {

public:
  ExchangeRates();
  ~ExchangeRates();

  void update(std::list<Currency>);
  const std::list<Currency> getAll();
  double getCurrency(QString from, QString to);

private:
  std::list<Currency> exchangeRates;
};

#endif // EXCHANGERATES_H
