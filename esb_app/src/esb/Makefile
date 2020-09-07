DB_ACCESS = ../db_access/get_active_route_id.c ../db_access/has_transport_config.c ../db_access/has_transform_config.c ../db_access/insert_to_esb_request.c
XML_HANDLER = ../bmd_assets/xml_handler.c ../bmd_assets/is_bmd_valid.c
INCLUDE = `mysql_config --cflags --libs` `xml2-config --cflags` `xml2-config --libs`
test: test_esb.c valid.o
	gcc test_esb.c ${XML_HANDLER} ${SQL_API} -o test_esb ${DB_ACCESS} ${INCLUDE} ../test/munit.c ./esb.c
valid.o: ${XML_HANDLER} ../bmd_assets/bmd.h
	gcc -c ${DB_ACCESS} ${XML_HANDLER} ../bmd_assets/is_bmd_valid.c ${INCLUDE}
clean:
	rm *.o test_esb
