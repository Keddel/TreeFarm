#pragma once
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <map>
#include <stdlib.h>
#include <string>
#include <thread>
#include <time.h>
#include <tuple>
#include <unistd.h>
#include <vector>

using namespace std;

extern string controls;

extern map<string, tuple<double, string, double>> shopMap;

void printTreeCollection(vector<string> collectedTrees);

void purchaseTree(vector<string> &collectedTrees, string key, string controls,
                  double &balance, double &incomePerSecond);

void disasters(double &balance, string controls, double &incomePerSecond,
               bool &tornado, bool &drought, bool &bank_blessing,
               bool &locust_swarm, bool &rain);

void disasterTimer(bool &tornado, double &incomePerSecond, double &balance,
                   bool &drought, bool &bank_blessing, bool &locust_swarm,
                   bool &rain);

void balanceTick(double &balance, string controls, bool &balanceThread,
                 bool &tornado, bool &drought, bool &bank_blessing,
                 bool &locust_swarm, bool &rain);

void awaitInput(double &balance, double &incomePerSecond, bool &balanceThread,
                int &sleepTime);

void tick(double &balance, double &incomePerSecond, int &sleepTime);