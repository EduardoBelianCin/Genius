int botao1 = 2, botao2 = 3, botao3 = 4, botao4 = 5; //variaveis
int led1 = 8, led2 = 9, led3 = 10, led4 = 11;
int buzzer = 7;
int dataPin = 6, latchPin = 12, clockPin = 13;
int tom1 = 349, tom2 = 392, tom3 = 440, tom4 = 494;
int stepDuration = 350;

#define MAX_LEVEL 50
int sequencia[MAX_LEVEL];
int nivelatual = 2;
int passo = 1;

void setup() {
  pinMode(botao1, INPUT_PULLUP); //botões
  pinMode(botao2, INPUT_PULLUP);
  pinMode(botao3, INPUT_PULLUP);
  pinMode(botao4, INPUT_PULLUP);

  pinMode(led1, OUTPUT); //leds
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(buzzer, OUTPUT); //buzzer
  pinMode(dataPin, OUTPUT); // Shift Register
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);

  Serial.begin(9600);

  randomSeed(analogRead(A0));

  start();
}

void loop() {
  int botaopressionado = verificarpressionado();
  if (botaopressionado != 0) {
    acender(botaopressionado);

    if (botaopressionado == sequencia[passo]) {
      passo++;

      if (passo == nivelatual) {
        delay(1000);
        nivelatual++;

        if (nivelatual > MAX_LEVEL) {
          vitoria();
        } else {
          adicionarpasso();
          passo = 0;
          tocarsequencia();
        }
      }
    } else {
      gameover();
    }
  }
}

void start() { //funçao de inicio de partida
  for (int i = 0; i < 3; i++)
    digitalWrite(led1, HIGH);
    delay(100);
    digitalWrite(led1, LOW);
    digitalWrite(led2, HIGH);
    delay(100);
    digitalWrite(led2, LOW);
    digitalWrite(led3, HIGH);
    delay(100);
    digitalWrite(led3, LOW);
    digitalWrite(led4, HIGH);
    delay(100);
    digitalWrite(led4, LOW);
  delay(250);

  nivelatual = 1;
  passo = 0;
  adicionarpasso();
  tocarsequencia();
}

void adicionarpasso() { // funçao para adicionar um novo botao a ser apertado na sequencia
  sequencia[nivelatual - 1] = random(1, 5);
}

void tocarsequencia() { //funçao para o genius exibir os botoes que devem ser apertados
  delay(500);
  for (int i = 0; i < nivelatual; i++) {
    int passo = sequencia[i];
    acender(passo);
    delay(stepDuration / 2);
  }
}

void acender(int num) { //funçao acender o led e toca a nota musical
  switch(num) {
    case 1:
      digitalWrite(led1, HIGH);
      tone(buzzer, tom1, stepDuration);
      delay(stepDuration);
      digitalWrite(led1, LOW);
      break;
    case 2:
      digitalWrite(led2, HIGH);
      tone(buzzer, tom2, stepDuration);
      delay(stepDuration);
      digitalWrite(led2, LOW);
      break;
    case 3:
      digitalWrite(led3, HIGH);
      tone(buzzer, tom3, stepDuration);
      delay(stepDuration);
      digitalWrite(led3, LOW);
      break;
    case 4:
      digitalWrite(led4, HIGH);
      tone(buzzer, tom4, stepDuration);
      delay(stepDuration);
      digitalWrite(led4, LOW);
      break;
  }
}

int verificarpressionado() {
  if (digitalRead(botao1) == LOW) {
    delay(50);
    while (digitalRead(botao1) == LOW);
    return 1;
  }
  if (digitalRead(botao2) == LOW) {
    delay(50);
    while (digitalRead(botao2) == LOW);
    return 2;
  }
  if (digitalRead(botao3) == LOW) {
    delay(50);
    while (digitalRead(botao3) == LOW);
    return 3;
  }
  if (digitalRead(botao4) == LOW) {
    delay(50);
    while (digitalRead(botao4) == LOW);
    return 4;
  }
  return 0;
}

void vitoria() { //função para caso a pessoa vença
  tone(buzzer, 659, 200); delay(250);
  tone(buzzer, 659, 200); delay(250);
  tone(buzzer, 659, 200); delay(250);
  tone(buzzer, 784, 800); delay(250);

  start();
}

void gameover() { // função para caso a pessoa perca
  tone(buzzer, 150, 1500);
  for (int i = 0; i < 3; i++) {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, HIGH);
    delay(250);
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
    delay(250);
  }
  start();
}