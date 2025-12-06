#include "donanteModel.h"

donanteModel::donanteModel() {}

donanteModel::donanteModel(int id, const QString &nombre, const QString &apellido,
                 const QString &email, const QString &telefono,
                 const QString &direccion, const QString &tipo_documento,
                 const QString &numero_documento,
                 const QDateTime &created_at, const QDateTime &updated_at)
    : id(id), nombre(nombre), apellido(apellido), email(email),
    telefono(telefono), direccion(direccion),
    tipo_documento(tipo_documento), numero_documento(numero_documento),
    created_at(created_at), updated_at(updated_at) {}

int donanteModel::getId() const { return id; }
QString donanteModel::getNombre() const { return nombre; }
QString donanteModel::getApellido() const { return apellido; }
QString donanteModel::getEmail() const { return email; }
QString donanteModel::getTelefono() const { return telefono; }
QString donanteModel::getDireccion() const { return direccion; }
QString donanteModel::getTipoDocumento() const { return tipo_documento; }
QString donanteModel::getNumeroDocumento() const { return numero_documento; }
QDateTime donanteModel::getCreatedAt() const { return created_at; }
QDateTime donanteModel::getUpdatedAt() const { return updated_at; }

void donanteModel::setId(int v) { id = v; }
void donanteModel::setNombre(const QString &v) { nombre = v; }
void donanteModel::setApellido(const QString &v) { apellido = v; }
void donanteModel::setEmail(const QString &v) { email = v; }
void donanteModel::setTelefono(const QString &v) { telefono = v; }
void donanteModel::setDireccion(const QString &v) { direccion = v; }
void donanteModel::setTipoDocumento(const QString &v) { tipo_documento = v; }
void donanteModel::setNumeroDocumento(const QString &v) { numero_documento = v; }
void donanteModel::setCreatedAt(const QDateTime &v) { created_at = v; }
void donanteModel::setUpdatedAt(const QDateTime &v) { updated_at = v; }
