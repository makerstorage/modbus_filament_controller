#include "SimpleModbusSlave.h"

//////////////// registers of your slave ///////////////////
enum 
{     
  // just add or remove registers and your good to go...
  // The first register starts at address 0
  ADC0,     
  ADC1,        
  // leave this one
  TOTAL_REGS_SIZE 
  // total number of registers for function 3 and 16 share the same register array
};

unsigned int holdingRegs[TOTAL_REGS_SIZE]; // function 3 and 16 register array
////////////////////////////////////////////////////////////

void setup()
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
  
  modbus_configure(9600, 1, 5, TOTAL_REGS_SIZE, 0);
 
}

void loop()
{
    // modbus_update() is the only method used in loop(). It returns the total error
  
    modbus_update(holdingRegs);
  
    holdingRegs[0] = 1;
    holdingRegs[1] = 122;
    
}
