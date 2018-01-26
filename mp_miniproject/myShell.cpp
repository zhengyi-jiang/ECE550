#include "myShell.h"
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>


Shell::Shell():argv(NULL), argc(0), envp(NULL), env(NULL), vars(), envs(), process_num(0), process_argv(),process_argc(){}
Shell::Shell(const Shell &rhs):  argv(NULL), argc(rhs.argc), envp(NULL), env(NULL), vars(rhs.vars), envs(rhs.envs), process_num(rhs.process_num),process_argv(rhs.process_argv),process_argc(rhs.process_argc){
  argv = (char**)malloc((rhs.argc+1)*sizeof(*argv));
  for(int i = 0; i < rhs.argc; i++ ){
    argv[i] = NULL;
    strcopy<char **const>(&(argv[i]),&(rhs.argv[i]));
  }
  argv[argc] = NULL;
  strcopy<char *const*>(&envp,&(rhs.envp));
  if(rhs.env != NULL){
    int i = 0;
    while(rhs.env[i] != NULL){
      env = (char **)realloc(env,(i+1)*sizeof(rhs.env));
      env[i] = NULL;
      strcopy<char **const>(&(env[i]),&(rhs.env[i]));
      i++;
    }
    env = (char **)realloc(env,(i+1)*sizeof(rhs.env));
    env[i] = NULL;
  }
}//copy constructor
Shell &Shell::operator= (const Shell &rhs)
{
  if (this != &rhs){
    Shell temp(rhs);
    std::swap(temp.argv,argv);
    std::swap(temp.argc,argc);
    std::swap(temp.envp,envp);
    std::swap(temp.env,env);
    std::swap(temp.vars,vars);
    std::swap(temp.envs,envs);
    std::swap(temp.process_argv,process_argv);
    std::swap(temp.process_argc,process_argc);
    process_num = rhs.process_num;
  }
  return *this;
}//operator
Shell::~Shell() {
  end();
  free(envp);
  envp = NULL;
}//destructor

void add_argv_helper(char *&arg,int &argi, char **&argv, int &argc){
  arg = (char*)realloc(arg,(argi+1)*sizeof(char));
  arg[argi] = '\0';
  argv = (char**)realloc(argv,(argc+2)*sizeof(char*));
  argv[argc] = arg;
  argv[argc+1] = NULL;
  arg = NULL;
  argi = 0;
  argc++;
}//this function is to add a new argument to the argv and add a NULL to the last of argv

int Shell::parse(){
  while(argc == 0){//check if the argv is NULL, if it is, it means no argument are passed in and need to be done again
    char *cdn = get_current_dir_name();
    if(cdn == NULL){
      perror("get current dir");
      exit(EXIT_FAILURE);
    }
    std::cout<<"myShell:"<<cdn<<"$ ";//get current directory
    free(cdn);
    if(stdin == NULL){
      std::cout<<"stdin can't be NULL!\n";
      exit(EXIT_FAILURE);
    }
    int c = 0;
    char *arg = NULL;
    int argi = 0;
    while((c = fgetc(stdin)) != '\n'){//if "\n" is not detected keep reading from stdin	
      if(c == EOF){
	std::cout << "\n";
	return END;
      }//when it encounter EOF, return END to end.
      if(c != ' '){
	arg = (char*)realloc(arg,(argi+1)*sizeof(char));
	arg[argi] = (char)c;
	argi++;
      }//if the char is not a ' ', get the char
      else{
	if(argi != 0){
	  if(arg[argi-1] == '\\'){
	    arg[argi-1] = ' ';
	  }//check if the ' ' is followed by the '\'.if not, there are two posibilities(1.delimited by it. 2.ignore it.)
	  else if(argi != 0){//if argi == 0, it means argi is cleared by a former space, should be skip
	    add_argv_helper(arg,argi,argv,argc);//add the 
	    while(strchr(argv[argc-1], '$') != NULL){
	      if(checkvar_replaces() == BREAK){//after add each argv, check if there is variable need to be replace.
		while(fgetc(stdin) != '\n');//when invalid variable are detected before '\n', get rid of the useless remainning stdin and return.
		return BREAK;//if invalid, return BREAK
	      }
	    }
	    if(argc == 2){
	      if(strcmp("set",argv[0]) == 0){
		return SET;
	      }
	    }
	  }
	}
      }
    }//if "\n" shows, do the next instruction
    if(argi != 0){//if there is nothing before "\n"
      add_argv_helper(arg,argi,argv,argc);
      while(strchr(argv[argc-1], '$') != NULL){//after add last argv, check if there is variable need to be replace.
	if(checkvar_replaces() == BREAK){
	  return BREAK;//if invalid, return BREAK
	}
      }
    }
  }
  
  if(argc == 1 && strcmp("exit",argv[0]) == 0){
    return END;
  }//check if the single command is exit
  if(strcmp("export",argv[0]) == 0){//check if the command is export, and then do export
    if(argc != 2){
      std::cout << "format should be:\"export var\"\n";
      return BREAK;//export can only be followed by one argument
    }
    return EXPORT;
  }
  if(strcmp("set",argv[0]) == 0){//check if the command is set
    std::cout << "format should be:\"set var value\"\n";
    return BREAK;//same as export
  }
  if((strcmp("cd",argv[0]) == 0) ){//check if it is cd command
    return CD;
  }//when enter exit, then exit;
  return EXE;
}

