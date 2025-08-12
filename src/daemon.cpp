#include "notification-service.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

static void print_me() {
    std::cout << "\t\t~A notification manager by Miles !" << std::endl;
}
static gboolean
handle_notify (NotificationServiceNotifications *interface,
               GDBusMethodInvocation *invocation,
               const gchar *app_name,
               guint replaces_id,
               const gchar *app_icon,
               const gchar *summary,
               const gchar *body,
               const gchar *const *actions,
               GVariant *hints,
               gint expire_timeout,
               gpointer user_data)
{
    g_print ("Notification received:\n");
    g_print ("  app_name: %s\n", app_name);
    g_print ("  replaces_id: %u\n", replaces_id);
    g_print ("  app_icon: %s\n", app_icon);
    g_print ("  summary: %s\n", summary);
    g_print ("  body: %s\n", body);
    g_print ("  expire_timeout: %d\n", expire_timeout);

    std::vector<std::pair<std::string, std::string>> action_list;
    for (int i = 0; actions[i] && actions[i + 1]; i += 2) {
        action_list.emplace_back(actions[i], actions[i + 1]);
    }

    //------------FIFO
    
std::ofstream pipe("/tmp/notif-pipe");
if (pipe.is_open()) {
    pipe << "{"
         << "\"app_name\": \"" << app_name << "\", "
         << "\"summary\": \"" << summary << "\", "
         << "\"body\": \"" << body << "\", "
         << "\"app_icon\": \"" << app_icon << "\", "
         << "\"actions\": [";

    for (size_t i = 0; i < action_list.size(); ++i) {
        pipe << "{"
             << "\"id\": \"" << action_list[i].first << "\", "
             << "\"label\": \"" << action_list[i].second << "\""
             << "}";
        if (i + 1 < action_list.size()) pipe << ", ";
    }

    pipe << "]"
         << "}" << std::endl;

    pipe.close();
}







//-------FIFO
    notification_service_notifications_complete_notify (interface, invocation, 1);

    return TRUE;
}

int main()
{
    print_me();
    GMainLoop *loop;
    NotificationServiceNotifications *interface;

    loop = g_main_loop_new (NULL, FALSE);

    interface = notification_service_notifications_skeleton_new ();
    g_signal_connect (interface, "handle-notify", G_CALLBACK (handle_notify), NULL);

    g_bus_own_name (G_BUS_TYPE_SESSION,
                    "org.freedesktop.Notifications",
                    G_BUS_NAME_OWNER_FLAGS_NONE,
                    NULL,
                    NULL,
                    NULL,
                    NULL,
                    NULL);

    g_dbus_interface_skeleton_export (G_DBUS_INTERFACE_SKELETON (interface),
                                      g_bus_get_sync (G_BUS_TYPE_SESSION, NULL, NULL),
                                      "/org/freedesktop/Notifications",
                                      NULL);

    g_main_loop_run (loop);

    g_object_unref (interface);
    g_main_loop_unref (loop);

    return 0;
}


