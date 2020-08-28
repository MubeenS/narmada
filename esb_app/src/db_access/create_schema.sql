.open test.db
CREATE TABLE routes (
    route_id INT PRIMARY KEY,
    sender VARCHAR(45) NOT NULL UNIQUE,
    destination VARCHAR(45) NOT NULL UNIQUE,
    message_type VARCHAR(45) NOT NULL,
    is_active BIT(1) NOT NULL
);
CREATE INDEX UK_sender_dest_msg_type 
ON routes(sender,destination,message_type);

CREATE TABLE transform_config (
    id INT PRIMARY KEY,
    route_id INT NOT NULL,
    config_key VARCHAR(45) NOT NULL,
    config_value TEXT,
    CONSTRAINT fk_route
      FOREIGN KEY (route_id) 
      REFERENCES routes(route_id)
      ON DELETE CASCADE
);
CREATE INDEX route_idx 
ON transform_config(route_id);

CREATE INDEX UK_route_config 
ON transform_config(route_id,config_key,config_value);

CREATE TABLE transport_config (
    id INT PRIMARY KEY,
    route_id INT,
    config_key VARCHAR(45),
    config_value TEXT,
    CONSTRAINT fk_route
      FOREIGN KEY (route_id) 
      REFERENCES routes(route_id)
      ON DELETE CASCADE
);
CREATE INDEX route_idx_tp 
ON transport_config(route_id);

CREATE INDEX UK_route_config_tp 
ON transport_config(route_id,config_key,config_value);


CREATE TABLE esb_request (
    id INT PRIMARY KEY,
    sender_id VARCHAR(45) NOT NULL,
    dest_id VARCHAR(45) NOT NULL,
    message_type VARCHAR(45) NOT NULL,
    reference_id VARCHAR(45) NOT NULL,
    message_id VARCHAR(45) NOT NULL,
    received_on DATETIME NOT NULL,
    data_location TEXT,
    curr_status VARCHAR(20),
    status_details TEXT
)


