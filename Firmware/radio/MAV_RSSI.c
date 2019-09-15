#include "MAV_RSSI.h"
#include "crc.h"

//Note there are multiple data types used in this 
__xdata uint8_t RSSI_Mavlink[9];

void writeRSSI_MAVLINK(uint8_t sysID, uint8_t compID, register uint8_t RSSI)
{
    //This is used to keep track of lost packets
    static __pdata uint8_t sequenceNum = 0;

    __pdata uint16_t crc;
    //This is the magic number that signifies the start of a mavlink message
    RSSI_Mavlink[0] = MAGIC_NUMBER;
    //payload length
    RSSI_Mavlink[1] = MAVLINK_RSSI_LENGTH;
    //This is the sequence number it just counts up for error tracking
    RSSI_Mavlink[2] = sequenceNum;
    //This is the system ID
    RSSI_Mavlink[3] = sysID;
    //This is the component ID
    RSSI_Mavlink[4] = compID;
    //This is the ID of the Mavlink message
    RSSI_Mavlink[5] = MAVLINK_RSSI_ID;
    //This is the RSSI value we are interested in
    RSSI_Mavlink[6] = RSSI;
    //This should make the checksum equal to 269 in uint16_t form
    crc = crc16(7, RSSI_Mavlink);
    //This sends the calculated CRC for the data. 
    RSSI_Mavlink[7] = (uint8_t)(crc);
    RSSI_Mavlink[8] = (uint8_t)(crc >> 8);

    ++sequenceNum;

    serial_write_buf(RSSI_Mavlink,9);

    return;
}
