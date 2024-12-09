#include <iostream>
#include <rapidjson/document.h>
#include <httplib.h>
#ifdef WIN32
#include <Windows.h>
#endif
using namespace std;
int main(){
  httplib::Server svr;
  svr.Get("/hi", [](const httplib::Request &, httplib::Response &res){
    cout<<"Request!"<<endl;
    res.set_content("Hello World!", "text/plain");
  });
  svr.listen("0.0.0.0", 80);
  return 0;
}