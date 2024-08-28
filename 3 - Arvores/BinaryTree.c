#include <stdio.h>
#include <stdlib.h>

struct arv {
  int dado;
  struct arv *esq;
  struct arv *dir;
};

typedef struct arv Arv;

Arv *criaArv(int dado, Arv *sae, Arv *sad) {
  Arv *p = (Arv *)malloc(sizeof(Arv));
  p->dado = dado;
  p->esq = sae;
  p->dir = sad;
  return p;
}

Arv *criaArvVazia() { return NULL; }

Arv *inserir(Arv *arv, int dado) {
  if (arv == NULL) {
    arv = criaArv(dado, criaArvVazia(), criaArvVazia());
  } else {
    if (dado <= arv->dado) {
      arv->esq = inserir(arv->esq, dado);
    } else {
      arv->dir = inserir(arv->dir, dado);
    }
  }
  return arv;
}

Arv *encontrarMinimo(Arv *arv) {
  Arv *atual = arv;
  while (atual && atual->esq != NULL) {
    atual = atual->esq;
  }
  return atual;
}

Arv *liberaArv(Arv *arv, int valor) {
  if (arv == NULL) {
    return arv;
  }

  if (valor < arv->dado) {
    arv->esq = liberaArv(arv->esq, valor);
  } else if (valor > arv->dado) {
    arv->dir = liberaArv(arv->dir, valor);
  } else {
    if (arv->esq == NULL) {
      Arv *temp = arv->dir;
      free(arv);
      return temp;
    } else if (arv->dir == NULL) {
      Arv *temp = arv->esq;
      free(arv);
      return temp;
    }

    Arv *temp = encontrarMinimo(arv->dir);
    arv->dado = temp->dado;
    arv->dir = liberaArv(arv->dir, temp->dado);
  }
  return arv;
}

Arv *excluirNo(Arv *arv, int valor) {
  if (arv == NULL) {
    return NULL;
  }

  if (valor < arv->dado) {
    arv->esq = excluirNo(arv->esq, valor);
  } else if (valor > arv->dado) {
    arv->dir = excluirNo(arv->dir, valor);
  } else {
    // Nó encontrado
    if (arv->esq == NULL) {
      Arv *dir = arv->dir;
      free(arv);
      return dir;
    } else if (arv->dir == NULL) {
      Arv *esq = arv->esq;
      free(arv);
      return esq;
    }

    // Nó com dois filhos, encontra o sucessor in-order
    Arv *sucessor = encontrarMinimo(arv->dir);
    arv->dado = sucessor->dado;
    arv->dir = excluirNo(arv->dir, sucessor->dado);
  }
  return arv;
}

int pertenceArv(Arv *a, int valor) {
  if (a == NULL) {
    return 0;
  }
  return a->dado == valor || pertenceArv(a->esq, valor) ||
         pertenceArv(a->dir, valor);
}

void percorrerEmOrdem(Arv *arv) {
  if (arv != NULL) {
    percorrerEmOrdem(arv->esq);
    printf("%d ", arv->dado);
    percorrerEmOrdem(arv->dir);
  }
}

void percorrerPreOrdem(Arv *arv) {
  if (arv != NULL) {
    printf("%d ", arv->dado);
    percorrerPreOrdem(arv->esq);
    percorrerPreOrdem(arv->dir);
  }
}

void percorrerPosOrdem(Arv *arv) {
  if (arv != NULL) {
    percorrerPosOrdem(arv->esq);
    percorrerPosOrdem(arv->dir);
    printf("%d ", arv->dado);
  }
}

void liberaArvore(Arv *arv) {
  if (arv != NULL) {
    liberaArvore(arv->esq);
    liberaArvore(arv->dir);
    free(arv);
  }
}

int main() {
  Arv *a = criaArv(5, criaArv(3, criaArvVazia(), criaArvVazia()),
                   criaArv(10, criaArvVazia(), criaArvVazia()));

  inserir(a, 4);
  inserir(a, 1);
  inserir(a, 7);
  inserir(a, 42);

  printf("Em Ordem: ");
  percorrerEmOrdem(a);
  printf("\n\n");

  excluirNo(a, 10);

  printf("Em Ordem: ");
  percorrerEmOrdem(a);
  printf("\n\n");

  printf("Pre Ordem: ");
  percorrerPreOrdem(a);
  printf("\n\n");

  printf("Pos Ordem: ");
  percorrerPosOrdem(a);
  printf("\n");

  liberaArvore(a); // Libera arv
  return 0;
}
