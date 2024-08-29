// Aluno: Enrico Freitas Modena - CC6M
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

Arv *encontrarMenor(Arv *arv) {
  if (arv->esq != NULL) {
    return encontrarMenor(arv->esq);
  } else {
    Arv *aux = arv;
    if (arv->dir != NULL)
      arv = arv->dir;
    else
      arv = NULL;
    return aux;
  }
}

Arv *liberarNo(Arv *arv, int dado) {
  if (arv == NULL) {
    return NULL;
  }

  if (dado < arv->dado) {
    arv->esq = liberarNo(arv->esq, dado);
  } else if (dado > arv->dado) {
    arv->dir = liberarNo(arv->dir, dado);
  } else { // Nó encontrado
    // Caso o nó seja folha
    if (arv->esq == NULL && arv->dir == NULL) {
      free(arv);
      return NULL;
    }
    // Caso o nó tenha apenas um filho à direita
    else if (arv->esq == NULL) {
      Arv *temp = arv->dir;
      free(arv);
      return temp;
    }
    // Caso o nó tenha apenas um filho à esquerda
    else if (arv->dir == NULL) {
      Arv *temp = arv->esq;
      free(arv);
      return temp;
    }
    // Caso o nó tenha dois filhos
    else {
      Arv *temp = encontrarMenor(arv->dir); // Pega o menor valor da sad
      arv->dado = temp->dado; // Substitui o valor do nó atual pelo menor valor
                              // da subárvore direita
      arv->dir = liberarNo(
          arv->dir, temp->dado); // Remove o nó menor na subárvore direita
    }
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

  printf("Pre Ordem: ");
  percorrerPreOrdem(a);
  printf("\n\n");

  printf("Pos Ordem: ");
  percorrerPosOrdem(a);
  printf("\n\n");

  printf("Remove 10...");
  liberarNo(a, 10);
  printf("\n\n");

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