void Shell::cd(){
  if(argc !=2){
    std::cout << "cd: to change directory\n";//if the cd command format is not valid 
    return;
    }
  int i = chdir(argv[1]);//change current dir
  if(i == 0){
    return;
  }
  else{
    perror("cd");//error detection
    return;
  }
}

void Shell::getpath(){
  std::string first("PATH");
  std::map<std::string,std::string>::iterator it = envs.find(first);//find PATH in env map
  if(it == envs.end()){exit(EXIT_FAILURE);}//if not find return error
  const char *path = it->second.c_str();
  strcopy<char const**>(&(envp),&(path));//copy PATH to envp(environment path) and use it to find a command
}

void Shell::setvar(char **environ){
  int i = 0;
  while(environ[i] != NULL){
    char *eq = strchr(environ[i] , '=');
    char *value = eq + 1;
    environ[i][eq - environ[i]] = '\0';
    std::string first(environ[i]);
    std::string second(value);
    vars.insert(std::pair<std::string,std::string>(first,second));
    environ[i][eq - environ[i]] = '=';
    i++;//copy all environment variables to my var map
  }
  envs = vars;//copy my var map to env map.
}

void Shell::addenv(){
  std::string first(argv[1]);
  std::map<std::string,std::string>::iterator it = vars.find(first);//see if the var exist
  if (it != vars.end()){
    std::string second(it->second);//see if env var exist
    std::map<std::string,std::string>::iterator it = envs.find(first);
    if (it != envs.end()){
      it->second = second;//find it, replace environment var
    }
    else{
      envs.insert(std::pair<std::string,std::string>(first,second));//or add the env car
    }
    std::cout <<"export:$"<<first << "=" << envs.at(first) << "as environment variable\n";
    return;
  }
  else{//or nothing found
    std::cout<<"variable "<< argv[1] << " not found!\n";
    return;
  }
}

int Shell::addvar(){
  int c = 0;
  char *arg = NULL;
  int argi = 0;
  while((c = fgetc(stdin)) != '\n'){
    if(c == EOF){
      return END;
    }
    arg = (char*)realloc(arg,(argi+1)*sizeof(char));
    arg[argi] = (char)c;
    argi++;//turn value to arg
  }
  if(argi == 0){
    std::cout << "format:\"set var value\"\n";
    return 0;//see if it is NULL
  }
  arg = (char*)realloc(arg,(argi+1)*sizeof(char));
  arg[argi] = '\0';//end arg
  int check_letter = 0;
  int letter = 0;
  while((letter=argv[1][check_letter]) != '\0'){
    if(letter < 48 || (letter > 57 && letter < 65) || (letter > 90 && letter != 95 && letter < 97 )|| letter > 122){
      std::cout << "variable can only contains letters, underscores or numbers.\n";
      free(arg);
      return 0;//check if the variables is legal
    }
    check_letter++;
  }//check if the var contains illegal letter
  std::string first(argv[1]);
  std::string second(arg);
  std::map<std::string,std::string>::iterator var_it = vars.find(first);//see if the car exist to replace or add
  if (var_it != vars.end()){
    var_it->second = second;//replace
  }
  else{
    vars.insert(std::pair<std::string,std::string>(first,second));//add
  }
  std::map<std::string,std::string>::iterator env_it = envs.find(first);//see if the var is in env to replace
  if (env_it != envs.end()){
    env_it->second = second;
  }
  free(arg);
  std::cout << "set:$"<<first << "=" << vars.at(first) << "\n";
  return 0;
}
  
