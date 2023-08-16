#include "calculate.h"

Calculate::Calculate() {
  this->client = new BankClient();
  this->client->startRequest(QUrl("https://belapb.by/ExCardsDaily.php"));
  this->money.push_back(*new Money("toUSD", "$", "USD"));
  this->money.push_back(*new Money("toEUR", "\u20AC", "EUR"));
  this->money.push_back(*new Money("toBYN", "р", "BYN"));
}

Calculate::~Calculate() {}

QString Calculate::calculate(QString expression) {
  // breakets proccesing
  while (expression.contains("(")) {
    int startPosition = expression.lastIndexOf("(");
    int endPosition = expression.indexOf(")", startPosition);
    QString subExpression;
    if (startPosition >= 5 && expression.mid(startPosition - 5, 2) == "to") {
      subExpression =
          expression.mid(startPosition - 5, 5) +
          expression.mid(startPosition + 1, endPosition - startPosition - 1);
      expression.replace(
          expression.mid(startPosition - 5, endPosition - startPosition + 6),
          calculate(subExpression));
    } else {
      subExpression =
          expression.mid(startPosition + 1, endPosition - startPosition - 1);
      expression.replace("(" + subExpression + ")", calculate(subExpression));
    }
  }

  // sum and sub operation processing
  if (expression.contains(QRegExp("\\d+.*[-+]+\\d+"))) {
    expression.replace(QRegExp("(--)|(\\+\\+)"), "+");
    expression.replace(QRegExp("(-\\+)|(\\+-)"), "-");
    expression.replace(QRegExp("^\\+"), "");
    QString subStr = "";
    if (expression.startsWith("to")) {
      subStr = expression.mid(0, 5);
      expression.replace(subStr, "");
    }

    QString symbol = nullptr;
    for (Money temp : this->money) {
      if (expression.contains(temp.getSymbol())) {
        if (symbol != nullptr) {
          return QString("error of operation diffirent types");
        }
        expression.replace(temp.getSymbol(), "");
        symbol = temp.getSymbol();
      }
    }

    int previous = 0;
    double result = 0;
    while (previous != -1) {
      int current = expression.indexOf(QRegExp("[+-]"), previous + 1);
      result += expression.mid(previous, current - previous).toDouble();
      previous = current;
    }
    if (subStr != "") {
      return subStr.append("(")
          .append(QString::number(result))
          .append(symbol)
          .append(")");
    } else {
      return QString::number(result).append(symbol);
    }
  }

  // converting proccesing
  for (Money temp : this->money) {
    if (expression.startsWith(temp.getCommand())) {
      for (Money var : this->money) {
        if (expression.contains(var.getSymbol())) {
          if (var.getName() == temp.getName()) {
            return expression.mid(5);
          } else {
            expression = expression.mid(5);
            expression.replace(var.getSymbol(), "");
            double rate =
                this->client->getCurrency(var.getName(), temp.getName());
            return QString::number(expression.toDouble() * rate)
                .append(temp.getSymbol());
          }
        }
      }
    }
  }

  return expression;
}

QString Calculate::getExchangeRates() {
  QString out;
  for (Currency temp : this->client->getAllCurrencies()) {
    out.append(temp.getFrom())
        .append(" to ")
        .append(temp.getTo())
        .append(" : ")
        .append(QString::number(temp.getRate()))
        .append("\n");
  }
  return out;
}

void Calculate::update() {
  this->client->startRequest(QUrl("https://belapb.by/ExCardsDaily.php"));
}

QString Calculate::help() {
  QString out;
  out.append("commands and symbols :\n");
  for (Money temp : money) {
    out.append("\t")
        .append(temp.getCommand())
        .append(" ")
        .append(temp.getSymbol())
        .append("\n");
  }
  out.append("example : toUSD(5р + 6р) + toUSD(toEUR(10$))");
  return out;
}
