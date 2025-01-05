#include "simul.h"

void increase_vruntime(Job *job);
int is_not_real(Job job, int current_time);
int calcuate_time_slice(Job job);

int fair_scheduler(Job jobs[], int n, int current_time, int *time_slice) {
    int min_vruntime_job_index = -1;
    int min_vruntime = INT_MAX;

    for (int i = 0; i < n; i++) {
        Job current_job = jobs[i];
        if (is_not_real(current_job, current_time)) {
            continue;
        }
        if (current_job.virtual_runtime < min_vruntime || min_vruntime_job_index == -1) {
            min_vruntime_job_index = i;
            min_vruntime = current_job.virtual_runtime;
        }
    }

    if (min_vruntime_job_index == -1) { // 수행할 작업이 없는 경우
        return min_vruntime_job_index;
    }

    *time_slice = calcuate_time_slice(jobs[min_vruntime_job_index]);
    increase_vruntime(&jobs[min_vruntime_job_index]);
    return min_vruntime_job_index;
}

void increase_vruntime(Job *job) {
    job->virtual_runtime += (double)TIME_QUANTUM * 1024 / job->weight;
}

int is_not_real(Job job, int current_time) {
    if (job.arrival_time > current_time || job.remaining_time <= 0) {
        return 1;
    }
    return 0;
}

int calcuate_time_slice(Job job) {
    return job.remaining_time > TIME_QUANTUM ? TIME_QUANTUM : job.remaining_time;
}
