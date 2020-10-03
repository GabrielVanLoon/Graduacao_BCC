/*
 * Projeto Final de Arduino: Minigame "Nao Exploda!"
 * 
 * INSTRUCOES
 * O jogo se inicia com 5 jogadores e 5 leds acessos. Em cada rodada um dos Led's eh sorteado 
 * aleatoriamente para conter uma bomba escondida. Os jogadores se revezam e apertam os botoes 
 * que representam os Led's e aquele que apertar o que contem a bomba eh eliminado. Uma nova 
 * rodada se inicia, porém com 4 jogadores, e as etapas se repetem eliminando um jogador por rodada 
 * ate que haja um vencedor.
 * 
 * MATERIAIS UTILIZADOS
 * - 20 Jumpers
 * - 5 Led's verdes e 1 Led vermelho
 * - 6 Resistores 220 Ohms
 * - 5 Push Buttons
 * - Buzzer 5 Voltz
 * 
 * CONEXOES NA PROTOBOARD (Visualizar esquema na pasta /images )
 * - Leds: digitalPin [mode:OUTPUT] -> Led -> Resistor 220 Ohm -> GND
 * - PushButtons: digitalPin [mode:INPUT_PULLUP] -> Push Button -> GND
 * - Buzzer: digitalPin [mode:OUTPUT] -> Buzzer -> GND
 * Obs: Caso se decida nao utilizar o modo PULLUP nos Push Buttons, eh necessario a 
 * utilizacao de um resistor de 10k Ohms como pull down no circuito.
 * 
 * AUTORES
 * Gabriel Van Loon Bode da Costa Dourada Fuentes Rojas - gabrielvanloon@usp.br 
 * Tamiris Fernandes Tinelli - tamiris.tinelli@usp.br
 * Mathias Fernandes Duarte Coelho - mathfernades@usp.br
 * 
 * EXTRA
 * Ao fim de cada jogatina, o arduino executa um trecho de musica do jogo Legend 
 * of Zelda, sendo a partitura utilizada para a transcricao das notas devidamente
 * referênciadas no código abaixo.
 * 
 * Prof. Eduardo do Valle Simões
 * ICMC/USP - Jun/2018
 */

// Configuracoes de pinagem
const int pinBuzzer = 2;
const int pinLedExplosao = 3;  
const int pinLedsBombas[5] = {4, 5, 6, 7, 8};

const int pinBotoes[5] = {9, 10, 11, 12, 13};
int auxBotoes[5] = {0, 0,  0,  0,  0}; // Salva o estado do botao no Loop anterior. HIGH para nao pressionado e LOW para pressionado

// Configuracoes do jogo
int qtdJogadores = 5; // Quantidade de jogadores na rodada, descresce a cada partida
int bombaEscondida = 0; // Pino em que a bomba fica escondida naquela rodada
bool estadoBotoes[5]; // 'true' se ainda nao foi utilizado, 'false' se ja foi utilizado naquela rodada
bool novaRodada = true; // Verifica se uma nova rodada precisa ser iniciada no proximo loop. 1 para inicia, 0 para nao iniciar

// Constantes para os sons utilizados pela musica de fim de jogo
#define SIb 247 // Si abaixo
#define DO 262
#define DOs 277
#define RE 294
#define REs 311
#define MI 330
#define FA 349
#define FAs 370 
#define SOL 392
#define SOLs 415
#define LA 440
#define LAs 466
#define SI 494
#define SIs 494
#define DOa 523 // Do acima

void setup() {
  // Setando os pinos
  pinMode(pinBuzzer, OUTPUT);
  pinMode(pinLedExplosao, OUTPUT);

  for(int i = 0; i < 5; i++){
    pinMode(pinLedsBombas[i], OUTPUT);
    pinMode(pinBotoes[i],INPUT_PULLUP);
  }

  // Porta serial e semente do Randon()
  Serial.begin(9600);
  randomSeed(analogRead(0));

  Serial.write("Execucao de setup finalizada com sucesso!\n");
}

void loop() {
  
  if(novaRodada == true){
    iniciarRodada();
  }

  // Verificando se algum botao ativo na partida foi pressionado
  for(int i = 0; i < qtdJogadores; i++){
     // Verificacoes: 
     // - pinBotoes[i] == LOW: Verifica que o botao esta pressionado
     // - auxBotoes[i] == HIGH: Impede que botoes que foram segurados execute a funcao multiplas vezes
     // - estadoBotoes[i] == true: Verifica se o botao ainda nao foi utilizado na rodada
     if( digitalRead(pinBotoes[i]) == LOW && auxBotoes[i] == HIGH && estadoBotoes[i] == true){

        Serial.write("Acao: um dos botoes da rodada foi pressionado!\n");
        
        if(i == bombaEscondida){

          // Som do clique da bomba
          nota(360,200);
          nota(260,200);
          nota(100,600);

          // Efeitos visuais de explosao
          cabum();

           // Toca a musica de fim de jogo, 
          if(qtdJogadores == 2){
            tocarMusica();
          }
          
          // Prepara para iniciar nova partida no proximo loop
          qtdJogadores--;
          novaRodada = true;

        } else {
          
          // Apaga o Led e desativa o botao nessa rodada
          digitalWrite(pinLedsBombas[i], LOW);
          estadoBotoes[i] == false;

          // Som do clique do led
          nota(500,100);
          nota(350,100);
          nota(560, 100);
         
        }

        // Impede que o programa leia dois botoes apertados simultaneamente
        break;
     }
  }

  // Salvar o estado dos botoes nesse loop
  for(int i = 0; i < 5; i++){
    auxBotoes[i] = digitalRead(pinBotoes[i]);
  }
  
  delay(100);
  
}

