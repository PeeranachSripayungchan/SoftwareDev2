#if defined(ESP32)
#include <WiFi.h>
#include <FirebaseESP32.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#endif

// include ไลบรารีสำหรับรับค่าเวลา
#include <NTPClient.h>
#include <WiFiUdp.h>

//Provide the token generation process info.
#include <addons/TokenHelper.h>

//Provide the RTDB payload printing info and other helper functions.
#include <addons/RTDBHelper.h>

// ประกาศฟังก์ชันสำหรับรับค่าเวลา
// Variable to save current epoch time
unsigned long epochTime;
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");

// Function that gets current epoch time
unsigned long getTime() {
  timeClient.update();
  unsigned long now = timeClient.getEpochTime();
  return now;
}

/* 1. Define the WiFi credentials */
#define WIFI_SSID "AndroidAP"
#define WIFI_PASSWORD "12345678"

//For the following credentials, see examples/Authentications/SignInAsUser/EmailPassword/EmailPassword.ino

/* 2. Define the API Key */
#define API_KEY "AIzaSyDlAJ3GXYcYvm_eU89HoqzrYFxnvZl_MlM"

/* 3. Define the RTDB URL */
#define DATABASE_URL "lift-8cd72-default-rtdb.asia-southeast1.firebasedatabase.app/" //<databaseName>.firebaseio.com or <databaseName>.<region>.firebasedatabase.app

/* 4. Define the user Email and password that alreadey registerd or added in your project */
#define USER_EMAIL "6310301015@cdti.ac.th"
#define USER_PASSWORD "peekub123"

//Define Firebase Data object
FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;

unsigned long count = 0;

void setup()
{
  // สำหรับรับค่าเวลา
  timeClient.begin();

  Serial.begin(115200);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);

  /* Assign the api key (required) */
  config.api_key = API_KEY;

  /* Assign the user sign in credentials */
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;

  /* Assign the RTDB URL (required) */
  config.database_url = DATABASE_URL;

  /* Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h

  //Or use legacy authenticate method
  //config.database_url = DATABASE_URL;
  //config.signer.tokens.legacy_token = "<database secret>";

  //////////////////////////////////////////////////////////////////////////////////////////////
  //Please make sure the device free Heap is not lower than 80 k for ESP32 and 10 k for ESP8266,
  //otherwise the SSL connection will fail.
  //////////////////////////////////////////////////////////////////////////////////////////////

  Firebase.begin(&config, &auth);

  //Comment or pass false value when WiFi reconnection will control by your code or third party library
  Firebase.reconnectWiFi(true);

  Firebase.setDoubleDigits(5);

  /** Timeout options.

    //WiFi reconnect timeout (interval) in ms (10 sec - 5 min) when WiFi disconnected.
    config.timeout.wifiReconnect = 10 * 1000;

    //Socket connection and SSL handshake timeout in ms (1 sec - 1 min).
    config.timeout.socketConnection = 10 * 1000;

    //Server response read timeout in ms (1 sec - 1 min).
    config.timeout.serverResponse = 10 * 1000;

    //RTDB Stream keep-alive timeout in ms (20 sec - 2 min) when no server's keep-alive event data received.
    config.timeout.rtdbKeepAlive = 45 * 1000;

    //RTDB Stream reconnect timeout (interval) in ms (1 sec - 1 min) when RTDB Stream closed and want to resume.
    config.timeout.rtdbStreamReconnect = 1 * 1000;

    //RTDB Stream error notification timeout (interval) in ms (3 sec - 30 sec). It determines how often the readStream
    //will return false (error) when it called repeatedly in loop.
    config.timeout.rtdbStreamError = 3 * 1000;

    Note:
    The function that starting the new TCP session i.e. first time server connection or previous session was closed, the function won't exit until the
    time of config.timeout.socketConnection.

    You can also set the TCP data sending retry with
    config.tcp_data_sending_retry = 1;

  */

  // random int set-up
  randomSeed(analogRead(0));
}

