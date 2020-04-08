# target shared library
ObjectFiles := $(patsubst %.c, %.o, $(wildcard *.c))
libPwn.so: $(ObjectFiles)
	gcc $(ObjectFiles) -shared -o libPwn.so

# compile every object files
ObjectFlags := -c -fPIC

PwnType.o: PwnType.h PwnType.c PwnIO.h PwnShell.h PwnError.h PwnSendFormat.h PwnRecvFormat.h
	gcc PwnType.c $(ObjectFlags)

PwnError.o: PwnError.h PwnError.c
	gcc PwnError.c $(ObjectFlags)

PwnFcntl.o: PwnFcntl.h PwnFcntl.c PwnError.h
	gcc PwnFcntl.c $(ObjectFlags)

PwnIO.o: PwnIO.h PwnIO.c PwnVB.h PwnDef.h PwnError.h PwnIOLocal.h PwnIORemote.h PwnIOTerminal.h
	gcc PwnIO.c $(ObjectFlags)

PwnIOLocal.o: PwnIOLocal.h PwnIOLocal.c PwnError.h
	gcc PwnIOLocal.c $(ObjectFlags)

PwnIORemote.o: PwnIORemote.h PwnIORemote.c PwnError.h
	gcc PwnIORemote.c $(ObjectFlags)

PwnIOTerminal.o: PwnIOTerminal.h PwnIOTerminal.c PwnError.h
	gcc PwnIOTerminal.c $(ObjectFlags)

PwnMisc.o: PwnMisc.h PwnMisc.c PwnDef.h PwnError.h
	gcc PwnMisc.c $(ObjectFlags)

PwnRecv.o: PwnRecv.h PwnRecv.c PwnIO.h PwnMisc.h PwnError.h PwnFcntl.h
	gcc PwnRecv.c $(ObjectFlags)

PwnRecvTimes.o: PwnRecvTimes.h PwnRecvTimes.c PwnIO.h PwnDef.h PwnMisc.h PwnError.h PwnFcntl.h
	gcc PwnRecvTimes.c $(ObjectFlags)

PwnRecvFormat.o: PwnRecvFormat.h PwnRecvFormat.c PwnIO.h PwnMisc.h PwnRecv.h PwnError.h PwnRecvTimes.h
	gcc PwnRecvFormat.c $(ObjectFlags)

PwnSend.o: PwnSend.h PwnSend.c PwnIO.h PwnDef.h PwnError.h
	gcc PwnSend.c $(ObjectFlags)

PwnSendTimes.o: PwnSendTimes.h PwnSendTimes.c PwnIO.h PwnDef.h
	gcc PwnSendTimes.c $(ObjectFlags)

PwnSendFormat.o: PwnSendFormat.h PwnSendFormat.c PwnIO.h PwnMisc.h PwnSend.h PwnError.h PwnSendTimes.h
	gcc PwnSendFormat.c $(ObjectFlags)

PwnShell.o: PwnShell.h PwnShell.c PwnIO.h PwnVB.h PwnDef.h PwnError.h PwnFcntl.h
	gcc PwnShell.c $(ObjectFlags)
