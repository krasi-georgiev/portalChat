//#include <QGuiApplication>
#include <QApplication>
#include <QQmlApplicationEngine>
//#include <QItemSelectionModel>
#include <QtQml>
//#include <QQmlContext>
#include <QtWebView>
//#include <QTreeView>
#include <profiles.h>
//#include <QtWebEngine>

//TODO features

// all new chats shows under job - unasigned
// the technician reads the message and clicks the job that this is relevant to -
// the job has a button - move selected text to this job and continue discussion here

// right click the job - mute this job chat - technicians can still message the technician using the hashtag - #chris - ...please have a look a this

// click the user name to open all recent jobs(last 40 days) he is subscribbed to

// from messenger the user will be presented a selection to - For new support ticket click here ,  or select an existing ticket - and it will show all jobs from the last 40 days
// click user -> show all jobs for assigned to this user + one job RANDOM -> select a job to continue discussing a specific job

// how to move messages from the RANDOM job to a specific job ?
// maybe when a user start a conversation it is given a selectio - start new ticket or select an existing ticket

// when creating new job from the messenger or the app - how to set company and subscribed users???

//    show user presence from facebook
//    file uploads ?

//  support hashtags (autocomplete name) - to force a notify even when a technician has mutted the job chat notification.

// the app will have 2 tabs - portal and chat - use the portal for full manipulation and login and the chat just for chat -
// the chat will query the api using the cookies set when logged in with the portal tab

int main(int argc, char *argv[])
{

    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QtWebView::initialize();

    qmlRegisterType<ProfilesModel>("profiles", 1, 0, "ProfilesModel");



    QQmlApplicationEngine engine;
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



