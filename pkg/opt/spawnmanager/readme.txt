This spawn system is based on a multi-agent implementation.
groupmanager is the agent which holds the spawn groups, and each regionmanager is an agent, which manages npc respawn, asking group manager for templates.
This pkg works with both 092 and 094, as tested.

This package also includes the text commands which make possible to manipulate the regions and groups by execution time:
-> .spawnmanager: allows groups/regions creation, manipulation, destroy, et al.
  * group managing: you can add a new group, delete an existing group, add template to a group, erase a template from a group...........
  * region managing: kinda like the groups, with one addition: you can enable/disable a region. A disabled region will not respawn dead npcs until enabled.
-> .buildmanagers: create managers for any regions which happen to have been destroyed.
-> .removemanagers: destroy all managers, which provides their spawns destruction.

How to install:

- Read howto_install.txt...

////////////////////////////////////////////
////Adriano Iank <aiank@convoy.com.br>  ////
////////////////////////////////////////////