void Shell::getenv(){//initiate env.
  int i = 0;
  for(std::map<std::string,std::string>::iterator it = envs.begin(); it !=envs.end(); ++it){
    env = (char**)realloc(env,(i+1)*sizeof(*env));
    std::string combine = it->first + "=" + it->second;//combine var value to var=value
    const char* combine_c = combine.c_str();
    env[i] = NULL;
    strcopy<const char **>(&(env[i]),&(combine_c));
    i++;
  }
  env = (char**)realloc(env,(i+1)*sizeof(*env));
  env[i] = NULL;//after add all, put a NULL in the back
  return;
}  

int Shell::checkvar_replaces(){   
  char *pch = strtok(argv[argc-1],"$");//argument is devided by $
  std::string temp;
  int i = 0;
  if(argv[argc-1][0] == '$'){
    i = 1;//if it start with $, do replaces after
  }
  else{
    temp += pch;//everything before $ is kept
  }
  while (pch != NULL){
    if(i != 0){      
      std::string var(pch);
      std::map<std::string,std::string>::iterator it = vars.find(var);
      if (it != vars.end()){
	temp += it->second;//do change
      }
      else{
	std::cout << "variable:" << var << " not found\n";
	return BREAK;//if not found, inform user and return
      }
    }
    pch = strtok (NULL, "$");
    i++; // keep searching variable  
  }
  const char *arg = temp.c_str();
  strcopy<const char **>(&(argv[argc-1]),&(arg));//copy the new argument to the old place
  if(strlen(argv[argc-1]) == 0){
    std::cout << "\"$\" must be followed by argument\n";  
    return BREAK;//if it contians nothing return
  }
  return 0;
}

char *cat_path_helper(char *arg, char *pch){
  int arglen = strlen(arg);
  int pchlen = strlen(pch);
  char *ans = (char*)malloc((arglen+pchlen+2)*sizeof(*arg));
  for(int i = 0; i < pchlen ; i++){
    ans[i] = pch[i];
  }
  ans[pchlen] = '/';
  for(int j = 0; j< arglen ; j++){
    ans[j+pchlen+1] = arg[j];
  }
  ans[arglen + pchlen+1] = '\0';
  return ans;
}//cat path with the command and add "/" in between

int check_access_helper(char *path){
  if(access(path,X_OK) != 0){
    return -1;
  }
  struct stat info;
  if(lstat(path,&info) == -1){
    return -1;
  }
  if((info.st_mode & S_IFMT) == S_IFDIR){
    return -1;
  }
  return 0;
}//check if the command can be execute or not if not return -1
    
char *Shell::check_accessable(char *arg, const char *envp){
  char* path = NULL;
  strcopy<const char **>(&(path),&(envp));
  if(strchr(arg,'/') == NULL){//check if "\" is contained.
    if (path!=NULL){
      char *pch = NULL;
      if((pch = strtok(path,":")) != NULL){//path is devided by ":"
	while (pch != NULL){
	  char *ans = cat_path_helper(arg,pch); 
	  if(check_access_helper(ans) == 0 ){//check each path add command
	    free(arg);
	    free(path);
	    return ans;
	  }
	  else{
	    pch = strtok (NULL, ":");//keep searching :
	    free(ans);
	  }
	  
	}
      }
      std::cout <<"Command "<< arg << " not found\n";//if nothing found to be execute
      free(arg);
      free(path);
      return NULL;
    }
    else{
      std::cout << "PATH is NULL\n";
      free(arg);
      free(path);
      return NULL;
    }
  }
  else{//if no : is contained
    if(check_access_helper(arg) != 0){
      std::cout <<"Command "<< arg << " not found\n";
      free(arg);
      free(path);
      return NULL;
    }
    else{
      free(path);
      return arg;
    }
  }
}

void Shell::resize_arg(int i,int z){
  free(process_argv[z][i]);
  free(process_argv[z][i+1]);
  process_argv[z][i] = NULL;
  process_argv[z][i+1] = NULL;
  while( i < process_argc[z]-2){
    strcopy<char **>(&(process_argv[z][i]),&(process_argv[z][i+2]));
    strcopy<char **>(&(process_argv[z][i+1]),&(process_argv[z][i+3]));
    i = i+2;
  }
  free(process_argv[z][process_argc[z]-1]);
  free(process_argv[z][process_argc[z]-2]);
  process_argv[z][process_argc[z]-1] = NULL;
  process_argv[z][process_argc[z]-2] = NULL;
  process_argc[z]= process_argc[z]-2;
}//remove all the redireciton in process_argv and resize if the argv is {cat -n < input | a | b | c > output NULL} it will first become { cat -n < input NULL a NULL b NULL c > output NULL} and then  become { cat -n NULL a NULL b NULL c NULL NULL NULL NULL NULL} so in end it's ok to free

