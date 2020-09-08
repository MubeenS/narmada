DB_ACCESS =  ./insert_to_esb_request.c ./get_active_route_id.c ./has_transport_config.c ./has_transform_config.c
XML_HANDLER = ../bmd_assets/xml_handler.c ../bmd_assets/is_bmd_valid.c
INCLUDE = `mysql_config --cflags --libs` `xml2-config --cflags` `xml2-config --libs`
<<<<<<< HEAD
fetch: select_new_esb_request.c
	gcc  ${DB_ACCESS} ${XML_HANDLER} select_new_esb_request.c -o fetch ${INCLUDE}
=======
test: test_db_access.c
	gcc  ${DB_ACCESS} ${XML_HANDLER} test_db_access.c -o test ${INCLUDE} ../test/munit.c
>>>>>>> 18a840062cda03baacc7a33fad7659413c5b2543
clean:
	rm fetch