#include "exp1.h"
#include "exp1lib.h"
#include <stdbool.h>
#include <pthread.h>

#define MAXCHILD 1200

bool echoBackLoop(int sock){
    char buf[1024];

  while(1){
    int ret = recv(sock, buf,1024,0);
    write(1,buf,ret);
    if(ret == 0){
      break;
    }
    send(sock,buf,ret,0);
  }
}



// thread function
void* thread_func(void *arg) {

 int* accP = (int*)arg;
 int acc = *accP;
 free(accP);

 pthread_detach(pthread_self());

 // echoBackLoop関数は自分で作成すること
 echoBackLoop(acc);
 close(acc);

 pthread_exit(NULL);
}

void acceptLoop(int sock) {
 while (true) {
  struct sockaddr_storage from;
  socklen_t len = sizeof(from);
  int acc = 0;
  if ((acc = accept(sock, (struct sockaddr *) &from, &len)) == -1) {
   // エラー処理
   if (errno != EINTR) {
    perror("accept");
   }
  } else {
   // クライアントからの接続が行われた場合
   char hbuf[NI_MAXHOST];
   char sbuf[NI_MAXSERV];
   getnameinfo((struct sockaddr *) &from, len, hbuf,
     sizeof(hbuf), sbuf, sizeof(sbuf),
     NI_NUMERICHOST | NI_NUMERICSERV);
   fprintf(stderr, "accept:%s:%s\n", hbuf, sbuf);

   // スレッド生成
   int* param = (int*)malloc(sizeof(int));
   *param = acc;
   pthread_t th;
   if ( pthread_create(&th, NULL, thread_func, param) != 0 ) {
    perror("pthread_create");
    close(acc); // 切断
   }
  }
 }
}


int main(void){
    int sock_listen;
    int sock_client;
    struct sockaddr addr;
    int len = 0;
    
	sock_listen = exp1_tcp_listen(11111);
	sock_client = accept(sock_listen, &addr, (socklen_t*) &len);
    acceptLoop(sock_listen);
	close(sock_client);
	close(sock_listen);

	return 0;
}