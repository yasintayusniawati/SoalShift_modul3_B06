# Soal Shift Modul 3

## Oleh Kelompok B06 :
1. Yasinta Yusniawati   05111740000054
2. Bima Satria Ramadhan 05111740000081

## Jawaban

### Soal 1
Untuk membuat program C yang bisa menghitung faktorial secara parallel lalu menampilkan hasilnya secara berurutan dibutuhkan thread dan join thread. Dalam program ini dibutuhkan beberapa fungsi, yaitu :

#### Faktorial 
```c
void* faktorial(void *parameter){
    int number = *((int*) parameter);
    unsigned long long fact = 1;
    int i;
    for(i=1; i<=number; i++){
        fact *=i;
    }
    printf("%d! = %llu\n", number, fact);
}
```
Fungsi ini digunakan untuk menghitung nilai yang di inputkan yang nantinya akan di panggil dalam main program.

#### Main
Dalam main program perintah sorting kami menggunakan bubble sort dalam implementasi programnya dan menambahkan perintah untuk create thread dan join thread.

1. Sorting
```c
for (i = 0; i < n; i++)          
       for (j = 0; j < n-i-1; j++)  
           if (argumen_angka[j] > argumen_angka[j+1]) 
              {
                    int temp = argumen_angka[j]; 
                    argumen_angka[j] = argumen_angka[j + 1]; 
                    argumen_angka[j + 1] = temp; 
              } 
```
2. Membuat thread dan join thread
```c
pthread_t tid[argc];

    for(i=0;i<argc-1;i++){
        int *temp = malloc(sizeof(*temp));
        *temp = argumen_angka[i];
        if(argumen_angka[i] < 0) continue;
        pthread_create(&(tid[i]), NULL, faktorial, temp);
        pthread_join(tid[i],NULL);
    }
```

### Soal 2
Bibutuhkan 4 program dalam soal ini yaitu :
1. Client 1 client yang terhubung dengan server penjual)
2. Client 2 (client yang terhubung dengan server pembeli)
3. Penjual (server Penjual)
4. Pembeli (server pembeli)

#### Client1
Client1 dapat menambahkan stok dengan cara connect terlebih dahulu ke server penjual kemudian mengirim string “tambah” ke server lalu stok bertambah 1
```c
if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }
    while(1){
        scanf("%s", kata);
        send(sock, kata, strlen(kata), 0);
        valread = read( sock , buffer, 1024);
        printf("%s\n",buffer );
        memset(buffer,0,1024);
    }
    return 0;
```

#### Server Penjual
Server memberitahu client1 menggunakan socket dan mengembalikan pesan bahwa stok berhasil di tambah
```c
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
```

Untuk mencetak jumlah stok yang ada dalam server penjual setiap 5 detik sekali:
```c
void* print(void *ptr){
    while(1){
        printf("Jumlah stok tersedia = %d\n", *stok);
        sleep(5);
        // system("clear");
    }
}
```

#### Server Pembeli
Server memberitahu client2 menggunakan socket dan mengembalikan pesan:
+ Jika stok habis maka client yang terkoneksi ke server pembeli akan mencetak “transaksi gagal”
+ Jika stok masih ada maka client yang terkoneksi ke server pembeli akan mencetak “transaksi berhasil”

```c
void* soket(void* ptr){
    int new_socket = *((int*) ptr);
    int valread;
    char buffer[1024];
    char *gagal = "gagal";
    char *berhasil = "berhasil";
    while(1){
        valread = read( new_socket , buffer, 1024);
        if(strcmp(buffer,"beli")==0){
            if(*stok<=0){
                send(new_socket , gagal , strlen(gagal) , 0 );
            }
        else
            {
                *stok = *stok - 1;
                send(new_socket , berhasil , strlen(berhasil) , 0 );
            }
        }

        memset(buffer,0,1024);
    }
}
```
#### Client2
Client2 dapat menambahkan stok dengan cara connect terlebih dahulu ke server pembeli kemudian mengirim string “beli” ke server lalu stok akan berkurang 1
```c
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }
    while(1){
        scanf("%s", kata);
        send(sock, kata, strlen(kata), 0);
        valread = read( sock , buffer, 1024);
        printf("%s\n",buffer );
        memset(buffer,0,1024);
    }
    return 0;
```

