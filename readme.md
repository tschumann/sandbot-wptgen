sandbot-wptgen
==============

Sandbot waypoint generator.

Based off bsp_tools by Jeffrey 'botman' Broome.


Usage
-----

```
sandbot-wptgen -wN -sinfo_spawn_entity mapname.bsp
```

A larger value of N will result in faster waypoint generation as the expense of fewer waypoints.


Tests
-----

```
powershell tests/test.ps1 Debug
powershell tests/test.ps1 Release
```


License
-------

GPL V2, because that's what the original project is.
