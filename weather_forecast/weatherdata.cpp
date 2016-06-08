#include "weatherdata.h"

#include <QJsonObject>
#include <QJsonArray>

const QString KEY_WEATHER_DATA_LIST("list");

const QString KEY_WEATHER_DATE("dt");
const QString KEY_WEATHER_TEMPERATURE("temp");
const QString KEY_WEATHER_TEMPERATURE_DAY("day");
const QString KEY_WEATHER_TEMPERATURE_NIGHT("night");
const QString KEY_WEATHER_PRESSURE("pressure");
const QString KEY_WEATHER_HUMIDITY("humidity");
const QString KEY_WEATHER_LIST("weather");
const QString KEY_WEATHER_LIST_ID("id");
const QString KEY_WEATHER_LIST_DESCRIPTION("description");

WeatherData::WeatherData(const QByteArray &json)
{
    mJson = QJsonDocument::fromJson(json, &mError);
}

bool WeatherData::hasData() const
{
    return mError.error == QJsonParseError::NoError;
}

QString WeatherData::error() const
{
    return mError.errorString();
}

int WeatherData::weatherItemsCount() const
{
    int count = 0;

    QJsonArray array = weatherArray();
    if (!array.isEmpty())
    {
        count = array.count();
    }

    return count;
}

Weather WeatherData::getWeather(int index) const
{
    QJsonObject obj = weatherArray().at(index).toObject();
    return parseWeather(obj);
}

Weather WeatherData::parseWeather(const QJsonObject &obj) const
{
    Weather weather;

    int ts = obj.value(KEY_WEATHER_DATE).toInt();
    QDateTime t;
    t.setTime_t(ts);
    weather.date = t.date();

    QJsonObject temp = obj.value(KEY_WEATHER_TEMPERATURE).toObject();
    weather.dayTemperature = temp.value(KEY_WEATHER_TEMPERATURE_DAY).toDouble();
    weather.nightTemperature = temp.value(KEY_WEATHER_TEMPERATURE_NIGHT).toDouble();

    weather.pressure = obj.value(KEY_WEATHER_PRESSURE).toDouble();

    weather.humidity = obj.value(KEY_WEATHER_HUMIDITY).toDouble();

    QJsonArray weatherDescArray = obj.value(KEY_WEATHER_LIST).toArray();
    for (QJsonValueRef value: weatherDescArray)
    {
        QJsonObject weatherItem = value.toObject();

        QJsonValue idValue = weatherItem.value(KEY_WEATHER_LIST_ID);
        QJsonValue descriptionValue = weatherItem.value(KEY_WEATHER_LIST_DESCRIPTION);
        if (!idValue.isUndefined() && !descriptionValue.isUndefined())
        {
            weather.weatherDescriptionById.insert(idValue.toInt(), descriptionValue.toString());
        }
    }

    return weather;
}

QJsonArray WeatherData::weatherArray() const
{
    QJsonArray array;

    if (hasData() && mJson.isObject())
    {
        QJsonObject obj = mJson.object();

        if (obj.contains(KEY_WEATHER_DATA_LIST))
        {
            array = obj.value(KEY_WEATHER_DATA_LIST).toArray();
        }
    }

    return array;
}
