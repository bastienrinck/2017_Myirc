cmake_minimum_required(VERSION 3.9)
project(PSU_myirc_2017)

set(CMAKE_CXX_STANDARD 11)

include_directories(
        include
)

add_executable(PSU_myirc_2017
        include/server.h
        include/socket.h
        shared/tools.c
        shared/socket.c
        shared/client_socket.c
        shared/server_socket.c
        server/client.c
        server/server.c
        server/parser.c
        server/cmd_handler.c
        server/poll_handler.c
        server/commands/cmd_nick.c
        server/commands/cmd_list.c
        server/commands/cmd_join.c
        server/commands/cmd_part.c
        server/commands/cmd_user.c
        server/commands/cmd_pass.c
        server/commands/cmd_ping.c
        server/commands/cmd_quit.c
        server/commands/cmd_names.c
        server/commands/cmd_server.c
        server/commands/cmd_privmsg.c
        server/commands/cmd_unknown.c
        server/commands/cmd_msg_fsend.c
        server/commands/cmd_msg_faccept.c)
