Ce repository contient le projet du groupe 16 (MATAGNE Miro-Manuel, VAN CALCK Ludéric, WILLAUMEZ Rachel)
Sont inclus :
-Les fichiers sources du programme
-Un makefile pour sa compilation
-La matrice de scores par défaut utilisée par l'algorithme (BLOSUM62.txt)
-Une protéine query (P00533.fasta)
-Les fichiers d'une base de données de protéines au format BLAST (newE.fasta.[pin|phr|psq])

--------------------------------------------------------------------------------------------------------

Pour lancer le programme : 

1) Téléchargez le repository.
2) Compilez le programme à l'aide de la commande "make"
3) Lancez l'exécutable à partir de la commande suivante : 
./projet <nom_de_la_proteine_query.fasta> <base_de_donnée.fasta> [paramètres optionnels]

Plusieurs drapeaux permettent de lancer le programme en modifiant certaines options :
-m autre_matrice.txt : permet de changer la matrice de scores utilisée pour l'algorithme
-gop gap_open_penalty : permet de changer le gap open penalty (par défaut 11)
-gep gap_extension_penalty : permet de changer le gap extension penalty (par défaut 1)

--------------------------------------------------------------------------------------------------------

Remarques :

- Par défaut la matrice de scores utilisée est la blosum62. Elle est encodée dans le fichier BLOSUM62.txt
qui doit se situer dans le même dossier que l'exécutable "projet" pour que le programme fonctionne sans
matrice donnée en paramètre.
- Si vous désirez utiliser une autre matrice de scores, celle-ci doit être encodée dans un fichier texte
dans le même format que BLOSUM62.txt, c'est à dire:
    - Première ligne : symboles (lettres) des acides aminés dans l'ordre utilisé par la matrice, séparés 
    par un ou plusieurs espaces.
    - Lignes suivantes : la matrice (scores séparés par un ou plusieurs espaces).

