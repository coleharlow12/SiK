#include <stdint.h>
#include "serial.h"

//These macros are used for the Mavlink protocol. They are used by the receiving end
//To determine the start of a new message and what information the data is holding. 
#define MAGIC_NUMBER 0xFE
#define MAVLINK_RSSI_ID 69
#define MAVLINK_RSSI_LENGTH 1

//These defines are used to create Macros which are used at the receiving end to 
//determine where the RSSI value is coming from. 
#define RADIO_MODEM 21
#define RIGHT_ANTENNA 1
#define LEFT_ANTENNA 2

/*
*The purpose of this function is to write a mavlink message across the UART serial port

* @param sysID	 ID of the sending system (in this case I consider each modem a system)
* @param compID	 ID of the component (in this case I condier each antenna a component)
* @param RSSI 	 returned signal strength indicator (RSSI)
*/
void writeRSSI_MAVLINK(uint8_t sysID, uint8_t compID, register uint8_t RSSI);