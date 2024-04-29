#ifndef TIPOS_H_
#define TIPOS_H_
#include <iostream>
using namespace std;
template <typename TIPO> struct TElemento { TIPO dado; };

template <typename T, int capacidade> struct Tlista {
  TElemento<T> vetor[capacidade];
  int quantidade;
};

template <typename T, int capacidade>
void inicializar(Tlista<T, capacidade> &lista) {
  lista.quantidade = 0;
}

template <typename T, int capacidade>
bool inserirInicio(Tlista<T, capacidade> &lista, int dado) {
  if (lista.quantidade == capacidade) {
    return false;
  }
  for (int i = lista.capacidade; i > 0; i--) {
    lista.vetor[i] = lista.vetor[i - 1];
  }
  TElemento<T> novaCaixa;
  novaCaixa.dado = dado;
  lista.vetor[0] = novaCaixa;
  lista.quantidade++;
  return true;
}

template <typename T, int capacidade>
bool inserirFim(Tlista<T, capacidade> &lista, T dado) {
  if (lista.quantidade == capacidade) {
    return false;
  }

  TElemento<T> novaCaixa;
  novaCaixa.dado = dado;
  lista.vetor[lista.quantidade] = novaCaixa;
  lista.quantidade++;
  return true;
}

template <typename T, int capacidade>
bool inserirPosicao(Tlista<T, capacidade> &lista, T dado, int posicao) {
  if (lista.quantidade == capacidade) {
    return false;
  } else if (posicao < 0 || posicao > lista.quantidade) {
    return false;
  } else {
    for (int i = lista.quantidade; i > posicao; i--) {
      lista.vetor[i] = lista.vetor[i - 1];
    }
    TElemento<T> novaCaixa;
    novaCaixa.dado = dado;
    lista.vetor[posicao] = novaCaixa;
    lista.quantidade++;
    return true;
  }
}

template <typename T, int capacidade>
T removerFim(Tlista<T, capacidade> &lista) {
  if (lista.quantidade == 0 || lista.quantidade < 0) {
    throw "Lista Vazia";
  }
  T copia = lista.vetor[lista.quantidade - 1].dado;
  lista.quantidade--;
  return copia;
}

template <typename T, int capacidade>
T removerInicio(Tlista<T, capacidade> &lista) {
  if (lista.quantidade == 0 || lista.quantidade < 0) {
    throw "Lista Vazia";
  }
  T copia = lista.vetor[0].dado;
  for (int i = 0; i < lista.quantidade - 1; i++) {
    lista.vetor[i] = lista.vetor[i + 1];
  }
  lista.quantidade--;
  return copia;
}

template <typename T, int capacidade>
T removerPosicao(Tlista<T, capacidade> &lista, int posicao) {
  if (lista.quantidade == 0 || posicao < 0 || posicao >= lista.quantidade) {
    throw "Lista Vazia";
  }
  T copia = lista.vetor[posicao].dado;
  for (int i = posicao; i < lista.quantidade - 1; i++) {
    lista.vetor[i] = lista.vetor[i + 1];
  }
  lista.quantidade--;
  return copia;
}

template <typename T, int capacidade>
T obterItem(Tlista<T, capacidade> &lista, int posicao) {
  if (posicao < 0 || posicao >= lista.quantidade) {
    throw "Posição Inválida";
  }
  return lista.vetor[posicao].dado;
}

template <typename T, int capacidade>
bool contemItem(Tlista<T, capacidade> &lista, T dado) {
  for (int i = 0; i < lista.quantidade; i++) {
    if (lista.vetor[i].dado == dado) {
      return true;
    }
  }
  return false;
}

template <typename T, int capacidade>
int descobrirIndice(Tlista<T, capacidade> &lista, T dado) {
  for (int i = 0; i < lista.quantidade; i++) {
    if (lista.vetor[i].dado == dado) {
      return i;
    }
  }
  return -1;
}

template <typename T, int capacidade>
void imprimirTlista(Tlista<T, capacidade> &lista) {
  for (int i = 0; i < lista.quantidade; i++) {
    cout << lista.vetor[i].dado << endl;
  }
}

#endif // TIPOS_H_