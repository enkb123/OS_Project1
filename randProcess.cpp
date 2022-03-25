//Eshen Brinkert
//March 25, 2022
//This program simulates the running of fifty processes on four different processors.
//Four different scenarios are provided for the user to chose from and the user can select one of five scheduling methods to solve the scenario.

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
    unsigned long long totatlTime; //wait time + service time


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
    cout<<"4. RR"<<endl;
    cout<<"5. ML"<<endl;
    cin>>sortAl;

    cout<< "What seed value would you like to use?"<<endl;
    cin >>seedVal;

    mt19937 gen(seedVal); //Standard mersenne_twister_engine seeded with rd()
    uniform_int_distribution<> distribMem(1, 8);
    uniform_int_distribution<> distribServ(10*pow(10,6), 10*pow(10,12));
    uniform_int_distribution<> distribAr(1, 10*pow(10,10));


    for (int n =0; n<50; n++){
        Process myPro;
        myPro.ID = n;
        myPro.memory = distribMem(gen);
        myPro.serviceTime = distribServ(gen);
        myPro.arrivalTime = distribAr(gen);
        totCycles += myPro.serviceTime;
        pro[n] = myPro;
        //cout<<pro[n].ID;
    }



    switch(scenario){
        case 1:
            {Processor essor1;
            essor1.memory = 8;
            essor1.speed = 3000000000;
            unsigned long long totTime1;
            queue<Process> q1;
            Processor essor2;
            essor2.memory = 8;
            essor2.speed = 3000000000;
            unsigned long long totTime2;
            queue<Process> q2;
            Processor essor3;
            essor3.memory = 8;
            essor3.speed = 3000000000;
            unsigned long long totTime3;
            queue<Process> q3;
            Processor essor4;
            essor4.memory = 8;
            essor4.speed = 3000000000; //3000000000 cycle/second
            unsigned long long totTime4;
            queue<Process> q4;
            switch(sortAl){
                case 1:{
                    for(int i = 0; i<50; i++){
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
                case 2:
                    break;
                case 3:
                    break;
                case 4:
                    break;
                case 5:
                    break;
                default:
                    break;
            }
            break;
            }
        case 2:
            {Processor essor1;
            essor1.memory = 2;
            essor1.speed = 3000000000;
            unsigned long long totTime1;
            queue<Process> q1;
            Processor essor2;
            essor2.memory = 2;
            essor2.speed = 3000000000;
            unsigned long long totTime2;
            queue<Process> q2;
            Processor essor3;
            essor3.memory = 4;
            essor3.speed = 3000000000;
            unsigned long long totTime3;
            queue<Process> q3;
            Processor essor4;
            essor4.memory = 8;
            essor4.speed = 3000000000; //3000000000 cycle/second
            unsigned long long totTime4;
            queue<Process> q4;
            switch(sortAl){
                case 1:{
                    for(int i = 0; i<50; i++){
                        if(essor1.memory>=pro[i].memory){
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
                        }else if(essor3.memory>=pro[i].memory){
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
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            }
            break;
            }
        case 3:
            {Processor essor1;
            essor1.memory = 2;
            essor1.speed = 2000000000;
            unsigned long long totTime1;
            unsigned long long avg1 = totTime1/essor1.speed;
            queue<Process> q1;
            Processor essor2;
            essor2.memory = 2;
            essor2.speed = 2000000000;
            unsigned long long totTime2;
            unsigned long long avg2 = totTime2/essor2.speed;
            queue<Process> q2;
            Processor essor3;
            essor3.memory = 4;
            essor3.speed = 3000000000;
            unsigned long long totTime3;
            unsigned long long avg3 = totTime3/essor3.speed;
            queue<Process> q3;
            Processor essor4;
            essor4.memory = 8;
            essor4.speed = 4000000000; //3000000000 cycle/second
            unsigned long long totTime4;
            unsigned long long avg4 = totTime4/essor4.speed;
            queue<Process> q4;
            switch(sortAl){
                case 1:{
                    for(int i = 0; i<50; i++){
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
                case 2:
                    break;
                case 3:
                    break;
                case 4:
                    break;
                case 5:
                    break;
                }
                break;
                }
        case 4:
            {Processor essor1;
            essor1.memory = 8;
            essor1.speed = 3000000000;
            unsigned long long totTime1;
            queue<Process> q1;
            Processor essor2;
            essor2.memory = 8;
            essor2.speed = 3000000000;
            unsigned long long totTime2;
            queue<Process> q2;
            Processor essor3;
            essor3.memory = 8;
            essor3.speed = 3000000000;
            unsigned long long totTime3;
            queue<Process> q3;
            Processor essor4;
            essor4.memory = 8;
            essor4.speed = 3000000000; //3000000000 cycle/second
            unsigned long long totTime4;
            queue<Process> q4;
            switch(sortAl){
                case 1:{
                    priority_queue<unsigned long long> pQ;
                    for(int n = 0; n<50; n++){
                        pQ.push(pro[n].arrivalTime);
                    }
                    while(!pQ.empty()){
                        unsigned long long temp = pQ.top();
                        pQ.pop();
                        int i = 0;
                        while (pro[i].arrivalTime != temp){
                            i++;
                        }
                        if(totTime1<=totTime2 && totTime1<=totTime3 && totTime1<=totTime4){
                            q1.push(pro[i]);
                            cout<<"Process number:" << pro[i].ID<<endl<<"Service time:"<<pro[i].serviceTime<<endl<<"Arrival time:"<<pro[i].arrivalTime<<endl;
                            cout<<"Memory requirements:"<< pro[i].memory<<endl<<"Wait time:"<<totTime1<<endl<<"Total time in system:"<<(totTime1 - pro[i].arrivalTime)+pro[i].serviceTime<<endl;
                            cout<<"In processor 1"<<endl;
                            totTime1 = pro[i].serviceTime;
                        }else if(totTime2 <=totTime3 && totTime2 <=totTime1 && totTime2 <=totTime4){
                            q2.push(pro[i]);
                            cout<<"Process number:" << pro[i].ID<<endl<<"Service time:"<<pro[i].serviceTime<<endl<<"Arrival time:"<<pro[i].arrivalTime<<endl;
                            cout<<"Memory requirements:"<< pro[i].memory<<endl<<"Wait time:"<<totTime2<<endl<<"Total time in system:"<<(totTime2 - pro[i].arrivalTime)+pro[i].serviceTime<<endl;
                            cout<<"In processor 2"<<endl;
                            totTime2 += pro[i].serviceTime;
                        }else if(totTime3 <= totTime4 && totTime3 <= totTime2 && totTime3 <= totTime1){
                            q3.push(pro[i]);
                            cout<<"Process number:" << pro[i].ID<<endl<<"Service time:"<<pro[i].serviceTime<<endl<<"Arrival time:"<<pro[i].arrivalTime<<endl;
                            cout<<"Memory requirements:"<< pro[i].memory<<endl<<"Wait time:"<<totTime3<<endl<<"Total time in system:"<<(totTime3-pro[i].arrivalTime)+pro[i].serviceTime<<endl;
                            cout<<"In processor 3"<<endl;
                            totTime3 += pro[i].serviceTime;
                        }else if(totTime4 <= totTime1 && totTime4 <= totTime2 && totTime4 <= totTime3){
                            q4.push(pro[i]);
                            cout<<"Process number:" << pro[i].ID<<endl<<"Service time:"<<pro[i].serviceTime<<endl<<"Arrival time:"<<pro[i].arrivalTime<<endl;
                            cout<<"Memory requirements:"<< pro[i].memory<<endl<<"Wait time:"<<totTime4<<endl<<"Total time in system:"<<(totTime4-pro[i].arrivalTime)+pro[i].serviceTime<<endl;
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
                case 2:
                    break;
                case 3:
                    break;
                case 4:
                    break;
                case 5:
                    break;
                }
                break;
                }
        default:
            break;
    }
}
