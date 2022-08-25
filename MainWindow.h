//---------------------------------
#ifndef MAINWINDOW_H
#define MAINWINDOW_H
//---------------------------------
#include <QMainWindow>
#include <QNetworkReply>
#include <QNetworkAccessManager>
//---------------------------------
namespace Ui { class MainWindow; }
//---------------------------------

class MainWindow : public QMainWindow {

    Q_OBJECT

    QNetworkAccessManager* HttpManager;

public:

    explicit MainWindow( QWidget* parent = Q_NULLPTR );
    ~MainWindow();

private:

    Ui::MainWindow* ui;

private slots:

    void httpRequestLogin();
    void httpRequestStartTicker();
    void httpRequestStopTicker();

    void getResponse( QNetworkReply* response );
};
//---------------------------------------------------------------------------------------------------

#endif // MAINWINDOW_H
