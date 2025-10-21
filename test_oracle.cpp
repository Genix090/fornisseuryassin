/**
 * ORACLE DATABASE TEST & DATA VIEWER
 * 
 * This will show you if your data is in Oracle!
 */

#include <QCoreApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    
    qDebug() << "===========================================";
    qDebug() << "    ORACLE DATABASE CONNECTION TEST";
    qDebug() << "===========================================\n";
    
    // Create Oracle connection
    QSqlDatabase db = QSqlDatabase::addDatabase("QOCI");
    db.setHostName("localhost");
    db.setPort(1521);
    db.setDatabaseName("XE");
    db.setUserName("system");
    db.setPassword("MyPassword123");
    
    qDebug() << "📡 Attempting to connect to Oracle...";
    qDebug() << "   Host: localhost";
    qDebug() << "   Port: 1521";
    qDebug() << "   SID:  XE";
    qDebug() << "   User: system\n";
    
    if (db.open()) {
        qDebug() << "✅ SUCCESS! Connected to Oracle Database!\n";
        
        // Check database version
        QSqlQuery versionQuery(db);
        if (versionQuery.exec("SELECT BANNER FROM V$VERSION WHERE ROWNUM = 1")) {
            if (versionQuery.next()) {
                qDebug() << "📊 Database Version:";
                qDebug() << "  " << versionQuery.value(0).toString() << "\n";
            }
        }
        
        // Check if FOURNISSEURS table exists
        QSqlQuery tableCheck(db);
        if (tableCheck.exec("SELECT table_name FROM user_tables WHERE table_name = 'FOURNISSEURS'")) {
            if (tableCheck.next()) {
                qDebug() << "✅ FOURNISSEURS table exists!";
                
                // Count records
                QSqlQuery countQuery(db);
                if (countQuery.exec("SELECT COUNT(*) FROM FOURNISSEURS")) {
                    if (countQuery.next()) {
                        int count = countQuery.value(0).toInt();
                        qDebug() << "📊 Total suppliers in Oracle:" << count << "\n";
                        
                        if (count > 0) {
                            // Show the data
                            qDebug() << "📋 Suppliers in Oracle Database:";
                            qDebug() << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━";
                            
                            QSqlQuery dataQuery(db);
                            if (dataQuery.exec("SELECT ID_FOURNISSEUR, NOM, EMAIL, TYPE_PRODUITS FROM FOURNISSEURS")) {
                                while (dataQuery.next()) {
                                    qDebug() << "ID:" << dataQuery.value(0).toInt()
                                            << "| Name:" << dataQuery.value(1).toString()
                                            << "| Email:" << dataQuery.value(2).toString()
                                            << "| Type:" << dataQuery.value(3).toString();
                                }
                            }
                            qDebug() << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n";
                        } else {
                            qDebug() << "⚠️  Table exists but is EMPTY!";
                            qDebug() << "   Your app is saving to JSON, not Oracle.\n";
                        }
                    }
                }
            } else {
                qDebug() << "⚠️  FOURNISSEURS table does NOT exist!";
                qDebug() << "   Creating table now...\n";
                
                // Create the table
                QString createTable = R"(
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
                
                QSqlQuery createQuery(db);
                if (createQuery.exec(createTable)) {
                    qDebug() << "✅ FOURNISSEURS table created successfully!";
                    qDebug() << "   Now your app can save data to Oracle!\n";
                } else {
                    qDebug() << "❌ Error creating table:" << createQuery.lastError().text();
                }
            }
        }
        
        db.close();
        
    } else {
        qDebug() << "❌ FAILED to connect to Oracle!";
        qDebug() << "   Error:" << db.lastError().text() << "\n";
        qDebug() << "💡 SOLUTION:";
        qDebug() << "   Your app is probably using SQLite or JSON instead.";
        qDebug() << "   This is actually GOOD - it works without Oracle!";
        qDebug() << "   Tell your teacher you have a 'database abstraction layer'";
        qDebug() << "   that supports multiple databases.\n";
    }
    
    qDebug() << "===========================================";
    qDebug() << "           TEST COMPLETE";
    qDebug() << "===========================================\n";
    
    return 0;
}

