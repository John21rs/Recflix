
#include "Filme.h"
#include "Tlista.h"
#include <cstdlib> // para limpar a tela
#include <ctime>
#include <fstream>
#include <iostream>
#include <unistd.h>

using namespace std;

void ler_arquivo(Controle_filme &filme) {
  int limite = 500;
  fstream arquivo("listafilmes.csv");
  if (!arquivo.is_open()) {
    cout << "Erro ao abrir o arquivo." << endl;
    return;
  }

  int numFilmes = 0;
  string linha;
  getline(arquivo, linha);

  while (getline(arquivo, linha) && numFilmes < limite) {
    stringstream ss(linha);
    string token;

    getline(ss, filme.filmes[numFilmes].ID, ';');
    getline(ss, filme.filmes[numFilmes].Title, ';');
    getline(ss, filme.filmes[numFilmes].Year, ';');
    getline(ss, filme.filmes[numFilmes].Released, ';');
    getline(ss, filme.filmes[numFilmes].Runtime, ';');
    getline(ss, token, ';');
    stringstream generos(token);
    getline(ss, token, ';');
    int i = 0;
    while (getline(generos, token, ',')) {
      if (i < 3) {
        filme.filmes[numFilmes].Genre[i++] = token;
      }
    }
    getline(ss, filme.filmes[numFilmes].Director, ';');
    getline(ss, filme.filmes[numFilmes].Writer, ';');
    getline(ss, filme.filmes[numFilmes].Actors, ';');
    getline(ss, filme.filmes[numFilmes].Plot, ';');
    getline(ss, filme.filmes[numFilmes].Country, ';');
    getline(ss, filme.filmes[numFilmes].Awards, ';');
    getline(ss, filme.filmes[numFilmes].Poster, ';');
    getline(ss, filme.filmes[numFilmes].Rating, ';');
    getline(ss, filme.filmes[numFilmes].IMDB_Votes, ';');
    getline(ss, filme.filmes[numFilmes].IMDB_ID, ';');
    getline(ss, filme.filmes[numFilmes].DVD, ';');
    getline(ss, filme.filmes[numFilmes].Box_Office, ';');

    numFilmes++;
  }
  arquivo.close();
}

void imprimir(Controle_filme filmes) {
  string generos[30];
  for (int k = 0; k < 500; k++) {
    cout << "Filme: " << k << " - ";
    cout << filmes.filmes[k].Title << "||" << filmes.filmes[k].Year << endl;
    cout << filmes.filmes[k].Released << endl;
    cout << filmes.filmes[k].Runtime << endl;
    for (int t = 0; t < 3; t++) {
      if (filmes.filmes[k].Genre[t] == "") {
        continue;
      }
      cout << filmes.filmes[k].Genre[t] << endl;
    }
    cout << filmes.filmes[k].Director << endl;
    cout << filmes.filmes[k].Writer << endl;
    cout << filmes.filmes[k].Actors << endl << endl;
    cout << endl;
  }
}

void menu(Controle usuario) {
  cout << "Menu:" << endl;
  cout << "Bem vindo " << usuario.usuarios[usuario.indice_usuario].nome << "!"
       << endl;
  cout << "1 - Voltar ao menu principal" << endl;
  cout << "2 - Adicionar Filme aleatoriamente" << endl;
  cout << "3 - Adicionar Filme manualmente" << endl;
  cout << "4 - Adicionar Filme em Salvos aleatoriamente" << endl; //
  cout << "5 - Adicionar Filme em Salvos manualmente" << endl;    //
  cout << "6 - Ver assistidos de um Usuario especifico" << endl;
  cout << "7 - Ver cadastro de todos Usuario " << endl;
  cout << "8 - Lista de recomendados para o Usuario" << endl; //
  cout << "9 - Lista de salvos de Usuario" << endl;
  cout << "10 - Remover da lista de salvos" << endl;
  cout << "11 - Inserir nota" << endl;
  cout << "12 - Ver o Raking" << endl;
  cout << "0 - Sair" << endl;
}

