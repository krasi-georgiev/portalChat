#include <QAbstractListModel>
#include <QStringList>

////![0]
//class Profile
//{
//public:
//    Profile(const QString &name, const QString &id);
////![0]

//    QString id() const;
//    QString name() const;

//private:
//    QString m_id;
//    QString m_name;
////![1]
//};

class ProfilesModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum ProfilesRoles {
        IdRole = Qt::UserRole + 1,
        NameRole
    };

    ProfilesModel(QObject *parent = 0);
    bool isLogged;
//![1]

    void addProfile(const QMap<QString, QString> &profile);

    int rowCount(const QModelIndex & parent = QModelIndex()) const;

    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
    Q_INVOKABLE void reload(QString cookie);
protected:
    QHash<int, QByteArray> roleNames() const;
private:
    QList<QMap<QString,QString>> m_profiles;
//![2]
};
//![2]


