DROP SCHEMA IF EXISTS `esb_db` ;

CREATE SCHEMA IF NOT EXISTS `esb_db` DEFAULT CHARACTER SET utf8mb4 ;
USE `esb_db` ;

DROP TABLE IF EXISTS `esb_db`.`routes`;
CREATE TABLE IF NOT EXISTS `esb_db`.`routes` (
  `route_id` INT NOT NULL AUTO_INCREMENT,
  `sender` VARCHAR(45) NOT NULL,
  `destination` VARCHAR(45) NOT NULL,
  PRIMARY KEY (`route_id`))
ENGINE = InnoDB;
