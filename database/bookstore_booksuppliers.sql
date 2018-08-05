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
-- Table structure for table `booksuppliers`
--

DROP TABLE IF EXISTS `booksuppliers`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
 SET character_set_client = utf8mb4 ;
CREATE TABLE `booksuppliers` (
  `book_id` int(11) NOT NULL,
  `supplier_id` int(11) NOT NULL,
  `price` double DEFAULT NULL,
  `suppliers_supplier_id` int(11) DEFAULT NULL,
  `books_book_id` int(11) DEFAULT NULL,
  PRIMARY KEY (`book_id`,`supplier_id`),
  KEY `fk_booksuppliers_suppliers1_idx` (`suppliers_supplier_id`),
  KEY `fk_booksuppliers_books1_idx` (`books_book_id`),
  CONSTRAINT `fk_booksuppliers_books1` FOREIGN KEY (`books_book_id`) REFERENCES `books` (`book_id`),
  CONSTRAINT `fk_booksuppliers_suppliers1` FOREIGN KEY (`suppliers_supplier_id`) REFERENCES `suppliers` (`supplier_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `booksuppliers`
--

LOCK TABLES `booksuppliers` WRITE;
/*!40000 ALTER TABLE `booksuppliers` DISABLE KEYS */;
INSERT INTO `booksuppliers` VALUES (10,95,60,NULL,NULL),(10,98,75,NULL,NULL),(11,100,10,NULL,NULL),(12,96,50,NULL,NULL),(12,97,45,NULL,NULL),(12,104,60,NULL,NULL),(13,96,75,NULL,NULL),(13,98,80,NULL,NULL),(14,96,50,NULL,NULL),(15,95,55,NULL,NULL),(15,102,40,NULL,NULL),(15,104,45,NULL,NULL),(16,95,5,NULL,NULL),(16,96,4,NULL,NULL),(16,97,8,NULL,NULL),(16,100,4,NULL,NULL),(17,96,15,NULL,NULL),(17,99,10,NULL,NULL),(17,102,5,NULL,NULL),(18,98,85,NULL,NULL),(18,103,100,NULL,NULL),(19,97,80,NULL,NULL),(19,102,90,NULL,NULL),(19,103,75,NULL,NULL),(19,104,70,NULL,NULL),(20,95,60,NULL,NULL),(20,98,52,NULL,NULL),(20,99,50,NULL,NULL);
/*!40000 ALTER TABLE `booksuppliers` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2018-08-05 18:40:10
