//#include <QGuiApplication>
#include <QApplication>
#include <QSettings>
#include <QtQml>
//#include <QQmlContext>
#include <QtWebView>
//#include <QTreeView>
#include <profiles.h>
#include <jobs.h>
//#include <QtWebEngine>


/*
TODO features


use rowLayout instead of a split view so we can use it in a phone - sort of fluid layout

show user presence from facebook
file uploads ?


App workflow and views
    Jobs - all from the portal
        when sellected shows all attached user and option to add or remove user
        how to mute conversation ? remove the technicians or set some param to mute ?

Job request from a new user
    register the user on the portal if doesn't exist.
    create a new job attached to the Vip-Consult company - so we can add bills and generate anonymous invoices
    add the user to the job so he receive notifications when we post an update


Job request from an existing user
    send auto message - a selection to - For new support ticket click here ,  or select an existing ticket - and it will show all jobs from the last 10 days
    select an existing chat topic or enter a title to start a new one.

JOB company assignment
    when started put in a vip consult
    right click to assigns to another company
    need to allow users outside the company to be attached to any job
        check the security complication ????

Job notifications
    no more email notifications - will use the app
    right click to mute - force a message notification with the hashtag - #chris  ...please have a look a this
    All technicians receive a notification and can right click to mute if it doesn't concern them
        later can filter which technicians receive notification by the page Id - like support channels





Merge jobs
    when the user decides to start a new job but there was already an existing job then can merge



*/
int main(int argc, char *argv[])
{

    QSettings settings("portalChat", "Vip Consult");
    settings.setValue("portalUrl", "https://dev.portal.vip-consult.co.uk/");
    settings.setValue("portalApi", "https://dev.portal.vip-consult.co.uk/webhook/messenger/v1/");
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QtWebView::initialize();

    qmlRegisterType<ProfilesModel>("profiles", 1, 0, "ProfilesModel");
    qmlRegisterType<JobsModel>("jobs", 1, 0, "JobsModel");



    QQmlApplicationEngine engine;


    QQmlContext *context = engine.rootContext();
    context->setContextProperty("portalUrl", settings.value("portalUrl").toString());
//    engine.rootContext().setContextProperty("url", settings.value("url").toString());

//    qDebug() << "Property value:" << QQmlProperty::read(object, "url").toString();

      engine.load(QUrl(QStringLiteral("qrc:/main.qml")));



//    QObject* window = getQmlWindow("appWindow");


//    QObject *www = engine.findChild<QObject*>("www");
    return app.exec();


//    ProfilesModel model;

//    QQuickView view;
//    view.setResizeMode(QQuickView::SizeRootObjectToView);
//    QQmlContext *ctxt = view.rootContext();
//    ctxt->setContextProperty("TechniciansModel", &model);

//    view.setSource(QUrl("qrc:main.qml"));
//    view.show();

//    view.showMaximized();

//    return app.exec();
}



