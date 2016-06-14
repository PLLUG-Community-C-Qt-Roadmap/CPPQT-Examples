#include "detail.h"
#include "detailsmodel.h"

Detail::Detail(QString type, QString model)
    : mType{type}
    , mModel{model}
{
}

Detail::~Detail()
{
}

QString Detail::model() const
{
    return mModel;
}

void Detail::setModel(const QString &model)
{
    mModel = model;
}

QString Detail::type() const
{
    return mType;
}

void Detail::setType(const QString &type)
{
    mType = type;
}
