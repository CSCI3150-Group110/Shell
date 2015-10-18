#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

#include "jobsList.h"

jobs *jobListCreate(pid_t *pidList, char **cmd) {
    jobs* newNode = malloc(sizeof (jobs));
    strcpy(newNode->cmd, cmd);
    newNode->pidList = *pidList;
    newNode->next = NULL;
    return newNode;
}

jobs *jobInsert(jobs *jobs_list,pid_t *pidList,char **cmd){
    jobs* newJobs=malloc(sizeof(jobs));
    newJobs->pidList=pidList;
    
}

void printJobs(jobs *job_list) {
    int num=1;
    if(job_list==NULL)
        printf("No suspended jobs\n");
    while(job_list){
        printf("[%d]\t%s",num++,job_list->cmd);
        job_list=job_list->next;
    }
}