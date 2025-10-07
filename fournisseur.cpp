#include "fournisseur.h"
#include <QRegularExpression>
#include <QJsonObject>

Fournisseur::Fournisseur()
    : idFournisseur(0), nom(""), adresse(""), email(""), telephone(""),
      typeProduits(""), historiqueLivraisons(""), isActive(true)
{
}

Fournisseur::Fournisseur(int id, const QString& nom, const QString& adresse,
                         const QString& email, const QString& telephone,
                         const QString& typeProduits, const QString& historiqueLivraisons,
                         bool isActive)
    : idFournisseur(id), nom(nom), adresse(adresse), email(email),
      telephone(telephone), typeProduits(typeProduits),
      historiqueLivraisons(historiqueLivraisons), isActive(isActive)
{
}

bool Fournisseur::validateEmail() const
{
    QRegularExpression emailRegex("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$");
    return emailRegex.match(email).hasMatch();
}

bool Fournisseur::validateTelephone() const
{
    QRegularExpression phoneRegex("^[0-9+\\-\\s()]{8,20}$");
    return phoneRegex.match(telephone).hasMatch();
}

bool Fournisseur::isValid() const
{
    return idFournisseur > 0 &&
           !nom.trimmed().isEmpty() &&
           !adresse.trimmed().isEmpty() &&
           validateEmail() &&
           validateTelephone();
}

QJsonObject Fournisseur::toJson() const
{
    QJsonObject json;
    json["id"] = idFournisseur;
    json["nom"] = nom;
    json["adresse"] = adresse;
    json["email"] = email;
    json["telephone"] = telephone;
    json["typeProduits"] = typeProduits;
    json["historiqueLivraisons"] = historiqueLivraisons;
    json["isActive"] = isActive;
    return json;
}

Fournisseur Fournisseur::fromJson(const QJsonObject& json)
{
    return Fournisseur(
        json["id"].toInt(),
        json["nom"].toString(),
        json["adresse"].toString(),
        json["email"].toString(),
        json["telephone"].toString(),
        json["typeProduits"].toString(),
        json["historiqueLivraisons"].toString(),
        json["isActive"].toBool()
    );
}

QString Fournisseur::toString() const
{
    return QString("ID: %1 | Nom: %2 | Email: %3 | Tel: %4")
        .arg(idFournisseur)
        .arg(nom)
        .arg(email)
        .arg(telephone);
}