/*  Funcao iniciarRodada()
 *  Eh executada ao iniciar o arduino ou quando a bomba explode e um jogador perde.
 *  Ela configura os leds e as variaveis responsaveis pelo funcionamento do programa.
 */
void iniciarRodada(){
  
  // Inicia uma nova jogatina com 5 jogadores
  if(qtdJogadores == 1){
    qtdJogadores = 5;
  }
  
  // Desligar todos os leds remanescentes das outras partidas
  // Reajusta os estados dos botoes na partida
  // Desliga o led da bomba
  for(int i = 0; i < 5; i++){
    digitalWrite(pinLedsBombas[i], LOW);
    estadoBotoes[i] = true;
    auxBotoes[i] = 0;
  }
  digitalWrite(pinLedExplosao, LOW);
  
  // Ligar os leds da rodada atual
  for(int i = 0; i < qtdJogadores; i++){
    digitalWrite(pinLedsBombas[i], HIGH);
  }

  // Define onde esta escondida a bomba
  bombaEscondida = random(qtdJogadores);

  novaRodada = false;

  Serial.write("Execucao de iniciarRodada() finalizada com sucesso!\n");
}

/*
 * Funcao cabum()
 * Ativa o som de explosao e o piscar das luzes
 */
void cabum(){
  
  // Loop para piscar 5x, quando for par acende e quando for impar apaga os leds
  for(int i = 0; i < 10; i++){
    int acao = (i % 2 == 0) ? HIGH : LOW; 

    digitalWrite(pinLedExplosao, acao);
    for(int j = 0; j < 5; j++){
      digitalWrite(pinLedsBombas[j], acao);
    }
    
    delay(100);
  }
 
}

/*
 * Funcao nota()
 * funcao para encapsular a sequencia de comandos ideias para a reproducao
 * de notas musicais no buzzer.
 */
void nota(int frequencia, int duracao){
   tone(pinBuzzer, frequencia, duracao); // Nota musical 
   delay(duracao*1.3); // Intervalo entre as notas
   noTone(pinBuzzer);
}

// Funcao tocarMusica()
// Executa a musica de fim de jogo, retirada da partitura da musica titulo do jogo Legend of Zelda
// 
// Partitura lida por Tamiris: http://tabs-ocarina.com/ocarina-tab-legend-zelda-title-theme-revised
void tocarMusica(){
    
    // Primeira linha
    nota(DOa, 800);
    delay(200);
    
    nota(SOL, 200);
    nota(SOL, 200);
    nota(DOa, 200);
    
    nota(LAs, 100);
    nota(SOLs,100);
    nota(LAs, 800);
    delay(200);
    delay(400);
    
    // Segunda linha
    nota(DOa, 800);
    delay(200);

    nota(SOLs, 200);
    nota(SOLs, 200);
    nota(DOa,  200);

    nota(SI, 100);
    nota(LA, 100);
    nota(SI, 800);
    delay(200);
    delay(400);

    // Terceira linha
    nota(SOL, 800);
    nota(SOL, 800);
    
    nota(SOL, 800);
    nota(SOL, 800);

    // Quarta linha
    nota(DOa, 400);
    nota(SOL, 400);
    delay(200);

    nota(DO, 200);
    nota(DO, 100);
    nota(RE, 100);
    nota(MI, 100);
    nota(FA, 100);

    nota(SOL, 800);
    delay(800);

    // Quinta linha
    nota(DOa, 400);
    nota(SOL, 400);
    delay(200);

    nota(DO, 200);
    nota(DO, 100);
    nota(RE, 100);
    nota(MI, 100);
    nota(FA, 100);

    nota(SOL, 800);
    delay(800);

    // Sexta linha
    nota(DOa, 400);
    nota(SOL, 400);
    delay(200);

    nota(DO, 200);
    nota(DO, 100);
    nota(RE, 100);
    nota(MI, 100);
    nota(FA, 100);

    nota(SOL, 800);
    delay(400);

    // Setima linha
    nota(SIb, 200);
    nota(SOLs,200);
    nota(LAs,200);

    nota(DOa,800);
    delay(400);

    nota(DOa, 200);
    nota(LAs, 200);
    nota(SOLs, 200);
    
    nota(LAs, 200);
    nota(LAs, 100);

    // Oitava linha
    nota(SOLs, 100);
    nota(SOL, 800);
    nota(SOL, 400);

    nota(FA, 200);
    nota(FA, 100);
    nota(SOL, 100);
    nota(SOLs, 800);

    nota(SOL, 200);
    nota(FA, 200);

    // Nona Linha
    nota(REs, 200);
    nota(REs, 100);
    nota(FA,  100);
    nota(FA,  800);

    nota(FA,  200);
    nota(MI,  200);

    nota(RE,  200);
    nota(RE,  100);
    nota(MI,  100);

    nota(FAs,  800);

    // Decima linha
    nota(LA,  400);
    nota(SOL,  400);
    
    nota(SOL,  100);
    nota(SOL,  100);
    nota(SOL,  200);
    
    nota(SOL,  100);
    nota(SOL,  100);
    nota(SOL,  200);
    
    nota(SOL,  100);
    nota(SOL,  100);
    nota(SOL,  200);
    nota(SOL,  200);
}

// Bom Jogo =D