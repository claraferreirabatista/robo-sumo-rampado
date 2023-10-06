//********************Inclusão das bibliotecas**************
#include <AFMotor.h>
#include <Ultrasonic.h>

//********************Definição dos pinos********************
#define triggere A2 // definicao do trigger do ultrassom esquerdo
#define echoe A3    // definicao do echo esquerdo
#define triggerd A4 // definicao do trigger do ultrassom direito
#define echod A5    // definicao do echo direito
#define sensor1 A6  // definicao do sensor de linha 1
#define sensor2 A7  // definicao do sensor de linha 2

//********************Criação dos objetos********************
AF_DCMotor motor1(1);
AF_DCMotor motor2(2);

Ultrasonic ue(triggere, echoe); // declaração do ultrassom esquerdo
Ultrasonic ud(triggerd, echod); // declaração do ultrassom direito

//********************Função de configuração******************
void setup()
{
  // Configuração de velocidade dos motores de 0 a 255
  motor1.setSpeed(255);
  motor2.setSpeed(255);
  pinMode(sensor1, INPUT); // Configura o pino do sensor 1 como entrada
  pinMode(sensor2, INPUT); // Configura o pino do sensor 2 como entrada
}
//********************Função principal********************
void loop()
{
  // Cálculo e conversão da leitura do sensor ultrassônico
  long me = ue.timing();
  float de = ue.convert(me, Ultrasonic::CM);
  long md = ud.timing();
  float dd = ud.convert(md, Ultrasonic::CM);

  // loop de busca enquanto dentro da borda
  while (digitalRead(sensor1) == 0 && digitalRead(sensor2) == 0)
  { // verifica se esta dentro da borda
    if (dd > 20 && de > 20)
      slow();
    else if (dd <= 20 && de > dd)
      direita();
    else if (dd > de && de <= 20)
      esquerda();
    else if (dd == de && (de <= 20¦¦ dd <= 20))
      ataque();
  }

  // quando encontrar a borda da meia volta
  parada();
  delay(1000);
  tras();
  delay(1000);
  esquerda();
  delay(500);
  parada();
}
}
//********************Movimenta o robô para frente com pausas(estrategia slow search)********************
void slow()
{
  motor1.run(FORWARD); // Motor dir
  motor2.run(FORWARD); // Motor esq
  delay(300);          // tempo de movimento do robo
  // pausa para diminuir atrito da rampa com a superficie
  motor1.run(RELEASE); // Motor dir
  motor2.run(RELEASE); // Motor esq
  delay(300);          // tempo da pausa

  //********************Movimenta o robô para frente a toda a força********************
}
void ataque()
{
  motor1.run(FORWARD); // Motor dir
  motor2.run(FORWARD); // Motor esq
}
//********************Movimenta o robô para trás********************
void tras()
{
  motor1.run(BACKWARD); // Motor dir
  motor2.run(BACKWARD); // Motor esq
}
//********************Para o robo********************
void parada()
{
  motor1.run(RELEASE); // Motor dir
  motor2.run(RELEASE); // Motor esq
}
//********************Movimenta o robô para esquerda********************
void esquerda()
{
  motor1.run(FORKWARD); // Motor dir
  motor2.run(BACKWARD); // Motor esq
}
//********************Movimenta o robô para direita********************
void direita()
{
  motor1.run(BACKWARD); // Motor dir
  motor2.run(FORWARD);  // Motor esq
}