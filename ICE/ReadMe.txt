================================================================================
    ICE Project - Kirth Gersen /KGJV (kgersen@hotmail.com)
    Release 3.4 (major build)
===============================================================================

Disclaimer & warning:

Provided "as is"
No documentation
Use at your own risk:
  To avoid breaking your alleg installation, always use ICE on
  a backup of the artwork folder

History:

NEW IN 1.50
	. added some bmp view (faction,ship (doesnt work well use model name instead of bmp name)).
	. the refresh button recompute the whole list (when u change an object name the list is not
	  update with the new name, so use this button to).
	. SHIPS:
		. the various masks (missiles,pack,...) are regrouped with a droplist
                  ('save' before selected another mask to apply ur changes).
                  (the 'undef' may be masks of some sort. Need to decode these.)
		. weapons slots fully implemented: The mask refer to the weapon masks ("usemask" in weapon view).
		  there is 2 unknnow values WS1 and WS2 (almost always constants (see AS for diff values for instance).
		  change the "# parts" value and save to update the dropdown list.(so yes ICE 1.15 can change the #
		  of weapons/turrets :)).

NEW IN 1.60
  - ships: display bug corrected (mask), HP and cost added (at last!!!)
  - projectiles: now show corresponding weapon(s)
  - factions: added lifepod id (was SUK2)

NEW IN 1.70
  - missing probes datas added.
  - projectiles: added matching probes

NEW IN 1.80
  - globals (drop-down list display index in decimal / hex)
  - "clear Pre" and "clear Def" (warning : "instant" apply, no undo) for tech tree
  - Ships: 
    default loadout is now a multi-select list box with 2 states ("edit" check-box)
    When edit is on  : select/deselect the items
    When edit is off : only show the selected items
    Only parts that are not upgrades of other parts are shown (ie mk1 parts)
	Use the ship save button to apply changes
  - Stations: added SH0,..,SH3. These values are mostly bit-masks related to shield,hull properties (lite,standard,hvy)     and to other properties.
    I repost here, spunky's first guess at these values:
        SH0 and SH1 behave in unison:

	SH0
	Major base=0111
	Minor base=0110
	Light base=1100

	SH1
	Major base=1010
	Minor base=1001
	Light base=1101

	SH2
		b3=ripcord
		b0=miners can offload here

	SH3=
		b5=heavy tele or special mines
		b4=SY
		b3=ref
		b2=for "platform" only
		b1=major base
		b0=dockable base

     NB: SHx input boxes use decimal values, so u'll have to perform the bits conversion (i know i'm lazy :)).

   - Others objects: i've added your inputs. Unconfirmed values are followed by a '?'.

NEW IN 1.85
  - Armor damage modifiers have now their own interface ("globals" entry, top of objects tree).
    I assume there is 20 sets of damage modifiers (DM00 to DM19).
    Missiles & projectiles now use a dropdown list for their DM.
    Each DM have 20 Armor classes modifiers. 
    So i assume there is 20 Armor classes (AC), named according to spunky's post.
    Ships & Stations now use a dropdown list for their AC (2 for stations).
    That gives 400 (20 DM x 20 AC) globals.
    There are 1 unfound DM (DM06) and 3 unusued DM (DM00,DM14,DM19).
    May be the unfound DM is for mines/caltrop. We should test the validity of DM00 too.
    According to the values, there are 1 unfound AC (AC11) and 6 unusued AC (AC15 to AC19).
    According to agc.dll, every 'concrete' object in the game have an armor class so may
    be the unfound AC is for missiles and probes.
    Otherwise these DM/AC look free to be used for our changes/adds.

    The first undecoded 40 globals remain in the lower part of the interface.

NEW IN 1.86
  - Fix stupid bugs in probes (on save SS4 & proj are messed up and
    negative entries couldnt be entered).

