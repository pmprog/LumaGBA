
#include "completion.h"

const uint8_t completion_tmx_completebkg_width = 30;
const uint8_t completion_tmx_completebkg_height = 20;
const uint16_t completion_tmx_completebkg_data[] = {
 0x0004, 0x0005, 0x0010, 0x0011, 0x0010, 0x0011, 0x0010, 0x0011, 0x0010, 0x0011, 0x0010, 0x0011, 0x0010, 0x0011, 0x0010, 0x0011, 0x0010, 0x0011, 0x0010, 0x0011, 0x0010, 0x0011, 0x0010, 0x0011, 0x0010, 0x0011, 0x0010, 0x0011, 0x0004, 0x0005,
 0x0006, 0x0007, 0x00B4, 0x00B5, 0x0012, 0x0013, 0x0004, 0x0005, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0004, 0x0005, 0x0012, 0x0013, 0x00B4, 0x00B5, 0x0006, 0x0007,
 0x0008, 0x0000, 0x00B6, 0x00B7, 0x009C, 0x009D, 0x0006, 0x0007, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0006, 0x0007, 0x009C, 0x009D, 0x00B6, 0x00B7, 0x0000, 0x0009,
 0x000A, 0x0000, 0x0000, 0x0000, 0x009E, 0x009F, 0x0084, 0x0085, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0084, 0x0085, 0x009E, 0x009F, 0x0000, 0x0000, 0x0000, 0x000B,
 0x0008, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0086, 0x0087, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0086, 0x0087, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0009,
 0x000A, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x000B,
 0x0008, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0009,
 0x000A, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x000B,
 0x0008, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0009,
 0x000A, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x000B,
 0x0008, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0009,
 0x000A, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x000B,
 0x0008, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0009,
 0x000A, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x000B,
 0x00BC, 0x00BD, 0x0014, 0x0015, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0018, 0x0019, 0x00B8, 0x00B9,
 0x00BE, 0x00BF, 0x0016, 0x0017, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x001A, 0x001B, 0x00BA, 0x00BB,
 0x001C, 0x001D, 0x00A4, 0x00A5, 0x0014, 0x0015, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0018, 0x0019, 0x00A0, 0x00A1, 0x001C, 0x001D,
 0x001E, 0x001F, 0x00A6, 0x00A7, 0x0016, 0x0017, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x001A, 0x001B, 0x00A2, 0x00A3, 0x001E, 0x001F,
 0x008C, 0x008D, 0x0000, 0x0000, 0x0000, 0x0000, 0x0014, 0x0015, 0x0004, 0x0005, 0x0004, 0x0005, 0x0004, 0x0005, 0x0004, 0x0005, 0x0004, 0x0005, 0x0004, 0x0005, 0x0004, 0x0005, 0x0018, 0x0019, 0x0000, 0x0000, 0x0000, 0x0000, 0x0088, 0x0089,
 0x008E, 0x008F, 0x0000, 0x0000, 0x0000, 0x0000, 0x0016, 0x0017, 0x0006, 0x0007, 0x0006, 0x0007, 0x0006, 0x0007, 0x0006, 0x0007, 0x0006, 0x0007, 0x0006, 0x0007, 0x0006, 0x0007, 0x001A, 0x001B, 0x0000, 0x0000, 0x0000, 0x0000, 0x008A, 0x008B,
};

const uint8_t completion_tmx_completemid_width = 30;
const uint8_t completion_tmx_completemid_height = 20;
const uint16_t completion_tmx_completemid_data[] = {
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
};

