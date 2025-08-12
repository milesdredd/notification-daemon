#include <sdbus-c++/sdbus-c++.h>
#include <iostream>
#include <cstdint>

using namespace std;

int main(){
    auto connection = sdbus::createSessionBusConnection();

    auto proxy = sdbus::createProxy(*connection,
        sdbus::ServiceName("org.freedesktop.Notifications"),
        sdbus::ObjectPath("/org/freedesktop/Notifications")
    );
        
    proxy->registerSignalHandler(
        sdbus::InterfaceName("org.freedesktop.Notifications"),
        sdbus::SignalName("NotificationClosed"),
        [](sdbus::Signal signal){
            uint32_t id, reason;
            signal >> id >> reason;
            cout << "Notification closed. ID: " << id << ", reason: " << reason << endl;
        }
    );

    // 🔧 Important!
//    proxy->finishRegistration();

    cout << "Listening for notifications..." << endl;
    connection->enterEventLoop();

    return 0;
}

