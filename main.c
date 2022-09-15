#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

typedef struct{
    char user[50];
    int partidas;
    int vitorias;
    int porcVitorias;
}t_jogador;

int tela_inicial(){
    char arq[]="palavrinhas.txt";
    char ch;
    FILE *tela_abertura;
 
    tela_abertura = fopen(arq, "r");
    if(tela_abertura == NULL)
        printf("Não é possível abrir o arquivo.\n");
    else
        while((ch = fgetc(tela_abertura)) != EOF)
    putchar(ch);
    
    fclose(tela_abertura);

    return 0;
}

int tela_gameover(){
    char arq[]="gameover.txt";
    char ch;
    FILE *tela_gameover;
 
    tela_gameover = fopen(arq, "r");
    if(tela_gameover == NULL)
        printf("Não é possível abrir o arquivo.\n");
    else
        while((ch = fgetc(tela_gameover)) != EOF)
    putchar(ch);
    
    fclose(tela_gameover);

    return 0;
}

int tela_vitoria(){
    char arq[]="vitoria.txt";
    char ch;
    FILE *tela_vitoria;
 
    tela_vitoria = fopen(arq, "r");
    if(tela_vitoria == NULL)
        printf("Não é possível abrir o arquivo.\n");
    else
        while((ch = fgetc(tela_vitoria)) != EOF)
    putchar(ch);
    
    fclose(tela_vitoria);

    return 0;
}

void texto_vermelho(){
    printf("\033[1;31m");
}

void texto_amarelo(){
    printf("\033[1;33m");
}

void texto_verde(){
    printf("\033[0;32m");
}

void reset_texto(){
    printf("\033[0m");
}

int novo_jogo(t_jogador *jogador){

    //sorteando um numero aleatorio
    int nmr_aleatorio;
    srand(time(NULL));
    nmr_aleatorio = rand() % 10;

    //abrir arquivo de palavras
    FILE *banco_palavras;
    banco_palavras = fopen("banco_palavras.txt", "r");
  
    int qtd_palavras = 0;
    char* palavras[50];
    char linha[50];
    int i = 0;
    
    if (banco_palavras == NULL){
        printf("Erro ao sortear palavra.");
    } else {
        while(fgets(linha, sizeof linha, banco_palavras) != NULL){
        palavras[i] = strdup(linha);
        i++;
        qtd_palavras++;
        }
    }

    fclose(banco_palavras);
  
    //início nova função
    int gameover = 0;
    int contador_lances = 1;
    char *segredo = palavras[nmr_aleatorio];
    int tam = 5;
    char tentativa[6];
    int tabela[255] = {0}; // inicializa todos os valores do array com 0
    for(int i = 0; segredo[i] != '\0'; i++)
        tabela[segredo[i]]++;
  
    int letra_certa_lugar_certo, letra_certa_lugar_errado;
  
    while(contador_lances < 7 || gameover == 0){
        letra_certa_lugar_certo = 0;
        letra_certa_lugar_errado = 0;
        printf("Adivinhe uma palavra de 5 letras: \n");
        scanf("%[^\n]%*c", tentativa);
        if(strlen(tentativa) != 5) //verificar se o comprimento é de 5 letras
            printf("\"%s\" não é uma palavra válida.\n", &*tentativa);
        else {
            int letras = 0, i;
            for (i = 0; tentativa[i] != '\0'; i++){
                //verificar quantas letras tem a palavra
                if (isalpha(tentativa[i]) != 0){
                letras++;
                }
            }
            if(letras != 5){
                printf("\"%s\" não é uma palavra válida.\n", &*tentativa);
        } else {
            for(int i = 0; tentativa[i] != '\0'; i++) {
                if(i < tam && tentativa[i] == segredo[i]){
                    texto_verde();
                    printf("%c", tentativa[i]);
                    reset_texto();
                    letra_certa_lugar_certo++;
                }
                else if(tabela[tentativa[i]]){
                    texto_amarelo();
                    printf("%c", tentativa[i]);
                    reset_texto();
                }else{
                    texto_vermelho();
                    printf("%c", tentativa[i]);
                    reset_texto();
                }
            }
            contador_lances++;
        }
    }
        printf("\n");

        if(letra_certa_lugar_certo == 5){
            jogador->partidas++;
            jogador->vitorias++;
            system("clear");
            tela_vitoria();
            printf("\nPARABÉNS, você acertou a palavrinha: %s!!!\n", segredo);
            printf("\n\n\n");
            contador_lances = 7;
            gameover = 1;
        }else if(contador_lances == 7 && gameover == 0){
            gameover = 1;
            jogador->partidas++;
            system("clear");
            tela_gameover();
            printf("\nVocê perdeu. A palavra sorteada era: %s\n", segredo);
            printf("\n\n\n");
        }
    }

    //fim nova função

    return 0;
}

