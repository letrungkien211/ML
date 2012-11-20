CC = g++
RM = rm -f
CFLAGS	= -Wall -g -O2

INCLUDES  = 	`pkg-config opencv --cflags` \
		-I/usr/include/eigen3 \
		-I../Utils



LIBS = `pkg-config opencv --libs`

TARGET	= image2matrix
OBJS = data.o ../Utils/utils.o

all:	$(TARGET)


$(TARGET): % : %.o $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)


.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<


clean:
	$(RM) $(TARGET) $(OBJS) *.o *~ *#*


