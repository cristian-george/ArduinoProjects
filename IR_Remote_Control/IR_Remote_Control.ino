#include <IRremote.hpp>

const int receiver = 6;  // Pin pentru receiver IR
const int LED_ROSU = 5;
const int LED_GALBEN = 4;
const int LED_VERDE = 3;

IRrecv irrecv(receiver);

void setup() {
  pinMode(LED_ROSU, OUTPUT);
  pinMode(LED_GALBEN, OUTPUT);
  pinMode(LED_VERDE, OUTPUT);

  Serial.begin(115200);
  IrReceiver.begin(receiver);
}

void loop() {
  if (IrReceiver.decode()) {
    uint32_t command = IrReceiver.decodedIRData.decodedRawData;
    if (command != 0) {
      Serial.print("Cod receptionat: ");
      Serial.println(command, HEX);

      switch (command) {
        case 0xBA45FF00: Serial.println("CH-"); break;
        case 0xB946FF00: Serial.println("CH"); break;
        case 0xB847FF00: Serial.println("CH+"); break;
        case 0xBB44FF00: Serial.println("FAST BACK"); break;
        case 0xBF40FF00: Serial.println("FAST FORWARD"); break;
        case 0xBC43FF00: Serial.println("PLAY / PAUSE"); break;
        case 0xF807FF00: Serial.println("VOL-DOWN"); break;
        case 0xEA15FF00: Serial.println("VOL-UP"); break;
        case 0xF609FF00: Serial.println("EQ"); break;
        case 0xE916FF00:
          Serial.println("0 - Stinge LED-uri");
          digitalWrite(LED_ROSU, LOW);
          digitalWrite(LED_GALBEN, LOW);
          digitalWrite(LED_VERDE, LOW);
          break;
        case 0xE619FF00: Serial.println("100+"); break;
        case 0xF20DFF00: Serial.println("200+"); break;
        case 0xF30CFF00:
          Serial.println("1 - Aprinde LED rosu");
          digitalWrite(LED_ROSU, HIGH);
          break;
        case 0xE718FF00:
          Serial.println("2 - Aprinde LED galben");
          digitalWrite(LED_GALBEN, HIGH);
          break;
        case 0xA15EFF00:
          Serial.println("3 - Aprinde LED verde");
          digitalWrite(LED_VERDE, HIGH);
          break;
        case 0xF708FF00: Serial.println("4"); break;
        case 0xE31CFF00: Serial.println("5"); break;
        case 0xA55AFF00: Serial.println("6"); break;
        case 0xBD42FF00: Serial.println("7"); break;
        case 0xAD52FF00: Serial.println("8"); break;
        case 0xB54AFF00: Serial.println("9"); break;
        default:
          Serial.println("Buton necunoscut");
          break;
      }
    }

    delay(500);
    IrReceiver.resume();  // Pregătire pentru următoarea citire
  }
}
