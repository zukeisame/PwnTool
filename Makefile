all: $(wildcard *.o)

PwnType.o: PwnType.h PwnType.c PwnIO.h PwnShell.h PwnError.h PwnSendFormat.h PwnRecvFormat.h
	gcc -c PwnType.c

PwnError.o: PwnError.h PwnError.c
	gcc -c PwnError.c

PwnFcntl.o: PwnFcntl.h PwnFcntl.c PwnError.h
	gcc -c PwnFcntl.c

PwnIO.o: PwnIO.h PwnIO.c PwnVB.h PwnDef.h PwnError.h PwnIOLocal.h PwnIORemote.h PwnIOTerminal.h
	gcc -c PwnIO.c

PwnIOLocal.o: PwnIOLocal.h PwnIOLocal.c PwnError.h
	gcc -c PwnIOLocal.c

PwnIORemote.o: PwnIORemote.h PwnIORemote.c PwnError.h
	gcc -c PwnIORemote.c

PwnIOTerminal.o: PwnIOTerminal.h PwnIOTerminal.c PwnError.h
	gcc -c PwnIOTerminal.c

PwnMisc.o: PwnMisc.h PwnMisc.c PwnDef.h
	gcc -c PwnMisc.c

PwnPause.o: PwnPause.h PwnPause.c
	gcc -c PwnPause.c

PwnRecv.o: PwnRecv.h PwnRecv.c PwnIO.h PwnMisc.h PwnError.h PwnFcntl.h
	gcc -c PwnRecv.c

PwnRecvTimes.o: PwnRecvTimes.h PwnRecvTimes.c PwnIO.h PwnDef.h PwnMisc.h PwnError.h PwnFcntl.h
	gcc -c PwnRecvTimes.c

PwnRecvFormat.o: PwnRecvFormat.h PwnRecvFormat.c PwnIO.h PwnMisc.h PwnRecv.h PwnError.h PwnRecvTimes.h
	gcc -c PwnRecvFormat.c

PwnSend.o: PwnSend.h PwnSend.c PwnIO.h PwnDef.h PwnError.h
	gcc -c PwnSend.c

PwnSendTimes.o: PwnSendTimes.h PwnSendTimes.c PwnIO.h PwnDef.h
	gcc -c PwnSendTimes.c

PwnSendFormat.o: PwnSendFormat.h PwnSendFormat.c PwnIO.h PwnMisc.h PwnSend.h PwnError.h PwnSendTimes.h
	gcc -c PwnSendFormat.c

PwnShell.o: PwnShell.h PwnShell.c PwnIO.h PwnVB.h PwnDef.h PwnSleep.h PwnError.h PwnFcntl.h
	gcc -c PwnShell.c

PwnSleep.o: PwnSleep.h PwnSleep.c PwnError.h
	gcc -c PwnSleep.c
