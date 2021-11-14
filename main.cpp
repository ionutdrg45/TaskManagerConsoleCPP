#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <fstream>

using namespace std;

char task_title[32], task_creator[32], task_event[128];

char all_tasks[100][32];

char command[32];

int tasks_count = 1;

void command_list() {
    cout<<endl;
    cout<<"close - close the program"<<endl;
    cout<<"new_task - create a new task"<<endl;
    cout<<"view_tasks - view all tasks"<<endl;
    cout<<"view_task - view a specific task"<<endl;
    cout<<"help - show command list"<<endl;

    cout<<endl;
}

void load_tasks() {
    tasks_count = 1;
    ifstream ftasks("tasks.txt");
    char c;
    int nr_chr=0;
    while(ftasks>>c)
    {
        if(c == '~') {
            all_tasks[tasks_count][nr_chr-4]=NULL;
            nr_chr = 0;
            tasks_count++;
        }
        else {
            all_tasks[tasks_count][nr_chr]=c;
            nr_chr++;
        }
    }
    ftasks.close();
    tasks_count--;
}

void add_task(){
    int t=1;
    cout<<"You are creating a new task now, if you want to close this action type command 'close' or 'continue'"<<endl<<" to continue this action."<<endl;
    cin.get(command,32);
    cin.get();
    if(strcmp(command,"close")!=0)
    {
        system("cls");
        cout<<"Please enter the title of your task: ";
        cin.get(task_title, 32);
        cin.get();
        for(int i=1;i <= tasks_count; i++){
            if(strcmp(all_tasks[i],task_title)==0) {
                cout<<endl<<"This task name is already used, please pick another one: "<<endl;
                cin.get(task_title, 32);
                cin.get();
                i=1;
            }
        }
        cout<<"Describe the task event: "<<endl;
        cin.get(task_event, 128);
        cin.get();
        cout<<"What's your signature: ";
        cin.get(task_creator, 32);
        cin.get();
        strcat(task_title,".txt");
        ofstream g(task_title);
        g<<task_title<<" - "<<task_creator<<"~"<<endl<<"       "<<task_event;
        g.close();
        ofstream gtasks("tasks.txt");
        for(int i=1;i<=tasks_count;i++)
            gtasks<<all_tasks[i]<<".txt~"<<endl;
        gtasks<<task_title<<"~"<<endl;
        gtasks.close();
        load_tasks();
    }
}

void view_tasks() {
    for(int i=1;i<=tasks_count;i++)
        cout<<all_tasks[i]<<endl;
}

void view_task(char title_task[32]) {
    int t=0;
    for(int i=1;i <= tasks_count; i++){
        while(strcmp(all_tasks[i],title_task)==0) {
            t=1;
            break;
        }
        if(t==1) break;
    }
    if(t==1) {
        char l;
        system("cls");
        strcat(title_task, ".txt");
        ifstream ftask(title_task);
        while(ftask>>l)
            if(l == '~') cout<<endl;
            else cout<<l;
        ftask.close();
        cout<<endl;
    }
    else cout<<"Invalid task title"<<endl;
}

int main()
{
    load_tasks();
    cout<<"Command list:";
    command_list();

    cout<<"Command: ";
    cin.get(command,32);
    cin.get();

    if(strcmp(command, "close")!=0)
    {
        while(strcmp(command, "close")!=0) {
            if(strcmp(command, "new_task") == 0) {
                system("cls");
                add_task();
            }
            else if(strcmp(command, "view_tasks") == 0) {
                system("cls");
                view_tasks();
            }
            else if(strcmp(command, "help") == 0) {
                system("cls");
                command_list();
            }
            else if(strcmp(command, "view_task") == 0) {
                system("cls");
                cout<<"What task are you looking for?: ";
                cin.get(command,32);
                cin.get();
                view_task(command);
            }
            cout<<endl<<"Command: ";
            cin.get(command, 32);
            cin.get();
        }
    }
    else cout<<"Program ended.";
    return 0;
}
