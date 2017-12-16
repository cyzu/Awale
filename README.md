# Jeu Awalé
 *Master 1 Informatique, Résolution de problèmes*

### Description du jeu
On possède une planche de 2 rangées ayant 5 trous chacune (c'est à dire 10 trous au total).
Au début de la partie, chaque trous possèdes 4 cailloux (40 cailloux au total).

Un joueur humain VS ordinateur.

Maximum 2s par coup pour chaque joueur.

Distribution des cailloux dans l'ordre des aiguilles d'une montre.

● profondeur maximale = 30
● joueur 1 = humain, joueur 0 = ordi
● MIN = joueur 0 (ordi) , MAX joueur 1 (humain)

ordi :      [5][6][7][8][9]     DANS LA STRUCTURE !!!!
humain :    [4][3][2][1][0]

### Règle du jeu
  - Le joueur sélectionne un trou dans sa rangée.
  - Il distribue tous les cailloux présent dans ce trou une à une dans les trous suivants.
  - Si le trou sélectionnée posséde 10 ou plus de cailloux, il saute le trou sélectionnée.
  - Si le trou final possède 2 ou 3 cailloux, le joueur peut récupérer les cailloux. 
  Si les trous précédents possèdent de même 2 ou 3 trous, il récupère les cailloux (récupération à la chaine).
  - Si l'adversaire n'a plus de cailloux, le joueur doit jouer un coup lui donnant au moins 1.
  - Aucun joueur ne peut passer son tour.
  
### Fin du jeu
  - Si un joueur a récupéré plus de 20 cailloux (plus de la moitié), il gagne la partie.
  - Sinon le jeu se termine lorsque le joueur ne peut plus jouer (il ne possède plus de cailloux). Dans ce cas celui qui possède encore des cailloux les récupère, et celui qui possède le plus de cailloux gagne la partie.
  - Aucune capture de graines n'est possible
  

### Implémentation
 Implémenter l'algorithme min-max pour jouer le meilleur coup possible, puis l'heuristique :alpha:-:beta:.
 
### Authors
  - Chloé Bensoussan
  - Andreina Wilhelm
  
### Remerciement
### Installation

##questions : 
✓ fonction évaluation ? déterminer une valeur a la profondeur max
- quand le coup n'est pas valide, pourquoi -100, +100 ?
- pourquoi retourner valeurMAX (40) quand c'est une positionFinale ?
- coupValide(), on vérifie que si il y a des graines ?
  
