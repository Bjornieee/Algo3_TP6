# Rapport TP6

___
    Je n'ai pas pu faire le dernier exercice en raison d'un manque de temps.
___
## __*Choix d'implémentation*__


__Fonction supplémentaires :__
- Pour des soucis de lisibilité j'ai décidé de rajoutter des fonctions comme par exemple :
  - isRightSon
  - isLeftSon
  - redSiblings
  - redParentAndUncle
  - redRoot
  - redAndParentToo

__Fonction bstree_searchv2 :__
- fonction qui renvoie une struct Couple afin de faire uniquement un seul search et pouvoir obtenir la position de la valeur en plus de savoir si elle a été trouvé (le but étant de réduire la complexité)   
     ```c
    typedef struct { 
        bool found;
        ptrBinarySearchTree pos;
    } Couple;
  ```

__Fonction bstree_remove_nodev2 :__
- Fonction faisant appel à remove_node afin d'être compatible avec le format de OperateFunctor

__Fonction printNode :__
- le type NodeColor ainsi que la fonction printNode sont déclarés dans bstree.c car l'utilisateur n'a en aucun cas besoin de l'utiliser. 
- création d'une chaine de caractère color car une enum renvoie un int et non pas le nom de l'élément.
    ```c
    char *color = t->color ? "red" : "black";
    ```
- texte de couleur blanche afin d'être visible dans les nodes noires.

__Fonction rbtree_export_do :__
- nodes de couleurs blanches ( même raison que pour le texte )

__Fonction rightrotate :__
- Cette fonction est déclarée uniquement dans bstree.c car l'utilisateur n'a en aucun cas besoin de l'utiliser. En l'utilisant il risque uniquement de déséquilibrer l'arbre.

__*Description du comportement sur les jeux de tests fournis*__

- Tous les jeux de test ont été validés avec les 3 fichiers
 

__*Analyse personnelle du travail effectué*__

