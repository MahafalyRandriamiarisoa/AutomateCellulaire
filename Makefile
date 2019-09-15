

# compilateur
CC := gcc
# options de compilation
CFLAGS := -std=c99 -Wall -Wextra -pedantic -ggdb -Wno-unused-but-set-parameter -Wno-unused-variable -Wno-unused-parameter -Wno-abi

# DPROJ = ../AutomateCellulaire
# DPROJ = . 

# repertoire de sortie
DOUT = out

# nom de l'executable
BIN = $(DOUT)/exe

# liste des objets (.o)
OBJS = $(DOUT)/main.o $(DOUT)/automate.o

# liste des dependances (header)
DEPS = header/automate.h

# INCLUDES = -I $(DPROJ)
# règle de compilation --- exécutables

$(BIN) : $(OBJS)
	$(CC) $(OBJS) -o $(BIN)

$(DOUT)/main.o : main.c $(DEPS)
	$(CC) $(CFLAGS) -c  main.c -o $(DOUT)/main.o

$(DOUT)/automate.o : src/automate.c $(DEPS)
	$(CC) $(CFLAGS) -c src/automate.c -o $(DOUT)/automate.o

memoire : $(BIN)
	valgrind --leak-check=full ./$(BIN)

exe : 
	@./$(BIN)

# options de compilation
clean:
	rm -r $(BIN) $(DOUT)/*.o 
 
#mention speciale à : http://www.bien-programmer.fr/make.htm