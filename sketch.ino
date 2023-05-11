/*
  Caso esteja utilizando algum software de simulação, determine a temperatura do sensor em 20 graus para ter maior precisao
*/

// Pinos
#define ECHO 4
#define TRIG 5
#define TEMP A0

// Variaveis
double t, s, sensor, temp, tempC, vSom;

void setup()
{
  // Sensor HC
  pinMode(ECHO, INPUT); // Recebe uma onda
  pinMode(TRIG, OUTPUT); // Manda uma onda
  
  // Monitor serial
  Serial.begin(9600);
}

void loop()
{
  // Temperatura e Velocidade
  tempC = TempGrausC();
  vSom = VelocidadeDoSomNoAr(tempC);
  
  // Bloco de chamadas das funcoes
  s = SensorHC(vSom); // Chamada de funcao
  ImprimeNoMonitor(s, tempC, vSom); // Chamada de funcao
  
  delay(5000);
}

// Calcula a distancia para o sensor HC-SR04
double SensorHC(double vSom){
  digitalWrite(TRIG, 1); // Comeca a mandar a onde
  delayMicroseconds(10);
  digitalWrite(TRIG, 0); // Encerra o envio da onda
  t = pulseIn(ECHO, 1); // Captura o tempo de retorno da onda
  //s = t * 0,0017
  s = t * vSom* 100 / 1000000 / 2; // Calcula a distancia do objeto segundo o tempo
  return s; // Retorna distancia
}

// Bloco de impressao
void ImprimeNoMonitor(double s, double tempC, double vSom){
  Serial.print("Sensor HC: ");
  Serial.print(s);
  Serial.println("cm");
  Serial.println("");
  Serial.print("Temp: ");
  Serial.print(tempC);
  Serial.println(" C");
  Serial.println("");
  Serial.print("Velocidade: ");
  Serial.print(vSom);
  Serial.println(" m/s");
  Serial.println("-----------------------------------------");
  delay(100);
}

// Captação da temperatura
double TempGrausC(){
  temp = analogRead(TEMP);
  temp = (temp *5)/1024;
  tempC = (temp - 0.5)*100;
  return tempC;
}

// Calculo da velocidade do som no ambiente
double VelocidadeDoSomNoAr(double tempC){
 return 331.45 * pow((tempC + 273.15) / 273.15, 0.5);
}
