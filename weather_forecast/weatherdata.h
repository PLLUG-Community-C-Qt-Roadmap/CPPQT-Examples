#ifndef WEATHERDATA_H
#define WEATHERDATA_H

#include <QByteArray>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QHash>
#include <QDate>

struct Weather
{
    QDate date;
    qreal dayTemperature;
    qreal nightTemperature;
    qreal pressure;
    qreal humidity;
    QHash<int, QString> weatherDescriptionById;
};

class WeatherData
{
public:
    WeatherData(const QByteArray &);

    bool hasData() const;
    QString error() const;

    int weatherItemsCount() const;

    Weather getWeather(int index) const;

private:
    Weather parseWeather(const QJsonObject &) const;
    QJsonArray weatherArray() const;

private:
    QJsonDocument mJson;
    QJsonParseError mError;
};

#endif // WEATHERDATA_H