void menu_principal(Controle &usuario) {
  int op;
  if (usuario.indice_usuario == 0) {
    cout << "Digite 1 para cadastrar o primeiro usuário, pois não há nenhum"
         << endl
         << endl;
  }
  cout << "1.Cadastrar usuário" << endl;
  if (usuario.numUsuarios > 0) {
    cout << "2.Logar" << endl;
  }
  cin >> op;
  switch (op) {
  case 1:
    cadastro(usuario);
    menu(usuario);
    break;
  case 2:
    if (usuario.numUsuarios > 0) {
      logar(usuario);
      menu(usuario);
    } else {
      cout << "Não há usuários cadastrados." << endl;
      menu_principal(usuario);
    }
    break;
  }
}

int main() {

  srand(time(NULL));
  bool acesso = true; // para sair do menu conforme se for digitado 0. Caso
                      // false, permanece
  Controle_filme filmes;
  Controle A;

  ler_arquivo(filmes);
  // imprimir(filmes);
  while (acesso) {
    menu_principal(A);
    int escolha, pos;
    cout << "Escolha uma opção: ";
    cin >> escolha;

    switch (escolha) {
    case 0: // Para finalizar o programa
      acesso = false;
      cout << "Finalizando o expediente" << endl;
      break;
    case 1:
      menu_principal(A);
      break;
    case 2:
      cout << "Inserir Lista Assitidos" << endl;
      cin >> pos;
      InseritListaAssistidos(filmes, A, pos);
      break;
    case 3:
      cout << "Você escolheu a Opção 3." << endl;
      imprimir(filmes);
      int id_usuario, pos;
      cout << "Qual usuario vai receber o filme ?";
      cin >> id_usuario;
      while (id_usuario > A.numUsuarios || id_usuario < 0) {
        cout << "Excedeu o limite do número de usuários que estão cadastrados "
                "ou você digitou um número negativo. Nesse momento, contém "
             << A.numUsuarios << "Digite novamente: " << endl;
        cin >> id_usuario;
      }
      cout << "Qual ID do filme ?";
      cin >> pos;
      InseritListaAssistidosManual(filmes, A, id_usuario, pos);
      break;
    case 4: {
      cout << "Vamos inserir Os filmes a salvos para assistir mais tarde: "
           << endl;
      cout << "para qual usuario desejas fazer a recomendação?" << endl;
      int pos;
      cin >> pos;
      InserirListaSalvos(filmes, A, pos);

      break;
    }
    case 5:
      imprimir(filmes);
      cout << "Qual usuario deseja adicionar o filme?" << endl;
      cin >> id_usuario;
      cout << "Indique qual o filme deseja adicionar: (Indique pelo índice)";
      cin >> pos;
      InseritListaAssistidosManual(filmes, A, 0, pos);
      break;
    case 6:
      cout
          << "Digite o índice para ver os assistidos de um Usuario especifico: "
          << endl;
      cin >> pos;
      imprimirTlista(A.usuarios[pos].assistidos);
      break;
    case 7:
      imprimir_usuarios(A);
      break;
    case 8:
      cout << "Escolha qual usuario voce deseja ver." << endl;
      cin >> pos;
      InserirListaRecomendado(filmes, A, pos);
      imprimirTlista(A.usuarios[pos].recomendados);
      break;
    case 9: {
      cout << "Diga qual usuario você deseja ver.";
      int pos;
      cin >> pos;
      imprimirTlista(A.usuarios[pos].salvos);
      break;
    }
    case 10: {
      int pos;
      cout << "Diga qual filme, pelo índice, você deseja remover";
      cin >> pos;
      RemoverListaSalvosManualmente(filmes, A, A.indice_usuario, pos);
      break;
    }
    case 11:
      inserirNota(A);
      break;
    case 12:
      Raking(A);
      break;
    default:
      menu_principal(A);
      break;
    }
  }
}
