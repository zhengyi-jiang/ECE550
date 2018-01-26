#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <pwd.h>
#include <grp.h>
#include <unistd.h>
//This function is for Step 4
char * time2str(const time_t * when, long ns) {
  char * ans = malloc(128 * sizeof(*ans));
  char temp1[64];
  char temp2[32];
  const struct tm * t= localtime(when);
  strftime(temp1,512,"%Y-%m-%d %H:%M:%S",t);  
  strftime(temp2,32,"%z",t);
  snprintf(ans,128,"%s.%09ld %s", temp1, ns, temp2);
  return ans;
}


void step_one(const struct stat *buf){
  if(buf == NULL){
    perror("no\n");
    exit(EXIT_FAILURE);
  }
  const char *file_type = NULL;
  switch (buf->st_mode & S_IFMT) {
  case S_IFBLK:  file_type = "block special file";
    break;
  case S_IFCHR:  file_type = "character special file";
    break;
  case S_IFDIR:  file_type = "directory";
    break;
  case S_IFIFO:  file_type = "fifo";
    break;
  case S_IFLNK:  file_type = "symbolic link";
    break;
  case S_IFREG:  file_type = "regular file";
    break;
  case S_IFSOCK: file_type = "socket";
    break;
  default:       file_type = "unknown?";
    break;
  }
  printf("  Size: %-10lu\tBlocks: %-10lu IO Block: %-6lu %s\n",buf->st_size,buf->st_blocks,buf->st_blksize,file_type);

  if((S_ISCHR(buf->st_mode) || S_ISBLK(buf->st_mode))){
      
    printf("Device: %lxh/%lud\tInode: %-10lu  Links: %-5lu Device type: %x,%x\n",buf->st_dev,buf->st_dev,buf->st_ino,buf->st_nlink,major(buf->st_rdev),minor(buf->st_rdev));
  }
  else{
    printf("Device: %lxh/%lud\tInode: %-10lu  Links: %lu\n",buf->st_dev,buf->st_dev,buf->st_ino,buf->st_nlink);      
  }
}

void step_two(const struct stat *buf){
  if(buf == NULL){
    perror("no\n");
    exit(EXIT_FAILURE);
  }
  
  char *ac = malloc(11*sizeof(*ac));
  switch((buf->st_mode) & S_IFMT){
  case S_IFBLK:    ac[0] = 'b';
    break;
  case S_IFCHR:    ac[0] = 'c';
    break;
  case S_IFDIR:    ac[0] = 'd';
    break;
  case S_IFIFO:    ac[0] = 'p';
    break;
  case S_IFLNK:    ac[0] = 'l';
    break;
  case S_IFREG:    ac[0] = '-';
    break;
  case S_IFSOCK:   ac[0] = 's';
    break;
  default:         ac[0] = ' ';
    break;
  }
  
  if((buf->st_mode & S_IRUSR)==0){
    ac[1] = '-';
  }
  else{
    ac[1] = 'r';
  }
  if((buf->st_mode & S_IWUSR)==0){
    ac[2] = '-';
  }
  else{
    ac[2] = 'w';
  }
  if((buf->st_mode & S_IXUSR)==0){
    ac[3] = '-';
  }
  else{
    ac[3] = 'x';
  }
  //first 3
  if((buf->st_mode & S_IRGRP)==0){
    ac[4] = '-';
  }
  else{
    ac[4] = 'r';
  }
  if((buf->st_mode & S_IWGRP)==0){
    ac[5] = '-';
  }
  else{
    ac[5] = 'w';
  }
  if((buf->st_mode & S_IXGRP)==0){
    ac[6] = '-';
  }
  else{
    ac[6] = 'x';
  }
  //second 3
  if((buf->st_mode & S_IROTH)==0){
    ac[7] = '-';
  }
  else{
    ac[7] = 'r';
  }
  if((buf->st_mode & S_IWOTH)==0){
    ac[8] = '-';
  }
  else{
    ac[8] = 'w';
  }
  if((buf->st_mode & S_IXOTH)==0){
    ac[9] = '-';
  }
  else{
    ac[9] = 'x';
  }
  //third 3
  ac[10] = '\0';
  printf("Access: (%04o/%s)",(buf->st_mode) & ~S_IFMT,ac);
  free(ac);
}

void step_three(const struct stat *buf){
  if(buf == NULL){
    perror("no\n");
    exit(EXIT_FAILURE);
  }
  
  struct passwd *pa = getpwuid(buf->st_uid);
  struct group *gp = getgrgid(buf->st_gid);
  printf("  Uid: (%5d/%8s)   Gid: (%5d/%8s)\n",buf->st_uid,pa->pw_name,buf->st_gid,gp->gr_name);
}

  
int main(int argc, char **argv){
  if(argc < 2){
    fprintf(stderr,"input should be a pathname\n");
    exit(EXIT_FAILURE);
  }
  for(int i = 1; i < argc; i++){
    if(argv[i] == NULL){
      perror("no\n");
      exit(EXIT_FAILURE);
    }
    struct stat info;
    if(lstat(argv[i],&info) == -1){
      perror("error loading name");
    }
    else{
      if(S_ISLNK(info.st_mode)){
	char linktarget[256];
	ssize_t len = readlink(argv[i], linktarget, 256);
	if (len == -1) {
	  perror("readlink");
	  exit(EXIT_FAILURE);
	}
	if (len > 255) {
	  fprintf(stderr, "symlink increased in size ");
	  exit(EXIT_FAILURE);
	}
	linktarget[len] = '\0';
	printf("  File: '%s' -> '%s'\n",argv[i],linktarget);
      }
      else{
	printf("  File: '%s'\n",argv[i]);
      }
      step_one(&info);
      step_two(&info);
      step_three(&info);
      
      char *atimestr = time2str(&info.st_atime,info.st_atim.tv_nsec);
      printf("Access: %s\n",atimestr);
      free(atimestr);
      
      char *mtimestr = time2str(&info.st_mtime,info.st_mtim.tv_nsec);
      printf("Modify: %s\n",mtimestr);
      free(mtimestr);
      
      char *ctimestr = time2str(&info.st_ctime,info.st_ctim.tv_nsec);
      printf("Change: %s\n",ctimestr);
      free(ctimestr);
      printf(" Birth: -\n");
    }
  }
  return 0;
}
