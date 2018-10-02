# PSU_myirc_2017

**Subject [here](https://github.com/thibautcornolti/MyIRC/blob/master/Subject.pdf)**

## Usage

Shell:
```
$> ./server 4242    # IRC server listening on port 4242
$> ./client         # IRC client
```

Client - command list:
```
> /server <ip>:<port>                     # connect to a server
> /nick <new nickname>                    # set a nickname
> /list                                   # channel list with users
> /join <#channel>                        # join an irc channel
> /part [#channel]                        # leave an irc channel or the current one
> /users                                  # list the connected users
> /names [#channel]                       # list users in a channel or the current one
> /msg <#channel / nickname> <msg>        # send a message to a channel or a user
```

## Credits

* Bastien Rinck
* Jonathan Frickert
