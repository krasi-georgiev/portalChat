
#include "jobs.h"
#include <QSettings>

#include <QNetworkAccessManager>
#include <QJsonParseError>
#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkCookieJar>
#include <QNetworkCookie>
#include <QNetworkReply>
#include <QJsonObject>

JobsModel::JobsModel(QObject *parent)
    : QAbstractListModel(parent){
}

void JobsModel::addJob(const QMap<QString,QString> &job)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_jobs<<job;
    endInsertRows();
}

void JobsModel::reload(QString cookie)
{
    QSettings settings("portalChat", "Vip Consult");
    QUrl url(settings.value("portalApi").toString()+"job");
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

            QVariant jobs=jsonObj.toVariantMap()["jobs"];

            beginResetModel();
            m_jobs.clear();
            endResetModel();

            if(!jobs.isNull()){
                for (const QVariant &row : jobs.value<QSequentialIterable>()) {
                    QMap<QString,QString> p;
                    p["title"]=row.toMap()["title"].toString();
                    p["id"]=row.toMap()["id_job"].toString();
                    p["company"]=row.toMap()["company_name"].toString();
                    addJob(p);
                }
            }
            dataChanged();
        }
    );
}

int JobsModel::rowCount(const QModelIndex & parent) const {
    Q_UNUSED(parent);
    return m_jobs.count();
}

QVariant JobsModel::data(const QModelIndex & index, int role) const {
    if (index.row() < 0 || index.row() >= m_jobs.count())
        return QVariant();

    const QMap<QString,QString> &job = m_jobs[index.row()];
    if (role == idRole)
        return job["id"];
    else if (role == titleRole)
        return job["title"];
    else if (role == companyRole)
        return job["company"];
    return QVariant();
}
//![0]
QHash<int, QByteArray> JobsModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[idRole] = "id";
    roles[titleRole] = "title";
    roles[companyRole] = "company";
    return roles;
}

//![0]

