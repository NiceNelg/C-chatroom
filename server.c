#include <stdio.h>
#include <malloc.h>
#include <unistd.h>
#include <string.h>
#include "socket.h"
#include "dlist.h"

/**
 * @brief   main 
 *
 * @param   string  argc
 * @param   string  argv[]
 *
 * @return  
 */
int main(int argc, char *argv[])
{

    DList *test;
    DListNode *node;

    test = dlist_create();

    //dlist_add(test, 0, (void *)"test1");
    node = dlist_get(test, 0);

    printf("%s\n", (char *)node->data);

    printf("hh\n");
    return 0;
    //int opt = 0;
    //int options_index = 0;
    //char *address;
    //char *port;

    //if(argc == 1) {
    //    return 2;
    //}

    //while((opt=getopt(argc,argv,"i:p:")) != -1) {
    //
    //    switch(opt) {
    //        case 'i':
    //            printf("Address:%s\n", optarg);
    //            address = (char *)malloc(sizeof(*optarg));
    //            memcpy(address, optarg, strlen(optarg));
    //            break;
    //        case 'p':
    //            printf("Port:%s\n", optarg);
    //            port = (char *)malloc(sizeof(*optarg));
    //            memcpy(port, optarg, strlen(optarg));
    //            break;
    //    }

    //}
    //
    //socket_build(address, port);
    //return 0;
}