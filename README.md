# Jeu Awalé
###### Master 1 Informatique 2017
###### Université Nice Sophia-Antipolis

### Description du jeu
Ce jeu originaire d'afrique, se joue par toutes les personnes, pour tous ages, quotidiennement.

On possède une planche de ayant 2 rangées de 6 trous, c'est à dire 12 trous au total.
Il est initialisé avec 4 cailloux dans tous les trous.

Il se joue par 2 personnes, choisissant à tour de rôle une case, puis distribue les cailloux vers les autres trous.

### Règle du jeu
  - Le joueur sélectionne un trou dans sa rangée.
  - Il distribue tous les cailloux présent dans ce trou une à une dans les trous suivants.
  - Si le trou sélectionné posséde 12 ou plus de cailloux, il saute le trou sélectionné.
  - Si le trou final possède 2 ou 3 cailloux, le joueur peut récupérer les cailloux. 
  Si les trous précédents possèdent de même 2 ou 3 cailloux, il récupère les cailloux (récupération à la chaine).
  - Si l'adversaire n'a plus de cailloux, le joueur doit jouer un coup lui en donnant au moins 1.
  - Aucun joueur ne peut passer son tour.
  
### Fin du jeu
  - Si un joueur a récupéré plus de la moitié des cailloux, il gagne la partie (majorité absolue).
  - Sinon le jeu se termine lorsque le joueur ne peut plus jouer (il ne possède plus de cailloux).
  - Aucune capture de graines n'est possible
  

### Implémentation
Ce projet consiste a implémenter ce jeu en intégrant de l'intelligence artificiel. Il ne nous été pas demandé d'implémenter le jeu tel décrit ci-dessus.

###### Les règles requises :
   - humain VS ordinateur (IA)
   - planche de 2 * 10 cases (au total 20 cases, 80 cailloux)
   - maximum 2s par coup
   - distribution des cailloux dans l'ordre des aiguilles d'une montre
   - la règle permettant de nourrir l'adversaire n'est pas obligatoire
   - implémenter l'algorithme min-max pour trouver le meilleur coup possible
   - implémenter l'heuristique :alpha:-:beta:

###### Structure dans le code
   - profondeur maximale = 8
   - joueur 1 = humain = min
   - joueur 0 = ordi = max
   
          ordi :      [ 0][ 1][ 2][ 3][ 4][ 5][ 6][ 7][ 8][ 9]      
          humain :    [19][18][17][16][15][14][13][12][11][10]
 
### Authors
  - Chloé Bensoussan
  - Andreina Wilhelm
  
### Installation
Télécharger le projet puis :
  - lancer depuis xcode
  - lancer depuis le terminal avec 
                              
        make all
        ./awale 
  - on pourra par la suite supprimer les .o et l'exec avec :
  
        make clean

### Commentaires et remerciements
Nous avons réaliser ce projet en moins d'une semaine. Ayant un gros manque de temps, nous n'avons pas pu implémenter une bonne fonction d'évaluation déterminant les meilleurs coup à jouer pour gagner la partie. C'est pourquoi l'ordinateur est d'un niveau plutôt faible. La profondeur de recherche dans l'arbre reste de même assez faible.


Cependant, pendant ce court lapse de temps, nous avons pu débuté dans l'optimisation d'un programme. Une fois l'implémentation du code plutôt correct, nous nous sommes concentrées sur l'optimisation du temps de l'exécution du programme. En se servant des cours suivis et des recherches, nous avons comparé des bouts de code, nous cherchions à supprimer des boucles, des variables, et enfin nous réfléchissions à un nouvel algorithme faisant les mêmes instructions.
Par cette manière nous avons ajouter les mots-clés ‘const‘ et ‘inline‘ dans notre code mais nous avons remarqué que le compilateur est aujourd'hui très puissant, sachant bien optimiser sans avoir de l'aide du programmeur.



Amusez-vous bien ! Merci beaucoup :star:
