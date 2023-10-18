server:server.o message_processing.o user_linkedlist.o wrap.o
	gcc -o server server.o message_processing.o user_linkedlist.o wrap.o
server.o:server.c message_processing.h user_linkedlist.h wrap.h
	gcc -c server.c
message_processing.o:message_processing.c user_linkedlist.h wrap.h administrator.h
	gcc -c message_processing.c
user_linkedlist.o:user_linkedlist.c user_linkedlist.h
	gcc -c user_linkedlist.c
wrap.o:wrap.c
	gcc -c wrap.c
clean:
	rm -f *.o
