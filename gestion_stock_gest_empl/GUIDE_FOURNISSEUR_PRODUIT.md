# 📚 GUIDE COMPLET: Gestion Fournisseurs & Produits

**Auteur:** Yassin  
**Date:** 22 Octobre 2025  
**Projet:** Smart Optical Store - Module Fournisseurs & Produits  
**Repository:** https://github.com/Genix090/fornisseuryassin

---

## 🎯 CE QUI A ÉTÉ AJOUTÉ

### **Classes Métier:**
- ✅ **Fournisseur** (`fournisseur.h/cpp`) - Gestion des fournisseurs
- ✅ **Produit** (`produit.h/cpp`) - Gestion des produits
- ✅ **DatabaseManager** (`databasemanager.h/cpp`) - Gestionnaire de base de données

### **Base de Données:**
```
FOURNISSEURS (Parent)
      |
      | 1,N Relation
      ↓
PRODUITS (Enfant avec Foreign Key)
```

**Exemple:**
```
Nestlé (1 fournisseur)
  ├─ Yaourt (produit)
  ├─ Lait (produit)
  └─ Fromage (produit)
```

---

## 📊 STRUCTURE DE LA BASE DE DONNÉES

### **Table FOURNISSEURS:**
```sql
CREATE TABLE FOURNISSEURS (
    ID_FOURNISSEUR INTEGER PRIMARY KEY AUTOINCREMENT,
    NOM VARCHAR(100) NOT NULL,
    EMAIL VARCHAR(100),
    TELEPHONE VARCHAR(20),
    ADRESSE VARCHAR(200),
    TYPE_PRODUITS VARCHAR(100),
    VILLE VARCHAR(50),
    PAYS VARCHAR(50)
);
```

### **Table PRODUITS (avec relation 1,N):**
```sql
CREATE TABLE PRODUITS (
    ID_PRODUIT INTEGER PRIMARY KEY AUTOINCREMENT,
    NOM_PRODUIT VARCHAR(100) NOT NULL,
    DESCRIPTION VARCHAR(200),
    PRIX_UNITAIRE REAL,
    QUANTITE_STOCK INTEGER,
    ID_FOURNISSEUR INTEGER NOT NULL,  -- Clé étrangère
    DATE_LIVRAISON DATE,
    FOREIGN KEY (ID_FOURNISSEUR) 
        REFERENCES FOURNISSEURS(ID_FOURNISSEUR)
);
```

---

## 🚀 COMPILATION ET EXÉCUTION

### **1. Compiler le projet:**
```bash
cd gestion_stock_gest_empl
mkdir build && cd build
cmake ..
cmake --build .
```

### **2. Lancer l'application:**
```bash
./gestion_stock  # Linux/Mac
gestion_stock.exe  # Windows
```

### **3. Au démarrage:**
- La base de données `optical_store.db` est créée automatiquement
- Les tables FOURNISSEURS et PRODUITS sont créées
- Un message de confirmation s'affiche

---

## 💻 UTILISATION DU CODE

### **Ajouter un Fournisseur:**
```cpp
// Exemple dans votre code UI
QString nom = ui->lineEditNom->text();
QString email = ui->lineEditEmail->text();
QString telephone = ui->lineEditTelephone->text();
QString adresse = ui->lineEditAdresse->text();
QString type = ui->lineEditTypeProduits->text();
QString ville = ui->lineEditVille->text();
QString pays = ui->lineEditPays->text();

// Validation
if (nom.isEmpty()) {
    QMessageBox::warning(this, "Erreur", "Le nom est obligatoire!");
    return;
}

// Générer ID
QList<Fournisseur> all = dbManager->getAllFournisseurs();
int newId = all.isEmpty() ? 1 : all.last().getId() + 1;

// Créer et insérer
Fournisseur newF(newId, nom, email, telephone, adresse, type, ville, pays);
if (dbManager->insertFournisseur(newF)) {
    QMessageBox::information(this, "Succès", "Fournisseur ajouté!");
    refreshFournisseurTable();
} else {
    QMessageBox::critical(this, "Erreur", dbManager->getLastError());
}
```

### **Ajouter un Produit (avec relation):**
```cpp
QString nom = ui->lineEditNomProduit->text();
QString desc = ui->lineEditDescription->text();
double prix = ui->lineEditPrix->text().toDouble();
int quantite = ui->spinBoxQuantite->value();
int idFournisseur = ui->comboBoxFournisseur->currentData().toInt();
QDate date = ui->dateEditLivraison->date();

if (nom.isEmpty() || idFournisseur <= 0) {
    QMessageBox::warning(this, "Erreur", "Remplissez tous les champs!");
    return;
}

QList<Produit> all = dbManager->getAllProduits();
int newId = all.isEmpty() ? 1 : all.last().getId() + 1;

Produit newP(newId, nom, desc, prix, quantite, idFournisseur, date);
if (dbManager->insertProduit(newP)) {
    QMessageBox::information(this, "Succès", "Produit ajouté!");
    refreshProduitTable();
}
```

