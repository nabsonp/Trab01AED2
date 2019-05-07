#include "avl.h"
#include <stdio.h>
#include <stdlib.h>

noAVL* criarAVL() {
  return NULL;
}

noAVL* buscaAVL(noAVL *r, int v) {
  if (r != NULL) {
    if (v < r->d) return buscaAVL(r->esq,v);
    else if (v > r->d) return buscaAVL(r->dir,v);
    else return r;
  } else return NULL;
}

noAVL* inserirAVL(noAVL *r, int d){
    if (r != NULL) {
      r->altura++;
      if (d < r->d) r->esq = inserirAVL(r->esq,d);
      else r->dir = inserirAVL(r->dir,d);
    } else {
        r = (noAVL *) malloc(sizeof(noAVL));
        r->d = d;
        r->esq = NULL;
        r->dir = NULL;
        r->altura = 1;
    }
    return r;
}

noAVL* inserirEmAVL(noAVL *r, int d){
  r = inserirAVL(r, d);
  return balanceianoAVL(r);
}

noAVL* dropAVL(noAVL *r) {
  if (r != NULL) {
    r->esq = dropAVL(r->esq);
    r->dir = dropAVL(r->dir);
    free(r);
  }
  return NULL;
}

int alturaAVL(noAVL *r) {
  if (r == NULL) return 0;
  return r->altura;
}

int  fb(noAVL *n) {
    return n == NULL ? 0 : alturaAVL(n->dir) - alturaAVL(n->esq);
}

noAVL* rotacaoSimplesDir(noAVL* n) {
  noAVL *y = n->dir;
  noAVL *T2 = y->esq;
  y->esq = n;
  n->dir = T2;
  n->altura = (alturaAVL(n->esq) > alturaAVL(n->dir) ? alturaAVL(n->esq) : alturaAVL(n->esq)) + 1;
  y->altura = (alturaAVL(y->esq) > alturaAVL(y->dir) ? alturaAVL(y->esq) : alturaAVL(y->esq)) + 1;
  return y;
}

noAVL* rotacaoSimplesEsq(noAVL *y) {
  noAVL *x = y->esq;
  noAVL *T2 = x->dir;
  x->dir = y;
  y->esq = T2;
  x->altura = (alturaAVL(x->esq) > alturaAVL(x->dir) ? alturaAVL(x->esq) : alturaAVL(x->esq)) + 1;
  y->altura = (alturaAVL(y->esq) > alturaAVL(y->dir) ? alturaAVL(y->esq) : alturaAVL(y->esq)) + 1;
  return x;
}

noAVL* rotacaoDuplaDir( noAVL* n ) {
	n->dir = rotacaoSimplesEsq(n->dir);
	return rotacaoSimplesDir(n);

}

noAVL* rotacaoDuplaEsq( noAVL *n ) {
	n->esq = rotacaoSimplesDir(n->esq);
  return rotacaoSimplesEsq(n);
}

noAVL* balanceianoAVL( noAVL *n ) {
  noAVL *newroot = NULL;
  if (n) {
  	if( n->esq ) n->esq  = balanceianoAVL(n->esq);
  	if( n->dir ) n->dir = balanceianoAVL(n->dir);
    n->altura = 1 + (alturaAVL(n->esq) > alturaAVL(n->dir) ? alturaAVL(n->esq) : alturaAVL(n->dir));
    int f = fb(n);
      //printf("%d\n", f);
  	if( f <= -2 ) {
  		if( fb(n->esq) <= -1 ) {newroot = rotacaoSimplesEsq(n);}
  		else newroot = rotacaoDuplaEsq(n);
  	} else if( f >= 2 ) {
  		if( fb(n->dir) >= 1 ) newroot = rotacaoSimplesDir(n);
  		else {
          newroot = rotacaoDuplaDir(n);}
  	} else {
  		newroot = n;
  	}
  }
	return newroot;
}

noAVL* converterVetorAVL(noAVL* r, int tam, int vet[]) {
  r = inserirEmAVL(r,vet[0]);
  for (int i=1; i < tam; i++) {
    r = inserirEmAVL(r,vet[i]);
    printf("%d\n", i);
  }
  return r;
}
