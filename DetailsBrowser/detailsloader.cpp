#include "detailsloader.h"

#include "detail.h"
#include "detailsmodel.h"

#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

DetailsLoader::DetailsLoader(QObject *parent)
    : QObject (parent),
      mDetailsModel{new DetailsModel(this)}
{

}

DetailsLoader::~DetailsLoader()
{
    qDeleteAll(mListDetails);
}

void DetailsLoader::setFileName(const QString &path)
{
    mPath = path;
    load();
}

QList<Detail *> DetailsLoader::details() const
{
    return  mListDetails;
}

void DetailsLoader::load()
{
    qDeleteAll(mListDetails);
    mListDetails.clear();

    QFile file(mPath);
    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug("Error: Could not open the file");
    }
    QByteArray data = file.readAll();
    file.close();

    QJsonParseError err;
    QJsonDocument doc = QJsonDocument::fromJson(data, &err);
    if (err.error == QJsonParseError::NoError && doc.isObject())
    {
        QJsonObject o = doc.object();
        QJsonValue value = o.value("details");
        if (value.isArray())
        {
            QJsonArray detailsArray = value.toArray();
            for (int i = 0; i < detailsArray.count(); i++)
            {
                QJsonValue nextValue = detailsArray.at(i);
                if (nextValue.isObject())
                {
                    QJsonObject nextObject = nextValue.toObject();
                    Detail *detail = parseDetail(nextObject);
                    if (detail)
                    {
                        mListDetails.append(detail);
                    }
                }
            }
            mDetailsModel->setDetailsList(mListDetails);
        }
    }
}

Detail *DetailsLoader::parseDetail(const QJsonObject &obj)
{
    Detail *rDetail = nullptr;

    QString type = obj.value("type").toString();
    QString model = obj.value("model").toString();

    if (!type.isEmpty() && !model.isEmpty())
    {
        rDetail = new Detail(type, model);
    }

    return  rDetail;
}

DetailsModel *DetailsLoader::detailsModel() const
{
    return mDetailsModel;
}

void DetailsLoader::setDetailsModel(DetailsModel *detailsModel)
{
    mDetailsModel = detailsModel;
}
