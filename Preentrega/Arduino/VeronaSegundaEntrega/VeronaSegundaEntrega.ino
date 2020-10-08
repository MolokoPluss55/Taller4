#include "Wire.h"  
#include "I2Cdev.h"  
#include "MPU6050.h"
 
// AD0 low = 0x68 
// AD0 high = 0x69
MPU6050 mpu(0x68);
MPU6050 mpu1(0x69);
 
int16_t ax, ay, az;  //Datos acelerometro 1
int16_t gx, gy, gz;
int16_t ax2, ay2, az2;  //Datos acelerometro 2
int16_t gx2, gy2, gz2;


//Cajitas para promedio aceleromentro X
const int numLecturas = 15; //número de lecturas para el promedio
int lecturas[numLecturas]; //arreglo con las lecturas de la entrada analogica
int index = 0;
int total = 0;
float promedioX = 0; 


//Cajitas para promedio aceleromentro X2
const int numLecturas2 = 15; //número de lecturas para el promedio
int lecturas2[numLecturas2]; //arreglo con las lecturas de la entrada analogica
int index2 = 0;
int total2 = 0;
float promedioX2 = 0; 


//Cajitas para promedio aceleromentro Y
const int numLecturasy = 15; //número de lecturas para el promedio
int lecturasy[numLecturasy]; //arreglo con las lecturas de la entrada analogica
int indexy = 0;
int totaly = 0;
float promedioY = 0;


//Cajitas para promedio aceleromentro Y
const int numLecturasy2 = 15; //número de lecturas para el promedio
int lecturasy2[numLecturasy2]; //arreglo con las lecturas de la entrada analogica
int indexy2 = 0;
int totaly2 = 0;
float promedioY2 = 0;

//Datos parseo
float datoXM;
int datoX;
String datoXL;


float datoYM;
int datoY;
String datoYL;


float datoXM2;
int datoX2;
String datoXL2;


float datoYM2;
int datoY2;
String datoYL2;

 
void setup() {
  Wire.begin();  //I2C bus
  Serial.begin(9600);
  while (!Serial) {
    ; //esperar a que se conecte el puerto serial
  }


 // Serial.println("Inicializando comunicación I2C");
  mpu.initialize();
  mpu1.initialize();
 
  // Verificar conexión
 // Serial.println(mpu.testConnection() ? "0x68 conectó" : "0x68 falló");
 // Serial.println(mpu1.testConnection() ? "0x69 conectó" : "0x69 falló");
 
  delay(1000);
}
 
void loop() {
 
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  mpu1.getMotion6(&ax2, &ay2, &az2, &gx2, &gy2, &gz2);

  ax = -(ax / 1000);
  ax2 = -(ax2 / 1000);

  ay = (ay / 1000);
  ay2 = (ay2 / 1000);

  //PROMEDIO AX
  total = total - lecturas[index];
  lecturas[index] = ax;
  total = total + lecturas[index];
  index = index + 1; 

  if(index >= numLecturas)
  {
    index = 0;  
  }

  promedioX = total / numLecturas;
  
  
  //PROMEDIO AX2
  total2 = total2 - lecturas2[index2];
  lecturas2[index2] = ax2;
  total2 = total2 + lecturas2[index2];
  index2 = index2 + 1;

  if(index2 >= numLecturas2)
  {
    index2 = 0;  
  }

  promedioX2 = total2 / numLecturas2;

  //PROMEDIO AY
  totaly = totaly - lecturasy[indexy];
  lecturasy[indexy] = ay;
  totaly = totaly + lecturasy[indexy];
  indexy = indexy + 1;

  if(indexy >= numLecturasy)
  {
    indexy = 0;  
  }

  promedioY = totaly / numLecturasy;

  //X
  datoXM = map(promedioX, -16, 16, -90, 90);
  datoX = (int) datoXM;
  datoXL = String(datoX);

  //Y
  datoYM = map(promedioY, -16, 16, -90, 90);
  datoY = (int) datoYM;
  datoYL = String(datoY);

  //X2
  datoXM2 = map(promedioX2, -16, 16, -90, 90);
  datoX2 = (int) datoXM2;
  datoXL2 = String(datoX2);

  //Y2
  datoYM2 = map(promedioY2, -16, 16, -90, 90);
  datoY2 = (int) datoYM2;
  datoYL2 = String(datoY2);

//PROMEDIO AY2
  totaly2 = totaly2 - lecturasy2[indexy2];
  lecturasy2[indexy2] = ay2;
  totaly2 = totaly2 + lecturasy2[indexy2];
  indexy2 = indexy2 + 1;

  if(indexy2 >= numLecturasy2)
  {
    indexy2 = 0;  
  }

  promedioY2 = totaly2 / numLecturasy2;

  Serial.print(datoXL);
  Serial.print(",");
  Serial.print(datoYL);
  Serial.print(",");
  Serial.print(datoXL2);
  Serial.print(",");
  Serial.println(datoYL2);
  Serial.flush();
  delay(10);

  
}
