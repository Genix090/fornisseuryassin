#ifndef ADVANCEDFEATURES_H
#define ADVANCEDFEATURES_H

#include <QString>
#include <QDateTime>
#include <QList>
#include <QJsonObject>
#include <QJsonArray>

// Activity Log Entry
class ActivityLog
{
private:
    QString action;        // "ADD", "MODIFY", "DELETE", "EXPORT", etc.
    QString description;
    QDateTime timestamp;
    QString userName;
    int fournisseurId;

public:
    ActivityLog(const QString& action, const QString& desc, int fId = -1);
    
    QString getAction() const { return action; }
    QString getDescription() const { return description; }
    QDateTime getTimestamp() const { return timestamp; }
    QString getUserName() const { return userName; }
    int getFournisseurId() const { return fournisseurId; }
    
    QJsonObject toJson() const;
    static ActivityLog fromJson(const QJsonObject& json);
    QString toString() const;
};

// Supplier Rating System
class SupplierRating
{
private:
    int fournisseurId;
    int qualityScore;      // 1-5 stars
    int deliveryScore;     // 1-5 stars
    int priceScore;        // 1-5 stars
    int communicationScore; // 1-5 stars
    QString comments;
    QDateTime ratedDate;
    int totalOrders;
    int onTimeDeliveries;
    double averageDeliveryTime; // in days

public:
    SupplierRating();
    SupplierRating(int fId, int quality, int delivery, int price, int communication,
                   const QString& comments = "");
    
    int getFournisseurId() const { return fournisseurId; }
    int getQualityScore() const { return qualityScore; }
    int getDeliveryScore() const { return deliveryScore; }
    int getPriceScore() const { return priceScore; }
    int getCommunicationScore() const { return communicationScore; }
    QString getComments() const { return comments; }
    int getTotalOrders() const { return totalOrders; }
    int getOnTimeDeliveries() const { return onTimeDeliveries; }
    double getAverageDeliveryTime() const { return averageDeliveryTime; }
    
    void setQualityScore(int score) { qualityScore = score; }
    void setDeliveryScore(int score) { deliveryScore = score; }
    void setPriceScore(int score) { priceScore = score; }
    void setCommunicationScore(int score) { communicationScore = score; }
    void setComments(const QString& c) { comments = c; }
    void setTotalOrders(int total) { totalOrders = total; }
    void setOnTimeDeliveries(int onTime) { onTimeDeliveries = onTime; }
    void setAverageDeliveryTime(double avgDays) { averageDeliveryTime = avgDays; }
    
    double getOverallRating() const;
    double getOnTimePercentage() const;
    QString getPerformanceLevel() const; // "Excellent", "Good", "Average", "Poor"
    
    QJsonObject toJson() const;
    static SupplierRating fromJson(const QJsonObject& json);
};

// Advanced Filter Criteria
class FilterCriteria
{
public:
    QString nom;
    QString email;
    QString typeProduits;
    QString adresse;
    int minRating;
    int maxRating;
    bool activeOnly;
    
    FilterCriteria();
    bool matches(const QString& fNom, const QString& fEmail, 
                const QString& fType, const QString& fAddr, 
                int rating, bool isActive) const;
};

// Backup Manager
class BackupManager
{
public:
    static bool createBackup(const QString& sourceFile, QString& backupPath);
    static bool restoreBackup(const QString& backupFile, const QString& targetFile);
    static QStringList listBackups(const QString& backupDir = "backups");
    static bool autoBackup(const QString& sourceFile, int maxBackups = 10);
};

// CSV Export/Import
class CSVManager
{
public:
    static bool exportToCSV(const QString& fileName, const QList<class Fournisseur>& fournisseurs);
    static QList<class Fournisseur> importFromCSV(const QString& fileName, bool& success);
    static QString escapeCSV(const QString& field);
    static QStringList parseCSVLine(const QString& line);
};

// Statistics Calculator
class AdvancedStats
{
public:
    struct Stats {
        int totalSuppliers;
        int activeSuppliers;
        int inactiveSuppliers;
        double averageRating;
        QString topRatedSupplier;
        QString mostCommonProductType;
        int totalActivities;
        QMap<QString, int> productTypeDistribution;
        QMap<int, int> ratingDistribution;
    };
    
    static Stats calculateStats(const QList<class Fournisseur>& fournisseurs,
                                const QList<SupplierRating>& ratings,
                                const QList<ActivityLog>& activities);
};

#endif // ADVANCEDFEATURES_H

