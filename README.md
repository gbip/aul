---
title: "Conception d'un compilateur et implémentation du jeu d'instruction en VHDL"
author: 
	- Julien Ferry
	- Paul Florence
date: 5 Mai 2019
titlepage: true
titlepage-color: "435488"
titlepage-text-color: "FFFFFF"
titlepage-rule-color : "FFFFFF"
logo : "./insa.png"
logo-width : 250
---

# Conception d'un compilateur

## Langage accepté

Notre compilateur accepte des programmes écrits dans un langage C réduit. Ce langage supporte : //TODO : MAJ

* les fonctionalités imposées par le cahier des charges (constantes, entiers, "if", "while"...etc) sauf fonctions et pointeurs
* les expressions conditionnelles (et, ou...)
* les boucles "for"
* les variables globales

## AST

Le programme à compiler, écrit dans notre langage C réduit (décrit précédemment), est tout d'abord transformé en une suite de tokens par un analyseur lexical produit par Lex. Le résultat est ensuite parsé  par l'analyseur syntaxique produit par Yacc. Au cours de son analyse (selon la grammaire que nous avons écrite), cet analyseur va effectuer des actions. En utilisant les fonctions appropriées, il va construire l'arbre syntaxique du programme à compiler. Cette structure arborescente présente deux avantages majeurs : elle nous dispensera, par la suite, d'avoir à utiliser une table des symboles, et elle permettra d'effectuer plus facilement des optimisations. 

![Extrait d'un programme à compiler\label{ASTexFrom}](./pictures/screenshot_ast_bis.png)

![AST correspondant construit (et affiché dans la console) \label{ASTex}](./pictures/screenshot_ast_bis_1.png)

## Représentation intermédiaire

Une fois l'arbre syntaxique produit, nous conservons une représentation arborescente du programme à compiler, mais transformons chaque noeud en instructions assembleur. Des optimisations peuvent alors être effectuées. Une deuxième passe sur cet "arbre de représentation intermédiaire" permet de "mettre à plat" le code assembleur, c'est à dire de transformer notre arbre d'instructions en une liste chainée d'instructions (le programme assembleur résultant de la compilation).

![Arbre de représentation intermédiaire correspondant à l'AST de la figure 2\label{IRTex}](./pictures/screenshot_irt.png)

L'exploitation de cet arbre de représentation intermédiaire ne consiste pas en une simple cancaténation des codes. Il s'agit aussi de générer les instructions de saut et les offset correspondants, pour les boucles et les structures conditionnelles, et d'apporter quelques améliorations au code (entre autres).

![Code assembleur final provenant de la mise à plat de l'IRT de la figure 3\label{IRTex}](./pictures/screenshot_irt_flatten.png)

### Notes sur la génération de code pour les expressions :

Lors de l'évaluation d'une expression, le cas le plus général peut se résumer à la formule suivante : 

Calculer la partie droite, l'empiler ; calculer la partie gauche, l'empiler ; dépiler les deux parties et effectuer l'opération.

C'est ce schéma que nous avons suivi pour notre première implémentation. Cependant, dans des cas simples, cette implémentation s'avère peu performante : elle génère beaucoup de STORE/LOAD consécutifs, et donc des accès mémoire inutiles. Nous avons donc apporté une amélioration qui nous a permis de diminuer la taille du fichier généré pour notre programme test d'environ 30%.
Le schéma que nous utilisons est le suivant :

S'il y a une partie gauche :
Calculer la partie droite, l'empiler ; calculer la partie gauche, le résultat est contenu dans R0 ; dépiler la partie droite seulement (dans R1) et effectuer l'opération.
Sinon :
Calculer la partie droite, le résultat est contenu dans R0.

Ainsi, à chaque noeud d'opération, un seul accès mémoire (au maximum) est généré (et il est ici nécessaire car lors de l'évaluation de la partie gauche le contenu du registre R0 risque d'être modifié).

## Jeu d'instruction
