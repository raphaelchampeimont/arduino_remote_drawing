#ifndef SERIAL_COM_H
#define SERIAL_COM_H

#define SERIAL_COM_LINE_OPCODE 'L'
#define SERIAL_COM_MSG_OPCODE 'M'
#define SERIAL_COM_CLEAR_OPCODE 'C'
#define SERIAL_COM_ALIVE_OPCODE 'A'

// The maximum number of characters in a status message (not including the \0)
// We can display exactly 100 characters on one line on the screen
#define MAX_STATUS_MESSAGE_LENGTH 100

// Each status message is divided in several packets
#define STATUS_MESSAGE_SIZE_IN_PACKET 10

typedef struct {
  int x0;
  int y0;
  int x1;
  int y1;
  byte color; // an index in the COLORS constant array
} Line;

typedef struct {
  byte offset;
  byte part[STATUS_MESSAGE_SIZE_IN_PACKET];
} StatusMessagePartInPacket;

// Sent packets (to UX Arduino) can contain status message, unlike received packets.
typedef union {
  Line line;
} DataInReceivedPacket;

typedef union {
  Line line;
  StatusMessagePartInPacket statusMessage;
} DataInSentPacket;

typedef struct {
  byte opcode;
  DataInReceivedPacket data;
} ReceivedPacket;

typedef struct {
  byte opcode;
  DataInSentPacket data;
} SentPacket;

// Inits the serial communication with the UX Arduino
void serialInit();

// Sends a message to the UX Arduino, meant to be displayed on status bar
void sendStatusMessage(const char *msg);

// Same as sendStatusMessage() but arguments as printf()
void sendStatusMessageFormat(const char *format, ...);

// Transmit line to the UX Arduino to display it
void serialTransmitLine(Line line);

// Tell the UX Arduino to clear the screen
void serialTransmitClear();

// Receive a packet from the UX Arduino
int serialReceivePacket(ReceivedPacket *packetAddr);

// Clear drawing
void serialTransmitClear();

// Tell the other Arduino that we are alive
void serialTransmitAlive();

#endif
