#include "SimpleModbusSlave.h"

#define DE_RE_PIN 5
short slaveAddress = 1;


//////////////// registers of your slave ///////////////////
enum 
{     
  // just add or remove registers and your good to go...
  // The first register starts at address 0
  ADC0,     
  ADC1, 
  ADC2,  
  ADC3,  
  // leave this one
  TOTAL_REGS_SIZE 
  // total number of registers for function 3 and 16 share the same register array
};

unsigned int holdingRegs[TOTAL_REGS_SIZE]; // function 3 and 16 register array
////////////////////////////////////////////////////////////

void ModbusSetup()
{
  /* parameters(long baudrate, 
                unsigned char ID, 
                unsigned char transmit enable pin, 
                unsigned int holding registers size,
                unsigned char low latency)
                
     The transmit enable pin is used in half duplex communication to activate a MAX485 or similar
     to deactivate this mode use any value < 2 because 0 & 1 is reserved for Rx & Tx.
     Low latency delays makes the implementation non-standard
     but practically it works with all major modbus master implementations.
  */
  
  modbus_configure(9600, slaveAddress, DE_RE_PIN, TOTAL_REGS_SIZE, 0);
 
}

void ModbusLoop()
{
    // modbus_update() is the only method used in loop(). It returns the total error
  
    

    if (EncoderTicks >= 0) {
      holdingRegs[0] = 1;
    } 
    else {
      holdingRegs[0] = 0;
    }
  
    long ValueLong = abs(distance);

    int16_t HighINT = (ValueLong >> 16) & 0x0000ffffl;
    int16_t LowINT  = ValueLong & 0x0000ffffl;

    // how to come back
    //newlong = ((long)H << 16) | L;
    
    holdingRegs[1] = LowINT;  
    holdingRegs[2] = HighINT;  

    // reset register if it is 1 reset encoder ticks and set register back to 0
    if (holdingRegs[3] == 1) {
      EncoderTicks=0;
      holdingRegs[3]=0;  
    }
    
    
    modbus_update(holdingRegs);
   
}
