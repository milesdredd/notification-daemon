#include <sdbus-c++/sdbus-c++.h>
#include <iostream>

int main() {
    auto connection = sdbus::createSessionBusConnection();
    sdbus::ObjectPath objectPath("/org/example/Minimal");
    auto object = sdbus::createObject(*connection, objectPath);

    const char* interfaceName = "org.example.Minimal";
    object->addVTable(
        sdbus::MethodVTableItem{
            sdbus::MethodName{"SayHello"},
            sdbus::Signature{"s"},
            std::vector<std::string>{"name"},
            sdbus::Signature{"s"},
            std::vector<std::string>{"greeting"},
            sdbus::method_callback(
            [](sdbus::MethodCall& call) {
                std::string name;
                call >> name;
                auto reply = call.createReply();
                reply << "Hello, " + name;
                reply.send();
            })
        },
        interfaceName
    );

    sdbus::ServiceName serviceName("org.example.Minimal");
    connection->requestName(serviceName);
    connection->enterEventLoop();

    return 0;
}
