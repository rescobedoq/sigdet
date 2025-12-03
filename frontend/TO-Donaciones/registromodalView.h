#ifndef REGISTROMODALVIEW_H
#define REGISTROMODALVIEW_H

#include <QDialog>
#include <QGridLayout>
#include <QLineEdit>
#include <QComboBox>
#include <QMap>
#include <QJsonObject>

class RegistroModal : public QDialog
{
    Q_OBJECT
public:
    explicit RegistroModal(const QString &nombreTabla, QWidget *parent = nullptr);

private slots:
    void guardarRegistro();

private:
    QString nombreTabla;
    QGridLayout *gridLayout = nullptr;

    QMap<QString, QWidget*> campos; // QLineEdit o QComboBox

    void construirFormulario();
    bool esForeignKey(const QString &columna, QString &fkTable);
};

#endif // REGISTROMODALVIEW_H
