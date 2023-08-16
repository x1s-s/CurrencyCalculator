#include "belapbparser.h"

#include <QString>

BelapbParser::BelapbParser() {}

BelapbParser::~BelapbParser() {}

std::list<Currency> BelapbParser::getCurrencyList(std::string request) {
  QXmlStreamReader *xml =
      new QXmlStreamReader(QByteArray::fromStdString(request));
  std::list<Currency> list;
  while (!xml->atEnd() && !xml->hasError()) {
    QXmlStreamReader::TokenType token = xml->readNext();
    if (token == QXmlStreamReader::StartDocument) {
      continue;
    }
    if (token == QXmlStreamReader::StartElement) {
      if (xml->name() == "CharCode") {
        QString text = xml->readElementText();
        if (text == "USD") {
          xml->readNext();
          xml->readElementText();
          xml->readNext();
          xml->readElementText();
          xml->readNext();
          xml->readNext();
          xml->readElementText();
          xml->readNext();
          xml->readNext();
          double rateBuy = xml->readElementText().toDouble();
          xml->readNext();
          xml->readNext();
          double rateSell = xml->readElementText().toDouble();
          list.push_back(
              *new Currency(QString("USD"), QString("BYN"), rateBuy));
          list.push_back(
              *new Currency(QString("BYN"), QString("USD"), 1 / rateSell));
        }
        if (text == "EUR") {
          xml->readNext();
          xml->readElementText();
          xml->readNext();
          xml->readElementText();
          xml->readNext();
          xml->readNext();
          xml->readElementText();
          xml->readNext();
          xml->readNext();
          double rateBuy = xml->readElementText().toDouble();
          xml->readNext();
          xml->readNext();
          double rateSell = xml->readElementText().toDouble();
          list.push_back(
              *new Currency(QString("EUR"), QString("BYN"), rateBuy));
          list.push_back(
              *new Currency(QString("BYN"), QString("EUR"), 1 / rateSell));
        }
        if (text == "EUR(USD)") {
          xml->readNext();
          xml->readElementText();
          xml->readNext();
          xml->readElementText();
          xml->readNext();
          xml->readNext();
          xml->readElementText();
          xml->readNext();
          xml->readNext();
          double rateBuy = xml->readElementText().toDouble();
          xml->readNext();
          xml->readNext();
          double rateSell = xml->readElementText().toDouble();
          list.push_back(
              *new Currency(QString("EUR"), QString("USD"), rateBuy));
          list.push_back(
              *new Currency(QString("USD"), QString("EUR"), 1 / rateSell));
        }
      }
    }
  }
  xml->clear();
  return list;
}
