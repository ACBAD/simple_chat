#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/client.hpp>
#include <iostream>
#include <thread>

typedef websocketpp::client<websocketpp::config::asio_client> client;

class websocket_client {
public:
    websocket_client() {
        // 初始化 WebSocket 客户端
        ws_client.init_asio();
        // 设置回调
        ws_client.set_open_handler([this](websocketpp::connection_hdl hdl) {
            std::cout << "Connection opened" << std::endl;
            connection_hdl = hdl;
            // 在连接建立后发送一条消息
            ws_client.send(hdl, "Hello Server", websocketpp::frame::opcode::text);
        });
        ws_client.set_close_handler([](websocketpp::connection_hdl hdl) {
            std::cout << "Connection closed" << std::endl;
        });
        ws_client.set_message_handler([](websocketpp::connection_hdl hdl, client::message_ptr msg) {
            std::cout << "Received: " << msg->get_payload() << std::endl;
        });
    }
    void connect(const std::string& uri) {
        websocketpp::lib::error_code ec;
        client::connection_ptr con = ws_client.get_connection(uri, ec);
        if (ec) {
            std::cout << "Could not create connection: " << ec.message() << std::endl;
            return;
        }
        ws_client.connect(con);
        ws_client.run();
    }
private:
    client ws_client;
    websocketpp::connection_hdl connection_hdl;
};

using namespace std;
int main(){
  websocket_client client;
  client.connect("ws://localhost:9002");
  return 0;
}