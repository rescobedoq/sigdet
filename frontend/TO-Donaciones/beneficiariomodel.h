#ifndef BENEFICIARIOMODEL_H
#define BENEFICIARIOMODEL_H
#include <QString>
#include <QDateTime>

class beneficiarioModel
{
private:
    int id;
    QString nombre;
    QString apellido;
    QString referencia;
    QString direccion;
    QString telefono;
    QDateTime created_at;
    QDateTime updated_at;

public:
    beneficiarioModel();

    beneficiarioModel(int id, const QString &nombre, const QString &apellido,
                 const QString &referencia, const QString &direccion,
                 const QString &telefono,
                 const QDateTime &created_at, const QDateTime &updated_at);

    // Getters
    int getId() const;
    QString getNombre() const;
    QString getApellido() const;
    QString getReferencia() const;
    QString getDireccion() const;
    QString getTelefono() const;
    QDateTime getCreatedAt() const;
    QDateTime getUpdatedAt() const;

    // Setters
    void setId(int v);
    void setNombre(const QString &v);
    void setApellido(const QString &v);
    void setReferencia(const QString &v);
    void setDireccion(const QString &v);
    void setTelefono(const QString &v);
    void setCreatedAt(const QDateTime &v);
    void setUpdatedAt(const QDateTime &v);
};


#endif // BENEFICIARIOMODEL_H
