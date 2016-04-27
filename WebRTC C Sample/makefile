SOURCES = ./WebRTC_MicroStackSample.c ./SimpleRendezvousServer.c core/utils.c 
SOURCES += Microstack/ILibAsyncServerSocket.c Microstack/ILibAsyncUDPSocket.c Microstack/ILibWebClient.c Microstack/ILibAsyncSocket.c Microstack/ILibParsers.c Microstack/ILibWebServer.c Microstack/ILibWebRTC.c Microstack/ILibWrapperWebRTC.c Microstack/ILibRemoteLogging.c Microstack/ILibProcessPipe.c
SOURCES += $(ADDITIONALSOURCES)

PATH_ARM5 = /home/default/Public/ToolChains/LinuxArm/bin/

OBJECTS = $(patsubst %.c,%.o, $(SOURCES))

EXENAME = webrtc_sample_linux

# Compiler command name
CC = gcc

# need to be separate for dependency generation	
INCDIRS = -I. -Iopenssl/include -Imicrostack -Icore

CFLAGS  ?= -g -Wall -D_POSIX -D_DEBUG -DMICROSTACK_PROXY -fno-strict-aliasing $(INCDIRS)
LDFLAGS ?= -Lopenssl-static/x86 -L. -lpthread -ldl -lssl -lsqlite3 -lz -lutil -lcrypto -lrt

.PHONY: all clean

all: $(EXENAME)

$(EXENAME): $(OBJECTS)
	$(V)$(CC) $^ $(LDFLAGS) -o $@

release:
	$(MAKE) $(MAKEFILE) EXENAME=$(EXENAME) INCDIRS="-I. -Iopenssl/include -Imicrostack -Icore" CFLAGS="-O2 -Wall -D_POSIX -D_DEBUG -D_DAEMON -DMICROSTACK_PROXY -fno-strict-aliasing $(INCDIRS)" LDFLAGS="-Lopenssl-static/x86 -L. -lpthread -ldl -lssl -lz -lutil -lcrypto -ljpeg -lX11 -lXtst -lrt"
	strip ./$(EXENAME)

clean:
	rm -f *.o
	rm -f core/*.o
	rm -f Microstack/*.o

cleanbin:
	-rm -f webrtc_sample_linux_arm*
	-rm -f webrtc_sample_linux_x64*
	-rm -f webrtc_sample_linux_x86*

depend: $(SOURCES)
	$(CC) -M $(CFLAGS) $(SOURCES) $(HEADERS) > depend
	
linux-32:
	$(MAKE) $(MAKEFILE) EXENAME="webrtc_sample_linux_x86" INCDIRS="-I. -Iopenssl/include -Imicrostack -Icore" CFLAGS="-m32 -O2 -Wall -D_POSIX -D_DEBUG -D_DAEMON -DMICROSTACK_PROXY -fno-strict-aliasing $(INCDIRS)" LDFLAGS="-m32 -Lopenssl-static/x86 -L. -lpthread -Wl,--no-as-needed -ldl -lssl -lutil -lcrypto -lrt"
	strip ./webrtc_sample_linux_x86

linux-64:
	$(MAKE) $(MAKEFILE) EXENAME="webrtc_sample_linux_x64" INCDIRS="-I. -Iopenssl/include -Imicrostack -Icore" CFLAGS="-O2 -Wall -D_POSIX -D_DEBUG -D_DAEMON -DMICROSTACK_PROXY -D_REMOTELOGGING -D_REMOTELOGGINGSERVER -fno-strict-aliasing $(INCDIRS)" LDFLAGS="-Lopenssl-static/x86-64 -L. -lpthread -Wl,--no-as-needed -ldl -lssl -lutil -lcrypto -lrt" 
	strip ./webrtc_sample_linux_x64

linux-arm:
	$(MAKE) $(MAKEFILE) EXENAME="webrtc_sample_linux_arm" CC=$(PATH_ARM5)"arm-none-linux-gnueabi-gcc" INCDIRS="-I. -Iopenssl/include -Imicrostack -Icore" CFLAGS="-O2 -Wall -D_POSIX -D_DEBUG -D_DAEMON -DMICROSTACK_PROXY -fno-strict-aliasing $(INCDIRS)" LDFLAGS="-Lopenssl-static/arm -L. -lpthread -Wl,--no-as-needed -ldl -lssl -lutil -lcrypto -lrt"
	$(PATH_ARM5)arm-none-linux-gnueabi-strip ./webrtc_sample_linux_arm


