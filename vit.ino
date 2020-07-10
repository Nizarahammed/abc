//#include <Adafruit_Sensor.h>
#define USE_ARDUINO_INTERRUPTS true
#include <DHT.h>
#define DHTTYPE DHT11
#define dhtpin 12
DHT dht(dhtpin,DHTTYPE);
//#include <PulseSensorPlayground.h>
#include <Blynk.h>       //cloud
#include <ESP8266WiFi.h>     //nodMCU library
#include <BlynkSimpleEsp8266.h>
char auth[] = "mFWuWO6hr17_Xp5CETjosg11P-tX22Ox";
char ssid[] = "Nizar";    //wifi name
char pass[] = "00000000";
//LM35 temp(A0);
#define heartPin A0
int threshold=550;
#define pi 3.14159265358979323846
double lat2[]={12.969457,12.969246,12.968407,12.966720,12.957781,12.957208,12.945937,12.934125,12.934894,12.936659,12.924380,12.924506,12.916565,12.901650,12.870492,12.973374,12.977799};
double lon2[]={79.154636,79.148797,79.136968,79.136868,79.137167,79.141953,79.137302,79.141439,79.153739,79.167686,79.134554,79.140168,79.132487,79.131560,79.089964,79.159538,79.154257};
String addr[]={"Chettinad Hospital, VIT University, Vellore-14","Paul Brand Integrate health centre, Old Katpadi, Vellore,ph:09885944778","Lakshmi Hospital, 7/8, Pillayar Kovil Street, Vellore road-007,ph:0416 224 2670","RM Hospital, 286/176, Dharaoadavedu, Katpadi-007,ph:0416 224 8279","Akshayaa Hospital, No.1, 4th Street, Gopalapuram, Katpadi, Vellore-006,093630 68886","Mohan's diabetes speciality centre, Sundhandhara Ponvizha nagar, Gandhinagar, Vellore,ph:078258 88651","Kumaran Hospital, 112, Near Kotab Mahindra bank, Gandhinagar, Vellore,ph:0416 224 3630","Naruvi Hospital, 72, Collector's office road, NH-48, Vellore,ph:087540 16970","Nalam Medical centre, 44, Arocot road, Sathuvachari, Vellore,ph:0416 225 4461","Manisundharam Hospital, 288, Near more Suprermarket, South Avenue road, Vellore,ph:0416 420 0326","Chest pain Unit, Christian Medical College, Ida Scudder road, Vellore","Indhra Nursing Home, 452, Main bazar road, Saidapet, Near CMC, Vellore,ph:098423 24425","CMC Hospital, Thottapalayam, Vellore,ph:--","Vellore Hospital, SH 207, Sashtri nagar, Veerasaami nagar, Vellore","Sri Narayani Hospital, Azad road, Thirumalaikodi, Vellore,ph:0416 220 6300","Free Medical Hospital, VIT, University, Vellore","Ex-Service man Hospital, VIT Complex, Vellore"};
double deg2rad(double);
double rad2deg(double);
int hos[20];
int k,temp=0;
//PulseSensorPlayground pulseSensor;




void setup() {
 
  // put your setup code here, to run once:
  Serial.begin(9600);


 
 
  Blynk.begin(auth, ssid, pass);    //inside void setup
                  //locating the given latitude and longitude in the blynk maps
//pulseSensor.begin();
//pulseSensor.analogInput(heartPin);
// pulseSensor.setThreshold(threshold);
// pulseSensor.setSerial(Serial);
 //pulseSensor.begin();
}
double distance(double lat1, double lon1,int unit) {
  double theta, dist;
  
  for(int i=0;i<17;i++)
  {
  if ((lat1 == lat2[i]) && (lon1 == lon2[i])) {
    return 0;
  }
  else {

    theta = lon1 - lon2[i];
    dist = sin(deg2rad(lat1)) * sin(deg2rad(lat2[i])) + cos(deg2rad(lat1)) * cos(deg2rad(lat2[i])) * cos(deg2rad(theta));
    dist = acos(dist);
    dist = rad2deg(dist);
    dist = dist * 60 * 1.1515;
    switch(unit) {
      case 'K':
        dist = dist * 1.609344;
        break;
      case 'N':
        dist = dist * 0.8684;
        break;
    }
   if(dist<2)
   {
    hos[k]=i;
   k++;
    }
  }
}
//return hos;
}


double deg2rad(double deg) {
  return (deg * pi / 180);
}


double rad2deg(double rad) {
  return (rad * 180 / pi);
}


void loop() {
  float temperature=dht.readTemperature();
  Serial.println(temperature);
  delay(500);
  int heartValue = analogRead(heartPin);
  Serial.println(heartValue);
  delay(500);
//int bpm=pulseSensor.getBeatsPerMinute();
//Serial.println(bpm);
  Blynk.virtualWrite(V0,temperature);
  Blynk.virtualWrite(V2,heartPin);
  
  if(heartValue>750)
  {distance(12.970181,79.156979,'K');
  for(int i=0;i<k;i++)
  {
    
    temp=hos[i];
   Serial.println(addr[temp]);
   Serial.println(" ");
    Blynk.notify(addr[temp]);
    Blynk.email("nizarahammed14@gmail.com", "Subject:HOSPITALS LESS THAN 2KKMS", addr[temp]);
  }
  k=0;
  }
   Blynk.run();
  

}