NEW IN 1.90
  - your inputs: nothing added yet, can u post a final status on recent probe values.
  - "refresh" button now reselect the object in the main left tree.
  - stations are no longer regrouped by faction (this regroupment was based on UIDs values
    and worked because of the values used (no longer valid for new bases)).
    NB: AGM still use this regroupment (so AGM might not handle correctly new bases
    (they will display  under gigacorp ).
    
  - ADDING (1st shoot, DELETE NOT IMPLEMENTED (:)):
    Adding a new object works by duplicating an existing one.
    Use the "duplicate" button. The current object is copied and the left tree is reloaded
    and expanded to the new copy. The new object is an exact copy except for its UID
    which is generated to be unique, so its recommended to rename the new copy immediatly.
    (Except for a projectile since its name is based on its UID).
    To duplicate a missile,mine,probe or counter: duplicate its "proxy part" (ie invmiss,invmine,..).
    ICE will duplicate both the proxy and the real part, link the two new copies together and
    then select the 'new part'. 

NEW IN 1.95:
  - your inputs on factions and probes

  - mines SS1/SS2 exposed

  - known sound entries

  - removed some bmp preview buttons and added model pre-preview (ships only/not functionnal yet)
    This will be moved to AMT (Allegiance Modeling Tool) when available.

  - all globals moved to 'globals' dialog.
    Global can be named (use a config file 'ice.ini')
    Use the 'set' button to change the value and/or the name of the selected global.
    Use the inner 'save' button to update the 'ice.ini' with the new names.
    DO NOT HAND EDIT ice.ini

  - Tech tree interface reworked.
    Type a value in the little box,use + or - to inc/dec this value.
    When editing the litte box, the right most window shows infos on that value.
    Use Toggle Pre/Def to add/remove this value from the Pre/Def set
    Clear All Pre and Clear All Def as before

NEW IN 1.96
  - Changed: renaming an entry now refresh the main list
    (minor bug: the tech tree is cleared, so reselect the entry if u want it)
  - Added: 2 bookmarks (top of window), use leading '>' to store and trailing '>' to recall.
  - Added: devel "path" entry, allowing to move a devel from a path to another
  - Aded: window can now be minimized 

NEW IN 1.97
  - relaxed "core 'magic' check" upon load so that latest cores from final alleg update can be loaded.

NEW IN 2.0
  * devel icon can now be changed. 
  * some images name have a leading letter that indicates that the used
    bmp.mdl file is prefixed with this letter.
    (example in devel icon: acs48 -> iacs48bmp.mdl)
    Once saved, click on the image to refresh it
  * station SS0 =  drone UID
  * shields, todo, last 2 words = sounds
  * cloak, SS1 and SS2 = sounds
  * some cleanup (decode boxes removed)
  * replacement problem fixed (entries sorted before saved).
  * all saved cores with this version are now compatible with AGM 1.10 or later

NEW IN 2.1
  * your inputs on missiles + sound entries
  * 'cargo playload' on mines,probes and missiles = cargo space the object occupies per slot
  * proxy parts :1 bug fix upon saving and  swarm type added

NEW IN 2.2
  * shields:  "B1" is now "Armor Class" with a dropdown list (so we can build special AC shields :))
  * stations: SH2 & SH3 input values replaced by bit fields (see partial decode below)
  * stations: "caps can dock" rename "caps can launch + Def 247"
  * ships: "capital?" bug fixed, 'isdock' renamed 'carrier', 'figther?' renamed 'small ship'
  * Cap ships/Sy: how it works
       cap = ship with 'small ship' unchecked
       if a cap ship must be available only when a sy/drydock is available then add '247' to the cap Pre set
       (all MS standard caps use this).
       cap can launch from stations that have 'cap can launch + def 247' checked
       cap can dock to stations that have 'SS3 bit #4' checked and 'capgarage' entries in their models (cvh file).

  * station SH2 & SH3:
	SH2
		b5=can dock
		b3=ripcord
		b0=miners can offload here

	SH3=
		b5= pick pods 
		b4=caps can dock 
		b3= ? (ref)
		b2=for "platform" only
		b1=major base
		b0=dockable base
NEW IN 2.3:
  * added sorting option (for stations & devels only):
      when 'sort' is clicked: entries are displayed alphabetically
      when 'sort' in unclicked: entries are in the order they'll appear in game.
           and u can use "move up" & "move down" buttons.
  * ships: relay lead indicator (was "capital?") & has lead indicator (was F2048)

NEW IN 2.4:
  * "loadout bmp" renamed "inactive model - loadout"
  * you inputs on missiles and global #32
  * drones:
	   + ss1 = AI script ( miner=0,wingman=2,layer=5,con=6,carrier=9 )
	   + added part uid for drones. Set mine/probe uid for AI script #5 (layer),
	    -1 for other scripts.
	    WARNING: if set to a probe uid, the probe object MUST have a projectile
	    or the server will crash (when "build on aleph" is ordered).
	    (set ammo to 0 or use a dummy projectile if u want a harmless probe).

  * Mines & Probes can now be duplicated directly (ie without duplicating a linked
    proxy part). Mines & Probes duplicated that way can only be used by layers
    (drone)
  * delete implemented (at last !).

NEW IN 2.5:
  * sig% for parts exposed
  * ss2/ss4 for weapons = sounds
  * probes features bits (was SS3)
  * "description" exposed for stations (oops :), funny no one noticed it was missing)
  * compiled with VS.Net Release

