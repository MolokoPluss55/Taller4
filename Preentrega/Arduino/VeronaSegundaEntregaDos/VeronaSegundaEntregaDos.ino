#include "Wire.h"  
#include "I2Cdev.h"  
#include "MPU6050.h"
#include "math.h"
 
// AD0 low = 0x68 
MPU6050 mpu;
 
int16_t ax, ay, az;  ///Datos acelerometro 1 - Leonardo
int16_t gx, gy, gz;
//Datos parseo
float datoX;
float datoY;

String datoXS;
int datoXI;

String datoYS;
int datoYI;

//Cajitas para promedio aceleromentro X
const int numLecturas = 15; //número de lecturas para el promedio
int lecturas[numLecturas]; //arreglo con las lecturas de la entrada analogica
int index = 0;
int total = 0;
float promedioX = 0; 

//Cajitas para promedio aceleromentro Y
const int numLecturasy = 15; //número de lecturas para el promedio
int lecturasy[numLecturasy]; //arreglo con las lecturas de la entrada analogica
int indexy = 0;
int totaly = 0;
float promedioY = 0;

void setup() {
  Wire.begin();  //I2C bus
  Serial.begin(9600);
  while (!Serial) {
    ;  //esperar a que se conecte el puerto serial
  }
 
  // Serial.println("Inicializando comunicación I2C");
  mpu.initialize();
  
 
 // Verificar conexión
 // Serial.println(mpu.testConnection() ? "0x68 conectó" : "0x68 falló");
  
  delay(1000);
}
 
void loop() {
 
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
 
  ax = -(ax / 1000);
  ay = (ay / 1000);
 
  //PROMEDIO AX
 /* total = total - lecturas[index];
  lecturas[index] = ax;
  total = total + lecturas[index];
  index = index + 1;

  if(index >= numLecturas)
  {
    index = 0;  
  }

  promedioX = total / numLecturas;
  

  //PROMEDIO AY
  totaly = totaly - lecturasy[indexy];
  lecturasy[indexy] = ay;
  totaly = totaly + lecturasy[indexy];
  indexy = indexy + 1;

  if(indexy >= numLecturasy)
  {
    indexy = 0;  
  }

  promedioY = totaly / numLecturasy;*/
  
  datoX = map(ax, -16, 16, -90, 90);
  datoXI = (int) datoX;
  datoXS = String(datoXI);

  datoY = map(ay, -16, 16, -90, 90);
  datoYI = (int) datoY;
  datoYS = String(datoYI);
  
  Serial.print(datoXS);
  Serial.print(",");
  Serial.println(datoYS);
 Serial.flush();
  delay(100);
}
