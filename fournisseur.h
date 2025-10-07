#ifndef FOURNISSEUR_H
#define FOURNISSEUR_H

#include <QString>
#include <QJsonObject>

class Fournisseur
{
private:
    int idFournisseur;
    QString nom;
    QString adresse;
    QString email;
    QString telephone;
    QString typeProduits;
    QString historiqueLivraisons;
    bool isActive;

public:
    // Constructors
    Fournisseur();
    Fournisseur(int id, const QString& nom, const QString& adresse, const QString& email,
                const QString& telephone, const QString& typeProduits,
                const QString& historiqueLivraisons, bool isActive = true);

    // Getters
    int getIdFournisseur() const { return idFournisseur; }
    QString getNom() const { return nom; }
    QString getAdresse() const { return adresse; }
    QString getEmail() const { return email; }
    QString getTelephone() const { return telephone; }
    QString getTypeProduits() const { return typeProduits; }
    QString getHistoriqueLivraisons() const { return historiqueLivraisons; }
    bool getIsActive() const { return isActive; }

    // Setters
    void setIdFournisseur(int id) { idFournisseur = id; }
    void setNom(const QString& n) { nom = n; }
    void setAdresse(const QString& a) { adresse = a; }
    void setEmail(const QString& e) { email = e; }
    void setTelephone(const QString& t) { telephone = t; }
    void setTypeProduits(const QString& tp) { typeProduits = tp; }
    void setHistoriqueLivraisons(const QString& h) { historiqueLivraisons = h; }
    void setIsActive(bool active) { isActive = active; }

    // Validation methods
    bool validateEmail() const;
    bool validateTelephone() const;
    bool isValid() const;

    // JSON serialization
    QJsonObject toJson() const;
    static Fournisseur fromJson(const QJsonObject& json);

    // Display info
    QString toString() const;
};

#endif // FOURNISSEUR_H

