
/*
 * LOCAL DATABASE Config
 * 
 *  Para acceder a una BD en la nube debes configurar un archivo .env
 */
const dbHost = "mysql-210e8947-tec-5485.b.aivencloud.com";
const dbPort = "18042";
const dbUser = "avnadmin";
const dbPass = "AVNS_Uxdxp-ONR2M8zkLD03O";
const dbName = "IoT";



/*
 * Server General Configuration
 */
const serverPort = 3000
const contextURL = '/iot'; //If needed, project context
const api = '/api'; // Sugested API URL

//URLS para los sensores

//SENSOR 1. *SENSOR DE TEMPERATURA*
const getTemperatureSensor = '/getTemperatures'
const getTemperatureSensorByDate = '/getTemperatures'
const postTemperatureSensor = '/insertTemperature' //Implemented Endpoint URL

//SENSOR 2. *SENSOR DE COLOR*
const getColorSensor = '/getColors'
const getColorSensorByDate = '/getColors'
const postColorSensor = '/insertColor';

//SENSOR 3. *SENSOR DE PROXIMIDAD*
const getDistanceSensor = '/getDistance'
const getDistanceSensorByDate = '/getDistance'
const postDistanceSensor = '/insertDistance';


//Queries de Base de Datos

//Sensor de temperatura
const selectTemperature = 'SELECT * FROM temps';
const selectTemperatureByDate = 'SELECT * FROM temps WHERE fecha between ? and ?';
const insertTemperature = 'INSERT INTO temps (valor) values (?)';

//Sensor de color
const selectColorSensor = 'SELECT * FROM color_sensor';
const selectColorSensorByDate = 'SELECT * FROM color_sensor WHERE fecha between ? and ?';
const insertColorSensor = 'INSERT INTO color_sensor (val, color) values (?, ?)';

// Sensor de distancia
const selectDistance = 'SELECT * FROM distancia';
const selectDistanceByDate = 'SELECT * FROM distancia WHERE fecha between ? and ?';
const insertDistance = 'INSERT INTO distancia (valor) values (?)';

module.exports= {
   dbHost,dbPort,dbUser,dbPass,dbName,serverPort, contextURL,api,getTemperatureSensor,
   getTemperatureSensorByDate,postTemperatureSensor,selectTemperature,selectTemperatureByDate,insertTemperature,
   getColorSensor, getColorSensorByDate, postColorSensor, selectColorSensor,selectColorSensorByDate,insertColorSensor,
   selectDistance, selectDistanceByDate, insertDistance
}
