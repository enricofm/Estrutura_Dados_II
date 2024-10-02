#include <stdio.h>
#include <stdlib.h>

#define VERMELHO 0
#define PRETO 1

struct No {
  int valor;
  int cor;
  struct No *esquerda, *direita, *pai;
};

typedef struct No No;

// Raiz incial pra arvore
No *raiz = NULL;

// Insere nó na arvore
No *inserir(No *no, No *temp) {
  if (no == NULL)
    return temp;

  // Percorre a arvore recursivamente
  if (temp->valor < no->valor) {
    no->esquerda = inserir(no->esquerda, temp);
    no->esquerda->pai = no;
  } else if (temp->valor > no->valor) {
    no->direita = inserir(no->direita, temp);
    no->direita->pai = no;
  }

  return no;
}

// Executa a rotação a direita
void rotacaoDireita(No *temp) {
  No *esquerda = temp->esquerda;
  temp->esquerda = esquerda->direita;

  if (temp->esquerda)
    temp->esquerda->pai = temp;

  esquerda->pai = temp->pai;

  if (!temp->pai)
    raiz = esquerda;
  else if (temp == temp->pai->esquerda)
    temp->pai->esquerda = esquerda;
  else
    temp->pai->direita = esquerda;

  esquerda->direita = temp;
  temp->pai = esquerda;
}

// Executa a rotação a esquerda
void rotacaoEsquerda(No *temp) {
  No *direita = temp->direita;
  temp->direita = direita->esquerda;

  if (temp->direita)
    temp->direita->pai = temp;

  direita->pai = temp->pai;

  if (!temp->pai)
    raiz = direita;
  else if (temp == temp->pai->esquerda)
    temp->pai->esquerda = direita;
  else
    temp->pai->direita = direita;

  direita->esquerda = temp;
  temp->pai = direita;
}

// Corrige as violações após a inserção na árvore
void corrigir(No *raiz, No *z) {
  No *pai_z = NULL;
  No *avo_z = NULL;

  while ((z != raiz) && (z->cor != PRETO) && (z->pai->cor == VERMELHO)) {
    pai_z = z->pai;
    avo_z = z->pai->pai;

    // O pai de z é o filho esquerdo do avô de z
    if (pai_z == avo_z->esquerda) {
      No *tio_z = avo_z->direita;

      // O tio de z tb é vermelho (corrige as cores)
      if (tio_z != NULL && tio_z->cor == VERMELHO) {
        avo_z->cor = VERMELHO;
        pai_z->cor = PRETO;
        tio_z->cor = PRETO;
        z = avo_z;
      } else {
        // z é o filho direito de seu pai (rotaciona a esquerda)
        if (z == pai_z->direita) {
          rotacaoEsquerda(pai_z);
          z = pai_z;
          pai_z = z->pai;
        }

        // z é o filho esquerdo de seu pai (rotacionar a direita)
        rotacaoDireita(avo_z);
        int t = pai_z->cor;
        pai_z->cor = avo_z->cor;
        avo_z->cor = t;
        z = pai_z;
      }
    }
    // O pai de z é o filho direito do avô de z
    else {
      No *tio_z = avo_z->esquerda;

      // O tio de z tb é vermelho (corrige as cores)
      if (tio_z != NULL && tio_z->cor == VERMELHO) {
        avo_z->cor = VERMELHO;
        pai_z->cor = PRETO;
        tio_z->cor = PRETO;
        z = avo_z;
      } else {
        // z é o filho esquerdo de seu pai (rotaciona a direita)
        if (z == pai_z->esquerda) {
          rotacaoDireita(pai_z);
          z = pai_z;
          pai_z = z->pai;
        }

        // z é o filho direito de seu pai (rotaciona a esquerda)
        rotacaoEsquerda(avo_z);
        int t = pai_z->cor;
        pai_z->cor = avo_z->cor;
        avo_z->cor = t;
        z = pai_z;
      }
    }
  }
  raiz->cor = PRETO;
}

// Função para percorrer a árvore em ordem
void percorrerEmOrdem(No *no) {
  if (no == NULL)
    return;
  percorrerEmOrdem(no->esquerda);
  printf("%d ", no->valor);
  percorrerEmOrdem(no->direita);
}

int main() {
  int n = 7;
  int valores[7] = {7, 6, 5, 4, 3, 2, 1};

  for (int i = 0; i < n; i++) {
    No *temp = (No *)malloc(sizeof(No));
    temp->direita = NULL;
    temp->esquerda = NULL;
    temp->pai = NULL;
    temp->valor = valores[i];
    temp->cor = VERMELHO;

    raiz = inserir(raiz, temp);

    // Corrige a árvore redblack
    corrigir(raiz, temp);
  }

  printf("Percorrendo em ordem:\n");
  percorrerEmOrdem(raiz);

  return 0;
}
