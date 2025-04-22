#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <cstring>  


using namespace std;

int main(){
    int fd[2];
    pid_t pid;
    if(pipe(fd)==-1){
        cout<<"error"<<endl;
    }

    int choice;
    cout<<"1.parent will send message to child"<<endl<<"2.child will send message to parent"<<endl;
    cin>>choice;

    pid = fork();

    if(pid<0){
        cout<<"error"<<endl;
        return 0;
    }
    

    if(pid>0){
        if(choice==1){
            close(fd[0]);
            string message;
            cin.ignore();
            cout<<"message form parent:"<<endl;
            getline(cin,message);
            write(fd[1],message.c_str(),message.length()+1);
            close(fd[1]);
        }
        else{
            close(fd[1]);
            char buffer[100];
            int bytesread = read(fd[0],buffer,sizeof(buffer)-1);
            if(bytesread>0){
                buffer[bytesread]='\0';
                cout<<"message recived by child from parent:"<<endl;
                cout<<buffer<<endl;
            }
            close(fd[0]);
        }
        wait(NULL);
    }
    else{
        if(choice==2){
            close(fd[0]);
            string message;
            cout<<"message from child:"<<endl;
            cin.ignore();
            getline(cin,message);
            write(fd[1],message.c_str(),message.length()+1);
            close(fd[1]);
        }
        else{
            close(fd[1]);
            char buffer[100];
            int bytesread = read(fd[0],buffer,sizeof(buffer)-1);
            if(bytesread>0){
                buffer[bytesread]='\0';
                cout<<"message to parent recived from child:"<<endl;
                cout<<buffer<<endl;
            }
            close(fd[0]);
        }
    }
    return 0;
}
