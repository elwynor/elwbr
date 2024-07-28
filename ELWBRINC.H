/*****************************************************************************
 * AMBR.H                                         Contract Bridge   V. 0.6.a *
 *                                                                           * 
 * (c) 1989  Amusers! Inc.                    By Gene Swope and Scott LaFond *
 * Copyright (c) 2004-2024 Rick Hadsall                                      *
 *                                                                           * 
 * MBBS v6.25/WG1/WG2 DOS Port - October 2004 - Rick Hadsall                 *
 * Worldgroup v3.2 Port - February 2006 - Rick Hadsall                       *
 * Major BBS V10 Port - July 2024 - Rick Hadsall                             *
 *                                                                           * 
 * This program is free software: you can redistribute it and/or modify      *
 * it under the terms of the GNU Affero General Public License as published  *
 * by the Free Software Foundation, either version 3 of the License, or      *
 * (at your option) any later version.                                       *
 *                                                                           *
 * This program is distributed in the hope that it will be useful,           *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of            *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the              *
 * GNU Affero General Public License for more details.                       *
 *                                                                           *
 * You should have received a copy of the GNU Affero General Public License  *
 * along with this program. If not, see <https://www.gnu.org/licenses/>.     *
 *                                                                           *
 * Additional Terms for Contributors:                                        *
 * 1. By contributing to this project, you agree to assign all right, title, *
 *    and interest, including all copyrights, in and to your contributions   *
 *    to Rick Hadsall and Elwynor Technologies.                              *
 * 2. You grant Rick Hadsall and Elwynor Technologies a non-exclusive,       *
 *    royalty-free, worldwide license to use, reproduce, prepare derivative  *
 *    works of, publicly display, publicly perform, sublicense, and          *
 *    distribute your contributions                                          *
 * 3. You represent that you have the legal right to make your contributions *
 *    and that the contributions do not infringe any third-party rights.     *
 * 4. Rick Hadsall and Elwynor Technologies are not obligated to incorporate *
 *    any contributions into the project.                                    *
 * 5. This project is licensed under the AGPL v3, and any derivative works   *
 *    must also be licensed under the AGPL v3.                               *
 * 6. If you create an entirely new project (a fork) based on this work, it  *
 *    must also be licensed under the AGPL v3, you assign all right, title,  *
 *    and interest, including all copyrights, in and to your contributions   *
 *    to Rick Hadsall and Elwynor Technologies, and you must include these   *
 *    additional terms in your project's LICENSE file(s).                    *
 *                                                                           *
 * By contributing to this project, you agree to these terms.                *
 *                                                                           *
 *****************************************************************************/

/*靈컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
  틊his structure is used for personal parameters
  聃컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 */
struct ablooker {      /* personal information on player in menu */
  LONG flags;          /* various user flags */
  INT  sitting;
}  *aball,             /* one for each line on system */
   *aballptr;          /* general purpose pointer */

/*靈컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
  틊his structure details each person at the table.
  聃컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 */
struct abplayer {      /* personal information on player in game */
  LONG flags;          /* various user flags */
  CHAR id[UIDSIZ];     /* players handle */
  INT  channel;        /* channel number of player */
  CHAR card[5];        /* last card played */
  INT  cardv;          /* value of last card played */
  INT  cards[4][13];   /* flag array for cards held */
}  *abinplay,          /* one for each N,S,E,W */
   *abintran,          /* one for esch N,S,E,W */
   *abplyptr,          /* general purpose pointer */
   *abplypto;          /* general purpose pointer */

/*靈컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
  틊his variable holds the various game flags.
  聃컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 */
LONG abflags;          /* game flags */

/*靈컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
  틊he following are values of the game and user flags.
  聃컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 */
#define SILENT   1     /* players must be silent in the game */
#define DOUBLED  4     /* bid has been doubled */
#define RDOUBLED 8     /* bid has been redoubled */ 
#define NSVULN   16    /* N-S vulverable */
#define EWVULN   32    /* E-W vulverable */
#define ABRUBOVR 64    /* flag indicates that rubber is over */
#define GRAPHIC  32768 /* player wants graphic display */

/*靈컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
  틍alues for the following are in AMBRMSG.h (from the .msg file)
  聃컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 */
INT  abpmode;          /* mode of play at current time */

/*靈컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
  틊he following variables can have the value NORTH EAST SOUTH or WEST
  �(defined in AMBRMSG.h from the .msg file) or NODUMMY below.
  聃컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 */
INT  abturn;           /* who's turn it is to do something */
INT  abturnp;          /* which seat position to play from */
INT  abdealer;         /* who is the current dealer */
INT  abdummy;          /* who is the current dummy  */
INT  ambrisit;         /* who's text is being processed */
INT  abhibidr;         /* current highest biddder */

#define NODUMMY   255


/*靈컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
  틍arious global pointers and values
  聃컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 */
INT  abpassno;         /* counts consecutive passes */
INT  abbidno;          /* counts number of valid bids */
INT  abhibid;          /* value of the highest bid so far */
INT  abtrickn;         /* number of tricks taken by N-S */
INT  abtricke;         /* number of tricks taken by E-W */
INT  absuitld;         /* suit led */
INT  abcplayd;         /* number of cards on this trick */
INT  abhonorn;         /* NS honors bonus for this hand */
INT  abhonore;         /* EW */
INT  ababoven;         /* NS above line score */
INT  ababovee;         /* EW */
INT  abgamen;          /* NS games won */
INT  abgamee;          /* EW */
INT  abpartn;          /* NS part score */
INT  abparte;          /* EW */
INT  abtotn;           /* NS total score */
INT  abtote;           /* EW */

/*靈컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
  틊his is the entire deck of cards
  聃컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 */
#define ABDKSIZE 52
INT abdeck[ABDKSIZE];

/*靈컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
  틊his is the bidding history.
  聃컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 */
#define ABMAXBID 115
INT abbidrec[ABMAXBID];

/*靈컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
  틊he suit names.
  聃컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 */
CHAR *absnames[]={"C","D","H","S","NT"};

/*靈컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
  틊he LONG suit names.
  聃컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 */
CHAR *absnamel[]={"Club","Diamond","Heart","Spade","No Trump"};

/*靈컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
  틊he card names.
  聃컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 */
CHAR *abcnames[]={"2","3","4","5","6","7","8","9","10","J","Q","K","A"};

/*靈컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
  틊he LONG card names.
  聃컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 */
CHAR *abcnamel[]={"2","3","4","5","6","7","8","9","10",
                  "Jack","Queen","King","Ace"};

/*靈컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
  틊he seat positions.
  聃컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 */
CHAR *abseatn[]={"N","E","S","W"};
