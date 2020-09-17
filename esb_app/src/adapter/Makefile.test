ADAPTER = ./email.c ./http_post.c 
test_adapter: test_adapter.c	
	gcc ${ADAPTER} test_adapter.c -lcurl -o test_adapter ../test/munit.c
