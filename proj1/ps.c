#include "types.h"
#include "user.h"
#include "uproc.h"

#define TABLE_SZ 10

int
main(int argc, char *argv[])
{
  static char *states[] = {
  [UNUSED]    "unused",
  [EMBRYO]    "embryo",
  [SLEEPING]  "sleep ",
  [RUNNABLE]  "runble",
  [RUNNING]   "run   ",
  [ZOMBIE]    "zombie"
  };

  struct uproc *table;

  table = malloc( TABLE_SZ * sizeof(struct uproc) );

  // SYSTEM CALL
  int n = getprocs(TABLE_SZ, table);

  int i;

  if (n > TABLE_SZ) {
    for (i = 0; i < TABLE_SZ; i++) {
      printf(1, "%d  %d  %s  %d  %s\n",
        table[i].pid,
        table[i].ppid,
        states[table[i].state],
        table[i].sz,
        table[i].name
      );
    }
  }
  else {
    for (i = 0; i < n; i++) {
      printf(1, "%d  %d  %s  %d  %s\n",
        table[i].pid,
        table[i].ppid,
        states[table[i].state],
        table[i].sz,
        table[i].name
      );
    }
  }

  exit();
}
