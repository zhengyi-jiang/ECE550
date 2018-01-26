#ifndef __MCS_H__
#define __MCS_H__
#include <cstdlib>
#include <utility>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <map>
#include <vector>
#define END -1
#define SET 1
#define CD 2
#define EXPORT 3
#define BREAK 4
#define EXE 0

class Shell {
private:
  char **argv;//all the input from stdin
  int argc;//the input number
  char *envp;//the environment variable for myShell: PATH
  char **env;//all environment variables passing to execve
  std::map<std::string,std::string> vars;//all variables are in the map
  std::map<std::string,std::string> envs;//all environment variables 
  int process_num;//the number of process need to be execve(for pipe)
  std::vector<char**> process_argv;//argv for each process to be passed to execve
  std::vector<int> process_argc;//argc for each process
 public:
  Shell();
  Shell(const Shell &rhs);
  Shell &operator= (const Shell &rhs);
  //step 1
  int parse();//to get the current dir and then parse stdin, read it's filename and it's arguements, if the first argument is set, cd or export return the correspond macro to run the build-in instruction, if $ is encountered, check if the variable exist, if not return BREAK to end the current process and start again, if it's exit or EOF, then return -1 to end myShell;
  int exe(int i);//call redirection to check and do the redirection and do pipe() according to the current process number, then fork to run the process, in parent process, wait and get the child process's exit status;
  void end();//make myShell empty and clean before doing the next line of command.
   //step 2
  void getpath();//get PATH from my environment map.
  char *check_accessable(char *arg, const char *envp);//check if the program exist and accessable; if not, return NULL.
  //step 3
  void cd();//implement cd command.
  void setvar(char **envrion);//initiate environment variables to variables map and env map
  int addvar();//add to var map;(set command)
  void addenv();//add to env map;(export command)
  int checkvar_replaces();//check if the variable exist, replace $var with value
  void getenv();//convert envs map to environment variables and pass it to execve.
  //step 4
  int redirection(char **in,char **out, char **err, int i);//check if the redirection syntax is right and initial redirection path to in, out, err. 
  void resize_arg(int i,int z);//during redirection, delete the redireciton argument and resize the process argument 
  int get_process_num() {return process_num;}//get private member process_num
  int pipe_process();//devide argv by "|" and get each process_argv and process_argc and total process_num
  //
  ~Shell();
};

void add_argv_helper(char *&arg,int &argi, char **&argv, int &argc);//help parse() to add argument to argv.
char *cat_path_helper(char *arg, char *pch);//help check_accessable() to concatenate path and instruction.
int check_access_helper(char *path);//help check_accessable() to check if the instruction can be executed or not.
int redirection_sytaxcheck_helper(char **path, char **des);//help redirection() check if the sytax is legal or not.
int exe_redirection_helper(char *&path, int &fd, int status);//help exe() to check if the redirectioned file can be opened or not.
template<typename T>
void strcopy(char **des,T tar){
  if(*tar == NULL){
    free(*des);
    *des = NULL;
    return;
  }
  int i = 0;
  *des = (char*)realloc (*des,(strlen(*tar)+1)*sizeof(char));
  while((*tar)[i] != '\0'){
    (*des)[i] = (*tar)[i];
    i++;
  }
  (*des)[i] = '\0';
  return;
}//this function if to copy a char*

#endif
