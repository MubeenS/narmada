DB_ACCESS = ../db_access/get_active_route_id.c ../db_access/has_transport_config.c ../db_access/has_transform_config.c
XML_HANDLER = ./xml_handler.c
INCLUDE = `mysql_config --cflags --libs` `xml2-config --cflags` `xml2-config --libs`
test: test_bmd.c
	gcc "../test/munit.c" test_bmd.c -o test "./xml_handler.c" ${XML_HANDLER} ${INCLUDE}