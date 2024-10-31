
/*
 * LOCAL DATABASE Config
 * 
 *  Para acceder a una BD en la nube debes configurar un archivo .env
 */
const dbHost = "localhost";
const dbPort = "3306";
const dbUser = "...";
const dbPass = "...";
const dbName = "iot";



/*
 * Server General Configuration
 */
const serverPort = 3000
const contextURL = '/iot'; //If needed, project context
const api = '/api'; // Sugested API URL

//SENSOR 1 URLS. Configurar URLS por cada sensor.
const getTemperatureSensor = '/getTemperatures'
const getTemperatureSensorByDate = '/getTemperatures'
const postTemperatureSensor = '/insertTemperature' //Implemented Endpoint URL
const getColorSensor = '/getColors'
const getColorSensorByDate = '/getColors'
const postColorSensor = '/insertColor';


/*
 * DB Queries
 * Agregar queries por sensor.
 */
const selectTemperature = 'SELECT * FROM temps';
const selectTemperatureByDate = 'SELECT * FROM temps WHERE fecha between ? and ?';
const insertTemperature = 'INSERT INTO temps (valor) values (?)';
const selectColorSensor = 'SELECT * FROM color_sensor';
const selectColorSensorByDate = 'SELECT * FROM color_sensor WHERE fecha between ? and ?';
const insertColorSensor = 'INSERT INTO color_sensor (val, color) values (?, ?)';


module.exports= {
   dbHost,dbPort,dbUser,dbPass,dbName,serverPort, contextURL,api,getTemperatureSensor,
   getTemperatureSensorByDate,postTemperatureSensor,selectTemperature,selectTemperatureByDate,insertTemperature,
   getColorSensor, getColorSensorByDate, postColorSensor, selectColorSensor,selectColorSensorByDate,insertColorSensor
}