
#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<string.h>

pthread_t tid[10];

void* mkdir1(){
	system("mkdir -p /home/bima/Documents/FolderProses1");
}

void* mkdir2(){
	system("mkdir -p /home/bima/Documents/FolderProses2");
}

void* proses1(){
	system("ps -aux | head -10 > /home/bima/Documents/FolderProses1/SimpanProses1.txt");
}

void* proses2(){
	system("ps -aux | head -10 > /home/bima/Documents/FolderProses2/SimpanProses2.txt");
}

void* zip1(){
	system("zip -j /home/bima/Documents/FolderProses1/KompresProses1.zip /home/bima/Documents/FolderProses1/SimpanProses1.txt");
	system("rm /home/bima/Documents/FolderProses1/SimpanProses1.txt");
	sleep(15);
	printf("Menunggu 15 detik untuk mengekstrak kembali\n");
}

void* zip2(){
	system("zip -j /home/bima/Documents/FolderProses2/KompresProses2.zip /home/bima/Documents/FolderProses2/SimpanProses2.txt");
	system("rm /home/bima/Documents/FolderProses2/SimpanProses2.txt");
	sleep(15);
	printf("Menunggu 15 detik untuk mengekstrak kembali\n");
}

void* unzip1(){
	system("unzip /home/bima/Documents/FolderProses1/KompresProses1.zip -d /home/bima/Documents/FolderProses1/");
}

void* unzip2(){
	system("unzip /home/bima/Documents/FolderProses2/KompresProses2.zip -d /home/bima/Documents/FolderProses2/");
}

int main()
{
	pthread_create(&(tid[0]),NULL,&mkdir1,NULL);
	pthread_create(&(tid[1]),NULL,&mkdir2,NULL);
	pthread_join(tid[0],NULL);
	pthread_join(tid[1],NULL);
	pthread_create(&(tid[2]),NULL,&proses1,NULL);
	pthread_create(&(tid[3]),NULL,&proses2,NULL);
	pthread_join(tid[2],NULL);
	pthread_join(tid[3],NULL);
	pthread_create(&(tid[4]),NULL,&zip1,NULL);
	pthread_create(&(tid[5]),NULL,&zip2,NULL);
	pthread_join(tid[4],NULL);
	pthread_join(tid[5],NULL);
	pthread_create(&(tid[6]),NULL,&unzip1,NULL);
	pthread_create(&(tid[7]),NULL,&unzip2,NULL);
	pthread_join(tid[6],NULL);
	pthread_join(tid[7],NULL);
}
