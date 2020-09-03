esb: esb.c
	gcc esb.c ../bmd_assets/xml_handler.c ../db_access/insert_to_esb_request.c -o esb `mysql_config --cflags --libs` `xml2-config --cflags` `xml2-config --libs`