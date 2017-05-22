#include <LiquidCrystal.h>

//Declare Serial Read variables
int CmdCount=1;
byte inData;
char inChar;
String BuildINString="";
String DisplayString="";
long DisplayValue;
String SentMessage="";
int ByteCount=0;
long A;
int B;
int C;
int WorkingVal;
String WorkingString="";
int RefreshCounter=0; // when the reading should refresh
int RefreshCounterMax=50; //Adjust this refreshrate
int RESETMenuName=0;

//MenuAnalogVal
int x;
//Declare Buttons
int MenuID=0;
int UpDownMenu=0;

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() 
{
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.setCursor(0, 0);
  Bootup(); //Simulate Bootup process doesnt have to be here this only makes it look cool
  Retry:
  lcd.setCursor(0, 0);
  lcd.print("Connecting......    ");
  lcd.setCursor(0, 1);
  lcd.print("                    ");
  Serial.begin(38400); 
  
  delay(500);
  //Send a test message to see if the ELM327 Chip is responding
  SentMessage = "ATI";
  Serial.println("ATI");delay(500);ReadData();
  if (BuildINString.substring(1,7)=="ELM327")
    {
      lcd.setCursor(0, 0);
      lcd.print("Welcome...            ");
      lcd.setCursor(0, 1);
      lcd.print("Connection OK         ");
      delay(1500);
      DisplayString="Reading Data...........";
    }
    else
    {
      lcd.setCursor(0, 0);
      lcd.print("Error             ");
      lcd.setCursor(0, 1);
      lcd.print("No Connection!         ");
      delay(1500);
      goto Retry;
    }
  SentMessage = "ATSP A3";
  Serial.println("ATSP A3");
  delay(1500);
}

