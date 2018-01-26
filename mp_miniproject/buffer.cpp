  /*argv[argc-1] = (char*)realloc(argv[argc-1],(strlen(arg)+1)*sizeof(argv[argc-1]));
  int j = 0;
  while(arg[j] != '\0'){
    argv[argc-1][j] = arg[j];
    j++;
  }
  argv[argc-1][j] = '\0';*/  //std::cout << argv[argc-1] <<"\n";


/*
    argv[i] = (char*)malloc((strlen(rhs.argv[i])+1)*sizeof(rhs.argv[i]));
    int j = 0;
    while(rhs.argv[i][j] != '\0'){
      argv[i][j] = rhs.argv[i][j];
      j++;
    }
    argv[i][j] = '\0';*/

/*
    envp = (char*)malloc((strlen(rhs.envp)+1)*sizeof(rhs.envp));
  int k = 0;
  while(rhs.envp[k] != '\0'){
    envp[k] = rhs.envp[k];
    k++;
  }
  envp[k] = '\0';*/


    /*  env[i] = (char*)malloc((strlen(rhs.env[i])+1)*sizeof(rhs.env[i]));
      int j = 0;
      while(rhs.env[i][j] != '\0'){
	env[i][j] = rhs.env[i][j];
	j++;
      }
      env[i][j] = '\0';*/

/*
    env[i] = (char*)malloc(strlen(combine_c+1)*sizeof(env[i]));
    int j = 0;
    while(combine_c[j] != '\0'){
      env[i][j] = combine_c[j];
      j++;
    }
    env[i][j] = '\0';*/

	    /*arg = (char*)realloc(arg,(argi+1)*sizeof(char));
	    arg[argi] = '\0';
	    argv = (char**)realloc(argv,(argc+2)*sizeof(char*));
	    argv[argc] = arg;
	    argv[argc+1] = NULL;
	    arg = NULL;
	    argi = 0;
	    argc++;*/
	    //to check if the command is set

















void Progarm::check_replaces(){
  char *pch;
  if(pch=strchr(argv[argc-1],'$')){
    check_replaces();
    if((pch-1) != NULL){
      if(*(pch-1) != '\\'){
	pch ++;
	std::cout << pch << "\n";
      }
    }
  }
  else{
    return;
  }
}
/*if((pch=strchr(pch,'$')) != NULL){
      if(check_replaces(pch+1) == BREAK){
	return BREAK;
      }
      if((pch-1) != NULL){
	if(*(pch-1) != '\\'){
	  pch ++;
	  std::string var(pch);
	  std::map<std::string,std::string>::iterator it = vars.find(var);
	  if (it != vars.end()){
	    const char *temp = it->second.c_str();
	    
	    
	  }
	  else{
	    std::cout << "var:$" << var << " not found\n";
	    return BREAK;
	  }
	}
	else{
	}
      }
      pch++;
      std::cout << pch << "\n";
    }
    else{
      return 0;
    }
  }
  else{
    return 0;
  }
  return 0;
}

*/

      /*std::string::iterator last = temp.end() -1;
      if(*last == '\\'){
	std::string var(pch);
	*last = '$';
	temp = temp + var;
	std::cout << temp;
      }*/
      
