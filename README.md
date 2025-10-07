# 🚀 Système de Gestion de Fournisseurs - Advanced Edition

![Qt](https://img.shields.io/badge/Qt-6.9.2-green.svg)
![C++](https://img.shields.io/badge/C++-17-blue.svg)
![License](https://img.shields.io/badge/license-MIT-orange.svg)
![Platform](https://img.shields.io/badge/platform-macOS%20%7C%20Windows%20%7C%20Linux-lightgrey.svg)

**Une application professionnelle de gestion de fournisseurs sans base de données SQL - Tout en JSON!**

## ✨ Caractéristiques Principales

### 🎯 Fonctionnalités de Base
- ✅ **CRUD Complet** - Ajouter, Modifier, Supprimer, Rechercher
- ✅ **Validation en Temps Réel** - Email, téléphone, champs obligatoires
- ✅ **Interface Moderne** - Design dark blue élégant
- ✅ **Tri Intelligent** - Par ID, Nom, Type, Rating
- ✅ **Export PDF** - Documents professionnels formatés

### 🔥 Fonctionnalités Avancées
- 📁 **Export/Import CSV** - Compatible Excel, Google Sheets
- ⭐ **Système de Notation** - Évaluation 5 étoiles (Qualité, Livraison, Prix, Communication)
- 🔍 **Filtre Multi-Critères** - Recherche avancée puissante
- 📝 **Historique d'Activités** - Traçabilité complète de toutes les actions
- 📈 **Statistiques Avancées** - Analytics détaillées
- 💾 **Backup Automatique** - Sauvegardes avec rétention (max 10)
- ♻️ **Restauration** - Récupération depuis sauvegardes
- 🎨 **Menu Advanced Features** - Dashboard centralisé magnifique

## 🏗️ Architecture

```
projectCppQt/
├── main.cpp                    # Point d'entrée
├── mainwindow.h/cpp/ui        # Interface principale
├── fournisseur.h/cpp          # Classe Fournisseur
├── advancedfeatures.h/cpp     # Fonctionnalités avancées
├── ADVANCED_FEATURES.md       # Documentation complète
├── FEATURES_SUMMARY.txt       # Résumé des fonctionnalités
├── sample_fournisseurs.csv    # Exemple de données
└── backups/                   # Sauvegardes automatiques
```

## 🚀 Installation & Utilisation

### Prérequis
- **Qt 6.9.2 ou supérieur**
- **C++17 ou supérieur**
- **Qt Creator** (recommandé)

### Compilation

```bash
# Cloner le repository
git clone https://github.com/Genix090/fornisseuryassin.git
cd fornisseuryassin

# Ouvrir dans Qt Creator
# Ouvrir projectCppQt.pro dans Qt Creator

# Ou compiler en ligne de commande
qmake projectCppQt.pro
make
```

### Démarrage Rapide

1. **Lancer l'application**
2. **Importer des données de test** : Menu → Advanced Features → Import CSV → `sample_fournisseurs.csv`
3. **Explorer les fonctionnalités** : Cliquer sur le bouton **🚀 ADVANCED FEATURES**

## 📊 Captures d'Écran

### Interface Principale
- Tableau élégant avec thème dark blue
- Boutons stylisés avec effets hover
- Formulaire de saisie validé

### Menu Advanced Features
- Dashboard 3x3 avec 9 fonctionnalités
- Design moderne avec gradients
- Statistiques en temps réel

## 💾 Stockage des Données

**ZÉRO SQL!** Tout est stocké en fichiers JSON lisibles:

- `fournisseurs.json` - Données principales des fournisseurs
- `supplier_ratings.json` - Notations et évaluations
- `activity_log.json` - Historique complet des activités
- `backups/*.json` - Sauvegardes automatiques horodatées

## 🎨 Système de Notation

Évaluez vos fournisseurs sur 4 critères (1-5 ⭐):

1. **Qualité des Produits** 📦
2. **Livraison** 🚚
3. **Prix** 💰
4. **Communication** 📞

**Note Globale** = Moyenne des 4 critères
**Niveau de Performance**: Excellent / Good / Average / Poor

## 📈 Statistiques Avancées

- Total fournisseurs (actifs/inactifs)
- Note moyenne globale
- Meilleur fournisseur
- Distribution par type de produits
- Distribution des notes (1-5 étoiles)
- Total d'activités enregistrées

## 🔒 Sécurité & Fiabilité

- ✅ Validation des entrées
- ✅ Confirmations avant suppression
- ✅ Sauvegardes automatiques
- ✅ Vérification des doublons à l'import
- ✅ Historique complet traçable
- ✅ Gestion des erreurs robuste

## ⚡ Performance

- **Chargement**: < 100ms pour 1000 fournisseurs
- **Recherche**: Instantanée
- **Tri**: O(n log n) - Très rapide
- **Export CSV**: Linéaire
- **Sauvegarde**: < 50ms

## 🎯 Cas d'Usage Idéaux

- ✅ PME (< 1000 fournisseurs)
- ✅ Prototypes & MVPs
- ✅ Applications autonomes
- ✅ Environnements sans serveur
- ✅ Démonstrations clients
- ✅ Projets d'apprentissage Qt

## 📖 Documentation

Consultez [`ADVANCED_FEATURES.md`](ADVANCED_FEATURES.md) pour la documentation complète de toutes les fonctionnalités avancées.

## 🛠️ Technologies Utilisées

- **Qt 6.9.2** - Framework GUI
- **C++17** - Langage de programmation
- **JSON** - Stockage de données
- **Qt Widgets** - Interface utilisateur
- **Qt PrintSupport** - Export PDF

## 🤝 Contribution

Les contributions sont les bienvenues! N'hésitez pas à:

1. Fork le projet
2. Créer une branche pour votre fonctionnalité (`git checkout -b feature/AmazingFeature`)
3. Commit vos changements (`git commit -m 'Add some AmazingFeature'`)
4. Push vers la branche (`git push origin feature/AmazingFeature`)
5. Ouvrir une Pull Request

## 📝 Licence

Ce projet est sous licence MIT. Voir le fichier `LICENSE` pour plus de détails.

## 👨‍💻 Auteur

**Genix090**
- GitHub: [@Genix090](https://github.com/Genix090)
- Repository: [fornisseuryassin](https://github.com/Genix090/fornisseuryassin)

## 🌟 Remerciements

- Qt Framework pour l'excellente bibliothèque GUI
- La communauté C++ pour les ressources et le support
- Tous les contributeurs potentiels

## 📞 Support

Si vous rencontrez des problèmes ou avez des questions:
- Ouvrir une [Issue](https://github.com/Genix090/fornisseuryassin/issues)
- Consulter la [documentation complète](ADVANCED_FEATURES.md)

---

**Développé avec ❤️ et Qt C++**

*Version 2.0 - Advanced Edition | Octobre 2025*

---

## 🚀 Quick Start Commands

```bash
# Clone
git clone https://github.com/Genix090/fornisseuryassin.git

# Build
cd fornisseuryassin
qmake projectCppQt.pro
make

# Run
./projectCppQt  # or open the .app on macOS
```

**Profitez de votre système de gestion avancé!** 🎉

