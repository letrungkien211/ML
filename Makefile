CC = g++
RM = rm -f
CD = cd
CP = cp 


CFLAGS	= -Wall -g -O2
INCLUDES=	`pkg-config opencv --cflags` \
		-I/usr/include/eigen3

LIBS = `pkg-config opencv --libs`

TARGET	= digitreg
OBJS 	= utils.o bpnn.o data.o
all:	$(TARGET)


$(TARGET): % :  $(OBJS) %.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS) 

.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $< 
clean:
	$(RM)  $(TARGET) $(OBJS) *.o *~



