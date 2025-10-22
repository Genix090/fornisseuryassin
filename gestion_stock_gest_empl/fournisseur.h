#ifndef FOURNISSEUR_H
#define FOURNISSEUR_H

#include <QString>
#include <QJsonObject>

class Fournisseur
{
private:
    int id;
    QString nom;
    QString email;
    QString telephone;
    QString adresse;
    QString typeProduits;
    QString ville;
    QString pays;

public:
    // Constructeurs
    Fournisseur();
    Fournisseur(int id, const QString &nom, const QString &email, 
                const QString &telephone, const QString &adresse,
                const QString &typeProduits, const QString &ville, const QString &pays);

    // Getters
    int getId() const { return id; }
    QString getNom() const { return nom; }
    QString getEmail() const { return email; }
    QString getTelephone() const { return telephone; }
    QString getAdresse() const { return adresse; }
    QString getTypeProduits() const { return typeProduits; }
    QString getVille() const { return ville; }
    QString getPays() const { return pays; }

    // Setters
    void setId(int newId) { id = newId; }
    void setNom(const QString &newNom) { nom = newNom; }
    void setEmail(const QString &newEmail) { email = newEmail; }
    void setTelephone(const QString &newTelephone) { telephone = newTelephone; }
    void setAdresse(const QString &newAdresse) { adresse = newAdresse; }
    void setTypeProduits(const QString &newType) { typeProduits = newType; }
    void setVille(const QString &newVille) { ville = newVille; }
    void setPays(const QString &newPays) { pays = newPays; }

    // JSON conversion
    QJsonObject toJson() const;
    static Fournisseur fromJson(const QJsonObject &json);
};

#endif // FOURNISSEUR_H

