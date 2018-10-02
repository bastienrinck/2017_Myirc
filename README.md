# PSU_myirc_2017


## Usage

Shell:
```
$> ./server 4242    # IRC server listening on port 4242
$> ./client         # IRC client
```
## Client - command list:

**Connect to a server**
```
> /server <ip>:<port>
```
**Set a nickname**
```
> /nick <new nickname>
```
**Channel list with users**
```
> /list
```
**Join an irc channel**
```
> /join <#channel>
```
**Leave an irc channel or the current one**
```
> /part [#channel]
```
**List the connected users**
```
> /users
```
**List users in a channel or the current one**
```
> /names [#channel]
```
**Send a message to a channel or a user**
```
> /msg <#channel / nickname> <msg>
```

## Credits

* Bastien Rinck
* Jonathan Frickert
