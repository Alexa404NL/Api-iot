const mysql = require("../database/db");
const constants = require("../constants")



async function getLogColor(req,res){
    try{
  
      var sql = constants.selectColorSensor;
      var conn = mysql.getConnection();
      conn.connect((error)=>{
          if (error) throw error;
          conn.query(sql, (error, data, fields) => {
              if (error) {
                res.status(500);
                res.send(error.message);
              } else {
                console.log(data);
                res.json({
                  data,
                });
              }
              conn.end();
          });
      });
    }catch(error){
      console.log(error)
      res.status(500)
      res.send(error)
    }
  }

  async function getLogByDateBetween_color(req,res){
    try{
      var sql = constants.selectColorSensorByDate;
  
      var date_one = req.body.date_one;
      var date_two = req.body.date_two;
  
      var conn = mysql.getConnection();
      conn.connect((error)=>{
          if (error) throw error;
          var params = [date_one,date_two];
          conn.execute(sql, params, (error, data, fields) => {
              if (error) {
                res.status(500);
                res.send(error.message);
              } else {
                console.log(data);
                res.json({
                  data,
                });
              }
              conn.end();
          });
      });
    }catch(error){
      console.log(error)
      res.status(500)
      res.send(error)
    }
    
  }


  async function insertLogColor(req,res){
    try{
  
      var sql = constants.insertColorSensor;
  
      //el valor se recibe en el cuerpo de correo
      //cualquier dato que vaya a ir en el insert deberás guardarlo en una variable local
      var val = req.body.val;
      var color = req.body.color;
  
      var conn = mysql.getConnection();
      conn.connect((error)=>{
          if (error) throw error;
  
          // así mismo, cualquier dato que vaya a insertarse, deberá incluirse en
          // los valores de los parámetros del Insert
          var params = [val, color]; 
          conn.execute(sql, params, (error, data, fields) => {
              if (error) {
                res.status(500);
                res.send(error.message);
              } else {
                console.log(data);
                res.json({
                  status: 200,
                  message: "Valor insertado",
                  affectedRows: data.affectedRows,
                });
              }
              conn.end();
          });
      });
  
    }catch(error){
      console.log(error)
      res.status(500)
      res.send(error)
    }
    
  }
  module.exports = {insertLogColor, getLogColor, getLogByDateBetween_color};