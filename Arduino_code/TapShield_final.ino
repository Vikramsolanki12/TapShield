#include <TapShield_inferencing.h>  // TinyML model header
#include <SoftwareSerial.h>


#define PIEZO_SENSOR_PIN A0
#define SIM_TX 8
#define SIM_RX 7


#define SAMPLE_SIZE 100
float sensorData[SAMPLE_SIZE];


SoftwareSerial sim800(SIM_TX, SIM_RX);

int captureData(size_t offset, size_t length, float *output) {
  memcpy(output, &sensorData[offset], length * sizeof(float));
  return 0;
}

void setup() {
  Serial.begin(9600);
  sim800.begin(9600);
  pinMode(PIEZO_SENSOR_PIN, INPUT);
  delay(2000);

  Serial.println("🔔 TapShield System Ready");
  sendSMS("+91XXXXXXXXXX", "TapShield activated and listening.");
}

void loop() {
  for (int i = 0; i < SAMPLE_SIZE; i++) {
    sensorData[i] = analogRead(PIEZO_SENSOR_PIN);
    delay(10);
  }

  ei_impulse_result_t result;
  signal_t inputSignal;
  inputSignal.total_length = SAMPLE_SIZE;
  inputSignal.get_data = &captureData;

  EI_IMPULSE_ERROR inferenceResult = run_classifier(&inputSignal, &result, false);
  if (inferenceResult != EI_IMPULSE_OK) {
    Serial.print("Error running inference: ");
    Serial.println(inferenceResult);
    return;
  }


  String classification = "";
  float confidence = 0.0;

  for (size_t i = 0; i < EI_CLASSIFIER_LABEL_COUNT; i++) {
    float score = result.classification[i].value;
    Serial.print(result.classification[i].label);
    Serial.print(": ");
    Serial.println(score);

    if (score > confidence) {
      confidence = score;
      classification = result.classification[i].label;
    }
  }
  if (confidence > 0.80) {
    if (classification == "one_tap") {
      sendSMS("+91XXXXXXXXXX", "Status: I am safe. ✔️");
    } else if (classification == "two_tap") {
      sendSMS("+91XXXXXXXXXX", "Alert: Please call me. 📞");
    } else if (classification == "three_tap") {
      sendSMS("+91XXXXXXXXXX", "⚠️ EMERGENCY! I need help immediately.");
    } else {
      Serial.println("Pattern unrecognized.");
    }
  }

  delay(2000);  // Pause before next read
}

void sendSMS(String recipient, String text) {
  Serial.println("Sending SMS...");
  sim800.println("AT+CMGF=1");
  delay(300);
  sim800.print("AT+CMGS=\"");
  sim800.print(recipient);
  sim800.println("\"");
  delay(300);
  sim800.print(text);
  sim800.write(26); // End SMS with CTRL+Z
  delay(4000);
  Serial.println("SMS Sent ✅");
}
