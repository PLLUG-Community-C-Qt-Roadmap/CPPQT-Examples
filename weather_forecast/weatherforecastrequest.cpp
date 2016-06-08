#include "weatherforecastrequest.h"

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrlQuery>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>

#include <QDebug>

const QString WEATHER_API_BASE_URL("http://api.openweathermap.org/data/2.5");

const QString REQUEST_WEATHER_FORECAST("forecast/daily");

const QString QUERY_CITY_NAME("q");
const QString QUERY_UNITS_FORMAT("units");
const QString QUERY_LANGUAGE("lang");
const QString QUERY_RESULTS_COUNT("cnt");

const QString DEFAULT_UNITS_FORMAT("metric");
const int DEFAULT_RESULTS_COUNT(1);

WeatherForecastRequest::WeatherForecastRequest(QObject *parent)
    : QObject(parent),
      mNetworkManager(new QNetworkAccessManager(this)),
      mReply(nullptr),
      mCount(0)
{

}

void WeatherForecastRequest::setCityName(const QString &city)
{
    mCity = city;
}

void WeatherForecastRequest::setLanguage(const QString &lang)
{
    mLang = lang;
}

void WeatherForecastRequest::setDaysCount(int count)
{
    mCount = count;
}

void WeatherForecastRequest::slotSend()
{
    QNetworkRequest request;

    QUrl requestUrl(QString("%1/%2").arg(WEATHER_API_BASE_URL).arg(REQUEST_WEATHER_FORECAST));

    QUrlQuery requestQuery;
    if (!mCity.isEmpty())
    {
        requestQuery.addQueryItem(QUERY_CITY_NAME, mCity);
    }
    if (!mLang.isEmpty())
    {
        requestQuery.addQueryItem(QUERY_LANGUAGE, mLang);
    }
    requestQuery.addQueryItem(QUERY_UNITS_FORMAT, DEFAULT_UNITS_FORMAT);
    requestQuery.addQueryItem(QUERY_RESULTS_COUNT, QString::number(mCount));
    requestUrl.setQuery(requestQuery);

    qDebug() << QString("Sending request: %1").arg(requestUrl.toString());

    request.setUrl(requestUrl);

    mReply = mNetworkManager->get(request);
    connect(mReply, &QNetworkReply::finished, this, &WeatherForecastRequest::slotRequestFinished, Qt::UniqueConnection);
}

void WeatherForecastRequest::slotRequestFinished()
{
    QByteArray replyData = mReply->readAll();
    qDebug() << "::: " << replyData;
    emit finished(replyData);
    mReply->deleteLater();
    mReply = nullptr;
}

