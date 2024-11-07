// Enrico Freitas Modena - CC6M
#include "stdio.h"
#include <stdbool.h>
#include <stdlib.h>

#define N 3

typedef struct arvB {
  int numChaves, chaves[N - 1];
  struct arvB *filhos[N];
  bool ehFolha;
} ArvB;

ArvB *criarNo(bool ehFolha) {
  ArvB *novoNo = (ArvB *)malloc(sizeof(ArvB));
  novoNo->numChaves = 0;
  novoNo->ehFolha = ehFolha;
  for (int i = 0; i < N; i++) {
    novoNo->filhos[i] = NULL;
  }
  return novoNo;
}

void separarFilhos(ArvB *pai, int index) {
  ArvB *filho = pai->filhos[index];
  ArvB *novoNo = criarNo(filho->ehFolha);
  novoNo->numChaves = N / 2 - 1;

  for (int i = 0; i < N / 2 - 1; i++) {
    novoNo->chaves[i] = filho->chaves[i + N / 2];
  }

  if (!filho->ehFolha) {
    for (int i = 0; i < N / 2; i++) {
      novoNo->filhos[i] = filho->filhos[i + N / 2];
    }
  }

  filho->numChaves = N / 2 - 1;

  for (int i = pai->numChaves; i > index; i--) {
    pai->filhos[i + 1] = pai->filhos[i];
  }

  pai->filhos[index + 1] = novoNo;

  for (int i = pai->numChaves - 1; i >= index; i--) {
    pai->chaves[i + 1] = pai->chaves[i];
  }

  pai->chaves[index] = filho->chaves[N / 2 - 1];
  pai->numChaves++;
}

void inserirNaoCheio(ArvB *no, int chave) {
  int i = no->numChaves - 1;

  if (no->ehFolha) {
    while (i >= 0 && no->chaves[i] > chave) {
      no->chaves[i + 1] = no->chaves[i];
      i--;
    }
    no->chaves[i + 1] = chave;
    no->numChaves++;
  } else {
    while (i >= 0 && no->chaves[i] > chave) {
      i--;
    }
    i++;

    if (no->filhos[i]->numChaves == N - 1) {
      separarFilhos(no, i);

      if (no->chaves[i] < chave) {
        i++;
      }
    }
    inserirNaoCheio(no->filhos[i], chave);
  }
}

void inserir(ArvB **raiz, int chave) {
  ArvB *node = *raiz;

  if (node == NULL) {
    *raiz = criarNo(true);
    (*raiz)->chaves[0] = chave;
    (*raiz)->numChaves = 1;
  } else {
    if (node->numChaves == N - 1) {
      ArvB *novaRaiz = criarNo(false);
      novaRaiz->filhos[0] = node;
      separarFilhos(novaRaiz, 0);
      *raiz = novaRaiz;
    }
    inserirNaoCheio(*raiz, chave);
  }
}

void imprimir(ArvB *raiz) {
  if (raiz != NULL) {
    for (int i = 0; i < raiz->numChaves; i++) {
      imprimir(raiz->filhos[i]);
      printf("%d ", raiz->chaves[i]);
    }
    imprimir(raiz->filhos[raiz->numChaves]);
  }
}

int main() {
  ArvB *raiz = NULL;

  inserir(&raiz, 12);
  inserir(&raiz, 45);
  inserir(&raiz, 7);
  inserir(&raiz, 23);
  inserir(&raiz, 9);
  inserir(&raiz, 34);
  inserir(&raiz, 51);

  printf("Árvore em ordem:\n\n");
  imprimir(raiz);

  return 0;
}
