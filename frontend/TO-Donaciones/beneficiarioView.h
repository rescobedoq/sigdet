#ifndef BENEFICIARIOVIEW_H
#define BENEFICIARIOVIEW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QTableWidget>
#include <QLineEdit>
#include <QFrame>
#include <QScrollArea>

class BeneficiarioView: public QWidget {
    Q_OBJECT
public:
    explicit BeneficiarioView(QWidget *parent = nullptr);

signals:
    void registrarDonacion();

private:
    QVBoxLayout *mainLayout;
    QWidget* crearTablaBeneficiaros();
    QJsonArray getBeneficiarios();
};

#endif // BENEFICIARIOVIEW_H
