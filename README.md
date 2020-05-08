# PuzzleBobble :joystick:

Este projeto foi realizado no primeiro semestre do curso de Ciência da Computação (Bacharelado) na UnB (Universidade de Brasília). Seu objetivo era implementar um jogo 2D similar ao Puzzle Bobble utilizando todos os conhecimentos obtidos durante o semestre sobre a linguagem C (bibliotecas, matrizes, strings, funções, variáveis globais e ponteiros).

## Começando

Este projeto foi desenvolvido no Linux e pode ocorrer alguns bugs caso tente rodar no WIndows
Para compilar o programa utilize o comando
```
gcc -std=c99 -o code JogoAPC.c
```
Para rodar o programa compilado bastar usar o comando
```
./code
```

### Instalando

É necessário ter o GCC e o projeto em sua máquina.
Para instalar o GCC utilize o comando
```
sudo apt-get install gcc
```
E para o projeto use
```
git clone https://github.com/plaisteixo-5/PuzzleBobble.git
```
E basta compilar e rodar o programa com os códigos anteriores.

## O jogo

Ao executar o arquivo compilado aparecerá uma tela com o nome do Jogo e ao apertar enter o usuário entrará no menu. Neste momento o programa irá criar os arquivos config.txt e ranking.bin.

### Menu

![Captura de tela de 2020-04-27 14-08-48](https://user-images.githubusercontent.com/61848846/80439690-775db000-88dd-11ea-8c58-61ff66e53784.png?w=10)

O menu é divídido em 5 opções:
1. Jogar
   * Ao entrar nessa o jogador tem quatro opções: Jogar criando um replay, acessando um replay já existente, jogar sem utilizar ou criar um replay e voltar ao menu principal. A mecanica do replay funciona da seguinte maneira: você cria ou acessa um arquivo .txt que já contem as peças que foram salvas em uma partida.
   * O jogo roda em um tabuleiro 9x16 e na linha 1 coluna 7 do tabuleiro sempre vai ficar a peça que vai ser lançada.As peças são A, B, C, D e E e o objetivo do jogo é marcar a maior quantidade de pontos, combinando as peças antes do Game Over. O Game Over vai acontecer quando quando tiver peças na linha 2 e o programa não conseguir mais abaixar o tabuleiro. O jogo já inicia como padrão de 4 peças necessárias para marcar ponto e 20 segundos pro tabuleiro abaixar e este é seu default.
   
2. Instruções
   * Todas as informações sobre como o jogo funciona, controles e etc.

3. Configurações
   * Este menu tem 3 opções: configurar a quantidade de peças necessárias para a explosão e o tempo para o tabuleiro abaixar, ativar o modo ranqueado e voltar ao menu.
   * Ao selecionar o modo ranqueado o programa irá solicitar um nick para que seja salvo no ranking do game. Automaticamente, ao selecionar o modo ranqueado, o game seta o número de peças para explosão como 5 e o tempo de descida como 15.
   
4. Ranking
   * O ranking mostra a pontução dos jogadores que jogaram o modo ranqueado desde que o programa foi iniciado. Assim que o programa for finalizado o ranking é resetado.

5. Sair
   * Sai do jogo.

### Comandos

O jogo é controlado pelas teclas "A", que move a mira para a esquerda, "D", que move a mira para a direita, "S" e Espaço, que lança a peça, e a tecla "0" que é a forma de sair da partida a qualquer momento.

## Autor
Felipe __"Fon"__ Fontenele

## MIT LICENSE

Copyright (c) 2020 Felipe

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
