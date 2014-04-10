boost-connection-manager
========================

A tool to help manage related boost connections.

In short in my projects I find that multiple signals are related to one area of connectivity.  I tend to connect/disconnect those signals in groups.  The two straight forward approaches are this.

```
Class 1:
  Signal1

Class 2:
  Function2
  Connection2

  Function3
  Connection3
```
####OPTION 1: I could use function identifiers to connec/disconnect 
```
Signal1.connect(Function2)
Signal1.connect(Function3)
```
and then to disconnect using
```
Signal1.disconnect(Function2)
Signal1.disconnect(Function3)
```
#####CONS: This doesn't work if I connect lambda functions and it doesn't explicitly disconnect my Functions when objects are destroyed.

####OPTION 2: I use a vector of connections
```
vector<Connection> mConns;
mConns.push_back( Signal1.connect(Function2) )
mConns.push_back( Signal1.connect(Function3) )
```

then in the disconnect/deconstructor
for(auto& conn : mConns) { conn.disconnect(); }

#####CONS:  Repetative, but this is more or less the structure I'll be using in my connection manager

###boost-connection-manager

Class that does something like this

```
BoostConnectionManager bcm;
bcm.conected() // bool tells us if we have connected signals
bcm.disconnect() // disconnects and releases all connections
bcm = Signal1.connect(Function2) // releases any existing connections and saves the new connection
bcm += Signal1.connect(Function3) // adds this new connection to the list of connections
~bcm // deconstructor will auto disconnect all signals
```
