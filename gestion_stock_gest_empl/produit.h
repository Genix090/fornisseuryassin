#ifndef PRODUIT_H
#define PRODUIT_H

#include <QString>
#include <QDate>
#include <QJsonObject>

class Produit
{
private:
    int id;
    QString nomProduit;
    QString description;
    double prixUnitaire;
    int quantiteStock;
    int idFournisseur;  // Foreign Key to FOURNISSEURS table
    QDate dateLivraison;

public:
    // Constructeurs
    Produit();
    Produit(int id, const QString &nomProduit, const QString &description,
            double prixUnitaire, int quantiteStock, int idFournisseur,
            const QDate &dateLivraison = QDate::currentDate());

    // Getters
    int getId() const { return id; }
    QString getNomProduit() const { return nomProduit; }
    QString getDescription() const { return description; }
    double getPrixUnitaire() const { return prixUnitaire; }
    int getQuantiteStock() const { return quantiteStock; }
    int getIdFournisseur() const { return idFournisseur; }
    QDate getDateLivraison() const { return dateLivraison; }

    // Setters
    void setId(int newId) { id = newId; }
    void setNomProduit(const QString &newNom) { nomProduit = newNom; }
    void setDescription(const QString &newDesc) { description = newDesc; }
    void setPrixUnitaire(double newPrix) { prixUnitaire = newPrix; }
    void setQuantiteStock(int newQuantite) { quantiteStock = newQuantite; }
    void setIdFournisseur(int newIdFournisseur) { idFournisseur = newIdFournisseur; }
    void setDateLivraison(const QDate &newDate) { dateLivraison = newDate; }

    // JSON conversion
    QJsonObject toJson() const;
    static Produit fromJson(const QJsonObject &json);
};

#endif // PRODUIT_H

