INSERT INTO `esb_db`.`routes`(sender,destination,message_type,is_active)
VALUES
('Send_A','Dest_a','CreditReport1',1),
('Send_B','Dest_b','CreditReport2',1),
('Send_C','Dest_c','CreditReport3',1),
('Send_D','Dest_d','CreditReport4',1),
('Send_E','Dest_e','CreditReport5',1);

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
