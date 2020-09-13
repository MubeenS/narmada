source create_schema.sql;

INSERT INTO routes (sender,destination,message_type,is_active)
VALUES
  ('A','https://reqres.in/api/users','CreditReport',b'1'),
  ('B','https://reqres.in/api/users','CreditReport',b'1'),
  ('C','https://reqres.in/api/users','CreditReport',b'1'),
  ('D','https://reqres.in/api/users','CreditReport',b'1'),
  ('E','https://reqres.in/api/users','CreditReport',b'1'),
  ('F','testmailtm02@gmail.com','CreditReport',b'1'),
  ('G','testmailtm02@gmail.com','CreditReport',b'1'),
  ('H','testmailtm02@gmail.com','CreditReport',b'1'),
  ('I','testmailtm02@gmail.com','CreditReport',b'1'),
  ('J','testmailtm02@gmail.com','CreditReport',b'1'),
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
   (1,"IFSC","No Transform"),
   (2,"IFSC","No Transform"),
   (3,"IFSC","No Transform"),
   (4,"IFSC","No Transform"),
   (5,"IFSC","No Transform"),
   (6,"IFSC","No Transform"),
   (7,"IFSC","No Transform"),
   (8,"IFSC","No Transform"),
   (9,"IFSC","No Transform");

INSERT INTO transport_config(route_id,config_key,config_value) 
VALUES 
   (1,"API_URL","https://ifsc.razorpay.com/"),
   (2,"API_URL","https://ifsc.razorpay.com/"),
   (3,"API_URL","https://ifsc.razorpay.com/"),
   (4,"API_URL","https://ifsc.razorpay.com/"),
   (5,"API_URL","https://ifsc.razorpay.com/"),
   (6,"API_URL","https://ifsc.razorpay.com/"),
   (7,"API_URL","https://ifsc.razorpay.com/"),
   (8,"API_URL","https://ifsc.razorpay.com/"),
   (9,"API_URL","https://ifsc.razorpay.com/");

