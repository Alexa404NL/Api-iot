/**
 * Instrucciones:
 * 
 * 1. Por cada sensor que tenga tu tabla de base de datos corresponsientes, deberás crear 
 *    un archivo similar al archivo /RestControllers/sensorTemperatura.js
 * 2. Registra en el router todos los métodos disponibles en tu controlador con una URL que haga mencion a dicha acción
 * 
 * 
 */
const constants = require("./constants")
const express = require('express');
const temperaturaController = require('./RestControllers/sensorTemperatura.js'); 
const colorController = require('./RestControllers/sensorColor.js'); 
const router = express.Router();

router.get("/",function(req,res){
    res.send('<html><head><title>API IoT</title></head><body><h1>Hello World!</h1></body></html>');
});

/**
 * URL's que debes configurar en tu server para incluir tus endpoints que reciben peticiones para cada 
 * sensor.
 * 
 * Hay 3 métodos actualmente, 1 get HTTP y 2 post HTTP. En todos, el primer argumento es una url (creada de manera parametrizada con constantes)
 * El segundo método es la función js que responderá a las peticiones de dicha URL. Estas están en el archivo sensorTemperatura.js
 * 
 * Para otros sensores, puedes agregar otros archivos y configurar sus url's.
 * 
 */
router.get(constants.contextURL + constants.api + constants.getTemperatureSensor, temperaturaController.getLogTemperatura);
router.post(constants.contextURL + constants.api + constants.getTemperatureSensorByDate, temperaturaController.getLogByDateBetween);
router.post(constants.contextURL + constants.api + constants.postTemperatureSensor,temperaturaController.insertLogTemperatura);
router.get(constants.contextURL + constants.api + constants.getColorSensor, colorController.getLogColor);
router.post(constants.contextURL + constants.api + constants.getColorSensorByDate, colorController.getLogByDateBetween_color);
router.post(constants.contextURL + constants.api + constants.postColorSensor,colorController.insertLogColor);


//le decimos a Node que queremos hacer uso de nuestro router en otros archivos (como por ejemplo, app.js)
module.exports = router;