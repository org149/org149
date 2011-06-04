#include <iostream>
#include <fstream>
#include <string>
#include "large.pb.cc"
#include "small.pb.cc"

using namespace std;

void small_data(small::Data *data)
{
  unsigned int counter = 0;
  string str;
  while (true) {
    getline(cin, str);
    getline(cin, str);
    data->ParseFromString(str);
    counter++;
    if(counter % 10000 == 0){
      cerr << "READER: " << counter << " records passed" << endl;
    }
  }
}

void large_data(large::Data *data)
{
  unsigned int counter = 0;
  string str;
  while (true) {
    getline(cin, str);
    getline(cin, str);
    !data->ParseFromString(str);
    counter++;
    if(counter % 10000 == 0){
      cerr << "READER: " << counter << " records passed" << endl;
    }
  }
}

int main(int argc, char* argv[]) {

  GOOGLE_PROTOBUF_VERIFY_VERSION;

  if (argc < 2) {
    cerr << "Usage:  " << argv[0] << " PROTO_CLASS" << endl;
    return -1;
  }
 
  string bufclass = argv[1];

  if (bufclass == "small"){
    small::Data data;
    small_data(&data);
  } else {
    large::Data data;
    large_data(&data);
  } 

  google::protobuf::ShutdownProtobufLibrary();

  return 0;
}
