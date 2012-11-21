CC = g++
RM = rm -f
CD = cd
MLDIR = $(HOME)/Dropbox/git/ML


CFLAGS	= -Wall -g -O2
INCLUDES=	`pkg-config opencv --cflags` \
		-I/usr/include/eigen3	\
		-I$(MLDIR)/Utils \
		-I$(MLDIR)/BPNN \
		-I$(MLDIR)/Data 
LIBS = `pkg-config opencv --libs`

TARGET	= digitreg
OBJS 	= $(MLDIR)/Utils/utils.o $(MLDIR)/BPNN/bpnn.o $(MLDIR)/Data/data.o
all:	$(TARGET)


$(TARGET): % :  $(OBJS) %.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS) 

.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $< 


clean:
	$(RM)  $(TARGET) $(OBJS) *.o *~



