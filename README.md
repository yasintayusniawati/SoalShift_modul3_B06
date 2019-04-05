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
+ 
```c

```