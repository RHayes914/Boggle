#spellchecker Makefile
CC = g++
CFLAGS = -g -Wall

all:boggle

boggle:main.o Lexicon.o BogglePieceGenerator.o ConsoleInterface.o ComputerPlayer.o BoggleBoard.o
	$(CC) $(CFLAGS) -o boggle main.o Lexicon.o BogglePieceGenerator.o ConsoleInterface.o ComputerPlayer.o BoggleBoard.o

main.o:main.cpp Lexicon.h BogglePieceGenerator.h ConsoleInterface.h ComputerPlayer.o
	$(CC) $(CFLAGS) -c main.cpp

Lexicon.o:Lexicon.cpp Lexicon.h
	$(CC) $(CFLAGS) -c Lexicon.cpp

BogglePieceGenerator.o:BogglePieceGenerator.cpp BogglePieceGenerator.h
	$(CC) $(CFLAGS) -c BogglePieceGenerator.cpp

ConsoleInterface.o:ConsoleInterface.cpp ConsoleInterface.h BoggleBoard.h
	$(CC) $(CFLAGS) -c ConsoleInterface.cpp

ComputerPlayer.o:ComputerPlayer.cpp ComputerPlayer.h Lexicon.h BoggleBoard.h
	$(CC) $(CFLAGS) -c ComputerPlayer.cpp

BoggleBoard.o:BoggleBoard.cpp BoggleBoard.h
	$(CC) $(CFLAGS) -c BoggleBoard.cpp

ConsoleInterface.h:BoggleBoard.h

clean:
	rm -f boggle *.o *.~ *.gch comp* human* callgrind*
