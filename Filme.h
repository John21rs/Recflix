#ifndef LISTA_FILMES
#define LISTA_FILMES
#include "Tlista.h"
#include "Usuario.h"
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

struct Filme {
  string ID;
  string Title;
  string Year;
  string Released;
  string Runtime;
  string Genre[3];
  Tlista<string, 50> IndividualGenres;
  string Director;
  string Writer;
  string Actors;
  string Plot;
  string Country;
  string Awards;
  string Poster;
  string Rating;
  string IMDB_Votes;
  string IMDB_ID;
  string DVD;
  string Box_Office;
};

struct Controle_filme {
  Filme filmes[500];
  int numFilmes = 500;
};

void InseritListaAssistidos(Controle_filme &filmes, Controle &controle,
                            int id_usuario) {
  if (controle.usuarios[id_usuario].assistidos.quantidade >= 50) {
    cout << "Lista Cheia";
    return;
  }
  srand(time(nullptr));
  while (controle.usuarios[id_usuario].assistidos.quantidade < 50) {
    int id_filme = rand() % filmes.numFilmes;
    bool jaAssistido = false;
    for (int j = 0; j < controle.usuarios[id_usuario].assistidos.quantidade;
         j++) {
      if (filmes.filmes[id_filme].Title ==
          controle.usuarios[id_usuario].assistidos.vetor[j].dado) {
        jaAssistido = true;
        break;
      }
    }
    if (!jaAssistido) {
      inserirFim(controle.usuarios[id_usuario].assistidos,
                 filmes.filmes[id_filme].Title);
    }
  }
}

// Para Inserir os filmes na lista de Assistidos conforme o case 3
void InseritListaAssistidosManual(Controle_filme &filmes, Controle &controle,
                                  int id_usuario, int pos_filme) {
  if (controle.usuarios[id_usuario].assistidos.quantidade >= 50) {
    throw "Lista Cheia";
  }
  for (int j = 0; j < controle.usuarios[id_usuario].assistidos.quantidade;
       j++) {
    if (filmes.filmes[pos_filme].Title ==
        controle.usuarios[id_usuario].assistidos.vetor[j].dado) {
      cout << "Filme já foi inserido antes" << endl;
      return;
    }
  }
  inserirFim(controle.usuarios[id_usuario].assistidos,
             filmes.filmes[pos_filme].Title);
}

// Para Inserir os filmes na lista de Assistidos conforme o case 3
void InserirListaSalvos(Controle_filme &filmes, Controle &controle,
                        int id_usuario) {
  if (controle.usuarios[id_usuario].salvos.quantidade >= 20) {
    throw "Lista Cheia";
  }
  srand(time(nullptr));
  while (controle.usuarios[id_usuario].salvos.quantidade < 20) {
    int id_filme = rand() % filmes.numFilmes;
    bool jaSalvo = false;
    for (int j = 0; j < controle.usuarios[id_usuario].salvos.quantidade; j++) {
      if (filmes.filmes[id_filme].Title ==
          controle.usuarios[id_usuario].salvos.vetor[j].dado) {
        jaSalvo = true;
        break;
      }
    }
    if (!jaSalvo) {
      inserirFim(controle.usuarios[id_usuario].salvos,
                 filmes.filmes[id_filme].Title);
    }
  }
}

void InserirListaSalvosManualmente(Controle_filme &filmes, Controle &controle,
                                   int id_usuario, int pos_filme) {
  if (controle.usuarios[id_usuario].salvos.quantidade >= 20) {
    throw "Lista Cheia";
  }
  for (int j = 0; j < controle.usuarios[id_usuario].salvos.quantidade; j++) {
    if (filmes.filmes[pos_filme].Title ==
        controle.usuarios[id_usuario].salvos.vetor[j].dado) {
      cout << "Filme já foi inserido antes" << endl;
      return;
    }
  }
  inserirFim(controle.usuarios[id_usuario].salvos,
             filmes.filmes[pos_filme].Title);
}

void RemoverListaSalvosManualmente(Controle_filme &filmes, Controle &controle,
                                   int id_usuario, int pos_filme) {
  if (controle.usuarios[id_usuario].salvos.quantidade == 0) {
    throw "Lista Vazia";
  } else {
    removerPosicao(controle.usuarios[id_usuario].salvos, pos_filme);
  }
}

void InserirListaRecomendado(Controle_filme &filmes, Controle &controle,
                             int id_usuario) {
  for (int j = 0; j < 10;) {
    int id_filme = rand() % filmes.numFilmes;
    bool jaRecomendado = false;

    for (int k = 0; k < controle.usuarios[id_usuario].recomendados.quantidade;
         k++) {
      if (filmes.filmes[id_filme].Title ==
          controle.usuarios[id_usuario].recomendados.vetor[k].dado) {
        jaRecomendado = true;
        break;
      }
    }

    if (!jaRecomendado) {
      for (int t = 0; t < 3 && j < 10; t++) {
        for (int i = 0; i < 3; i++) {
          if (filmes.filmes[id_filme].Genre[t] ==
              controle.usuarios[id_usuario].generos.vetor[i].dado) {
            inserirFim(controle.usuarios[id_usuario].recomendados,
                       filmes.filmes[id_filme].Title);
            j++;
            break;
          }
        }
      }
    }
  }
}

void NotaFilme(Controle_filme &filmes, Controle &controle, int id_usuario) {

  inserirFim(controle.usuarios[id_usuario].Nota,
             filmes.filmes[id_usuario].Rating);
}
#endif