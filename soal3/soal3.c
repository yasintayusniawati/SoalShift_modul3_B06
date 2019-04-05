#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

pthread_t tid1, tid2;
int wk_stat=0;
int sp_stat=100;
int fitur;
int agflag=0;
int irflag=0;
//pthread_t tid1, tid2;

void *t_agmal(void *args){
    while(1)
    {
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
        if(irflag == 3)
        {
            printf("\nFitur Agmal Ayo Bangun disabled 10 s\n");
            sleep(10);
            irflag = 0;
	    printf("Fitur Agmal Ayo Bangun enabled\n");
        }
    }
}

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
