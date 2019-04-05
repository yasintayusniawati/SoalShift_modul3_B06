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