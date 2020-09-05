XML_HANDLER = ../bmd_assets/xml_handler.c ../bmd_assets/is_bmd_valid.c
SQL_API     = ../db_access/insert_to_esb_request.c ../db_access/select_active_routes.c
XML_LIB     =   `xml2-config --cflags` `xml2-config --libs`
SQL_LIB     =  `mysql_config --cflags --libs`
esb: esb.c
	gcc esb.c ${XML_HANDLER} ${SQL_API} -o esb $(SQL_LIB) ${XML_LIB}