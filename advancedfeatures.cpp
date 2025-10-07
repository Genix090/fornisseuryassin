#include "advancedfeatures.h"
#include "fournisseur.h"
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QRegularExpression>

// ===== ActivityLog Implementation =====
ActivityLog::ActivityLog(const QString& action, const QString& desc, int fId)
    : action(action), description(desc), fournisseurId(fId)
{
    timestamp = QDateTime::currentDateTime();
    userName = "Admin"; // Could be extended to support multiple users
}

QJsonObject ActivityLog::toJson() const
{
    QJsonObject json;
    json["action"] = action;
    json["description"] = description;
    json["timestamp"] = timestamp.toString(Qt::ISODate);
    json["userName"] = userName;
    json["fournisseurId"] = fournisseurId;
    return json;
}

ActivityLog ActivityLog::fromJson(const QJsonObject& json)
{
    ActivityLog log(json["action"].toString(), 
                   json["description"].toString(),
                   json["fournisseurId"].toInt());
    log.timestamp = QDateTime::fromString(json["timestamp"].toString(), Qt::ISODate);
    log.userName = json["userName"].toString();
    return log;
}

QString ActivityLog::toString() const
{
    return QString("[%1] %2: %3")
        .arg(timestamp.toString("yyyy-MM-dd hh:mm:ss"))
        .arg(action)
        .arg(description);
}

// ===== SupplierRating Implementation =====
SupplierRating::SupplierRating()
    : fournisseurId(-1), qualityScore(0), deliveryScore(0), priceScore(0),
      communicationScore(0), totalOrders(0), onTimeDeliveries(0), averageDeliveryTime(0.0)
{
    ratedDate = QDateTime::currentDateTime();
}

SupplierRating::SupplierRating(int fId, int quality, int delivery, int price, 
                               int communication, const QString& comments)
    : fournisseurId(fId), qualityScore(quality), deliveryScore(delivery),
      priceScore(price), communicationScore(communication), comments(comments),
      totalOrders(0), onTimeDeliveries(0), averageDeliveryTime(0.0)
{
    ratedDate = QDateTime::currentDateTime();
}

double SupplierRating::getOverallRating() const
{
    return (qualityScore + deliveryScore + priceScore + communicationScore) / 4.0;
}

double SupplierRating::getOnTimePercentage() const
{
    if (totalOrders == 0) return 0.0;
    return (onTimeDeliveries * 100.0) / totalOrders;
}

QString SupplierRating::getPerformanceLevel() const
{
    double rating = getOverallRating();
    if (rating >= 4.5) return "Excellent";
    if (rating >= 3.5) return "Good";
    if (rating >= 2.5) return "Average";
    return "Poor";
}

QJsonObject SupplierRating::toJson() const
{
    QJsonObject json;
    json["fournisseurId"] = fournisseurId;
    json["qualityScore"] = qualityScore;
    json["deliveryScore"] = deliveryScore;
    json["priceScore"] = priceScore;
    json["communicationScore"] = communicationScore;
    json["comments"] = comments;
    json["ratedDate"] = ratedDate.toString(Qt::ISODate);
    json["totalOrders"] = totalOrders;
    json["onTimeDeliveries"] = onTimeDeliveries;
    json["averageDeliveryTime"] = averageDeliveryTime;
    return json;
}

SupplierRating SupplierRating::fromJson(const QJsonObject& json)
{
    SupplierRating rating(
        json["fournisseurId"].toInt(),
        json["qualityScore"].toInt(),
        json["deliveryScore"].toInt(),
        json["priceScore"].toInt(),
        json["communicationScore"].toInt(),
        json["comments"].toString()
    );
    rating.ratedDate = QDateTime::fromString(json["ratedDate"].toString(), Qt::ISODate);
    rating.totalOrders = json["totalOrders"].toInt();
    rating.onTimeDeliveries = json["onTimeDeliveries"].toInt();
    rating.averageDeliveryTime = json["averageDeliveryTime"].toDouble();
    return rating;
}

// ===== FilterCriteria Implementation =====
FilterCriteria::FilterCriteria()
    : minRating(0), maxRating(5), activeOnly(false)
{
}

bool FilterCriteria::matches(const QString& fNom, const QString& fEmail,
                            const QString& fType, const QString& fAddr,
                            int rating, bool isActive) const
{
    if (activeOnly && !isActive) return false;
    if (rating < minRating || rating > maxRating) return false;
    if (!nom.isEmpty() && !fNom.contains(nom, Qt::CaseInsensitive)) return false;
    if (!email.isEmpty() && !fEmail.contains(email, Qt::CaseInsensitive)) return false;
    if (!typeProduits.isEmpty() && !fType.contains(typeProduits, Qt::CaseInsensitive)) return false;
    if (!adresse.isEmpty() && !fAddr.contains(adresse, Qt::CaseInsensitive)) return false;
    return true;
}

// ===== BackupManager Implementation =====
bool BackupManager::createBackup(const QString& sourceFile, QString& backupPath)
{
    QDir backupDir("backups");
    if (!backupDir.exists()) {
        backupDir.mkpath(".");
    }
    
    QString timestamp = QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss");
    backupPath = QString("backups/fournisseurs_backup_%1.json").arg(timestamp);
    
    return QFile::copy(sourceFile, backupPath);
}

