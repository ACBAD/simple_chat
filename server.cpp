#include <iostream>
#include <rapidjson/document.h>
#include <httplib.h>
#ifdef _WIN32
#include <Windows.h>
#endif
using namespace std;
int main(){
  cout<<"Start"<<endl;
  httplib::Server svr;
  svr.Get("/hi", [](const httplib::Request &, httplib::Response &res){
    cout<<"Request!"<<endl;
    res.set_content("Hello World!", "text/plain");
  });
  cout<<"Start Listening ..."<<endl;
  svr.listen("0.0.0.0", 80);
  return 0;
}