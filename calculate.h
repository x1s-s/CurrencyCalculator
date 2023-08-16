#ifndef CALCULATE_H
#define CALCULATE_H

#include <bankclient.h>
#include <list>
#include <money.h>

class Calculate {
public:
  Calculate();
  ~Calculate();
  QString calculate(QString expression);
  QString getExchangeRates();
  void update();
  QString help();

private:
  BankClient *client;
  std::list<Money> money;
};

#endif // CALCULATE_H
