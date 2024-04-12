sandbot-wptgen
==============

Sandbot waypoint generator.

Based off [BSP_tool](http://hpb-bot.bots-united.com/bsp_tool.html) by Jeffrey 'botman' Broome.


Building
--------

### Linux

```
sudo apt-get install make gcc gcc-multilib g++-multilib
cd sandbot-wptgen/
make
```


Usage
-----

```
sandbot-wptgen -wN -sinfo_spawn_entity mapname.bsp
```

A larger value of N will result in faster waypoint generation as the expense of fewer waypoints.


Tests
-----

### Windows

End to end and unit tests:
```
tests/test.sh
```
You can specify whether to use the x86 or x64 build too:
```
tests/test.sh -p x86
tests/test.sh -p x64
```

### Linux

End to end tests:
```
tests/test.sh
```
Performance and undefined behaviour tests:
```
tests/test.sh -t gprof
tests/test.sh -t ubsan
```


License
-------

GPL v2 because the original project is GPL v2.