### Soal 3
```c
void *t_agmal(void *args){
    while(1)
    {
        if(irflag == 3)
        {
            printf("\nFitur Agmal Ayo Bangun disabled 10 s\n");
            sleep(10);
            irflag = 0;
	    printf("Fitur Agmal Ayo Bangun enabled\n");
        }
	if(fitur == 2)
        {
            wk_stat += 15;
            printf("\nWakeup_status Agmal %d\n", wk_stat);
            agflag += 1;
            irflag = 0;
	    fitur = 0;

            //if(wk_stat >= 100)
            //{
            //	printf("\nAgmal Terbangun, mereka bangun pagi dan berolahraga\n");
            //	break;
       	    //}
        }
    }
}
```
isi dari proses thread t_agmal

```c

void *t_iraj(void *args){
    while(1)
    {
        if(fitur == 3)
        {
            sp_stat -= 20;
            printf("\nSpirit_status Iraj %d\n", sp_stat);
            irflag += 1;
            agflag = 0;
	    fitur = 0;

            //if(sp_stat <= 0)
            //{
            //	printf("\nIraj ikut tidur, dan bangun kesiangan bersama Agmal\n");
            //	break;
            //}
        }
        if(agflag == 3)
        {
            printf("\nFitur Iraj Ayo Tidur disabled 10 s\n");
            sleep(10);
            agflag = 0;
            printf("Fitur Iraj Ayo Tidur enabled\n");
        }
    }
}
```
isi dari proses thread t_iraj

```c
int main(){

    pthread_create(&(tid1), NULL, &t_agmal, NULL);
    pthread_create(&(tid2), NULL, &t_iraj, NULL);

    while(1){

        if(wk_stat >= 100)
        {
            printf("\nAgmal Terbangun, mereka bangun pagi dan berolahraga\n");
            return 0;
        }
        if(sp_stat <= 0)
        {
            printf("\nIraj ikut tidur, dan bangun kesiangan bersama Agmal\n");
            return 0;
        }

        printf("\n1. All Status\t 2. Agmal Ayo Bangun\t 3. Iraj Ayo Tidur\n");
        scanf("%d", &fitur);

        if(fitur == 1)
        {
            printf("\nAgmal WakeUp_Status = %d\n", wk_stat);
            printf("Iraj Spirit_Status = %d\n", sp_stat);
        }
    }

    return 0;
}
```
isi dari fungsi utama yang akan menjalankan kedua thread t_agmal dan t_siraj. Disitu juga terdapat menu fitur pilihan untuk menjalankan program

### Soal 4
Untuk menjalankan perintah soal no 4 kami menggunakan 8 thread.
```c
void* mkdir1(){
	system("mkdir -p /home/bima/Documents/FolderProses1");
}

void* mkdir2(){
	system("mkdir -p /home/bima/Documents/FolderProses2");
}
```
thread diatas berfungsi untuk membuat folder FolderProses1 dan FolderProses2

```c
void* proses1(){
	system("ps -aux | head -10 > /home/bima/Documents/FolderProses1/SimpanProses1.txt");
}

void* proses2(){
	system("ps -aux | head -10 > /home/bima/Documents/FolderProses2/SimpanProses2.txt");
}
```
melakukan perintah ps -aux dibatasi 10 saja dan dimasukkan ke SimpanProses1.txt dan SimpanProses2.txt

```c
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
```
proses zip SimpanProses1.txt ke KompresProses1.zip dan SimpanProses2.txt ke KompresProses2.zip 

```c
void* unzip1(){
	system("unzip /home/bima/Documents/FolderProses1/KompresProses1.zip -d /home/bima/Documents/FolderProses1/");
}

void* unzip2(){
	system("unzip /home/bima/Documents/FolderProses2/KompresProses2.zip -d /home/bima/Documents/FolderProses2/");
}
```
merupakan proses unzip