bool BackupManager::restoreBackup(const QString& backupFile, const QString& targetFile)
{
    if (!QFile::exists(backupFile)) return false;
    
    // Remove existing target file
    if (QFile::exists(targetFile)) {
        QFile::remove(targetFile);
    }
    
    return QFile::copy(backupFile, targetFile);
}

QStringList BackupManager::listBackups(const QString& backupDir)
{
    QDir dir(backupDir);
    QStringList filters;
    filters << "*.json";
    return dir.entryList(filters, QDir::Files, QDir::Time);
}

bool BackupManager::autoBackup(const QString& sourceFile, int maxBackups)
{
    QString backupPath;
    if (!createBackup(sourceFile, backupPath)) {
        return false;
    }
    
    // Remove old backups if exceeding max
    QStringList backups = listBackups();
    while (backups.size() > maxBackups) {
        QFile::remove("backups/" + backups.last());
        backups.removeLast();
    }
    
    return true;
}

// ===== CSVManager Implementation =====
QString CSVManager::escapeCSV(const QString& field)
{
    QString escaped = field;
    if (escaped.contains(',') || escaped.contains('"') || escaped.contains('\n')) {
        escaped.replace('"', "\"\"");
        escaped = '"' + escaped + '"';
    }
    return escaped;
}

QStringList CSVManager::parseCSVLine(const QString& line)
{
    QStringList fields;
    QString currentField;
    bool inQuotes = false;
    
    for (int i = 0; i < line.length(); ++i) {
        QChar c = line[i];
        
        if (c == '"') {
            if (inQuotes && i + 1 < line.length() && line[i + 1] == '"') {
                currentField += '"';
                ++i;
            } else {
                inQuotes = !inQuotes;
            }
        } else if (c == ',' && !inQuotes) {
            fields.append(currentField);
            currentField.clear();
        } else {
            currentField += c;
        }
    }
    fields.append(currentField);
    
    return fields;
}

bool CSVManager::exportToCSV(const QString& fileName, const QList<Fournisseur>& fournisseurs)
{
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return false;
    }
    
    QTextStream out(&file);
    
    // Header
    out << "ID,Nom,Adresse,Email,Telephone,TypeProduits,HistoriqueLivraisons\n";
    
    // Data
    for (const Fournisseur& f : fournisseurs) {
        out << f.getIdFournisseur() << ","
            << escapeCSV(f.getNom()) << ","
            << escapeCSV(f.getAdresse()) << ","
            << escapeCSV(f.getEmail()) << ","
            << escapeCSV(f.getTelephone()) << ","
            << escapeCSV(f.getTypeProduits()) << ","
            << escapeCSV(f.getHistoriqueLivraisons()) << "\n";
    }
    
    file.close();
    return true;
}

QList<Fournisseur> CSVManager::importFromCSV(const QString& fileName, bool& success)
{
    QList<Fournisseur> fournisseurs;
    success = false;
    
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return fournisseurs;
    }
    
    QTextStream in(&file);
    
    // Skip header
    if (!in.atEnd()) {
        in.readLine();
    }
    
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = parseCSVLine(line);
        
        if (fields.size() >= 7) {
            Fournisseur f(
                fields[0].toInt(),
                fields[1],
                fields[2],
                fields[3],
                fields[4],
                fields[5],
                fields[6]
            );
            fournisseurs.append(f);
        }
    }
    
    file.close();
    success = true;
    return fournisseurs;
}

// ===== AdvancedStats Implementation =====
AdvancedStats::Stats AdvancedStats::calculateStats(const QList<Fournisseur>& fournisseurs,
                                                   const QList<SupplierRating>& ratings,
                                                   const QList<ActivityLog>& activities)
{
    Stats stats;
    stats.totalSuppliers = fournisseurs.size();
    stats.activeSuppliers = 0;
    stats.inactiveSuppliers = 0;
    stats.averageRating = 0.0;
    stats.totalActivities = activities.size();
    
    // Count active/inactive
    for (const Fournisseur& f : fournisseurs) {
        if (f.getIsActive()) {
            stats.activeSuppliers++;
        } else {
            stats.inactiveSuppliers++;
        }
        
        // Product type distribution
        QString type = f.getTypeProduits();
        if (type.isEmpty()) type = "Non spécifié";
        stats.productTypeDistribution[type]++;
    }
    
    // Calculate average rating and find top rated
    double totalRating = 0.0;
    double maxRating = 0.0;
    int maxRatingId = -1;
    
    for (const SupplierRating& rating : ratings) {
        double overall = rating.getOverallRating();
        totalRating += overall;
        
        int roundedRating = qRound(overall);
        stats.ratingDistribution[roundedRating]++;
        
        if (overall > maxRating) {
            maxRating = overall;
            maxRatingId = rating.getFournisseurId();
        }
    }
    
    if (!ratings.isEmpty()) {
        stats.averageRating = totalRating / ratings.size();
    }
    
    // Find top rated supplier name
    if (maxRatingId != -1) {
        for (const Fournisseur& f : fournisseurs) {
            if (f.getIdFournisseur() == maxRatingId) {
                stats.topRatedSupplier = f.getNom();
                break;
            }
        }
    }
    
    // Find most common product type
    int maxCount = 0;
    for (auto it = stats.productTypeDistribution.begin(); 
         it != stats.productTypeDistribution.end(); ++it) {
        if (it.value() > maxCount) {
            maxCount = it.value();
            stats.mostCommonProductType = it.key();
        }
    }
    
    return stats;
}

