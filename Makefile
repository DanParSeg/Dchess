CC = "g++"
PROJECT = dchess

SRC = src/main.cpp src/board.cpp src/pieceSprites.cpp src/piece.cpp src/fenParser.cpp src/chessGame.cpp

LIBS = -lsfml-graphics -lsfml-window -lsfml-system

build/$(PROJECT) : $(SRC)
	$(CC) $(SRC) -o build/$(PROJECT) $(LIBS)

clean :
	rm -rf *.o build/$(PROJECT)
