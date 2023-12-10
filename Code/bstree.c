#include "bstree.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

/*------------------------  STRUCTURES  ---------------------------------*/
typedef enum {
    black, red
} NodeColor;

struct _bstree {
    BinarySearchTree *parent;
    BinarySearchTree *left;
    BinarySearchTree *right;
    int root;
    NodeColor color;
};

typedef struct {
    bool found;
    ptrBinarySearchTree pos;
} Couple;

struct _BSTreeIterator {
    const BinarySearchTree *collection;
    const BinarySearchTree *(*begin)(const BinarySearchTree *);
    const BinarySearchTree *current;
    BinarySearchTree *(*next)(const BinarySearchTree *);
};

/*------------------------  CREATION ARBRE  -------------------------*/

BinarySearchTree *bstree_create() {
    return NULL;
}

BinarySearchTree *bstree_cons(BinarySearchTree *left, BinarySearchTree *right, int root) {
    BinarySearchTree *t = malloc(sizeof(struct _bstree));
    t->parent = NULL;
    t->root = root;
    t->left = left;
    t->right = right;
    t->color = red;
    return t;
}

ptrBinarySearchTree fixredblack_insert(ptrBinarySearchTree x);

void bstree_add(ptrBinarySearchTree *t, int value) {
    BinarySearchTree *curr = NULL, *stop = NULL;
    if (!*t) {
        (*t) = bstree_cons(NULL, NULL, value);
        curr = *t;
        goto fixColor;
    }
    ptrBinarySearchTree *tree = t;
    while (*tree) {
        if (value == (*tree)->root) return;
        if (value > (*tree)->root) {
            if ((*tree)->right) {
                tree = &((*tree)->right);
            } else {
                (*tree)->right = bstree_cons(NULL, NULL, value);
                (*tree)->right->parent = (*tree);
                curr = (*tree)->right;
                goto fixColor;
            }
        } else {
            if ((*tree)->left) {
                tree = &((*tree)->left);
            } else {
                (*tree)->left = bstree_cons(NULL, NULL, value);
                (*tree)->left->parent = (*tree);
                curr = (*tree)->left;
                goto fixColor;
            }
        }
    }
    fixColor:
    stop = fixredblack_insert(curr);
    if (stop->parent == NULL)
        *t = stop;
}

/*-----------------------  ACCES ARBRE  -----------------------------*/

bool bstree_empty(const BinarySearchTree *t) {
    return t == NULL;
}

int bstree_root(const BinarySearchTree *t) {
    assert(!bstree_empty(t));
    return t->root;
}

BinarySearchTree *bstree_left(const BinarySearchTree *t) {
    assert(!bstree_empty(t));
    return t->left;
}

BinarySearchTree *bstree_right(const BinarySearchTree *t) {
    assert(!bstree_empty(t));
    return t->right;
}

BinarySearchTree *bstree_parent(const BinarySearchTree *t) {
    assert(!bstree_empty(t));
    return t->parent;
}

bool isRightSon(const BinarySearchTree *t) {
    assert(t->parent);
    return t == t->parent->right;
}

bool isLeftSon(const BinarySearchTree *t) {
    assert(t->parent);
    return t == t->parent->left;
}

ptrBinarySearchTree grandparent(ptrBinarySearchTree n) {
    return n->parent->parent;
}

ptrBinarySearchTree uncle(ptrBinarySearchTree n) {
    ptrBinarySearchTree pp = grandparent(n);
    if (isLeftSon(n->parent)) return pp->right;
    return pp->left;
}

bool redParentAndUncle(ptrBinarySearchTree x) {
    return (x->parent && x->parent->color == red && grandparent(x) && uncle(x) && uncle(x)->color == red);
}

bool redSiblings(ptrBinarySearchTree x) {
    return x->parent && x->parent->right && x->parent->left && x->parent->right->color == red && x->parent->left->color == red;
}

bool redRoot(ptrBinarySearchTree x) {
    return x->color == red && !x->parent;
}

bool redAndParentToo(ptrBinarySearchTree x) {
    return x->color == red && x->parent->color == red;
}

BinarySearchTree *bstree_successor(const BinarySearchTree *x) {
    assert(!bstree_empty(x));
    BinarySearchTree *y = NULL;
    if (x->right) {
        y = x->right;
        while (y->left) {
            y = y->left;
        }
    } else {
        y = x->parent;
        while (y && (x = y->right)) {
            x = y;
            y = y->parent;
        }
    }
    return y;
}

