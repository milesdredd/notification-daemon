import dbus


bus = dbus.SessionBus()
notify = bus.get_object("org.freedesktop.Notifications", "/org/freedesktop/Notifications")
iface = dbus.Interface(notify, "org.freedesktop.Notifications")

notif_id = iface.Notify(
    "TestApp",        # app_name
    0,                # replaces_id
    "",               # app_icon
    "Hello World",    # summary
    "This is a test notification with buttons",  # body
    ["reply", "Reply", "dismiss", "Dismiss"],    # actions (key1, label1, key2, label2)
    {},               # hints
    -1                # expire_timeout
)