const uint8_t completion_tmx_completeupr_width = 30;
const uint8_t completion_tmx_completeupr_height = 20;
const uint16_t completion_tmx_completeupr_data[] = {
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x013E, 0x013E, 0x013E, 0x013E, 0x013E, 0x013E, 0x013E, 0x013E, 0x013E, 0x013E, 0x013E, 0x013E, 0x013E, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x00C4, 0x00C4, 0x00C4, 0x00C4, 0x00C4, 0x00C4, 0x00C4, 0x00C4, 0x00C4, 0x00C4, 0x00C4, 0x00C4, 0x00C4, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x01BF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0139, 0x0139, 0x0139, 0x0139, 0x0139, 0x0139, 0x0139, 0x0139, 0x0139, 0x0139, 0x0139, 0x0139, 0x0139, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x01BF, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x01BE, 0x0000, 0x01B5, 0x0000, 0x0000, 0x0000, 0x013A, 0x013A, 0x013A, 0x013A, 0x013A, 0x013A, 0x013A, 0x013A, 0x013A, 0x013A, 0x013A, 0x013A, 0x013A, 0x0000, 0x0000, 0x0000, 0x01B5, 0x0000, 0x01BE, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x01BE, 0x0000, 0x01B4, 0x0000, 0x01C9, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x01C9, 0x0000, 0x01B4, 0x0000, 0x01BE, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x01BE, 0x0000, 0x01B4, 0x0000, 0x01C8, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x01C8, 0x0000, 0x01B4, 0x0000, 0x01BE, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x01BE, 0x0000, 0x01B4, 0x0000, 0x01C8, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x01C8, 0x0000, 0x01B4, 0x0000, 0x01BE, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x01BE, 0x0000, 0x01B4, 0x0000, 0x01C8, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x01C8, 0x0000, 0x01B4, 0x0000, 0x01BE, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x01BE, 0x0000, 0x01B4, 0x0000, 0x01C8, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x01C8, 0x0000, 0x01B4, 0x0000, 0x01BE, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x01BE, 0x0000, 0x01B4, 0x0000, 0x01C8, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x01C8, 0x0000, 0x01B4, 0x0000, 0x01BE, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x01BE, 0x0000, 0x01B4, 0x0000, 0x01C8, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x01C8, 0x0000, 0x01B4, 0x0000, 0x01BE, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x01BE, 0x0000, 0x01B4, 0x0000, 0x01C8, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x01C8, 0x0000, 0x01B4, 0x0000, 0x01BE, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x01BE, 0x0000, 0x01B4, 0x0000, 0x01C8, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x01C8, 0x0000, 0x01B4, 0x0000, 0x01BE, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x01BE, 0x0000, 0x01B4, 0x0000, 0x01C8, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x01C8, 0x0000, 0x01B4, 0x0000, 0x01BE, 0x0000, 0x0000,
 0x0000, 0x0000, 0x01BA, 0x01C1, 0x0000, 0x01B4, 0x0000, 0x01C8, 0x0000, 0x013B, 0x013B, 0x013B, 0x013B, 0x013B, 0x013B, 0x013B, 0x013B, 0x013B, 0x013B, 0x013B, 0x013B, 0x013B, 0x0000, 0x01C8, 0x0000, 0x01B4, 0x0000, 0x01C0, 0x01BC, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x01B4, 0x0000, 0x01C8, 0x0000, 0x013C, 0x013C, 0x013C, 0x013C, 0x013C, 0x013C, 0x013C, 0x013C, 0x013C, 0x013C, 0x013C, 0x013C, 0x013C, 0x0000, 0x01C8, 0x0000, 0x01B4, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x01B0, 0x01B7, 0x0000, 0x01C8, 0x0000, 0x00C4, 0x00C4, 0x00C4, 0x00C4, 0x00C4, 0x00C4, 0x00C4, 0x00C4, 0x00C4, 0x00C4, 0x00C4, 0x00C4, 0x00C4, 0x0000, 0x01C8, 0x0000, 0x01B6, 0x01B2, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x01C8, 0x0000, 0x013D, 0x013D, 0x013D, 0x013D, 0x013D, 0x013D, 0x013D, 0x013D, 0x013D, 0x013D, 0x013D, 0x013D, 0x013D, 0x0000, 0x01C8, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x01C4, 0x01C5, 0x01C5, 0x01C5, 0x01C5, 0x01CB, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x01CA, 0x01C5, 0x01C5, 0x01C5, 0x01C5, 0x01C6, 0x0000,
};
