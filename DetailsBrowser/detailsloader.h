#ifndef DELAILSLOADER_H
#define DELAILSLOADER_H

#include <QObject>
#include <QList>

class Detail;
class QJsonObject;
class DetailsModel;

class DetailsLoader : public QObject
{
    Q_OBJECT
public:
    explicit DetailsLoader(QObject *parent = nullptr);
    ~DetailsLoader();

    void setFileName(const QString &path);

    QList<Detail *> details() const;

    DetailsModel *detailsModel() const;
    void setDetailsModel(DetailsModel *detailsModel);

private:
    void load();

    Detail *parseDetail(const QJsonObject &obj);

private:
    DetailsModel* mDetailsModel;
    QList<Detail *>  mListDetails;
    QString mPath;
};

#endif // DELAILSLOADER_H
