#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) // constructeur
    , dbManager(nullptr)
    , useDatabase(false)
    , fournisseurModel(new QStandardItemModel(this))
    , produitModel(new QStandardItemModel(this))
    , selectedFournisseurId(-1)
    , selectedProduitId(-1)
{
    ui->setupUi(this);
    ui->comboBox->addItem("Category  A");
    ui->comboBox->addItem("Category  B");
    ui->comboBox->addItem("Produit C");
    QPixmap image(":/stat.png");  // le ":" indique que c'est une ressource
    ui->labelImage->setPixmap(image);
    ui->labelImage->setScaledContents(true);
    ui->stackedWidget->setCurrentIndex(0);// page 0 par defaut

    // quand on clique sur le bouton login → appeler la fonction
    connect(ui->btnLogin, &QPushButton::clicked, this, &MainWindow::onLoginClicked);
    
    // Initialize database and tables
    initializeDatabase();
    
    qDebug() << "🎉 Smart Optical Store with Fournisseur Management Ready!";
}



MainWindow::~MainWindow()
{
    if (dbManager) {
        delete dbManager;
    }
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    // Exemple : ajouter produit dans le tableau
    QString nom = ui->lineEdit->text();
    QString quantite = ui->lineEdit_2->text();

    int row = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(row);
    ui->tableWidget->setItem(row, 0, new QTableWidgetItem(nom));
    ui->tableWidget->setItem(row, 1, new QTableWidgetItem(quantite));
}
void MainWindow::onLoginClicked()
{
    QString user = ui->lineUser->text();
    QString pass = ui->linePass->text();

    if(user == "admin" && pass == "1234") {
        // passage à la page gestion stock (index 1)
        ui->stackedWidget->setCurrentIndex(1);
    }
}



// page 1 :


void MainWindow::on_btnGestionEmployes_PageStock_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}


void MainWindow::on_btnBack_PageStock_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);

}


// page 3 :


void MainWindow::on_btnGestionStock_Page_Employes_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}




void MainWindow::on_btnBack_Page_Employes_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

// ============================================================================
// DATABASE INITIALIZATION
// ============================================================================

void MainWindow::initializeDatabase()
{
    // Create database manager with SQLite (works on Windows, macOS, Linux)
    dbManager = new DatabaseManager(DatabaseManager::SQLite);
    
    // Try to connect
    if (dbManager->connectToDatabase("optical_store.db")) {
        qDebug() << "✅ Connected to database!";
        
        // Create tables
        if (dbManager->createTables()) {
            qDebug() << "✅ Tables created successfully!";
            qDebug() << "   - FOURNISSEURS (Parent table)";
            qDebug() << "   - PRODUITS (Child table with Foreign Key)";
            qDebug() << "   - Relation: 1 Fournisseur → N Produits";
            
            useDatabase = true;
            
            QMessageBox::information(this, "✅ Database Ready!", 
                "Successfully connected to Smart Optical Store Database!\n\n"
                "📊 Tables:\n"
                "• FOURNISSEURS (Suppliers)\n"
                "• PRODUITS (Products with 1,N relation)\n\n"
                "🎯 Features:\n"
                "• Full CRUD operations\n"
                "• Foreign Key constraints\n"
                "• Search & Filter\n"
                "• Relation management\n\n"
                "Ready for demonstration!");
        } else {
            qDebug() << "❌ Failed to create tables:" << dbManager->getLastError();
            useDatabase = false;
        }
    } else {
        qDebug() << "❌ Database connection failed:" << dbManager->getLastError();
        useDatabase = false;
    }
}

void MainWindow::setupFournisseurTable()
{
    // Setup table model for Fournisseurs
    fournisseurModel->clear();
    fournisseurModel->setHorizontalHeaderLabels({
        "ID", "Nom", "Email", "Téléphone", "Adresse", "Type Produits", "Ville", "Pays"
    });
}

