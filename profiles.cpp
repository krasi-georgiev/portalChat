
#include "profiles.h"
#include <QSettings>

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

void ProfilesModel::reload(QString cookie,QString endpoint)
{
    QSettings settings("portalChat", "Vip Consult");
    QUrl url(settings.value("portalApi").toString()+"profile"+endpoint);

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

            beginResetModel();
            m_profiles.clear();
            endResetModel();

            if(!profiles.isNull()){
                for (const QVariant &row : profiles.value<QSequentialIterable>()) {
                    QMap<QString,QString> p;
                    p["name"]=row.toMap()["first_name"].toString();
                    p["id"]=row.toMap()["id_profile_identity"].toString();
                    addProfile(p);
                }
            }
            dataChanged();

        }
    );
}

int ProfilesModel::rowCount(const QModelIndex & parent) const {
    Q_UNUSED(parent);
    return m_profiles.count();
}

QVariant ProfilesModel::data(const QModelIndex & index, int role) const {
    if (index.row() < 0 || index.row() >= m_profiles.count())
        return QVariant();

    const QMap<QString,QString> &profile = m_profiles[index.row()];
    if (role == idRole)
        return profile["id"];
    else if (role == nameRole)
        return profile["name"];
    return QVariant();
}
//![0]
QHash<int, QByteArray> ProfilesModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[idRole] = "id";
    roles[nameRole] = "name";
    return roles;
}

//![0]

