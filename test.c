#include <pthread.h>
#include <stdio.h>

void changeSpeed(int i, int gpio, char* fileString)
{

         FILE *file;
         for(;;)
         {
            file = fopen("stop.txt", "r");
            if (fgetc(file) == 's') break;
            fclose(file);

            //Do speed stuff here
         }

         //This just creates an ending file in the same directery that shows
         //The function has successfuly been told to stop.
         printf("ENDING\n");
         file = fopen("itEnded.txt","a");
         fputs("The Function Has Ended",file);
         fclose(file);
         pthread_exit(0);

}

//This is like the web handler
int webHandler()
{
    pthread_t hilo1;

    pthread_create(&hilo1,NULL, changeSpeed, 1,2,"test");

    printf("The test example web handler function has finished");
    return 0 ;

}

//This is like web server core function
int main(void)
{

    for (;;)
    {
        //This is like web call
        webHandler();
        int input;
        scanf("%d",&input);
    }

}
