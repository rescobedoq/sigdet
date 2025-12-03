#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class Sidebar; // declaración anticipada

class MainWindow : public QMainWindow
{
    Q_OBJECT
signals:
    void logoutRequested();
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void resetToDefaultView();
private:
    Sidebar *sidebar;
    Ui::MainWindow *ui;
    QStackedWidget *stackedWidget; // contendrá las vistas dinámicas

private slots:
    void onMenuSelected(const QString &menuName);
};
#endif // MAINWINDOW_H
