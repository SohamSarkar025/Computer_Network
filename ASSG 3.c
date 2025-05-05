//ASSG 3

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<unistd.h>

int main(){
    char s1[1024],s2[1024];
    int fd1,n,fd2[2],pid;
    fd1=open("a.txt",O_RDONLY,0764);
    n = read(fd1,s1,sizeof(s1));
    pipe(fd2);
    pid = fork();
    if(pid==-1){
        printf("Unsuccessful process creation\n");
        exit(1);
    }
    else if(pid==0){ //in child process
        close(fd2[1]);
        n=read(fd2[0],s2,sizeof(s2));
        s2[n]='\0';
        printf("\nReading from pipe\n");
        puts(s2);
    }
   else {
        // In parent process
        close(fd2[0]); // Close read end
        write(fd2[1], s1, n); // Write file content into pipe
    }
return 0;
}
