INSERT INTO `esb_db`.`routes`(sender,destination,message_type)
VALUES
('A','a','CreditReport1'),
('B','b','CreditReport2'),
('C','c','CreditReport3'),
('D','d','CreditReport4'),
('E','e','CreditReport5');

INSERT INTO esb_db.transform_config(route_id,config_key,config_value)
VALUES
(1,'key1','a'),
(2,'key2','b'),
(3,'key3','c'),
(4,'key4','d'),
(5,'key5','e');

INSERT INTO esb_db.transport_config (route_id,config_key,config_value)
VALUES
(1,'k1','a'),
(2,'k2','b'),
(3,'k3','c'),
(4,'k4','d'),
(5,'k5','e');