int redirection_sytaxcheck_helper(char **path, char **des){
  if(*path != NULL){
    if(**path != '\0'){
      if(**path == '<' || **path == '>' || ((**path == '2') && ((*path)[1] == '>'))){
	std::cout << "redireciton syntax error: should be followed by filename\n";
	return -1;
      }
      strcopy<char **>(des,path);   //std::cout << *des << '\n';
      return 0;
    }
  }
  std::cout << "redireciton syntax error: should be followed by filename\n";
  return -1;//check redirection sytax is valid or not , if is place filename in in out or err
}  

int Shell::redirection(char **in,char **out, char **err,int z){
  for(int i = 1; i < process_argc[z]; i++){
    if(strcmp(process_argv[z][i],"<") == 0){
      if(z != 0){
	std::cout << "only the first program can take an input file for redireciton\n";
	return -1;
      }
      if(redirection_sytaxcheck_helper(&((process_argv[z])[i+1]),in) == -1){	
	free(*in);
	return -1;
      }
      if(access(*in,R_OK) != 0){//see if the in file can be read or not
	std::cout <<"Can't read \""<< *in << "\" \n";
	free(*in);
	return -1;
      }
      resize_arg(i,z);
      i--;
    }
    else if(strcmp(process_argv[z][i],">") == 0){
      if(z != process_num -1){
	std::cout << "only the last program can take an output file for redireciton\n";
	return -1;
      }
      if(redirection_sytaxcheck_helper(&((process_argv[z])[i+1]),out) == -1){
	free(*out);
	return -1;
      }
      resize_arg(i,z);
      i--;
    }
    else if(strcmp(process_argv[z][i],"2>") == 0){
      if(redirection_sytaxcheck_helper(&(process_argv[z][i+1]),err) == -1){
	free(*out);
	return -1;
      }
      resize_arg(i,z);
      i--;
    }
  }
  return 0;
}//do redirection

int exe_redirection_helper(char *&path, int &fd, int status){
  if(fd == -1){
    std::cout << "Can't open redirection file.\n";
    return -1;
  }
  dup2(fd, status);
  close(fd);
  return 0;
}//check if the redirection can be open or not

int Shell::exe(int z){
  char *in = NULL;
  char *out = NULL;
  char *err = NULL;
  if(redirection(&in,&out,&err,z) == -1){//put redirection file path to NULL, and pass it to redirection() to initiate, if something is illegal, return -1 and repeat get stdin
    return -2;
  }
  pid_t cpid,wpid;
  int status;
  int pipefile[2];
  if(z != process_num -1){//if more than one program, do the pipe()
    if(pipe(pipefile) == -1){
      perror("pipe syscall fail");
      exit(EXIT_FAILURE);
    }//fail detection
  }
  cpid = fork();
  if (cpid == -1) {
    perror("fork");
    exit(EXIT_FAILURE);
  }
   if (cpid == 0) {
     if(z != process_num -1){
       close(pipefile[0]);
       dup2(pipefile[1],1);
     }//if it is not the last program, connect the pipe
     if(in != NULL){
      int fd = open(in, O_RDONLY);
      if(exe_redirection_helper(in,fd,0) == -1){
	free(in);free(out);free(err);
    	return -1;
      }
    }
    if(out != NULL){
      int fd = open(out, O_WRONLY | O_CREAT| O_TRUNC , 0666);
     if(exe_redirection_helper(out,fd,1) == -1){
       free(in);free(out);free(err);
	return -1;
      }
    }
    if(err != NULL){
      int fd = open(err, O_WRONLY | O_CREAT |O_TRUNC , 0666);
      if(exe_redirection_helper(err,fd,2) == -1){
	free(in);free(out);free(err);
	return -1;
      }
    }//do and check redirection
    free(in);free(out);free(err);
    execve(process_argv[z][0],process_argv[z],env);
    std::cout << argv[0] << " can't execute.\n";
    return -1;//in case execve fail.
  }
  else {
    wpid = waitpid(cpid, &status, WUNTRACED | WCONTINUED);
    if (wpid == -1) {
      perror("waitpid");
      exit(EXIT_FAILURE);
    }//err detection
    if(z != process_num - 1){
      close(pipefile[1]);
      dup2(pipefile[0],0);
    }    //    std::cout << "parents!!!!!!!!\n";
    if (WIFEXITED(status)) {
      printf("Program%d exited with status %d\n", z,WEXITSTATUS(status));
    }
    else if (WIFSIGNALED(status)) {
      printf("%dkilled by signal %d\n",z, WTERMSIG(status));
    }
    else if (WIFSTOPPED(status)) {
      printf("stopped by signal %d\n", WSTOPSIG(status));
    }
    else if (WIFCONTINUED(status)) {
      printf("continued\n");
    }//return status
  }
  free(in);free(out);free(err);
  return 0;
}

