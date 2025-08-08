#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <SPIFFS.h>

const char* ssid = "ESP32-Web";
const char* password = "12345678";

WebServer server(80);

void handleFileUpload() {
  HTTPUpload& upload = server.upload();
  if (upload.status == UPLOAD_FILE_START) {
    Serial.printf("UploadStart: %s\n", upload.filename.c_str());
    String path = "/" + upload.filename;
    fs::File file = SPIFFS.open(path, FILE_WRITE);
    if (!file) return;
    file.close();
  } else if (upload.status == UPLOAD_FILE_WRITE) {
    String path = "/" + upload.filename;
    fs::File file = SPIFFS.open(path, FILE_APPEND);
    if (file) file.write(upload.buf, upload.currentSize);
    file.close();
  } else if (upload.status == UPLOAD_FILE_END) {
    Serial.printf("UploadEnd: %s (%u)\n", upload.filename.c_str(), upload.totalSize);
  }
}

void listFiles() {
  String output = "<h1>Files:</h1><ul>";
  File root = SPIFFS.open("/");
  File file = root.openNextFile();
  while (file) {
    output += "<li><a href=\"/" + String(file.name()) + "\">" + String(file.name()) + "</a></li>";
    file = root.openNextFile();
  }
  output += "</ul><form method='POST' action='/upload' enctype='multipart/form-data'>";
  output += "<input type='file' name='upload'><input type='submit' value='Upload'></form>";
  server.send(200, "text/html", output);
}

void setup() {
  Serial.begin(115200);
  WiFi.softAP(ssid, password);
  Serial.println("WiFi started. IP: " + WiFi.softAPIP().toString());

  if (!SPIFFS.begin(true)) {
    Serial.println("SPIFFS Mount Failed");
    return;
  }

  server.on("/", HTTP_GET, listFiles);
  server.on("/upload", HTTP_POST, []() {
    server.send(200);
  }, handleFileUpload);
  server.serveStatic("/", SPIFFS, "/");

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}
