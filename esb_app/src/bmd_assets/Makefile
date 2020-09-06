DB_ACCESS = ../db_access/get_active_route_id.c ../db_access/has_transport_config.c ../db_access/has_transform_config.c
XML_HANDLER = ./xml_handler.c ./is_bmd_valid.c
INCLUDE = `mysql_config --cflags --libs` `xml2-config --cflags` `xml2-config --libs`
parse: xml_handler.c bmd.h
	gcc  ${DB_ACCESS} ${XML_HANDLER} test_bmd.c -o test ${INCLUDE} ../test/munit.c