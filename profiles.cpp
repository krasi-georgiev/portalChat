
#include "profiles.h"
#include <QNetworkAccessManager>
#include <QJsonParseError>
#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkCookieJar>
#include <QNetworkCookie>
#include <QNetworkReply>
#include <QJsonObject>

ProfilesModel::ProfilesModel(QObject *parent)
    : QAbstractListModel(parent){

}

void ProfilesModel::addProfile(const QMap<QString,QString> &profile)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_profiles<<profile;
    endInsertRows();
}

void ProfilesModel::reload(QString cookie)
{
    QUrl url("https://dev.portal.vip-consult.co.uk/webhook/messenger/v1/profile");

    QNetworkAccessManager *manager = new QNetworkAccessManager();
    QNetworkCookieJar *jar = new QNetworkCookieJar(manager);

    QList<QNetworkCookie> cookies({QNetworkCookie("PHPSESSID",cookie.toUtf8())});

    jar->setCookiesFromUrl(cookies,url);
    QNetworkRequest request(url);
    manager->setCookieJar(jar);
    request.setHeader(QNetworkRequest::ContentTypeHeader, QString("application/json"));

    manager->get(request);
    QObject::connect(manager, &QNetworkAccessManager::finished,[=](QNetworkReply *r) {
            QString strReply = (QString)r->readAll() ;
            QJsonParseError parseError;

            QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8(),&parseError);
            QJsonObject jsonObj = jsonResponse.object();

            QVariant profiles=jsonObj.toVariantMap()["profiles"];

            if(!profiles.isNull()){
                qDebug()<<cookie;

                for (const QVariant &row : profiles.value<QSequentialIterable>()) {
                    QMap<QString,QString> p;
                    p["name"]=row.toMap()["first_name"].toString();
                    p["id"]=row.toMap()["id_profile_identity"].toString();
                    addProfile(p);
                }
            }
            else{
//                qDebug()<<cookie;
                beginResetModel();
                m_profiles.clear();
                endResetModel();
            }
        }
    );

    //    beginInsertRows(QModelIndex(), rowCount(), rowCount());
//    endInsertRows();
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

