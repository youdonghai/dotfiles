#include <memory>
#include <signal.h>

#include "worker.h"

std::vector<pthread_t> thread_id_vec;

void SignalHandler(int signum) {
    for (int i = 0; i < thread_id_vec.size(); ++i) {
        pthread_cancel(thread_id_vec[i]);
    }
    exit(0);
}

void *autoKeyWorker(void *event_file) {
    Worker w((const char *) event_file);
    w.run();
    pthread_exit((void *) 0);
}


int main(int argc, char **argv) {
    signal(SIGHUP, SignalHandler);
    signal(SIGTERM, SignalHandler);

    std::vector<std::string> keyboard_events = KeyboardDevice::GetKeyboardDeviceList();
    for (int i = 0; i < keyboard_events.size(); ++i) {
        pthread_t pid;
        if (0 == pthread_create(&pid, NULL, autoKeyWorker, (void *) keyboard_events[i].c_str())) {
            thread_id_vec.push_back(pid);
        }
    }

    for (int i = 0; i < thread_id_vec.size(); ++i) {
        void *retval = NULL;
        pthread_join(thread_id_vec[i], &retval);
    }
    return 0;
}
