//---------------------------------
#include <QDebug>
#include <QUrlQuery>
#include <QJsonObject>
#include <QJsonDocument>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
//---------------------------------
#include "MainWindow.h"
#include "ui_MainWindow.h"
//---------------------------------

MainWindow::MainWindow( QWidget* parent ) : QMainWindow( parent ),
                                            ui(new Ui::MainWindow) {

    ui->setupUi( this );

    HttpManager = new QNetworkAccessManager( this );

    connect( ui->loginButton, &QPushButton::clicked , this, &MainWindow::httpRequestLogin       );
    connect( ui->startButton, &QPushButton::clicked , this, &MainWindow::httpRequestStartTicker );
    connect( ui->stopButton , &QPushButton::clicked , this, &MainWindow::httpRequestStopTicker  );

    connect( HttpManager, &QNetworkAccessManager::finished, this, &MainWindow::getResponse );
}
//---------------------------------------------------------------------------------------------------

MainWindow::~MainWindow() {

    delete ui;
}
//---------------------------------------------------------------------------------------------------

void MainWindow::httpRequestLogin() {

    QNetworkRequest request( QUrl("http://localhost:8080/login") );

    QJsonObject jsonBody;
    jsonBody.insert("login"   , QJsonValue::fromVariant("admin"));
    jsonBody.insert("password", QJsonValue::fromVariant("admin"));

    request.setHeader( QNetworkRequest::ContentTypeHeader  , "application/json" );

    HttpManager->post(request, QJsonDocument(jsonBody).toJson(QJsonDocument::Compact));

    qDebug() << "Send request: Login";
}
//---------------------------------------------------------------------------------------------------

void MainWindow::httpRequestStartTicker() {

    QNetworkRequest request( QUrl("http://localhost:8080/ticker/start") );
    HttpManager->post(request, QByteArray());

    qDebug() << "Send request: Start Ticker";
}
//---------------------------------------------------------------------------------------------------

void MainWindow::httpRequestStopTicker() {

    QNetworkRequest request( QUrl("http://localhost:8080/ticker/stop") );
    HttpManager->post(request, QByteArray());

    qDebug() << "Send request: Stop Ticker";
}
//---------------------------------------------------------------------------------------------------

void MainWindow::getResponse( QNetworkReply* response ) {

    qDebug() << "Get response";

    if( response->error() != QNetworkReply::NoError ) {

        qDebug() << response->errorString();
    } else {

        //qDebug() << "Sucecss request. Get status: " << response->error();
    }
}
//---------------------------------------------------------------------------------------------------

