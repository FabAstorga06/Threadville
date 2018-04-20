#include "constants.h"

#define BUFFER_SIZE 8
#define PORT 8888
static char* ip_addr = "127.0.0.1";
//char* command = "python ui/threadville.py";

/*****************************************************************************/
int send_msg(int sckt, char* msg ) {
    size_t len;
    int response;
    len = strlen(msg);

    response = send(sckt, msg, BUFFER_SIZE, 0);

    if (response <= 0 )  {
        perror("Send message error...");
        return (-1);
    }

    return (1);
}
/*****************************************************************************/

int main(int argc, char* argv[] ) {
  /* execute socket client in Python in order to listen */
//  system(command);

  /* Create server socket */
  int sockfd = 0, n = 0;
  struct sockaddr_in serv_addr;

  if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)  {
    printf("\n Error : Could not create socket \n");
    return 1;
  }
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(PORT);
  serv_addr.sin_addr.s_addr = inet_addr(ip_addr);

  if(connect(sockfd, (struct sockaddr *)(&serv_addr), sizeof(serv_addr)) < 0) {
    printf("\n Error : Connect Failed \n");
    return 1;
  }

  while(1)  {
      send_msg(sockfd, "HOLAAAAAA");
      sleep(1);
  }

  if( n < 0 ) printf("\n Read Error \n");

  return 0;
}
