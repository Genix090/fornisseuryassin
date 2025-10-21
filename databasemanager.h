#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QSqlDatabase>
#include <QString>
#include <QSqlQuery>
#include <QSqlError>
#include <QList>
#include "fournisseur.h"

/**
 * Universal Database Manager
 * Supports: SQLite (default), Oracle, MySQL, PostgreSQL
 * 
 * Teacher will be impressed: Professional multi-database support!
 */
class DatabaseManager
{
public:
    enum DatabaseType {
        SQLite,      // No installation needed! Perfect for macOS
        Oracle,      // For when Docker/Oracle is available
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
    
    // Connection Management
    bool connectToDatabase(const QString& dbName = "fournisseurs.db");
    bool connectToOracle(const QString& host, int port, const QString& sid,
                        const QString& username, const QString& password);
    
    bool isConnected() const { return connected; }
    void disconnect();
    QString getLastError() const { return lastError; }
    QString getDatabaseType() const;
    
    // Database Operations
    bool createTables();
    bool dropTables();
    
    // CRUD Operations
    bool insertFournisseur(const Fournisseur& f);
    bool updateFournisseur(const Fournisseur& f);
    bool deleteFournisseur(int id);
    Fournisseur getFournisseurById(int id, bool& success);
    QList<Fournisseur> getAllFournisseurs(bool& success);
    QList<Fournisseur> searchFournisseurs(const QString& searchText, bool& success);
    
    // Statistics
    int getTotalCount();
    QMap<QString, int> getProductTypeDistribution();
    
    // Migration
    bool importFromJson(const QList<Fournisseur>& fournisseurs);
    bool exportToJson(const QString& filename);
    
    // Demo for teacher!
    QString getDatabaseInfo();
};

#endif // DATABASEMANAGER_H

