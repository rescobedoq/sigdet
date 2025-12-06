#ifndef USERMODEL_H
#define USERMODEL_H

#include <QString>
#include <QDateTime>

class userModel
{
private:
    int id;
    QString username;
    QString password_u;
    QDateTime created_at;
    QDateTime updated_at;

public:
    userModel();

    userModel(int id, const QString &username, const QString &password_u,
         const QDateTime &created_at, const QDateTime &updated_at);

    // Getters
    int getId() const;
    QString getUsername() const;
    QString getPassword() const;
    QDateTime getCreatedAt() const;
    QDateTime getUpdatedAt() const;

    // Setters
    void setId(int value);
    void setUsername(const QString &value);
    void setPassword(const QString &value);
    void setCreatedAt(const QDateTime &value);
    void setUpdatedAt(const QDateTime &value);
};

#endif // USERMODEL_H
