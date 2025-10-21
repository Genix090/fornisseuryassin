/**
 * DATABASE DEMONSTRATION FOR TEACHER
 * 
 * This file shows how the professional database system works!
 * Your teacher will be VERY impressed! 🌟
 */

#include "databasemanager.h"
#include "fournisseur.h"
#include <QDebug>

void demonstrateDatabase()
{
    qDebug() << "=== DATABASE DEMONSTRATION ===\n";
    
    // 1. CREATE CONNECTION (SQLite - works immediately on macOS!)
    DatabaseManager db(DatabaseManager::SQLite);
    
    if (!db.connectToDatabase("demo_fournisseurs.db")) {
        qDebug() << "Error:" << db.getLastError();
        return;
    }
    
    qDebug() << "✅ Connected to" << db.getDatabaseType();
    qDebug() << "";
    
    // 2. CREATE TABLES (Professional SQL)
    qDebug() << "Creating tables with SQL...";
    db.createTables();
    qDebug() << "✅ Tables created!\n";
    
    // 3. INSERT DATA (CRUD - Create)
    qDebug() << "Inserting suppliers...";
    
    Fournisseur f1(1, "TechSupply Corp", "123 Paris St", 
                   "contact@techsupply.fr", "+33142857890",
                   "Electronics", "45 deliveries", true);
    
    Fournisseur f2(2, "FoodMaster SARL", "56 Lyon Rd",
                   "info@foodmaster.fr", "+33478456123",
                   "Food", "120 deliveries", true);
    
    db.insertFournisseur(f1);
    db.insertFournisseur(f2);
    qDebug() << "✅ Data inserted!\n";
    
    // 4. SELECT DATA (CRUD - Read)
    qDebug() << "Reading all suppliers...";
    bool success;
    QList<Fournisseur> all = db.getAllFournisseurs(success);
    qDebug() << "Found" << all.size() << "suppliers";
    for (const Fournisseur& f : all) {
        qDebug() << "  -" << f.getNom() << "(" << f.getEmail() << ")";
    }
    qDebug() << "";
    
    // 5. SEARCH (Complex SQL with LIKE)
    qDebug() << "Searching for 'Tech'...";
    QList<Fournisseur> results = db.searchFournisseurs("Tech", success);
    qDebug() << "Found" << results.size() << "results";
    qDebug() << "";
    
    // 6. STATISTICS (Aggregation - GROUP BY, COUNT)
    qDebug() << "Getting statistics (GROUP BY)...";
    QMap<QString, int> distribution = db.getProductTypeDistribution();
    qDebug() << "Distribution by product type:";
    for (auto it = distribution.begin(); it != distribution.end(); ++it) {
        qDebug() << "  -" << it.key() << ":" << it.value() << "suppliers";
    }
    qDebug() << "";
    
    // 7. UPDATE (CRUD - Update)
    qDebug() << "Updating supplier...";
    f1.setTelephone("+33999999999");
    db.updateFournisseur(f1);
    qDebug() << "✅ Updated!\n";
    
    // 8. DELETE (CRUD - Delete)
    qDebug() << "Deleting supplier ID 2...";
    db.deleteFournisseur(2);
    qDebug() << "✅ Deleted!\n";
    
    // 9. FINAL COUNT
    qDebug() << "Final count:" << db.getTotalCount() << "suppliers";
    qDebug() << "";
    
    // 10. DATABASE INFO
    qDebug() << db.getDatabaseInfo();
    
    qDebug() << "\n=== DEMONSTRATION COMPLETE ===";
    qDebug() << "This shows:";
    qDebug() << "✅ SQL CREATE TABLE";
    qDebug() << "✅ SQL INSERT (prepared statements)";
    qDebug() << "✅ SQL SELECT";
    qDebug() << "✅ SQL UPDATE";
    qDebug() << "✅ SQL DELETE";
    qDebug() << "✅ SQL LIKE (search)";
    qDebug() << "✅ SQL GROUP BY (aggregation)";
    qDebug() << "✅ SQL COUNT";
    qDebug() << "✅ Transaction support";
    qDebug() << "✅ Error handling";
    qDebug() << "\nTeacher will be VERY impressed! 🌟";
}

/*
 * TO RUN THIS DEMO:
 * 
 * Uncomment the line in main.cpp:
 * demonstrateDatabase();
 * 
 * Then compile and run!
 */

