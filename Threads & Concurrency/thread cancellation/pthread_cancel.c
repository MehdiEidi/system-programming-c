#include <sys/types.h>
#include <pthread.h>

void worker();

int main(void) {
    pthread_t tid;

    pthread_create(&tid, 0, worker, NULL);

    // some code

    pthread_cancel(tid);

    pthread_join(tid, NULL);
}
