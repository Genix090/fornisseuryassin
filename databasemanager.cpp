#include "databasemanager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonArray>
#include <QFile>

DatabaseManager::DatabaseManager(DatabaseType type)
    : connected(false), dbType(type)
{
}

DatabaseManager::~DatabaseManager()
{
    if (connected) {
        disconnect();
    }
}

QString DatabaseManager::getDatabaseType() const
{
    switch(dbType) {
        case SQLite: return "SQLite (Perfect for macOS!)";
        case Oracle: return "Oracle Database";
        case MySQL: return "MySQL Database";
        case PostgreSQL: return "PostgreSQL Database";
        default: return "Unknown";
    }
}

bool DatabaseManager::connectToDatabase(const QString& dbName)
{
    // SQLite - Works on ANY macOS without installation!
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbName);
    
    if (db.open()) {
        connected = true;
        lastError.clear();
        qDebug() << "✅ Connected to" << getDatabaseType();
        return true;
    } else {
        connected = false;
        lastError = db.lastError().text();
        qDebug() << "❌ Connection failed:" << lastError;
        return false;
    }
}

bool DatabaseManager::connectToOracle(const QString& host, int port, 
                                      const QString& sid,
                                      const QString& username, 
                                      const QString& password)
{
    // Oracle connection (when available)
    db = QSqlDatabase::addDatabase("QOCI");
    db.setHostName(host);
    db.setPort(port);
    db.setDatabaseName(sid);
    db.setUserName(username);
    db.setPassword(password);
    dbType = Oracle;
    
    if (db.open()) {
        connected = true;
        lastError.clear();
        qDebug() << "✅ Connected to Oracle Database!";
        return true;
    } else {
        connected = false;
        lastError = db.lastError().text();
        qDebug() << "❌ Oracle connection failed:" << lastError;
        return false;
    }
}

void DatabaseManager::disconnect()
{
    if (connected) {
        db.close();
        connected = false;
    }
}

bool DatabaseManager::createTables()
{
    if (!connected) {
        lastError = "Not connected to database";
        return false;
    }
    
    QSqlQuery query(db);
    QString createTableSQL;
    
    if (dbType == SQLite) {
        // SQLite syntax
        createTableSQL = R"(
            CREATE TABLE IF NOT EXISTS FOURNISSEURS (
                ID_FOURNISSEUR INTEGER PRIMARY KEY AUTOINCREMENT,
                NOM TEXT NOT NULL,
                ADRESSE TEXT,
                EMAIL TEXT,
                TELEPHONE TEXT,
                TYPE_PRODUITS TEXT,
                HISTORIQUE_LIVRAISONS TEXT,
                IS_ACTIVE INTEGER DEFAULT 1,
                DATE_CREATION TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
                DATE_MODIFICATION TIMESTAMP DEFAULT CURRENT_TIMESTAMP
            )
        )";
    } else {
        // Oracle syntax
        createTableSQL = R"(
            CREATE TABLE FOURNISSEURS (
                ID_FOURNISSEUR NUMBER(10) PRIMARY KEY,
                NOM VARCHAR2(100) NOT NULL,
                ADRESSE VARCHAR2(200),
                EMAIL VARCHAR2(100),
                TELEPHONE VARCHAR2(20),
                TYPE_PRODUITS VARCHAR2(100),
                HISTORIQUE_LIVRAISONS VARCHAR2(500),
                IS_ACTIVE NUMBER(1) DEFAULT 1,
                DATE_CREATION TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
                DATE_MODIFICATION TIMESTAMP DEFAULT CURRENT_TIMESTAMP
            )
        )";
    }
    
    if (!query.exec(createTableSQL)) {
        lastError = query.lastError().text();
        qDebug() << "Error creating table:" << lastError;
        return false;
    }
    
    qDebug() << "✅ Tables created successfully in" << getDatabaseType();
    return true;
}

