#ifndef DONANTEMODEL_H
#define DONANTEMODEL_H

#include <QString>
#include <QDateTime>

class donanteModel
{
private:
    int id;
    QString nombre;
    QString apellido;
    QString email;
    QString telefono;
    QString direccion;
    QString tipo_documento;
    QString numero_documento;
    QDateTime created_at;
    QDateTime updated_at;

public:
    donanteModel();

    donanteModel(int id, const QString &nombre, const QString &apellido,
            const QString &email, const QString &telefono,
            const QString &direccion, const QString &tipo_documento,
            const QString &numero_documento,
            const QDateTime &created_at, const QDateTime &updated_at);

    // Getters
    int getId() const;
    QString getNombre() const;
    QString getApellido() const;
    QString getEmail() const;
    QString getTelefono() const;
    QString getDireccion() const;
    QString getTipoDocumento() const;
    QString getNumeroDocumento() const;
    QDateTime getCreatedAt() const;
    QDateTime getUpdatedAt() const;

    // Setters
    void setId(int v);
    void setNombre(const QString &v);
    void setApellido(const QString &v);
    void setEmail(const QString &v);
    void setTelefono(const QString &v);
    void setDireccion(const QString &v);
    void setTipoDocumento(const QString &v);
    void setNumeroDocumento(const QString &v);
    void setCreatedAt(const QDateTime &v);
    void setUpdatedAt(const QDateTime &v);
};

#endif // DONANTEMODEL_H
