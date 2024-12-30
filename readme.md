sandbot-wptgen
==============

Sandbot waypoint generator.

Based off [BSP_tool](http://hpb-bot.bots-united.com/bsp_tool.html) by Jeffrey 'botman' Broome.


Cloning
-------

Checkout the submodules:
```
git submodule init
git submodule update --recursive
```


Building
--------

### Linux

```
sudo apt-get install make gcc gcc-multilib g++-multilib
cd sandbot-wptgen/
make
```

### Windows

Open `sandbot-wptgen.sln` in Visual Studio and build.


Usage
-----

```
sandbot-wptgen -wN -fS -sinfo_spawn_entity mapname.bsp
```

A larger value of N will result in faster waypoint generation as the expense of fewer waypoints.


Tests
-----

### Windows

End to end tests:
```
tests/test.sh
```

You can specify whether to use the x86 or x64 build too:
```
tests/test.sh -p x86
tests/test.sh -p x64
```

Unit tests:
```
tests/test_unit.ps1
```

Code scan:
```
tests/scan.ps1
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
