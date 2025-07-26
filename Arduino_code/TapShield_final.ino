#include <TapShield_inferencing.h> 
#include <SoftwareSerial.h>

#define PIEZO_PIN A0
#define BUFFER_SIZE 100

float signalBuffer[BUFFER_SIZE];

#define SIM_TX 8
#define SIM_RX 7
SoftwareSerial sim800(SIM_TX, SIM_RX);

int getSignalData(size_t offset, size_t length, float *out_ptr) {
  memcpy(out_ptr, &signalBuffer[offset], length * sizeof(float));
  return 0;
}

void setup() {
  Serial.begin(9600);
  sim800.begin(9600);
  pinMode(PIEZO_PIN, INPUT);
  delay(3000); 

  Serial.println("🤖 TapShield ML System Started...");
  sendSMS("+91XXXXXXXXXX", "TapShield armed and ready!");
}

void loop() {
  for (int i = 0; i < BUFFER_SIZE; i++) {
    signalBuffer[i] = analogRead(PIEZO_PIN);
    delay(10);
  }
  ei_impulse_result_t result;
  signal_t signal;
  signal.total_length = BUFFER_SIZE;
  signal.get_data = &getSignalData;

  EI_IMPULSE_ERROR res = run_classifier(&signal, &result, false);
  if (res != EI_IMPULSE_OK) {
    Serial.print("❌ Inference failed: ");
    Serial.println(res);
    return;
  }
  String detectedLabel = "";
  float highestConfidence = 0.0;

  for (size_t i = 0; i < EI_CLASSIFIER_LABEL_COUNT; i++) {
    float conf = result.classification[i].value;
    Serial.print(result.classification[i].label);
    Serial.print(": ");
    Serial.println(conf);

    if (conf > highestConfidence) {
      highestConfidence = conf;
      detectedLabel = result.classification[i].label;
    }
  }

  if (highestConfidence > 0.80) { 
    if (detectedLabel == "one_tap") {
      sendSMS("+91XXXXXXXXXX", "I am Safe.");
    } else if (detectedLabel == "two_tap") {
      sendSMS("+91XXXXXXXXXX", "Please Call Me.");
    } else if (detectedLabel == "three_tap") {
      sendSMS("+91XXXXXXXXXX", "EMERGENCY! Need Help Immediately.");
    } else {
      Serial.println("⚠️ Unrecognized pattern.");
    }
  }

  delay(2000); 
}
void sendSMS(String number, String message) {
  Serial.println("📤 Sending SMS: " + message);
  sim800.println("AT+CMGF=1"); delay(500);
  sim800.print("AT+CMGS=\"");
  sim800.print(number);
  sim800.println("\"");
  delay(500);
  sim800.print(message);
  sim800.write(26);
  delay(5000);
  Serial.println("✅ SMS Sent");
}
