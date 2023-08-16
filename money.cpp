#include "money.h"

Money::Money(QString command, QString symbol, QString name) {
  this->command = command;
  this->symbol = symbol;
  this->name = name;
}

Money::~Money() {}

const QString Money::getCommand() { return this->command; }

const QString Money::getSymbol() { return this->symbol; }

const QString Money::getName() { return this->name; }
