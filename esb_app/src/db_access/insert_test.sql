source create_schema.sql;

INSERT INTO routes (sender,destination,message_type,is_active)
VALUES
  ('A','X','CreditReport',b'1'),
  ('A','Y','CreditReport',b'1'),
  ('A','Z','CreditReport',b'1'),
  ('B','X','CreditReport',b'1'),
  ('B','Y','CreditReport',b'1'),
  ('B','Z','CreditReport',b'1'),
  ('C','X','CreditReport',b'1'),
  ('C','Y','CreditReport',b'1'),
  ('C','Z','CreditReport',b'1'),
  ('A','X','AvlBal',b'1'),
  ('A','Y','AvlBal',b'1'),
  ('A','Z','AvlBal',b'1'),
  ('B','X','AvlBal',b'1'),
  ('B','Y','AvlBal',b'1'),
  ('B','Z','AvlBal',b'1'),
  ('C','X','AvlBal',b'1'),
  ('C','Y','AvlBal',b'1'),
  ('C','Z','AvlBal',b'1');

INSERT INTO transform_config(route_id,config_key,config_value) 
VALUES 
   (1,"config-a","config-1"),
   (2,"config-g","config-2"),
   (3,"config-ag","config-3"),
   (4,"config-b","config-1"),
   (5,"config-ab","config-3"),
   (6,"config-x","config-4"),
   (7,"config-ab","config-5"),
   (8,"config-ax","config-6"),
   (9,"config-ai","config-7");

INSERT INTO transport_config(route_id,config_key,config_value) 
VALUES 
   (1,"config-a","config-1"),
   (2,"config-g","config-2"),
   (3,"config-ag","config-3"),
   (4,"config-b","config-1"),
   (5,"config-ab","config-3"),
   (6,"config-x","config-4"),
   (7,"config-ab","config-5"),
   (8,"config-ax","config-6"),
   (9,"config-ai","config-7");
