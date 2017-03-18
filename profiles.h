#include <QAbstractListModel>
#include <QStringList>

class ProfilesModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum ProfilesRoles {
        idRole = Qt::UserRole + 1,
        nameRole
    };

    ProfilesModel(QObject *parent = 0);
//![1]

    void addProfile(const QMap<QString, QString> &profile);

    int rowCount(const QModelIndex & parent = QModelIndex()) const;

    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
    Q_INVOKABLE void reload(QString cookie, QString endpoint);
protected:
    QHash<int, QByteArray> roleNames() const;
private:
    QList<QMap<QString,QString>> m_profiles;

signals:
   void dataChanged();
//![2]
};
//![2]


