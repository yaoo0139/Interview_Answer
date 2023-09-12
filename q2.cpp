#include <iostream>
#include <mutex>
#include "pthread.h"

// identify issues of running threads and propose your solution.

using namespace std;

int counter;
mutex counter_mtx;
pthread_rwlock_t rwlock;

void * thd_func1 (void *arg) {
    counter_mtx.lock();
    pthread_rwlock_rdlock(&rwlock);
  
    // 由於這邊下的是讀鎖，但是counter++是寫入，所以必須將鎖定方式改成寫鎖。
  
    counter++;
    pthread_rwlock_unlock(&rwlock);
    counter_mtx.unlock();
    return NULL;
}

void *thd_func2 (void *arg) {
    // rwlock也是公共資源的一種，我在思考他被互斥鎖鎖住的可能性。也就是說當我執行thd_func1的時候，直到我thd_func1的counter_mtx.unlock()執行之前，thd_func2都無法被上寫鎖。
    pthread_rwlock_wrlock(&rwlock);
    counter_mtx.lock();
    counter--;
    counter_mtx.unlock();
    pthread_rwlock_unlock(&rwlock);
    return NULL;
}


int main()
{
    pthread_rwlock_init(&rwlock ,NULL);
    pthread_t thd[2];
    pthread_create(&thd[0], NULL, thd_func1, NULL);
    pthread_create(&thd[1], NULL, thd_func2, NULL);
    for (int i = 0; i < 2; ++i) {
        pthread_join(thd[i], NULL);
    }

    return 0;
}
