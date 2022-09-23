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
tests/test.sh x86
tests/test.sh x64
```

### Linux

End to end tests:
```
tests/test.sh
```


License
-------

The original project is GPLv2, so the original code is GPLv2. New code is not GPLv2 (check the comments at the top of the files).