### **Voir les Produits d'un Fournisseur:**
```cpp
// Démonstration de la relation 1,N
QList<Produit> produits = dbManager->getProduitsByFournisseur(idFournisseur);

QString msg = QString("Produits de ce fournisseur:\n\n");
for (const Produit& p : produits) {
    msg += QString("• %1 - %2€ (Qté: %3)\n")
               .arg(p.getNomProduit())
               .arg(p.getPrixUnitaire())
               .arg(p.getQuantiteStock());
}
QMessageBox::information(this, "Produits", msg);
```

### **Supprimer avec Contrainte:**
```cpp
// Vérifier si le fournisseur a des produits
int count = dbManager->countProduitsByFournisseur(idFournisseur);

if (count > 0) {
    QMessageBox::warning(this, "Impossible", 
        QString("Ce fournisseur a %1 produit(s)!\n"
                "Supprimez d'abord les produits.").arg(count));
    return;
}

// OK, on peut supprimer
if (dbManager->deleteFournisseur(idFournisseur)) {
    QMessageBox::information(this, "Succès", "Fournisseur supprimé!");
}
```

---

## 🎓 DÉMONSTRATION POUR L'ENSEIGNANT

### **Scénario Complet:**

#### **1. Lancer l'Application**
→ Message: "✅ Database Ready!" avec détails des tables

#### **2. Ajouter un Fournisseur**
```
Nom:           Nestlé
Email:         contact@nestle.fr
Téléphone:     +33123456789
Adresse:       10 Rue de la Paix
Type Produits: Produits laitiers
Ville:         Paris
Pays:          France
```
→ Cliquer "Ajouter" → Fournisseur ID=1 créé

#### **3. Ajouter des Produits Liés**

**Produit 1:**
```
Nom:           Yaourt Nature
Description:   Yaourt 100g
Prix:          2.50€
Quantité:      100
Fournisseur:   Nestlé (ID=1)  ← Relation!
Date:          22/10/2025
```

**Produit 2:**
```
Nom:           Lait Demi-Écrémé
Description:   Lait 1L
Prix:          1.20€
Quantité:      50
Fournisseur:   Nestlé (ID=1)  ← Relation!
Date:          22/10/2025
```

#### **4. Afficher les Produits du Fournisseur**
→ Sélectionner Nestlé → Cliquer "Voir Produits"
→ **Résultat:** 2 produits affichés (Yaourt, Lait)
→ **Cela démontre la relation 1,N!**

#### **5. Tenter de Supprimer le Fournisseur**
→ Sélectionner Nestlé → Cliquer "Supprimer"
→ **Erreur:** "Ce fournisseur a 2 produit(s) associé(s)!"
→ **Cela démontre la contrainte de clé étrangère!**

#### **6. Supprimer dans le Bon Ordre**
→ Supprimer Yaourt → OK
→ Supprimer Lait → OK
→ Maintenant supprimer Nestlé → OK!

### **Points Forts à Mentionner:**
✅ **Relation 1,N correctement modélisée**  
✅ **Contrainte d'intégrité référentielle fonctionnelle**  
✅ **Architecture professionnelle multi-couches**  
✅ **Support multi-SGBD (SQLite/Oracle/MySQL/PostgreSQL)**  
✅ **Code réutilisable et extensible**  
✅ **CRUD complet avec validation**  

---

## 🔧 SWITCH VERS ORACLE (Optionnel)

Si vous voulez utiliser Oracle au lieu de SQLite:

### **Modifier mainwindow.cpp ligne 105:**

**Actuel (SQLite):**
```cpp
dbManager = new DatabaseManager(DatabaseManager::SQLite);
if (dbManager->connectToDatabase("optical_store.db")) {
```

**Pour Oracle:**
```cpp
dbManager = new DatabaseManager(DatabaseManager::Oracle);
if (dbManager->connectToOracle("localhost", 1521, "XE", 
                                "system", "password")) {
```

**C'est tout!** Le reste du code fonctionne identique.

---

## 📁 FICHIERS DU PROJET

### **Nouveaux Fichiers:**
```
gestion_stock_gest_empl/
├── fournisseur.h           (Classe Fournisseur)
├── fournisseur.cpp
├── produit.h               (Classe Produit avec FK)
├── produit.cpp
├── databasemanager.h       (Gestionnaire BD universel)
├── databasemanager.cpp
└── GUIDE_FOURNISSEUR_PRODUIT.md  (Ce guide)
```

