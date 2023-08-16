#include "bankclient.h"

#include <QNetworkReply>

BankClient::BankClient(QObject *parent)
    : QObject(parent), reply(nullptr), httpRequestAborted(false) {
  this->exhcangeRates = new ExchangeRates();
  this->parser = new BelapbParser();
  connect(&qnam, &QNetworkAccessManager::sslErrors, this,
          &BankClient::sslErrors);
}

BankClient::~BankClient() {
  delete this->exhcangeRates;
  delete this->parser;
}

void BankClient::startRequest(const QUrl &requestedUrl) {
  qDebug() << "start requesting";
  url = requestedUrl;
  httpRequestAborted = false;

  reply = qnam.get(QNetworkRequest(url));
  connect(reply, &QNetworkReply::finished, this, &BankClient::httpFinished);
  connect(reply, &QIODevice::readyRead, this, &BankClient::httpReadyRead);
}

double BankClient::getCurrency(QString from, QString to) {
  return this->exhcangeRates->getCurrency(from, to);
}

const std::list<Currency> BankClient::getAllCurrencies() {
  return this->exhcangeRates->getAll();
}

void BankClient::httpReadyRead() {
  qDebug() << "ready read reply";
  this->exhcangeRates->update(
      this->parser->getCurrencyList(this->reply->readAll().toStdString()));
}

void BankClient::httpFinished() {
  qDebug() << "finished";
  if (httpRequestAborted) {
    reply->deleteLater();
    reply = nullptr;
    return;
  }

  if (reply->error()) {
    reply->deleteLater();
    reply = nullptr;
    return;
  }

  const QVariant redirectionTarget =
      reply->attribute(QNetworkRequest::RedirectionTargetAttribute);

  reply->deleteLater();
  reply = nullptr;
}

#ifndef QT_NO_SSL
void BankClient::sslErrors(QNetworkReply *, const QList<QSslError> &errors) {
  QString errorString;
  for (const QSslError &error : errors) {
    if (!errorString.isEmpty())
      errorString += '\n';
    errorString += error.errorString();
  }
  qDebug() << errorString;
}
#endif
