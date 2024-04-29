#ifndef USUARIOS
#define USUARIOS
#include "Tlista.h"
#include <iostream>
using namespace std;

struct Usuario
{
  string nome;
  int idade;
  Tlista<string, 3> generos;
  Tlista<string, 50> assistidos;
  Tlista<string, 20> salvos;
  Tlista<string, 10> recomendados;
  Tlista<string, 50> Nota;
};

struct Controle
{
  Usuario usuarios[100];
  int numUsuarios = 0;
  int indice_usuario = 0;
};

struct FilmeNota
{
  string filme;
  double mediaNota;
};

void cadastro(Controle &controle)
{
  if (controle.numUsuarios >= 100)
  {
    cout << "Número máximo de usuários atingido!" << endl;
    return;
  }
  cout << "Qual seu nome? " << endl;
  cin >> controle.usuarios[controle.numUsuarios].nome;
  cout << "Qual sua idade? " << endl;
  cin >> controle.usuarios[controle.numUsuarios].idade;
  cout << "Gêneros disponíveis: Action, Adventure, Fantasy, Thriller, Drama, "
          "Sci-Fi, Comedy, Family, Mystery, Western, Romance, Animation, "
          "Crime, Horror"
       << endl;
  cout << "Quais são os generos que você gosta? Digite um por vez" << endl;
  for (int i = 0; i < 3; i++)
  {
    string dado;
    cin >> dado;
    inserirFim(controle.usuarios[controle.numUsuarios].generos, dado);
  }
  controle.numUsuarios++;
  controle.indice_usuario = controle.numUsuarios - 1;
  cout << "Cadastrado com sucesso!" << endl;
}

void imprimir_usuarios(Controle &controle)
{
  for (int i = 0; i < controle.numUsuarios; i++)
  {
    cout << "Nome: " << controle.usuarios[i].nome << endl;
    cout << "Idade: " << controle.usuarios[i].idade << endl;
    for (int j = 0; j < 3; j++)
    {
      cout << "Genero " << j + 1 << ": "
           << controle.usuarios[i].generos.vetor[j].dado << "\n";
    }
    for (int j = 0; j < 50; j++)
    {
      if (controle.usuarios[i].assistidos.vetor[j].dado ==
          "")
      { // esses ifs são para ignorar se não tiver nada na lista
        continue;
      }
      cout << "Assistidos " << j + 1 << ": "
           << controle.usuarios[i].assistidos.vetor[j].dado << "\t" << endl;
    }
    for (int j = 0; j < 20; j++)
    {
      if (controle.usuarios[i].salvos.vetor[j].dado == "")
      {
        continue;
      }
      cout << "Salvos " << j + 1 << ": "
           << controle.usuarios[i].salvos.vetor[j].dado << "\t" << endl;
    }
    for (int j = 0; j < 10; j++)
    {
      if (controle.usuarios[i].recomendados.vetor[j].dado == "")
      {
        continue;
      }
      cout << "Recomendados " << j + 1 << ": "
           << controle.usuarios[i].recomendados.vetor[j].dado << "\t" << endl;
    }
    cout << endl;
  }
}

void logar(Controle &Usuario)
{
  cout << "Login" << endl;
  for (int i = 0; i < Usuario.numUsuarios; i++)
  {
    cout << "Usuário: " << i << " " << Usuario.usuarios[i].nome << endl;
  }
  cout << "Digite o número do usuário: ";
  cin >> Usuario.indice_usuario;
  while (Usuario.indice_usuario < 0 ||
         Usuario.indice_usuario >= Usuario.numUsuarios)
  {
    cout << "Usuário inválido! Veja a lista e digita qual para acessar" << endl;
    cin >> Usuario.indice_usuario;
  }
  cout << "Usuário Logado! Seu nome é: "
       << Usuario.usuarios[Usuario.indice_usuario].nome << endl;
}

void inserirNota(Controle &Usuario)
{
  int nota = 0;
  int id_assistidos =
      rand() % Usuario.usuarios[Usuario.indice_usuario].assistidos.quantidade;
  string filme = Usuario.usuarios[Usuario.indice_usuario]
                     .assistidos.vetor[id_assistidos]
                     .dado;
  cout << "Digita a nota do filme: " << filme << " (de 0 a 5)" << endl;
  cin >> nota;
  while (nota < 0 || nota > 5)
  {
    cout << "Nota inválida, digite novamente: (0 a 5)";
    cin >> nota;
  }
  Usuario.usuarios[Usuario.indice_usuario].Nota.vetor[id_assistidos].dado =
      nota;
  Usuario.usuarios[Usuario.indice_usuario].Nota.quantidade++;
}

void Raking(Controle Usuario)
{
  if (Usuario.usuarios[Usuario.indice_usuario].Nota.quantidade == 0)
  {
    cout << "Não há notas cadastradas" << endl;
    return;
  }
  double somaNotas = 0;
  int numNotas = 0;
  Tlista<FilmeNota, 50> ranking;

  for (int i = 0; i < Usuario.usuarios[Usuario.indice_usuario].Nota.quantidade;
       i++)
  {
    string filme =
        Usuario.usuarios[Usuario.indice_usuario].assistidos.vetor[i].dado;
    for (int j = 0; j < Usuario.numUsuarios; j++)
    {
      if (Usuario.usuarios[j].Nota.vetor[i].dado != "")
      {
        somaNotas += stod(Usuario.usuarios[j].Nota.vetor[i].dado);
        numNotas++;
      }
    }
    if (numNotas > 0)
    {
      double media = somaNotas / numNotas;
      FilmeNota filmeNota{filme, media};
      inserirFim(ranking, filmeNota);
    }
  }

  for (int i = 0; i < ranking.quantidade - 1; i++)
  {
    for (int j = 0; j < ranking.quantidade - i - 1; j++)
    {
      if (ranking.vetor[j].dado.mediaNota <
          ranking.vetor[j + 1].dado.mediaNota)
      {
        swap(ranking.vetor[j], ranking.vetor[j + 1]);
      }
    }
  }

  for (int k = 0; k < ranking.quantidade; k++)
  {
    cout << "Filme: " << ranking.vetor[k].dado.filme
         << " Nota: " << ranking.vetor[k].dado.mediaNota;
  }
}

#endif