#include "detailsmodel.h"

#include "detail.h"

QHash<int, QByteArray> DetailsModel::roleNames() const
{
    QHash<int, QByteArray> rolesHash;
    rolesHash.insert(DetailTypeRole, "type");
    rolesHash.insert(DetailModelRole, "model");
    return rolesHash;
}

DetailsModel::DetailsModel(QObject *parent)
    : QAbstractItemModel(parent)
{
}

QModelIndex DetailsModel::index(int row, int column, const QModelIndex &parent) const
{
    return createIndex(row, column);
}

QModelIndex DetailsModel::parent(const QModelIndex &index) const
{
    return QModelIndex();
}

int DetailsModel::rowCount(const QModelIndex &parent) const
{
    return mListDetails.count();
    // FIXME: Implement me!
}

int DetailsModel::columnCount(const QModelIndex &parent) const
{
    return 0;
}

QVariant DetailsModel::data(const QModelIndex &index, int role) const
{
    QVariant result;
    if (!index.isValid())
        return QVariant();

    Detail* detail = mListDetails[index.row()];

    switch (role) {
        case DetailTypeRole:
            result = detail->type();
        break;
        case DetailModelRole:
            result = detail->model();
        break;
    }

    // FIXME: Implement me!
    return result;
}

void DetailsModel::setDetailsList(QList<Detail *> listDetails)
{
    mListDetails = listDetails;
}
#include <QDebug>
void DetailsModel::debug()
{
    qDebug() << "It's alive!";
}
