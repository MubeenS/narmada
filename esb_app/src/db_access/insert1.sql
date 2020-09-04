INSERT INTO `esb_db`.`routes`(sender,destination,message_type)
VALUES
('Send_A','Dest_a','CreditReport1'),
('Send_B','Dest_b','CreditReport2'),
('Send_C','Dest_c','CreditReport3'),
('Send_D','Dest_d','CreditReport4'),
('Send_E','Dest_e','CreditReport5');

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
