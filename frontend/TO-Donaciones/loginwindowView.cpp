#include "loginwindowView.h"
#include "databasemanagerController.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QFrame>
#include <QLineEdit>
#include <QPushButton>
#include <QPixmap>
#include <QSpacerItem>
#include <QSizePolicy>
#include <QApplication>
#include <QGraphicsDropShadowEffect>

LoginWindow::LoginWindow(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Inicio de Sesión - ONG Ayuda");
    resize(950, 600);
    setStyleSheet(R"(
        QWidget {
            font-family: 'Segoe UI';
            color: #1e293b;
        }
        QLineEdit {
            border: 1px solid #cbd5e1;
            border-radius: 8px;
            padding: 10px;
            font-size: 15px;
            background: #f8fafc;
        }
        QLineEdit:focus {
            border: 1px solid #2563eb;
            background: #ffffff;
        }
        QPushButton {
            background-color: #2563eb;
            color: white;
            font-weight: bold;
            font-size: 15px;
            border-radius: 8px;
            padding: 10px 0;
            margin-top: 10px;
        }
        QPushButton:hover {
            background-color: #1d4ed8;
        }
        QLabel#title {
            font-size: 26px;
            font-weight: 600;
            color: #0f172a;
        }
        QLabel#subtitle {
            font-size: 15px;
            color: #64748b;
        }
        QLabel#footer {
            font-size: 13px;
            color: #64748b;
        }
        QLabel#footer a {
            color: #2563eb;
            text-decoration: none;
        }
        QLabel#footer a:hover {
            text-decoration: underline;
        }
        QFrame#leftPanel {
            background-position: center;
            background-repeat: no-repeat;
            background-size: cover;
        }
        QFrame#overlay {
            background: qlineargradient(x1:0, y1:1, x2:0, y2:0, stop:0 rgba(0,0,0,0.6), stop:1 transparent);
        }
        QLabel#leftTitle {
            color: white;
            font-size: 34px;
            font-weight: bold;
        }
        QLabel#leftSubtitle {
            color: white;
            font-size: 17px;
        }
    )");

    // --- Layout principal (2 columnas) ---
    auto *mainLayout = new QHBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);
    // --- Panel Izquierdo (imagen con texto) ---
    QFrame *leftPanel = new QFrame;
    leftPanel->setObjectName("leftPanel");
    leftPanel->setStyleSheet(leftPanel->styleSheet() +
                             "QFrame#leftPanel { background-image: url(:/icons/ayudaImages/ong.png); }");

    QVBoxLayout *leftLayout = new QVBoxLayout(leftPanel);
    leftLayout->setContentsMargins(40, 40, 40, 40);
    leftLayout->addStretch();

    QLabel *leftTitle = new QLabel("ONG Ayuda");
    leftTitle->setObjectName("leftTitle");
    leftTitle->setStyleSheet("font-size: 34px; font-weight: 900; color: white;");

    // Efecto de sombra (suave y sutil)
    auto *shadowTitle = new QGraphicsDropShadowEffect;
    shadowTitle->setBlurRadius(10);          // qué tan difusa es la sombra
    shadowTitle->setOffset(2, 2);            // desplazamiento en x, y
    shadowTitle->setColor(QColor(0, 0, 0, 160)); // sombra negra semitransparente
    leftTitle->setGraphicsEffect(shadowTitle);

    // --- Subtítulo ---
    QLabel *leftSubtitle = new QLabel("Conectando donaciones, transformando vidas.");
    leftSubtitle->setObjectName("leftSubtitle");
    leftSubtitle->setStyleSheet("font-size: 17px; font-weight: 600; color: white;");

    // Efecto de sombra también en el subtítulo (más sutil)
    auto *shadowSubtitle = new QGraphicsDropShadowEffect;
    shadowSubtitle->setBlurRadius(8);
    shadowSubtitle->setOffset(1, 1);
    shadowSubtitle->setColor(QColor(0, 0, 0, 120));
    leftSubtitle->setGraphicsEffect(shadowSubtitle);

    leftLayout->addWidget(leftTitle);
    leftLayout->addWidget(leftSubtitle);
    leftLayout->addSpacing(20);

    // --- Panel Derecho (formulario login) ---
    QFrame *rightPanel = new QFrame;
    rightPanel->setStyleSheet("background-color: white;");

    QVBoxLayout *rightLayout = new QVBoxLayout(rightPanel);
    rightLayout->setContentsMargins(80, 60, 80, 60);
    rightLayout->setSpacing(14);
    rightLayout->setAlignment(Qt::AlignCenter);

    // --- Logo + Title layout ---
    QVBoxLayout *logoTitleLayout = new QVBoxLayout;
    logoTitleLayout->setSpacing(0);  // ✅ No hay separación entre logo y title
    logoTitleLayout->setContentsMargins(0, 0, 0, 0);
    logoTitleLayout->setAlignment(Qt::AlignCenter);

    // Logo circular
    QLabel *logo = new QLabel;
    QPixmap pix(":/icons/sidebar/logo.png");
    pix = pix.scaled(80, 80, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
    logo->setPixmap(pix);
    logo->setFixedSize(80, 80);
    logo->setStyleSheet("border-radius: 40px; overflow: hidden;");

    // Título principal
    QLabel *title = new QLabel("Bienvenido de nuevo");
    title->setObjectName("title");
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("font-size: 30px; font-weight: 700; color: #0f172a; margin-top: 8px;");

    // Agregar logo y title al layout interno
    logoTitleLayout->addWidget(logo, 0, Qt::AlignCenter);
    logoTitleLayout->addWidget(title);

    // Subtítulo
    QLabel *subtitle = new QLabel("Inicia sesión en tu cuenta para continuar");
    subtitle->setObjectName("subtitle");
    subtitle->setAlignment(Qt::AlignCenter);
    subtitle->setStyleSheet("font-size: 15px; color: #64748b; margin-bottom: 16px;");

    // --- Campo Usuario ---
    QVBoxLayout *userLayout = new QVBoxLayout;
    userLayout->setSpacing(2);
    QLabel *lblUser = new QLabel("Usuario");
    lblUser->setStyleSheet("font-size: 14px; font-weight: 500; color: #334155;");
    txtUser = new QLineEdit;
    txtUser->setPlaceholderText("Escribe tu usuario");
    userLayout->addWidget(lblUser);
    userLayout->addWidget(txtUser);

    // --- Campo Contraseña ---
    QVBoxLayout *passLayout = new QVBoxLayout;
    passLayout->setSpacing(2);
    QLabel *lblPass = new QLabel("Contraseña");
    lblPass->setStyleSheet("font-size: 14px; font-weight: 500; color: #334155; margin-top: 10px;");
    txtPassword = new QLineEdit;
    txtPassword->setPlaceholderText("Escribe tu contraseña");
    txtPassword->setEchoMode(QLineEdit::Password);
    passLayout->addWidget(lblPass);
    passLayout->addWidget(txtPassword);

    // --- Botón ---
    QPushButton *btnLogin = new QPushButton("Iniciar Sesión");
    btnLogin->setMinimumHeight(44);
    btnLogin->setCursor(Qt::PointingHandCursor);
    btnLogin->setStyleSheet(R"(
        QPushButton {
            background-color: #2563eb;
            color: white;
            font-weight: bold;
            font-size: 15px;
            border-radius: 8px;
            padding: 10px 0;
            margin-top: 10px;
        }
        QPushButton:hover {
            background-color: #1d4ed8;
        }
    )");
    // --- Mensaje de error ---
    lblMessage = new QLabel;
    lblMessage->setAlignment(Qt::AlignCenter);
    lblMessage->setStyleSheet("color: red; font-size: 13px;");

    // --- Agregar todos los widgets ---

    rightLayout->addLayout(logoTitleLayout);
    rightLayout->addWidget(subtitle);
    rightLayout->addSpacing(10);
    rightLayout->addLayout(userLayout);
    rightLayout->addLayout(passLayout);
    rightLayout->addWidget(btnLogin);
    rightLayout->addWidget(lblMessage);
    rightLayout->addStretch();

    // --- Combinar ambos paneles ---
    mainLayout->addWidget(leftPanel, 1);
    mainLayout->addWidget(rightPanel, 1);

    // --- Conexiones ---
    connect(btnLogin, &QPushButton::clicked, this, &LoginWindow::onLoginClicked);
}

LoginWindow::~LoginWindow() {}

void LoginWindow::onLoginClicked()
{
    QString user = txtUser->text().trimmed();
    QString pass = txtPassword->text().trimmed();
    DatabaseManager dbManager;

    if (dbManager.doLogin(user, pass)) {
        lblMessage->clear();
        emit loginSuccessful();
    } else {
        lblMessage->setText("Usuario o contraseña incorrectos");
    }
}
