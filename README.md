<pre>
          __         _     __         
         / /_  _____(_)___/ /___ ____ 
        / __ \/ ___/ / __  / __ `/ _ \
       / /_/ / /  / / /_/ / /_/ /  __/
      /_.___/_/  /_/\__,_/\__, /\___/ 
                         /____/       
                                                                
                version 0.7.0
 Copyright (c) 2005-2024 Elwynor Technologies
</pre>

## WHAT IS BRIDGE?

 Bridge is a multi-player text-based bridge game.  The game plays
 bridge for up to four players at a table, with the ability for
 people to sit down as a trainee to learn the game from another
 player as he/she plays.
 
## GAMEPLAY
 
 The game plays like bridge would if you were playing in person.
 The seats at the table are labeled North, South, East, and West.
 Trainees may sit alongside a player.  
 
## COMMANDS
 
 The game starts and resets upon command when all seats are empty.
 
 The following are game commands:
 
 Anytime within the game:
 /table, /bids, /myhand, /faceup (dummy), $ (for score sheet), + (priv msg)
 
 Dealer commands:
 /shuffle, /deal
 
 Bidder commands:
 /1heart, /pass, /2notrump, /double, /redouble
 
 Play commands:
 /<card> - e.g. /h4 = heart 4, /d10 = diamonds 10, /sa = spade ace
 
## INSTALLATION AND CONFIGURATION
 
 Simply unzip the game archive to your BBS server directory,
 add the module to your menu, configure the MSG file to your liking, 
 and start the BBS! It's that easy! 

## GAME HISTORY
 
 Bridge was written and developed by Gene Swope of Amusers, Inc, in 1988-89.
 Elwynor Technologies acquired the module in 2004, and ported it to
 MBBS/WG DOS in October 2004 and to Worldgroup 3.2 in February 2006. It was
 then ported to Major BBS V10 in July 2024.
 
## LICENSE

 This project is licensed under the AGPL v3. Additional terms apply to 
 contributions and derivative projects. Please see the LICENSE file for 
 more details.

## CONTRIBUTING

 We welcome contributions from the community. By contributing, you agree to the
 terms outlined in the CONTRIBUTING file.

## CREATING A FORK

 If you create an entirely new project based on this work, it must be licensed 
 under the AGPL v3, assign all right, title, and interest, including all 
 copyrights, in and to your fork to Rick Hadsall and Elwynor Technologies, and 
 you must include the additional terms from the LICENSE file in your project's 
 LICENSE file.

## COMPILATION

 This is a Worldgroup 3.2 / Major BBS v10 module. It's compiled using Borland
 C/C++ 5.0 for Worldgroup 3.2. If you have a working Worldgroup 3.2 development
 kit, a simple "make -f ELWBR" should do it! For Major BBS v10, import this
 project folder in the isv/ subtree of Visual Studio 2022, right click the
 project name and choose build! When ready to build for "release", ensure you
 are building for release.

## PACKING UP

 The DIST folder includes all of the items that should be packaged up in a 
 ELWBR.ZIP. When unzipped in a Worldgroup 3.2 or Major BBS V10 installation 
 folder, it "installs" the module.
