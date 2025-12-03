#ifndef DONACIONESRECIBIDASVIEW_H
#define DONACIONESRECIBIDASVIEW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QTableWidget>
#include <QLineEdit>
#include <QFrame>
#include <QScrollArea>

class DonacionesRecibidasView : public QWidget {
    Q_OBJECT
public:
    explicit DonacionesRecibidasView(QWidget *parent = nullptr);

signals:
    void registrarDonacion();

private:
    QVBoxLayout *mainLayout;
    QWidget* crearResumenCards(const QJsonArray &data);
    QWidget* crearTablaDonaciones(const QJsonArray &data);
    QJsonArray getDonancionesRecibidas();
    QWidget *resumenCards = nullptr;
    void reloadResumenCards();
};


#endif // DONACIONESRECIBIDASVIEW_H
