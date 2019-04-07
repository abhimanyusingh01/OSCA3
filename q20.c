#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<semaphore.h>
#include<pthread.h>
int table_used=1,generated_item[2],generated=0;
char *item[]={"pen","paper","qpaper"};
sem_t table;
void *teacher(void *arg)
{
// agent thread function that has infinite number of ingredians
int i,j,k=0;
int count=0;
while(1)
{
sleep(1);
sem_wait(&table);
if(count==6) exit(0);
if(table_used==1)
{
i=k;
j=i+1;
if(j==3)
j=0;
k=j;
generated_item[0]=i;
generated_item[1]=j;
printf("Teacher gives %s,%s\n",item[i],item[j]);
generated=1;
table_used=0;
count++;
}
sem_post(&table);

}
}
void *studenti(void *i)
{
//int count=0;
while(1)
{
sleep(1);
sem_wait(&table);
if(table_used==0)
{
if(generated && generated_item[0]!=(int)i &&
generated_item[1]!=(int)i)
{
printf("Student%d completed his work\n",(int)i);
printf("\n");
//count++;
table_used=1;
generated=0;
}
}
sem_post(&table);
//if(count==5) exit(0);
}
}
main()
{
pthread_t student1,student2,student0,techer;
sem_init(&table,0,1);
printf("STUDENT0 has pen\n");
printf("STUDENT1 has paper\n");
printf("STUDENT2 has qpaper\n");
pthread_create(&techer,0,teacher,0);
pthread_create(&student0,0,studenti,(void*)0);
pthread_create(&student1,0,studenti,(void*)1);
pthread_create(&student2,0,studenti,(void*)2);
while(1);
}
