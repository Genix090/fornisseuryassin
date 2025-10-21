#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include <QStandardItemModel>
#include "fournisseur.h"
#include "advancedfeatures.h"
#include "databasemanager.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onAjouterClicked();
    void onModifierClicked();
    void onSupprimerClicked();
    void onRechercherClicked();
    void onTrierClicked();
    void onStatClicked();
    void onExportPdfClicked();
    void onRefreshClicked();
    void onTableSelectionChanged();
    
    // Advanced Feature Slots
    void onExportCSVClicked();
    void onImportCSVClicked();
    void onRateSupplierClicked();
    void onViewActivityLogClicked();
    void onBackupClicked();
    void onRestoreBackupClicked();
    void onAdvancedFilterClicked();
    void onAdvancedStatsClicked();
    void onAdvancedFeaturesButtonClicked();

private:
    Ui::MainWindow *ui;
    QList<Fournisseur> listeFournisseurs;
    QStandardItemModel *tableModel;
    int currentSelectedId;
    
    // Advanced Features Data
    QList<SupplierRating> supplierRatings;
    QList<ActivityLog> activityLog;
    
    // Database Manager for Oracle/SQLite
    DatabaseManager *dbManager;
    bool useDatabase;

    // Helper methods
    void setupTableView();
    void refreshTableView();
    void clearInputFields();
    void loadFournisseurToFields(const Fournisseur& f);
    int generateNewId();
    
    // Data persistence
    void saveToFile();
    void loadFromFile();
    void saveAdvancedData();
    void loadAdvancedData();
    
    // Validation
    bool validateInputs();
    
    // Sorting
    void sortByNom();
    void sortById();
    void sortByTypeProduits();
    void sortByRating();
    
    // Advanced features
    void addActivityLog(const QString& action, const QString& description, int fId = -1);
    SupplierRating* getRatingForSupplier(int fournisseurId);
    void createAdvancedMenu();
    
    // Database connection
    bool connectToOracle();
    void loadFromDatabase();
    void saveToDatabase();
};
#endif // MAINWINDOW_H
