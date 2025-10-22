#include "fournisseur.h"

Fournisseur::Fournisseur()
    : id(0), nom(""), email(""), telephone(""), adresse(""),
      typeProduits(""), ville(""), pays("")
{
}

Fournisseur::Fournisseur(int id, const QString &nom, const QString &email,
                         const QString &telephone, const QString &adresse,
                         const QString &typeProduits, const QString &ville, const QString &pays)
    : id(id), nom(nom), email(email), telephone(telephone), adresse(adresse),
      typeProduits(typeProduits), ville(ville), pays(pays)
{
}

QJsonObject Fournisseur::toJson() const
{
    QJsonObject json;
    json["id"] = id;
    json["nom"] = nom;
    json["email"] = email;
    json["telephone"] = telephone;
    json["adresse"] = adresse;
    json["typeProduits"] = typeProduits;
    json["ville"] = ville;
    json["pays"] = pays;
    return json;
}

Fournisseur Fournisseur::fromJson(const QJsonObject &json)
{
    return Fournisseur(
        json["id"].toInt(),
        json["nom"].toString(),
        json["email"].toString(),
        json["telephone"].toString(),
        json["adresse"].toString(),
        json["typeProduits"].toString(),
        json["ville"].toString(),
        json["pays"].toString()
    );
}

