#include "oracleconnection.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonArray>
#include <QFile>

OracleConnection::OracleConnection()
    : connected(false)
{
}

OracleConnection::~OracleConnection()
{
    if (connected) {
        disconnect();
    }
}

bool OracleConnection::connectToOracle(const QString& host, int port, 
                                       const QString& sid, 
                                       const QString& username, 
                                       const QString& password)
{
    // Create Oracle connection
    db = QSqlDatabase::addDatabase("QOCI"); // Oracle Call Interface
    
    // Connection string format: hostname:port/sid
    QString connectionString = QString("%1:%2/%3").arg(host).arg(port).arg(sid);
    
    db.setHostName(host);
    db.setPort(port);
    db.setDatabaseName(sid);
    db.setUserName(username);
    db.setPassword(password);
    
    // Alternative: Use connection string directly
    // db.setDatabaseName(connectionString);
    
    if (db.open()) {
        connected = true;
        lastError.clear();
        qDebug() << "✅ Connected to Oracle Database successfully!";
        qDebug() << "Database version:" << getDatabaseVersion();
        return true;
    } else {
        connected = false;
        lastError = db.lastError().text();
        qDebug() << "❌ Oracle connection failed:" << lastError;
        return false;
    }
}

void OracleConnection::disconnect()
{
    if (connected) {
        db.close();
        connected = false;
        qDebug() << "Disconnected from Oracle Database";
    }
}

bool OracleConnection::testConnection()
{
    if (!connected) return false;
    
    QSqlQuery query(db);
    return query.exec("SELECT 1 FROM DUAL");
}

QString OracleConnection::getDatabaseVersion()
{
    if (!connected) return "Not connected";
    
    QSqlQuery query(db);
    if (query.exec("SELECT BANNER FROM V$VERSION WHERE ROWNUM = 1")) {
        if (query.next()) {
            return query.value(0).toString();
        }
    }
    return "Unknown version";
}

bool OracleConnection::createTables()
{
    if (!connected) {
        lastError = "Not connected to database";
        return false;
    }
    
    QSqlQuery query(db);
    
    // Create FOURNISSEURS table
    QString createTableSQL = R"(
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
    
    if (!query.exec(createTableSQL)) {
        lastError = query.lastError().text();
        qDebug() << "Error creating table:" << lastError;
        return false;
    }
    
    // Create sequence for auto-increment ID
    QString createSequenceSQL = R"(
        CREATE SEQUENCE FOURNISSEUR_SEQ
        START WITH 1
        INCREMENT BY 1
        NOCACHE
        NOCYCLE
    )";
    
    if (!query.exec(createSequenceSQL)) {
        lastError = query.lastError().text();
        qDebug() << "Error creating sequence:" << lastError;
        // Continue even if sequence creation fails (might already exist)
    }
    
    // Create trigger for auto-increment
    QString createTriggerSQL = R"(
        CREATE OR REPLACE TRIGGER FOURNISSEUR_BI
        BEFORE INSERT ON FOURNISSEURS
        FOR EACH ROW
        BEGIN
            IF :NEW.ID_FOURNISSEUR IS NULL THEN
                SELECT FOURNISSEUR_SEQ.NEXTVAL INTO :NEW.ID_FOURNISSEUR FROM DUAL;
            END IF;
        END;
    )";
    
    if (!query.exec(createTriggerSQL)) {
        lastError = query.lastError().text();
        qDebug() << "Error creating trigger:" << lastError;
    }
    
    qDebug() << "✅ Tables created successfully!";
    return true;
}

bool OracleConnection::dropTables()
{
    if (!connected) return false;
    
    QSqlQuery query(db);
    
    // Drop in order: trigger, table, sequence
    query.exec("DROP TRIGGER FOURNISSEUR_BI");
    query.exec("DROP TABLE FOURNISSEURS");
    query.exec("DROP SEQUENCE FOURNISSEUR_SEQ");
    
    return true;
}

bool OracleConnection::insertFournisseur(const Fournisseur& f)
{
    if (!connected) {
        lastError = "Not connected to database";
        return false;
    }
    
    QSqlQuery query(db);
    query.prepare(R"(
        INSERT INTO FOURNISSEURS 
        (ID_FOURNISSEUR, NOM, ADRESSE, EMAIL, TELEPHONE, TYPE_PRODUITS, 
         HISTORIQUE_LIVRAISONS, IS_ACTIVE)
        VALUES (:id, :nom, :adresse, :email, :telephone, :type, :historique, :active)
    )");
    
    query.bindValue(":id", f.getIdFournisseur());
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

bool OracleConnection::updateFournisseur(const Fournisseur& f)
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

bool OracleConnection::deleteFournisseur(int id)
{
    if (!connected) return false;
    
    QSqlQuery query(db);
    query.prepare("DELETE FROM FOURNISSEURS WHERE ID_FOURNISSEUR = :id");
    query.bindValue(":id", id);
    
    return query.exec();
}

Fournisseur OracleConnection::getFournisseurById(int id, bool& success)
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

QList<Fournisseur> OracleConnection::getAllFournisseurs(bool& success)
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

QList<Fournisseur> OracleConnection::searchFournisseurs(const QString& searchText, bool& success)
{
    QList<Fournisseur> list;
    success = false;
    
    if (!connected) return list;
    
    QSqlQuery query(db);
    query.prepare(R"(
        SELECT * FROM FOURNISSEURS 
        WHERE UPPER(NOM) LIKE :search 
           OR UPPER(EMAIL) LIKE :search
           OR UPPER(TYPE_PRODUITS) LIKE :search
        ORDER BY ID_FOURNISSEUR
    )");
    
    QString searchPattern = "%" + searchText.toUpper() + "%";
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

int OracleConnection::getTotalCount()
{
    if (!connected) return 0;
    
    QSqlQuery query(db);
    if (query.exec("SELECT COUNT(*) FROM FOURNISSEURS") && query.next()) {
        return query.value(0).toInt();
    }
    return 0;
}

QMap<QString, int> OracleConnection::getProductTypeDistribution()
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

QList<Fournisseur> OracleConnection::getFournisseursByType(const QString& type)
{
    QList<Fournisseur> list;
    
    if (!connected) return list;
    
    QSqlQuery query(db);
    query.prepare("SELECT * FROM FOURNISSEURS WHERE TYPE_PRODUITS = :type");
    query.bindValue(":type", type);
    
    if (query.exec()) {
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
    }
    
    return list;
}

bool OracleConnection::importFromJson(const QList<Fournisseur>& fournisseurs)
{
    if (!connected) return false;
    
    db.transaction(); // Start transaction
    
    for (const Fournisseur& f : fournisseurs) {
        if (!insertFournisseur(f)) {
            db.rollback();
            return false;
        }
    }
    
    return db.commit();
}

bool OracleConnection::exportToJson(const QString& filename)
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

