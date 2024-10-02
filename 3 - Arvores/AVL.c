// Enrico Freitas Modena - CC6M
#include <stdio.h>
#include <stdlib.h>

struct No {
  int valor;
  struct No *esquerda;
  struct No *direita;
  int altura;
};

// Calcula a altura de um nó
int altura(struct No *N) {
  if (N == NULL)
    return 0;
  return N->altura;
}

// Retorna o maior dos dois valores
int max(int a, int b) { return (a > b) ? a : b; }

// Aloca o nó com um valor e define ponteiros e altura
struct No *novoNo(int valor) {
  struct No *no = (struct No *)malloc(sizeof(struct No));
  no->valor = valor;
  no->esquerda = NULL;
  no->direita = NULL;
  no->altura = 1; // Nó novo inicialmente inserido como folha
  return (no);
}

// Realiza rotação a direita na sub arvore
struct No *rotacaoDireita(struct No *y) {
  struct No *x = y->esquerda;
  struct No *T2 = x->direita;

  x->direita = y;
  y->esquerda = T2;

  // Atualiza as alturas
  y->altura = max(altura(y->esquerda), altura(y->direita)) + 1;
  x->altura = max(altura(x->esquerda), altura(x->direita)) + 1;

  // Retorna a raiz
  return x;
}

// Função para realizar rotação à esquerda na subárvore
struct No *rotacaoEsquerda(struct No *x) {
  struct No *y = x->direita;
  struct No *T2 = y->esquerda;

  // Realiza a rotação
  y->esquerda = x;
  x->direita = T2;

  // Atualiza as alturas
  x->altura = max(altura(x->esquerda), altura(x->direita)) + 1;
  y->altura = max(altura(y->esquerda), altura(y->direita)) + 1;

  // Retorna a nova raiz
  return y;
}

// Retorna o fator de balanceamento do nó n
int obterBalanceamento(struct No *N) {
  if (N == NULL)
    return 0;
  return altura(N->esquerda) - altura(N->direita);
}

// Encontra o nó com o menor valor na sub arvore
struct No *noComValorMinimo(struct No *no) {
  struct No *atual = no;

  // Percorre até encontrar o nó mais a esquerda
  while (atual->esquerda != NULL)
    atual = atual->esquerda;

  return atual;
}

// Insere um valor na sub arvore e balanceia
struct No *inserir(struct No *no, int valor) {
  if (no == NULL)
    return (novoNo(valor));

  if (valor < no->valor)
    no->esquerda = inserir(no->esquerda, valor);
  else if (valor > no->valor)
    no->direita = inserir(no->direita, valor);
  else
    return no; // não insere valores repetidos

  // Atualiza a altura do nó atual
  no->altura = 1 + max(altura(no->esquerda), altura(no->direita));

  // Verifica o balanceamento do nó
  int balanceamento = obterBalanceamento(no);

  // Caso o nó esteja desbalanceado
  // Esquerda-Esquerda
  if (balanceamento > 1 && valor < no->esquerda->valor)
    return rotacaoDireita(no);

  // Direita-Direita
  if (balanceamento < -1 && valor > no->direita->valor)
    return rotacaoEsquerda(no);

  // Esquerda-Direita
  if (balanceamento > 1 && valor > no->esquerda->valor) {
    no->esquerda = rotacaoEsquerda(no->esquerda);
    return rotacaoDireita(no);
  }

  // Direita-Esquerda
  if (balanceamento < -1 && valor < no->direita->valor) {
    no->direita = rotacaoDireita(no->direita);
    return rotacaoEsquerda(no);
  }

  return no;
}

// Deletar um nó da arvore
struct No *deletarNo(struct No *raiz, int valor) {
  if (raiz == NULL)
    return raiz;

  if (valor < raiz->valor)
    raiz->esquerda = deletarNo(raiz->esquerda, valor);
  else if (valor > raiz->valor)
    raiz->direita = deletarNo(raiz->direita, valor);
  else {
    // Nó com um filho ou nenhum
    if ((raiz->esquerda == NULL) || (raiz->direita == NULL)) {
      struct No *temp = raiz->esquerda ? raiz->esquerda : raiz->direita;

      // Nó sem filhos
      if (temp == NULL) {
        temp = raiz;
        raiz = NULL;
      } else
        *raiz = *temp;

      free(temp); // libera no temporario
    } else {
      // Nó com dois filhos: pega o menor nó na sub arvore da direita
      struct No *temp = noComValorMinimo(raiz->direita);

      raiz->valor = temp->valor;

      // Remove o sucessor
      raiz->direita = deletarNo(raiz->direita, temp->valor);
    }
  }

  // Se a arvore tiver um nó, retorna ele
  if (raiz == NULL)
    return raiz;

  // Atualiza a altura do nó atual
  raiz->altura = 1 + max(altura(raiz->esquerda), altura(raiz->direita));

  // Verifica o fator de balanceamento do nó
  int balanceamento = obterBalanceamento(raiz);

  // Se o nó estiver desbalanceado
  // Esquerda-Esquerda
  if (balanceamento > 1 && obterBalanceamento(raiz->esquerda) >= 0)
    return rotacaoDireita(raiz);

  // Esquerda-Direita
  if (balanceamento > 1 && obterBalanceamento(raiz->esquerda) < 0) {
    raiz->esquerda = rotacaoEsquerda(raiz->esquerda);
    return rotacaoDireita(raiz);
  }

  // Direita-Direita
  if (balanceamento < -1 && obterBalanceamento(raiz->direita) <= 0)
    return rotacaoEsquerda(raiz);

  // Direita-Esquerda
  if (balanceamento < -1 && obterBalanceamento(raiz->direita) > 0) {
    raiz->direita = rotacaoDireita(raiz->direita);
    return rotacaoEsquerda(raiz);
  }

  return raiz;
}

// Imprime a arvore em pre ordem
void percorrePreOrdem(struct No *raiz) {
  if (raiz != NULL) {
    printf("%d ", raiz->valor);
    percorrePreOrdem(raiz->esquerda);
    percorrePreOrdem(raiz->direita);
  }
}

int main() {
  struct No *raiz = NULL;

  raiz = inserir(raiz, 10);
  raiz = inserir(raiz, 20);
  raiz = inserir(raiz, 30);
  raiz = inserir(raiz, 40);
  raiz = inserir(raiz, 50);
  raiz = inserir(raiz, 25);

  printf("Pré-ordem da árvore AVL:\n");
  percorrePreOrdem(raiz);

  // Deletando o nó com valor 40
  raiz = deletarNo(raiz, 40);

  printf("\n\nPré-ordem após deletar 40:\n");
  percorrePreOrdem(raiz);

  return 0;
}