### **Fichiers Modifiés:**
```
gestion_stock_gest_empl/
├── mainwindow.h            (Ajout méthodes CRUD)
├── mainwindow.cpp          (Implémentation complète)
└── CMakeLists.txt          (Ajout SQL + nouveaux fichiers)
```

### **Fichier Créé Automatiquement:**
```
gestion_stock_gest_empl/
└── optical_store.db        (Base de données SQLite)
```

---

## 🔗 LIENS UTILES

**Repository GitHub:**  
https://github.com/Genix090/fornisseuryassin

**Branch avec le code:**  
https://github.com/Genix090/fornisseuryassin/tree/ghaith-travail-integre-stock-employe

**Voir les fichiers en ligne:**  
https://github.com/Genix090/fornisseuryassin/tree/ghaith-travail-integre-stock-employe/gestion_stock_gest_empl

---

## 💡 INTÉGRATION AVEC L'ÉQUIPE

### **Votre Module:**
- Gestion Fournisseurs
- Gestion Produits
- Relation Fournisseur → Produits

### **Module de Ghaith:**
- Gestion Stock
- Gestion Employés

### **Comment Connecter:**

**Option 1:** Stock utilise vos Produits
```cpp
// Dans son module Stock:
QList<Produit> produits = dbManager->getAllProduits();
```

**Option 2:** Employés gèrent vos Fournisseurs
```cpp
// Dans son module Employé:
QList<Fournisseur> fournisseurs = dbManager->getAllFournisseurs();
```

**Base de données commune:** `optical_store.db`

---

## ✅ RÉSUMÉ TECHNIQUE

### **Architecture:**
```
┌─────────────────────┐
│   MainWindow (UI)   │
└─────────┬───────────┘
          │
          ↓
┌─────────────────────┐
│  DatabaseManager    │  (Abstraction)
└─────────┬───────────┘
          │
          ↓
┌─────────────────────┐
│   SQLite/Oracle     │  (SGBD)
└─────────────────────┘
          │
          ↓
┌─────────────────────┐
│  FOURNISSEURS (1)   │
│        ↓            │
│  PRODUITS (N)       │
└─────────────────────┘
```

### **Relation 1,N:**
```
Un fournisseur peut livrer plusieurs produits → (1,N)
Un produit est livré par un seul fournisseur → (1,1)
```

### **Contrainte SQL:**
```sql
FOREIGN KEY (ID_FOURNISSEUR) 
    REFERENCES FOURNISSEURS(ID_FOURNISSEUR)
```

### **Méthodes Disponibles:**

**Fournisseur:**
- `insertFournisseur()`
- `updateFournisseur()`
- `deleteFournisseur()`
- `getAllFournisseurs()`
- `getFournisseurById()`
- `searchFournisseurs()`

**Produit:**
- `insertProduit()`
- `updateProduit()`
- `deleteProduit()`
- `getAllProduits()`
- `getProduitById()`
- `getProduitsByFournisseur()`  ← Relation!
- `searchProduits()`

**Relations:**
- `countProduitsByFournisseur()`
- `fournisseurHasProduits()`

---

## 🎉 FÉLICITATIONS!

Votre module Fournisseurs & Produits est:
- ✅ **Complet** - CRUD + Relations
- ✅ **Professionnel** - Architecture propre
- ✅ **Documenté** - Guide complet
- ✅ **Testé** - Prêt à démontrer
- ✅ **Partagé** - Sur GitHub

**Votre enseignant sera impressionné!** 🌟

---

## 📞 BESOIN D'AIDE?

**Tous les exemples de code sont dans:**
- `mainwindow.cpp` (lignes 237-493)
- Ce guide (sections ci-dessus)

**Base de données:**
- Fichier: `optical_store.db`
- Outil pour visualiser: DB Browser for SQLite

**Questions fréquentes:**

**Q: Comment voir ma base de données?**  
R: Télécharger "DB Browser for SQLite" et ouvrir `optical_store.db`

**Q: Puis-je utiliser Oracle?**  
R: Oui! Changer une ligne dans `mainwindow.cpp` (voir section Switch vers Oracle)

**Q: Comment ajouter des champs UI?**  
R: Ouvrir `mainwindow.ui` dans Qt Designer et ajouter QLineEdit, QPushButton, etc.

**Q: Le code compile-t-il sur Windows?**  
R: Oui! SQLite fonctionne sur Windows, macOS et Linux.

---

**Bon courage pour votre présentation! 🚀**

**- Yassin**

