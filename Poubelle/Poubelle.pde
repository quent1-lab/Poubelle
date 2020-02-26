import processing.serial.*;

Com myCom;
Serial Port;

void setup() {
  fullScreen();
  X = width / 640.0;
  Y = height / 360.0;
  
  myCom = new Com();
  
  smooth();
  textAlign(LEFT, CENTER);
  frameRate(60);
  printArray(Serial.list()); 
  Port = new Serial(this, Serial.list()[0], 9600);
}


void draw() {
  scale(X, Y);
  Shape();
  myCom.Read();
  myCom.Write();
}
