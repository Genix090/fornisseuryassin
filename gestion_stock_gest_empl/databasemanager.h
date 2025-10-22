#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QString>
#include <QSqlDatabase>
#include <QList>
#include "fournisseur.h"
#include "produit.h"

class DatabaseManager
{
public:
    enum DatabaseType {
        SQLite,      // Easy to use, no installation needed
        Oracle,      // For production Oracle database
        MySQL,       // Alternative option
        PostgreSQL   // Another alternative
    };

private:
    QSqlDatabase db;
    bool connected;
    QString lastError;
    DatabaseType dbType;

public:
    DatabaseManager(DatabaseType type = SQLite);
    ~DatabaseManager();

    // Connection
    bool connectToDatabase(const QString& dbName = "optical_store.db");
    bool connectToOracle(const QString& host, int port, const QString& sid,
                        const QString& username, const QString& password);
    void disconnect();
    bool isConnected() const { return connected; }
    QString getLastError() const { return lastError; }
    QString getDatabaseType() const;

    // Table creation
    bool createTables();

    // FOURNISSEUR operations
    bool insertFournisseur(const Fournisseur& f);
    bool updateFournisseur(const Fournisseur& f);
    bool deleteFournisseur(int id);
    QList<Fournisseur> getAllFournisseurs();
    Fournisseur getFournisseurById(int id);
    QList<Fournisseur> searchFournisseurs(const QString& searchTerm);

    // PRODUIT operations
    bool insertProduit(const Produit& p);
    bool updateProduit(const Produit& p);
    bool deleteProduit(int id);
    QList<Produit> getAllProduits();
    Produit getProduitById(int id);
    QList<Produit> getProduitsByFournisseur(int idFournisseur);
    QList<Produit> searchProduits(const QString& searchTerm);

    // Relations
    int countProduitsByFournisseur(int idFournisseur);
    bool fournisseurHasProduits(int idFournisseur);
};

#endif // DATABASEMANAGER_H