int regras(){
    printf("\n**REGRAS**\n");
    printf("Descubra a palavrinha de 5 letras em 6 tentativas. A palavrinha pode ser apenas categorias de verbo no infinitivo, substantivos, adjetivos ou advérbios.\nSe você acertou uma letra e a posição dela, ela será exibida em ");
    texto_verde();
    printf("verde.\n");
    reset_texto();
    printf("Se você acertou uma letra, mas a posição dela não está correta, ela será exibida em ");
    texto_amarelo();
    printf("amarelo.\n");
    reset_texto();
    printf("As letras já inseridas, mas não contidas na palavra serão exibidas em ");
    texto_vermelho();
    printf("vermelho.\n\n");
    reset_texto();
    
    return 0;
}

int creditos(){
    printf("\n**CRÉDITOS**\n");
    printf("Esse jogo foi desenvolvido por André Santoro, Gustavo Pedro Lima e Maísa Moreira para a disciplina de Projeto Integrador 2 do curso de Ciência da Computação no IESB. Ele foi desenvolvido apenas para fins didáticos.\nO jogo original se chama Termo e foi desenvolvido por Fernando Serboncini. Ele pode ser acessado em https://term.ooo/\n\n");

    return 0;
}

int estatisticas(t_jogador *jogador){
    if(jogador->partidas == 0){
        printf("Jogador: %s\nPartidas: 0\nVitorias: 0\nPorcentagem de Vitorias: 0%%\n\n\n", jogador->user);
    }else{
        jogador->porcVitorias = (jogador->vitorias*100/jogador->partidas);
        printf("Jogador: %s\n", jogador->user);
        printf("Partidas: %i\n",jogador->partidas);
        printf("Vitorias: %i\n",jogador->vitorias);
        printf("Porcentagem de vitorias: %i%%\n\n\n",jogador->porcVitorias);
  }

  return 0;
};

int main(void) {
    tela_inicial();
    
    printf("\n\n\n");
    char tecla_inicio;
    scanf("%c", &tecla_inicio);
  
    system("clear");

    t_jogador jogador;
    printf("Digite seu nick: \n");
    scanf("%s",jogador.user);
    jogador.partidas = 0;
    jogador.vitorias = 0;
    jogador.porcVitorias = 0;

    if (tecla_inicio == 'x' || tecla_inicio == 'X'){
        system("clear");
        int opcao;
        printf("Bem-vinde, %s!\n\n", jogador.user); 
        do{
            printf("**MENU INICIAL**\n");
            printf("0. Novo Jogo\n");
            printf("1. Regras\n");
            printf("2. Créditos\n");
            printf("3. Estatísticas\n");
            printf("4. Sair\n");

            printf("Escolha uma das opções acima:\n");
            scanf("%d%*c", &opcao);
            system("clear");
            switch(opcao){
                case 0: 
                    novo_jogo(&jogador);
                    break;
                case 1:
                    regras();
                    break;
                case 2:
                    creditos();
                    break;
                case 3:
                    estatisticas(&jogador);
                    break;
                case 4: 
                    exit(0);
                    break;
                default:
                    printf("Opção inválida.\n");
            }
        } while(opcao != 4);
  }
  
  return 0;
}