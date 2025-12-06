#ifndef LOGINWINDOWVIEW_H
#define LOGINWINDOWVIEW_H

#include <QWidget>

class QLineEdit;
class QPushButton;
class QLabel;

class LoginWindow : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

signals:
    void loginSuccessful();

private slots:
    void onLoginClicked();

private:
    QLineEdit *txtUser;
    QLineEdit *txtPassword;
    QLabel *lblMessage;
};

#endif // LOGINWINDOWVIEW_H