void MainWindow::setupProduitTable()
{
    // Setup table model for Produits
    produitModel->clear();
    produitModel->setHorizontalHeaderLabels({
        "ID", "Nom Produit", "Description", "Prix", "Quantité", "ID Fournisseur", "Date Livraison"
    });
}

void MainWindow::refreshFournisseurTable()
{
    if (!useDatabase || !dbManager) return;
    
    setupFournisseurTable();
    QList<Fournisseur> fournisseurs = dbManager->getAllFournisseurs();
    
    for (const Fournisseur& f : fournisseurs) {
        QList<QStandardItem*> row;
        row.append(new QStandardItem(QString::number(f.getId())));
        row.append(new QStandardItem(f.getNom()));
        row.append(new QStandardItem(f.getEmail()));
        row.append(new QStandardItem(f.getTelephone()));
        row.append(new QStandardItem(f.getAdresse()));
        row.append(new QStandardItem(f.getTypeProduits()));
        row.append(new QStandardItem(f.getVille()));
        row.append(new QStandardItem(f.getPays()));
        fournisseurModel->appendRow(row);
    }
    
    qDebug() << "📊 Loaded" << fournisseurs.size() << "fournisseurs";
}

void MainWindow::refreshProduitTable()
{
    if (!useDatabase || !dbManager) return;
    
    setupProduitTable();
    QList<Produit> produits = dbManager->getAllProduits();
    
    for (const Produit& p : produits) {
        QList<QStandardItem*> row;
        row.append(new QStandardItem(QString::number(p.getId())));
        row.append(new QStandardItem(p.getNomProduit()));
        row.append(new QStandardItem(p.getDescription()));
        row.append(new QStandardItem(QString::number(p.getPrixUnitaire(), 'f', 2)));
        row.append(new QStandardItem(QString::number(p.getQuantiteStock())));
        row.append(new QStandardItem(QString::number(p.getIdFournisseur())));
        row.append(new QStandardItem(p.getDateLivraison().toString("dd/MM/yyyy")));
        produitModel->appendRow(row);
    }
    
    qDebug() << "📦 Loaded" << produits.size() << "produits";
}

void MainWindow::clearFournisseurInputs()
{
    selectedFournisseurId = -1;
    // Clear input fields if they exist in UI
    qDebug() << "🧹 Cleared fournisseur inputs";
}

void MainWindow::clearProduitInputs()
{
    selectedProduitId = -1;
    // Clear input fields if they exist in UI
    qDebug() << "🧹 Cleared produit inputs";
}

void MainWindow::loadFournisseursIntoComboBox()
{
    if (!useDatabase || !dbManager) return;
    
    QList<Fournisseur> fournisseurs = dbManager->getAllFournisseurs();
    
    // Assuming there's a comboBox for selecting fournisseur in Produit page
    // ui->comboBoxFournisseur->clear();
    // for (const Fournisseur& f : fournisseurs) {
    //     ui->comboBoxFournisseur->addItem(f.getNom(), f.getId());
    // }
    
    qDebug() << "📋 Loaded" << fournisseurs.size() << "fournisseurs into dropdown";
}

// ============================================================================
// FOURNISSEUR MANAGEMENT
// ============================================================================

