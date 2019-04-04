#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* faktorial(void *parameter){
    int number = *((int*) parameter);
    unsigned long long fact = 1;
    int i;
    for(i=1; i<=number; i++){
        fact *=i;
    }
    printf("%d! = %llu\n", number, fact);
}

int main(int argc, char* argv[])
{
    int i, count;
    int argumen_angka[argc];
    for(count=1; count<argc;count++){
        argumen_angka[count-1] = atoi(argv[count]);
    }

    int j;
    int n=argc-1;
    for (i = 0; i < n; i++)          
       for (j = 0; j < n-i-1; j++)  
           if (argumen_angka[j] > argumen_angka[j+1]) 
              {
                    int temp = argumen_angka[j]; 
                    argumen_angka[j] = argumen_angka[j + 1]; 
                    argumen_angka[j + 1] = temp; 
              } 
    pthread_t tid[argc];

    for(i=0;i<argc-1;i++){
        int *temp = malloc(sizeof(*temp));
        *temp = argumen_angka[i];
        if(argumen_angka[i] < 0) continue;
        pthread_create(&(tid[i]), NULL, faktorial, temp);
        pthread_join(tid[i],NULL);
    }

    return 0;
}