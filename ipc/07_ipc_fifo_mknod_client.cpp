/**
 * Esempio di
 * File Type    Description
 * S_IFBLK      Block special
 * S_IFCHR      Character special
 * S_IFIFO      FIFO special
 * S_IFREG      Regular file
 * S_IFDIR      Directory
 * S_IFLNK      Symbolic Link
 *
 * File Mode    Description
 * S_IRWXU      Read, write, execute/search by owner
 * S_IRUSR      Read permission, owner
 * S_IWUSR      Write permission, owner
 * S_IXUSR      Execute/search permission, owner
 * S_IRWXG      Read, write, execute/search by group
 * S_IRGRP      Read permission, group
 * S_IWGRP      Write permission, group
 * S_IXGRP      Execute/search permission, group
 * S_IRWXO      Read, write, execute/search by others
 * S_IROTH      Read permission, others
 * S_IWOTH      Write permission, others
 * S_IXOTH      Execute/search permission, others
 *
 */

#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>

using namespace std;

int main()
{
    int fd;

    // Configurazione del path della FIFO
    char fifoPath[] = "/tmp/r2d2Fifo";

    // Creazione della FIFO mediante la chiamata mknod.
    // mknod(const char *pathname, mode_t mode, dev_t dev)
    // mknod(fifoPath, S_IFIFO | S_IRUSR | S_IWUSR, 0);

    // char sndMsg[80], rcvMsg[80];
    char sndMsg[80];

    cout << "Apertura della FIFO" << endl;
    // Apertura della FIFO in sola scrittura
    fd = open(fifoPath, O_CREAT | O_WRONLY);

    while (1)
    {
        cout << "Inserisci il messaggio da inviare: ";
        cin.getline(sndMsg, 80);
        if (write(fd, sndMsg, strlen(sndMsg)) >= 0)
        {
            cout << "Messaggio inviato." << endl;
        }
        else
        {
            cerr << "Errore nell'invio del messaggio." << endl;
            perror("Details");
        }

        if (strcmp(sndMsg, "stop") == 0)
        {
            close(fd);
            break;
        }
    }
    return 0;
}
