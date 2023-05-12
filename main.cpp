
#include "mainheader.h"
using namespace std;

int main() { // contains a lot of variable declarations and joins several
             // threads/functions together to run at once
  int sleepTime = 2;
  bool balanceThread = false;
  bool tornado = false;
  bool drought = false;
  bool bank_blessing = false;
  bool locust_swarm = false;
  bool rain = false;
  double balance = 0;
  double incomePerSecond = 0.1;
  thread t1(tick, ref(balance), ref(incomePerSecond), ref(sleepTime));
  thread t2(awaitInput, ref(balance), ref(incomePerSecond), ref(balanceThread),
            ref(sleepTime));
  thread t3(balanceTick, ref(balance), controls, ref(balanceThread),
            ref(tornado), ref(drought), ref(bank_blessing), ref(locust_swarm),
            ref(rain));
  thread t4(disasters, ref(balance), controls, ref(incomePerSecond),
            ref(tornado), ref(drought), ref(bank_blessing), ref(locust_swarm),
            ref(rain));
  thread t5(disasterTimer, ref(tornado), ref(incomePerSecond), ref(balance),
            ref(drought), ref(bank_blessing), ref(locust_swarm), ref(rain));
  t5.join();
  t3.join();
  t4.join();

  t1.join();
  t2.join();

  return 0;
}
