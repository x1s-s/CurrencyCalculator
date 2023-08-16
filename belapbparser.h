#ifndef BELAPBPARSER_H
#define BELAPBPARSER_H

#include <QXmlStreamReader>
#include <QtDebug>
#include <currency.h>

class BelapbParser {
public:
  BelapbParser();
  ~BelapbParser();
  std::list<Currency> getCurrencyList(std::string request);
};

#endif // BELAPBPARSER_H
