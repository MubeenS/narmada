parse: xml_handler.c bmd.h
	gcc ../db_access/select_active_routes.c ./xml_handler.c is_bmd_valid.c -o valid `mysql_config --cflags --libs` `xml2-config --cflags` `xml2-config --libs`