void loop() 
{
RefreshCounter++;

x = analogRead (0);
//Serial.println(x);
lcd.setCursor(10,1);
if (x > 450 and x < 600){if (MenuID>0){MenuID--;}DisplayString="Reading Data...........";delay(250);} //Left
if (x > 300 and x < 400){if (UpDownMenu<3){UpDownMenu++;}delay(250);RESETMenuName=0;} //DOWN
if (x > 20 and x < 240){if (UpDownMenu>0){UpDownMenu--;}delay(250);RESETMenuName=0;} //UP
if (x > -10 and x < 10) {if (MenuID<13){MenuID++;}DisplayString="Reading Data...........";delay(250);} //Right

if (UpDownMenu==0)
{
  if(RESETMenuName==0){lcd.setCursor(0, 0);lcd.print("Economy          ");lcd.setCursor(0, 1);lcd.print("                      ");delay(2000);RESETMenuName=1;}
    lcd.setCursor(0,0);
    lcd.print(DisplayString);
    if (RefreshCounter==RefreshCounterMax)
    {
      SentMessage=="01 0C";
      Serial.println("01 0C");
      delay(50);
      ReadData();
      
      if (C >= 900)
        {
          lcd.setCursor(0,1);
          lcd.print("Change up a gear");
        }
        else
        {
          lcd.print(" ");
        }
     }
}

if (UpDownMenu==1)
{
  if(RESETMenuName==0){lcd.setCursor(0, 0);lcd.print("Engine Readings  ");lcd.setCursor(0, 1);lcd.print("                      ");delay(2000);RESETMenuName=1;}
  if (MenuID==0){lcd.setCursor(0, 0);lcd.print("01 RPM             ");lcd.setCursor(0, 1);lcd.print(DisplayString);if (RefreshCounter==RefreshCounterMax){SentMessage = "01 0C";Serial.println("01 0C");delay(50);ReadData();}}
  if (MenuID==1){lcd.setCursor(0, 0);lcd.print("02 IAT Temp        ");lcd.setCursor(0, 1);lcd.print(DisplayString);if (RefreshCounter==RefreshCounterMax){SentMessage = "01 0F";Serial.println("01 0F");delay(50);ReadData();}}
  if (MenuID==2){lcd.setCursor(0, 0);lcd.print("03 Ambient Temp    ");lcd.setCursor(0, 1);lcd.print(DisplayString);if (RefreshCounter==RefreshCounterMax){SentMessage = "01 46";Serial.println("01 46");delay(50);ReadData();}}
  if (MenuID==3){lcd.setCursor(0, 0);lcd.print("04 Throttle %      ");lcd.setCursor(0, 1);lcd.print(DisplayString);if (RefreshCounter==RefreshCounterMax){SentMessage = "01 11";Serial.println("01 11");delay(50);ReadData();}}
  if (MenuID==4){lcd.setCursor(0, 0);lcd.print("05 CAT 1 Temp      ");lcd.setCursor(0, 1);lcd.print(DisplayString);if (RefreshCounter==RefreshCounterMax){SentMessage = "01 3C";Serial.println("01 3C");delay(50);ReadData();}}
  if (MenuID==5){lcd.setCursor(0, 0);lcd.print("06 CAT 2 Temp      ");lcd.setCursor(0, 1);lcd.print(DisplayString);if (RefreshCounter==RefreshCounterMax){SentMessage = "01 3D";Serial.println("01 3D");delay(50);ReadData();}}
  if (MenuID==6){lcd.setCursor(0, 0);lcd.print("07 CAT 3 Temp      ");lcd.setCursor(0, 1);lcd.print(DisplayString);if (RefreshCounter==RefreshCounterMax){SentMessage = "01 3E";Serial.println("01 3E");delay(50);ReadData();}}
  if (MenuID==7){lcd.setCursor(0, 0);lcd.print("08 CAT 4 Temp      ");lcd.setCursor(0, 1);lcd.print(DisplayString);if (RefreshCounter==RefreshCounterMax){SentMessage = "01 3F";Serial.println("01 3F");delay(50);ReadData();}}
  if (MenuID==8){lcd.setCursor(0, 0);lcd.print("09 Coolant Temp    ");lcd.setCursor(0, 1);lcd.print(DisplayString);if (RefreshCounter==RefreshCounterMax){SentMessage = "01 05";Serial.println("01 05");delay(50);ReadData();}}
  if (MenuID==9){lcd.setCursor(0, 0);lcd.print("10 Vehicle Speed   ");lcd.setCursor(0, 1);lcd.print(DisplayString);if (RefreshCounter==RefreshCounterMax){SentMessage = "01 0D";Serial.println("01 0D");delay(50);ReadData();}}
  if (MenuID==10){lcd.setCursor(0, 0);lcd.print("11 Air Flow Rate  ");lcd.setCursor(0, 1);lcd.print(DisplayString);if (RefreshCounter==RefreshCounterMax){SentMessage = "01 10";Serial.println("01 10");delay(50);ReadData();}}
  if (MenuID==11){lcd.setCursor(0, 0);lcd.print("12 Barometric     ");lcd.setCursor(0, 1);lcd.print(DisplayString);if (RefreshCounter==RefreshCounterMax){SentMessage = "01 33";Serial.println("01 33");delay(50);ReadData();}}
  if (MenuID==12){lcd.setCursor(0, 0);lcd.print("13 EGT            ");lcd.setCursor(0, 1);lcd.print(DisplayString);if (RefreshCounter==RefreshCounterMax){SentMessage = "01 78";Serial.println("01 78");delay(50);ReadData();}}
  if (MenuID==13){lcd.setCursor(0, 0);lcd.print("14 Oil Temp       ");lcd.setCursor(0, 1);lcd.print(DisplayString);if (RefreshCounter==RefreshCounterMax){SentMessage = "01 5C";Serial.println("01 5C");delay(50);ReadData();}}
}

if (UpDownMenu==2)
{
  if(RESETMenuName==0){lcd.setCursor(0, 0);lcd.print("About By Marek");lcd.setCursor(0, 1);lcd.print("\\TKHKChip V1.00 ");delay(2000);RESETMenuName=1;}
  lcd.setCursor(0, 0);lcd.print("System Version  ");  
}

//Restart RefreshCounter  
if (RefreshCounter>=RefreshCounterMax){RefreshCounter=0;}
delay(1);

}

