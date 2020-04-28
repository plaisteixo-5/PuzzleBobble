/*####################################################
#Universidade de Brasilia                            #
#Instituto de Ciencias Exatas                        #
#Departamento de Ciencia da Computacao               #
#                                                    #
#Algoritimos e Programacao de Computadores           #
#- 1/2019                                            #
#                                                    #
#Aluno : Felipe Fontenele Dos Santos                 #
#Matricula : 19/0027622                              #
#Turma : A                                           #
# Versao do compilador : gcc 8.2.0                   #
#Descricao : O Jogo a seguir foi desenvolvido        #
#para ser semelhante ao jogo bubbles, criado em		 #
#1994. Ele e baseado em combinar pecas para acumular #
#pontos.						                     #
#####################################################*/

#define _XOPEN_SOURCE 500
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<unistd.h>
#include<string.h>
#include<stdbool.h>
#if _WIN32
    #define CLEAR "cls"
#else
    #define CLEAR "clear"
#endif
#define MENUMAIN 1
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define BLUE "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN "\x1b[36m"
#define RESET "\x1b[0m"
#define RED "\x1b[31m"
#ifndef _WIN32
#include<termios.h>
#include<fcntl.h>
    int kbhit(){
        struct termios oldt, newt;
        int ch, oldf;
        tcgetattr(STDIN_FILENO,&oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
        fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
        ch = getchar();
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        fcntl(STDIN_FILENO, F_SETFL, oldf);
        if(ch != EOF){
        ungetc(ch,stdin);
        return 1;
        }
        return 0;
    }
    int getch(void) {
        int ch;
        struct termios oldt;
        struct termios newt;
        tcgetattr(STDIN_FILENO,&oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        ch = getchar();
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        return ch;
    }
#else
#include <conio.h>
#endif

typedef struct{
    int qtdP;
    int tempo;
}configuracoes;

typedef struct{
    char nick[11];
    int score;
}Ranked;
Ranked Y[10];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Variaveis Globais.                                                                                               //
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int largura = 16,altura = 9 , S = 1 , pontuacao , conectaP, tempoM = 2, Flag_LR = 0, Flag_UR = 0 , ModoRank = 0;
int contJogador = 0;
char Tabuleiro[9][16],TabAux[9][16], peca = 'A', nomeJogador[11];
char nomeArq[40];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Cabecalho de funcoes para evitar erros e warnings.                                                               //
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int time();
int letrasAleatorias();
void menu();
void Config();
void ModificaPeca();
void Jogo();
void mira();
void ordenaRank();
void verificaVoadora();
void printaPrincipalNoAux();
void MontaMira();
void printaTabuleiro();
void montaTabuleiro();
void limpaTabuleiro();
void Intrucoes();
void Ranking();
void setArch();
_Bool pecaLinha2();
_Bool ehLetra(char);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
~~                                                    Funcoes                                                      ~~
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

_Bool pecaLinha2(){
    int i;

    for(i = 0 ; i < 16 ; i++){
        if (i == 7) i++;
        if(ehLetra(Tabuleiro[1][i]) || ehLetra(Tabuleiro[2][7])) return true;
    }
    return false;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Está função seta o arquivo binário, caso ele não exista, e o arquivo das configurações, fazendo com que o número //
//de peças necessárias para pontuar seja 4 e o tempo para abaixar o tabuleiro seja 20 segundos.                    //
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void setArch(){

    FILE* arquivo;
    FILE* config;
    arquivo = fopen("ranking.bin","wb");
    fclose(arquivo);
    config = fopen("config.txt","w+");
    fprintf(config, "4 20");
    fclose(config);

}

_Bool ehLetra(char letra){
    if (letra == 'A' || letra == 'B' || letra == 'C' || letra == 'D' || letra == 'E') return true;
    else return false;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Funcao para verificar se tem pecas voando pelo tabuleiro.                                                        //
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void verificaVoadora(){
    int i,j;

    for(i = 8 ; i >= 0 ; i--){
        for(j = 0 ; j < 15 ; j ++){
            if(ehLetra(Tabuleiro[i][j])){
                if(Tabuleiro[i][j-1] == ' ' || Tabuleiro[i][j-1] == '*'){
                    if(Tabuleiro[i+1][j-1] == ' ' || Tabuleiro[i+1][j-1] == '*'){
                        if(Tabuleiro[i+1][j] == ' ' || Tabuleiro[i+1][j] == '*'){
                            if(Tabuleiro[i+1][j+1] == ' ' || Tabuleiro[i+1][j+1] == '*'){
                                if(Tabuleiro[i][j+1] == ' ' || Tabuleiro[i][j+1] == '*'){
                                    if(Tabuleiro[i+1][j] == ' ' || Tabuleiro[i+1][j] == '*'){
                                        if(Tabuleiro[i-1][j] == ' ' || Tabuleiro[i-1][j] == '*'){
                                            if(Tabuleiro[i-1][j-1] == ' ' || Tabuleiro[i-1][j-1] == '*'){
                                                if(Tabuleiro[i-1][j+1] == ' ' || Tabuleiro[i-1][j+1] == '*'){
                                                    Tabuleiro[i][j] = '*';
                                                }
                                            }
                                        }
                                    }
                                    
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Funcao chamada para ordernar e printar o Ranking.                                                                //
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ordenaRank(){
    char saux[15];
    FILE* arquivo;
    system(CLEAR);

    int i, j;
    for(j = 0; j < contJogador; j++){
        for(i = 0; i<= contJogador; i++){
            if(Y[i].score < Y[i+1].score){
                int aux = Y[i].score;
                strcpy(saux,Y[i].nick);
                Y[i].score = Y[i+1].score;
                strcpy(Y[i].nick,Y[i+1].nick);
                Y[i+1].score = aux;
                strcpy(Y[i+1].nick,saux);
            }
        }
    }
    
    arquivo = fopen("ranking.bin","rb");
    for(i = 0 ; i < contJogador ; i++){
        fread(&Y, sizeof(Ranked),1,arquivo);
        printf("%d - Nome: %s\nScore: %d\n",i+1,Y[i].nick,Y[i].score);
        printf("---------------------------\n");
    }
    fclose(arquivo);
    getchar();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Funcao de Game Over.                                                                                             //
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GameOver(){
    
    system(CLEAR);

    printf(RED"Game Over!!\n"RESET);
    printf("Sua pontuacao foi de: %d\n",pontuacao);
    printf("Aperte ENTER para continuar.\n");
    getchar();
    menu();

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Funcao para abaixar o tabuleiro assim que o tempo determinado chegar.                                            //
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void abaixaPecaTab(){
    int i,j;
    char linhaAux[16];
    char aux[16];
    printaPrincipalNoAux();
    if(pecaLinha2()) GameOver();

    for(i = 8 ; i >= 1 ; i--){
        for (j = 0 ; j < 16 ; j++){
            if (i != 8){
                aux[j] = Tabuleiro[i][j];
                Tabuleiro[i][j] = linhaAux[j];
                linhaAux[j] = aux[j];
            }
            else linhaAux[j] = Tabuleiro[i][j];
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Esta funcao serve para transcrever o tabuleiro original em um auxiliar, para que a funcao explode e			  //
//verificaAdjacentes funcionem corretamente.																	  //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void printaPrincipalNoAux(){
    int i,j;
    for(i = 0 ; i < 8 ; i++){
        for(j = 0 ; j < 16 ; j++){
            TabAux[i][j] = Tabuleiro[i][j];
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//A funcao verificaAdjacentes serve para analisar todas as pecas que estao ao redor de uma posicao especifica,    //
//que eh enviada pela funcao mira para a funcao explode, que envia para a verificaAdjacentes. Nela sao guardadas  //
//posicoes que sao retornadas para a funcao explode, e assim ela consegue verificar todas as pecas ao seu redor e // 
//todas ao redor da mesma.                                                                                        //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int verificaAdjacentes(int contador, char peca, int px, int py , int Linha[] , int Coluna[]){

    if(Tabuleiro[py][px] == peca && TabAux[py][px] == peca){
        TabAux[py][px] = '*';
        contador++;
    }
    if(Tabuleiro[py][px+1] == peca && TabAux[py][px+1] == peca){
        TabAux[py][px+1] = '*';
        contador++;
        Coluna[S] = px+1;
        Linha[S] = py;
        S++;
    }
    if(Tabuleiro[py+1][px+1] == peca && TabAux[py+1][px+1] == peca){
        TabAux[py+1][px+1] = '*';
        contador++;
        Coluna[S] = px+1;
        Linha[S] = py+1;
        S++;
    }
    if(Tabuleiro[py+1][px] == peca && TabAux[py+1][px] == peca){
        TabAux[py+1][px] = '*';
        contador++;
        Coluna[S] = px;
        Linha[S] = py+1;
        S++;
    }
    if(Tabuleiro[py+1][px-1] == peca && TabAux[py+1][px-1] == peca){
        TabAux[py+1][px-1] = '*';
        contador++;
        Coluna[S] = px-1;
        Linha[S] = py+1;
        S++;
    }
    if(Tabuleiro[py][px-1] == peca && TabAux[py][px-1] == peca){
        TabAux[py][px-1] = '*';
        contador++;
        Coluna[S] = px-1;
        Linha[S] = py;
        S++;
    }
    if(Tabuleiro[py-1][px-1] == peca && TabAux[py-1][px-1] == peca){
        TabAux[py-1][px-1] = '*';
        contador++;
        Coluna[S] = px-1;
        Linha[S] = py-1;
        S++;
    }
    if(Tabuleiro[py-1][px] == peca && TabAux[py-1][px] == peca){
        TabAux[py-1][px] = '*';
        contador++;
        Coluna[S] = px;
        Linha[S] = py-1;
        S++;
    }
    if(Tabuleiro[py-1][px+1] == peca && TabAux[py-1][px+1] == peca){
        TabAux[py-1][px+1] = '*';
        Coluna[S] = px+1;
        Linha[S] = py-1;
        contador++;
        S++;
    }
    return contador;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Essa funcao faz a verificacao das pecas que vao ser explodidas.												  //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void explode(int linhaExplosao, int colunaExplosao , char peca){
    printaPrincipalNoAux();

    int contador = 0;
    int Linha[100];
    int Coluna[100];
    int i,j,px,py;
    S = 0;
    Linha[S] = linhaExplosao;
    Coluna[S] = colunaExplosao;
    S = 1;
    while(S > 0 ){
        S--;
        px = Coluna[S];
        py = Linha[S];
        contador = verificaAdjacentes(contador , peca , px , py , Linha , Coluna);
    }

    if(contador >= conectaP){
        for(i = 0 ; i < 8 ; i++){
            for(j = 0 ; j < 15 ; j++){
                Tabuleiro[i][j] = TabAux[i][j];
            }
        }
        pontuacao = pontuacao+contador*10;
    }

    verificaVoadora();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//A funcao MontaMira recebe o coeficiente angular que eh enviado pela funcao mira. Nesta funcao ele multiplica o  //
//coeficiente angular pela posicao da linha ,que vai de 0 ate 7, e eh arrendodado, e o valor resultante eh a nova //
//posicao do "-" que formara a reta.                                                                              //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MontaMira(double CoeficienteAngular){
    double y;
    int k, j = 7 , i;

    for(i = 1 ; i < 8 ; i++) {
        y = CoeficienteAngular*i;
        k = (int) y;
        if((Tabuleiro[i][k+j] == ' ') && (Tabuleiro[i][k+j] != '#') && (i != 1) && (i != 0) && (i != 8) && (k+j<largura) && (k+j>0)){
            Tabuleiro[i][k+j] = '-';
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//A funcao letrasAleatorias usa a ferramenta rand para gerar valores aleatorios. Os resultados sao retornados para //
//a funcao mira.                                                                                                   //
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int letrasAleatorias(){
    char letra = 'A';
    letra = 'A'+rand()%5;
    return letra;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//A funcao printaTabuleiro, como o nome ja diz, printa o tabuleiro original na tela sempre que eh chamada.         //
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void printaTabuleiro(){
    int i,j;
    char peca = letrasAleatorias();
    
    for(i = 8 ; i >= 0; i--){
        for(j = 0 ; j < 16 ; j++){
            if(Tabuleiro[i][j] == 'A'){
                printf(RED"A"RESET);
            }
            else if(Tabuleiro[i][j] == 'B'){
                printf(GREEN"B"RESET);
            }
            else if(Tabuleiro[i][j] == 'C'){
                printf(YELLOW"C"RESET);
            }
            else if(Tabuleiro[i][j] == 'D'){
                printf(CYAN"D"RESET);
            }
            else if(Tabuleiro[i][j] == 'E'){
                printf(MAGENTA"E"RESET);
            }
            else if(Tabuleiro[i][j] == '*'){
                printf(YELLOW"*"RESET);
            }
            else printf("%c",Tabuleiro[i][j]);
        }
        printf("\n");
    }

    printf("\n");
    printf(RED"Pontuacao:"RESET"%d\n",pontuacao);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Esta funcao eh chamada apenas uma vez, e ela monta toda a base do tabuleiro que eh usado ao longo da partida.    //
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void montaTabuleiro(){
    int i,j;
    for(i = 8 ; i >= 0; i--){//for pra montar as linhas do tabuleiro
        for(j = 0 ; j < 16 ; j++){// for para montar as colunas do tabuleiro
            if(i==0 || j==0 || j==15|| i==8){//if para verificar se é a borda
                Tabuleiro[i][j]='#';
                TabAux[i][j] = '#';
            }
           else if(j==7){//else para verificar se é o meio do tabuleiro
                if((i !=0 && i != 8) || (i != 1 && j != 8)){//a linha não pode ser igual a primeira ou a ultima
                    Tabuleiro[i][j]='-';
                    TabAux[i][j]='-';
                }
            }
            else{//else para se não for borda nem o meio do tabuleiro
                Tabuleiro[i][j]=' ';
                TabAux[i][j] = ' ';
            }
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Esta funcao serve para limpar o tabuleiro original da tela, ele remove todos os caracteres, excetos as letras.   //
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void limpaTabuleiro(){
    int i,j;
    for(i = 1 ; i < altura - 1 ; i++){
        for(j = 1 ; j < largura - 1 ; j++){
            if(Tabuleiro[i][j] != 'A' && Tabuleiro[i][j] != 'B' && Tabuleiro[i][j] != 'C' && Tabuleiro[i][j] != 'D' && Tabuleiro[i][j] != 'E' && Tabuleiro[i][j] != '#'){
                Tabuleiro[i][j]=' ';
                TabAux[i][j] = ' ';
            }
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//A funcao mira eh a essencial para o funcionamento do jogo. Nela sao realizadas as principais tarefas e a maioria //
// das outras funcoes retorna a ela. O timer é startado no inicio dela, e a verificação de todas as flags do       //
//replay tambem acontecem no inicio. Em seguida ela le o input do teclado e vai modificando o tabuleiro,           //
//movimentando a mira e atirando as letras ate que a partida acabe.                                                //
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void mira(){
    FILE* arquivo;
    pontuacao = 0;
    char peca = 'A',pecaDoReplay;
    int flag = 0,flag1 = 0, ColunaAnterior = 7,LinhaAnterior = 1,salvaLinha;
    int l,tecla,salvaColuna = 0,i;
    double CoeficienteAngular = 0;
    time_t begin = time(0);
	time_t end = time(0);
	pontuacao = 0;
    system(CLEAR);

    if(Flag_UR == 1){
        arquivo = fopen(nomeArq,"r");
    }

    end=(end+1)-begin;
    montaTabuleiro();
    printaTabuleiro();

    while(tecla != '0'){
        verificaVoadora();
        tecla=getch();
        limpaTabuleiro();

        if(tecla=='a' || tecla=='A'){
            CoeficienteAngular-=0.1;
            MontaMira(CoeficienteAngular);
        }
        else if(tecla == 'D' || tecla == 'd'){
            CoeficienteAngular+=0.1;
            MontaMira(CoeficienteAngular);
        }
        else if(tecla == ' ' || tecla == 's'){
            MontaMira(CoeficienteAngular);
            while(flag != 1){
                for(i = 2 ; i < 8 && flag == 0; i++){
                    flag1 = 0;
                    for(l = 1 ; l < 16 && flag1 == 0 ; l++){
                        if(!ehLetra(Tabuleiro[i][l]) && Tabuleiro[i][l] != '#'){
                            if(Tabuleiro[i][l] == '-'){
                                Tabuleiro[LinhaAnterior][ColunaAnterior] = '-';
                                TabAux[LinhaAnterior][ColunaAnterior] = '-';
                                if (i != 7){
                                    LinhaAnterior = i;
                                    ColunaAnterior = l;
                                }
                                Tabuleiro[i][l] = peca;
                                flag1 = 1;
                                printaTabuleiro();
                                salvaColuna = l;
                                salvaLinha = i;
                                system(CLEAR);
                            }
                        }
                    }
                    printaTabuleiro();
                    usleep(50000);
                    system(CLEAR);
                }
                salvaLinha--;
                // i--;
                // printf("%d %d %d\n",i,salvaLinha,salvaColuna);
                // getchar();
                explode(salvaLinha,salvaColuna,peca);
                printaTabuleiro();
                usleep(99990);
                system(CLEAR);
                limpaTabuleiro();
                MontaMira(CoeficienteAngular);
                printaTabuleiro();
                flag = 1;
            }
            flag = 0;
            ColunaAnterior = 7;
            LinhaAnterior = 1;

            if(Flag_UR == 0){
                peca = letrasAleatorias();
                if(Flag_LR == 1){
                    FILE* arquivo;
                    arquivo = fopen(nomeArq,"a+");
                    fprintf(arquivo,"%c",peca);
                    fclose(arquivo);
                }
            }
            else{
                if(fscanf(arquivo,"%c",&pecaDoReplay) != EOF){
                    peca = pecaDoReplay;
                }
                else menu();
            }
            
            Tabuleiro[1][7]=peca;
        }

        end = time(0);
        end = end-begin;
        if(end >= tempoM){
            abaixaPecaTab();
            begin = time(0);
        }

        Tabuleiro[1][7] = peca;
        system(CLEAR);
        printaTabuleiro();
        if(pecaLinha2()) break;
    }

    if(Flag_UR == 1){
        fclose(arquivo);
    }

    if(ModoRank == 1){
        FILE* fd;
        FILE* conf;
        fd = fopen("ranking.bin","ab");
        strcpy(Y[contJogador].nick,nomeJogador);
        Y[contJogador].score = pontuacao;
        fwrite(&Y , sizeof(Ranked) , 1 , fd);
        fclose(fd);
        conf = fopen("config.txt","w+");
        fprintf(conf,"4 20");
        fclose(conf);
        ModoRank = 0;
        contJogador++;
    }

    GameOver();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Esta funcao serve para que o jogador escolha a forma como vai jogar, seja criando ou usando um replay já         //
//existente. O replay salva todas as peças que foram jogadas em um arquivo .txt que o jogador escolher e quando    //
//ele quiser jogar com a mesma configuração, basta informar o nome do .txt que salvou o jogo. No inicio dela eh    //
//aberto e lido o arquivo texto das configuracoes do game.                                                         //
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Jogo(){ 
    system(CLEAR);
    char input;
    pontuacao = 0;

    FILE* arquivo;
    configuracoes X;
    arquivo = fopen("config.txt","r+");
    fscanf(arquivo,"%d %d",&X.qtdP,&X.tempo);
    conectaP = X.qtdP;
    tempoM = X.tempo;
    fclose(arquivo);

    while(input != '4' || input == '0'){
        system(CLEAR);
        printf(RED"1"RESET" - Criar Replay\n"BLUE"2"RESET" - Escolher Replay\n"MAGENTA"3"RESET" - Jogar Sem Utilizar ou Criar Replay\n"YELLOW"4"RESET" - Voltar\n");

        input = getch();

        switch(input){
            case '0':
            menu();
            break;
            case '1':
                Flag_LR = 1;
                system(CLEAR);
                printf("Digitar o nome de um arquivo .txt para o Replay que sera criado:\n");
                scanf("%s",nomeArq);
                arquivo = fopen(nomeArq,"w");
                fclose(arquivo);
                mira();
            break;
            case '2':
                Flag_UR = 1;
                printf("Digite o nome de um replay com a extensao .txt para roda-lo:\n");
                scanf("%s",nomeArq);
                arquivo = fopen(nomeArq , "r");
                if(arquivo == NULL){
                    printf("Arquivo inexistente!!\nTente novamente ou pressione 4 para voltar ao menu\n");
                    getchar();
                }
                else{
                    fclose(arquivo);
                    mira();
                }
            break;
            case '3':
                mira();
            break;
            case '4':
            menu();
            break;
            default:
            printf("Opcao invalida, escolha uma das opcoes novamente\n");
            getchar();
        }
    }
}

void Instrucao(){//funcao pra instruir o jogo
    system(CLEAR);
    printf(RED"#######################################################################################\n"RESET);
    printf("\n");
    printf("O Jogo funciona da seguinte maneira: o tablueiro é delimitado por #, e o jogador deve lançar letras pelo tabuleiro com o objetivo de combina-las.\n");
    printf("Ao combinar x letras, você acumula pontos e a área ao redor também eh eliminada\n");
    printf("Use as letras A e D para mover a mira para a esquerda e para a direita, respectivamente, e espaco para atira-las\n");
    printf("Caso queira parar o jogo no meio da partida, basta apertar zero =)\n");
    printf("\n");
    printf("O sistema de replay serve para salvar as pecas que sao lancadas em uma partida normal. Para criar um replay, basta criar um arquivo .txt apos escolher a opcao 1 do menu Jogar.\n");
    printf(RED"#######################################################################################\n"RESET);
    getchar();
}

void Ranking(){

    ordenaRank();
    menu();
}

void ModificaPeca(){
    int flag = 0;
    char entrada = 'A';
    configuracoes X;
    FILE* arquivo;

    arquivo = fopen("config.txt","w");

    while(entrada != '2'){
        system(CLEAR);
        printf("1 - Configurar pecas conectadas e tempo para o tabuleiro abaixar\n2 - Voltar para o Menu\n");
        entrada = getch();

        if(entrada == '1'){
            while(!flag){
                system(CLEAR);

                printf(RED"Digite um numero entre 03 e 10, para escolher a quantidade de pecas necessarias para a explosao\n"RESET);
                printf(RED"e o tempo entre 10 e 35 que o tabuleiro levara para ser abaixado: \n"RESET);
                scanf("%d",&X.qtdP);
                scanf("%d",&X.tempo);

                if(((X.qtdP <= 10) && (X.qtdP >= 03)) && ((X.tempo >= 10) && (X.tempo <= 35))){
                    fprintf(arquivo,"%d %d\n", X.qtdP,X.tempo);
                    flag++;
                }
                else {
                    printf(RED"Valor invalido. Aperte ENTER e digite novamente.\n"RESET);
                    getchar();
                    getchar();
                }
            }
            fclose(arquivo);
            entrada = '2';
        }
        else if (entrada == '2') return;

        else{
            system(CLEAR);
            printf("Opcao nao reconhecida, aperte ENTER e escolha uma das opcoes disponiveis novamente.\n");
            getchar();
        }
    }
    printf(GREEN"As pecas necessarias para a explosao agora sao: %d \nO tempo para o tabuleiro abaixar eh de: %d\nAperte ENTER para continuar\n"RESET,X.qtdP,X.tempo);
    getchar();
    getchar();

   Config();
}

void Config(){//funcao pra configurar o jogo
    system(CLEAR);
    char entrada;
    int flag = 1,test;
    FILE* arquivo;

    printf(BLUE"1"RESET" - Pecas e Tempo\n"RED"2"RESET" - Ativar Modo Rankeado\n"MAGENTA"3"RESET" - Voltar\n");
    entrada = getch();
    switch(entrada){
        case '1' :
            ModificaPeca();
            break;
        case '2' :
            ModoRank = 1;
            while(flag){
                printf("Digite um nickname de 1 a 10 caracteres:\n");
                scanf("%s",nomeJogador);
                test = strlen(nomeJogador);
                if(test>10 || test<1){
                    printf(RED"Nickname invalido, digite novamente:\n"RESET);
                }
                else{  
                    printf("Nome aceito.\n"GREEN"VAMOS JOGAR\n"RESET);
                    getchar();
                    flag = 0;
                    arquivo = fopen("config.txt","w+");
                    fprintf(arquivo,"5 15");
                    fclose(arquivo);
                    menu();
                }
            }
            break;
        case '3' :
            menu();
            break;
        default:
            printf("Opcao nao reconhecida, aperte ENTER e escolha uma das opcoes disponiveis novamente.\nAperte ENTER e voce voltara para o Menu");
            getchar();
            menu();
    }
}

void menu(){//funcao do menu
    system(CLEAR);
    char input;
    system(CLEAR);
    
    Flag_LR = 0;
    Flag_UR = 0;

    printf(MAGENTA"1"RESET" -Jogar\n"BLUE"2"RESET" - Intrucoes\n"RED"3"RESET" - Configuracoes\n"YELLOW"4"RESET" - Ranking\n"GREEN"5"RESET" - Sair\nSelecione uma Opcao:\n");

    input = getch();
    switch(input){
        case '1' :
            Jogo();
            break;
        case '2' :
            Instrucao();
            break;
        case '3' :
            Config();
            break;
        case '4' :
            Ranking();  
            break;
        case '5' :
            system(CLEAR);
            printf(GREEN"Obrigado"RESET""RED" por"RESET" "YELLOW"Jogar"RESET""BLUE" ^.^!!"RESET);
            exit(0);
        default:
        printf("Opcao nao reconhecida, aperte ENTER e escolha uma das opcoes disponiveis novamente.\n");
        getchar();
        menu();
    }
}

int main(){
    int input;
    srand(0);
    system(CLEAR);
    setArch();
    printf(RED"F"BLUE"O"GREEN"N"YELLOW"T "RED"B"BLUE"U"GREEN"B"YELLOW"B"RED"L"BLUE"E"GREEN"S"RESET);
    getchar();
    while(input != 5){
        menu();
    }
    return 0;
}