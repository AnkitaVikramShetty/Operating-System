#include <xinu.h>
#include <string.h>
#include <stdio.h>

shellcmd xsh_xinuclient(int nargs, char *args[]) {
	uint32 remoteip;
	dot2ip("192.168.1.100",&remoteip);	/* remote IP address to use	*/
	int	i;				/* index into buffer		*/
	int	retval;				/* return value			*/
	char	msg[] = "Xinu testing Linux server"; /* message to send	*/
	char	inbuf[1500];			/* buffer for incoming reply	*/
	int32	slot;				/* UDP slot to use		*/
	int32	msglen;				/* length of outgoing message	*/
	uint16	echoport= 8888;			/* port number for UDP echo	*/
	uint16	locport	= 52743;		/* local port to use		*/
	int32	retries	= 6;			/* number of retries		*/
	int32	delay	= 2000;			/* reception delay in ms	*/
	
	/* register local UDP port */
	slot = udp_register(remoteip, echoport, locport);
	if (slot == SYSERR) {
		fprintf(stderr, "%s: could not reserve UDP port %d\n",
				args[0], locport);
		return 1;
	}

	/* Retry sending outgoing datagram and getting response */
	msglen = strnlen(msg, 1200);
	for (i=0; i<retries; i++) {
		retval = udp_send(slot, msg, msglen+10);
		if (retval == SYSERR) {
			fprintf(stderr, "%s: error sending UDP \n",
				args[0]);
			return 1;
		}

		retval = udp_recv(slot, inbuf, sizeof(inbuf), delay);
		if (retval == TIMEOUT) {
			fprintf(stderr, "%s: timeout...\n", args[0]);
			continue;
		} else if (retval == SYSERR) {
			fprintf(stderr, "%s: error from udp_recv \n",
				args[0]);
			udp_release(slot);
			return 1;
		}
		break;
	}

	udp_release(slot);
	if (retval == TIMEOUT) {
		fprintf(stderr, "%s: retry limit exceeded\n",
			args[0]);
		return 1;
	}

	printf("UDP echo test was successful\n");
	printf("Received value is %d\n", atoi(inbuf));
	return 0;
}
