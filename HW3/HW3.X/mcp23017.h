
#ifndef MCP23017_H    /* Guard against multiple inclusion */
#define MCP23017_H


//Address of MCP23017 with A0-A2 grounded
#define MCP23017_HIGH 0x40
#define A0 0 
#define A1 0
#define A2 0
#define MCP23017_ADDRESS (MCP23017_HIGH | A2<<3 | A1<<2 | A0 << 1)


//Interleaved SFR Addresses
#define IODIRA      0x00
#define IODIRB      0x01
#define IPOLA       0x02
#define IPOLB       0x03
#define GPINTENA    0x04
#define GPINTENB    0x05
#define DEFVALA     0x06
#define DEFVALB     0x07
#define INTCONA     0x08
#define INTCONB     0x09
#define IOCON_A     0x0A
#define IOCON_B     0x0B
#define GPPUA       0x0C
#define GPPUB       0x0D
#define INTFA       0x0E
#define INTFB       0x0F
#define INTCAPA     0x10
#define INTCAPB     0x11
#define GPIOA       0x12
#define GPIOB       0x13
#define OLATA       0x14
#define OLATB       0x15

//Define bank variables
#define BANK_A 0
#define BANK_B 1

void mcp23017Init(void);
void writeMCP23017(unsigned char address, unsigned char reg, unsigned char value);
unsigned char readMCP23017(unsigned char address, unsigned char reg);
int readGPIO(int gpio, int bank);
void writeGPIO(int gpio, int bank, int level);

#endif /* MCP23017_H */

/* *****************************************************************************
 End of File
 */
