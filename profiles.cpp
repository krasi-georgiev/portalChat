
#include "profiles.h"
#include <QNetworkAccessManager>
#include <QJsonParseError>
#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonObject>

//Profile::Profile(const QString &name, const QString &id)
//    : m_id(id), m_name(name)
//{
//}

//QString Profile::id() const
//{
//    return m_id;
//}

//QString Profile::name() const
//{
//    return m_name;
//}

ProfilesModel::ProfilesModel(QObject *parent)
    : QAbstractListModel(parent)
{

    QNetworkAccessManager *manager = new QNetworkAccessManager();

    QNetworkRequest request(QUrl("https://portal.vip-consult.co.uk/webhook/messenger/v1/profile"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, QString("application/json"));

    manager->get(request);
    QObject::connect(manager, &QNetworkAccessManager::finished,[=](QNetworkReply *r) {

                        QString strReply = (QString)r->readAll() ;
                        QJsonParseError parseError;

                        QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8(),&parseError);
                        QJsonObject jsonObj = jsonResponse.object();

                        QVariant profiles=jsonObj.toVariantMap()["profiles"];


                        for (const QVariant &row : profiles.value<QSequentialIterable>()) {
//                            row.toMap()["first_name"],row.toMap()["id_profile"]
                            QMap<QString,QString> p;
                            p["name"]=row.toMap()["first_name"].toString();
                            p["id"]=row.toMap()["id_profile_identity"].toString();
                            this->addProfile(p);
                        }


                     }
    );
}

void ProfilesModel::addProfile(const QMap<QString,QString> &profile)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_profiles<<profile;
    endInsertRows();
}

int ProfilesModel::rowCount(const QModelIndex & parent) const {
    Q_UNUSED(parent);
    return m_profiles.count();
}

QVariant ProfilesModel::data(const QModelIndex & index, int role) const {
    if (index.row() < 0 || index.row() >= m_profiles.count())
        return QVariant();

    const QMap<QString,QString> &profile = m_profiles[index.row()];
    if (role == IdRole)
        return profile["id"];
    else if (role == NameRole)
        return profile["name"];
    return QVariant();
}

//![0]
QHash<int, QByteArray> ProfilesModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[IdRole] = "id";
    roles[NameRole] = "name";
    return roles;
}
//![0]

