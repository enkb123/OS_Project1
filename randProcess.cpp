//Eshen Brinkert
//April 13, 2022
//This program simulates the running of fifty processes on four different processors.
//Four different scenarios are provided for the user to chose from and the user can select one of five scheduling methods to solve the scenario.
//This code would be better if I had made separate methods for the contents of the switch but I was more concerned with functionality so I did not prioritize well organized code. Sorry.
#include <iostream>
#include <random>
#include <math.h>
#include <queue>

using namespace std;

class Process{
public:
    int ID;
    unsigned long long serviceTime;
    unsigned long long arrivalTime;
    int memory;
    unsigned long long waitTime;
    unsigned long long totalTime; //wait time + service time
    int priority; //stores the priority level of the process
    int SJFrank; //stores the rank of the process based on shortest job first (1 = shortest service time)
    bool done; //stores whether the process has finished
    unsigned long long rt; //stores the time the process has remaining after it has been kicked off the processor
    unsigned long long startTime; //stores the start time of the process
    unsigned long long endTime;//stores the end time of the process

};

class Processor{
public:
    unsigned long long speed;
    int memory;
};

int main(){
    Process pro[50];
    priority_queue<unsigned long long> myQ;
    int scenario; //stores the scenario chosen by user
    int seedVal; //stores the value of the seed input by user
    int sortAl;  //stores the algorithm chosen by the user
    unsigned long long totCycles;
    cout << "Welcome to the process simulator. \n Which scenario would you like to run." <<endl;
    cout<< "1. All four processors are identical with a speed of 3GHz and a memory capacity of 8GB"<< endl;
    cout<< "2. All four processors have identical speeds, 3GHz, but varying memory availability. P1 and P2 have 2GB, P3 has 4GB, and P4 has 8GB."<<endl;
    cout<< "3. All four processors have identical memory availability, 8GB, but varying speeds. P1 and P2 are 2GHz, P3 is 3GHz, and P4 is 4GHz." <<endl;
    cout<< "4. All four processors are identical with a speed of 3GHz and a memory capacity of 8GB. Your system must handle the processes based on their arrival times, i.e. you cannot inspect the entire set of processes, but must schedule them as they arrive in the system." <<endl;
    cin >> scenario;

    cout<<"Which sorting algorithm would you like to use?"<<endl;
    cout<<"1. FIFO"<<endl;
    cout<<"2. SJF"<<endl;
    cout<<"3. SRT"<<endl;
    //cout<<"4. RR"<<endl;
    cout<<"5. ML"<<endl;
    cin>>sortAl;

    cout<< "What seed value would you like to use?"<<endl;
    cin >>seedVal;

    mt19937 gen(seedVal); //Standard mersenne_twister_engine seeded with rd()
    uniform_int_distribution<> distribMem(1, 8);
    uniform_int_distribution<> distribP(1,50);
    uniform_int_distribution<> distribServ(10*pow(10,6), 10*pow(10,12));
    uniform_int_distribution<> distribAr(1, 10*pow(10,10));

    unsigned long long totTimes = 0;
    unsigned long long avgST = 0;
    unsigned long long avgAT = 0;
    int avgM = 0;
    for (int n =0; n<50; n++){
        Process myPro;
        myPro.ID = n;
        myPro.memory = distribMem(gen); //randomly generates memory of process
        avgM += myPro.memory;
        myPro.serviceTime = distribServ(gen);//randomly generates service time of process
        avgST += myPro.serviceTime;
        myPro.arrivalTime = distribAr(gen); //randomly generated arrival time of process
        avgAT += myPro.arrivalTime;
        myPro.priority = distribP(gen);//randomly generated priority of process
        //totCycles += myPro.serviceTime;
        myPro.rt = myPro.serviceTime; //sets the remaining time of the process
        myPro.done = false;
        pro[n] = myPro;
        totTimes += myPro.serviceTime;
    }
    cout<<"Avg mem:"<<avgM/50<<endl<<"AvgST:"<<avgST/50<<endl<<"AvgAT:"<<avgAT/50<<endl;



    switch(scenario){
        case 1:
            {Processor essor1;
            essor1.memory = 8;
            essor1.speed = 3000000000;
            unsigned long long totTime1 = 0;
            queue<Process> q1;
            Processor essor2;
            essor2.memory = 8;
            essor2.speed = 3000000000;
            unsigned long long totTime2 = 0;
            queue<Process> q2;
            Processor essor3;
            essor3.memory = 8;
            essor3.speed = 3000000000;
            unsigned long long totTime3 = 0;
            queue<Process> q3;
            Processor essor4;
            essor4.memory = 8;
            essor4.speed = 3000000000; //3000000000 cycle/second
            unsigned long long totTime4 = 0;
            queue<Process> q4;
            unsigned long long avgTT = 0;
            unsigned long long avgWT = 0;
            switch(sortAl){
                case 1:{
                    for(int i = 0; i<50; i++){
                        if(totTime1<=totTime2 && totTime1<=totTime3 && totTime1<=totTime4){
                            q1.push(pro[i]);
                            cout<<"Process number:" << pro[i].ID<<endl;
                            cout<<"Service time:"<<pro[i].serviceTime<<endl<<"Arrival time:"<<0<<endl;
                            cout<<"Memory requirements:"<< pro[i].memory<<endl<<"Wait time:"<<totTime1<<endl<<"Total time in system:"<<totTime1+pro[i].serviceTime<<endl;
                            cout<<"In processor 1"<<endl;
                            avgTT += (totTime1+pro[i].serviceTime);
                            avgWT += totTime1;
                            totTime1 = pro[i].serviceTime;
                        }else if(totTime2 <=totTime3 && totTime2 <=totTime1 && totTime2 <=totTime4){
                            q2.push(pro[i]);
                            cout<<"Process number:" << pro[i].ID<<endl;
                            cout<<"Service time:"<<pro[i].serviceTime<<endl<<"Arrival time:"<<0<<endl;
                            cout<<"Memory requirements:"<< pro[i].memory<<endl<<"Wait time:"<<totTime2<<endl<<"Total time in system:"<<totTime2+pro[i].serviceTime<<endl;
                            cout<<"In processor 2"<<endl;
                            totTime2 += pro[i].serviceTime;
                            avgWT += totTime2;
                            avgTT += (totTime2+pro[i].serviceTime);
                        }else if(totTime3 <= totTime4 && totTime3 <= totTime2 && totTime3 <= totTime1){
                            q3.push(pro[i]);
                            cout<<"Process number:" << pro[i].ID<<endl;
                            cout<<"Service time:"<<pro[i].serviceTime<<endl<<"Arrival time:"<<0<<endl;
                            cout<<"Memory requirements:"<< pro[i].memory<<endl<<"Wait time:"<<totTime3<<endl<<"Total time in system:"<<totTime3+pro[i].serviceTime<<endl;
                            cout<<"In processor 3"<<endl;
                            avgWT += totTime3;
                            avgTT += (totTime3+pro[i].serviceTime);
                            totTime3 += pro[i].serviceTime;
                        }else if(totTime4 <= totTime1 && totTime4 <= totTime2 && totTime4 <= totTime3){
                            q4.push(pro[i]);
                            cout<<"Process number:" << pro[i].ID<<endl;
                            cout<<"Service time:"<<pro[i].serviceTime<<endl<<"Arrival time:"<<0<<endl;
                            cout<<"Memory requirements:"<< pro[i].memory<<endl<<"Wait time:"<<totTime4<<endl<<"Total time in system:"<<totTime4+pro[i].serviceTime<<endl;
                            cout<<"In processor 4"<<endl;
                            avgWT += totTime4;
                            avgTT += (totTime4+pro[i].serviceTime);
                            totTime4 += pro[i].serviceTime;
                        }
                    }
                    unsigned long long overallTime = totTime1;
                    if(totTime2>overallTime){
                        overallTime = totTime2;
                    }
                    if(totTime3>overallTime){
                        overallTime = totTime3;
                    }
                    if(totTime4>overallTime){
                        overallTime = totTime4;
                    }
                    cout<<"Total cycles:" << overallTime<<endl;
                    cout<<"AVGtt:"<< avgTT/50<<endl;
                    cout<<"AVGwt:"<<avgWT/50<<endl;
                    break;
                }
                case 2:{
                    priority_queue<unsigned long long> pqSJF1;
                    for(int n = 0; n<50; n++){
                        pqSJF1.push(-(pro[n].serviceTime));
                    }
                    while(!pqSJF1.empty()){
                        unsigned long long temp = pqSJF1.top();
                        pqSJF1.pop();
                        int i = 0;
                        while (pro[i].serviceTime != -(temp)){
                            i++;
                        }
                        if(totTime1<=totTime2 && totTime1<=totTime3 && totTime1<=totTime4){
                            q1.push(pro[i]);
                            cout<<"Process number:" << pro[i].ID<<endl<<"Service time:"<<pro[i].serviceTime<<endl<<"Arrival time:"<<0<<endl;
                            cout<<"Memory requirements:"<< pro[i].memory<<endl<<"Wait time:"<<totTime1<<endl<<"Total time in system:"<<totTime1+pro[i].serviceTime<<endl;
                            cout<<"In processor 1"<<endl;
                            totTime1 = pro[i].serviceTime;
                        }else if(totTime2 <=totTime3 && totTime2 <=totTime1 && totTime2 <=totTime4){
                            q2.push(pro[i]);
                            cout<<"Process number:" << pro[i].ID<<endl<<"Service time:"<<pro[i].serviceTime<<endl<<"Arrival time:"<<0<<endl;
                            cout<<"Memory requirements:"<< pro[i].memory<<endl<<"Wait time:"<<totTime2<<endl<<"Total time in system:"<<totTime2+pro[i].serviceTime<<endl;
                            cout<<"In processor 2"<<endl;
                            totTime2 += pro[i].serviceTime;
                        }else if(totTime3 <= totTime4 && totTime3 <= totTime2 && totTime3 <= totTime1){
                            q3.push(pro[i]);
                            cout<<"Process number:" << pro[i].ID<<endl<<"Service time:"<<pro[i].serviceTime<<endl<<"Arrival time:"<<0<<endl;
                            cout<<"Memory requirements:"<< pro[i].memory<<endl<<"Wait time:"<<totTime3<<endl<<"Total time in system:"<<totTime3+pro[i].serviceTime<<endl;
                            cout<<"In processor 3"<<endl;
                            totTime3 += pro[i].serviceTime;
                        }else if(totTime4 <= totTime1 && totTime4 <= totTime2 && totTime4 <= totTime3){
                            q4.push(pro[i]);
                            cout<<"Process number:" << pro[i].ID<<endl<<"Service time:"<<pro[i].serviceTime<<endl<<"Arrival time:"<<0<<endl;
                            cout<<"Memory requirements:"<< pro[i].memory<<endl<<"Wait time:"<<totTime4<<endl<<"Total time in system:"<<totTime4+pro[i].serviceTime<<endl;
                            cout<<"In processor 4"<<endl;
                            totTime4 += pro[i].serviceTime;
                        }
                    }
                    unsigned long long overallTime = totTime1;
                    if(totTime2>overallTime){
                        overallTime = totTime2;
                    }
                    if(totTime3>overallTime){
                        overallTime = totTime3;
                    }
                    if(totTime4>overallTime){
                        overallTime = totTime4;
                    }
                    cout<<"Total cycles:" << overallTime<<endl;

                    break;
                }
                case 3:{

                    priority_queue<unsigned long long> pqSJF1;
                    for(int n = 0; n<50; n++){
                        pqSJF1.push(-(pro[n].serviceTime));
                    }
                    while(!pqSJF1.empty()){
                        unsigned long long temp = pqSJF1.top();
                        pqSJF1.pop();
                        int i = 0;
                        while (pro[i].serviceTime != -(temp)){
                            i++;
                        }
                        if(totTime1<=totTime2 && totTime1<=totTime3 && totTime1<=totTime4){
                            q1.push(pro[i]);
                            cout<<"Process number:" << pro[i].ID<<endl;
                            /*
                            cout<<"Service time:"<<pro[i].serviceTime<<endl<<"Arrival time:"<<0<<endl;
                            cout<<"Memory requirements:"<< pro[i].memory<<endl<<"Wait time:"<<totTime1<<endl<<"Total time in system:"<<totTime1+pro[i].serviceTime<<endl;
                            cout<<"In processor 1"<<endl;
                            */
                            avgWT += totTime1;
                            avgTT += (totTime1+pro[i].serviceTime);
                            totTime1 = pro[i].serviceTime;
                        }else if(totTime2 <=totTime3 && totTime2 <=totTime1 && totTime2 <=totTime4){
                            q2.push(pro[i]);
                            cout<<"Process number:" << pro[i].ID<<endl;
                            /*
                            cout<<"Service time:"<<pro[i].serviceTime<<endl<<"Arrival time:"<<0<<endl;
                            cout<<"Memory requirements:"<< pro[i].memory<<endl<<"Wait time:"<<totTime2<<endl<<"Total time in system:"<<totTime2+pro[i].serviceTime<<endl;
                            cout<<"In processor 2"<<endl;
                            */
                            avgWT += totTime2;
                            avgTT += (totTime2+pro[i].serviceTime);
                            totTime2 += pro[i].serviceTime;
                        }else if(totTime3 <= totTime4 && totTime3 <= totTime2 && totTime3 <= totTime1){
                            q3.push(pro[i]);
                            cout<<"Process number:" << pro[i].ID<<endl;
                            /*
                            cout<<"Service time:"<<pro[i].serviceTime<<endl<<"Arrival time:"<<0<<endl;
                            cout<<"Memory requirements:"<< pro[i].memory<<endl<<"Wait time:"<<totTime3<<endl<<"Total time in system:"<<totTime3+pro[i].serviceTime<<endl;
                            cout<<"In processor 3"<<endl;
                            */
                            avgWT += totTime3;
                            avgTT += (totTime3+pro[i].serviceTime);
                            totTime3 += pro[i].serviceTime;
                        }else if(totTime4 <= totTime1 && totTime4 <= totTime2 && totTime4 <= totTime3){
                            q4.push(pro[i]);
                            cout<<"Process number:" << pro[i].ID<<endl;
                            /*
                            cout<<"Service time:"<<pro[i].serviceTime<<endl<<"Arrival time:"<<0<<endl;
                            cout<<"Memory requirements:"<< pro[i].memory<<endl<<"Wait time:"<<totTime4<<endl<<"Total time in system:"<<totTime4+pro[i].serviceTime<<endl;
                            cout<<"In processor 4"<<endl;
                            */
                            avgWT += totTime4;
                            avgTT += (totTime4+pro[i].serviceTime);
                            totTime4 += pro[i].serviceTime;
                        }
                    }
                    unsigned long long overallTime = totTime1;
                    if(totTime2>overallTime){
                        overallTime = totTime2;
                    }
                    if(totTime3>overallTime){
                        overallTime = totTime3;
                    }
                    if(totTime4>overallTime){
                        overallTime = totTime4;
                    }
                    cout<<"Total cycles:" << overallTime<<endl;
                    cout<<"AVGtt:"<< avgTT/50<<endl;
                    cout<<"AVGwt:"<<avgWT/50<<endl;

                    break;
                }
                case 4:{

                    break;
                }
                case 5:{
                    priority_queue<int> pqML;
                    for(int n = 0; n<50; n++){
                      pqML.push(pro[n].priority);
                    }
                    while(!pqML.empty()){
                        int temp = pqML.top();
                        pqML.pop();
                        int i = 0;
                        while (pro[i].priority != temp || pro[i].done == true){
                            i++;
                        }
                        pro[i].done = true;
                        if(totTime1<=totTime2 && totTime1<=totTime3 && totTime1<=totTime4){
                            q1.push(pro[i]);
                            cout<<"Process number:" << pro[i].ID<<endl<<"Service time:"<<pro[i].serviceTime<<endl<<"Arrival time:"<<0<<endl;
                            cout<<"Memory requirements:"<< pro[i].memory<<endl<<"Wait time:"<<totTime1<<endl<<"Total time in system:"<<totTime1+pro[i].serviceTime<<endl;
                            cout<<"In processor 1"<<endl;
                            totTime1 = pro[i].serviceTime;
                        }else if(totTime2 <=totTime3 && totTime2 <=totTime1 && totTime2 <=totTime4){
                            q2.push(pro[i]);
                            cout<<"Process number:" << pro[i].ID<<endl<<"Service time:"<<pro[i].serviceTime<<endl<<"Arrival time:"<<0<<endl;
                            cout<<"Memory requirements:"<< pro[i].memory<<endl<<"Wait time:"<<totTime2<<endl<<"Total time in system:"<<totTime2+pro[i].serviceTime<<endl;
                            cout<<"In processor 2"<<endl;
                            totTime2 += pro[i].serviceTime;
                        }else if(totTime3 <= totTime4 && totTime3 <= totTime2 && totTime3 <= totTime1){
                            q3.push(pro[i]);
                            cout<<"Process number:" << pro[i].ID<<endl<<"Service time:"<<pro[i].serviceTime<<endl<<"Arrival time:"<<0<<endl;
                            cout<<"Memory requirements:"<< pro[i].memory<<endl<<"Wait time:"<<totTime3<<endl<<"Total time in system:"<<totTime3+pro[i].serviceTime<<endl;
                            cout<<"In processor 3"<<endl;
                            totTime3 += pro[i].serviceTime;
                        }else if(totTime4 <= totTime1 && totTime4 <= totTime2 && totTime4 <= totTime3){
                            q4.push(pro[i]);
                            cout<<"Process number:" << pro[i].ID<<endl<<"Service time:"<<pro[i].serviceTime<<endl<<"Arrival time:"<<0<<endl;
                            cout<<"Memory requirements:"<< pro[i].memory<<endl<<"Wait time:"<<totTime4<<endl<<"Total time in system:"<<totTime4+pro[i].serviceTime<<endl;
                            cout<<"In processor 4"<<endl;
                            totTime4 += pro[i].serviceTime;
                        }
                    }
                    unsigned long long overallTime = totTime1;
                    if(totTime2>overallTime){
                        overallTime = totTime2;
                    }
                    if(totTime3>overallTime){
                        overallTime = totTime3;
                    }
                    if(totTime4>overallTime){
                        overallTime = totTime4;
                    }
                    cout<<"Total cycles:" << overallTime<<endl;
                    break;
                    }
                default:
                    break;
            }
            break;
            }
        case 2:
            {Processor essor1;
            essor1.memory = 2;
            essor1.speed = 3000000000;
            unsigned long long totTime1 = 0;
            queue<Process> q1;
            Processor essor2;
            essor2.memory = 2;
            essor2.speed = 3000000000;
            unsigned long long totTime2 = 0;
            queue<Process> q2;
            Processor essor3;
            essor3.memory = 4;
            essor3.speed = 3000000000;
            unsigned long long totTime3 = 0;
            queue<Process> q3;
            Processor essor4;
            essor4.memory = 8;
            essor4.speed = 3000000000; //3000000000 cycle/second
            unsigned long long totTime4 = 0;
            unsigned long long avgTT = 0;
            unsigned long long avgWT = 0;
            queue<Process> q4;
            switch(sortAl){
                case 1:{
                    for(int i = 0; i<50; i++){
                        if(essor1.memory>=pro[i].memory && totTime1<=totTime2){
                            q1.push(pro[i]);
                            cout<<"Process number:" << pro[i].ID<<endl<<"Service time:"<<pro[i].serviceTime<<endl<<"Arrival time:"<<0<<endl;
                            cout<<"Memory requirements:"<< pro[i].memory<<endl<<"Wait time:"<<totTime1<<endl<<"Total time in system:"<<totTime1+pro[i].serviceTime<<endl;
                            cout<<"In processor 1"<<endl;
                            avgTT += (totTime1+pro[i].serviceTime);
                            avgWT += totTime1;
                            totTime1 = pro[i].serviceTime;
                        }else if(essor2.memory>=pro[i].memory){
                            q2.push(pro[i]);
                            cout<<"Process number:" << pro[i].ID<<endl<<"Service time:"<<pro[i].serviceTime<<endl<<"Arrival time:"<<0<<endl;
                            cout<<"Memory requirements:"<< pro[i].memory<<endl<<"Wait time:"<<totTime2<<endl<<"Total time in system:"<<totTime2+pro[i].serviceTime<<endl;
                            cout<<"In processor 2"<<endl;
                            avgTT += (totTime2+pro[i].serviceTime);
                            avgWT += totTime2;
                            totTime2 += pro[i].serviceTime;
                        }else if(essor3.memory>=pro[i].memory && totTime3<=totTime4){
                            q3.push(pro[i]);
                            cout<<"Process number:" << pro[i].ID<<endl<<"Service time:"<<pro[i].serviceTime<<endl<<"Arrival time:"<<0<<endl;
                            cout<<"Memory requirements:"<< pro[i].memory<<endl<<"Wait time:"<<totTime3<<endl<<"Total time in system:"<<totTime3+pro[i].serviceTime<<endl;
                            cout<<"In processor 3"<<endl;
                            avgTT += (totTime3+pro[i].serviceTime);
                            avgWT += totTime3;
                            totTime3 += pro[i].serviceTime;
                        }else if(essor4.memory>=pro[i].memory){
                            q4.push(pro[i]);
                            cout<<"Process number:" << pro[i].ID<<endl<<"Service time:"<<pro[i].serviceTime<<endl<<"Arrival time:"<<0<<endl;
                            cout<<"Memory requirements:"<< pro[i].memory<<endl<<"Wait time:"<<totTime4<<endl<<"Total time in system:"<<totTime4+pro[i].serviceTime<<endl;
                            cout<<"In processor 4"<<endl;
                            avgTT += (totTime4+pro[i].serviceTime);
                            avgWT += totTime4;
                            totTime4 += pro[i].serviceTime;
                        }
                    }
                    unsigned long long overallTime = totTime1;
                    if(totTime2>overallTime){
                        overallTime = totTime2;
                    }
                    if(totTime3>overallTime){
                        overallTime = totTime3;
                    }
                    if(totTime4>overallTime){
                        overallTime = totTime4;
                    }
                    cout<<"Total cycles:" << overallTime<<endl;
                    cout<<"Total cycles:" << overallTime<<endl;
                    cout<<"AVGtt:"<< avgTT/50<<endl;
                    cout<<"AVGwt:"<<avgWT/50<<endl;
                    break;
                }
            case 2:
                {

                priority_queue<unsigned long long> pqSJF1;
                    for(int n = 0; n<50; n++){
                        pqSJF1.push(-(pro[n].serviceTime));
                    }
                    while(!pqSJF1.empty()){
                        unsigned long long temp = pqSJF1.top();
                        pqSJF1.pop();
                        int i = 0;
                        while (pro[i].serviceTime != -(temp)){
                            i++;
                        }
                        if(essor1.memory>=pro[i].memory && totTime1 <= totTime2){
                            q1.push(pro[i]);
                            cout<<"Process number:" << pro[i].ID<<endl<<"Service time:"<<pro[i].serviceTime<<endl<<"Arrival time:"<<0<<endl;
                            cout<<"Memory requirements:"<< pro[i].memory<<endl<<"Wait time:"<<totTime1<<endl<<"Total time in system:"<<totTime1+pro[i].serviceTime<<endl;
                            cout<<"In processor 1"<<endl;
                            totTime1 = pro[i].serviceTime;
                        }else if(essor2.memory>=pro[i].memory){
                            q2.push(pro[i]);
                            cout<<"Process number:" << pro[i].ID<<endl<<"Service time:"<<pro[i].serviceTime<<endl<<"Arrival time:"<<0<<endl;
                            cout<<"Memory requirements:"<< pro[i].memory<<endl<<"Wait time:"<<totTime2<<endl<<"Total time in system:"<<totTime2+pro[i].serviceTime<<endl;
                            cout<<"In processor 2"<<endl;
                            totTime2 += pro[i].serviceTime;
                        }else if(essor3.memory>=pro[i].memory && totTime3<=totTime4){
                            q3.push(pro[i]);
                            cout<<"Process number:" << pro[i].ID<<endl<<"Service time:"<<pro[i].serviceTime<<endl<<"Arrival time:"<<0<<endl;
                            cout<<"Memory requirements:"<< pro[i].memory<<endl<<"Wait time:"<<totTime3<<endl<<"Total time in system:"<<totTime3+pro[i].serviceTime<<endl;
                            cout<<"In processor 3"<<endl;
                            totTime3 += pro[i].serviceTime;
                        }else if(essor4.memory>=pro[i].memory){
                            q4.push(pro[i]);
                            cout<<"Process number:" << pro[i].ID<<endl<<"Service time:"<<pro[i].serviceTime<<endl<<"Arrival time:"<<0<<endl;
                            cout<<"Memory requirements:"<< pro[i].memory<<endl<<"Wait time:"<<totTime4<<endl<<"Total time in system:"<<totTime4+pro[i].serviceTime<<endl;
                            cout<<"In processor 4"<<endl;
                            totTime4 += pro[i].serviceTime;
                        }
                    }
                    unsigned long long overallTime = totTime1;
                    if(totTime2>overallTime){
                        overallTime = totTime2;
                    }
                    if(totTime3>overallTime){
                        overallTime = totTime3;
                    }
                    if(totTime4>overallTime){
                        overallTime = totTime4;
                    }
                    cout<<"Total cycles:" << overallTime<<endl;

                    break;
                }
            case 3:
                {

                priority_queue<unsigned long long> pqSJF1;
                    for(int n = 0; n<50; n++){
                        pqSJF1.push(-(pro[n].serviceTime));
                    }
                    while(!pqSJF1.empty()){
                        unsigned long long temp = pqSJF1.top();
                        pqSJF1.pop();
                        int i = 0;
                        while (pro[i].serviceTime != -(temp)){
                            i++;
                        }
                        if(essor1.memory>=pro[i].memory && totTime1 <= totTime2){
                            q1.push(pro[i]);
                            cout<<"Process number:" << pro[i].ID<<endl;
                            /*
                            cout<<"Service time:"<<pro[i].serviceTime<<endl<<"Arrival time:"<<0<<endl;
                            cout<<"Memory requirements:"<< pro[i].memory<<endl<<"Wait time:"<<totTime1<<endl<<"Total time in system:"<<totTime1+pro[i].serviceTime<<endl;
                            cout<<"In processor 1"<<endl;
                            */
                            avgWT += totTime1;
                            avgTT += (totTime1+pro[i].serviceTime);
                            totTime1 = pro[i].serviceTime;
                        }else if(essor2.memory>=pro[i].memory){
                            q2.push(pro[i]);
                            cout<<"Process number:" << pro[i].ID<<endl;
                            /*
                            cout<<"Service time:"<<pro[i].serviceTime<<endl<<"Arrival time:"<<0<<endl;
                            cout<<"Memory requirements:"<< pro[i].memory<<endl<<"Wait time:"<<totTime2<<endl<<"Total time in system:"<<totTime2+pro[i].serviceTime<<endl;
                            cout<<"In processor 2"<<endl;
                            */
                            avgWT += totTime2;
                            avgTT += (totTime2+pro[i].serviceTime);
                            totTime2 += pro[i].serviceTime;
                        }else if(essor3.memory>=pro[i].memory && totTime3<=totTime4){
                            q3.push(pro[i]);
                            cout<<"Process number:" << pro[i].ID<<endl;
                            /*
                            cout<<"Service time:"<<pro[i].serviceTime<<endl<<"Arrival time:"<<0<<endl;
                            cout<<"Memory requirements:"<< pro[i].memory<<endl<<"Wait time:"<<totTime3<<endl<<"Total time in system:"<<totTime3+pro[i].serviceTime<<endl;
                            cout<<"In processor 3"<<endl;
                            */
                            avgWT += totTime3;
                            avgTT += (totTime3+pro[i].serviceTime);
                            totTime3 += pro[i].serviceTime;
                        }else if(essor4.memory>=pro[i].memory){
                            q4.push(pro[i]);
                            cout<<"Process number:" << pro[i].ID<<endl;
                            /*
                            cout<<"Service time:"<<pro[i].serviceTime<<endl<<"Arrival time:"<<0<<endl;
                            cout<<"Memory requirements:"<< pro[i].memory<<endl<<"Wait time:"<<totTime4<<endl<<"Total time in system:"<<totTime4+pro[i].serviceTime<<endl;
                            cout<<"In processor 4"<<endl;
                            */
                            avgWT += totTime4;
                            avgTT += (totTime4+pro[i].serviceTime);
                            totTime4 += pro[i].serviceTime;
                        }
                    }
                    unsigned long long overallTime = totTime1;
                    if(totTime2>overallTime){
                        overallTime = totTime2;
                    }
                    if(totTime3>overallTime){
                        overallTime = totTime3;
                    }
                    if(totTime4>overallTime){
                        overallTime = totTime4;
                    }
                    cout<<"Total cycles:" << overallTime<<endl;
                    cout<<"AVGtt:"<< avgTT/50<<endl;
                    cout<<"AVGwt:"<<avgWT/50<<endl;

                    break;
                }
            case 4:
                break;
            case 5:{
                    priority_queue<int> pqML;
                    for(int n = 0; n<50; n++){
                      pqML.push(pro[n].priority);
                    }
                    while(!pqML.empty()){
                        int temp = pqML.top();
                        pqML.pop();
                        int i = 0;
                        while (pro[i].priority != temp || pro[i].done == true){
                            i++;
                        }
                        pro[i].done = true;
                        if(essor1.memory>=pro[i].memory && totTime1 <= totTime2){
                            q1.push(pro[i]);
                            cout<<"Process number:" << pro[i].ID<<endl<<"Service time:"<<pro[i].serviceTime<<endl<<"Arrival time:"<<0<<endl;
                            cout<<"Memory requirements:"<< pro[i].memory<<endl<<"Wait time:"<<totTime1<<endl<<"Total time in system:"<<totTime1+pro[i].serviceTime<<endl;
                            cout<<"In processor 1"<<endl;
                            totTime1 = pro[i].serviceTime;
                        }else if(essor2.memory>=pro[i].memory){
                            q2.push(pro[i]);
                            cout<<"Process number:" << pro[i].ID<<endl<<"Service time:"<<pro[i].serviceTime<<endl<<"Arrival time:"<<0<<endl;
                            cout<<"Memory requirements:"<< pro[i].memory<<endl<<"Wait time:"<<totTime2<<endl<<"Total time in system:"<<totTime2+pro[i].serviceTime<<endl;
                            cout<<"In processor 2"<<endl;
                            totTime2 += pro[i].serviceTime;
                        }else if(essor3.memory>=pro[i].memory && totTime3<=totTime4){
                            q3.push(pro[i]);
                            cout<<"Process number:" << pro[i].ID<<endl<<"Service time:"<<pro[i].serviceTime<<endl<<"Arrival time:"<<0<<endl;
                            cout<<"Memory requirements:"<< pro[i].memory<<endl<<"Wait time:"<<totTime3<<endl<<"Total time in system:"<<totTime3+pro[i].serviceTime<<endl;
                            cout<<"In processor 3"<<endl;
                            totTime3 += pro[i].serviceTime;
                        }else if(essor4.memory>=pro[i].memory){
                            q4.push(pro[i]);
                            cout<<"Process number:" << pro[i].ID<<endl<<"Service time:"<<pro[i].serviceTime<<endl<<"Arrival time:"<<0<<endl;
                            cout<<"Memory requirements:"<< pro[i].memory<<endl<<"Wait time:"<<totTime4<<endl<<"Total time in system:"<<totTime4+pro[i].serviceTime<<endl;
                            cout<<"In processor 4"<<endl;
                            totTime4 += pro[i].serviceTime;
                        }
                    }
                    unsigned long long overallTime = totTime1;
                    if(totTime2>overallTime){
                        overallTime = totTime2;
                    }
                    if(totTime3>overallTime){
                        overallTime = totTime3;
                    }
                    if(totTime4>overallTime){
                        overallTime = totTime4;
                    }
                    cout<<"Total cycles:" << overallTime<<endl;
                    break;
                    }
            default:
                break;
            }
            break;
            }
        case 3:
            {Processor essor1;
            essor1.memory = 8;
            essor1.speed = 2;
            unsigned long long totTime1 = 0;
            unsigned long long avg1;
            queue<Process> q1;
            Processor essor2;
            essor2.memory = 8;
            essor2.speed = 2;
            unsigned long long totTime2 = 0;
            unsigned long long avg2;
            queue<Process> q2;
            Processor essor3;
            essor3.memory = 8;
            essor3.speed = 3;
            unsigned long long totTime3 = 0;
            unsigned long long avg3 = totTime3/essor3.speed;
            queue<Process> q3;
            Processor essor4;
            essor4.memory = 8;
            essor4.speed = 4;
            unsigned long long totTime4 = 0;
            unsigned long long avg4;
            unsigned long long avgTT = 0;
            unsigned long long avgWT = 0;
            queue<Process> q4;
            switch(sortAl){
                case 1:{
                    for(int i = 0; i<50; i++){
                        avg1 = totTime1/essor1.speed;
                        avg2 = totTime2/essor2.speed;
                        avg3 = totTime3/essor3.speed;
                        avg4 = totTime4/essor4.speed;
                        if(avg1 <= avg2 && avg1 <= avg3 && avg1<= avg4){
                            q1.push(pro[i]);
                            cout<<"Process number:" << pro[i].ID<<endl<<"Service time:"<<pro[i].serviceTime<<endl<<"Arrival time:"<<0<<endl;
                            cout<<"Memory requirements:"<< pro[i].memory<<endl<<"Wait time:"<<totTime1<<endl<<"Total time in system:"<<totTime1+pro[i].serviceTime<<endl;
                            cout<<"In processor 1"<<endl;
                            avgTT += (totTime1+pro[i].serviceTime);
                            avgWT += totTime1;
                            totTime1 = pro[i].serviceTime;
                        }else if(avg2 <= avg1 && avg2 <= avg3 && avg2<= avg4){
                            q2.push(pro[i]);
                            cout<<"Process number:" << pro[i].ID<<endl<<"Service time:"<<pro[i].serviceTime<<endl<<"Arrival time:"<<0<<endl;
                            cout<<"Memory requirements:"<< pro[i].memory<<endl<<"Wait time:"<<totTime2<<endl<<"Total time in system:"<<totTime2+pro[i].serviceTime<<endl;
                            cout<<"In processor 2"<<endl;
                            avgTT += (totTime2+pro[i].serviceTime);
                            avgWT += totTime2;
                            totTime2 += pro[i].serviceTime;
                        }else if(avg3 <= avg2 && avg3 <= avg1 && avg3<= avg4){
                            q3.push(pro[i]);
                            cout<<"Process number:" << pro[i].ID<<endl<<"Service time:"<<pro[i].serviceTime<<endl<<"Arrival time:"<<0<<endl;
                            cout<<"Memory requirements:"<< pro[i].memory<<endl<<"Wait time:"<<totTime3<<endl<<"Total time in system:"<<totTime3+pro[i].serviceTime<<endl;
                            cout<<"In processor 3"<<endl;
                            avgTT += (totTime3+pro[i].serviceTime);
                            avgWT += totTime3;
                            totTime3 += pro[i].serviceTime;
                        }else if(avg4 <= avg2 && avg4 <= avg3 && avg4<= avg1){
                            q4.push(pro[i]);
                            cout<<"Process number:" << pro[i].ID<<endl<<"Service time:"<<pro[i].serviceTime<<endl<<"Arrival time:"<<0<<endl;
                            cout<<"Memory requirements:"<< pro[i].memory<<endl<<"Wait time:"<<totTime4<<endl<<"Total time in system:"<<totTime4+pro[i].serviceTime<<endl;
                            cout<<"In processor 4"<<endl;
                            avgTT += (totTime4+pro[i].serviceTime);
                            avgWT += totTime4;
                            totTime4 += pro[i].serviceTime;
                        }
                    }
                    unsigned long long overallTime = totTime1;
                    if(totTime2>overallTime){
                        overallTime = totTime2;
                    }
                    if(totTime3>overallTime){
                        overallTime = totTime3;
                    }
                    if(totTime4>overallTime){
                        overallTime = totTime4;
                    }
                    cout<<"Total cycles:" << overallTime<<endl;
                    cout<<"Total cycles:" << overallTime<<endl;
                    cout<<"AVGtt:"<< avgTT/50<<endl;
                    cout<<"AVGwt:"<<avgWT/50<<endl;
                    break;
                    }
                case 2:{
                    priority_queue<unsigned long long> pqSJF1;
                    for(int n = 0; n<50; n++){
                        pqSJF1.push(-(pro[n].serviceTime));
                    }
                    while(!pqSJF1.empty()){
                        avg1 = totTime1/essor1.speed;
                        avg2 = totTime2/essor2.speed;
                        avg3 = totTime3/essor3.speed;
                        avg4 = totTime4/essor4.speed;
                        unsigned long long temp = pqSJF1.top();
                        pqSJF1.pop();
                        int i = 0;
                        while (pro[i].serviceTime != -(temp)){
                            i++;
                        }
                    if(avg1 <= avg2 && avg1 <= avg3 && avg1<= avg4){
                            q1.push(pro[i]);
                            cout<<"Process number:" << pro[i].ID<<endl<<"Service time:"<<pro[i].serviceTime<<endl<<"Arrival time:"<<0<<endl;
                            cout<<"Memory requirements:"<< pro[i].memory<<endl<<"Wait time:"<<totTime1<<endl<<"Total time in system:"<<totTime1+pro[i].serviceTime<<endl;
                            cout<<"In processor 1"<<endl;
                            totTime1 = pro[i].serviceTime;
                        }else if(avg2 <= avg1 && avg2 <= avg3 && avg2<= avg4){
                            q2.push(pro[i]);
                            cout<<"Process number:" << pro[i].ID<<endl<<"Service time:"<<pro[i].serviceTime<<endl<<"Arrival time:"<<0<<endl;
                            cout<<"Memory requirements:"<< pro[i].memory<<endl<<"Wait time:"<<totTime2<<endl<<"Total time in system:"<<totTime2+pro[i].serviceTime<<endl;
                            cout<<"In processor 2"<<endl;
                            totTime2 += pro[i].serviceTime;
                        }else if(avg3 <= avg2 && avg3 <= avg1 && avg3<= avg4){
                            q3.push(pro[i]);
                            cout<<"Process number:" << pro[i].ID<<endl<<"Service time:"<<pro[i].serviceTime<<endl<<"Arrival time:"<<0<<endl;
                            cout<<"Memory requirements:"<< pro[i].memory<<endl<<"Wait time:"<<totTime3<<endl<<"Total time in system:"<<totTime3+pro[i].serviceTime<<endl;
                            cout<<"In processor 3"<<endl;
                            totTime3 += pro[i].serviceTime;
                        }else if(avg4 <= avg2 && avg4 <= avg3 && avg4<= avg1){
                            q4.push(pro[i]);
                            cout<<"Process number:" << pro[i].ID<<endl<<"Service time:"<<pro[i].serviceTime<<endl<<"Arrival time:"<<0<<endl;
                            cout<<"Memory requirements:"<< pro[i].memory<<endl<<"Wait time:"<<totTime4<<endl<<"Total time in system:"<<totTime4+pro[i].serviceTime<<endl;
                            cout<<"In processor 4"<<endl;
                            totTime4 += pro[i].serviceTime;
                        }
                    }
                    unsigned long long overallTime = totTime1;
                    if(totTime2>overallTime){
                        overallTime = totTime2;
                    }
                    if(totTime3>overallTime){
                        overallTime = totTime3;
                    }
                    if(totTime4>overallTime){
                        overallTime = totTime4;
                    }
                    cout<<"Total cycles:" << overallTime<<endl;
                    break;
                }
                case 3:{
                    priority_queue<unsigned long long> pqSJF1;
                    for(int n = 0; n<50; n++){
                        pqSJF1.push(-(pro[n].serviceTime));
                    }
                    while(!pqSJF1.empty()){
                        avg1 = totTime1/essor1.speed;
                        avg2 = totTime2/essor2.speed;
                        avg3 = totTime3/essor3.speed;
                        avg4 = totTime4/essor4.speed;
                        unsigned long long temp = pqSJF1.top();
                        pqSJF1.pop();
                        int i = 0;
                        while (pro[i].serviceTime != -(temp)){
                            i++;
                        }
                    if(avg1 <= avg2 && avg1 <= avg3 && avg1<= avg4){
                            q1.push(pro[i]);
                            cout<<"Process number:" << pro[i].ID<<endl;
                            /*
                            cout<<"Service time:"<<pro[i].serviceTime<<endl<<"Arrival time:"<<0<<endl;
                            cout<<"Memory requirements:"<< pro[i].memory<<endl<<"Wait time:"<<totTime1<<endl<<"Total time in system:"<<totTime1+pro[i].serviceTime<<endl;
                            cout<<"In processor 1"<<endl;
                            */
                            avgWT += totTime1;
                            avgTT += (totTime1+pro[i].serviceTime);
                            totTime1 = pro[i].serviceTime;
                        }else if(avg2 <= avg1 && avg2 <= avg3 && avg2<= avg4){
                            q2.push(pro[i]);
                            cout<<"Process number:" << pro[i].ID<<endl;
                            /*
                            cout<<"Service time:"<<pro[i].serviceTime<<endl<<"Arrival time:"<<0<<endl;
                            cout<<"Memory requirements:"<< pro[i].memory<<endl<<"Wait time:"<<totTime2<<endl<<"Total time in system:"<<totTime2+pro[i].serviceTime<<endl;
                            cout<<"In processor 2"<<endl;
                            */
                            avgWT += totTime2;
                            avgTT += (totTime2+pro[i].serviceTime);
                            totTime2 += pro[i].serviceTime;
                        }else if(avg3 <= avg2 && avg3 <= avg1 && avg3<= avg4){
                            q3.push(pro[i]);
                            cout<<"Process number:" << pro[i].ID<<endl;
                            /*
                            cout<<"Service time:"<<pro[i].serviceTime<<endl<<"Arrival time:"<<0<<endl;
                            cout<<"Memory requirements:"<< pro[i].memory<<endl<<"Wait time:"<<totTime3<<endl<<"Total time in system:"<<totTime3+pro[i].serviceTime<<endl;
                            cout<<"In processor 3"<<endl;
                            */
                            avgWT += totTime3;
                            avgTT += (totTime3+pro[i].serviceTime);
                            totTime3 += pro[i].serviceTime;
                        }else if(avg4 <= avg2 && avg4 <= avg3 && avg4<= avg1){
                            q4.push(pro[i]);
                            cout<<"Process number:" << pro[i].ID<<endl;
                            /*
                            cout<<"Service time:"<<pro[i].serviceTime<<endl<<"Arrival time:"<<0<<endl;
                            cout<<"Memory requirements:"<< pro[i].memory<<endl<<"Wait time:"<<totTime4<<endl<<"Total time in system:"<<totTime4+pro[i].serviceTime<<endl;
                            cout<<"In processor 4"<<endl;
                            */
                            avgWT += totTime4;
                            avgTT += (totTime4+pro[i].serviceTime);
                            totTime4 += pro[i].serviceTime;
                        }
                    }
                    unsigned long long overallTime = totTime1;
                    if(totTime2>overallTime){
                        overallTime = totTime2;
                    }
                    if(totTime3>overallTime){
                        overallTime = totTime3;
                    }
                    if(totTime4>overallTime){
                        overallTime = totTime4;
                    }
                    cout<<"Total cycles:" << overallTime<<endl;
                    cout<<"AVGtt:"<< avgTT/50<<endl;
                    cout<<"AVGwt:"<<avgWT/50<<endl;
                    break;
                }
                case 4:
                    break;
                case 5:{
                    priority_queue<int> pqML;
                    for(int n = 0; n<50; n++){
                      pqML.push(pro[n].priority);
                    }
                    while(!pqML.empty()){
                        avg1 = totTime1/essor1.speed;
                        avg2 = totTime2/essor2.speed;
                        avg3 = totTime3/essor3.speed;
                        avg4 = totTime4/essor4.speed;
                        int temp = pqML.top();
                        pqML.pop();
                        int i = 0;
                        while (pro[i].priority != temp || pro[i].done == true){
                            i++;
                        }
                        pro[i].done = true;
                        if(avg1 <= avg2 && avg1 <= avg3 && avg1<= avg4){
                            q1.push(pro[i]);
                            cout<<"Process number:" << pro[i].ID<<endl<<"Service time:"<<pro[i].serviceTime<<endl<<"Arrival time:"<<0<<endl;
                            cout<<"Memory requirements:"<< pro[i].memory<<endl<<"Wait time:"<<totTime1<<endl<<"Total time in system:"<<totTime1+pro[i].serviceTime<<endl;
                            cout<<"In processor 1"<<endl;
                            totTime1 = pro[i].serviceTime;
                        }else if(avg2 <= avg1 && avg2 <= avg3 && avg2<= avg4){
                            q2.push(pro[i]);
                            cout<<"Process number:" << pro[i].ID<<endl<<"Service time:"<<pro[i].serviceTime<<endl<<"Arrival time:"<<0<<endl;
                            cout<<"Memory requirements:"<< pro[i].memory<<endl<<"Wait time:"<<totTime2<<endl<<"Total time in system:"<<totTime2+pro[i].serviceTime<<endl;
                            cout<<"In processor 2"<<endl;
                            totTime2 += pro[i].serviceTime;
                        }else if(avg3 <= avg2 && avg3 <= avg1 && avg3<= avg4){
                            q3.push(pro[i]);
                            cout<<"Process number:" << pro[i].ID<<endl<<"Service time:"<<pro[i].serviceTime<<endl<<"Arrival time:"<<0<<endl;
                            cout<<"Memory requirements:"<< pro[i].memory<<endl<<"Wait time:"<<totTime3<<endl<<"Total time in system:"<<totTime3+pro[i].serviceTime<<endl;
                            cout<<"In processor 3"<<endl;
                            totTime3 += pro[i].serviceTime;
                        }else if(avg4 <= avg2 && avg4 <= avg3 && avg4<= avg1){
                            q4.push(pro[i]);
                            cout<<"Process number:" << pro[i].ID<<endl<<"Service time:"<<pro[i].serviceTime<<endl<<"Arrival time:"<<0<<endl;
                            cout<<"Memory requirements:"<< pro[i].memory<<endl<<"Wait time:"<<totTime4<<endl<<"Total time in system:"<<totTime4+pro[i].serviceTime<<endl;
                            cout<<"In processor 4"<<endl;
                            totTime4 += pro[i].serviceTime;
                        }
                    }
                    unsigned long long overallTime = totTime1;
                    if(totTime2>overallTime){
                        overallTime = totTime2;
                    }
                    if(totTime3>overallTime){
                        overallTime = totTime3;
                    }
                    if(totTime4>overallTime){
                        overallTime = totTime4;
                    }
                    cout<<"Total cycles:" << overallTime<<endl;
                    break;
                    }
                }
                break;
                }
        case 4:
            {Processor essor1;
            essor1.memory = 8;
            essor1.speed = 3000000000;
            unsigned long long totTime1 = 0;
            queue<Process> q1;
            Processor essor2;
            essor2.memory = 8;
            essor2.speed = 3000000000;
            unsigned long long totTime2 = 0;
            queue<Process> q2;
            Processor essor3;
            essor3.memory = 8;
            essor3.speed = 3000000000;
            unsigned long long totTime3 = 0;
            queue<Process> q3;
            Processor essor4;
            essor4.memory = 8;
            essor4.speed = 3000000000;
            unsigned long long totTime4 = 0;
            Process p1; //stores current processes on each processor
            Process p2;
            Process p3;
            Process p4;
            unsigned long long avgTT = 0;
            unsigned long long avgWT = 0;
            queue<Process> q4;
            switch(sortAl){
                case 1:{
                    priority_queue<unsigned long long> pQ;
                    for(int n = 0; n<50; n++){
                        pQ.push(-(pro[n].arrivalTime));
                    }
                    while(!pQ.empty()){
                        unsigned long long temp = pQ.top();
                        pQ.pop();
                        int i = 0;
                        while (-(pro[i].arrivalTime) != temp){
                            i++;
                        }
                        if(totTime1<=totTime2 && totTime1<=totTime3 && totTime1<=totTime4){
                            q1.push(pro[i]);
                            if(totTime1 == 0){
                               totTime1 += pro[i].arrivalTime;
                            }
                            if(totTime1<pro[i].arrivalTime){
                                totTime1 = pro[i].arrivalTime;
                            }
                            cout<<"Process number:" << pro[i].ID<<endl;
                            //cout<<"Service time:"<<pro[i].serviceTime<<endl<<"Arrival time:"<<pro[i].arrivalTime<<endl;
                            //cout<<"Memory requirements:"<< pro[i].memory<<endl<<"Wait time:"<<totTime1-pro[i].arrivalTime<<endl<<"Total time in system:"<<(totTime1 +pro[i].serviceTime) - pro[i].arrivalTime<<endl;
                            //cout<<"In processor 1"<<endl;
                            avgTT += (totTime1 +pro[i].serviceTime) - pro[i].arrivalTime;
                            avgWT += totTime1-pro[i].arrivalTime;
                            totTime1 += pro[i].serviceTime;
                        }else if(totTime2 <=totTime3 && totTime2 <=totTime1 && totTime2 <=totTime4){
                            q2.push(pro[i]);
                            if(totTime2 == 0){
                               totTime2 += pro[i].arrivalTime;
                            }
                            if(totTime2<pro[i].arrivalTime){
                                totTime2 = pro[i].arrivalTime;
                            }
                            cout<<"Process number:" << pro[i].ID<<endl;
                            //cout<<"Service time:"<<pro[i].serviceTime<<endl<<"Arrival time:"<<pro[i].arrivalTime<<endl;
                            //cout<<"Memory requirements:"<< pro[i].memory<<endl<<"Wait time:"<<totTime2-pro[i].arrivalTime<<endl<<"Total time in system:"<<(totTime2 + pro[i].serviceTime) - pro[i].arrivalTime<<endl;
                            //cout<<"In processor 2"<<endl;
                            avgTT += (totTime2 +pro[i].serviceTime) - pro[i].arrivalTime;
                            avgWT += totTime2-pro[i].arrivalTime;
                            totTime2 += pro[i].serviceTime;
                        }else if(totTime3 <= totTime4 && totTime3 <= totTime2 && totTime3 <= totTime1){
                            q3.push(pro[i]);
                            if(totTime3 == 0){
                               totTime3 += pro[i].arrivalTime;
                            }
                            if(totTime3<pro[i].arrivalTime){
                                totTime3 = pro[i].arrivalTime;
                            }
                            cout<<"Process number:" << pro[i].ID<<endl;
                            //cout<<"Service time:"<<pro[i].serviceTime<<endl<<"Arrival time:"<<pro[i].arrivalTime<<endl;
                            //cout<<"Memory requirements:"<< pro[i].memory<<endl<<"Wait time:"<<totTime3-pro[i].arrivalTime<<endl<<"Total time in system:"<<(totTime3+pro[i].serviceTime)-pro[i].arrivalTime<<endl;
                            //cout<<"In processor 3"<<endl;
                            avgTT += (totTime3 +pro[i].serviceTime) - pro[i].arrivalTime;
                            avgWT += totTime3-pro[i].arrivalTime;
                            totTime3 += pro[i].serviceTime;
                        }else if(totTime4 <= totTime1 && totTime4 <= totTime2 && totTime4 <= totTime3){
                            q4.push(pro[i]);
                            if(totTime4 == 0){
                               totTime4 += pro[i].arrivalTime;
                            }
                            if(totTime4<pro[i].arrivalTime){
                                totTime4 = pro[i].arrivalTime;
                            }
                            cout<<"Process number:" << pro[i].ID<<endl;
                            //cout<<"Service time:"<<pro[i].serviceTime<<endl<<"Arrival time:"<<pro[i].arrivalTime<<endl;
                            //cout<<"Memory requirements:"<< pro[i].memory<<endl<<"Wait time:"<<totTime4-pro[i].arrivalTime<<endl<<"Total time in system:"<<(totTime4+pro[i].serviceTime)-pro[i].arrivalTime<<endl;
                            //cout<<"In processor 4"<<endl;
                            avgTT += (totTime4 +pro[i].serviceTime) - pro[i].arrivalTime;
                            avgWT += totTime4-pro[i].arrivalTime;
                            totTime4 += pro[i].serviceTime;
                        }
                    }
                    unsigned long long overallTime = totTime1;
                    if(totTime2>overallTime){
                        overallTime = totTime2;
                    }
                    if(totTime3>overallTime){
                        overallTime = totTime3;
                    }
                    if(totTime4>overallTime){
                        overallTime = totTime4;
                    }
                    cout<<"Total cycles:" << overallTime<<endl;
                    cout<<"Total cycles:" << overallTime<<endl;
                    cout<<"AVGtt:"<< avgTT/50<<endl;
                    cout<<"AVGwt:"<<avgWT/50<<endl;
                    break;
                }
                case 2:{
                    priority_queue<unsigned long long> pqSJF;
                    priority_queue<unsigned long long> arrivalPQ;
                    unsigned long long smallestTime = 0;
                    unsigned long long sortedSJF[50];
                    for(int n = 0; n<50; n++){ //places the processes into a priority queue based on their service times
                        pqSJF.push(-(pro[n].serviceTime));
                    }
                    for(int m = 0; m<50; m++){ //places the processes into a priority queue based on their arrival times
                        arrivalPQ.push(-(pro[m].arrivalTime));
                    }
                    for(int j = 0; j<50; j++){ //takes the priority queue of service times and places into an array
                            unsigned long long temp2 = -(pqSJF.top());
                            sortedSJF[j] = temp2;
                            for(int finding = 0; finding<50; finding++){
                               if(temp2 == pro[finding].serviceTime){
                                    pro[finding].SJFrank = j; //sets the rank of the process in sjf
                               }
                            }
                            pqSJF.pop();
                    }
                    while(!arrivalPQ.empty()){
                        int i = 0;
                        if(totTime1 == 0 || totTime2 == 0 || totTime3 == 0 || totTime4 ==0){
                           unsigned long long temp = -(arrivalPQ.top());
                            arrivalPQ.pop();
                            while(pro[i].arrivalTime != temp){
                                i++;
                            }
                        }else{
                           unsigned long long temp3 = -(arrivalPQ.top());
                            while(pro[i].arrivalTime != temp3){
                                i++;
                            }
                            int save = i; //stores the arrival time of the popped process
                            for(int h = 0; h<50; h++){
                                if(pro[h].arrivalTime<smallestTime && pro[h].SJFrank<pro[i].SJFrank && pro[h].done == false){
                                    i = h;
                                }
                            }
                            if(i == save){
                                arrivalPQ.pop();
                            }
                        }
                        if(pro[i].done == false){
                        if(totTime1<=totTime2 && totTime1<=totTime3 && totTime1<=totTime4){
                            q1.push(pro[i]);
                            if(totTime1 == 0){
                               totTime1 += pro[i].arrivalTime;
                            }
                            if(totTime1<pro[i].arrivalTime){
                                totTime1 = pro[i].arrivalTime;
                            }
                            cout<<"Process number:" << pro[i].ID<<endl<<"Service time:"<<pro[i].serviceTime<<endl<<"Arrival time:"<<pro[i].arrivalTime<<endl;
                            cout<<"Memory requirements:"<< pro[i].memory<<endl<<"Wait time:"<<totTime1-pro[i].arrivalTime<<endl<<"Total time in system:"<<(totTime1 - pro[i].arrivalTime)+pro[i].serviceTime<<endl;
                            cout<<"In processor 1"<<endl;
                            totTime1 += pro[i].serviceTime;
                        }else if(totTime2 <=totTime3 && totTime2 <=totTime1 && totTime2 <=totTime4){
                            q2.push(pro[i]);
                            if(totTime2 == 0){
                               totTime2 += pro[i].arrivalTime;
                            }
                            if(totTime2<pro[i].arrivalTime){
                                totTime2 = pro[i].arrivalTime;
                            }
                            cout<<"Process number:" << pro[i].ID<<endl<<"Service time:"<<pro[i].serviceTime<<endl<<"Arrival time:"<<pro[i].arrivalTime<<endl;
                            cout<<"Memory requirements:"<< pro[i].memory<<endl<<"Wait time:"<<totTime2-pro[i].arrivalTime<<endl<<"Total time in system:"<<(totTime2 - pro[i].arrivalTime)+pro[i].serviceTime<<endl;
                            cout<<"In processor 2"<<endl;
                            totTime2 += pro[i].serviceTime;
                        }else if(totTime3 <= totTime4 && totTime3 <= totTime2 && totTime3 <= totTime1){
                            q3.push(pro[i]);
                            if(totTime3 == 0){
                               totTime3 += pro[i].arrivalTime;
                            }
                            if(totTime3<pro[i].arrivalTime){
                                totTime3 = pro[i].arrivalTime;
                            }
                            cout<<"Process number:" << pro[i].ID<<endl<<"Service time:"<<pro[i].serviceTime<<endl<<"Arrival time:"<<pro[i].arrivalTime<<endl;
                            cout<<"Memory requirements:"<< pro[i].memory<<endl<<"Wait time:"<<totTime3-pro[i].arrivalTime<<endl<<"Total time in system:"<<(totTime3-pro[i].arrivalTime)+pro[i].serviceTime<<endl;
                            cout<<"In processor 3"<<endl;
                            totTime3 += pro[i].serviceTime;
                        }else if(totTime4 <= totTime1 && totTime4 <= totTime2 && totTime4 <= totTime3){
                            q4.push(pro[i]);
                            if(totTime4 == 0){
                               totTime4 += pro[i].arrivalTime;
                            }
                            if(totTime1<pro[i].arrivalTime){
                                totTime1 = pro[i].arrivalTime;
                            }
                            cout<<"Process number:" << pro[i].ID<<endl<<"Service time:"<<pro[i].serviceTime<<endl<<"Arrival time:"<<pro[i].arrivalTime<<endl;
                            cout<<"Memory requirements:"<< pro[i].memory<<endl<<"Wait time:"<<totTime4-pro[i].arrivalTime<<endl<<"Total time in system:"<<(totTime4-pro[i].arrivalTime)+pro[i].serviceTime<<endl;
                            cout<<"In processor 4"<<endl;
                            totTime4 += pro[i].serviceTime;
                        }
                        smallestTime = totTime1;
                        if(smallestTime>totTime2){
                            smallestTime = totTime2;
                        }
                        if(smallestTime>totTime3){
                            smallestTime = totTime3;
                        }
                        if(smallestTime>totTime4){
                            smallestTime = totTime4;
                        }
                        pro[i].done = true;
                    }

                    }
                    unsigned long long overallTime = totTime1;
                    if(totTime2>overallTime){
                        overallTime = totTime2;
                    }
                    if(totTime3>overallTime){
                        overallTime = totTime3;
                    }
                    if(totTime4>overallTime){
                        overallTime = totTime4;
                    }
                    cout<<"Total cycles:" << overallTime<<endl;
                    break;
                }
                case 3:{
                    priority_queue<unsigned long long> arrivalSRT;//stores processes in order based on arrival time
                    priority_queue<unsigned long long> available;//stores processes that have not finished but are not on processor by SRT
                    Process currentPro; //stores current process on processor
                    unsigned long long nextArr; //stores the rt of next process to arrive
                    for(int n =0; n<50; n++){ //adds processes to pq based on arrival time
                        arrivalSRT.push(-(pro[n].arrivalTime));
                    }
                    ////
                    for(int m = 0; m<4; m++){//places the first four processes on a processor
                      unsigned long long temp = -(arrivalSRT.top());
                      arrivalSRT.pop();
                      int u = 0;
                      while(pro[u].arrivalTime != temp){
                        u++;
                      }
                      if(m == 0){
                        q1.push(pro[u]);
                        totTime1 = pro[u].arrivalTime;
                        p1 = pro[u];
                        pro[u].startTime = pro[u].arrivalTime;
                      }else if(m==1){
                          q2.push(pro[u]);
                           totTime2 = pro[u].arrivalTime;
                           p2 = pro[u];
                           pro[u].startTime = pro[u].arrivalTime;
                      }else if(m == 2){
                          q3.push(pro[u]);
                           totTime3 = pro[u].arrivalTime;
                           p3 = pro[u];
                           pro[u].startTime = pro[u].arrivalTime;
                      }else{
                          q4.push(pro[u]);
                          totTime4 = pro[u].arrivalTime;
                          p4 = pro[u];
                          pro[u].startTime = pro[u].arrivalTime;
                      }

                    }
                    ////
                    while(!arrivalSRT.empty() && !available.empty()){//goes until all processes have finished
                        //find smallest totTime
                        unsigned long long smallestTT = totTime1;
                        int timer = 1;
                        if(totTime2<smallestTT){
                            smallestTT = totTime2;
                            timer = 2;
                        }
                        if(totTime3<smallestTT){
                            smallestTT = totTime3;
                            timer = 3;
                        }
                        if(totTime4>smallestTT){
                            smallestTT = totTime4;
                            timer = 4;
                        }
                        ////
                        if(!arrivalSRT.empty()){
                            if(timer ==1){
                                 int c = 0;
                                 while(pro[c].ID != p1.ID){ //finds the current process on processor
                                    c++;
                                 }
                                 //adds the next arrived process to the available queue based on rt
                                 currentPro = pro[c];
                                 if(pro[c].serviceTime-(totTime1-pro[c].startTime) <= 0){
                                    pro[c].endTime = totTime1;
                                    nextArr = available.top();
                                    available.pop();
                                    int n = 0;
                                     while(nextArr != pro[n].rt){
                                        n++;
                                     }
                                    pro[c] = pro[n];
                                 }else{
                                 nextArr = arrivalSRT.top();
                                 available.push(nextArr);
                                 arrivalSRT.pop();
                                 nextArr = available.top();
                                 available.pop();
                                 //
                                 //gets information for next process
                                 int n = 0;
                                 while(nextArr != pro[n].rt){
                                    n++;
                                 }
                                 totTime1=pro[n].arrivalTime;
                                 if(pro[c].serviceTime-(totTime1-pro[c].startTime)>nextArr){
                                 //if the rt of current process is greater than the rt of next process
                                    pro[c].rt = pro[c].serviceTime-(pro[n].arrivalTime-pro[c].startTime);
                                    available.push(pro[c].rt);
                                    pro[n].startTime = pro[n].arrivalTime;
                                    p1 = pro[n];
                                 }else{
                                    totTime1 = pro[c].arrivalTime;
                                    unsigned long long tempNext = arrivalSRT.top();
                                    int tn = 0;
                                     while(tempNext != pro[tn].rt){
                                        tn++;
                                     }
                                     totTime1 = pro[tn].arrivalTime;
                                 }
                                }

                            }else if(timer == 2){
                                 int c = 0;
                                 while(pro[c].ID != p2.ID){ //finds the current process on processor
                                    c++;
                                 }
                                 //adds the next arrived process to the available queue based on rt
                                 currentPro = pro[c];
                                 if(pro[c].serviceTime-(totTime2-pro[c].startTime) <= 0){
                                    pro[c].endTime = totTime2;
                                 }else{
                                 nextArr = arrivalSRT.top();
                                 available.push(nextArr);
                                 arrivalSRT.pop();
                                 nextArr = available.top();
                                 available.pop();
                                 //
                                 //gets information for next process
                                 int n = 0;
                                 while(nextArr != pro[n].rt){
                                    n++;
                                 }
                                 totTime2=pro[n].arrivalTime;
                                 if(pro[c].serviceTime-(totTime2-pro[c].startTime)>nextArr){
                                 //if the rt of current process is greater than the rt of next process
                                    pro[c].rt = pro[c].serviceTime-(pro[n].arrivalTime-pro[c].startTime);
                                    available.push(pro[c].rt);
                                    pro[n].startTime = pro[n].arrivalTime;
                                    p2 = pro[n];
                                 }else{
                                    totTime2 = pro[c].arrivalTime;
                                    unsigned long long tempNext = arrivalSRT.top();
                                    int tn = 0;
                                     while(tempNext != pro[tn].rt){
                                        tn++;
                                     }
                                     totTime2 = pro[tn].arrivalTime;
                                 }
                                }
                            }else if(timer ==3){
                                int c = 0;
                                 while(pro[c].ID != p3.ID){ //finds the current process on processor
                                    c++;
                                 }
                                 //adds the next arrived process to the available queue based on rt
                                 currentPro = pro[c];
                                 if(pro[c].serviceTime-(totTime3-pro[c].startTime) <= 0){
                                    pro[c].endTime = totTime3;
                                 }else{
                                 nextArr = arrivalSRT.top();
                                 available.push(nextArr);
                                 arrivalSRT.pop();
                                 nextArr = available.top();
                                 available.pop();
                                 //
                                 //gets information for next process
                                 int n = 0;
                                 while(nextArr != pro[n].rt){
                                    n++;
                                 }
                                 totTime3=pro[n].arrivalTime;
                                 if(pro[c].serviceTime-(totTime3-pro[c].startTime)>nextArr){
                                 //if the rt of current process is greater than the rt of next process
                                    pro[c].rt = pro[c].serviceTime-(pro[n].arrivalTime-pro[c].startTime);
                                    available.push(pro[c].rt);
                                    pro[n].startTime = pro[n].arrivalTime;
                                    p3 = pro[n];
                                 }else{
                                    totTime3 = pro[c].arrivalTime;
                                    unsigned long long tempNext = arrivalSRT.top();
                                    int tn = 0;
                                     while(tempNext != pro[tn].rt){
                                        tn++;
                                     }
                                     totTime3 = pro[tn].arrivalTime;
                                 }
                                }
                            }else{
                                int c = 0;
                                 while(pro[c].ID != p4.ID){ //finds the current process on processor
                                    c++;
                                 }
                                 //adds the next arrived process to the available queue based on rt
                                 currentPro = pro[c];
                                 if(pro[c].serviceTime-(totTime4-pro[c].startTime) <= 0){
                                    pro[c].endTime = totTime4;
                                 }else{
                                 nextArr = arrivalSRT.top();
                                 available.push(nextArr);
                                 arrivalSRT.pop();
                                 nextArr = available.top();
                                 available.pop();
                                 //
                                 //gets information for next process
                                 int n = 0;
                                 while(nextArr != pro[n].rt){
                                    n++;
                                 }
                                 totTime4=pro[n].arrivalTime;
                                 if(pro[c].serviceTime-(totTime4-pro[c].startTime)>nextArr){
                                 //if the rt of current process is greater than the rt of next process
                                    pro[c].rt = pro[c].serviceTime-(pro[n].arrivalTime-pro[c].startTime);
                                    available.push(pro[c].rt);
                                    pro[n].startTime = pro[n].arrivalTime;
                                    p4 = pro[n];
                                 }else{
                                    totTime4 = pro[c].arrivalTime;
                                    unsigned long long tempNext = arrivalSRT.top();
                                    int tn = 0;
                                     while(tempNext != pro[tn].rt){
                                        tn++;
                                     }
                                     totTime4 = pro[tn].arrivalTime;
                                 }
                                }
                            }
                        //have to keep track of current process in queue bleh
                        //check if the rt of the next arrivalSRT is less than the rt(arrivalSRT) of the current process on smallest totTime
                        //if yes: add current process's remaining time to available and put next arrivalSRT on processor
                        //if no: add next arrivalSRT to available
                        }else{
                            //pop available
                            //add to smallest totTime
                            unsigned long long temp2 = available.top();
                            available.pop();
                            int i = 0;
                            while(pro[i].rt != temp2){
                                i++;
                            }
                            pro[i].endTime = smallestTT + pro[i].rt;
                            if(timer == 1){
                                totTime1 += pro[i].rt;
                            }if(timer == 2){
                                totTime2 += pro[i].rt;
                            }if(timer == 3){
                                totTime3 += pro[i].rt;
                            }else{
                                totTime4 += pro[i].rt;
                            }

                        }



                    }
                    for(int t = 0; t<50; t++){ //prints information about each process after all processes have finished
                        cout<<"Process number:"<<pro[t].ID<<endl<<"Service time:"<<pro[t].serviceTime<<endl;
                        cout<<"Arrival time:"<<pro[t].arrivalTime<<endl<<"Memory requirements:"<<pro[t].memory<<endl;
                        cout<<"Wait time:"<<(pro[t].endTime - pro[t].arrivalTime)-pro[t].serviceTime<<endl;
                        cout<<"Total time in system:"<< pro[t].endTime - pro[t].arrivalTime<<endl;
                        cout<<pro[t].endTime<<endl;
                    }
                    unsigned long long overallTime = totTime1;
                    if(totTime2>overallTime){
                        overallTime = totTime2;
                    }
                    if(totTime3>overallTime){
                        overallTime = totTime3;
                    }
                    if(totTime4>overallTime){
                        overallTime = totTime4;
                    }
                    cout<<"Total cycles:" << overallTime<<endl;
                    break;
                    }
                case 4:{
                    break;
                }
                case 5:
                    break;
                break;
                }
    }
}
}
