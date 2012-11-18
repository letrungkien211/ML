CC = g++
CFLAGS	= 
LDFLAGS	=
#INCLUDES = -I/usr/local/include/opencv
#LIBS	= -L/usr/local/lib -lcxcore -lcv -lhighgui -lcvaux -lml
INCLUDES  = ${shell pkg-config opencv --cflags} 
LIBS += ${shell pkg-config opencv --libs}
TARGET	= knntest
OBJS	= main.o myknn.o myutils.o

all:	$(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS) $(LIBS)

clean:
	-rm -f $(TARGET) $(OBJS) *~

.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $<


