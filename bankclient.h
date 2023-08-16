#ifndef BANKCLIENT_H
#define BANKCLIENT_H

#include <QFile>
#include <QNetworkAccessManager>
#include <QObject>
#include <belapbparser.h>
#include <exchangerates.h>

class BankClient : public QObject {
  Q_OBJECT

public:
  explicit BankClient(QObject *parent = nullptr);
  ~BankClient();

  void startRequest(const QUrl &requestedUrl);
  double getCurrency(QString from, QString to);
  const std::list<Currency> getAllCurrencies();

private slots:

  void httpFinished();
  void httpReadyRead();
#ifndef QT_NO_SSL
  void sslErrors(QNetworkReply *, const QList<QSslError> &errors);
#endif

private:
  std::unique_ptr<QFile> openFileForWrite(const QString &fileName);
  QUrl url;
  QNetworkAccessManager qnam;
  QNetworkReply *reply;
  bool httpRequestAborted;
  ExchangeRates *exhcangeRates;
  BelapbParser *parser;
};

#endif // BANKCLIENT_H
