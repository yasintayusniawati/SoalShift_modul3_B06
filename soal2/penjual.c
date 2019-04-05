#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <pthread.h>
#define PORT 8080

key_t key = 1111;
int *stok;
pthread_t thread; //insialisasi thread

void* print(void *ptr){
    while(1){
        printf("Jumlah stok tersedia = %d\n", *stok);
        sleep(5);
        // system("clear");
    }
}

void* soket(void* ptr){
    int new_socket = *((int*) ptr);
    int valread;
    char buffer[1024];
    char *kata = "berhasil menambah";
    while(1){
        // printf("%d\n",*stok);
        valread = read( new_socket , buffer, 1024);
        if(strcmp(buffer,"tambah")==0){
            *stok = *stok+1;
        }
        send(new_socket , kata , strlen(kata) , 0 );
        // printf("%d\n",*stok);
        memset(buffer,0,1024);
    }
}

int main(int argc, char const *argv[]) {
    int th;
    th = pthread_create(&(thread), NULL, print, NULL);

    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    

    int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
    stok = shmat(shmid, NULL, 0);

    *stok=3;

      
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
      
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );
      
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    pthread_t tread_soket;
    int *temp = malloc(sizeof(*temp));
    *temp = new_socket;
    pthread_create(&tread_soket,NULL,soket,temp);
    pthread_join(tread_soket,NULL);

    
    return 0;
}