sandbot-wptgen
==============

Sandbot waypoint generator.

Based off bsp_tools by Jeffrey 'botman' Broome.


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

### Linux

End to end tests:
```
tests/test.sh
```


License
-------

The original project is GPLv2, so the original code is GPLv2. New code is not GPLv2 (check the comments at the top of the files).
