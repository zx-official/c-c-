client:client.o home_page.o processing_terminal_message.o processing_server_message.o wrap.o 
	gcc -o client client.o home_page.o processing_terminal_message.o processing_server_message.o wrap.o 
client.o:client.c home_page.h processing_terminal_message.h processing_server_message.h wrap.h
	gcc -c client.c 
home_page.o:home_page.c home_page.h wrap.h	
	gcc -c home_page.c
processing_terminal_message.o:processing_terminal_message.c home_page.h wrap.h
	gcc -c processing_terminal_message.c
processing_server_message.o:processing_server_message.c processing_terminal_message.h home_page.h wrap.h
	gcc -c processing_server_message.c
wrap.o:wrap.c
	gcc -c wrap.c
clean:
	rm -f *.o

