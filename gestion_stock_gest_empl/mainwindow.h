#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QMessageBox>
#include "fournisseur.h"
#include "produit.h"
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
    void on_pushButton_clicked();
    void onLoginClicked();



    void on_btnGestionClients_PageStock_clicked();


    void on_btnGestionEmployes_PageStock_clicked();





    void on_btnBack_PageStock_clicked();

    void on_btnGestionStock_PageClients_clicked();

    void on_btnGestionEmployes_PageClients_clicked();

    void on_btnBack_PageClients_clicked();

    void on_btnGestionStock_Page_Employes_clicked();

    void on_btnGestionClients_Page_Employes_clicked();


    void on_btnBack_Page_Employes_clicked();

    void on_btnGestionSponsors_PageStock_clicked();

    void on_btnGestionFournisseurs_PageStock_clicked();

    void on_btnGestionSponsors_PageClients_clicked();

    void on_btnGestionFournisseurs_PageClients_clicked();

    void on_btnGestionSponsors_Page_Employes_clicked();

    void on_btnGestionFournisseurs_Page_Employes_clicked();

    void on_btnGestionStock_Page_Sponsors_clicked();

    void on_btnGestionClients_Page_Sponsors_clicked();

    void on_btnGestionEmployes_Page_Sponsors_clicked();

    void on_btnGestionFournisseurs_Page_Sponsors_clicked();

    void on_btnBack_Page_Sponsors_clicked();

    void on_btnGestionStock_Page_Fournisseurs_clicked();

    void on_btnGestionClients_Page_Fournisseurs_clicked();


    void on_btnGestionEmployes_PageFournisseurs_clicked();

    void on_btnGestionSponsors_Page_Fournisseurs_clicked();

    void on_btnBack_Page_Fournisseurs_clicked();

    // Fournisseur management slots
    void onAddFournisseurClicked();
    void onUpdateFournisseurClicked();
    void onDeleteFournisseurClicked();
    void onSearchFournisseurClicked();
    void onFournisseurTableClicked(const QModelIndex &index);
    void onViewProduitsByFournisseurClicked();

    // Produit management slots
    void onAddProduitClicked();
    void onUpdateProduitClicked();
    void onDeleteProduitClicked();
    void onSearchProduitClicked();
    void onProduitTableClicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    
    // Database
    DatabaseManager *dbManager;
    bool useDatabase;
    
    // Table models
    QStandardItemModel *fournisseurModel;
    QStandardItemModel *produitModel;
    
    // Current selection
    int selectedFournisseurId;
    int selectedProduitId;
    
    // Helper functions
    void initializeDatabase();
    void setupFournisseurTable();
    void setupProduitTable();
    void refreshFournisseurTable();
    void refreshProduitTable();
    void clearFournisseurInputs();
    void clearProduitInputs();
    void loadFournisseursIntoComboBox();
};
#endif // MAINWINDOW_H
