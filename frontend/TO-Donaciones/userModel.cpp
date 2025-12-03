#include "userModel.h"

userModel::userModel() {}

userModel::userModel(int id, const QString &username, const QString &password_u,
           const QDateTime &created_at, const QDateTime &updated_at)
    : id(id), username(username), password_u(password_u),
    created_at(created_at), updated_at(updated_at) {}

int userModel::getId() const { return id; }
QString userModel::getUsername() const { return username; }
QString userModel::getPassword() const { return password_u; }
QDateTime userModel::getCreatedAt() const { return created_at; }
QDateTime userModel::getUpdatedAt() const { return updated_at; }

void userModel::setId(int value) { id = value; }
void userModel::setUsername(const QString &value) { username = value; }
void userModel::setPassword(const QString &value) { password_u = value; }
void userModel::setCreatedAt(const QDateTime &value) { created_at = value; }
void userModel::setUpdatedAt(const QDateTime &value) { updated_at = value; }
