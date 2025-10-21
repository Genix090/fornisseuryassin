#ifndef ORACLECONNECTION_H
#define ORACLECONNECTION_H

#include <QSqlDatabase>
#include <QString>
#include <QSqlQuery>
#include <QSqlError>
#include <QList>
#include "fournisseur.h"

class OracleConnection
{
private:
    QSqlDatabase db;
    bool connected;
    QString lastError;

public:
    OracleConnection();
    ~OracleConnection();
    
    // Connection Management
    bool connectToOracle(const QString& host = "localhost",
                        int port = 1521,
                        const QString& sid = "XE",
                        const QString& username = "system",
                        const QString& password = "YourPassword123");
    
    bool isConnected() const { return connected; }
    void disconnect();
    QString getLastError() const { return lastError; }
    
    // Database Operations
    bool createTables();
    bool dropTables();
    
    // CRUD Operations for Fournisseur
    bool insertFournisseur(const Fournisseur& f);
    bool updateFournisseur(const Fournisseur& f);
    bool deleteFournisseur(int id);
    Fournisseur getFournisseurById(int id, bool& success);
    QList<Fournisseur> getAllFournisseurs(bool& success);
    QList<Fournisseur> searchFournisseurs(const QString& searchText, bool& success);
    
    // Advanced Queries
    int getTotalCount();
    QMap<QString, int> getProductTypeDistribution();
    QList<Fournisseur> getFournisseursByType(const QString& type);
    
    // Utility
    bool testConnection();
    QString getDatabaseVersion();
    
    // Migration: Import from JSON to Oracle
    bool importFromJson(const QList<Fournisseur>& fournisseurs);
    
    // Export from Oracle to JSON
    bool exportToJson(const QString& filename);
};

#endif // ORACLECONNECTION_H

