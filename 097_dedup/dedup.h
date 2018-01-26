#ifndef _DEDUP_H
#define _DEDUP_H
#include <cstdlib>
#include <functional>
#include <list>
#include <utility>
#include <string>
#include <utility>
#include <iostream>
#include <sstream>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <vector>
#include <fstream>

using namespace std;


class d_hashmap {
private:
  hash<string> myhasher;
  vector<list<pair<size_t,string> > > *table;
public:
  d_hashmap():myhasher(),table(new vector<list<pair<size_t,string> > >(1000)) {}
  d_hashmap(const d_hashmap& a):myhasher(),table(new vector<list<pair<size_t,string> > >(*(a.table))) {}
  
  bool dele(const string& toC,const string& toRemove){
    ifstream ftoC;
    ftoC.open(toC, std::ifstream::in);
    ifstream ftoR;
    ftoR.open(toRemove, std::ifstream::in);
    stringstream sc;
    sc << ftoC.rdbuf();
    string ccontent = sc.str();
    stringstream rc;
    rc << ftoR.rdbuf();
    string scontent = rc.str();
    if(ccontent == scontent){
      /*
	#Removing /home/ece551/test/file1 (duplicate of
	/home/ece551/test/dir1/file2).
	
	rm /home/ece551/test/file1
      */
      cout << "#Removing " << toRemove <<" (duplicate of "<< toC << ").\n";
      cout << "rm " << toRemove <<"\n";
      return true;
    }
    else{
      return false;
    }
  }
      
    

  bool findadd(const string& path) {
    bool del = false;
    ifstream curr;
    curr.open(path);
    if(curr.is_open()){
      stringstream s;
      s << curr.rdbuf();
      string content = s.str();
      size_t key = myhasher(content);
      size_t h = key % 1000;
      for (list<pair<size_t,string> >::iterator it = (*table)[h].begin(); it != (*table)[h].end(); ++it){
	if((*it).first == key){
	  del = dele((*it).second , path);
	  if(del == true){
	    return true;
	  }
	}
      }
      (*table)[h].push_front(pair<size_t,string>(key, path));
      curr.close();
      return del;    
    }
    else{
      cout << "error loading file!:" << path << "\n";
      exit(EXIT_FAILURE);
    }
  }
  
  ~d_hashmap(){
    delete table;
  }
};

#endif
