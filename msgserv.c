#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

typedef struct message_server{
  char name[50];
  u_int16_t udp_port;
  u_int16_t tcp_port;
  struct in_addr ip_addr;
};

int main(int argc, char** argv){

  char name[50];
  int upt = 0, tpt = 0;
  struct in_addr* ip;
  int i;
  int m, r, sipt;
  struct in_addr* siip;
  struct hostent *h;
  struct sockaddr_in sid; /*estruturas para os servidores de identidades e de mensagens*/
  struct message_server ms;

  if( argc < 9 ){
    printf("invalid number of arguments\n");
    exit(-1);
  }

  strcpy( name , argv[2] );
  upt = atoi( argv[6] );
  tpt = atoi( argv[8] );
  if( !inet_aton( argv[4] , ip ) ){
    exit(-1);
  }

  /*atribuir os parametros a uma variavel message_server*/
  strcpy(ms.name , name );
  ms.udp_port = upt;
  ms.tcp_port = tpt;
  ms.ip_addr = *ip;

  /*definir parametros opcionais, caso nao sejam dados na invocacao*/
  if((h = gethostbyname("tejo.tecnico.ulisboa.pt")) == NULL) exit(-1);
	siip = (struct in_addr*)h->h_addr_list[0];
  sipt = 59000;
  m = 200;
  r = 10;

  /*verificar quais os parametros opcionais que sao dados*/
  for(i = 9 ; i < argc && argc > 9 ; i+=2){
    if(!strcmp( argv[i] , "-i")){
      if( !inet_aton( argv[i+1] , siip ) ){
        exit(-1);
      }
    }
    else if(!strcmp( argv[i] , "-p")){
       sipt = atoi(argv[i+1]);
    }
    else if(!strcmp( argv[i] , "-m")){
       m = atoi(argv[i+1]);
    }
    else if(!strcmp( argv[i] , "-r")){
      r = atoi(argv[i+1]);
    }
  }

  sid.sin_addr=*siip;
  sid.sin_port=sipt;

  printf("MS -> name: %s, IP: %s, udp port: %d, tcp port: %d\n", ms.name, inet_ntoa(ms.ip_addr), ms.udp_port, ms.tcp_port);
  printf("SID -> IP: %s udo port: %d \n", inet_ntoa(sid.sin_addr), sid.sin_port);
  printf("maximo de mensagens: %d , intervalo de tempo: %d\n", m, r);

  return(0);

}
