
#include "profiles.h"

Profile::Profile(const QString &name, const QString &id)
    : m_id(id), m_name(name)
{
}

QString Profile::id() const
{
    return m_id;
}

QString Profile::name() const
{
    return m_name;
}

ProfilesModel::ProfilesModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

void ProfilesModel::addProfile(const Profile &profile)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_profiles << profile;
    endInsertRows();
}

int ProfilesModel::rowCount(const QModelIndex & parent) const {
    Q_UNUSED(parent);
    return m_profiles.count();
}

QVariant ProfilesModel::data(const QModelIndex & index, int role) const {
    if (index.row() < 0 || index.row() >= m_profiles.count())
        return QVariant();

    const Profile &profile = m_profiles[index.row()];
    if (role == IdRole)
        return profile.id();
    else if (role == NameRole)
        return profile.name();
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

