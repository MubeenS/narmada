MYSQL_LIB = `mysql_config --cflags --libs`

select: has_transport_config.c connector.h
	gcc has_transport_config.c -o get -std=c99 -g ${MYSQL_LIB}
