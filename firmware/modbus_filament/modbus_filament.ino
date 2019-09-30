const byte EncoderPinA = 3;
const byte EncoderPinB = 4;

long EncoderTicks = 0;
long distance = 0;

bool EncoderBSet;

#define EncoderIsReversed

void setup() {

  pinMode(EncoderPinA, INPUT_PULLUP);
  pinMode(EncoderPinB, INPUT_PULLUP);    
  
  attachInterrupt(digitalPinToInterrupt(EncoderPinA), encoder, RISING);
 // SerialUSB.begin(9600);

  ModbusSetup();
   
}

void loop() {

 // SerialUSB.println(EncoderTicks);  

  //int gearDiameter = 11; // diameter of the gear is 11 mm
  // circumtance = pi*11 = 34.558 mm
  //int encoderRes = 360; // one turn produce 360 encoder ticks
  // 34.558/360 = distance at 1 tick = 0.09599444
  distance =  EncoderTicks * 0.09599444;
  ModbusLoop();
 // delay(500);
  
 
}

void encoder() {
  // Test transition; since the interrupt will only fire on 'rising' we don't need to read pin A
  EncoderBSet = digitalRead_fast(EncoderPinB);   // read the input pin
 
  // and adjust counter + if A leads B
  #ifdef EncoderIsReversed
    EncoderTicks -= EncoderBSet ? -1 : +1;
  #else
    EncoderTicks += EncoderBSet ? -1 : +1;
  #endif
}
