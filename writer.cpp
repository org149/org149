#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include "large.pb.cc"
#include "small.pb.cc"
#include "function_map_small.h"
#include "function_map_large.h"

#define LARGE_FIELDS 50
#define SMALL_FIELDS 5

using namespace std;


string gen_random(const int len) {
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    string s("");
    for (int i = 0; i < len; ++i) {
        s += alphanum[rand() % (sizeof(alphanum) - 1)];
    }
    return s;
}

int main(int argc, char* argv[]) {

  GOOGLE_PROTOBUF_VERIFY_VERSION;

  if (argc < 2) {
    cerr << "Usage:  " << argv[0] << " STRING_LENGTH PROTO_CLASS" << endl;
    return -1;
  }

  int L = atoi(argv[1]);
  string l_buf = gen_random(L);
  string bufclass = argv[2];
  string name;
  string value; 
  string output;
  char buffer [10];


  if (bufclass == "small"){

    small::Data data;
    for(int i =0; i < SMALL_FIELDS; i++)
    { 
      sprintf(buffer, "%d", i);
      name = "set_int_field";
      name += buffer;
      value = "100";
      lookup_and_call_small(&data, name, value); 
    }
    for(int i =0; i < SMALL_FIELDS; i++)
    { 
      sprintf(buffer, "%d", i);
      name = "set_string_field";
      name += buffer;
      value = l_buf;
      lookup_and_call_small(&data, name, value); 
    }
    data.SerializeToString(&output);

  }else{

    large::Data data;
    for(int i =0; i < LARGE_FIELDS; i++)
    { 
      sprintf(buffer, "%d", i);
      name = "set_int_field";
      name += buffer;
      value = "100";
      lookup_and_call_large(&data, name, value);
    }
    for(int i =0; i < LARGE_FIELDS; i++)
    { 
      sprintf(buffer, "%d", i);
      name = "set_string_field";
      name += buffer;
      value = l_buf;
      lookup_and_call_large(&data, name, value);
    }
    data.SerializeToString(&output);

  }
  unsigned int counter = 0;
  while(true){
    //printf("%s",output.c_str());
    cout << output;
    counter++;
    if(counter % 10000 == 0){
      cerr << "WRITER: " << counter << " records passed" << endl;
    }
  }
  google::protobuf::ShutdownProtobufLibrary();

  return 0;
}
