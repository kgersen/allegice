# AME (ALLEGIANCE MAP EDITOR) - Release History

## Version 1.98 (February 20, 2025)
- Built with VS2022
- Sector planet bitmap is now customizable (select the last value in the dropdown)
- Note: Not added to sector templates

## Version 1.97 (December 3, 2017)
- Updated to use Steam registry (HKCU - 1.4)

## Version 1.96 (August 6, 2008)
- Now uses freeimage as a dll
- MDL bitmaps previews available regardless of desktop screen resolution
- Added "fixed position" aleph property
  - Position won't be randomized (supported in Allegiance R5)
  - Shows leading "*" in aleph name for R4 or previous versions
  - Fixed position alephs shown as black dot with blue border
- Updated default values to match server code:
  - Aleph default radius: 100 (was 200)
  - Rock default sig: radius/100 (was radius/10)
  - Rock default HP: scales to radius
  - He3 rock default helium: 65 (was radius*2)
- Aleph icon now displayed and editable

## Version 1.95 (2003)
- Various fixes regarding bases/core

## Version 1.9 (March 12, 2003)
- Fixed randomize rocks crash bug
- Added "inner alephs" creation (aleph to same sector)
- Enhanced custom nebula globe sector model choice

## Version 1.8 (March 11, 2003)
- AME became a standalone tool
- Fixed base list choices from core
- Enhanced custom rock model choice

## Version 1.7 (July 16, 2002)
- Added Thorium rock type

## Version 1.6 (May 27, 2002)
- Full sector properties exposed
- Planet BMP displayed (requires 16bits color display & client artwork)
- Distance to center shown when moving objects
- Z coordinate displayed near object (when using ctrl-click drag)

## Version 1.5 (April 30, 2002)
- Added support for server version 1.0.0.4
- Maintained compatibility with previous version (1.0.0.3004)
- Preserved Allsrv32.exe file date/time when setting core

## Version 1.4 (March 30, 2002)
- New Alephs randomize algorithm with parameters
- Added View Z coords option for alephs & bases
- Added Rename sectors option using text file

## Version 1.3 (February 24, 2002)
- Changed "Starting money" & "Total money" to input boxes (0-9 range, fractional values allowed)
- Added "Game length" settings in minutes (0 for unlimited)

## Version 1.2 (February 19, 2002)
- Added new game option: prosperity
- Built with VS.Net release version

## Version 1.1 (July 3, 2001)
- Updated to work with new cores from Allegiance Final update

## Version 1.0 (July 3, 2001)
- AGM Updates:
  - Added DeathMatch option with kill goals
  - Added "N/A" imbalance choice
  - Added toggles for eject pods, Friendly fire, and Lives
  - Added server core selection
- AME Updates:
  - Fixed Z coordinates display
  - Added keyboard shortcuts:
    - Paste: shift + LMB click
    - Copy: shift + RMB click
    - Delete: ctrl + RMB click
  - Added rocks layout option

## RC (May 1, 2001)
- Added copy/paste for bases & rocks
- Reduced font size for sector view
- Added templates with 'apply to' feature
- Added sector info display
- Added snap and grid switches
- Added in-game "scrolling zone" on mini-map grid
- Added sector name display on mouse over

[Earlier versions omitted for brevity, dating back to BETA 0 release on April 6, 2001]
