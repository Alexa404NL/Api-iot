-- MySQL dump 10.13  Distrib 8.0.35, for Win64 (x86_64)
--
-- Host: localhost    Database: iot
-- ------------------------------------------------------
-- Server version	8.0.35

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8mb4 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `temps`
--

CREATE TABLE sensores (
    id_sens INT AUTO_INCREMENT PRIMARY KEY,
    tipo_sensor VARCHAR(20) NOT NULL
);


CREATE TABLE color (
    id int AUTO_INCREMENT PRIMARY KEY,
    sensor_id INT NOT NULL,
    r INT NOT NULL,
    g INT NOT NULL,
    b INT NOT NULL,
    color_formado VARCHAR(50) NOT NULL,
    tiempo TIMESTAMP,
    FOREIGN KEY (sensor_id) REFERENCES sensores(id_sens)
);


CREATE TABLE distancia (
    id int AUTO_INCREMENT PRIMARY KEY,
    sensor_id INT NOT NULL,
    distancia FLOAT NOT NULL,
    tiempo TIMESTAMP,
    FOREIGN KEY (sensor_id) REFERENCES sensores(id_sens)
);


CREATE TABLE promedios (
    id int AUTO_INCREMENT PRIMARY KEY,
    sensor_id INT NOT NULL,
    tipo_promedio VARCHAR(20) NOT NULL CHECK (tipo_promedio IN ('color', 'distancia')),
    promedio_valor FLOAT NOT NULL,
    timestamp_inicio TIMESTAMP NOT NULL,
    timestamp_fin TIMESTAMP NOT NULL,
    FOREIGN KEY (sensor_id) REFERENCES sensores(id_sens)
);