- Il n'y a aucune fuite de mémoire et à ma connaissance aucune erreur.
- Pour l'équilibrage de l'arbre mon algorithme fonctionne mais n'est pas idéal. On voit que pour testsimple1 il y a 4 rouges alors qu'idéalement on ne devrait en obtenir que 3 rouges comme sur l'exemple suivant :
  [Si le lien n'affiche pas l'arbre correctement veuillez copiez coller le code suivant](https://dreampuf.github.io/GraphvizOnline/#%20digraph%20RedBlackTree%20%7B%0A%09graph%5B%20ranksep%20%3D0.5%5D%3B%0A%09node%20%5B%20shape%20%3D%20record%2C%20color%20%3D%20white%5D%3B%0A%0A%09n1%20%5Bstyle%3Dfilled%2C%20fillcolor%3Dred%2C%20fontcolor%20%3D%20white%2C%20label%3D%22%7B%7B%3Cparent%3E%7D%7C1%7C%7B%3Cleft%3E%7C%3Cright%3E%7D%7D%22%5D%3B%0A%09lnil1%20%5Bstyle%3Dfilled%2C%20fillcolor%3Dgrey%2C%20label%3D%22NIL%22%5D%3B%0A%09n1%3Aleft%3Ac%20-%3E%20lnil1%3An%20%5Bheadclip%3Dfalse%2C%20tailclip%3Dfalse%5D%0A%09rnil1%20%5Bstyle%3Dfilled%2C%20fillcolor%3Dgrey%2C%20label%3D%22NIL%22%5D%3B%0A%09n1%3Aright%3Ac%20-%3E%20rnil1%3An%20%5Bheadclip%3Dfalse%2C%20tailclip%3Dfalse%5D%0A%09n2%20%5Bstyle%3Dfilled%2C%20fillcolor%3Dblack%2C%20fontcolor%20%3D%20white%2C%20label%3D%22%7B%7B%3Cparent%3E%7D%7C2%7C%7B%3Cleft%3E%7C%3Cright%3E%7D%7D%22%5D%3B%0A%09n2%3Aleft%3Ac%20-%3E%20n1%3Aparent%3Ac%20%5Bheadclip%3Dfalse%2C%20tailclip%3Dfalse%5D%0A%09rnil2%20%5Bstyle%3Dfilled%2C%20fillcolor%3Dgrey%2C%20label%3D%22NIL%22%5D%3B%0A%09n2%3Aright%3Ac%20-%3E%20rnil2%3An%20%5Bheadclip%3Dfalse%2C%20tailclip%3Dfalse%5D%0A%09n3%20%5Bstyle%3Dfilled%2C%20fillcolor%3Dblack%2C%20fontcolor%20%3D%20white%2C%20label%3D%22%7B%7B%3Cparent%3E%7D%7C3%7C%7B%3Cleft%3E%7C%3Cright%3E%7D%7D%22%5D%3B%0A%09n3%3Aleft%3Ac%20-%3E%20n2%3Aparent%3Ac%20%5Bheadclip%3Dfalse%2C%20tailclip%3Dfalse%5D%0A%09n3%3Aright%3Ac%20-%3E%20n4%3Aparent%3Ac%20%5Bheadclip%3Dfalse%2C%20tailclip%3Dfalse%5D%0A%09n4%20%5Bstyle%3Dfilled%2C%20fillcolor%3Dblack%2C%20fontcolor%20%3D%20white%2C%20label%3D%22%7B%7B%3Cparent%3E%7D%7C4%7C%7B%3Cleft%3E%7C%3Cright%3E%7D%7D%22%5D%3B%0A%09lnil4%20%5Bstyle%3Dfilled%2C%20fillcolor%3Dgrey%2C%20label%3D%22NIL%22%5D%3B%0A%09n4%3Aleft%3Ac%20-%3E%20lnil4%3An%20%5Bheadclip%3Dfalse%2C%20tailclip%3Dfalse%5D%0A%09rnil4%20%5Bstyle%3Dfilled%2C%20fillcolor%3Dgrey%2C%20label%3D%22NIL%22%5D%3B%0A%09n4%3Aright%3Ac%20-%3E%20rnil4%3An%20%5Bheadclip%3Dfalse%2C%20tailclip%3Dfalse%5D%0A%09n5%20%5Bstyle%3Dfilled%2C%20fillcolor%3Dblack%2C%20fontcolor%20%3D%20white%2C%20label%3D%22%7B%7B%3Cparent%3E%7D%7C5%7C%7B%3Cleft%3E%7C%3Cright%3E%7D%7D%22%5D%3B%0A%09n5%3Aleft%3Ac%20-%3E%20n3%3Aparent%3Ac%20%5Bheadclip%3Dfalse%2C%20tailclip%3Dfalse%5D%0A%09n5%3Aright%3Ac%20-%3E%20n7%3Aparent%3Ac%20%5Bheadclip%3Dfalse%2C%20tailclip%3Dfalse%5D%0A%09n6%20%5Bstyle%3Dfilled%2C%20fillcolor%3Dblack%2C%20fontcolor%20%3D%20white%2C%20label%3D%22%7B%7B%3Cparent%3E%7D%7C6%7C%7B%3Cleft%3E%7C%3Cright%3E%7D%7D%22%5D%3B%0A%09lnil6%20%5Bstyle%3Dfilled%2C%20fillcolor%3Dgrey%2C%20label%3D%22NIL%22%5D%3B%0A%09n6%3Aleft%3Ac%20-%3E%20lnil6%3An%20%5Bheadclip%3Dfalse%2C%20tailclip%3Dfalse%5D%0A%09rnil6%20%5Bstyle%3Dfilled%2C%20fillcolor%3Dgrey%2C%20label%3D%22NIL%22%5D%3B%0A%09n6%3Aright%3Ac%20-%3E%20rnil6%3An%20%5Bheadclip%3Dfalse%2C%20tailclip%3Dfalse%5D%0A%09n7%20%5Bstyle%3Dfilled%2C%20fillcolor%3Dblack%2C%20fontcolor%20%3D%20white%2C%20label%3D%22%7B%7B%3Cparent%3E%7D%7C7%7C%7B%3Cleft%3E%7C%3Cright%3E%7D%7D%22%5D%3B%0A%09n7%3Aleft%3Ac%20-%3E%20n6%3Aparent%3Ac%20%5Bheadclip%3Dfalse%2C%20tailclip%3Dfalse%5D%0A%09n7%3Aright%3Ac%20-%3E%20n8%3Aparent%3Ac%20%5Bheadclip%3Dfalse%2C%20tailclip%3Dfalse%5D%0A%09n8%20%5Bstyle%3Dfilled%2C%20fillcolor%3Dblack%2C%20fontcolor%20%3D%20white%2C%20label%3D%22%7B%7B%3Cparent%3E%7D%7C8%7C%7B%3Cleft%3E%7C%3Cright%3E%7D%7D%22%5D%3B%0A%09lnil8%20%5Bstyle%3Dfilled%2C%20fillcolor%3Dgrey%2C%20label%3D%22NIL%22%5D%3B%0A%09n8%3Aleft%3Ac%20-%3E%20lnil8%3An%20%5Bheadclip%3Dfalse%2C%20tailclip%3Dfalse%5D%0A%09rnil8%20%5Bstyle%3Dfilled%2C%20fillcolor%3Dgrey%2C%20label%3D%22NIL%22%5D%3B%0A%09n8%3Aright%3Ac%20-%3E%20rnil8%3An%20%5Bheadclip%3Dfalse%2C%20tailclip%3Dfalse%5D%0A%09n9%20%5Bstyle%3Dfilled%2C%20fillcolor%3Dblack%2C%20fontcolor%20%3D%20white%2C%20label%3D%22%7B%7B%3Cparent%3E%7D%7C9%7C%7B%3Cleft%3E%7C%3Cright%3E%7D%7D%22%5D%3B%0A%09n9%3Aleft%3Ac%20-%3E%20n5%3Aparent%3Ac%20%5Bheadclip%3Dfalse%2C%20tailclip%3Dfalse%5D%0A%09n9%3Aright%3Ac%20-%3E%20n15%3Aparent%3Ac%20%5Bheadclip%3Dfalse%2C%20tailclip%3Dfalse%5D%0A%09n10%20%5Bstyle%3Dfilled%2C%20fillcolor%3Dblack%2C%20fontcolor%20%3D%20white%2C%20label%3D%22%7B%7B%3Cparent%3E%7D%7C10%7C%7B%3Cleft%3E%7C%3Cright%3E%7D%7D%22%5D%3B%0A%09lnil10%20%5Bstyle%3Dfilled%2C%20fillcolor%3Dgrey%2C%20label%3D%22NIL%22%5D%3B%0A%09n10%3Aleft%3Ac%20-%3E%20lnil10%3An%20%5Bheadclip%3Dfalse%2C%20tailclip%3Dfalse%5D%0A%09rnil10%20%5Bstyle%3Dfilled%2C%20fillcolor%3Dgrey%2C%20label%3D%22NIL%22%5D%3B%0A%09n10%3Aright%3Ac%20-%3E%20rnil10%3An%20%5Bheadclip%3Dfalse%2C%20tailclip%3Dfalse%5D%0A%09n11%20%5Bstyle%3Dfilled%2C%20fillcolor%3Dblack%2C%20fontcolor%20%3D%20white%2C%20label%3D%22%7B%7B%3Cparent%3E%7D%7C11%7C%7B%3Cleft%3E%7C%3Cright%3E%7D%7D%22%5D%3B%0A%09lnil11%20%5Bstyle%3Dfilled%2C%20fillcolor%3Dgrey%2C%20label%3D%22NIL%22%5D%3B%0A%09n11%3Aleft%3Ac%20-%3E%20lnil11%3An%20%5Bheadclip%3Dfalse%2C%20tailclip%3Dfalse%5D%0A%09rnil11%20%5Bstyle%3Dfilled%2C%20fillcolor%3Dgrey%2C%20label%3D%22NIL%22%5D%3B%0A%09n11%3Aright%3Ac%20-%3E%20rnil11%3An%20%5Bheadclip%3Dfalse%2C%20tailclip%3Dfalse%5D%0A%09n12%20%5Bstyle%3Dfilled%2C%20fillcolor%3Dblack%2C%20fontcolor%20%3D%20white%2C%20label%3D%22%7B%7B%3Cparent%3E%7D%7C12%7C%7B%3Cleft%3E%7C%3Cright%3E%7D%7D%22%5D%3B%0A%09n12%3Aleft%3Ac%20-%3E%20n10%3Aparent%3An%20%5Bheadclip%3Dfalse%2C%20tailclip%3Dfalse%5D%0A%09n12%3Aright%3Ac%20-%3E%20n13%3Aparent%3An%20%5Bheadclip%3Dfalse%2C%20tailclip%3Dfalse%5D%0A%09n13%20%5Bstyle%3Dfilled%2C%20fillcolor%3Dred%2C%20fontcolor%20%3D%20white%2C%20label%3D%22%7B%7B%3Cparent%3E%7D%7C13%7C%7B%3Cleft%3E%7C%3Cright%3E%7D%7D%22%5D%3B%0A%09n13%3Aleft%3Ac%20-%3E%20n11%3Aparent%3Ac%20%5Bheadclip%3Dfalse%2C%20tailclip%3Dfalse%5D%0A%09n13%3Aright%3Ac%20-%3E%20n14%3Aparent%3Ac%20%5Bheadclip%3Dfalse%2C%20tailclip%3Dfalse%5D%0A%09n14%20%5Bstyle%3Dfilled%2C%20fillcolor%3Dblack%2C%20fontcolor%20%3D%20white%2C%20label%3D%22%7B%7B%3Cparent%3E%7D%7C14%7C%7B%3Cleft%3E%7C%3Cright%3E%7D%7D%22%5D%3B%0A%09lnil14%20%5Bstyle%3Dfilled%2C%20fillcolor%3Dgrey%2C%20label%3D%22NIL%22%5D%3B%0A%09n14%3Aleft%3Ac%20-%3E%20lnil14%3An%20%5Bheadclip%3Dfalse%2C%20tailclip%3Dfalse%5D%0A%09rnil14%20%5Bstyle%3Dfilled%2C%20fillcolor%3Dgrey%2C%20label%3D%22NIL%22%5D%3B%0A%09n14%3Aright%3Ac%20-%3E%20rnil14%3An%20%5Bheadclip%3Dfalse%2C%20tailclip%3Dfalse%5D%0A%09n15%20%5Bstyle%3Dfilled%2C%20fillcolor%3Dblack%2C%20fontcolor%20%3D%20white%2C%20label%3D%22%7B%7B%3Cparent%3E%7D%7C15%7C%7B%3Cleft%3E%7C%3Cright%3E%7D%7D%22%5D%3B%0A%09n15%3Aleft%3Ac%20-%3E%20n12%3Aparent%3An%20%5Bheadclip%3Dfalse%2C%20tailclip%3Dfalse%5D%0A%09n15%3Aright%3Ac%20-%3E%20n19%3Aparent%3An%20%5Bheadclip%3Dfalse%2C%20tailclip%3Dfalse%5D%0A%09n16%20%5Bstyle%3Dfilled%2C%20fillcolor%3Dblack%2C%20fontcolor%20%3D%20white%2C%20label%3D%22%7B%7B%3Cparent%3E%7D%7C16%7C%7B%3Cleft%3E%7C%3Cright%3E%7D%7D%22%5D%3B%0A%09lnil16%20%5Bstyle%3Dfilled%2C%20fillcolor%3Dgrey%2C%20label%3D%22NIL%22%5D%3B%0A%09n16%3Aleft%3Ac%20-%3E%20lnil16%3An%20%5Bheadclip%3Dfalse%2C%20tailclip%3Dfalse%5D%0A%09rnil16%20%5Bstyle%3Dfilled%2C%20fillcolor%3Dgrey%2C%20label%3D%22NIL%22%5D%3B%0A%09n16%3Aright%3Ac%20-%3E%20rnil16%3An%20%5Bheadclip%3Dfalse%2C%20tailclip%3Dfalse%5D%0A%09n17%20%5Bstyle%3Dfilled%2C%20fillcolor%3Dred%2C%20fontcolor%20%3D%20white%2C%20label%3D%22%7B%7B%3Cparent%3E%7D%7C17%7C%7B%3Cleft%3E%7C%3Cright%3E%7D%7D%22%5D%3B%0A%09n17%3Aleft%3Ac%20-%3E%20n16%3Aparent%3Ac%20%5Bheadclip%3Dfalse%2C%20tailclip%3Dfalse%5D%0A%09n17%3Aright%3Ac%20-%3E%20n18%3Aparent%3Ac%20%5Bheadclip%3Dfalse%2C%20tailclip%3Dfalse%5D%0A%09n18%20%5Bstyle%3Dfilled%2C%20fillcolor%3Dblack%2C%20fontcolor%20%3D%20white%2C%20label%3D%22%7B%7B%3Cparent%3E%7D%7C18%7C%7B%3Cleft%3E%7C%3Cright%3E%7D%7D%22%5D%3B%0A%09lnil18%20%5Bstyle%3Dfilled%2C%20fillcolor%3Dgrey%2C%20label%3D%22NIL%22%5D%3B%0A%09n18%3Aleft%3Ac%20-%3E%20lnil18%3An%20%5Bheadclip%3Dfalse%2C%20tailclip%3Dfalse%5D%0A%09rnil18%20%5Bstyle%3Dfilled%2C%20fillcolor%3Dgrey%2C%20label%3D%22NIL%22%5D%3B%0A%09n18%3Aright%3Ac%20-%3E%20rnil18%3An%20%5Bheadclip%3Dfalse%2C%20tailclip%3Dfalse%5D%0A%09n19%20%5Bstyle%3Dfilled%2C%20fillcolor%3Dblack%2C%20fontcolor%20%3D%20white%2C%20label%3D%22%7B%7B%3Cparent%3E%7D%7C19%7C%7B%3Cleft%3E%7C%3Cright%3E%7D%7D%22%5D%3B%0A%09n19%3Aleft%3Ac%20-%3E%20n17%3Aparent%3Ac%20%5Bheadclip%3Dfalse%2C%20tailclip%3Dfalse%5D%0A%09n19%3Aright%3Ac%20-%3E%20n20%3Aparent%3Ac%20%5Bheadclip%3Dfalse%2C%20tailclip%3Dfalse%5D%0A%09n20%20%5Bstyle%3Dfilled%2C%20fillcolor%3Dblack%2C%20fontcolor%20%3D%20white%2C%20label%3D%22%7B%7B%3Cparent%3E%7D%7C20%7C%7B%3Cleft%3E%7C%3Cright%3E%7D%7D%22%5D%3B%0A%09lnil20%20%5Bstyle%3Dfilled%2C%20fillcolor%3Dgrey%2C%20label%3D%22NIL%22%5D%3B%0A%09n20%3Aleft%3Ac%20-%3E%20lnil20%3An%20%5Bheadclip%3Dfalse%2C%20tailclip%3Dfalse%5D%0A%09rnil20%20%5Bstyle%3Dfilled%2C%20fillcolor%3Dgrey%2C%20label%3D%22NIL%22%5D%3B%0A%09n20%3Aright%3Ac%20-%3E%20rnil20%3An%20%5Bheadclip%3Dfalse%2C%20tailclip%3Dfalse%5D%0A%7D%0A)
 ```dot
   digraph RedBlackTree {
	graph[ ranksep =0.5];
	node [ shape = record, color = white];

	n1 [style=filled, fillcolor=red, fontcolor = white, label="{{<parent>}|1|{<left>|<right>}}"];
	lnil1 [style=filled, fillcolor=grey, label="NIL"];
	n1:left:c -> lnil1:n [headclip=false, tailclip=false]
	rnil1 [style=filled, fillcolor=grey, label="NIL"];
	n1:right:c -> rnil1:n [headclip=false, tailclip=false]
	n2 [style=filled, fillcolor=black, fontcolor = white, label="{{<parent>}|2|{<left>|<right>}}"];
	n2:left:c -> n1:parent:c [headclip=false, tailclip=false]
	rnil2 [style=filled, fillcolor=grey, label="NIL"];
	n2:right:c -> rnil2:n [headclip=false, tailclip=false]
	n3 [style=filled, fillcolor=black, fontcolor = white, label="{{<parent>}|3|{<left>|<right>}}"];
	n3:left:c -> n2:parent:c [headclip=false, tailclip=false]
	n3:right:c -> n4:parent:c [headclip=false, tailclip=false]
	n4 [style=filled, fillcolor=black, fontcolor = white, label="{{<parent>}|4|{<left>|<right>}}"];
	lnil4 [style=filled, fillcolor=grey, label="NIL"];
	n4:left:c -> lnil4:n [headclip=false, tailclip=false]
	rnil4 [style=filled, fillcolor=grey, label="NIL"];
	n4:right:c -> rnil4:n [headclip=false, tailclip=false]
	n5 [style=filled, fillcolor=black, fontcolor = white, label="{{<parent>}|5|{<left>|<right>}}"];
	n5:left:c -> n3:parent:c [headclip=false, tailclip=false]
	n5:right:c -> n7:parent:c [headclip=false, tailclip=false]
	n6 [style=filled, fillcolor=black, fontcolor = white, label="{{<parent>}|6|{<left>|<right>}}"];
	lnil6 [style=filled, fillcolor=grey, label="NIL"];
	n6:left:c -> lnil6:n [headclip=false, tailclip=false]
	rnil6 [style=filled, fillcolor=grey, label="NIL"];
	n6:right:c -> rnil6:n [headclip=false, tailclip=false]
	n7 [style=filled, fillcolor=black, fontcolor = white, label="{{<parent>}|7|{<left>|<right>}}"];
	n7:left:c -> n6:parent:c [headclip=false, tailclip=false]
	n7:right:c -> n8:parent:c [headclip=false, tailclip=false]
	n8 [style=filled, fillcolor=black, fontcolor = white, label="{{<parent>}|8|{<left>|<right>}}"];
	lnil8 [style=filled, fillcolor=grey, label="NIL"];
	n8:left:c -> lnil8:n [headclip=false, tailclip=false]
	rnil8 [style=filled, fillcolor=grey, label="NIL"];
	n8:right:c -> rnil8:n [headclip=false, tailclip=false]
	n9 [style=filled, fillcolor=black, fontcolor = white, label="{{<parent>}|9|{<left>|<right>}}"];
	n9:left:c -> n5:parent:c [headclip=false, tailclip=false]
	n9:right:c -> n15:parent:c [headclip=false, tailclip=false]
	n10 [style=filled, fillcolor=black, fontcolor = white, label="{{<parent>}|10|{<left>|<right>}}"];
	lnil10 [style=filled, fillcolor=grey, label="NIL"];
	n10:left:c -> lnil10:n [headclip=false, tailclip=false]
	rnil10 [style=filled, fillcolor=grey, label="NIL"];
	n10:right:c -> rnil10:n [headclip=false, tailclip=false]
	n11 [style=filled, fillcolor=black, fontcolor = white, label="{{<parent>}|11|{<left>|<right>}}"];
	lnil11 [style=filled, fillcolor=grey, label="NIL"];
	n11:left:c -> lnil11:n [headclip=false, tailclip=false]
	rnil11 [style=filled, fillcolor=grey, label="NIL"];
	n11:right:c -> rnil11:n [headclip=false, tailclip=false]
	n12 [style=filled, fillcolor=black, fontcolor = white, label="{{<parent>}|12|{<left>|<right>}}"];
	n12:left:c -> n10:parent:n [headclip=false, tailclip=false]
	n12:right:c -> n13:parent:n [headclip=false, tailclip=false]
	n13 [style=filled, fillcolor=red, fontcolor = white, label="{{<parent>}|13|{<left>|<right>}}"];
	n13:left:c -> n11:parent:c [headclip=false, tailclip=false]
	n13:right:c -> n14:parent:c [headclip=false, tailclip=false]
	n14 [style=filled, fillcolor=black, fontcolor = white, label="{{<parent>}|14|{<left>|<right>}}"];
	lnil14 [style=filled, fillcolor=grey, label="NIL"];
	n14:left:c -> lnil14:n [headclip=false, tailclip=false]
	rnil14 [style=filled, fillcolor=grey, label="NIL"];
	n14:right:c -> rnil14:n [headclip=false, tailclip=false]
	n15 [style=filled, fillcolor=black, fontcolor = white, label="{{<parent>}|15|{<left>|<right>}}"];
	n15:left:c -> n12:parent:n [headclip=false, tailclip=false]
	n15:right:c -> n19:parent:n [headclip=false, tailclip=false]
	n16 [style=filled, fillcolor=black, fontcolor = white, label="{{<parent>}|16|{<left>|<right>}}"];
	lnil16 [style=filled, fillcolor=grey, label="NIL"];
	n16:left:c -> lnil16:n [headclip=false, tailclip=false]
	rnil16 [style=filled, fillcolor=grey, label="NIL"];
	n16:right:c -> rnil16:n [headclip=false, tailclip=false]
	n17 [style=filled, fillcolor=red, fontcolor = white, label="{{<parent>}|17|{<left>|<right>}}"];
	n17:left:c -> n16:parent:c [headclip=false, tailclip=false]
	n17:right:c -> n18:parent:c [headclip=false, tailclip=false]
	n18 [style=filled, fillcolor=black, fontcolor = white, label="{{<parent>}|18|{<left>|<right>}}"];
	lnil18 [style=filled, fillcolor=grey, label="NIL"];
	n18:left:c -> lnil18:n [headclip=false, tailclip=false]
	rnil18 [style=filled, fillcolor=grey, label="NIL"];
	n18:right:c -> rnil18:n [headclip=false, tailclip=false]
	n19 [style=filled, fillcolor=black, fontcolor = white, label="{{<parent>}|19|{<left>|<right>}}"];
	n19:left:c -> n17:parent:c [headclip=false, tailclip=false]
	n19:right:c -> n20:parent:c [headclip=false, tailclip=false]
	n20 [style=filled, fillcolor=black, fontcolor = white, label="{{<parent>}|20|{<left>|<right>}}"];
	lnil20 [style=filled, fillcolor=grey, label="NIL"];
	n20:left:c -> lnil20:n [headclip=false, tailclip=false]
	rnil20 [style=filled, fillcolor=grey, label="NIL"];
	n20:right:c -> rnil20:n [headclip=false, tailclip=false]
}
```