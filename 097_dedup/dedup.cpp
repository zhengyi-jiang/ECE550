#include "dedup.h"
#include <string.h>
 
void listfile(const char *path, vector<string> &files){
  DIR *dirptr=NULL;
  struct dirent *entry;
  if((dirptr = opendir(path))==NULL){
    printf("opendir failed!\n");
    exit(EXIT_FAILURE);
  }
  else{
    while((entry=readdir(dirptr))){
      if(strcmp(entry->d_name,".")==0 || strcmp(entry->d_name,"..")==0){
      }
      else{
	if(entry->d_type & DT_DIR){
	  //printf("pathname:%s/%s",path,entry->d_name);
	  stringstream childpath;
	  childpath << path << "/"<<entry->d_name;
	  listfile((childpath.str()).c_str(),files);
	}
	else{
	  stringstream filepath;
	  filepath << path << "/"<<entry->d_name;
	  struct stat info;
	  if(lstat((filepath.str()).c_str(),&info) == -1){
	    perror("error loading name");
	  }
	  else{
	    if(S_ISLNK(info.st_mode)){
	    }
	    else{
	      files.push_back(filepath.str());
	    }
	  }
	}
      }
    }
    closedir(dirptr);
    return;
  }
}

int main(int argc, char **argv){

  if(argc == 1){
    cout << "This is for dedup!\n";
    exit(EXIT_FAILURE);
  }
  
  else{
    
    cout << "#!/bin/bash\n";
    for(int i = 1; i < argc; i++){
      d_hashmap filehash;
      vector<string> allfiles;
      listfile(argv[i],allfiles);
      for (vector<string>::iterator it = allfiles.begin() ; it != allfiles.end(); ++it){
	filehash.findadd(*it);
	//cout << ' ' << *it << ' ';
      }
    }
   
    return EXIT_SUCCESS;
  }
}
