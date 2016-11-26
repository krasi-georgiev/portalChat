#ifndef CONTACTS_H
#define CONTACTS_H

#include <QList>
#include <QVariant>
#include <QAbstractItemModel>
#include <QModelIndex>
#include <QtNetwork>

class Contact
{
public:
    explicit Contact(const QList<QVariant> &data, Contact *parentItem = 0);
    ~Contact();

    void appendChild(Contact *child);

    Contact *child(int row);
    int childCount() const;
    int columnCount() const;
    QVariant data(int column) const;
    int row() const;
    Contact *parentItem();

private:
    QList<Contact*> m_childItems;
    QList<QVariant> m_itemData;
    Contact *m_parentItem;
};

class Contacts : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit Contacts(QObject *parent = 0);
    ~Contacts();

    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    QModelIndex parent(const QModelIndex &index) const Q_DECL_OVERRIDE;
    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    void setData(QNetworkReply *r);
private:

    Contact *rootItem;
};
//! [0]


#endif // CONTACTS_H
