source create_schema.sql;

INSERT INTO routes (sender,destination,message_type,is_active)
VALUES
  ('A','X','xml',b'1'),
  ('A','Y','xml',b'1'),
  ('A','Z','xml',b'1'),
  ('B','X','xml',b'1'),
  ('B','Y','xml',b'1'),
  ('B','Z','xml',b'1'),
  ('C','X','xml',b'1'),
  ('C','Y','xml',b'1'),
  ('C','Z','xml',b'1'),
  ('A','X','json',b'1'),
  ('A','Y','json',b'1'),
  ('A','Z','json',b'1'),
  ('B','X','json',b'1'),
  ('B','Y','json',b'1'),
  ('B','Z','json',b'1'),
  ('C','X','json',b'1'),
  ('C','Y','json',b'1'),
  ('C','Z','json',b'1');

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
