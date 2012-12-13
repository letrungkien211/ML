CC = g++
RM = rm -f
GIT= git 

CFLAGS	= -Wall -g -O2
LDFLAGS	= -Wall -g -O2
INCLUDES= ${shell pkg-config opencv --cflags} \
	-I/usr/include/eigen3	\
	-I../BPNN/
LIBS += ${shell pkg-config opencv --libs}

TARGET	= recognition
OBJS = ../BPNN/bpnn.o ../BPNN/myeigen.o
all:	$(TARGET)


$(TARGET): % : %.o $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^ $(LIBS)

clean:
	$(RM)  $(TARGET) $(OBJS) *.o *~

.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<


