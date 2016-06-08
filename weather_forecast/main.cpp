#include <QCoreApplication>

#include <QCommandLineOption>
#include <QCommandLineParser>

#include "weatherforecastrequest.h"
#include "weatherdata.h"

#include <QTextStream>
#include <QNetworkProxy>

void printResult(QByteArray data)
{
    WeatherData weatherData(data);

    QTextStream out(stdout);
    out << endl;

    if (!weatherData.hasData())
    {
        out << QLatin1String("Invalid weather data.") << endl;
    }

    for (int index = 0; index < weatherData.weatherItemsCount(); ++index)
    {
        Weather weather = weatherData.getWeather(index);
        out << QString("-= %1 =-").arg(weather.date.toString()) << endl;
        out << "===================" << endl;
        out << QString("Day: %1 C   Night: %2 C")
               .arg(weather.dayTemperature, 2)
               .arg(weather.nightTemperature, 2) << endl;
        out << QString("Pressure: %1 hPa").arg(weather.pressure) << endl;
        out << QString("Humidity: %1 %").arg(weather.humidity) << endl;
        out << QStringList(weather.weatherDescriptionById.values()).join(";") << endl;
        out << endl;
    }
}

const QLatin1String APP_NAME("WeatherApp");
const QLatin1String APP_VERSION("1.0");

const QLatin1String OPTION_CITY_SHORT("c");
const QLatin1String OPTION_CITY_LONG("city");
const QLatin1String OPTION_CITY_DESCRIPTION("City name (country code could be appended after comma)");
const QLatin1String OPTION_CITY_NAME("city");

const QLatin1String OPTION_LOCALE_SHORT("l");
const QLatin1String OPTION_LOCALE_LONG("locale");
const QLatin1String OPTION_LOCALE_DESCRIPTION("Name of the locale");
const QLatin1String OPTION_LOCALE_NAME("l");
const QLatin1String OPTION_LOCALE_DEFAULT("ua");

const QLatin1String OPTION_DAYS_SHORT("d");
const QLatin1String OPTION_DAYS_LONG("days");
const QLatin1String OPTION_DAYS_DESCRIPTION("Number of days");
const QLatin1String OPTION_DAYS_NAME("days");
const QLatin1String OPTION_DAYS_DEFAULT("days");

const QLatin1String OPTION_PROXY_HOST_LONG("host");
const QLatin1String OPTION_PROXY_HOST_DESCRIPTION("Proxy host");
const QLatin1String OPTION_PROXY_HOST_NAME("host");

const QLatin1String OPTION_PROXY_PORT_LONG("port");
const QLatin1String OPTION_PROXY_PORT_DESCRIPTION("Proxy port");
const QLatin1String OPTION_PROXY_PORT_NAME("port");

const QLatin1String OPTION_PROXY_USER_LONG("user");
const QLatin1String OPTION_PROXY_USER_DESCRIPTION("Proxy username");
const QLatin1String OPTION_PROXY_USER_NAME("user");

const QLatin1String OPTION_PROXY_PASS_LONG("pass");
const QLatin1String OPTION_PROXY_PASS_DESCRIPTION("Proxy password");
const QLatin1String OPTION_PROXY_PASS_NAME("pass");

int main(int argc, char *argv[])
{
    QCoreApplication application(argc, argv);
    application.setApplicationName(APP_NAME);
    application.setApplicationVersion(APP_VERSION);

    QCommandLineOption cityOption({OPTION_CITY_SHORT, OPTION_CITY_LONG},
        OPTION_CITY_DESCRIPTION, OPTION_CITY_NAME);

    QCommandLineOption localeOption({OPTION_LOCALE_SHORT, OPTION_LOCALE_LONG},
        OPTION_LOCALE_DESCRIPTION, OPTION_LOCALE_NAME, OPTION_LOCALE_DEFAULT);

    QCommandLineOption daysOption({OPTION_DAYS_SHORT, OPTION_DAYS_LONG},
        OPTION_DAYS_DESCRIPTION, OPTION_DAYS_NAME, OPTION_DAYS_DEFAULT);

    QCommandLineOption proxyHostOption(OPTION_PROXY_HOST_LONG,
        OPTION_PROXY_HOST_DESCRIPTION, OPTION_PROXY_HOST_NAME);

    QCommandLineOption proxyPortOption(OPTION_PROXY_PORT_LONG,
        OPTION_PROXY_PORT_DESCRIPTION, OPTION_PROXY_PORT_NAME);

    QCommandLineOption proxyUserOption(OPTION_PROXY_USER_LONG,
        OPTION_PROXY_USER_DESCRIPTION, OPTION_PROXY_USER_NAME);

    QCommandLineOption proxyPassOption(OPTION_PROXY_PASS_LONG,
        OPTION_PROXY_PASS_DESCRIPTION, OPTION_PROXY_PASS_NAME);

    QCommandLineParser commandLineParser;
    commandLineParser.addOptions({cityOption, localeOption, daysOption,
        proxyHostOption, proxyPortOption, proxyUserOption, proxyPassOption});
    commandLineParser.addVersionOption();
    commandLineParser.setApplicationDescription("Retrieves weather forecast up to next 16 days.");
    commandLineParser.process(application);

    if (!commandLineParser.isSet(cityOption))
    {
        commandLineParser.showHelp();
        return -1;
    }

    QNetworkProxy proxy;
    if (commandLineParser.isSet(proxyHostOption)
        && commandLineParser.isSet(proxyPortOption)
        && commandLineParser.isSet(proxyUserOption)
        && commandLineParser.isSet(proxyPassOption))
    {
        proxy.setType(QNetworkProxy::HttpProxy);
        proxy.setHostName(commandLineParser.value(proxyHostOption));
        proxy.setPort(commandLineParser.value(proxyPortOption).toInt());
        proxy.setUser(commandLineParser.value(proxyUserOption));
        proxy.setPassword(commandLineParser.value(proxyPassOption));
        QNetworkProxy::setApplicationProxy(proxy);
    }

    WeatherForecastRequest request;
    request.setCityName(commandLineParser.value(cityOption));
    request.setLanguage(commandLineParser.value(localeOption));
    request.setDaysCount(commandLineParser.value(daysOption).toInt());
    QObject::connect(&request, &WeatherForecastRequest::finished, &printResult);
    QObject::connect(&request, &WeatherForecastRequest::finished,
        &application, &QCoreApplication::quit);
    request.slotSend();

    return application.exec();
}