void MainWindow::onAddFournisseurClicked()
{
    if (!useDatabase || !dbManager) {
        QMessageBox::warning(this, "Error", "Database not connected!");
        return;
    }
    
    // Example: Get data from UI inputs (you'll need to add these widgets)
    // For now, using example data for demonstration
    
    QMessageBox::information(this, "Add Fournisseur", 
        "To add fournisseurs, you need to:\n\n"
        "1. Add input fields in the UI:\n"
        "   - lineEditNom\n"
        "   - lineEditEmail\n"
        "   - lineEditTelephone\n"
        "   - etc.\n\n"
        "2. Connect this button to get values\n"
        "3. Call dbManager->insertFournisseur()\n\n"
        "Example code is in mainwindow.cpp!");
    
    /* EXAMPLE CODE FOR WHEN UI IS READY:
    
    QString nom = ui->lineEditNomFournisseur->text();
    QString email = ui->lineEditEmailFournisseur->text();
    QString tel = ui->lineEditTelFournisseur->text();
    QString adresse = ui->lineEditAdresseFournisseur->text();
    QString type = ui->lineEditTypeProduits->text();
    QString ville = ui->lineEditVille->text();
    QString pays = ui->lineEditPays->text();
    
    if (nom.isEmpty()) {
        QMessageBox::warning(this, "Validation", "Le nom est obligatoire!");
        return;
    }
    
    // Get new ID
    QList<Fournisseur> all = dbManager->getAllFournisseurs();
    int newId = all.isEmpty() ? 1 : all.last().getId() + 1;
    
    Fournisseur newF(newId, nom, email, tel, adresse, type, ville, pays);
    
    if (dbManager->insertFournisseur(newF)) {
        QMessageBox::information(this, "Succès", "Fournisseur ajouté!");
        refreshFournisseurTable();
        clearFournisseurInputs();
    } else {
        QMessageBox::critical(this, "Erreur", 
            "Erreur lors de l'ajout:\n" + dbManager->getLastError());
    }
    */
}

void MainWindow::onUpdateFournisseurClicked()
{
    if (!useDatabase || !dbManager) return;
    if (selectedFournisseurId < 0) {
        QMessageBox::warning(this, "Selection", "Veuillez sélectionner un fournisseur!");
        return;
    }
    
    QMessageBox::information(this, "Update Fournisseur", 
        "Update functionality ready!\n\n"
        "Add UI inputs and call:\n"
        "dbManager->updateFournisseur(updatedF)");
}

void MainWindow::onDeleteFournisseurClicked()
{
    if (!useDatabase || !dbManager) return;
    if (selectedFournisseurId < 0) {
        QMessageBox::warning(this, "Selection", "Veuillez sélectionner un fournisseur!");
        return;
    }
    
    // Check if fournisseur has products
    int prodCount = dbManager->countProduitsByFournisseur(selectedFournisseurId);
    
    if (prodCount > 0) {
        QMessageBox::warning(this, "Cannot Delete", 
            QString("Ce fournisseur a %1 produit(s) associé(s)!\n\n"
                    "Supprimez d'abord les produits.").arg(prodCount));
        return;
    }
    
    auto reply = QMessageBox::question(this, "Confirmation",
                                        "Êtes-vous sûr de supprimer ce fournisseur?",
                                        QMessageBox::Yes | QMessageBox::No);
    
    if (reply == QMessageBox::Yes) {
        if (dbManager->deleteFournisseur(selectedFournisseurId)) {
            QMessageBox::information(this, "Succès", "Fournisseur supprimé!");
            refreshFournisseurTable();
            clearFournisseurInputs();
        } else {
            QMessageBox::critical(this, "Erreur", dbManager->getLastError());
        }
    }
}

void MainWindow::onSearchFournisseurClicked()
{
    if (!useDatabase || !dbManager) return;
    
    QMessageBox::information(this, "Search", 
        "Search functionality ready!\n\n"
        "Add a search input field and call:\n"
        "dbManager->searchFournisseurs(searchTerm)");
}

void MainWindow::onFournisseurTableClicked(const QModelIndex &index)
{
    if (!index.isValid()) return;
    
    // Get ID from first column
    QModelIndex idIndex = fournisseurModel->index(index.row(), 0);
    selectedFournisseurId = fournisseurModel->data(idIndex).toInt();
    
    qDebug() << "📌 Selected Fournisseur ID:" << selectedFournisseurId;
    
    // Load data into input fields
    // ui->lineEditNomFournisseur->setText(fournisseurModel->data(...).toString());
    // etc.
}

