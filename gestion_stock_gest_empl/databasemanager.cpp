#include "databasemanager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QVariant>

DatabaseManager::DatabaseManager(DatabaseType type)
    : connected(false), dbType(type)
{
}

DatabaseManager::~DatabaseManager()
{
    disconnect();
}

bool DatabaseManager::connectToDatabase(const QString& dbName)
{
    // SQLite - Works on any platform without installation
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
    // Oracle connection
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
    if (connected && db.isOpen()) {
        db.close();
        connected = false;
    }
}

QString DatabaseManager::getDatabaseType() const
{
    switch(dbType) {
        case SQLite: return "SQLite Database";
        case Oracle: return "Oracle Database";
        case MySQL: return "MySQL Database";
        case PostgreSQL: return "PostgreSQL Database";
        default: return "Unknown Database";
    }
}

bool DatabaseManager::createTables()
{
    if (!connected) {
        lastError = "Not connected to database";
        return false;
    }

    QSqlQuery query(db);

    // Create FOURNISSEURS table (Parent table)
    QString createFournisseurs = R"(
        CREATE TABLE IF NOT EXISTS FOURNISSEURS (
            ID_FOURNISSEUR INTEGER PRIMARY KEY AUTOINCREMENT,
            NOM VARCHAR(100) NOT NULL,
            EMAIL VARCHAR(100),
            TELEPHONE VARCHAR(20),
            ADRESSE VARCHAR(200),
            TYPE_PRODUITS VARCHAR(100),
            VILLE VARCHAR(50),
            PAYS VARCHAR(50)
        )
    )";

    if (!query.exec(createFournisseurs)) {
        lastError = "Failed to create FOURNISSEURS table: " + query.lastError().text();
        qDebug() << "❌" << lastError;
        return false;
    }

    qDebug() << "✅ FOURNISSEURS table ready";

    // Create PRODUITS table (Child table with Foreign Key)
    QString createProduits = R"(
        CREATE TABLE IF NOT EXISTS PRODUITS (
            ID_PRODUIT INTEGER PRIMARY KEY AUTOINCREMENT,
            NOM_PRODUIT VARCHAR(100) NOT NULL,
            DESCRIPTION VARCHAR(200),
            PRIX_UNITAIRE REAL,
            QUANTITE_STOCK INTEGER,
            ID_FOURNISSEUR INTEGER NOT NULL,
            DATE_LIVRAISON DATE,
            FOREIGN KEY (ID_FOURNISSEUR) REFERENCES FOURNISSEURS(ID_FOURNISSEUR)
        )
    )";

    if (!query.exec(createProduits)) {
        lastError = "Failed to create PRODUITS table: " + query.lastError().text();
        qDebug() << "❌" << lastError;
        return false;
    }

    qDebug() << "✅ PRODUITS table ready with 1,N relation to FOURNISSEURS";

    return true;
}

// ============================================================================
// FOURNISSEUR Operations
// ============================================================================

bool DatabaseManager::insertFournisseur(const Fournisseur& f)
{
    if (!connected) return false;

    QSqlQuery query(db);
    query.prepare("INSERT INTO FOURNISSEURS (ID_FOURNISSEUR, NOM, EMAIL, TELEPHONE, ADRESSE, TYPE_PRODUITS, VILLE, PAYS) "
                  "VALUES (:id, :nom, :email, :tel, :adresse, :type, :ville, :pays)");
    
    query.bindValue(":id", f.getId());
    query.bindValue(":nom", f.getNom());
    query.bindValue(":email", f.getEmail());
    query.bindValue(":tel", f.getTelephone());
    query.bindValue(":adresse", f.getAdresse());
    query.bindValue(":type", f.getTypeProduits());
    query.bindValue(":ville", f.getVille());
    query.bindValue(":pays", f.getPays());

    if (!query.exec()) {
        lastError = query.lastError().text();
        qDebug() << "❌ Insert failed:" << lastError;
        return false;
    }

    qDebug() << "✅ Fournisseur inserted:" << f.getNom();
    return true;
}

bool DatabaseManager::updateFournisseur(const Fournisseur& f)
{
    if (!connected) return false;

    QSqlQuery query(db);
    query.prepare("UPDATE FOURNISSEURS SET NOM=:nom, EMAIL=:email, TELEPHONE=:tel, "
                  "ADRESSE=:adresse, TYPE_PRODUITS=:type, VILLE=:ville, PAYS=:pays "
                  "WHERE ID_FOURNISSEUR=:id");
    
    query.bindValue(":id", f.getId());
    query.bindValue(":nom", f.getNom());
    query.bindValue(":email", f.getEmail());
    query.bindValue(":tel", f.getTelephone());
    query.bindValue(":adresse", f.getAdresse());
    query.bindValue(":type", f.getTypeProduits());
    query.bindValue(":ville", f.getVille());
    query.bindValue(":pays", f.getPays());

    if (!query.exec()) {
        lastError = query.lastError().text();
        return false;
    }

    qDebug() << "✅ Fournisseur updated:" << f.getNom();
    return true;
}