bool DatabaseManager::insertFournisseur(const Fournisseur& f)
{
    if (!connected) return false;
    
    QSqlQuery query(db);
    query.prepare(R"(
        INSERT INTO FOURNISSEURS 
        (NOM, ADRESSE, EMAIL, TELEPHONE, TYPE_PRODUITS, 
         HISTORIQUE_LIVRAISONS, IS_ACTIVE)
        VALUES (:nom, :adresse, :email, :telephone, :type, :historique, :active)
    )");
    
    query.bindValue(":nom", f.getNom());
    query.bindValue(":adresse", f.getAdresse());
    query.bindValue(":email", f.getEmail());
    query.bindValue(":telephone", f.getTelephone());
    query.bindValue(":type", f.getTypeProduits());
    query.bindValue(":historique", f.getHistoriqueLivraisons());
    query.bindValue(":active", f.getIsActive() ? 1 : 0);
    
    if (!query.exec()) {
        lastError = query.lastError().text();
        qDebug() << "Insert error:" << lastError;
        return false;
    }
    
    return true;
}

bool DatabaseManager::updateFournisseur(const Fournisseur& f)
{
    if (!connected) return false;
    
    QSqlQuery query(db);
    query.prepare(R"(
        UPDATE FOURNISSEURS SET
            NOM = :nom,
            ADRESSE = :adresse,
            EMAIL = :email,
            TELEPHONE = :telephone,
            TYPE_PRODUITS = :type,
            HISTORIQUE_LIVRAISONS = :historique,
            IS_ACTIVE = :active,
            DATE_MODIFICATION = CURRENT_TIMESTAMP
        WHERE ID_FOURNISSEUR = :id
    )");
    
    query.bindValue(":nom", f.getNom());
    query.bindValue(":adresse", f.getAdresse());
    query.bindValue(":email", f.getEmail());
    query.bindValue(":telephone", f.getTelephone());
    query.bindValue(":type", f.getTypeProduits());
    query.bindValue(":historique", f.getHistoriqueLivraisons());
    query.bindValue(":active", f.getIsActive() ? 1 : 0);
    query.bindValue(":id", f.getIdFournisseur());
    
    return query.exec();
}

bool DatabaseManager::deleteFournisseur(int id)
{
    if (!connected) return false;
    
    QSqlQuery query(db);
    query.prepare("DELETE FROM FOURNISSEURS WHERE ID_FOURNISSEUR = :id");
    query.bindValue(":id", id);
    
    return query.exec();
}

Fournisseur DatabaseManager::getFournisseurById(int id, bool& success)
{
    Fournisseur f;
    success = false;
    
    if (!connected) return f;
    
    QSqlQuery query(db);
    query.prepare("SELECT * FROM FOURNISSEURS WHERE ID_FOURNISSEUR = :id");
    query.bindValue(":id", id);
    
    if (query.exec() && query.next()) {
        f = Fournisseur(
            query.value("ID_FOURNISSEUR").toInt(),
            query.value("NOM").toString(),
            query.value("ADRESSE").toString(),
            query.value("EMAIL").toString(),
            query.value("TELEPHONE").toString(),
            query.value("TYPE_PRODUITS").toString(),
            query.value("HISTORIQUE_LIVRAISONS").toString(),
            query.value("IS_ACTIVE").toInt() == 1
        );
        success = true;
    }
    
    return f;
}

QList<Fournisseur> DatabaseManager::getAllFournisseurs(bool& success)
{
    QList<Fournisseur> list;
    success = false;
    
    if (!connected) return list;
    
    QSqlQuery query(db);
    if (!query.exec("SELECT * FROM FOURNISSEURS ORDER BY ID_FOURNISSEUR")) {
        lastError = query.lastError().text();
        return list;
    }
    
    while (query.next()) {
        Fournisseur f(
            query.value("ID_FOURNISSEUR").toInt(),
            query.value("NOM").toString(),
            query.value("ADRESSE").toString(),
            query.value("EMAIL").toString(),
            query.value("TELEPHONE").toString(),
            query.value("TYPE_PRODUITS").toString(),
            query.value("HISTORIQUE_LIVRAISONS").toString(),
            query.value("IS_ACTIVE").toInt() == 1
        );
        list.append(f);
    }
    
    success = true;
    return list;
}

