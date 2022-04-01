#include "Arduino.h"
#include "L298N_Gaby.h"

// construction of dual motor for ESP32
L298N_Gaby::L298N_Gaby(int IN1,int IN2,int ENA, int CHA, int IN3, int IN4,int ENB, int CHB)

{
#if defined(ARDUINO_ARCH_ESP32)	
  ledcSetup(CHA, this->_frequency, this->_resulotion);
  ledcAttachPin(ENA, CHA);
  
  ledcSetup(CHB, this->_frequency, this->_resulotion);
  ledcAttachPin(ENB, CHB);  
  
  _chA = CHA;  
  _chB = CHB;
#endif  	
    // -- pin settings
   _in1=IN1;
   _in2=IN2;
   _enA=CHA;
   _in3=IN3;
   _in4=IN4;
   _enB=CHB;
   if( IN3 && IN4  && ENB)
   _dual = true;      
 
}

void L298N_Gaby::begin()
{
#if defined(ARDUINO_ARCH_ESP32)	
	pinMode(this->_in1, OUTPUT);
	pinMode(this->_in2, OUTPUT);

	if(this->_debug)
	{
				Serial.println("L298N_Gaby Motor Library");				
	}
  
      if(this->_dual)
	  {
		pinMode(this->_in3, OUTPUT);
		pinMode(this->_in4, OUTPUT);

			if(this->_debug)
			{				
				Serial.println("Dual Motor Demo");
			}		
		  
	  }else{
			if(this->_debug)
			{				
				Serial.println("Single Motor Demo");
			}		  
	  }	
   
#else
	pinMode(this->_in1, OUTPUT);
	pinMode(this->_in2, OUTPUT);
	pinMode(this->_enA, OUTPUT);	
	if(this->_debug)
	{
				Serial.println("L298N_Gaby Motor Library");				
	}
  
      if(this->_dual)
	  {
		pinMode(this->_in3, OUTPUT);
		pinMode(this->_in4, OUTPUT);
		pinMode(this->_enB, OUTPUT);
			if(this->_debug)
			{				
				Serial.println("Dual Motor Demo");
			}		
		  
	  }else{
			if(this->_debug)
			{				
				Serial.println("Single Motor Demo");
			}		  
	  }	
#endif


}

void L298N_Gaby::rotate(int motor, int speed, int direktion) {

#if defined(ARDUINO_ARCH_ESP32)	
  uint32_t duty = (this->_bits / 255) * min(toPWM(speed), 255);

/* Serial.print("speed:");
   Serial.print (speed);  
   Serial.print(" duty:");
   Serial.print (duty); 
   Serial.print(" toPWM(speed)");
   Serial.println (toPWM(speed));    */ 
   
   
	if(direktion ==1){
		if(motor ==1)
		{
				digitalWrite(this->_enA, LOW);// see page 7 of datasheet. You must keep ENABLE pin low before applying changes to IN			
				digitalWrite(this->_in1, LOW);
				digitalWrite(this->_in2, HIGH);
			this->printDebug3(motor, this->_in1,LOW,this->_in2,HIGH, direktion, speed , duty);					
		}else{
				digitalWrite(this->_enB, LOW);// see page 7 of datasheet. You must keep ENABLE pin low before applying changes to IN				
				digitalWrite(this->_in3, LOW);
				digitalWrite(this->_in4, HIGH);	
			this->printDebug3(motor, this->_in3,LOW,this->_in4,HIGH, direktion, speed , duty);					
		}

		
	}else{
		if(motor ==1)
		{
				digitalWrite(this->_enA, LOW);// see page 7 of datasheet. You must keep ENABLE pin low before applying changes to IN				
				digitalWrite(this->_in1, HIGH);
				digitalWrite(this->_in2, LOW);
			this->printDebug3(motor, this->_in1,HIGH,this->_in2,LOW, direktion, speed, duty );					
		}else{
				digitalWrite(this->_enB, LOW);// see page 7 of datasheet. You must keep ENABLE pin low before applying changes to IN				
				digitalWrite(this->_in3, HIGH);
				digitalWrite(this->_in4, LOW);	
			this->printDebug3(motor, this->_in3,HIGH,this->_in4,LOW, direktion, speed, duty);					
		}

	}

    int enPin;
		if(motor ==1)
		{
			enPin= this->_enA;
		}else{
			enPin= this->_enB;
		}
#else
	if(direktion ==1){
		if(motor ==1)
		{
				digitalWrite(this->_enA, LOW);// see page 7 of datasheet. You must keep ENABLE pin low before applying changes to IN			
				digitalWrite(this->_in1, LOW);
				digitalWrite(this->_in2, HIGH);
			this->printDebug1(motor, this->_in1,LOW,this->_in2,HIGH, direktion, speed );					
		}else{
				digitalWrite(this->_enB, LOW);// see page 7 of datasheet. You must keep ENABLE pin low before applying changes to IN				
				digitalWrite(this->_in3, LOW);
				digitalWrite(this->_in4, HIGH);	
			this->printDebug1(motor, this->_in3,LOW,this->_in4,HIGH, direktion, speed );					
		}

		
	}else{
		if(motor ==1)
		{
				digitalWrite(this->_enA, LOW);// see page 7 of datasheet. You must keep ENABLE pin low before applying changes to IN				
				digitalWrite(this->_in1, HIGH);
				digitalWrite(this->_in2, LOW);
			this->printDebug1(motor, this->_in1,HIGH,this->_in2,LOW, direktion, speed );					
		}else{
				digitalWrite(this->_enB, LOW);// see page 7 of datasheet. You must keep ENABLE pin low before applying changes to IN				
				digitalWrite(this->_in3, HIGH);
				digitalWrite(this->_in4, LOW);	
			this->printDebug1(motor, this->_in3,HIGH,this->_in4,LOW, direktion, speed );					
		}

	}

    int enPin;
		if(motor ==1)
		{
			enPin= this->_enA;
		}else{
			enPin= this->_enB;
		}	
#endif	

    if(speed >=0 && speed <=100 ){
#if defined(ARDUINO_ARCH_ESP32)	
  // write duty to LEDC
  ledcWrite(enPin, duty);
  
      
#else
		analogWrite(enPin, toPWM(speed));
#endif		
	}else{
			if(this->_debug)
			{
				Serial.print("***** Speed speed must be between 0 and 100");
				
			}			
	}

 
}//rotate::rotate(int motor, int speed, int direktion) {
void L298N_Gaby::brake(int motor){
	if(motor ==3)
	{
		digitalWrite(this->_in3, LOW);
		digitalWrite(this->_in4, LOW);		
		digitalWrite(this->_in1, LOW);
		digitalWrite(this->_in2, LOW);
		digitalWrite(this->_enA, LOW);	
		digitalWrite(this->_enB, LOW);			
		
		if(this->_debug){
			Serial.println("All Motors Braked");
		}				
	}else if(motor ==2)
	{
		digitalWrite(this->_in3, LOW);
		digitalWrite(this->_in4, LOW);	
		digitalWrite(this->_enB, LOW);			
		if(this->_debug){
			Serial.println("Motor 2 Braked");
		}			
	}else{
		digitalWrite(this->_in1, LOW);
		digitalWrite(this->_in2, LOW);	
		digitalWrite(this->_enA, LOW);		
		if(this->_debug){
			Serial.println("Motor 1 Braked");
		}				
	}

}

int L298N_Gaby::toPWM(int v){