bool DatabaseManager::deleteFournisseur(int id)
{
    if (!connected) return false;

    // Check if fournisseur has products
    if (fournisseurHasProduits(id)) {
        lastError = "Cannot delete fournisseur: has associated products";
        qDebug() << "❌" << lastError;
        return false;
    }

    QSqlQuery query(db);
    query.prepare("DELETE FROM FOURNISSEURS WHERE ID_FOURNISSEUR=:id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        lastError = query.lastError().text();
        return false;
    }

    qDebug() << "✅ Fournisseur deleted:" << id;
    return true;
}

QList<Fournisseur> DatabaseManager::getAllFournisseurs()
{
    QList<Fournisseur> list;
    if (!connected) return list;

    QSqlQuery query("SELECT * FROM FOURNISSEURS ORDER BY ID_FOURNISSEUR", db);
    
    while (query.next()) {
        Fournisseur f(
            query.value("ID_FOURNISSEUR").toInt(),
            query.value("NOM").toString(),
            query.value("EMAIL").toString(),
            query.value("TELEPHONE").toString(),
            query.value("ADRESSE").toString(),
            query.value("TYPE_PRODUITS").toString(),
            query.value("VILLE").toString(),
            query.value("PAYS").toString()
        );
        list.append(f);
    }

    return list;
}

Fournisseur DatabaseManager::getFournisseurById(int id)
{
    if (!connected) return Fournisseur();

    QSqlQuery query(db);
    query.prepare("SELECT * FROM FOURNISSEURS WHERE ID_FOURNISSEUR=:id");
    query.bindValue(":id", id);
    
    if (query.exec() && query.next()) {
        return Fournisseur(
            query.value("ID_FOURNISSEUR").toInt(),
            query.value("NOM").toString(),
            query.value("EMAIL").toString(),
            query.value("TELEPHONE").toString(),
            query.value("ADRESSE").toString(),
            query.value("TYPE_PRODUITS").toString(),
            query.value("VILLE").toString(),
            query.value("PAYS").toString()
        );
    }

    return Fournisseur();
}

QList<Fournisseur> DatabaseManager::searchFournisseurs(const QString& searchTerm)
{
    QList<Fournisseur> list;
    if (!connected) return list;

    QSqlQuery query(db);
    query.prepare("SELECT * FROM FOURNISSEURS WHERE "
                  "NOM LIKE :term OR EMAIL LIKE :term OR "
                  "TELEPHONE LIKE :term OR VILLE LIKE :term OR "
                  "TYPE_PRODUITS LIKE :term ORDER BY ID_FOURNISSEUR");
    
    QString term = "%" + searchTerm + "%";
    query.bindValue(":term", term);
    
    if (query.exec()) {
        while (query.next()) {
            Fournisseur f(
                query.value("ID_FOURNISSEUR").toInt(),
                query.value("NOM").toString(),
                query.value("EMAIL").toString(),
                query.value("TELEPHONE").toString(),
                query.value("ADRESSE").toString(),
                query.value("TYPE_PRODUITS").toString(),
                query.value("VILLE").toString(),
                query.value("PAYS").toString()
            );
            list.append(f);
        }
    }

    return list;
}

// ============================================================================
// PRODUIT Operations
// ============================================================================

bool DatabaseManager::insertProduit(const Produit& p)
{
    if (!connected) return false;

    QSqlQuery query(db);
    query.prepare("INSERT INTO PRODUITS (ID_PRODUIT, NOM_PRODUIT, DESCRIPTION, "
                  "PRIX_UNITAIRE, QUANTITE_STOCK, ID_FOURNISSEUR, DATE_LIVRAISON) "
                  "VALUES (:id, :nom, :desc, :prix, :qte, :idfour, :date)");
    
    query.bindValue(":id", p.getId());
    query.bindValue(":nom", p.getNomProduit());
    query.bindValue(":desc", p.getDescription());
    query.bindValue(":prix", p.getPrixUnitaire());
    query.bindValue(":qte", p.getQuantiteStock());
    query.bindValue(":idfour", p.getIdFournisseur());
    query.bindValue(":date", p.getDateLivraison().toString(Qt::ISODate));

    if (!query.exec()) {
        lastError = query.lastError().text();
        qDebug() << "❌ Insert produit failed:" << lastError;
        return false;
    }

    qDebug() << "✅ Produit inserted:" << p.getNomProduit();
    return true;
}

bool DatabaseManager::updateProduit(const Produit& p)
{
    if (!connected) return false;

    QSqlQuery query(db);
    query.prepare("UPDATE PRODUITS SET NOM_PRODUIT=:nom, DESCRIPTION=:desc, "
                  "PRIX_UNITAIRE=:prix, QUANTITE_STOCK=:qte, ID_FOURNISSEUR=:idfour, "
                  "DATE_LIVRAISON=:date WHERE ID_PRODUIT=:id");
    
    query.bindValue(":id", p.getId());
    query.bindValue(":nom", p.getNomProduit());
    query.bindValue(":desc", p.getDescription());
    query.bindValue(":prix", p.getPrixUnitaire());
    query.bindValue(":qte", p.getQuantiteStock());
    query.bindValue(":idfour", p.getIdFournisseur());
    query.bindValue(":date", p.getDateLivraison().toString(Qt::ISODate));

    if (!query.exec()) {
        lastError = query.lastError().text();
        return false;
    }

    qDebug() << "✅ Produit updated:" << p.getNomProduit();
    return true;
}

