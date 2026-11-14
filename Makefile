CC     = gcc								#compilador a utilizar
CFLAGS = -std=c11 -Wall -Wextra -pedantic -O2		#muestran todas las advertencias utiles
OBJS   = main.o artemis.o validaciones.o	#archivos objeto: uno por cada archivo .c del proyecto

artemis: $(OBJS)								# Une los archivos objeto en el ejecutable final.  #enlaza la libreria matematica para usar sqrt y pow
	$(CC) $(CFLAGS) -o $@ $(OBJS) -lm 			
											
%.o: %.c artemis.h validaciones.h				#si se modifica un .h se recompilan todos los .o; si se modifica un .c,solo se recompila ese archivo.
	$(CC) $(CFLAGS) -c $<

clean:											# elimina los archivos generados durante la compilacion
	rm -f $(OBJS) artemis
