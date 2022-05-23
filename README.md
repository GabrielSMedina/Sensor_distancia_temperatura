# Sensor_distancia_temperatura

Um pequeno projeto que visa aumentar a precisão de um sensor de distância HC-SR04 acoplando um sensor de temperatura. A ideia é que sabendo a temperatura do ambiente possamos modificar a equação de conversão do Echo para distância, trocando a velocidade do som de 340 m/s para a velocidade do som real naquele momento.

## Circuito

![Circuito](https://user-images.githubusercontent.com/42703913/169857711-d54c83a0-847e-4955-9a71-3c06809d3627.png)


É um circuito relativamente simples, feito apenas para testar a hipótese levantada. Ele consiste em um sensor ultrassônico e um sensor de temperatura, ambos acoplados no Arduíno pela protoboard.

## Código

O código é relativamente simples, o diferencial dele esta na aplicação de alguns conceitos de cinemática para chegar a resultados satisfatórios, criando funções para pegar a temperatura do ambiente e com isso descobrir a uma aproximação da velocidade do som naquele instante, além de outra função que substitui a biblioteca nativa do sensor convertendo o Echo(tempo de retorno da onda) em uma distância.

### Lendo a temperatura do ambiente
```
double TempGrausC(){
  temp = analogRead(TEMP);
  temp = (temp *5)/1024;
  tempC = (temp - 0.5)*100;
  return tempC;
}
```

### Achando a velocidade do som no ambiente
``` 
double VelocidadeDoSomNoAr(double tempC){
  return 331.45 * pow((tempC + 273.15) / 273.15, 0.5);
} 
```

### Convertendo o Echo em distância da forma correta
```
double SensorHC(double vSom){
  digitalWrite(TRIG, 1); // Comeca a mandar a onde
  delayMicroseconds(10);
  digitalWrite(TRIG, 0); // Encerra o envio da onda
  t = pulseIn(ECHO, 1); // Captura o tempo de retorno da onda
  //s = t * 0,0017
  s = t * vSom* 100 / 1000000 / 2; // Calcula a distancia do objeto segundo o tempo
  return s; // Retorna distancia
}
```
