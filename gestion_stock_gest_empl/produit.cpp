#include "produit.h"

Produit::Produit()
    : id(0), nomProduit(""), description(""), prixUnitaire(0.0),
      quantiteStock(0), idFournisseur(0), dateLivraison(QDate::currentDate())
{
}

Produit::Produit(int id, const QString &nomProduit, const QString &description,
                 double prixUnitaire, int quantiteStock, int idFournisseur,
                 const QDate &dateLivraison)
    : id(id), nomProduit(nomProduit), description(description),
      prixUnitaire(prixUnitaire), quantiteStock(quantiteStock),
      idFournisseur(idFournisseur), dateLivraison(dateLivraison)
{
}

QJsonObject Produit::toJson() const
{
    QJsonObject json;
    json["id"] = id;
    json["nomProduit"] = nomProduit;
    json["description"] = description;
    json["prixUnitaire"] = prixUnitaire;
    json["quantiteStock"] = quantiteStock;
    json["idFournisseur"] = idFournisseur;
    json["dateLivraison"] = dateLivraison.toString(Qt::ISODate);
    return json;
}

Produit Produit::fromJson(const QJsonObject &json)
{
    return Produit(
        json["id"].toInt(),
        json["nomProduit"].toString(),
        json["description"].toString(),
        json["prixUnitaire"].toDouble(),
        json["quantiteStock"].toInt(),
        json["idFournisseur"].toInt(),
        QDate::fromString(json["dateLivraison"].toString(), Qt::ISODate)
    );
}