//Read Data and act accordingly
void ReadData()
{

  BuildINString="";  
  while(Serial.available() > 0)
  {
    inData=0;
    inChar=0;
    inData = Serial.read();
    inChar=char(inData);
    BuildINString = BuildINString + inChar;
  }
  
  //if(BuildINString!=""){Serial.print(BuildINString);}
  BuildINString.replace(SentMessage,"");
  BuildINString.replace(">","");
  BuildINString.replace("OK","");
  BuildINString.replace("STOPPED","");
  BuildINString.replace("SEARCHING","");
  BuildINString.replace("NO DATA","");
  BuildINString.replace("?","");
  BuildINString.replace(",","");
  //Serial.print(BuildINString);
  
  //Check which OBD Command was sent and calculate VALUE 
  //Calculate RPM I.E Returned bytes wil be 41 0C 1B E0 
  //RPM
  if (SentMessage=="01 0C")
  {
    WorkingString = BuildINString.substring(7,9);
    A = strtoul(WorkingString.c_str(),NULL,16);
    WorkingString = BuildINString.substring(10,12);
    B = strtoul(WorkingString.c_str(),NULL,16);
   
   DisplayValue = ((A * 256)+B)/4;
   DisplayString = String(DisplayValue) + " rpm               ";
   lcd.setCursor(0, 1);
   lcd.print(DisplayString);
   C = DisplayString.toInt();
  }
  
  //Calculate Vehicle speed I.E Returned bytes wil be 41 0C 1B E0 
  if (SentMessage=="01 0D")
  {
    WorkingString = BuildINString.substring(7,9);
    A = strtoul(WorkingString.c_str(),NULL,16);

   DisplayValue = A;
   DisplayString = String(DisplayValue) + " km/h              ";
   lcd.setCursor(0, 1);
   lcd.print(DisplayString); 
  }
  
  //Coolant Temp 
  if (SentMessage=="01 05")
  {
    WorkingString = BuildINString.substring(7,9);
    A = strtoul(WorkingString.c_str(),NULL,16);

   DisplayValue = A - 40;
   DisplayString = String(DisplayValue) + " C                ";
   lcd.setCursor(0, 1);
   lcd.print(DisplayString); 
  }
  
  //IAT Temp 
  if (SentMessage=="01 0F")
  {
    WorkingString = BuildINString.substring(7,9);
    A = strtoul(WorkingString.c_str(),NULL,16);

   DisplayValue = A -40;
   DisplayString = String(DisplayValue) + " C                ";
   lcd.setCursor(0, 1);
   lcd.print(DisplayString); 
  }
  
  //Air flow Rate
  if (SentMessage=="01 10")
  {
    WorkingString = BuildINString.substring(7,9);
    A = strtoul(WorkingString.c_str(),NULL,16);
    WorkingString = BuildINString.substring(11,13);
    B = strtoul(WorkingString.c_str(),NULL,16);
   
   DisplayValue = ((A * 256)+B)/100;
   DisplayString = String(DisplayValue) + " g/s            ";
   lcd.setCursor(0, 1);
   lcd.print(DisplayString); 
  }
  
  //Ambient Temp 
  if (SentMessage=="01 46")
  {
    WorkingString = BuildINString.substring(7,9);
    A = strtoul(WorkingString.c_str(),NULL,16);

   DisplayValue = A -40;
   DisplayString = String(DisplayValue) + " C             ";
   lcd.setCursor(0, 1);
   lcd.print(DisplayString); 
  }
  
  //ENGINE OIL TEMP
  if (SentMessage=="01 5C")
  {
    WorkingString = BuildINString.substring(7,9);
    A = strtoul(WorkingString.c_str(),NULL,16);

   DisplayValue = A -40;
   DisplayString = String(DisplayValue) + " C             ";
   lcd.setCursor(0, 1);
   lcd.print(DisplayString); 
  }
  
  //Throttle position 
  if (SentMessage=="01 11")
  {
    WorkingString = BuildINString.substring(7,9);
    A = strtoul(WorkingString.c_str(),NULL,16);

   DisplayValue = A *100/255;
   DisplayString = String(DisplayValue) + " %              ";
   lcd.setCursor(0, 1);
   lcd.print(DisplayString); 
  }
  
  //Barometric pressure
  if (SentMessage=="01 33")
  {
    WorkingString = BuildINString.substring(7,9);
    A = strtoul(WorkingString.c_str(),NULL,16);

   DisplayValue = A;
   DisplayString = String(DisplayValue) + " kpa              ";
   lcd.setCursor(0, 1);
   lcd.print(DisplayString); 
  }

  //CAT 1 Temp //((A*256)+B)/10 - 40
  if (SentMessage=="01 3C")
  {
    WorkingString = BuildINString.substring(7,9);
    A = strtoul(WorkingString.c_str(),NULL,16);
    WorkingString = BuildINString.substring(10,12);
    B = strtoul(WorkingString.c_str(),NULL,16);
   
   DisplayValue = ((A * 256)+B)/10 - 40;
   DisplayString = String(DisplayValue) + " C               ";
   lcd.setCursor(0, 1);
   lcd.print(DisplayString);
  }
  
  //CAT 2 Temp //((A*256)+B)/10 - 40
  if (SentMessage=="01 3D")
  {
    WorkingString = BuildINString.substring(7,9);
    A = strtoul(WorkingString.c_str(),NULL,16);
    WorkingString = BuildINString.substring(10,12);
    B = strtoul(WorkingString.c_str(),NULL,16);
   
   DisplayValue = ((A * 256)+B)/10 - 40;
   DisplayString = String(DisplayValue) + " C               ";
   lcd.setCursor(0, 1);
   lcd.print(DisplayString);
  }
  
  //CAT 3 Temp //((A*256)+B)/10 - 40
  if (SentMessage=="01 3E")
  {
    WorkingString = BuildINString.substring(7,9);
    A = strtoul(WorkingString.c_str(),NULL,16);
    WorkingString = BuildINString.substring(10,12);
    B = strtoul(WorkingString.c_str(),NULL,16);
   
   DisplayValue = ((A * 256)+B)/10 - 40;
   DisplayString = String(DisplayValue) + " C               ";
   lcd.setCursor(0, 1);
   lcd.print(DisplayString);
  }
  
  //CAT 4 Temp //((A*256)+B)/10 - 40
  if (SentMessage=="01 3F")
  {
    WorkingString = BuildINString.substring(7,9);
    A = strtoul(WorkingString.c_str(),NULL,16);
    WorkingString = BuildINString.substring(10,12);
    B = strtoul(WorkingString.c_str(),NULL,16);
   
   DisplayValue = ((A * 256)+B)/10 - 40;
   DisplayString = String(DisplayValue) + " C               ";
   lcd.setCursor(0, 1);
   lcd.print(DisplayString);
  }
}

void Bootup()
{
lcd.print("TKHKChip V1.00 ");
     for (int i=0; i <= 1; i++)
     {
       for (int j=1; j <= 4; j++)// -/|\-
       {
        if(j==1){lcd.setCursor(0, 1);lcd.print ("-");delay(200);} 
        if(j==2){lcd.setCursor(0, 1);lcd.print ("/");delay(200);}
        if(j==3){lcd.setCursor(0, 1);lcd.print ("|");delay(200);} 
        if(j==4){lcd.setCursor(0, 1);lcd.print ("\\");delay(200);} 
       }   
     }
 lcd.setCursor(2, 1);
 lcd.print("Marek Kivitalo");    
delay(2000);  
}
