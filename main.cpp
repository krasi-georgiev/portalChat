#include <QGuiApplication>
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QStandardItemModel>
#include <QItemSelectionModel>
#include <QtQml>
#include <QQuickView>
#include <QTreeView>
int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
//    QApplication app(argc, argv);

    QStandardItemModel model;
    QStandardItem *parentItem = model.invisibleRootItem();
    for (int i = 0; i < 4; ++i) {
        QStandardItem *item = new QStandardItem(QString("item %0").arg(i));
        parentItem->appendRow(item);
        parentItem = item;

    }
//    model.appendRow(parentItem);
//    QModelIndex p=model.index(0,0);
//    QModelIndex p1=model.index(0,0,p);
//    qDebug() << model.data(model.index(0,0,p)).toString();
//    qDebug() << model.data(model.index(0,0,p1)).toString();

//    QTreeView v;
//    v.setModel(&model);
//    v.show();


    QQuickView view;
    QQmlContext *ctxt = view.rootContext();
    ctxt->setContextProperty("modelC", &model);

    view.setSource(QUrl("qrc:main.qml"));
    view.show();

    return app.exec();
}
