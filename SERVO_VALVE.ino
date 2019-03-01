#include <Servo.h>

Servo serwo;
int opened=90;				//Default open angle
int closed=0;				//Default close angle
bool humidity_sensor=0;		//If humidity sensor is installed switch to 1;

int valve_position;

unsigned long actual_time;
unsigned long old_time;
unsigned long open_time;
unsigned long close_time;

void setup() {
  Serial.begin(9600);

  actual_time = millis();
  old_time=actual_time;
  serwo.attach(9);
  valve_position=closed;
  serwo.write(valve_position);
}

void loop() {
  actual_time=millis();
  if(actual_time < old_time){old_time=actual_time;} //Anti overflow feature
  
  if(humidity_sensor){Serial.println("Czujka WIP");}
 // else{config_valve();}
  set_valve();
}


//Rotating valve to set valve_position for set time;
void set_valve(){
  if(actual_time-old_time >= close_time && valve_position==closed){
    config_valve();
    old_time=actual_time;
    valve_position=opened;
	  Serial.print("Czas otwarcia: ");
	  Serial.println(open_time);
    Serial.println(opened);
  }
  if(actual_time-old_time >= open_time && valve_position==opened){
     config_valve();
     valve_position=closed;
     old_time=actual_time;
     Serial.print("Czas zamkniecia: ");
	   Serial.println(close_time);
    }
  serwo.write(valve_position);
}


//Setting valve valve_position and open/close time if no humidity sensor is present;
void config_valve(){
  open_time = map(analogRead(A5),0,1023,1000,50000);
  close_time = map(analogRead(A4),0,1023,1000,50000);
  opened = map(analogRead(A3),0,1023,0,180);
}


//Setting valve valve_position when and open/close condition when humidity sensor is present;
void read_sensor(){
    
}