int Shell::pipe_process(){
  int j = 0;
  process_num=0;//process is initial
  for(int i = 0; i < argc ; i++){
    if(strcmp(argv[i],"|") == 0){
      if(j == i || i == argc -1){
	std::cout << "pipe error: format.\n";
	return -1;
      }//detect pipe sytax
      if((argv[j] = check_accessable(argv[j], envp)) == NULL){
	return -1;
      }      //std::cout << "process" <<process_num << ":\n";
      process_argv.push_back(argv+j);//add process_argv
      for(int z = j ; z < i; z++){	//	std::cout << argv[z] << "\n";
      }
      process_argc.push_back(i-j);//add argv
      process_num++;
      j = i + 1;
      free(argv[i]);
      argv[i] = NULL;//replace "|" with NULL ,and continue searching
    }
  }
  if((argv[j] = check_accessable(argv[j], envp)) == NULL){
    return -1;
  }
  process_argv.push_back(argv+j);
  process_argc.push_back(argc-j);  //std::cout << "process" <<process_num << ":\n";
  for(int i = j; i < argc; i++){    //std::cout << argv[i] << "\n";
  }
  process_num++;//add last one
  for(int i = 0; i < process_num; i++){
    int j = 0;    //std::cout <<i << ":\n";
    while( process_argv[i][j] != NULL){      //std::cout <<process_argv[i][j] << "\n";
      j++;
    }    //    std::cout << process_argc[i]  << "\n";
  }
  return 0;
}

void Shell::end(){  
  for(int i = 0; i < argc; i++){
    free(argv[i]);
  }
  free(argv);
  argc = 0;
  argv = NULL;
  int i = 0;
  if(env != NULL){
    while(env[i] != NULL){
      free(env[i]);
      i++;
    }
  }
  free(env);
  env =NULL;
  process_num = 0;
  process_argv.clear();
  process_argc.clear();
}//after each command line, clean myShell, and repeat the process

int main(){
  Shell a;
  a.setvar(environ);//set enironment variables to env and var map
  int status = 0;
  Shell b(a);//check rule of three
  while((status = a.parse() )!= END){//if eof and exit
    if(status == CD){//cd command
      a.cd();
    }
    else if(status == SET){//set command
      if(a.addvar() == END){
	break;//illegal sytan encounter
      }
    }
    else if(status == EXPORT){
      a.addenv();//export command
    }
    else if(status == EXE){//execute command
      b = a;
      a.getpath();
      a.getenv();
      b = a;
      if(a.pipe_process() == -1){
      }//check valid sytax
      else{
	if(a.get_process_num() != 1){
	  int status;
	  pid_t cpid = 1;
	  pid_t wpid = 0;
	  cpid = fork();
	  if (cpid == -1) {
	    perror("fork");
	    exit(EXIT_FAILURE);
	  }//if there is pipe do the fork at the begining
	  if (cpid == 0) {
	    for(int i = 0; i < a.get_process_num(); i++){
	      int status= 0;
	      if((status= a.exe(i)) == -1){
		return 0;
	      }
	      else if(status == -2){
		break;
	      }
	    }
	    return 0;
	  }
	  else{
	    wpid = waitpid(cpid, &status, WUNTRACED | WCONTINUED);
	    if (wpid == -1) {
	      perror("waitpid");
	      exit(EXIT_FAILURE);
	    }
	  }
	}
	else{//if not just exe
	  if((status= a.exe(0)) == -1){
	    return 0;//if error occur
	  }
	}
      }
    }
    else if(status == BREAK){
    }//if sytax is illegal, clean and repeat get the stdin
    a.end();
  }
  std::cout << "exit myshell\n";//exit
  return 0;
}
