

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
OBJS = $(DOUT)/main.o $(DOUT)/automate.o $(DOUT)/termcap_initializer.o $(DOUT)/utils.o $(DOUT)/pgm_img.o 

# liste des dependances (header)
DEPS = header/automate.h header/termcap_initializer.h header/utils.h header/pgm_img.h 

# options de compilation (lien vers certaine library)
OPT = -ltermcap -lncurses -lm
# INCLUDES = -I $(DPROJ)
# règle de compilation --- exécutables

$(BIN) : $(OBJS)
	$(CC) $(OBJS) -o $(BIN) $(OPT)

$(DOUT)/main.o : main.c $(DEPS)
	$(CC) $(CFLAGS) -c  main.c -o $(DOUT)/main.o

$(DOUT)/automate.o : src/automate.c $(DEPS)
	$(CC) $(CFLAGS) -c src/automate.c -o $(DOUT)/automate.o 

$(DOUT)/termcap_initializer.o : src/termcap_initializer.c $(DEPS)
	$(CC) $(CFLAGS) -c src/termcap_initializer.c -o $(DOUT)/termcap_initializer.o 

$(DOUT)/utils.o : src/utils.c $(DEPS)
	$(CC) $(CFLAGS) -c src/utils.c -o $(DOUT)/utils.o 

$(DOUT)/pgm_img.o : src/pgm_img.c $(DEPS)
	$(CC) $(CFLAGS) -c src/pgm_img.c -o $(DOUT)/pgm_img.o 

# $(DOUT)/differentsRules.o : src/differentsRules.c $(DEPS)
# 	$(CC) $(CFLAGS) -c src/differentsRules.c -o $(DOUT)/differentsRules.o 

# $(DOUT)/RuleStrategy.o : src/RuleStrategy.c $(DEPS)
# 	$(CC) $(CFLAGS) -c src/RuleStrategy.c -o $(DOUT)/RuleStrategy.o 

memoire : $(BIN)
	valgrind --leak-check=full ./$(BIN)
	# valgrind --leak-check=full --show-leak-kinds=all ./$(BIN)
	# valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(BIN)

memoire2 : $(BIN)
	valgrind --leak-check=full --show-leak-kinds=all ./$(BIN) sc

exe : 
	@./$(BIN) std

fexe : 
	@./$(BIN) fcy

pgm : 
	@./$(BIN) pgm
	
bonus : 
	@./$(BIN) sc
# options de compilation
clean:
	rm -r $(BIN) $(DOUT)/*.o 

cleanPgm : 
	rm *.pgm
 
#mention speciale à : http://www.bien-programmer.fr/make.htm