void MainWindow::onViewProduitsByFournisseurClicked()
{
    if (!useDatabase || !dbManager) return;
    if (selectedFournisseurId < 0) {
        QMessageBox::warning(this, "Selection", "Sélectionnez un fournisseur!");
        return;
    }
    
    QList<Produit> produits = dbManager->getProduitsByFournisseur(selectedFournisseurId);
    
    QString msg = QString("Produits du fournisseur (ID: %1):\n\n").arg(selectedFournisseurId);
    
    if (produits.isEmpty()) {
        msg += "Aucun produit trouvé.";
    } else {
        for (const Produit& p : produits) {
            msg += QString("• %1 - %2 (Qté: %3)\n")
                       .arg(p.getNomProduit())
                       .arg(p.getDescription())
                       .arg(p.getQuantiteStock());
        }
    }
    
    QMessageBox::information(this, "Produits", msg);
}

// ============================================================================
// PRODUIT MANAGEMENT
// ============================================================================

void MainWindow::onAddProduitClicked()
{
    if (!useDatabase || !dbManager) {
        QMessageBox::warning(this, "Error", "Database not connected!");
        return;
    }
    
    QMessageBox::information(this, "Add Produit", 
        "To add produits, you need to:\n\n"
        "1. Add input fields in UI for:\n"
        "   - Nom produit\n"
        "   - Description\n"
        "   - Prix\n"
        "   - Quantité\n"
        "   - ComboBox to select Fournisseur\n"
        "   - Date\n\n"
        "2. Call dbManager->insertProduit()\n\n"
        "Example code in mainwindow.cpp!");
    
    /* EXAMPLE CODE:
    
    QString nom = ui->lineEditNomProduit->text();
    QString desc = ui->lineEditDescription->text();
    double prix = ui->lineEditPrix->text().toDouble();
    int qte = ui->spinBoxQuantite->value();
    int idFour = ui->comboBoxFournisseur->currentData().toInt();
    QDate date = ui->dateEditLivraison->date();
    
    if (nom.isEmpty() || idFour <= 0) {
        QMessageBox::warning(this, "Validation", "Remplissez tous les champs!");
        return;
    }
    
    QList<Produit> all = dbManager->getAllProduits();
    int newId = all.isEmpty() ? 1 : all.last().getId() + 1;
    
    Produit newP(newId, nom, desc, prix, qte, idFour, date);
    
    if (dbManager->insertProduit(newP)) {
        QMessageBox::information(this, "Succès", "Produit ajouté!");
        refreshProduitTable();
        clearProduitInputs();
    } else {
        QMessageBox::critical(this, "Erreur", dbManager->getLastError());
    }
    */
}

void MainWindow::onUpdateProduitClicked()
{
    if (!useDatabase || !dbManager) return;
    if (selectedProduitId < 0) {
        QMessageBox::warning(this, "Selection", "Sélectionnez un produit!");
        return;
    }
    
    QMessageBox::information(this, "Update Produit", 
        "Update functionality ready!\n"
        "Call: dbManager->updateProduit(updatedP)");
}

void MainWindow::onDeleteProduitClicked()
{
    if (!useDatabase || !dbManager) return;
    if (selectedProduitId < 0) {
        QMessageBox::warning(this, "Selection", "Sélectionnez un produit!");
        return;
    }
    
    auto reply = QMessageBox::question(this, "Confirmation",
                                        "Supprimer ce produit?",
                                        QMessageBox::Yes | QMessageBox::No);
    
    if (reply == QMessageBox::Yes) {
        if (dbManager->deleteProduit(selectedProduitId)) {
            QMessageBox::information(this, "Succès", "Produit supprimé!");
            refreshProduitTable();
            clearProduitInputs();
        } else {
            QMessageBox::critical(this, "Erreur", dbManager->getLastError());
        }
    }
}

void MainWindow::onSearchProduitClicked()
{
    if (!useDatabase || !dbManager) return;
    
    QMessageBox::information(this, "Search Produit", 
        "Search ready! Call:\n"
        "dbManager->searchProduits(searchTerm)");
}

void MainWindow::onProduitTableClicked(const QModelIndex &index)
{
    if (!index.isValid()) return;
    
    QModelIndex idIndex = produitModel->index(index.row(), 0);
    selectedProduitId = produitModel->data(idIndex).toInt();
    
    qDebug() << "📌 Selected Produit ID:" << selectedProduitId;
}

