#define actuator_a 5

void setup() 
{
  // put your setup code here, to run once:
  pinMode(actuator_a, OUTPUT);
//  analogWrite(actuator_a, 255);
  analogWrite(actuator_a, 30);//for 2.5mA safe
  //serial connection Baud rate 9600
  Serial.begin(9600);
}

void loop() 
{
  // put your main code here, to run repeatedly:
  if (Serial.available()){
    char select_actuator = Serial.read();
    int voltage_rate = Serial.parseInt();
    write_voltage(select_actuator, voltage_rate);
    }
}

void write_voltage(char actuator, int rate)
{
  //data format "a%1"
  if (actuator == 'a'){
      printf("The pressure rate is:%d \n", rate);
//      analogWrite(actuator_a, 255 - rate);
      analogWrite(actuator_a, rate);
      return;
    }
    
  else
    printf("No actuator selected!\n");
    
  return;
}
