#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#include <errno.h>
#include <semaphore.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/stat.h>


#define BUFFER_SIZE 2 //��������Ԫ��


sem_t mutex,full,empty;//�����ź���

//������
struct DataBuffer
{
int buffer[BUFFER_SIZE];
int count;//��ǰ��Ʒ����
}dataBuffer;


//�ƶ�������
void moveDataForward(){
int i;
for(i=0;i<dataBuffer.count;i++)
dataBuffer.buffer[i]=dataBuffer.buffer[i+1];
}
//��Ʒ���뻺����
void push(int data){
dataBuffer.buffer[dataBuffer.count++]=data;
}
//�ӻ�����ȡ��Ʒ
int pop(){
int data=dataBuffer.buffer[0];
dataBuffer.count--;
moveDataForward();
return data;
}
//�������߳�
void producer(void arg){

int product;
int a;
a=((int)arg);
srand(time(NULL));
product=rand()%1000+a;

sleep(1);
printf("������ %d ����һ����Ʒ%d\n",a,product);
sleep(1);
printf("������ %d ���뻺����\n",a);
sleep(1);

sem_wait(&empty);
sem_wait(&mutex);
printf("������ %d ���뻺�����ɹ�\n",a);
sleep(1);
printf("������ %d ����Ʒ%d���뻺����\n",a,product);
sleep(1);
push(product);
sem_post(&mutex);
sem_post(&full);
printf("������ %d �ͷŻ�����,��ǰ��������%d����Ʒ\n",a,dataBuffer.count);


}

//�������߳�
void customer(void arg){
int d;
int a;
a=((int)arg);
sleep(1);
printf("������ %d ���뻺����\n",a);
sleep(1);
sem_wait(&full);
sem_wait(&mutex);
printf("������ %d ���뻺�����ɹ�\n",a);
sleep(1);
d=pop();
printf("������ %d �ӻ�����ȡ����Ʒ%d\n",a,d);
sleep(1);
sem_post(&mutex);
sem_post(&empty);
printf("������ %d �ͷŻ���������ǰ��������%d����Ʒ\n",a,dataBuffer.count);

}

int main(){
pthread_t thrd_prd1,thrd_prd2,thrd_prd3,thrd_cst1,thrd_cst2,thrd_cst3;
int i1=1,i2=2,i3=3;
sem_init(&mutex, 0, 1);
sem_init(&empty, 0, BUFFER_SIZE);
sem_init(&full, 0, 0);
pthread_create(&thrd_prd1, NULL, producer, (void )&i1);
pthread_create(&thrd_prd2, NULL, producer, (void )&i2);
pthread_create(&thrd_prd3, NULL, producer, (void )&i3);
pthread_create(&thrd_cst1, NULL, customer, (void )&i1);
pthread_create(&thrd_cst2, NULL, customer, (void )&i2);
pthread_create(&thrd_cst3, NULL, customer, (void )&i3);

pthread_join(thrd_prd1, NULL);
pthread_join(thrd_prd2, NULL);
pthread_join(thrd_prd3, NULL);
pthread_join(thrd_cst1, NULL);
pthread_join(thrd_cst2, NULL);
pthread_join(thrd_cst3, NULL);
return 0;
}