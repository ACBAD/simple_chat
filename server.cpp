#include <rapidjson/document.h>
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>
#include <iostream>
#include <set>

typedef websocketpp::server<websocketpp::config::asio> server;
typedef server::message_ptr message_ptr;

class websocket_server {
public:
    websocket_server() {
        // 初始化 WebSocket 服务端
        ws_server.init_asio();

        // 设置回调
        ws_server.set_open_handler(bind(&websocket_server::on_open, this, std::placeholders::_1));
        ws_server.set_close_handler(bind(&websocket_server::on_close, this, std::placeholders::_1));
        ws_server.set_message_handler(bind(&websocket_server::on_message, this, std::placeholders::_1, std::placeholders::_2));
    }

    void run(uint16_t port) {
        // 监听指定端口
        ws_server.listen(port);
        ws_server.start_accept();
        ws_server.run();
    }

private:
    void on_open(websocketpp::connection_hdl hdl) {
        // 记录新连接
        connections.insert(hdl);
        std::cout << "Connection opened" << std::endl;
    }

    void on_close(websocketpp::connection_hdl hdl) {
        // 移除断开的连接
        connections.erase(hdl);
        std::cout << "Connection closed" << std::endl;
    }

    void on_message(websocketpp::connection_hdl hdl, message_ptr msg) {
        // 回显消息给客户端
        try {
            ws_server.send(hdl, msg->get_payload(), msg->get_opcode());
        } catch (const websocketpp::exception& e) {
            std::cout << "Message send failed: " << e.what() << std::endl;
        }
    }

    server ws_server;
    std::set<websocketpp::connection_hdl, std::owner_less<websocketpp::connection_hdl>> connections;
};

int main(){
  std::cout<<"Start"<<std::endl;
  websocket_server server;
  server.run(9002);
  return 0;
}