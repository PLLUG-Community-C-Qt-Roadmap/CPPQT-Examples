#ifndef DETAILSMODEL_H
#define DETAILSMODEL_H

#include <QAbstractItemModel>

class Detail;

class DetailsModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    enum DetailsRole {
        DetailTypeRole = Qt::UserRole + 1,
        DetailModelRole
    };

    QHash<int, QByteArray> roleNames() const override;

    explicit DetailsModel(QObject *parent = 0);

    // Basic functionality:
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    void setDetailsList(QList<Detail *> listDetails);

    Q_INVOKABLE void debug();

private:
    QList<Detail *> mListDetails;
};

#endif // DETAILSMODEL_H
