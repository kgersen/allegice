# AME - ALLEGIANCE MAP EDITOR

## A. Installation

### You need to run AME on a computer where Allegiance is installed

Nothing else to install. Just launch "AME.EXE". Keep FreeImage.dll with the .exe

## B. Using AME (new in this release = blue)

The button 'MAP EDITOR' launch the map editor (AME)

Use the **New** button to create a new map from scratch
Use the **Load** button to load an existing one.  
"Save" and "Save as" are obvious.

Map name is displayed on top right line.

![](readme1.gif)

AME basics:

### Sectors creation/deletion/moving/properties
**right double-click on mini-map to create a sector**  
left click a sector in the sectors list or in the mini-map to view its content (big right frame called 'sector view' here after)  
double-left clic on a sector in the sectors list or in the mini-map to edit its properties (u can **delete it** from there then)  
use the mini-map (lower left) to move sector (left mouse button drag, right button to cancel while dragging)  
moving mouse over a sector display its name  
the mini-map auto-scale so that it doesnt need scrolling. The red frame shows the 'in-game' mini-map scrolling zone. Drag sector off the mini-map (right or top) to up the scale.  
When grid snap is on, sectors can only be created and dragged to the grid.
### Alephs - creation/deletion/properties editing
right click on a sector in the mini-map and drag the mouse to another sector then release the button to create an aleph (when yellow the line turn green)  
(aleph are created at random coords (**updated**) )  
double-clic or right clicking on it and select "properties"  to edit its props (**updated ("no spin" option)**)
U can delete an aleph by right clicking on it and selecting "delete" (the connection aleph in the other sector is also deleted).  
Renaming a sector rename all matching alephs  
Added: 'randomize alephs' in the right-click sector menu  
The mini-map now use a 'grid snap' of 0.1 and a grid view. (use the 2 toggles to turn on/off these)  
The sector are now colored by the "team" they belong to (see bases colors below).
### Bases - creation/deletion/properties 
editing****right click an empty space** in the sector view to bring the menu and select 'add base' (default: garrison of team1).  
base color **match** the team color (as the game: Team1 = yellow, Team2 = blue, Team3=purple and so on)  
bring the right click menu to delete a base or all bases in the sector  
**double-clic** a base to edit its properties  
Use the 'type' button to display a cascading menu of all base types and select the one (base name will change too but u can edit it after).  
Also note that the server **doesnt** compute the leader board at start so if a team has more bases (gar or tech) then another , game will display 50%/50% at start until a new base is created (or one is destroyed) while playing.  
### Rocks - creation/deletion/properties  
NB:** Once a sector has AT LEAST 1 rock then then server doesnt generate anything in it. If the sector has no rock at all in the map then the server generates asteriods,he3 and resources according to the game settings or the team setting of the sector (neutral or home sector).**right click an empty space** in the sector view to bring the menu and go in 'Add rock' submenu to choose a standard rock type.  
Use 'Add asteriods Layout' to add many asteriods  at a time. The layout uses the following parameters:  
   Center (CX,CY,CZ), Radius ,Z Variance (ZVar) ,  Number of rocks (nbrocks).  
Generate nbrocks (using rock templates for size,hp and sig) on a given disc (Center and radius).  
The rocks are randomly placed within the disc boundaries. If ZVar is 0, all rocks are on the same Z plan (CZ), otherwise they're randomly set above and under the Z plan (CZ) (ie between CZ+ZVaz and CZ-Zvar).  
All rock are **red dots** **surrounded** by a  color matching their 'abilities' ('features' in rock properties) as in the game (grey for asteriod, white for helium, green for silicon, ...). If a rock has **no abilities** or **more then one** (yes, can be :)) then the surrounding color is **pink**.  
bring the right click menu to delete a rock or all rocks in the sector  
**double-clic** a base to edit its properties:  
the name of the rock is auto upon creation but u can edit it. Check 'hidden' to not see it in the F3 view of the game  
the icon is the little rock icon showing near the rock and on "right column of the extended mini-map in the game" (icon doesnt not need to match the feature of the rock but its better to do so cause players might went crazy :)) (u can set here 2 new icons that will also show in the game mini-map :))  
the render is the rendering model of the rock (need help here to set the good 'template' render). **Custom** render are implemented now (partial object lists (bases,ships,missiles,counters only for now))  
sig and radius are same as for alephs (default is sig = radius / 10)  
HP = hitpoints (default = radius \*5)  
HP gauge = display or not the HP gauge of the rock (standard in the game for he3 and tech rocks)  
Phantom = HP to zero and HP gauge on = the rock (bug in alleg ? :) cant be **destroyed** and can be fly thru (player ships only). But it still cut the line of sight (good place to hide in :))  
Random spin & orientation for rocks. AGM will fix maps with invalid spin values upon load.  
Added: 'randomize rocks' in the right-click sector menu  
the template list set most of the  properties back to one of the standard types of rock (except name & render)
### Alephs, Bases and Rocks moving**:  
Use left mouse button to drag object.  
**Use** **CTRL + Left mouse button to set Z coord of object**.
* Added: global buttons to randomize alephs and rocks positions and to delete objects.
* Added: cut & paste rocks & bases, shortcuts (LMB = left mouse button, RMB = right mouse button):  
      Paste = shift + LMB click  
      Copy = shift + RMB click  
      Delete = ctrl + RMB click
* Added: sector templates with 'apply to' feature
* Added: aleph templates with 'apply to' feature
* Added: rocks templates with 'apply to' feature

## E. History / Changes
see [CHANGELOG.md](CHANGELOG.md)

Please all bugs report to [www.alleg.net](http://www.alleg.net) in the corresponding board or on Alleg discord.

Kirth Gersen/KGJV [(kgersen@hotmail.com](mailto:(kgersen@hotmail.com))

Thx to Nick Thoman  (NoodleNT) for his cool icon , gj man :)  
Thx to Maurice Spee for the SLA.

And to the many beta-testers and users
