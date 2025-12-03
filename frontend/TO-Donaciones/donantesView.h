#ifndef DONANTESVIEW_H
#define DONANTESVIEW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QTableWidget>
#include <QLineEdit>
#include <QFrame>
#include <QScrollArea>

class DonantesView: public QWidget {
    Q_OBJECT
public:
    explicit DonantesView(QWidget *parent = nullptr);

signals:
    void registrarDonacion();

private:
    QVBoxLayout *mainLayout;
    QWidget* crearTablaDonantes();
    QJsonArray getDonantes();
};

#endif // DONANTESVIEW_H