BinarySearchTree *bstree_predecessor(const BinarySearchTree *x) {
    assert(!bstree_empty(x));
    BinarySearchTree *y;
    if (x->left) {
        y = x->left;
        while (y->right) {
            y = y->right;
        }
    } else {
        y = x->parent;
        while (y && (x = y->left)) {
            x = y;
            y = y->parent;
        }
    }
    return y;
}

Couple bstree_searchv2(const BinarySearchTree *tree, int value) {
    Couple couple;
    couple.found = false;
    couple.pos = NULL;
    if (!tree) return couple;
    BinarySearchTree *t = (BinarySearchTree *) tree;
    while (t) {
        if (t->root == value) {
            couple.pos = t;
            couple.found = true;
            return couple;
        } else if (t->root > value) t = (t->left);
        else if (t->root < value) t = (t->right);
    }
    return couple;
}

bool bstree_search(const BinarySearchTree *tree, int value) {
    return bstree_searchv2(tree, value).found;
}

const BinarySearchTree *goto_min(const BinarySearchTree *e) {
    if (!e) return NULL;
    if (!(e->left)) return e;
    ptrBinarySearchTree t = e->left;
    while (t->left) {
        t = t->left;
    }
    return t;
}

const BinarySearchTree *goto_max(const BinarySearchTree *e) {
    if (!e) return NULL;
    if (!(e->right)) return e;
    ptrBinarySearchTree t = e->right;
    while (t->right) {
        t = t->right;
    }
    return t;
}

/*------------------------  PERMUTATION  ----------------------------*/
void bstree_swap_nodes(ptrBinarySearchTree *tree, ptrBinarySearchTree from, ptrBinarySearchTree to) {
    assert(!bstree_empty(*tree) && !bstree_empty(from) && !bstree_empty(to));
    if (from->parent) {
        if (from->parent->left == from) from->parent->left = to;
        else from->parent->right = to;
    } else *tree = to;
    if (to->parent) {
        if (to->parent->left == to) to->parent->left = from;
        else to->parent->right = from;
    }
    BinarySearchTree *tmp = from->parent;
    from->parent = to->parent;
    to->parent = tmp;
    if (from->left) from->left->parent = to;
    if (to->left) to->left->parent = from;
    tmp = from->left;
    from->left = to->left;
    to->left = tmp;
    if (from->right) from->right->parent = to;
    if (to->right) to->right->parent = from;
    tmp = from->right;
    from->right = to->right;
    to->right = tmp;
}

/*------------------------  SUPPRESSION  ----------------------------*/

void bstree_remove_node(ptrBinarySearchTree *t, ptrBinarySearchTree current) {
    ptrBinarySearchTree subs;
    if (current->left == current->right) subs = NULL;
    else if (!current->left) subs = current->right;
    else if (!current->right) subs = current->left;
    else {
        ptrBinarySearchTree leaf = bstree_successor(current);
        bstree_swap_nodes(t, current, leaf);
        subs = current->right;
    }
    if (subs) subs->parent = current->parent;
    if (!current->parent) *t = subs;
    else if (current->parent->left == current) current->parent->left = subs;
    else current->parent->right = subs;
    free(current);
}

void bstree_remove_nodev2(BinarySearchTree *current, void *userData) {
    bstree_remove_node((ptrBinarySearchTree *) userData, current);
}

void bstree_delete(ptrBinarySearchTree *t) {
    bstree_depth_postfix(*t, (OperateFunctor) bstree_remove_nodev2, *t);
    *t = NULL;
}

void bstree_remove(ptrBinarySearchTree *t, int v) {
    Couple couple = bstree_searchv2(*t, v);
    if (couple.found) {
        bstree_remove_node(t, couple.pos);
    }
}

/*------------------------  VISITEURS  ------------------------------*/

void bstree_depth_prefix(const BinarySearchTree *tree, OperateFunctor f, void *userData) {
    if (bstree_empty(tree)) {
        return;
    }
    f(tree, userData);
    bstree_depth_prefix(tree->left, f, userData);
    bstree_depth_prefix(tree->right, f, userData);
}

void bstree_depth_infix(const BinarySearchTree *tree, OperateFunctor f, void *userData) {
    if (!tree) {
        return;
    }
    bstree_depth_infix(tree->left, f, userData);
    f(tree, userData);
    bstree_depth_infix(tree->right, f, userData);
}

