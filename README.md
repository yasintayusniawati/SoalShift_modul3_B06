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