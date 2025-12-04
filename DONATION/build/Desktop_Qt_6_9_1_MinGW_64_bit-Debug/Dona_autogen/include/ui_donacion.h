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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Donacion
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_main;
    QLabel *labelTitulo;
    QGroupBox *groupBoxFormulario;
    QGridLayout *gridLayoutForm;
    QLabel *labelDonante;
    QLineEdit *inputDonante;
    QLabel *labelTipo;
    QComboBox *comboTipo;
    QLabel *labelCantidad;
    QSpinBox *spinCantidad;
    QLabel *labelFecha;
    QDateEdit *dateFecha;
    QHBoxLayout *horizontalLayoutButtons;
    QPushButton *btnRegistrar;
    QPushButton *btnLimpiar;
    QTableWidget *tablaDonaciones;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Donacion)
    {
        if (Donacion->objectName().isEmpty())
            Donacion->setObjectName("Donacion");
        Donacion->resize(526, 450);
        centralwidget = new QWidget(Donacion);
        centralwidget->setObjectName("centralwidget");
        verticalLayout_main = new QVBoxLayout(centralwidget);
        verticalLayout_main->setObjectName("verticalLayout_main");
        labelTitulo = new QLabel(centralwidget);
        labelTitulo->setObjectName("labelTitulo");
        labelTitulo->setStyleSheet(QString::fromUtf8("\n"
"        font-size: 22px;\n"
"        font-weight: bold;\n"
"        color: #2a4d69;\n"
"       "));
        labelTitulo->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_main->addWidget(labelTitulo);

        groupBoxFormulario = new QGroupBox(centralwidget);
        groupBoxFormulario->setObjectName("groupBoxFormulario");
        groupBoxFormulario->setStyleSheet(QString::fromUtf8("\n"
"        font-size: 14px;\n"
"       "));
        gridLayoutForm = new QGridLayout(groupBoxFormulario);
        gridLayoutForm->setObjectName("gridLayoutForm");
        labelDonante = new QLabel(groupBoxFormulario);
        labelDonante->setObjectName("labelDonante");

        gridLayoutForm->addWidget(labelDonante, 0, 0, 1, 1);

        inputDonante = new QLineEdit(groupBoxFormulario);
        inputDonante->setObjectName("inputDonante");

        gridLayoutForm->addWidget(inputDonante, 0, 1, 1, 1);

        labelTipo = new QLabel(groupBoxFormulario);
        labelTipo->setObjectName("labelTipo");

        gridLayoutForm->addWidget(labelTipo, 1, 0, 1, 1);

        comboTipo = new QComboBox(groupBoxFormulario);
        comboTipo->addItem(QString());
        comboTipo->addItem(QString());
        comboTipo->setObjectName("comboTipo");

        gridLayoutForm->addWidget(comboTipo, 1, 1, 1, 1);

        labelCantidad = new QLabel(groupBoxFormulario);
        labelCantidad->setObjectName("labelCantidad");

        gridLayoutForm->addWidget(labelCantidad, 2, 0, 1, 1);

        spinCantidad = new QSpinBox(groupBoxFormulario);
        spinCantidad->setObjectName("spinCantidad");
        spinCantidad->setMinimum(1);
        spinCantidad->setMaximum(9999);

        gridLayoutForm->addWidget(spinCantidad, 2, 1, 1, 1);

        labelFecha = new QLabel(groupBoxFormulario);
        labelFecha->setObjectName("labelFecha");

        gridLayoutForm->addWidget(labelFecha, 3, 0, 1, 1);

        dateFecha = new QDateEdit(groupBoxFormulario);
        dateFecha->setObjectName("dateFecha");
        dateFecha->setCalendarPopup(true);

        gridLayoutForm->addWidget(dateFecha, 3, 1, 1, 1);


        verticalLayout_main->addWidget(groupBoxFormulario);

        horizontalLayoutButtons = new QHBoxLayout();
        horizontalLayoutButtons->setObjectName("horizontalLayoutButtons");
        btnRegistrar = new QPushButton(centralwidget);
        btnRegistrar->setObjectName("btnRegistrar");
        btnRegistrar->setStyleSheet(QString::fromUtf8("\n"
"          background-color: #4caf50;\n"
"          color: white;\n"
"          padding: 6px;\n"
"          border-radius: 4px;\n"
"         "));

        horizontalLayoutButtons->addWidget(btnRegistrar);

        btnLimpiar = new QPushButton(centralwidget);
        btnLimpiar->setObjectName("btnLimpiar");
        btnLimpiar->setStyleSheet(QString::fromUtf8("\n"
"          background-color: #f44336;\n"
"          color: white;\n"
"          padding: 6px;\n"
"          border-radius: 4px;\n"
"         "));

        horizontalLayoutButtons->addWidget(btnLimpiar);


        verticalLayout_main->addLayout(horizontalLayoutButtons);

        tablaDonaciones = new QTableWidget(centralwidget);
        if (tablaDonaciones->columnCount() < 4)
            tablaDonaciones->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tablaDonaciones->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tablaDonaciones->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tablaDonaciones->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tablaDonaciones->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        tablaDonaciones->setObjectName("tablaDonaciones");
        tablaDonaciones->setRowCount(0);
        tablaDonaciones->setColumnCount(4);

        verticalLayout_main->addWidget(tablaDonaciones);

        Donacion->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Donacion);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 526, 25));
        Donacion->setMenuBar(menubar);
        statusbar = new QStatusBar(Donacion);
        statusbar->setObjectName("statusbar");
        Donacion->setStatusBar(statusbar);

        retranslateUi(Donacion);

        QMetaObject::connectSlotsByName(Donacion);
    } // setupUi

    void retranslateUi(QMainWindow *Donacion)
    {
        Donacion->setWindowTitle(QCoreApplication::translate("Donacion", "Registro de Donaci\303\263n", nullptr));
        labelTitulo->setText(QCoreApplication::translate("Donacion", "Gesti\303\263n de Donaciones", nullptr));
        groupBoxFormulario->setTitle(QCoreApplication::translate("Donacion", "Formulario de Registro", nullptr));
        labelDonante->setText(QCoreApplication::translate("Donacion", "Nombre del Donante:", nullptr));
        labelTipo->setText(QCoreApplication::translate("Donacion", "Tipo de Donaci\303\263n:", nullptr));
        comboTipo->setItemText(0, QCoreApplication::translate("Donacion", "Alimento", nullptr));
        comboTipo->setItemText(1, QCoreApplication::translate("Donacion", "Ropa", nullptr));

        labelCantidad->setText(QCoreApplication::translate("Donacion", "Cantidad:", nullptr));
        labelFecha->setText(QCoreApplication::translate("Donacion", "Fecha:", nullptr));
        btnRegistrar->setText(QCoreApplication::translate("Donacion", "Registrar", nullptr));
        btnLimpiar->setText(QCoreApplication::translate("Donacion", "Limpiar", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tablaDonaciones->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("Donacion", "Donante", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tablaDonaciones->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("Donacion", "Tipo", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tablaDonaciones->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("Donacion", "Cantidad", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tablaDonaciones->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("Donacion", "Fecha", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Donacion: public Ui_Donacion {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DONACION_H