bool DatabaseManager::deleteProduit(int id)
{
    if (!connected) return false;

    QSqlQuery query(db);
    query.prepare("DELETE FROM PRODUITS WHERE ID_PRODUIT=:id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        lastError = query.lastError().text();
        return false;
    }

    qDebug() << "✅ Produit deleted:" << id;
    return true;
}

QList<Produit> DatabaseManager::getAllProduits()
{
    QList<Produit> list;
    if (!connected) return list;

    QSqlQuery query("SELECT * FROM PRODUITS ORDER BY ID_PRODUIT", db);
    
    while (query.next()) {
        Produit p(
            query.value("ID_PRODUIT").toInt(),
            query.value("NOM_PRODUIT").toString(),
            query.value("DESCRIPTION").toString(),
            query.value("PRIX_UNITAIRE").toDouble(),
            query.value("QUANTITE_STOCK").toInt(),
            query.value("ID_FOURNISSEUR").toInt(),
            QDate::fromString(query.value("DATE_LIVRAISON").toString(), Qt::ISODate)
        );
        list.append(p);
    }

    return list;
}

Produit DatabaseManager::getProduitById(int id)
{
    if (!connected) return Produit();

    QSqlQuery query(db);
    query.prepare("SELECT * FROM PRODUITS WHERE ID_PRODUIT=:id");
    query.bindValue(":id", id);
    
    if (query.exec() && query.next()) {
        return Produit(
            query.value("ID_PRODUIT").toInt(),
            query.value("NOM_PRODUIT").toString(),
            query.value("DESCRIPTION").toString(),
            query.value("PRIX_UNITAIRE").toDouble(),
            query.value("QUANTITE_STOCK").toInt(),
            query.value("ID_FOURNISSEUR").toInt(),
            QDate::fromString(query.value("DATE_LIVRAISON").toString(), Qt::ISODate)
        );
    }

    return Produit();
}

QList<Produit> DatabaseManager::getProduitsByFournisseur(int idFournisseur)
{
    QList<Produit> list;
    if (!connected) return list;

    QSqlQuery query(db);
    query.prepare("SELECT * FROM PRODUITS WHERE ID_FOURNISSEUR=:id ORDER BY ID_PRODUIT");
    query.bindValue(":id", idFournisseur);
    
    if (query.exec()) {
        while (query.next()) {
            Produit p(
                query.value("ID_PRODUIT").toInt(),
                query.value("NOM_PRODUIT").toString(),
                query.value("DESCRIPTION").toString(),
                query.value("PRIX_UNITAIRE").toDouble(),
                query.value("QUANTITE_STOCK").toInt(),
                query.value("ID_FOURNISSEUR").toInt(),
                QDate::fromString(query.value("DATE_LIVRAISON").toString(), Qt::ISODate)
            );
            list.append(p);
        }
    }

    return list;
}

QList<Produit> DatabaseManager::searchProduits(const QString& searchTerm)
{
    QList<Produit> list;
    if (!connected) return list;

    QSqlQuery query(db);
    query.prepare("SELECT * FROM PRODUITS WHERE "
                  "NOM_PRODUIT LIKE :term OR DESCRIPTION LIKE :term "
                  "ORDER BY ID_PRODUIT");
    
    QString term = "%" + searchTerm + "%";
    query.bindValue(":term", term);
    
    if (query.exec()) {
        while (query.next()) {
            Produit p(
                query.value("ID_PRODUIT").toInt(),
                query.value("NOM_PRODUIT").toString(),
                query.value("DESCRIPTION").toString(),
                query.value("PRIX_UNITAIRE").toDouble(),
                query.value("QUANTITE_STOCK").toInt(),
                query.value("ID_FOURNISSEUR").toInt(),
                QDate::fromString(query.value("DATE_LIVRAISON").toString(), Qt::ISODate)
            );
            list.append(p);
        }
    }

    return list;
}

// ============================================================================
// Relations (1,N between Fournisseur and Produit)
// ============================================================================

int DatabaseManager::countProduitsByFournisseur(int idFournisseur)
{
    if (!connected) return 0;

    QSqlQuery query(db);
    query.prepare("SELECT COUNT(*) as total FROM PRODUITS WHERE ID_FOURNISSEUR=:id");
    query.bindValue(":id", idFournisseur);
    
    if (query.exec() && query.next()) {
        return query.value("total").toInt();
    }

    return 0;
}

bool DatabaseManager::fournisseurHasProduits(int idFournisseur)
{
    return countProduitsByFournisseur(idFournisseur) > 0;
}

