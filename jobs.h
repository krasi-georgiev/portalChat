#include <QAbstractListModel>
#include <QStringList>

class JobsModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum jobsRoles {
        idRole = Qt::UserRole + 1,
        titleRole,
        companyRole,

    };

    JobsModel(QObject *parent = 0);
//![1]

    void addJob(const QMap<QString, QString> &profile);

    int rowCount(const QModelIndex & parent = QModelIndex()) const;

    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
    Q_INVOKABLE void reload(QString cookie);
protected:
    QHash<int, QByteArray> roleNames() const;
private:
    QList<QMap<QString,QString>> m_jobs;

signals:
   void dataChanged();
//![2]
};
//![2]


