enum procstate { UNUSED, EMBRYO, SLEEPING, RUNNABLE, RUNNING, ZOMBIE };

struct uproc {
  int pid;
  int ppid;
  enum procstate state;
  uint sz;
  char name[16];
};