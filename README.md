# Palavrinhas
Jogo desenvolvido em C para a disciplina de Estrutura de Dados do curso de Ciência da Computação em 2022.1. [Link para jogar](https://replit.com/@maisamrr/PALAVRINHASojogo#main.c).

**Palavrinhas** tem como base o jogo [Wordle](https://www.nytimes.com/games/wordle/index.html), desenvolvido por Josh Wardle, e sua versão brasileira [Termo](https://term.ooo/), desenvolvida por Fernando Serboncini.<br>
O objetivo é adivinhar uma palavra de 5 letras sorteada aleatoriamente. À medida em que o usuário faz uma tentativa, recebe um feedback do jogo sobre as letras inseridas. Há um total de 6 tentativas por rodada.<br>
Nesse jogo, o banco de dados utiliza a leitura de um arquivo em .TXT que contém 50 palavras escolhidas aleatoriamente, incluindo apenas verbos no infinitivo, substantivos e advérbios.
<br>

## Detalhamento de Estados
ES1 - **Início**. Menu principal: Apresenta o menu da tela inicial, contendo as opções: Novo jogo (ES2), Regras (ES3), Créditos (ES4), Estatísticas (ES5) e Sair (ES6). Transições: É capaz de ir para uma nova partida do jogo (ES2), ler as regras e entender como jogar (ES3), ler os créditos do jogo (ES4), ver as estatísticas para o atual usuário (ES5) e finalizar a rodada atual do usuário (ES6).<br>

ES2 - **Novo jogo**. Realiza a execução da dinâmica do jogo. É sorteada uma palavra aleatória do banco de dados e em seguida é solicitado ao usuário inserir sua tentativa (input). É feita a verificação inicial, se a palavra tem 5 caracteres e se estes são apenas letras. Caso o usuário tenha inserido uma tentativa inválida, é solicitada uma nova tentativa. Caso a tentativa seja válida, a verificação das letras e posições acontece, posteriormente exibindo o feedback na tela em forma de caracteres coloridos de acordo com as regras do jogo. As regras são:<br>
Caso a letra esteja na posição certa, o caractere é pintado de verde;<br>
Caso esteja na palavra mas em uma posição errada é pintado de amarelo;<br>
Caso não esteja na palavra, de vermelho;<br>
Se todas as letras foram acertadas na posição correta, o usuário ganhou e a partida atual é encerrada, voltando para o menu inicial (ES1). Após cada input seguido de feedback, o número de tentativas é incrementado (caso o input seja válido) e é feita sua validação dentro das 6 tentativas disponibilizadas por partida. Caso o usuário atinja as 6 tentativas sem acertar todas as letras em suas respectivas posições, a partida atual é encerrada e ele perde, retornando ao menu inicial (ES1). Finalizando a rodada, o número de partidas é incrementado para constar nas estatísticas (ES5), assim como também é contabilizado se o usuário obteve uma vitória na rodada.<br><br>

ES3 - **Regras**. Exibe as regras e dinâmica do jogo. Transições: É capaz de voltar apenas para o menu inicial (ES1).<br><br>

ES4 - **Créditos**. Exibe os créditos do jogo. Transições: É capaz de voltar apenas para o menu inicial (ES1).<br><br>

ES5 - **Estatísticas**. Exibe a quantidade de partidas jogadas, vitórias e porcentagem de acertos, tendo como base o usuário atual. Transições: É capaz de voltar apenas para o menu inicial (ES1).<br><br>

ES6 - **Sair**. Descrição: Finaliza o jogo do usuário atual.<br>

## Especificação das Estruturas de Dados

ED1 - **Estatísticas do jogador**: estrutura contendo dois tipos de dados char e int, que reúnem informações sobre o usuário que está jogando, a quantidade de partidas, a quantidade de vitórias e a porcentagem de vitórias.<br>
```c
typedef struct{
    char user[50];
    int partidas;
    int vitorias;
    int porcVitorias;
}t_jogador;
```
Protótipo da função: estrutura que guarda as informações do usuário em relação às partidas.<br>
```c
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

```

ED2 - **Verificação de letras da Palavrinha**: estrutura de tabela hash utilizada para verificar os acertos e posições de letras numa tentativa em relação à palavra que deve ser acertada. A estrutura define uma tabela de 256 posições preenchida de zeros, baseada na tabela ASCII. O mapeamento dela é feito de 1:1, de forma que um laço percorra a palavra sorteada e preencha na tabela apenas as posições das letras que constam nela. Ao fazer a comparação com o input do usuário, o retorno da tabela indica o status das letras.<br>
```c
int novo_jogo(t_jogador *jogador){
(...)
char *segredo = palavras[nmr_aleatorio];
    int tam = 5;
    char tentativa[6];
    int tabela[256] = {0};
    for(int i = 0; segredo[i] != '\0'; i++)
        tabela[segredo[i]]++;
 
    int letra_certa_lugar_certo, letra_certa_lugar_errado;
    
    (...)
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
              letra_certa_lugar_errado++;
        }else{
              texto_vermelho();
              printf("%c", tentativa[i]);
              reset_texto();
        }
      }

```
## Conclusões
O desenvolvimento do projeto seguiu de forma fluida, sendo implementados os estados e, à medida em que a equipe avançava, complementos a eles foram sendo adicionados para tornar a jogabilidade mais próxima do jogo original.<br>
A maior dificuldade encontrada foi resolver a lógica de feedback das letras, pois nas pesquisas desenvolvidas pelo grupo não eram utilizadas estrutura de dados, apenas encadeamento de laços nas variáveis. Porém a implementação da tabela hash tornou o código do projeto mais limpo, permitindo também um processamento mais rápido sem a necessidade de tantos laços, resolvendo a lógica de maneira direta e assertiva.<br>
O resultado final do “Palavrinhas” é funcional e pode ser jogado por qualquer pessoa com acesso ao [link](https://replit.com/@maisamrr/PALAVRINHASojogo#main.c). A limitação do banco de palavras e o problema com retorno de letras repetidas são ressalvas a serem apresentadas.<br>