NEW IN 2.6
 
  * Treasures Set exposed ! (chance value remain to be explained :)). Treasure Set cant be duplicated
    cause i dont the point of having more than 1 treasure set... until i mod AGM map editor to build
    custom map that use diff treasure sets than the default one.

  * bmp display fixed , now use same code as AMT.
  * lotta new values/correction exposed everywhere (correlated with fed sql from allegiancetool.zip).
  * group for ships (0 or 4 for ships, -1 for miners/drones/cons (ie to hide them in F4 screen))
  * stations:
     * Local techtree set in stations exposed - These new tech numbers are local to the station and
       allows more dependancies. This is a 'Def' set only. Only available for stations.
     * station type renamed to 'class', custom classes entries added. Class is used by the game to
       perform tech "transfert" when a base is captured (TBV).
     * previous SH2/SH3 renamed with explicit names as shown in igc.h (some checks must be done here).

    
NEW IN 2.7
  * "sort" available for drones too
  * Thorium 'build on' option for Stations (warning: Thorium rocks only available in Custom maps).

NEW IN 2.8
  * special 1st public release (undocumented changes)
  * exe name changed to ICE.exe
  * file dialogs (open & save) dont default to alleg artwork anymore

NEW IN 2.9
  * UI reorg: main window is smaller by using "properties/tech tree" tabs.
  * proxy parts transfered into 'real parts' under 'Ship mounting properties' sub window. Probes and Mines 'Ship mounting properties' can be removed/added (unmountable probes/mines are for layer drones).
  * most 'overrided by' values now use -1 instead of 65535 for "no override".
  * F5 icon view for station added. The bmp file name is i<model>bmp.mdl and is mandatory in client artwork for "buidable" stations.
  * various fixes

NEW IN 2.95 - Experimental - Comments/Debug
  * filter in 'tech tree' panel. Use 'toggle filter' to add/remove from the filter set a tech number.
    The left main tree will be filtered and will display only the entries that have AT LEAST ALL the numbers of the filter set in their Pre set.
    (globals, factions, projectiles and treasure sets are never filtered).
    Examples:
       input '19' in the tech number and click 'toggle filter' should display giga specific entries.
    Use 'clear filter' to reset the full list.

NEW IN 2.96 
  * filter not experimental anymore
  * 'sort' implemented for ships & parts.
  * some memory leaks fixed.

NEW IN 2.97
  * command line argument (ice.exe <full path to a core.igc file> (you can also associate .igc files to ice.exe in order to load them
    by double-click from explorer).
  * left 'tree' refresh time optimization.
  * sort on subparts (mines,chaffs,missiles and probes).
    When in sort mode, subparts are mixed with other parts (weapons,...) in order to sort them for loadout screen (ie no more 
    mines,chaffs,missiles and probes subtrees).
  * sort on factions
  
NEW IN 2.98
  * some field names changed (projs,stations, mines)
  * "DM00 been used by collision" is now indicated
  * refresh upon save (to refresh the 'auto sort' on save).
  * stations: 	'tele unload' renamed to 'Miners can tele offload' (ie offloading without docking).
    The 'Miners can offload' flag is needed too so the UI now handles the dependancy.
  
NEW IN 3.0
  * redesign of parts usage masks & ship loadout editing (new tab in shis view)

NEW IN 3.1
  * AC exposed for Probes
  * minor UI layout fixes
  * prevent 'description' and 'name' fields to overflow (200 & 25 chars max resp.)
  * fix corruption bug on 'mount enable' for probes/mines.
  * auto backup ('backup' check box near 'Save').
    Backups are named "core.001.igc", "core.002.igc", ... (where "core" is actual core name)
    The numbering sequence doesnt check for 'holes' so if core.001.igc and core.003.igc exist
    but not core.002.igc then next backup will be 002 not 004. Upon reaching 999, backup will fail.

NEW IN 3.2
  * one sided resonator feature for missiles
  * layout change for missiles

NEW IN 3.21
  * enabled Blast Power (AOE) for missiles

NEW IN 3.30
  * removed "16 bits desktop resolution" limitation. ICE will now always display images whatever the desktop resolution.
  * fix in missiles: icon can now be changed

NEW IN 3.31
  * changed display for factions pre/def tech bits
  * added 'no devel' dependancies display for tech bits
See TechTree.txt for documention on the techtree (NEW IN 1.95)

NEW IN 3.4
  * 'validate' button to find next error
  * shorcuts buttons and links everywhere to jump to referenced objects (successors, projectiles,...)
  * switchable DM/AC editing
  * dump to xml or txt file
  * compare with other core
  * check artwork for missing files

Known bugs:
	none

Kirth
/////////////////////////////////////////////////////////////////////////////
