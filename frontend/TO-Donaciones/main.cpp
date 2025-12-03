#include "mainwindow.h"
#include <QFile>
#include <QApplication>
#include "loginwindowView.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    // 🔹 Cargar el archivo QSS
    QFile styleFile(":/styles/globalStyles/overflow.qss");  // si lo agregas a recursos .qrc

    if (styleFile.open(QFile::ReadOnly | QFile::Text)) {
        QTextStream stream(&styleFile);
        QString styleSheet = stream.readAll();
        a.setStyleSheet(styleSheet);
        styleFile.close();
    }

    LoginWindow login;
    MainWindow mainWindow;

    QObject::connect(&login, &LoginWindow::loginSuccessful, [&]() {
        login.hide();
        mainWindow.show();
        mainWindow.resetToDefaultView();
    });

    QObject::connect(&mainWindow, &MainWindow::logoutRequested, [&]() {
        mainWindow.hide();
        login.show();
    });

    login.show();
    return a.exec();
}
