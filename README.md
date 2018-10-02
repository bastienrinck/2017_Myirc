# PSU_myirc_2017

**Subject [here](https://github.com/thibautcornolti/MyIRC/blob/master/Subject.pdf)**

## Usage

Shell:
```
$> ./server 4242    # IRC server listening on port 4242
$> ./client         # IRC client
```
```
Client - command list:
```
## connect to a server
```
> /server <ip>:<port>
```
## set a nickname
```
> /nick <new nickname>
```
## channel list with users
```
> /list
```
## join an irc channel
```
> /join <#channel>
```
## leave an irc channel or the current one
```
> /part [#channel]
```
## list the connected users
```
> /users
```
## list users in a channel or the current one
```
> /names [#channel]
```
## send a message to a channel or a user
```
> /msg <#channel / nickname> <msg>
```

## Credits

* Bastien Rinck
* Jonathan Frickert
