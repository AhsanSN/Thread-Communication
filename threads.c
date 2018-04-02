#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <stdbool.h>
 
// Let us create a global queue to change it in threads
int mesg_text[10];//queue size
bool read = false;// if the consumer should read or not
 
// The function to be executed by producer thread
void *producer()
{  
    int queue_index_p = 0;
    int rand_num;
    int total_num_sent = 0;
    FILE *fp; //file object- producer
    //create a producer txt file
    fp = fopen("producer.txt", "w+");
 
    while(total_num_sent!=1000)//for all 1000 values
    {
	while(read);
    	// random number generate
    	rand_num = rand() % 100;

    	//storing number in array of lenght 10
    	mesg_text[queue_index_p] = rand_num;
	fprintf(fp, "%d \n",rand_num);//storing in file
    	queue_index_p++;
    	total_num_sent++;	
    	if (queue_index_p==10)
    	{
		queue_index_p =0;
		read = true;//consumer can read now
    	}
    }
    //close file
    fclose(fp);
}

// The function to be executed by consumer thread
void *consumer()
{
    int queue_index_c = 0;
    int total_num_recvd = 0;
    FILE *fc; //file object- consumer
    //create a consumer txt file
    fc = fopen("consumer.txt", "w+");
 
    while(total_num_recvd<1000)
    {
	while(!read);
    	//storing number in file
	fprintf(fc, "%d \n",mesg_text[queue_index_c]);
    	queue_index_c++;
	total_num_recvd++;

    	if (queue_index_c==10)
    	{
		queue_index_c =0;
		read = false;// the producer can produce now
    	}
    }
    //close file
    fclose(fc);
}
 
int main()
{
    //create thread id
    pthread_t tid;
    
    srand(time(NULL));   // should only be called once

    //create two threads
    //producer thread
    pthread_create(&tid, NULL, producer, NULL);

    //consumer thread
    pthread_create(&tid, NULL, consumer,  NULL);

    //destroy all threads
    pthread_exit(NULL);

    return 0;
}
