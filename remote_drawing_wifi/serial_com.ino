// This file contains the code to communicate with the "UX" Arduino

#include <stdarg.h>
#include "serial_com.h"
#include "pins.h"

void serialInit() {
  Serial1.begin(115200, SERIAL_8E1);

  // Used to trigger serial reception
  pinMode(WIFI_ARDUINO_INTERRUPT_PIN, INPUT);

  // Leave some time for the UX Arduino to start up before sending serial data
  delay(5000);

  sendStatusMessageFormat("Hello received from Wifi Arduino. I am client %d.", myClientId);
  delay(1000);

  // Clear any remaining displayed drawing from previous run.
  serialTransmitClear();
}

void sendStatusMessage(const char *msg) {
  Serial1.write(SERIAL_COM_MSG_OPCODE);
  Serial1.write((byte *) msg, strlen(msg) + 1);

  Serial.print("MSG: ");
  Serial.println(msg);
}

void sendStatusMessageFormat(const char *format, ...) {
  char buf[MAX_STATUS_MESSAGE_BUFFER_SIZE];
  va_list args;
  va_start(args, format);
  vsnprintf(buf, MAX_STATUS_MESSAGE_BUFFER_SIZE, format, args);
  sendStatusMessage(buf);
  va_end(args);
}

// Report fatal error on status bar and reboot. This function never returns.
void fatalError(const char *format, ...) {
  char buf[MAX_STATUS_MESSAGE_BUFFER_SIZE];
  char bufFinal[MAX_STATUS_MESSAGE_BUFFER_SIZE];
  va_list args;
  va_start(args, format);
  vsnprintf(buf, MAX_STATUS_MESSAGE_BUFFER_SIZE, format, args);
  for (int i=60; i>0; i--) {
    snprintf(bufFinal, MAX_STATUS_MESSAGE_BUFFER_SIZE, "%s - Rebooting in %d seconds...", buf, i);
    sendStatusMessage(bufFinal);
    delay(1000);
  }
  reboot();
  va_end(args);
}

void serialTransmitLine(Line line) {
  Serial1.write(SERIAL_COM_LINE_OPCODE);
  Serial1.write((byte*) &line, sizeof(Line));
}

int serialReceiveLine(Line *line) {
  if (Serial1.readBytes((byte*) line, sizeof(Line)) == sizeof(Line)) {
    return 1;
  } else {
    return 0;
  }
}

int serialReceiveOpCode() {
  int opcode = Serial1.read();
  return opcode;
}

void serialTransmitClear() {
  Serial1.write(SERIAL_COM_CLEAR_OPCODE);
}