void bstree_depth_postfix(const BinarySearchTree *tree, OperateFunctor f, void *userData) {
    if (bstree_empty(tree)) {
        return;
    }
    bstree_depth_postfix(tree->left, f, userData);
    bstree_depth_postfix(tree->right, f, userData);
    f(tree, userData);
}

void bstree_iterative_depth_infix(const BinarySearchTree *t, OperateFunctor f, void *userData) {
    BinarySearchTree *current = (BinarySearchTree *) t;
    BinarySearchTree *next = bstree_parent(t);
    BinarySearchTree *prev = bstree_parent(t);
    while (!bstree_empty(current)) {
        if (prev == bstree_parent(current)) {
            prev = current;
            next = bstree_left(current);
        }
        if (bstree_empty(next) || prev == bstree_left(current)) {
            f(current, userData);
            prev = current;
            next = bstree_right(current);
        }
        if (bstree_empty(next) || prev == bstree_right(current)) {
            prev = current;
            next = bstree_parent(current);
        }
        current = next;
    }
}

void bstree_iterative_breadth_prefix(const BinarySearchTree *t, OperateFunctor f, void *userData) {
    Queue *queue = createQueue();
    queuePush(queue, t);
    while (!queueEmpty(queue)) {
        if (!queueTop(queue)) queuePop(queue);
        else {
            f(queueTop(queue), userData);
            queuePush(queue, bstree_left(queueTop(queue)));
            queuePush(queue, bstree_right(queueTop(queue)));
            queuePop(queue);
        }
    }
    deleteQueue(&queue);
}

/*------------------------  ITERATEUR  ------------------------------*/

BSTreeIterator *bstree_iterator_create(const BinarySearchTree *collection, IteratorDirection direction) {
    BSTreeIterator *iterator = malloc(sizeof(BSTreeIterator));
    iterator->collection = collection;
    if (direction == forward) {
        iterator->begin = goto_min;
        iterator->next = bstree_successor;
    } else {
        iterator->begin = goto_max;
        iterator->next = bstree_predecessor;
    }
    return iterator;
}

void bstree_iterator_delete(ptrBSTreeIterator *i) {
    free(*i);
    *i = NULL;
}

BSTreeIterator *bstree_iterator_begin(BSTreeIterator *i) {
    i->current = i->begin(i->collection);
    return i;
}

bool bstree_iterator_end(const BSTreeIterator *i) {
    return i->current == NULL;
}

BSTreeIterator *bstree_iterator_next(BSTreeIterator *i) {
    i->current = i->next(i->current);
    return i;
}

const BinarySearchTree *bstree_iterator_value(const BSTreeIterator *i) {
    return i->current;
}

/*------------------------  DOT PRINT  ------------------------------*/
void printNode(const BinarySearchTree *t, void *userData) {
    FILE *file = (FILE *) userData;

    printf("%d ", bstree_root(t));
    char *color = t->color ? "red" : "black";
    fprintf(file,
            "\tn%d [style=filled, fillcolor=%s, fontcolor = white, label=\"{{<parent>}|%d|{<left>|<right>}}\"];\n",
            bstree_root(t), color, bstree_root(t));

    if (bstree_left(t)) {
        fprintf(file, "\tn%d:left:c -> n%d:parent:c [headclip=false, tailclip=false]\n", bstree_root(t),
                bstree_root(bstree_left(t)));
    } else {
        fprintf(file, "\tlnil%d [style=filled, fillcolor=grey, label=\"NIL\"];\n", bstree_root(t));
        fprintf(file, "\tn%d:left:c -> lnil%d:n [headclip=false, tailclip=false]\n", bstree_root(t), bstree_root(t));
    }
    if (bstree_right(t)) {
        fprintf(file, "\tn%d:right:c -> n%d:parent:c [headclip=false, tailclip=false]\n", bstree_root(t),
                bstree_root(bstree_right(t)));
    } else {
        fprintf(file, "\trnil%d [style=filled, fillcolor=grey, label=\"NIL\"];\n", bstree_root(t));
        fprintf(file, "\tn%d:right:c -> rnil%d:n [headclip=false, tailclip=false]\n", bstree_root(t), bstree_root(t));
    }
}

void rbtree_export_dot(const BinarySearchTree *t, FILE *file) {
    fprintf(file, " digraph RedBlackTree {\n\tgraph[ ranksep =0.5];\n\tnode [ shape = record, color = white];\n\n");
    bstree_iterative_depth_infix(t, printNode, file);
    fprintf(file, "\n}\n");
}

