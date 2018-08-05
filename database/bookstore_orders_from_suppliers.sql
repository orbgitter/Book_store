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
-- Table structure for table `orders_from_suppliers`
--

DROP TABLE IF EXISTS `orders_from_suppliers`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
 SET character_set_client = utf8mb4 ;
CREATE TABLE `orders_from_suppliers` (
  `order_id` int(11) NOT NULL,
  `supplier_id` int(11) DEFAULT NULL,
  `employee_id` int(11) DEFAULT NULL,
  `date` date DEFAULT NULL,
  `status` int(11) DEFAULT NULL,
  `employees_employee_id` int(11) DEFAULT NULL,
  `suppliers_supplier_id` int(11) DEFAULT NULL,
  `orders_from_suppliers_order_id` int(11) DEFAULT NULL,
  `status_codes_status` int(11) DEFAULT NULL,
  PRIMARY KEY (`order_id`),
  KEY `fk_ordersfromsuppliers_employees1_idx` (`employees_employee_id`),
  KEY `fk_ordersfromsuppliers_suppliers1_idx` (`suppliers_supplier_id`),
  KEY `fk_orders_from_suppliers_status_codes1_idx` (`status_codes_status`),
  CONSTRAINT `fk_orders_from_suppliers_status_codes1` FOREIGN KEY (`status_codes_status`) REFERENCES `status_codes` (`status`),
  CONSTRAINT `fk_ordersfromsuppliers_employees1` FOREIGN KEY (`employees_employee_id`) REFERENCES `employees` (`employee_id`),
  CONSTRAINT `fk_ordersfromsuppliers_suppliers1` FOREIGN KEY (`suppliers_supplier_id`) REFERENCES `suppliers` (`supplier_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `orders_from_suppliers`
--

LOCK TABLES `orders_from_suppliers` WRITE;
/*!40000 ALTER TABLE `orders_from_suppliers` DISABLE KEYS */;
INSERT INTO `orders_from_suppliers` VALUES (10,95,1193,'2018-02-05',1,NULL,NULL,NULL,NULL),(11,95,8410,'2017-08-05',1,NULL,NULL,NULL,NULL),(12,95,8410,'2017-10-23',1,NULL,NULL,NULL,NULL),(13,96,2115,'2015-12-17',1,NULL,NULL,NULL,NULL),(14,96,2115,'2016-12-01',1,NULL,NULL,NULL,NULL),(15,97,2854,'2018-01-01',1,NULL,NULL,NULL,NULL),(16,98,2854,'2018-01-02',1,NULL,NULL,NULL,NULL),(17,98,2854,'2017-12-25',1,NULL,NULL,NULL,NULL),(18,99,7584,'2018-11-12',1,NULL,NULL,NULL,NULL),(19,100,7584,'2018-09-02',1,NULL,NULL,NULL,NULL),(20,100,5482,'2018-09-02',1,NULL,NULL,NULL,NULL),(21,101,4001,'2018-09-09',1,NULL,NULL,NULL,NULL),(22,102,4111,'2018-04-02',1,NULL,NULL,NULL,NULL),(23,102,4111,'2017-11-18',1,NULL,NULL,NULL,NULL),(24,103,5529,'2017-08-22',1,NULL,NULL,NULL,NULL),(25,104,5529,'2018-06-01',1,NULL,NULL,NULL,NULL);
/*!40000 ALTER TABLE `orders_from_suppliers` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2018-08-05 18:40:06
