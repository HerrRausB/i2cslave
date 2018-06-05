TARGET=i2ctest
TARGETDIR = /usr/local/bin

CC = gcc
CCFLAGS =

LD = gcc
LDFLAGS =
#LIBS = -lpigpio -lrt
LIBS =

SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)

$(TARGET): $(OBJ)
	$(LD) $(LDFLAGS) -o $@ $^ $(LIBS) 
	sudo cp $(TARGET) $(TARGETDIR)

clean:
	rm -f $(OBJ) $(TARGET)
	
rebuild: clean $(TARGET)

run: $(TARGET)
	sudo $(TARGET)