/*------------------------  ROTATIONS  ------------------------------*/

void leftrotate(BinarySearchTree *x) {
    BinarySearchTree *y = x->right;
    x->right = y->left;
    if (y->left) y->left->parent = x;
    y->parent = x->parent;
    if (!x->parent) x->parent = y;
    else if (x->parent->left == x) x->parent->left = y;
    else x->parent->right = y;
    y->left = x;
    x->parent = y;
}

void rightrotate(BinarySearchTree *y) {
    BinarySearchTree *x = y->left;
    y->left = x->right;
    if (x->right) x->right->parent = y;
    x->parent = y->parent;
    if (!y->parent) y->parent = x;
    else if (y->parent->left == y) y->parent->left = x;
    else y->parent->right = x;
    x->right = y;
    y->parent = x;
}

void testrotateleft(BinarySearchTree *t) {
    leftrotate(t);
}

void testrotateright(BinarySearchTree *t) {
    rightrotate(t);
}

/*------------------------  EQUILIBRAGE  ----------------------------*/

/**//*----------------------------------------------------------------------------------*//**/
/**/    ptrBinarySearchTree fixredblack_insert_case0(ptrBinarySearchTree x);              /**/
/**/    ptrBinarySearchTree fixredblack_insert_case1(ptrBinarySearchTree x);              /**/
/**/    ptrBinarySearchTree fixredblack_insert_case1bis(ptrBinarySearchTree x);           /**/
/**/    ptrBinarySearchTree fixredblack_insert_case2(ptrBinarySearchTree x);              /**/
/**/    ptrBinarySearchTree fixredblack_insert_case2_left(ptrBinarySearchTree x);         /**/
/**/    ptrBinarySearchTree fixredblack_insert_case2_right(ptrBinarySearchTree x);        /**/
/**//*----------------------------------------------------------------------------------*//**/


ptrBinarySearchTree fixredblack_insert(ptrBinarySearchTree x) {
    if (redParentAndUncle(x) || redSiblings(x) || redRoot(x) || redAndParentToo(x))
        return fixredblack_insert_case0(x);
    return x;
}

ptrBinarySearchTree fixredblack_insert_case0(ptrBinarySearchTree x) {
    if (redRoot(x)) {
        x->color = black;
        return x;
    }
    return fixredblack_insert_case1(x);
}

ptrBinarySearchTree fixredblack_insert_case1(ptrBinarySearchTree x) {
    if (redSiblings(x)) {
        x->parent->left->color = black;
        x->parent->right->color = black;
        if (grandparent(x)) x->parent->color = red;
    }
    return fixredblack_insert_case1bis(x);
}

ptrBinarySearchTree fixredblack_insert_case1bis(ptrBinarySearchTree x) {
    if (redParentAndUncle(x)) {
        x->parent->color = black;
        uncle(x)->color = black;
        return fixredblack_insert(grandparent(x));
    }
    return fixredblack_insert_case2(x);
}

ptrBinarySearchTree fixredblack_insert_case2(ptrBinarySearchTree x) {
    if (grandparent(x)) {
        if (isLeftSon(x->parent)) return fixredblack_insert_case2_left(x);
        return fixredblack_insert_case2_right(x);
    }
    return fixredblack_insert(x->parent);
}

ptrBinarySearchTree fixredblack_insert_case2_left(ptrBinarySearchTree x) {
    if (isLeftSon(x)) {
        rightrotate(grandparent(x));
        x->parent->color = black;
        x->parent->right->color = red;
        if (redSiblings(x)) {
            x->parent->left->color = black;
            x->parent->right->color = black;
            x->parent->color = red;
        }
        return fixredblack_insert(x->parent);
    } else {
        leftrotate(x->parent);
        rightrotate(x->parent);
        x->color = red;
        x->left->color = black;
        x->right->color = black;
        return fixredblack_insert(x);
    }
}

ptrBinarySearchTree fixredblack_insert_case2_right(ptrBinarySearchTree x) {
    if (isRightSon(x)) {
        leftrotate(grandparent(x));
        x->parent->color = black;
        x->parent->left->color = red;
        if (redSiblings(x)) {
            x->parent->left->color = black;
            x->parent->right->color = black;
            x->parent->color = red;
        }
        return fixredblack_insert(x->parent);
    } else {
        rightrotate(x->parent);
        leftrotate(x->parent);
        x->color = red;
        x->left->color = black;
        x->right->color = black;
        return fixredblack_insert(x);
    }
}