QList<Fournisseur> DatabaseManager::searchFournisseurs(const QString& searchText, bool& success)
{
    QList<Fournisseur> list;
    success = false;
    
    if (!connected) return list;
    
    QSqlQuery query(db);
    query.prepare(R"(
        SELECT * FROM FOURNISSEURS 
        WHERE NOM LIKE :search 
           OR EMAIL LIKE :search
           OR TYPE_PRODUITS LIKE :search
        ORDER BY ID_FOURNISSEUR
    )");
    
    QString searchPattern = "%" + searchText + "%";
    query.bindValue(":search", searchPattern);
    
    if (!query.exec()) {
        lastError = query.lastError().text();
        return list;
    }
    
    while (query.next()) {
        Fournisseur f(
            query.value("ID_FOURNISSEUR").toInt(),
            query.value("NOM").toString(),
            query.value("ADRESSE").toString(),
            query.value("EMAIL").toString(),
            query.value("TELEPHONE").toString(),
            query.value("TYPE_PRODUITS").toString(),
            query.value("HISTORIQUE_LIVRAISONS").toString(),
            query.value("IS_ACTIVE").toInt() == 1
        );
        list.append(f);
    }
    
    success = true;
    return list;
}

int DatabaseManager::getTotalCount()
{
    if (!connected) return 0;
    
    QSqlQuery query(db);
    if (query.exec("SELECT COUNT(*) FROM FOURNISSEURS") && query.next()) {
        return query.value(0).toInt();
    }
    return 0;
}

QMap<QString, int> DatabaseManager::getProductTypeDistribution()
{
    QMap<QString, int> distribution;
    
    if (!connected) return distribution;
    
    QSqlQuery query(db);
    if (query.exec("SELECT TYPE_PRODUITS, COUNT(*) as CNT FROM FOURNISSEURS GROUP BY TYPE_PRODUITS")) {
        while (query.next()) {
            QString type = query.value(0).toString();
            int count = query.value(1).toInt();
            distribution[type] = count;
        }
    }
    
    return distribution;
}

bool DatabaseManager::importFromJson(const QList<Fournisseur>& fournisseurs)
{
    if (!connected) return false;
    
    db.transaction();
    
    for (const Fournisseur& f : fournisseurs) {
        if (!insertFournisseur(f)) {
            db.rollback();
            return false;
        }
    }
    
    return db.commit();
}

bool DatabaseManager::exportToJson(const QString& filename)
{
    bool success;
    QList<Fournisseur> fournisseurs = getAllFournisseurs(success);
    
    if (!success) return false;
    
    QJsonArray jsonArray;
    for (const Fournisseur& f : fournisseurs) {
        jsonArray.append(f.toJson());
    }
    
    QJsonDocument doc(jsonArray);
    QFile file(filename);
    
    if (file.open(QIODevice::WriteOnly)) {
        file.write(doc.toJson());
        file.close();
        return true;
    }
    
    return false;
}

QString DatabaseManager::getDatabaseInfo()
{
    if (!connected) return "Not connected";
    
    QString info = QString("📊 DATABASE INFORMATION:\n\n");
    info += QString("Type: %1\n").arg(getDatabaseType());
    info += QString("Status: Connected ✅\n");
    info += QString("Total Records: %1\n").arg(getTotalCount());
    info += QString("\nFeatures:\n");
    info += QString("✅ Full CRUD Operations\n");
    info += QString("✅ Search & Filter\n");
    info += QString("✅ Statistics\n");
    info += QString("✅ JSON Import/Export\n");
    info += QString("✅ Professional SQL queries\n");
    
    return info;
}

bool DatabaseManager::dropTables()
{
    if (!connected) return false;
    
    QSqlQuery query(db);
    return query.exec("DROP TABLE IF EXISTS FOURNISSEURS");
}

