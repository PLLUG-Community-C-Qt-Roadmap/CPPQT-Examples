#ifndef DETAIL_H
#define DETAIL_H

#include <QString>

class Detail
{
public:
    Detail(QString type, QString model);
    ~Detail();

    QString model() const;
    void setModel(const QString &model);

    QString type() const;
    void setType(const QString &type);

private:
    QString mType;
    QString mModel;
};

#endif // DETAIL_H
