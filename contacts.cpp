#include "Contacts.h"
#include <QtNetwork>


//! [0]
Contact::Contact(const QList<QVariant> &data, Contact *parent)
{
    m_parentItem = parent;
    m_itemData = data;
}
//! [0]

//! [1]
Contact::~Contact()
{
    qDeleteAll(m_childItems);
}
//! [1]

//! [2]
void Contact::appendChild(Contact *item)
{
    m_childItems.append(item);
}
//! [2]

//! [3]
Contact *Contact::child(int row)
{
    return m_childItems.value(row);
}
//! [3]

//! [4]
int Contact::childCount() const
{
    return m_childItems.count();
}
//! [4]

//! [5]
int Contact::columnCount() const
{
    return m_itemData.count();
}
//! [5]

//! [6]
QVariant Contact::data(int column) const
{
    return m_itemData.value(column);
}
//! [6]

//! [7]
Contact *Contact::parentItem()
{
    return m_parentItem;
}
//! [7]

//! [8]
int Contact::row() const
{
    if (m_parentItem)
        return m_parentItem->m_childItems.indexOf(const_cast<Contact*>(this));

    return 0;
}
//! [8]

/*
    Contacts.cpp

    Provides a simple tree model to show how to create and use hierarchical
    models.
*/

#include "Contacts.h"

#include <QStringList>
#include <Qfile>
#include <QtDebug>


//! [0]
Contacts::Contacts(QObject *parent)
    : QAbstractItemModel(parent)
{
    QList<QVariant> rootData;
    rootData<<"Name";
    rootItem = new Contact (rootData);
    QList<Contact*> parents;

    parents.append(rootItem);

    QList<QVariant> t;
    t<<"Technicians";
    Contact *p=new Contact(t, parents.last());
    parents.last()->appendChild(p);

    parents.append(parents.last()->child(parents.last()->childCount()-1));

    QList<QVariant> u;
    u << "Users";
    parents.pop_back();
    parents.last()->appendChild(new Contact(u, parents.last()));
}
//! [0]

//! [1]
Contacts::~Contacts()
{
    delete rootItem;
}
//! [1]

//! [2]
int Contacts::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return static_cast<Contact*>(parent.internalPointer())->columnCount();
    else
        return rootItem->columnCount();
}
//! [2]

//! [3]
//!
QVariant Contacts::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole)
        return QVariant();

    Contact *item = static_cast<Contact*>(index.internalPointer());

    return item->data(index.column());
}
//! [3]


//! [5]
QVariant Contacts::headerData(int section, Qt::Orientation orientation,
                               int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return rootItem->data(section);

    return QVariant();
}
//! [5]

//! [6]
QModelIndex Contacts::index(int row, int column, const QModelIndex &parent)
            const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    Contact *parentItem;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<Contact*>(parent.internalPointer());

    Contact *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}
//! [6]

//! [7]
QModelIndex Contacts::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    Contact *childItem = static_cast<Contact*>(index.internalPointer());
    Contact *parentItem = childItem->parentItem();

    if (parentItem == rootItem)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}
//! [7]

//! [8]
int Contacts::rowCount(const QModelIndex &parent) const
{
    Contact *parentItem;
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<Contact*>(parent.internalPointer());

    return parentItem->childCount();
}
//! [8]

void Contacts::setData(QNetworkReply *r){

    QString strReply = (QString)r->readAll() ;
    QJsonParseError parseError;

    QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8(),&parseError);
    QJsonObject jsonObj = jsonResponse.object();

    QVariant profiles=jsonObj.toVariantMap()["profiles"];

    beginResetModel();


    for (const QVariant &row : profiles.value<QSequentialIterable>()) {
        QList<QVariant> t1;
        t1 << row.toMap()["first_name"];
        Contact *item=new Contact(t1, rootItem->child(1));
        rootItem->child(1)->appendChild(item);
    }
    endResetModel();
}

//void Contacts::addUser(){
//    QList<QVariant> u1;
//    u1 << "David";
//    parents.last()->appendChild(new Contact(u1, parents.last()));
//}


//void Contacts::setupModelData()
//{

//}
