#ifndef WEATHERFORECASTREQUEST_H
#define WEATHERFORECASTREQUEST_H

#include <QObject>

class QNetworkAccessManager;
class QNetworkReply;

class WeatherForecastRequest : public QObject
{
    Q_OBJECT
public:
    explicit WeatherForecastRequest(QObject *parent = 0);

    void setCityName(const QString &city);
    void setLanguage(const QString &lang);
    void setDaysCount(int count);

signals:
    void finished(const QByteArray &);

public slots:
    void slotSend();

private slots:
    void slotRequestFinished();

private:
    QNetworkAccessManager *mNetworkManager;
    QNetworkReply *mReply;

    QString mCity;
    QString mLang;
    int mCount;
};

#endif // WEATHERFORECASTREQUEST_H
