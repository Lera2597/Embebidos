int POT = A0;      // Pin de entrada de senal del potenciometro
int POT_valor = 0; // Variable de almacenamiento del porcentaje del potenciometro 
byte porcentaje;    // Variable de conversion a porcentaje

void setup() {
  Serial.begin(9600); // Inicializacion del puerto serial a 9600 baudios
}

void loop() {
  POT_valor = analogRead(POT);              // Lee el valor del sensor (Rango de 0 a 1023)
  porcentaje = map(POT_valor,0,1023,0,100); // Porcentaje del rango de 0 a 100%
                                            // 100 corresponde a 5V y 0 a 0V
  //Serial.println(porcentaje);
  Serial.write(porcentaje);                 // Escritura por puerto del porcentaje de voltaje
  delay(20);                               // Tiempo de retraso para siguiente rutina
}