void loop()
{
  //Flash string (PROGMEM and  (FPSTR), String,, String C/C++ string, const char, char array, string literal are supported
  //in all Firebase and FirebaseJson functions, unless F() macro is not supported.

  if (Firebase.ready() && (millis() - sendDataPrevMillis > 15000 || sendDataPrevMillis == 0))
  {
    sendDataPrevMillis = millis();

    // random int set-up
    // อุณหภูมิความร้อน (องศาเซลเซียส)
    int randNumber_Temp1 = random(20, 181);
    // ปริมาณแก็ส (PPM)
    int randNumber_PPM1 = random(0, 151);
    // ค่าปิดเปิดเสียงกริ่ง (ปิด = 0, เปิด = 1)
    int randNumber_OnOff1;
    if (randNumber_Temp1 < 150 && randNumber_PPM1 < 130){
      randNumber_OnOff1 = 0;
    }
    else {
      randNumber_OnOff1 = 1;
    }

    int randNumber_Temp2 = random(20, 181);
    // ปริมาณแก็ส (PPM)
    int randNumber_PPM2 = random(0, 151);
    // ค่าปิดเปิดเสียงกริ่ง (ปิด = 0, เปิด = 1)
    int randNumber_OnOff2;
    if (randNumber_Temp2 < 150 && randNumber_PPM2 < 130){
      randNumber_OnOff2 = 0;
    }
    else {
      randNumber_OnOff2 = 1;
    }

    int randNumber_Temp3 = random(20, 181);
    // ปริมาณแก็ส (PPM)
    int randNumber_PPM3 = random(0, 151);
    // ค่าปิดเปิดเสียงกริ่ง (ปิด = 0, เปิด = 1)
    int randNumber_OnOff3;
    if (randNumber_Temp3 < 150 && randNumber_PPM3 < 130){
      randNumber_OnOff3 = 0;
    }
    else {
      randNumber_OnOff3 = 1;
    }

    // ส่งและรับค่า temperature1
    Serial.printf("Set int temperature1... %s\n", Firebase.setInt(fbdo, "/Set1/temperature1", randNumber_Temp1) ? "ok" : fbdo.errorReason().c_str());
    Serial.printf("Get int temperature1... %s\n", Firebase.getInt(fbdo, "/Set1/temperature1") ? String(fbdo.to<int>()).c_str() : fbdo.errorReason().c_str());
    int iVal = 0;
    Serial.printf("Get int temperature1 ref... %s\n", Firebase.getInt(fbdo, "//Set1/temperature1", &iVal) ? String(iVal).c_str() : fbdo.errorReason().c_str());
    Serial.printf("Push int temperature1... %s\n", Firebase.pushInt(fbdo, "/Push1/temperature1", randNumber_Temp1) ? "ok" : fbdo.errorReason().c_str());

    // ส่งและรับค่า PPM1
    Serial.printf("Set int PPM1... %s\n", Firebase.setInt(fbdo, "/Set1/PPM1", randNumber_PPM1) ? "ok" : fbdo.errorReason().c_str());
    Serial.printf("Get int PPM1... %s\n", Firebase.getInt(fbdo, "/Set1/PPM1") ? String(fbdo.to<int>()).c_str() : fbdo.errorReason().c_str());
    int iVal_2 = 0;
    Serial.printf("Get int PPM1 ref... %s\n", Firebase.getInt(fbdo, "//Set1/PPM1", &iVal_2) ? String(iVal_2).c_str() : fbdo.errorReason().c_str());
    Serial.printf("Push int PPM1... %s\n", Firebase.pushInt(fbdo, "/Push1/PPM1", randNumber_PPM1) ? "ok" : fbdo.errorReason().c_str());

    // ส่งและรับค่า OnOff1
    Serial.printf("Set int OnOff1... %s\n", Firebase.setInt(fbdo, "/Set1/OnOff1", randNumber_OnOff1) ? "ok" : fbdo.errorReason().c_str());
    Serial.printf("Get int OnOff1... %s\n", Firebase.getInt(fbdo, "/Set1/OnOff1") ? String(fbdo.to<int>()).c_str() : fbdo.errorReason().c_str());
    int iVal_1 = 0;
    Serial.printf("Get int OnOff1 ref... %s\n", Firebase.getInt(fbdo, "//Set1/OnOff", &iVal_1) ? String(iVal_1).c_str() : fbdo.errorReason().c_str());
    Serial.printf("Push int OnOff1... %s\n", Firebase.pushInt(fbdo, "/Push1/OnOff", randNumber_OnOff1) ? "ok" : fbdo.errorReason().c_str());

    // สำหรับรับค่าเวลา
    epochTime = getTime();
    Serial.print("Epoch Time: ");
    Serial.println(epochTime);
    Serial.printf("Set int Epoch Time... %s\n", Firebase.setInt(fbdo, "/Set1/EpochTime", epochTime) ? "ok" : fbdo.errorReason().c_str());
    Serial.printf("Push int Epoch Time... %s\n", Firebase.pushInt(fbdo, "/Push1/EpochTime", epochTime) ? "ok" : fbdo.errorReason().c_str());










    // ส่งและรับค่า temperature2
    Serial.printf("Set2 int temperature2... %s\n", Firebase.setInt(fbdo, "/Set2/temperature2", randNumber_Temp2) ? "ok" : fbdo.errorReason().c_str());
    Serial.printf("Get2 int temperature2... %s\n", Firebase.getInt(fbdo, "/Set2/temperature2") ? String(fbdo.to<int>()).c_str() : fbdo.errorReason().c_str());
    Serial.printf("Get2 int temperature2 ref... %s\n", Firebase.getInt(fbdo, "//Set2/temperature2", &iVal) ? String(iVal).c_str() : fbdo.errorReason().c_str());
    Serial.printf("Push2 int temperature2... %s\n", Firebase.pushInt(fbdo, "/Push2/temperature2", randNumber_Temp2) ? "ok" : fbdo.errorReason().c_str());

    // ส่งและรับค่า PPM2
    Serial.printf("Set2 int PPM2... %s\n", Firebase.setInt(fbdo, "/Set2/PPM2", randNumber_PPM2) ? "ok" : fbdo.errorReason().c_str());
    Serial.printf("Get2 int PPM2... %s\n", Firebase.getInt(fbdo, "/Set2/PPM2") ? String(fbdo.to<int>()).c_str() : fbdo.errorReason().c_str());
    Serial.printf("Get2 int PPM2 ref2... %s\n", Firebase.getInt(fbdo, "//Set2/PPM2", &iVal_2) ? String(iVal_2).c_str() : fbdo.errorReason().c_str());
    Serial.printf("Push2 int PPM2... %s\n", Firebase.pushInt(fbdo, "/Push2/PPM2", randNumber_PPM2) ? "ok" : fbdo.errorReason().c_str());

    // ส่งและรับค่า OnOff2
    Serial.printf("Set2 int OnOff2... %s\n", Firebase.setInt(fbdo, "/Set2/OnOff2", randNumber_OnOff2) ? "ok" : fbdo.errorReason().c_str());
    Serial.printf("Get2 int OnOff2... %s\n", Firebase.getInt(fbdo, "/Set2/OnOff2") ? String(fbdo.to<int>()).c_str() : fbdo.errorReason().c_str());
    Serial.printf("Get2 int OnOff2 ref... %s\n", Firebase.getInt(fbdo, "//Set2/OnOff2", &iVal_1) ? String(iVal_1).c_str() : fbdo.errorReason().c_str());
    Serial.printf("Push2 int OnOff2... %s\n", Firebase.pushInt(fbdo, "/Push2/OnOff2", randNumber_OnOff2) ? "ok" : fbdo.errorReason().c_str());

    
    // สำหรับรับค่าเวลา
    epochTime = getTime();
    Serial.print("Epoch Time 2: ");
    Serial.println(epochTime);
    Serial.printf("Set2 int Epoch Time... %s\n", Firebase.setInt(fbdo, "/Set2/EpochTime", epochTime) ? "ok" : fbdo.errorReason().c_str());
    Serial.printf("Push2 int Epoch Time... %s\n", Firebase.pushInt(fbdo, "/Push2/EpochTime", epochTime) ? "ok" : fbdo.errorReason().c_str());




    // ส่งและรับค่า temperature3
    Serial.printf("Set3 int temperature3... %s\n", Firebase.setInt(fbdo, "/Set3/temperature3", randNumber_Temp3) ? "ok" : fbdo.errorReason().c_str());
    Serial.printf("Get3 int temperature3... %s\n", Firebase.getInt(fbdo, "/Set3/temperature3") ? String(fbdo.to<int>()).c_str() : fbdo.errorReason().c_str());
    Serial.printf("Get3 int temperature3 ref... %s\n", Firebase.getInt(fbdo, "//Set3/temperature3", &iVal) ? String(iVal).c_str() : fbdo.errorReason().c_str());
    Serial.printf("Push3 int temperature3... %s\n", Firebase.pushInt(fbdo, "/Push3/temperature3", randNumber_Temp3) ? "ok" : fbdo.errorReason().c_str());

    // ส่งและรับค่า PPM3
    Serial.printf("Set3 int PPM3... %s\n", Firebase.setInt(fbdo, "/Set3/PPM3", randNumber_PPM3) ? "ok" : fbdo.errorReason().c_str());
    Serial.printf("Get3 int PPM3... %s\n", Firebase.getInt(fbdo, "/Set3/PPM3") ? String(fbdo.to<int>()).c_str() : fbdo.errorReason().c_str());
    Serial.printf("Get3 int PPM3 ref2... %s\n", Firebase.getInt(fbdo, "//Set3/PPM3", &iVal_2) ? String(iVal_2).c_str() : fbdo.errorReason().c_str());
    Serial.printf("Push3 int PPM3... %s\n", Firebase.pushInt(fbdo, "/Push3/PPM3", randNumber_PPM3) ? "ok" : fbdo.errorReason().c_str());

    // ส่งและรับค่า OnOff3
    Serial.printf("Set3 int OnOff3... %s\n", Firebase.setInt(fbdo, "/Set3/OnOff3", randNumber_OnOff3) ? "ok" : fbdo.errorReason().c_str());
    Serial.printf("Get3 int OnOff3... %s\n", Firebase.getInt(fbdo, "/Set3/OnOff3") ? String(fbdo.to<int>()).c_str() : fbdo.errorReason().c_str());
    Serial.printf("Get3 int OnOff3 ref... %s\n", Firebase.getInt(fbdo, "//Set3/OnOff3", &iVal_1) ? String(iVal_1).c_str() : fbdo.errorReason().c_str());
    Serial.printf("Push3 int OnOff3... %s\n", Firebase.pushInt(fbdo, "/Push3/OnOff3", randNumber_OnOff3) ? "ok" : fbdo.errorReason().c_str());

    
    // สำหรับรับค่าเวลา
    epochTime = getTime();
    Serial.print("Epoch Time 3: ");
    Serial.println(epochTime);
    Serial.printf("Set3 int Epoch Time... %s\n", Firebase.setInt(fbdo, "/Set3/EpochTime", epochTime) ? "ok" : fbdo.errorReason().c_str());
    Serial.printf("Push3 int Epoch Time... %s\n", Firebase.pushInt(fbdo, "/Push3/EpochTime", epochTime) ? "ok" : fbdo.errorReason().c_str());




    Serial.println();

    //For generic set/get functions.

    //For generic set, use Firebase.set(fbdo, <path>, <any variable or value>)

    //For generic get, use Firebase.get(fbdo, <path>).
    //And check its type with fbdo.dataType() or fbdo.dataTypeEnum() and
    //cast the value from it e.g. fbdo.to<int>(), fbdo.to<std::string>().

    //The function, fbdo.dataType() returns types String e.g. string, boolean,
    //int, float, double, json, array, blob, file and null.

    //The function, fbdo.dataTypeEnum() returns type enum (number) e.g. fb_esp_rtdb_data_type_null (1),
    //fb_esp_rtdb_data_type_integer, fb_esp_rtdb_data_type_float, fb_esp_rtdb_data_type_double,
    //fb_esp_rtdb_data_type_boolean, fb_esp_rtdb_data_type_string, fb_esp_rtdb_data_type_json,
    //fb_esp_rtdb_data_type_array, fb_esp_rtdb_data_type_blob, and fb_esp_rtdb_data_type_file (10)

    count++;
  }
}
