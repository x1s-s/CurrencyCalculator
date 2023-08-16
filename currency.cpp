#include "currency.h"

Currency::Currency(QString from, QString to, double rate) {
  this->from = from;
  this->to = to;
  this->rate = rate;
}

Currency::~Currency() {}

const QString Currency::getFrom() { return this->from; }

const QString Currency::getTo() { return this->to; }

double Currency::getRate() { return this->rate; }
