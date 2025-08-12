# Notification Daemon

A lightweight Linux notification daemon using the `org.freedesktop.Notifications` D-Bus interface.

It receives desktop notifications and writes their details as JSON to a FIFO pipe (`/tmp/notif-pipe`), allowing other programs to read and react.

---

## Features

- receives notifications from applications using D-Bus
- outputs notification data to `/tmp/notif-pipe` as JSON
- uses auto-generated D-Bus interface code with `gdbus-codegen`
- written in C++ and C with GLib/GIO libraries

---

## Build & Run

```bash
git clone https://github.com/milesdredd/notification-daemon.git
cd noti
make
./notify
```

---

## Status

This is an early-stage project focused on basic notification reception and forwarding.


## Why Use This?
- simple and easy to understand codebase
- good learning project for Linux D-Bus and IPC
- lightweight and customizable notification backend


