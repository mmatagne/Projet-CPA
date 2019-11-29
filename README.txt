Ce repository contient le projet du groupe 16 (MATAGNE Miro-Manuel, VAN CALCK Ludéric, WILLAUMEZ Rachel)

Un makefile a été créé pour la compilation du programme (lancer la commande /make dans le repository)
L'exécutable créé s'appelle "out" (lancer ./out sans argument pour lancer le programme)

ATTENTION : pour que le programme s'exécute correctement, il faut que les fichiers uniprot_sprot.fasta.[pin|phr|psq] ainsi que le fichier
de la protéine P00533.fasta se situent dans le même répertoire que l'exécutable. (Il faut encore que l'on rajoute le passage de ces fichiers
en paramètres du programme)

La lecture du fichier .pin est faite dans le fichier input.cpp
                      .phr ------------------------- header.cpp
                      .psq ------------------------- bddsequences.cpp
Et la comparaison des chaînes est réalisee dans le fichier main2711.cpp 
