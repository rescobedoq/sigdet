#include "beneficiarioModel.h"

beneficiarioModel::beneficiarioModel() {}
beneficiarioModel::beneficiarioModel(int id, const QString &nombre, const QString &apellido,
                           const QString &referencia, const QString &direccion,
                           const QString &telefono,
                           const QDateTime &created_at, const QDateTime &updated_at)
    : id(id), nombre(nombre), apellido(apellido),
    referencia(referencia), direccion(direccion), telefono(telefono),
    created_at(created_at), updated_at(updated_at) {}

int beneficiarioModel::getId() const { return id; }
QString beneficiarioModel::getNombre() const { return nombre; }
QString beneficiarioModel::getApellido() const { return apellido; }
QString beneficiarioModel::getReferencia() const { return referencia; }
QString beneficiarioModel::getDireccion() const { return direccion; }
QString beneficiarioModel::getTelefono() const { return telefono; }
QDateTime beneficiarioModel::getCreatedAt() const { return created_at; }
QDateTime beneficiarioModel::getUpdatedAt() const { return updated_at; }

void beneficiarioModel::setId(int v) { id = v; }
void beneficiarioModel::setNombre(const QString &v) { nombre = v; }
void beneficiarioModel::setApellido(const QString &v) { apellido = v; }
void beneficiarioModel::setReferencia(const QString &v) { referencia = v; }
void beneficiarioModel::setDireccion(const QString &v) { direccion = v; }
void beneficiarioModel::setTelefono(const QString &v) { telefono = v; }
void beneficiarioModel::setCreatedAt(const QDateTime &v) { created_at = v; }
void beneficiarioModel::setUpdatedAt(const QDateTime &v) { updated_at = v; }
