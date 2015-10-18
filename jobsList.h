#ifndef JOBSLIST_H
#define	JOBSLIST_H

typedef struct jobsList {
    char cmd[255];
    pid_t *pidList;
    struct jobs *next;
} jobs;

void printJobs(jobs *jobs_list);

#endif
