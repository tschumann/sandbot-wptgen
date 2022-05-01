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
```
powershell tests/test.ps1
tests/test.sh
```

### Linux
```
tests/test.sh
```


License
-------

GPL V2, because that's what the original project is.
