#ifndef DONACIONESENVIADASVIEW_H
#define DONACIONESENVIADASVIEW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QTableWidget>
#include <QLineEdit>
#include <QFrame>
#include <QScrollArea>

class DonacionesEnviadasView: public QWidget {
    Q_OBJECT
public:
    explicit DonacionesEnviadasView(QWidget *parent = nullptr);

signals:
    void registrarDonacion();

private:
    QVBoxLayout *mainLayout;
    QWidget* crearResumenCards(const QJsonArray &data);
    QWidget* crearTablaDonaciones(const QJsonArray &data);
    QJsonArray getDonancionesEnviadas();
    QWidget *resumenCards = nullptr;
    void reloadResumenCards();
};

#endif // DONACIONESENVIADASVIEW_H
