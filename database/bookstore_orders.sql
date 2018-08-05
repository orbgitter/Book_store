-- MySQL dump 10.13  Distrib 8.0.12, for Win64 (x86_64)
--
-- Host: 127.0.0.1    Database: bookstore
-- ------------------------------------------------------
-- Server version	8.0.12

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
 SET NAMES utf8 ;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `orders`
--

DROP TABLE IF EXISTS `orders`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
 SET character_set_client = utf8mb4 ;
CREATE TABLE `orders` (
  `order_id` int(11) NOT NULL,
  `customer_id` int(11) DEFAULT NULL,
  `employee_id` int(11) DEFAULT NULL,
  `date` date DEFAULT NULL,
  `init_status` int(11) DEFAULT NULL,
  `end_status` int(11) DEFAULT NULL,
  `customers_customer_id` int(11) DEFAULT NULL,
  `employees_employee_id` int(11) DEFAULT NULL,
  `status_codes_status` int(11) DEFAULT NULL,
  PRIMARY KEY (`order_id`),
  KEY `fk_orders_customers1_idx` (`customers_customer_id`),
  KEY `fk_orders_employees1_idx` (`employees_employee_id`),
  KEY `fk_orders_status_codes1_idx` (`status_codes_status`),
  CONSTRAINT `fk_orders_customers1` FOREIGN KEY (`customers_customer_id`) REFERENCES `customers` (`customer_id`),
  CONSTRAINT `fk_orders_employees1` FOREIGN KEY (`employees_employee_id`) REFERENCES `employees` (`employee_id`),
  CONSTRAINT `fk_orders_status_codes1` FOREIGN KEY (`status_codes_status`) REFERENCES `status_codes` (`status`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `orders`
--

LOCK TABLES `orders` WRITE;
/*!40000 ALTER TABLE `orders` DISABLE KEYS */;
INSERT INTO `orders` VALUES (110,2835,4949,'2018-01-10',2,1,NULL,NULL,NULL),(111,2835,1193,'2018-04-08',2,2,NULL,NULL,NULL),(112,2834,7584,'2018-08-09',2,3,NULL,NULL,NULL),(113,2835,8410,'2018-10-11',2,2,NULL,NULL,NULL),(114,2886,2835,'2017-02-08',1,1,NULL,NULL,NULL),(115,7634,2854,'2017-05-01',1,1,NULL,NULL,NULL),(116,3183,2854,'2017-08-03',1,1,NULL,NULL,NULL),(117,3821,5482,'2017-11-13',1,1,NULL,NULL,NULL),(118,3785,5529,'2016-03-10',1,1,NULL,NULL,NULL),(119,7634,7584,'2016-03-12',1,1,NULL,NULL,NULL),(120,3785,8410,'2016-12-10',1,1,NULL,NULL,NULL),(121,4463,2854,'2016-09-08',1,1,NULL,NULL,NULL),(122,4463,2854,'2018-03-18',1,1,NULL,NULL,NULL),(123,3821,1193,'2017-04-22',1,1,NULL,NULL,NULL),(124,3821,8410,'2017-06-19',1,1,NULL,NULL,NULL);
/*!40000 ALTER TABLE `orders` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2018-08-05 18:40:07
