// Librerias
#include <Adafruit_GFX.h>
#include <Adafruit_LEDBackpack.h>

Adafruit_8x8matrix matrix = Adafruit_8x8matrix();

int gasPin = 2; // Pin digital conectado al pin DOUT del sensor
int buzzerPin = 3; // Pin digital conectado al buzzer

void setup() {
  pinMode(gasPin, INPUT); // Pin como entrada
  pinMode(buzzerPin, OUTPUT); //  Pin del buzzer como salida
  matrix.begin(0x70); // Inicializa la matriz LED 
  Serial.begin(9600); 
}

void loop() {
  int gasValue = digitalRead(gasPin); // Leer el valor del sensor

  if (gasValue == HIGH) { // Si se detecta gas
    Serial.println("¡Gas detectado!");
    digitalWrite(buzzerPin, HIGH); 
    displayFlame(); 
    delay(1000); 
    digitalWrite(buzzerPin, LOW); 
    clearDisplay(); 
    delay(1000); 
  }
}

void displayFlame() {
  // Definir la forma de la animación 
  byte flame[8] = {
    B00111100,
    B01111110,
    B11111111,
    B11111111,
    B11111111,
    B01111110,
    B00111100,
    B00000000
  };

  // Mostrar la animación en la matriz LED
  for (int row = 0; row < 8; row++) {
    for (int col = 0; col < 8; col++) {
      if (bitRead(flame[row], col)) {
        matrix.drawPixel(col, row, LED_ON);
      } else {
        matrix.drawPixel(col, row, LED_OFF);
      }
    }
  }

  // Actualizar la matriz LED
  matrix.writeDisplay();
}

// Limpiar 8x8x

void clearDisplay() {
  matrix.clear();
  matrix.writeDisplay();
}
