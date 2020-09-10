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
  ('A','X','PO',b'1'),
  ('A','Y','PO',b'1'),
  ('A','Z','PO',b'1'),
  ('B','X','PO',b'1'),
  ('B','Y','PO',b'1'),
  ('B','Z','PO',b'1'),
  ('C','X','PO',b'1'),
  ('C','Y','PO',b'1'),
  ('C','Z','PO',b'1');

INSERT INTO transform_config(route_id,config_key,config_value) 
VALUES 
   (1,"config-a","json"),
   (2,"config-g","json"),
   (3,"config-ag","json"),
   (4,"config-b","json"),
   (5,"config-ab","json"),
   (6,"config-x","json"),
   (7,"config-ab","json"),
   (8,"config-ax","json"),
   (9,"config-ai","json");

INSERT INTO transport_config(route_id,config_key,config_value) 
VALUES 
   (1,"config-a","email"),
   (2,"config-g","email"),
   (3,"config-ag","email"),
   (4,"config-b","email"),
   (5,"config-ab","email"),
   (6,"config-x","email"),
   (7,"config-ab","email"),
   (8,"config-ax","email"),
   (9,"config-ai","email");
