CREATE TABLE routes (
    route_id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
    sender VARCHAR(45) NOT NULL,
    destination VARCHAR(45) NOT NULL,
    message_type VARCHAR(45) NOT NULL,
    is_active BIT(1) NOT NULL,
    CONSTRAINT UK_sender_dest_msg_type 
    UNIQUE (sender,destination,message_type)
);
CREATE UNIQUE INDEX UK_sender_dest_msg_type 
ON routes(sender,destination,message_type);

CREATE TABLE transform_config (
    id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
    route_id INT NOT NULL,
    config_key VARCHAR(45) NOT NULL,
    config_value TEXT,
    CONSTRAINT fk_route
      FOREIGN KEY (route_id) 
      REFERENCES routes(route_id)
      ON DELETE CASCADE,
    CONSTRAINT route_idx UNIQUE (route_id),
    CONSTRAINT UK_route_config 
    UNIQUE (route_id,config_key,config_value)
);
CREATE UNIQUE INDEX route_idx 
ON transform_config(route_id);

CREATE UNIQUE INDEX UK_route_config 
ON transform_config(route_id,config_key,config_value);

CREATE TABLE transport_config (
    id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
    route_id INT,
    config_key VARCHAR(45),
    config_value TEXT,
    CONSTRAINT fk_route
      FOREIGN KEY (route_id) 
      REFERENCES routes(route_id)
      ON DELETE CASCADE,
    CONSTRAINT route_idx UNIQUE (route_id),
    CONSTRAINT UK_route_config 
    UNIQUE (route_id,config_key,config_value)
);
CREATE UNIQUE INDEX route_idx_tp 
ON transport_config(route_id);

CREATE UNIQUE INDEX UK_route_config_tp 
ON transport_config(route_id,config_key,config_value);

CREATE TABLE esb_request (
    id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
    sender_id VARCHAR(45) NOT NULL,
    dest_id VARCHAR(45) NOT NULL,
    message_type VARCHAR(45) NOT NULL,
    reference_id VARCHAR(45) NOT NULL,
    message_id VARCHAR(45) NOT NULL,
    received_on DATETIME NOT NULL,
    data_location TEXT,
    status VARCHAR(20) NOT NULL,
    status_details TEXT
);