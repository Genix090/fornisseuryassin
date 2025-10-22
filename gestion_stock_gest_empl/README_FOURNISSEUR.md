# 🎯 Module Fournisseur & Produit

## ✅ Ce qui a été ajouté

### **Nouvelles Classes:**
- `Fournisseur` - Gestion des fournisseurs
- `Produit` - Gestion des produits avec relation 1,N
- `DatabaseManager` - Gestionnaire SQL universel (SQLite/Oracle/MySQL/PostgreSQL)

### **Base de Données:**
```sql
FOURNISSEURS (Parent)
    ↓ (1,N)
PRODUITS (Enfant avec FK)
```

### **Fonctionnalités:**
✅ CRUD complet pour Fournisseurs  
✅ CRUD complet pour Produits  
✅ Relation 1,N: Un fournisseur → Plusieurs produits  
✅ Contrainte de clé étrangère  
✅ Recherche et filtrage  
✅ Multi-database support  

---

## 🚀 Utilisation Rapide

### **1. Compilation:**
```bash
cd gestion_stock_gest_empl
mkdir build && cd build
cmake ..
cmake --build .
```

### **2. Exécution:**
- Lance l'app
- DB créée automatiquement (`optical_store.db`)
- Message de confirmation s'affiche

### **3. Exemple d'ajout:**

**Fournisseur:**
```cpp
Fournisseur f(1, "Nestlé", "contact@nestle.com", "0123456789", 
              "Paris", "Produits laitiers", "Paris", "France");
dbManager->insertFournisseur(f);
```

**Produit (avec relation):**
```cpp
Produit p(1, "Yaourt Nature", "Yaourt 100g", 2.50, 100, 
          1, QDate::currentDate());  // ID_FOURNISSEUR = 1 (Nestlé)
dbManager->insertProduit(p);
```

---

## 📖 Documentation Complète

Voir: **`INTEGRATION_FOURNISSEUR_PRODUIT.md`**

---

## 🎓 Pour la Démonstration

1. Ajouter un fournisseur (ex: Nestlé)
2. Ajouter des produits liés (Yaourt, Lait)
3. Voir les produits du fournisseur
4. Essayer de supprimer le fournisseur → Erreur (a des produits)
5. Supprimer les produits d'abord
6. Supprimer le fournisseur → OK

**Cela démontre la relation 1,N et l'intégrité référentielle!**

---

## 🔄 Switch to Oracle

```cpp
// mainwindow.cpp ligne 105
// Change:
dbManager = new DatabaseManager(DatabaseManager::Oracle);
dbManager->connectToOracle("localhost", 1521, "XE", "user", "pass");
```

---

## 📊 Fichiers Ajoutés

```
✅ fournisseur.h/cpp
✅ produit.h/cpp
✅ databasemanager.h/cpp
✅ mainwindow.h/cpp (modifié)
✅ CMakeLists.txt (modifié)
✅ INTEGRATION_FOURNISSEUR_PRODUIT.md
✅ README_FOURNISSEUR.md
```

---

**État:** 🟢 READY FOR MERGE!

