// Enrico Freitas Modena - CC6M
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct treap {
  int valor, prioridade;
  struct treap *esq, *dir;
} Treap;

Treap *criar(int valor) {
  Treap *novoNo = (Treap *)malloc(sizeof(Treap));
  novoNo->valor = valor;
  novoNo->prioridade = rand() % 100;
  novoNo->esq = novoNo->dir = NULL;
  return novoNo;
}

Treap *rotacionarDir(Treap *y) {
  Treap *x = y->esq, *T2 = x->dir;

  x->dir = y;
  y->esq = T2;

  return x;
}

Treap *rotacionarEsq(Treap *x) {
  Treap *y = x->dir, *T2 = y->esq;

  y->esq = x;
  x->dir = T2;

  return y;
}

Treap *inserir(Treap *raiz, int valor) {
  if (!raiz)
    return criar(valor);

  if (valor <= raiz->valor) {
    raiz->esq = inserir(raiz->esq, valor);

    if (raiz->esq->prioridade > raiz->prioridade)
      raiz = rotacionarDir(raiz);
  } else {
    raiz->dir = inserir(raiz->dir, valor);

    if (raiz->dir->prioridade > raiz->prioridade)
      raiz = rotacionarEsq(raiz);
  }

  return raiz;
}

void *remover(Treap *raiz, int valor) {
  if (!raiz)
    return NULL;
  if (valor < raiz->valor)
    raiz->esq = remover(raiz->esq, valor);
  else if (valor > raiz->valor)
    raiz->dir = remover(raiz->dir, valor);

  else if (raiz->esq == NULL) {
    Treap *temp = raiz->dir;
    raiz = NULL;
    raiz = temp;
  }

  else if (raiz->dir == NULL) {
    Treap *temp = raiz->esq;
    raiz = NULL;
    raiz = temp;
  }

  else if (raiz->esq->prioridade < raiz->dir->prioridade) {
    raiz = rotacionarEsq(raiz);
    raiz->esq = remover(raiz->esq, valor);
  } else {
    raiz = rotacionarDir(raiz);
    raiz->dir = remover(raiz->dir, valor);
  }

  return raiz;
}

void percorreEmOrdem(Treap *raiz) {
  if (raiz) {
    percorreEmOrdem(raiz->esq);
    printf("valor: %d  | prioridade: %d", raiz->valor, raiz->prioridade);
    if (raiz->esq)
      printf("  |  filho Esq: %d", raiz->esq->valor);
    if (raiz->dir)
      printf("  |  filho Dir: %d", raiz->dir->valor);
    printf("\n\n");
    percorreEmOrdem(raiz->dir);
  }
}

int main() {
  // srand(time(NULL));

  Treap *raiz = NULL;
  raiz = inserir(raiz, 50);
  raiz = inserir(raiz, 30);
  raiz = inserir(raiz, 20);
  raiz = inserir(raiz, 40);
  raiz = inserir(raiz, 70);
  raiz = inserir(raiz, 60);
  raiz = inserir(raiz, 80);
  percorreEmOrdem(raiz);
  printf("Remove 20...\n\n");
  remover(raiz, 20);
  percorreEmOrdem(raiz);
  printf("Remove 50...\n\n");
  remover(raiz, 50);
  percorreEmOrdem(raiz);
  return 0;
}
