#include "exchangerates.h"

#include <QString>

ExchangeRates::ExchangeRates() {}

ExchangeRates::~ExchangeRates() {}

double ExchangeRates::getCurrency(QString from, QString to) {
  for (Currency temp : this->exchangeRates) {
    if (temp.getFrom() == from && temp.getTo() == to) {
      return temp.getRate();
    }
  }
  return -1;
}

void ExchangeRates::update(std::list<Currency> list) {
  this->exchangeRates = list;
}

const std::list<Currency> ExchangeRates::getAll() {
  return this->exchangeRates;
}
