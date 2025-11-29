# Compte-rendu – Séance 1 : Méthodes de descente en C++

## 1. Démarche et objectifs du projet

Lors de cette première séance, notre groupe a travaillé sur la mise en œuvre de méthodes de descente pour minimiser différentes fonctions en C++.
L’objectif principal était de :

- Implémenter une **méthode de descente du gradient** avec un **pas fixe** (`alpha = 0.1`)
- Tester la méthode sur trois fonctions :
  - `q1(x1,x2) = x1² + 2*x2²`
  - `q2(x1,x2,x3) = x1² + 2*x2² + 3*x3²`
  - `r(x1,x2) = (1-x1)² + 100*(x2-x1²)²` (fonction de Rosenbrock)
- Vérifier la convergence des méthodes et analyser les résultats

Nous avons commencé par définir des **classes C++** pour structurer le projet : `Fonction` pour représenter une fonction et son nom, 'Fonctions' pour implémenter les fonctions précises, `MethodeOptimisation` pour la logique de descente, et `MethodeDescente` pour la spécialisation avec pas fixe.

---

## 2. Organisation du code et du repository

Pour faciliter la collaboration, nous avons structuré notre projet comme suit :

```

/scripts
  /build
    /src
      Fonction.o
      Fonctions.o
      MethodeDeDescente.o
      MethodeOptimisation.o
    main.o
  
  /includes
  Fonction.hpp
  Fonctions.hpp
  MethodeOptimisation.hpp

  /src
  Fonction.cpp
  Fonctions.cpp
  MethodeOptimisation.cpp
  MethodeDeDescente.cpp

  main.cpp
  Makefile

```

- Chaque membre du groupe s’est vu **attribuer une classe ou un module** à implémenter
- Nous avons harmonisé les **noms de variables, types et signatures** de fonctions pour assurer la compatibilité
- Le projet est versionné sur **GitHub**, permettant un suivi clair des modifications et des contributions de chacun

---

## 3. Résultats

Nous avons testé notre méthode sur les trois fonctions :

### 3.1 Fonction q1(x1,x2) = x1^2 + 2*x2^2

```

--- Descente de Gradient (Pas Fixe) ---
Point initial :  (3.00, 5.00)
Fonction : x1^2 + 2*x2^2
Méthode : Descente Gradient
Max-iters : 100

Iter.           Obj.         ||Grad||         Point
0              59.00000      2.09e+01      (3.00, 5.00)
10              0.10559      6.55e-01      (0.32, 0.03)
20              0.00120      6.92e-02      (0.03, 0.00)
...
Solution :
Statut : CONVERGENCE (Tolérance atteinte)
Solution : (0.00, 0.00)
Valeur : 0.00

```

### 3.2 Fonction q2(x1,x2,x3) = x1^2 + 2*x2^2 + 3*x3^2

```

--- Descente de Gradient (Pas Fixe) ---
Point initial :  (3.00, 5.00, 2.00)
Fonction : x1^2 + 2*x2^2 + 3*x3^2
Méthode : Descente Gradient
Max-iters : 100

Iter.           Obj.         ||Grad||         Point
0              71.00000      2.41e+01      (3.00, 5.00, 2.00)
10              0.10559      6.55e-01      (0.32, 0.03, 0.00)
20              0.00120      6.92e-02      (0.03, 0.00, 0.00)
...
Solution :
Statut : CONVERGENCE (Tolérance atteinte)
Solution : (0.00, 0.00, 0.00)
Valeur : 0.00

```

### 3.3 Fonction r(x1,x2) = (1-x1)^2 + 100*(x2-x1²)^2 (Rosenbrock)

```

--- Descente de Gradient (Pas Fixe) ---
Point initial :  (0.00, 0.00)
Fonction : (1-x1)^2 + 100*(x2-x1^2)
Méthode : Descente Gradient
Max-iters : 100

Iter.           Obj.         ||Grad||         Point
0               1.00000      2.00e+00      (0.00, 0.00)
10              0.96076      1.96e+00      (0.02, 0.00)
20              0.92318      1.92e+00      (0.04, 0.00)
...
Solution :
Statut : ECHEC (Max itérations atteintes)
Solution : (0.17, 0.03)
Valeur : 0.68

```

---

## 4. Analyse et conclusion

- Pour des fonctions **quadratiques simples** (`q1` et `q2`), la descente du gradient avec pas fixe fonctionne très bien et converge rapidement vers le minimum global.
- Pour la **fonction de Rosenbrock**, plus complexe et non convexe, la méthode n’a pas réussi à converger dans le nombre d’itérations limité. Cela met en évidence la **limitation du pas fixe** et la nécessité d’implémenter éventuellement :
  - des **stratégies de pas adaptatif**
  - ou des **méthodes plus robustes**

---

## 5. Organisation du groupe

- Répartition des tâches :
  - Classe `Fonction` et `Fonctions.hpp/.cpp` : Jean-Loup
  - Classe `MethodeOptimisation` : Adrien
  - Classe `MethodeDeDescente` : Karim
  - `main.cpp` et tests : Tout le monde
- Harmonisation des noms et conventions C++
- Suivi sur GitHub avec commits réguliers et revue de code

