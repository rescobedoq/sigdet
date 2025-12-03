/********************************************************************************
** Form generated from reading UI file 'donacion.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DONACION_H
#define UI_DONACION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Donacion
{
public:
    QVBoxLayout *mainLayout;
    QFormLayout *formLayout;
    QLabel *lblNombre;
    QLineEdit *txtNombre;
    QLabel *lblTipo;
    QComboBox *cmbTipo;
    QLabel *lblCantidad;
    QDoubleSpinBox *spnCantidad;
    QLabel *lblFecha;
    QDateEdit *dateFecha;
    QHBoxLayout *buttonsLayout;
    QPushButton *btnRegistrar;
    QPushButton *btnLimpiar;

    void setupUi(QWidget *Donacion)
    {
        if (Donacion->objectName().isEmpty())
            Donacion->setObjectName("Donacion");
        Donacion->resize(400, 300);
        mainLayout = new QVBoxLayout(Donacion);
        mainLayout->setObjectName("mainLayout");
        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        lblNombre = new QLabel(Donacion);
        lblNombre->setObjectName("lblNombre");

        formLayout->setWidget(0, QFormLayout::ItemRole::LabelRole, lblNombre);

        txtNombre = new QLineEdit(Donacion);
        txtNombre->setObjectName("txtNombre");

        formLayout->setWidget(0, QFormLayout::ItemRole::FieldRole, txtNombre);

        lblTipo = new QLabel(Donacion);
        lblTipo->setObjectName("lblTipo");

        formLayout->setWidget(1, QFormLayout::ItemRole::LabelRole, lblTipo);

        cmbTipo = new QComboBox(Donacion);
        cmbTipo->addItem(QString());
        cmbTipo->addItem(QString());
        cmbTipo->setObjectName("cmbTipo");

        formLayout->setWidget(1, QFormLayout::ItemRole::FieldRole, cmbTipo);

        lblCantidad = new QLabel(Donacion);
        lblCantidad->setObjectName("lblCantidad");

        formLayout->setWidget(2, QFormLayout::ItemRole::LabelRole, lblCantidad);

        spnCantidad = new QDoubleSpinBox(Donacion);
        spnCantidad->setObjectName("spnCantidad");

        formLayout->setWidget(2, QFormLayout::ItemRole::FieldRole, spnCantidad);

        lblFecha = new QLabel(Donacion);
        lblFecha->setObjectName("lblFecha");

        formLayout->setWidget(3, QFormLayout::ItemRole::LabelRole, lblFecha);

        dateFecha = new QDateEdit(Donacion);
        dateFecha->setObjectName("dateFecha");

        formLayout->setWidget(3, QFormLayout::ItemRole::FieldRole, dateFecha);


        mainLayout->addLayout(formLayout);

        buttonsLayout = new QHBoxLayout();
        buttonsLayout->setObjectName("buttonsLayout");
        btnRegistrar = new QPushButton(Donacion);
        btnRegistrar->setObjectName("btnRegistrar");

        buttonsLayout->addWidget(btnRegistrar);

        btnLimpiar = new QPushButton(Donacion);
        btnLimpiar->setObjectName("btnLimpiar");

        buttonsLayout->addWidget(btnLimpiar);


        mainLayout->addLayout(buttonsLayout);


        retranslateUi(Donacion);

        QMetaObject::connectSlotsByName(Donacion);
    } // setupUi

    void retranslateUi(QWidget *Donacion)
    {
        Donacion->setWindowTitle(QCoreApplication::translate("Donacion", "Formulario de Donaci\303\263n", nullptr));
        lblNombre->setText(QCoreApplication::translate("Donacion", "Nombre:", nullptr));
        lblTipo->setText(QCoreApplication::translate("Donacion", "Tipo:", nullptr));
        cmbTipo->setItemText(0, QCoreApplication::translate("Donacion", "Alimentos", nullptr));
        cmbTipo->setItemText(1, QCoreApplication::translate("Donacion", "Ropa", nullptr));

        lblCantidad->setText(QCoreApplication::translate("Donacion", "Cantidad:", nullptr));
        lblFecha->setText(QCoreApplication::translate("Donacion", "Fecha:", nullptr));
        btnRegistrar->setText(QCoreApplication::translate("Donacion", "Registrar", nullptr));
        btnLimpiar->setText(QCoreApplication::translate("Donacion", "Limpiar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Donacion: public Ui_Donacion {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DONACION_H
