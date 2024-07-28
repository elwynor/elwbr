/*****************************************************************************
 * AMBR.C                                         Contract Bridge   V. 0.6.a *
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

#include "gcomm.h"
#include "majorbbs.h"
#include "elwbrinc.h"
#include "elwbr.h"

/*VOID EXPORT init__bridge(VOID);*/
GBOOL bridgeLogon(VOID);
GBOOL bridgeInput(VOID);
VOID bridgeHangup(VOID);
VOID bridgeShutdown(VOID);

VOID ambrdcld(VOID);
VOID ambrmain(VOID);
VOID ambrhow(VOID);
VOID ambrparm(VOID);
VOID ambrsit(INT tmode);
VOID ambrbye(VOID);
VOID ambrcold(VOID);
VOID absetpar(VOID);
VOID ambrdsit(INT seat,INT tmode);
VOID ambrleav(INT tmode);
VOID ambrproc(INT tmode);
VOID ambrprom(INT tmode,INT mynum);
VOID ambrget(INT tmode,INT mynum);
VOID abcksil(VOID);
VOID absend7(VOID);
INT ambrsply(INT tmode);
VOID abshufl(VOID);
VOID abdump(VOID);
VOID abclrbid(VOID);
VOID abclrsc(VOID);
INT abwtran(VOID);
VOID abdispar(VOID);
VOID abwhispr(INT tmode);
VOID abhelpme(VOID);
VOID abslash(INT tmode);
VOID abscdisp(VOID);
VOID absndgos(INT tmode);
VOID abddeler(VOID);
VOID abdbider(VOID);
VOID abdplyer(VOID);
VOID abslasht(VOID);
VOID abln356(INT j,INT k);
VOID abdumt(VOID);
VOID abduml(INT linptr,CHAR *cl,CHAR *cr);
VOID abdumr(INT linptr);
VOID abslashb(VOID);
VOID abslashm(VOID);
VOID abslashf(VOID);
VOID abshowh(INT which);
INT abdumln(VOID);
VOID abslashs(VOID);
VOID abslashd(VOID);
VOID abbidpas(VOID);
VOID abbiddbl(VOID);
VOID abbidrdb(VOID);
VOID abbidsut(VOID);
VOID abckbid(INT bid);
VOID abgoplay(VOID);
VOID abgopdl(VOID);
VOID abstbid(INT bid);
CHAR *abbidtxt(INT bid);
VOID abplayit(VOID);
VOID abckply(INT value,INT suit);
VOID abhostrk(VOID);
VOID abschon(VOID);
INT abscho1(INT seat);
VOID abscupd(VOID);
VOID abclrcrd(VOID);
VOID absend1(INT seat,INT msg);
VOID ambrsels(INT tmode);
INT abtlkm(INT tmode);

#define VERSION "0.7.0"

static INT bridgestt;         /* Bridge module number (state)         */
struct module bridge={        /* module interface block               */
     "",                      /*    name used to refer to this module */
     bridgeLogon,             /*    user logon supplemental routine   */
     bridgeInput,             /*    input routine if selected         */
     NULL,                    /*    status-input routine if selected  */
     NULL,                    /*    "injoth" routine for this module  */
     NULL,                    /*    user logoff supplemental routine  */
     NULL,                    /*    hangup (lost carrier) routine     */
     NULL,                    /*    midnight cleanup routine          */
     NULL,                    /*    delete-account routine            */
     bridgeShutdown          /*    finish-up (sys shutdown) routine  */
};

static
HMCVFILE brmb;                   /* message block pointer             */

/*靈컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
  틄ower up initialization.
  聃컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 */
void EXPORT init__elwbr(void)
{
 
     stzcpy(bridge.descrp,gmdnam("ELWBR.MDF"),MNMSIZ);
     bridgestt=register_module(&bridge);
     brmb=opnmsg("elwbr.mcv");     /* define messaage file  */

/*靈컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
  튲ynamic memory allocation for structures.
  聃컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 */
     aball=(struct ablooker *)alcmem(nterms*sizeof(struct ablooker));
     abinplay=(struct abplayer *)alcmem(4*sizeof(struct abplayer));
     abintran=(struct abplayer *)alcmem(4*sizeof(struct abplayer));

     setmem(aball,nterms*sizeof(struct ablooker),0);
     setmem(abinplay,4*sizeof(struct abplayer),0);
     setmem(abintran,4*sizeof(struct abplayer),0);
/*靈컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
  튷nitialize all flags to their default value.
  聃컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 */
     ambrdcld();

     shocst(spr("ELW Bridge v%s",VERSION),"(C) Copyright 2004-24 Elwynor Technologies - www.elwynor.com");
}

/*靈컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
  틄layer has typed something, or has entered from Main BBS menu.
  聃컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 */
GBOOL bridgeInput()
{
    INT entstt = usrptr->substt;      /* substt when entered */
    INT tmode=-1;       /* 1=playing 0=training */

/*靈컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
  튷n this area, goes all the things that must be done each time
  튮 person types something.
  聃컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 */
     setmbk(brmb);               /* point to message file */
/*靈컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
  틊his dispatches to each area of the program depending on what
  틊he substate flag is. when first entered from the main menu
  틇ubstt is 0 .
  聃컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 */
     switch (entstt=usrptr->substt) {
     case 0:
          prfmsg(AMBRWELC,VERSION);        /* welcome meaasge */
          ambrmain();              /* show menu and set substt */
          break;
/*靈컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
  틄rocess a selection from the Main Menu.
  聃컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 */
     case AMBRMAIN:
          switch(toupper(*margv[0])) {
          case 'H': ambrhow();  break;     /* how to play */
          case 'P': ambrparm(); break;     /* set personal parameters */
          case 'S':                        /* undocumented alias for B */
          case 'B': ambrsit(1); break;     /* enter as a player */
          case 'T': ambrsit(0); break;     /* enter as a trainee */
          case 'X': ambrbye();  return(0); /* return to system */
          case 'R': ambrcold(); break;     /* reset the game */
          default:  ambrmain(); break;     /* unknown command */
          }
          break;
/*靈컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
  틇et personal parameters.
  聃컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 */
     case AMBRPERP: absetpar(); break;      /* set personal parameters */
/*靈컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
  틄rocess a selection from the seat selection menu.
  聃컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 */
     case ABPICK2T:
     case ABPICK2:
          tmode=entstt-ABPICK2T;
          switch(toupper(*margv[0])) {
          case 'N': ambrdsit(0,tmode); break;  /* sit down N if empty */
          case 'E': ambrdsit(1,tmode); break;  /* sit down E if empty */
          case 'S': ambrdsit(2,tmode); break;  /* sit down S if empty */
          case 'W': ambrdsit(3,tmode); break;  /* sit down W if empty */
          case 'X': ambrmain();        break;  /* return to main menu */
          default:  ambrsit(tmode);    break;  /* unknown command */
          }
          break;
/*靈컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
  틄rocess text input while in game.
  聃컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 */
     case AMBRPRMT:
     case AMBRPROM:
          tmode=entstt-AMBRPRMT;
          switch(toupper(*margv[0])) {
          case 'X': ambrleav(tmode);   break;      /* get up from table */
          default:  ambrproc(tmode);               /* any other command */
                    ambrprom(tmode,usrnum);
                    break;
          }
          break;
     }
/*靈컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
  튳nd of processing for this input.
  틃utput any text in buffer, and return control to major.
  聃컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 */
     outprf(usrnum);
     return(1);
}

/*靈컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
  튽eaving back to main BBS menu.
  聃컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 */
VOID ambrbye(VOID)  { 
   prfmsg(AMBRBYE);            /* say goodbye */
   outprf(usrnum);
}

/*靈컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
  튶angup routine.
  聃컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 */
VOID bridgeHangup(VOID)
{
   INT tmode;     /* 1=playing  0=training */
   INT entstt;
   entstt=usrptr->substt;
   if ( (usrptr->state == bridgestt)
      && ( (entstt==AMBRPRMT)|| (entstt==AMBRPROM)) ) {
         setmbk(brmb);                   /* point to message file */
         tmode=entstt-AMBRPRMT;
         ambrget(tmode,usrnum);
         strcpy (abplyptr->id,"\0");       /* set seat to empty */
         abcksil();
         prfmsg(ABANNCUT,usaptr->userid);  /* tell others who left */
         prfmsg(LNORTH+ambrisit);
         prfmsg(ABANNP2T+tmode);
         absend7();                        /* send it to others */
/*靈컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
  틁ote: abplyptr and abplypto are undeterined at this point.
  聃컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 */
   }
}

/*靈컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
  튣eset the game.
  聃컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 */
VOID ambrcold(VOID)
{
   if ( (usrptr->flags&MASTER) || (ambrsply(3)==8) ) {
        ambrdcld();
        prfmsg(ABGRESET);
   }
   ambrmain();
}

VOID ambrdcld(VOID)
{
     INT i,j,k;
     srand(now());                      /* seed random generator */
     for(i=0;i<ABDKSIZE;abdeck[i]=i++); /* initialize deck */
     for(i=0;i<4;i++) {
        abshufl();                      /* shuffle the cards */
        abplyptr=&abintran[i];
        strcpy (abplyptr->id,"\0");     /* set all trainee seats to empty */
        abplyptr=&abinplay[i];
        strcpy (abplyptr->id,"\0");     /* set all player  seats to empty */
        strcpy (abplyptr->card,"    "); /* set last card played to nothing*/
        for(k=0;k<4;k++){               /* for each suit */
          for(j=0;j<13;abplyptr->cards[k][j++]=0) ; /* clear all cards held */
        }
     }
     abclrbid();                        /* clear the bidding history */
     abclrsc();                         /* clear the score sheet */
     abpmode=PREDEAL;                   /* set mode to predeal */
     abdealer=rand()%4;                 /* set dealer to a random */
     abturn=abdealer;                   /* set whose turn to dealer */
     abdummy=NODUMMY;                   /* no one is dummy yet */
     abcksil();
   }


/*靈컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
  틇tubs for unimplemented major BBS functions.
  聃컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 */
/*靈컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
  튽og-on supplement.
  聃컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 */
GBOOL bridgeLogon(VOID)
{
   setmbk(brmb);                         /* point to message file */
   return(0);
}


/*靈컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
  틇ystem shutdown.
  聃컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 */
VOID bridgeShutdown(VOID) {
  clsmsg(brmb);
}




/*靈컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
  튧tility functions.
  聃컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 */
/*靈컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
  틊his routine sets the structure pointers for any given mynum
  튷t points abplyptr to mynum's structure and
  튮bplypto to the attached trainee/trainer's structure.
  聃컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 */
VOID ambrget(INT tmode,INT mynum)
/* 1=playing  0=training */
/* usernum of the person seting up */
{
       aballptr=&aball[mynum];      /* point to mynum's personal structure */
       ambrisit=aballptr->sitting;  /* dertermine mynum's seat */
       if (tmode) {         /* mynum is a player, attached is a trainee */
           abplyptr=&abinplay[aballptr->sitting];
           abplypto=&abintran[aballptr->sitting];
       }
       else {               /* mynum is a trainee, attached is a player */
           abplyptr=&abintran[aballptr->sitting];
           abplypto=&abinplay[aballptr->sitting];
       }
}

/*靈컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
  틇ends message to other 7 people. NOT usrnum.
  튩ARNING: destroys abplyptr and abplypto.
  聃컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 */
VOID absend7(VOID)
{
    INT i;
    for(i=0;i < 4;i++) {            /* send message to all trainees */
       abplyptr=&abintran[i];
       if ((!sameas(abplyptr->id,"\0")) && (abplyptr->channel!=usrnum)) {
            outprf(abplyptr->channel);
       }
    }
    for(i=0;i < 4;i++) {            /* send message to all players  */
       abplyptr=&abinplay[i];
       if ((!sameas(abplyptr->id,"\0")) && (abplyptr->channel!=usrnum)) {
            outprf(abplyptr->channel);
       }
    }
    clrprf();                       /* clear bufer */
    for(i=0;i < 4;i++) {            /* regenerate prompt for all trainees */
       abplyptr=&abintran[i];
       if ((!sameas(abplyptr->id,"\0")) && (abplyptr->channel!=usrnum)) {
            ambrprom(0,abplyptr->channel);
            outprf(abplyptr->channel);
       }
    }
    for(i=0;i < 4;i++) {            /* regenerate prompt for all players  */
       abplyptr=&abinplay[i];
       if ((!sameas(abplyptr->id,"\0")) && (abplyptr->channel!=usrnum)) {
            ambrprom(1,abplyptr->channel);
            outprf(abplyptr->channel);
       }
    }
}

/*靈컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
  튲etermine center prompt character and talk mode.
  튞OTE: abmrget() must be run for this player before calling.
  聃컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 */
INT abtlkm(INT tmode)                        /* 1=playing  0=training */
{
    if ((ambrisit==abturn) && tmode) {   /* it's my turn */
       if (abflags & SILENT) 
             return(abpmode+7);         /* this is a silent game */
       else return(abpmode);             /* this is a freindly game */
    }
    else {
       if (abflags & SILENT) {           /* not my turn */
          if ((abpmode==PREDEAL) || (abpmode==POSTPLAY))
               return(MGOSSIP);          /* silent game, but not dealt */
          else return(MSILENT);          /* silent game, be quiet */
       }
       else return(MGOSSIP);             /* friendly game, gossip ok */
    }
}

/*靈컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
  튲etermine entire prompt for a given player. (in game)
  聃컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 */
VOID ambrprom(INT tmode,INT mynum)
/* 1=playing  0=training */
/* usrnum of player being processed */
{
    ambrget(tmode,mynum);
    prfmsg(NORTH+ambrisit,"\r","");      /* prompt with seat */
    prfmsg(abtlkm(tmode));               /* get and display center chr */
    if (abwtran()) prfmsg(AMBRPRMT);     /* training? */
    prfmsg(AMBRPROM);                    /* final '>' */
}

/*靈컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
  틆eturn to main menu. (display and set substt)
  聃컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 */
VOID ambrmain(VOID) {prfmsg(usrptr->substt=AMBRMAIN);} 

/*靈컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
  튷s a trainer/trainee attached to me? return( true=yes  false=no )
  聃컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 */
INT abwtran(VOID) { return(!sameas(abplypto->id,"\0")); }

/*靈컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
  틇huffle the cards.
  聃컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 */
VOID abshufl(VOID)
{
    INT i,j,k;
    for (i=1;i<ABDKSIZE;i++) {
        j=abdeck[i];
        abdeck[i]=abdeck[k=(rand()%(i+1))];
        abdeck[k]=j;
    }
}
        
/*靈컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
  틊emporary debugging routine to dump various things to the screen **REMOVE**
  聃컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 */
VOID abdump(VOID)
{
prf ("nope");

}

/*靈컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
  튳rase bidding history.
  聃컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 */
VOID abclrbid(VOID)
{
    INT i;
    for(i=0;i<ABMAXBID;abbidrec[i++]=255);     /* clear bidding record */
    abpassno=0;                                /* set number of passes to 0 */
    abbidno=0;                                 /* set pointer to beginning */
    abhibid=0;                                 /* set high bid to 0 */
    abflags&=~(DOUBLED+RDOUBLED);              /* clear dbl and redbl flags */
}

/*靈컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
  튳rases all players' cards.
  聃컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 */
VOID abclrcrd(VOID)
{
   INT i,j,k;
   abdummy=NODUMMY;
   for(i=0;i<4;i++) { 
     abplypto=&abinplay[i];                      /* for each player */
     strcpy(abplypto->card,"    ");              /* clear last card */
     for(k=0;k<4;k++){                           /* for each suit */
        for(j=0;j<13;abplypto->cards[k][j++]=0) ;   /* clear all cards held */
     }
   }
}

/*靈컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
  튰lears the score sheet
  聃컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 */
VOID abclrsc(VOID)
{
  ababoven=0;  ababovee=0;  abgamen=0;  abgamee=0;
  abpartn=0;   abparte=0;   abtotn=0;   abtote=0;
}
/*靈컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
  틊his routine sends a specific message to player (N,S,E,W)
  聃컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 */
VOID absend1(INT seat,INT msg)
{
    abplypto=&abinplay[seat];
    if (!sameas(abplypto->id,"\0"))  {
         prfmsg(msg);
         ambrprom(1,abplypto->channel);
         outprf(abplyptr->channel);
    }
}

/*靈컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
  틊his routine recomputes the silent flag
  聃컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 */
VOID abcksil(VOID)
{
   INT i; LONG j=0;
   for (i=0;i<4;i++) {
     abplypto=&abinplay[i];
     if (!sameas(abplypto->id,"\0")) j|=abplypto->flags;
   }
   abflags=(abflags&~SILENT)|(j&SILENT);
}





/*靈컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
  튝ain menu and seat selection functions.
  聃컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 */
/*靈컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
  튲isplay all player names for seat menu selections.
  틆eturns a count of empty seats for this selection.
  聃컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 */
INT ambrsply(INT tmode)     /* 1=playing  0=training */
{
    INT i;        /* general purpose */
    INT j=0;      /* count of empty player  seats */
    INT k=0;      /* count of empty trainee seats */
    prfmsg(ABHERE);
    for(i=0;i < 4;i++) {
       abplyptr=&abinplay[i];
        if (sameas(abplyptr->id,"\0")) j++ ; /* count empty player seats */
        else {
           prf(" %s (%s)",abplyptr->id,abseatn[i]); /* show full player seats */
        }
    }
    if (j==4) prfmsg(ABNONE);                /* if all player seats empty */
    prfmsg(ABHERET);
    for(i=0;i < 4;i++) {
       abplyptr=&abintran[i];
        if (sameas(abplyptr->id,"\0")) k++ ; /* count empty trainee seats */
        else {
           prf(" %s (%s)",abplyptr->id,abseatn[i]);         /* show full trainee seats */
        }
    }
    if (k==4) prfmsg(ABNONE);                /* if all trainee seats empty */
    if      (tmode==1) return(j);            /* return correct count */
    else if (tmode==0) return(k);
    else               return(j+k);
}

/*靈컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
  튲isplay all empty seats in this area for seat menu selections.
  聃컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 */
VOID ambrsels(INT tmode)      /* 1=playing  0=training */
{
   INT i;       /* general purpose */
   for(i=0;i < 4;i++) {
      if (tmode) abplyptr=&abinplay[i];     /* select player seats */
      else       abplyptr=&abintran[i];     /* select trainee seats */
      if (sameas(abplyptr->id,"\0")) prfmsg(LNORTH+i);
     }
}

/*靈컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
  튰omplete display for seat menu selection.
  聃컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 */
VOID ambrsit(INT tmode)     /* 1=playing  0=training */
{
    if (ambrsply(tmode)) {                     /* show players */
       prfmsg(ABPICK);                         /* ask for selection */
       ambrsels(tmode);                        /* show empty seats */
       prfmsg(usrptr->substt=ABPICK2T+tmode);  /* prompt & set substt */
    }
    else {
       prfmsg(ABTFULL);                        /* area is full, sorry */
       ambrmain();                             /* redisplay menu */
    }
}

/*靈컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
  틄rocess seat menu selection.
  聃컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 */
VOID ambrdsit(INT seat,INT tmode)
       /* seat: 0=N   1=E  2=S   3=W  */
       /* tmode: 1=playing  0=training */
{
     if (tmode) abplyptr=&abinplay[seat];     /* training or playing? */
     else       abplyptr=&abintran[seat];
     if (sameas(abplyptr->id,"\0")) {         /* make sure seat available */
         strcpy(abplyptr->id,usaptr->userid); /* copy name to name field */
         aballptr=&aball[usrnum];             /* get players parameters */
         aballptr->sitting=seat;              /* set seat # in aball */
         ambrget(tmode,usrnum);               /* select structures */
         abplyptr->flags=aballptr->flags;     /* copy flags to flag field */
         abplyptr->channel=usrnum;            /* set my channel */
         abcksil();                           /* recompute the silent flag */
         prfmsg(ABANNPLT,usaptr->userid);     /* tell others who came in */
         prfmsg(LNORTH+seat);
         prfmsg(ABANNP2T+tmode);
         absend7();                           /* send it to others */
/*靈컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
  틁ote: abplyptr and abplypto are undeterined at this point.
  聃컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 */
         prfmsg(ABWELLT,usaptr->userid);      /* welcome player to table */
         prfmsg(LNORTH+seat);
         prfmsg(ABANNP2T+tmode);
         ambrprom(tmode,usrnum);              /* prompt  */   
/*靈컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
  틁ote: abplyptr and abplypto restored now.
  聃컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 */
         usrptr->substt=AMBRPRMT+tmode;       /* set substt */

     }
     else {
        prfmsg(ABONLAP);                      /* sorry that seat is taken */
        ambrsit(tmode);                       /* try again */
     }
}

/*靈컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
  튶ow to play from main menu.
  聃컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 */
VOID ambrhow(VOID)
{ 
    prfmsg(AMBRHOW2);
    ambrmain();
}

/*靈컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
  틇et personal parameters from main menu.
  聃컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 */
VOID ambrparm(VOID)
{
    prfmsg(usrptr->substt=AMBRPERP);  /* prompt & set substt */
    aballptr=&aball[usrnum];
    abdispar();
}

/*靈컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
  튲isplays personal parameters and asks for selection.
  聃컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 */
VOID abdispar(VOID)
{
    prfmsg(AMBRPER3);
    if (aballptr->flags & SILENT) prf("S");
    else prf("G");
    prfmsg(AMBRPER2);
}

/*靈컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
  틄rocess personal parameter setting
  聃컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 */
VOID absetpar(VOID)
{
   aballptr=&aball[usrnum];
   switch(toupper(*margv[0])) {
     case 'S': 
        aballptr->flags |= SILENT;        /* set silent flag */
        abdispar();
        break;
     case 'G':
        aballptr->flags &= ~SILENT;       /* clear silent flag */
        abdispar();
        break;
     case 'X': ambrmain();        break;  /* return to main menu */
     default:  ambrparm();        break;  /* unknown command */
   }
}



/*靈컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
  틊ext processing while at table
  聃컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 */
/*靈컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
  튽eave from table back to main menu.
  聃컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 */
VOID ambrleav(INT tmode)  /* 1=playing  0=training */
{
       ambrget(tmode,usrnum);
       strcpy (abplyptr->id,"\0");       /* set seat to empty */
       abcksil();                        /* recompute silent flag */
       prfmsg(ABANNBYE,usaptr->userid);  /* tell others who left */
       prfmsg(LNORTH+ambrisit);
       prfmsg(ABANNP2T+tmode);
       absend7();                        /* send it to others */
/*靈컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
  틁ote: abplyptr and abplypto are undeterined at this point.
  聃컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 */
         /* if there are no players left, set abpmode=PREPLAY */
       ambrmain();                       /* return to main menu */
}

/*靈컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
  틄rocess text input for player or trainee already seated.
  聃컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 */
VOID ambrproc(INT tmode)    /* 1=playing  0=training */
{
   ambrget(tmode,usrnum);
/*靈컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
  � ********        debugging dump   ********  REMOVE      ********    */
   if (sameas(margv[0],"abdump()")) { abdump(); return; }
/*聃컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 */
   if (margc==0) prfmsg(ABJUSTCR);
   else {
      switch (margv[0][0]) {
         case '+': abwhispr(tmode); break;    /* whisper to traine(e|r) */
         case '?': abhelpme();      break;    /* request for help */
         case '/': abslash(tmode);  break;    /* slash commands */
         case '$': abscdisp();      break;    /* display score */
         default : absndgos(tmode); break;    /* any other command  */
      }
   }
}

/*靈컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
  틇end private message to attached person.
  聃컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 */
VOID abwhispr(INT tmode)     /* 1=playing  0=training */
{
    if (abwtran()) {                                 /* if anyone attached */
        rstrin();
        prfmsg(ABTALKT+tmode,abplyptr->id,margv[0]); /* copy message */
        ambrprom(1-tmode,abplypto->channel);         /* restore his prompt */
/*靈컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
  틁ote: the above prompt restoration exchanges abplyptr and abplypto
  聃컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 */
        outprf(abplyptr->channel);                   /* send it */
        prfmsg(AMBRSNTT);                            /* say it was sent */
    }
    else  prfmsg(ABNOPLAY+tmode);                    /* no one attached */
}

/*靈컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
  튰alled when player types '?'
  聃컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 */
VOID abhelpme(VOID)
{
   prfmsg(AMBRCRON);
}

/*靈컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
  튲isplay the rubber score
  聃컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 */
VOID abscdisp(VOID)
{
    prfmsg(AMBRSHSC,ababoven,ababovee,
           abgamen,abgamee,abpartn,abparte,abtotn,abtote);
}

/*靈컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
  틇end unrecognized text as a gossip
  聃컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 */
VOID absndgos(INT tmode)   /* 1=playing  0=training */
{
   INT i;   /* general purpose */
   if ( ((i=abtlkm(tmode))==MGOSSIP) || (i<=ALTMOD2) ) {
       rstrin();
       prfmsg(ABTALKT+tmode,abplyptr->id,margv[0]); /* copy message */
       absend7();                                   /* send it to everyone */
/*靈컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
  틁ote: abplyptr and abplypto are undeterined at this point.
  聃컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 */
       prfmsg(AMBRSENT);           /* say it was sent */
   }
   else prfmsg(AMBRSHH);           /* say you cant gossip */
}

/*靈컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
  튲ispatch  '/'  commands.
  聃컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 */
VOID abslash(INT tmode)     /* 1=playing  0=training */
{
   if (sameas(margv[0],"/")) prfmsg(ABJUSTCR);   /* just slash...HELP! */
   else {
/*靈컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
  틊his dispatches to a command handler if it is the players turn.
  聃컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 */
      if ((abturn==ambrisit) && (tmode)) {
         switch (abpmode) {
            case PREDEAL:
            case POSTPLAY: abddeler();  break;   /* dealer */
            case BIDDING:  abdbider();  break;   /* bidder */
            case PREPLAY:
            case PLAYING:  abdplyer();  break;   /* my turn to play */
            default:                             /* any invalid state */
                 prfmsg(AMBRDAMN,"Invalid abpmode in abslash"); break;
         }
      }
/*靈컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
  틊hese are the global slash commands.
  聃컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 */
      else {
          switch (toupper(margv[0][1])) {
             case 'T': abslasht();       break;  /* look at table */
             case 'B': abslashb();       break;  /* review bids */
             case 'M': abslashm();       break;  /* look at hand */
             case 'F': abslashf();       break;  /* look at dummy hand */
             default : prfmsg(AMBROOPS); break;  /* any other command  */
          }
      }
   }
}

/*靈컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
  튲ealer command dispatch 
  聃컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 */
VOID abddeler(VOID)
{
   switch (toupper(margv[0][1])) {
       case 'S': abslashs();  break;       /* shuffle */
       case 'D': abslashd();  break;       /* deal */
       case 'T': abslasht();  break;       /* look at table */
       case 'B': abslashb();  break;       /* review bids */
       default : prfmsg(AMBROOPS); break;  /* any other command  */
   }
}

/*靈컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
  튯idder command dispatch
  聃컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 */
VOID abdbider(VOID)
{
   switch (toupper(margv[0][1])) {
       case 'T': abslasht();  break;    /* look at table */
       case 'B': abslashb();  break;    /* review bids */
       case 'M': abslashm();  break;    /* look at hand */
       case 'P': abbidpas();  break;    /* pass */
       case 'D': abbiddbl();  break;    /* double */
       case 'R': abbidrdb();  break;    /* redouble */
       default : abbidsut();  break;    /* any other command or bid */
   }
}

/*靈컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
  틄lay a card dispatch
  聃컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 */
VOID abdplyer(VOID)
{
   switch (toupper(margv[0][1])) {
       case 'T': abslasht();  break;       /* look at table */
       case 'B': abslashb();  break;       /* review bids */
       case 'M': abslashm();  break;       /* look at hand */
       case 'F': abslashf();  break;       /* look at dummy hand */
       default : abplayit();  break;       /* any other command  */
   }
}



/*靈컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
  튵lobal slash commands.
  聃컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 */
/*靈컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
  �/T command process. (look at table)
  聃컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 */
VOID abslasht(VOID)
{
    INT i,j,abturnd;   /* general purpose */
    CHAR *ct,*cl,*cr;  /* cards on table */
    CHAR *abbidtxt();
/*靈컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
  튽ine 1
  聃컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 */
    if (abpmode==PLAYING) abturnd=abturnp;
    else abturnd=abturn;
    prfmsg(ABTL1);
    prfmsg( (i=(ambrisit+2)%4),"(",")");  /* print seat label partner */
    abplypto=&abinplay[i];                /* point to partner */
    ct=abplypto->card;                    /* part's card 4 later disp. */
    if (sameas(abplypto->id,"\0"))
         prf(" No one.   ");              /* if seat is empty */
    else prf(" %-10s",abplypto->id);      /* partner's name */
    prf("%3s",(abturnd==i ? "(*)" : "")); /* partner's turn? */
    abplypto=&abintran[i];                /* point to trainee */
    if (sameas(abplypto->id,"\0")) prf("\n");
    else prf(" [%s]\n",abplypto->id);      
    abplypto=&abinplay[i];                /* point to partner */
    if(abdummy==i) abdumt();              /* if part. is dummy */
/*靈컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
  튽ine 2- and line 2
  聃컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 */
    abplypto=&abintran[i=((ambrisit+1)%4)];  /* point to trainee */
    if (sameas(abplypto->id,"\0")) prfmsg(ABTL2,"");
    else prfmsg(ABTL2,spr("[%s]",abplypto->id));      
    abplypto=&abinplay[i];                /* point to partner */
    prfmsg(i,"(",")");                    /* print seat label left */
    abplypto=&abinplay[i];                /* point to left side player*/
    cl=abplypto->card;                    /* card for later disp. */
    if (sameas(abplypto->id,"\0"))
         prf(" No one.   ");              /* if seat is empty */
    else prf(" %-10s",abplypto->id);      /* left player's name */
    prfmsg(ABTL2A,(abturnd==i ? "(*)" : "   "),ct);   /* his turn? */
    prfmsg( (i=(ambrisit+3)%4),"(",")");  /* print seat label right */
    abplypto=&abinplay[i];                /* point to right side player*/
    cr=abplypto->card;                    /* card for later disp. */
    if (sameas(abplypto->id,"\0"))
        prf(" No one.   ");               /* if seat is empty */
    else prf(" %-10s",abplypto->id);      
    prf("%3s",(abturnd==i ? "(*)" : "")); /* his turn? */
    abplypto=&abintran[i];                /* point to trainee */
    if (sameas(abplypto->id,"\0")) prf("\n");
    else prf(" [%s]\n",abplypto->id);      
    abplypto=&abinplay[i]; 
    if (abdummy!=NODUMMY) abplypto=&abinplay[abdummy];
/*靈컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
  튽ines  3-6
  聃컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 */
    abln356(0,ABTL3A);
    if (abdummy==(ambrisit+1)%4) abduml(1,cl,cr);
    else prfmsg(ABTL4A,cl,cr);
    if (abdummy==(ambrisit+3)%4) abdumr(1);
    else prf("\n");
    abln356(2,ABTL3A);
    abplyptr=&abinplay[ambrisit];                  /* point to PLAYER  */
    if (abdummy==(ambrisit+1)%4) abduml(3,0,0);
    else prfmsg(ABTL6A,abplyptr->card);
    if (abdummy==(ambrisit+3)%4) abdumr(3);
    else prf("\n");
/*靈컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
  튽ine 7 & 8
  聃컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 */
    prfmsg(ABTL7);
    if (abpmode<=PREPLAY) prfmsg(ABTL1);           /* no tricks to show */
    else  prfmsg(ABTL8A);                          /* show tricks */
    prfmsg( (ambrisit),"(",")");                   /* seat label player */
    if (sameas(abplyptr->id,"\0"))
        prf(" No one.   ");                        /* if seat is empty */
    else  prf(" %-10s",abplyptr->id);              /* player's name */
    prf("%3s",(abturnd==ambrisit ? "(*)" : ""));   /* player's turn? */
    abplypto=&abintran[ambrisit];                  /* point to trainee */
    if (sameas(abplypto->id,"\0")) prf("\n");
    else prf(" [%s]\n",abplypto->id);      
    if (abpmode!=PREDEAL) {
       if (abpmode<=PREPLAY) {                     /* display my cards */
          for(j=0;j<4;j++) {
            prfmsg(MYCARDS1+j);
            for (i=12;i>=0;i--) {
                  if (abplyptr->cards[3-j][i])
                      prf(" %s",abcnames[i]);
            }            
          }
       }
       else {                     /* display my cards AND tricks taken */
          if (abflags&RDOUBLED) cl="Rdbl";
          else if (abflags&DOUBLED) cl="Dbl";
          else cl="";
          ct=spr("%s %s",abbidtxt(abhibid),cl);
          for(j=0;j<4;j++) {
            switch (j) {
               case 0: prfmsg(MYCARDT0,abtrickn); break;
               case 1: prfmsg(MYCARDT1,abtricke); break;
               case 2: prfmsg(MYCARDT2,ct);       break;
               case 3: prfmsg(MYCARDC1);          break;
            }
            for (i=12;i>=0;i--) {
                  if (abplyptr->cards[3-j][i])
                      prf(" %s",abcnames[i]);
            }
          }
       }
    }
}

/*靈컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
  틆outines for lines 3 & 5, checks for dummy and prints cards
  聃컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 */
VOID abln356(INT j,INT k)
{
   if (abdummy==(ambrisit+1)%4) abduml(j,0,0);
   else prfmsg(k);
   if (abdummy==(ambrisit+3)%4) abdumr(j);
   else prf("\n");
}

/*靈컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
  틆outine to print dummies cards, if partner is dummy.
  聃컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 */
VOID abdumt(VOID)
{
   INT i,j;
   if (abpmode<=PREPLAY) return;
   for(j=0;j<4;j++) {
       prfmsg(MYCARDS1+j);
       for (i=12;i>=0;i--) {
          if (abplypto->cards[3-j][i]) prf(" %s",abcnames[i]);
       }            
   }
   prf("\n");
}

/*靈컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
  틆outine to print one line dummy to left of player.
  聃컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 */
VOID abduml(INT linptr,CHAR *cl,CHAR *cr)
{
    INT i,j,k=0;
    if (abpmode<=PREPLAY) prfmsg(ABTL1);
    else {
        if ((j=abdumln())!=13 ) {               /* indent from left margin */
            for (i=j;i<13;i++ ) prf("  ");
        }
        prf("%s:",absnames[3-linptr]);          /* print the cards */
        for (i=12;i>=0;i--) {
           if (abplypto->cards[3-linptr][i]) {
                prf(" %s",abcnames[i]);
                k++;
           }
        }
        if (j!=k) {
            for(i=k;i<j;i++) prf("  ");         /* fill to the table */
        }
        if (abplypto->cards[3-linptr][8]==0) prf(" ");
    }
    if      (linptr==1) prfmsg(ABTL4B,cl,cr);
    else if (linptr==3) prfmsg(ABTL6B,abplyptr->card);
    else  prfmsg(ABTL3B);

}

/*靈컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
  틆outine to print one line dummy to right of player.
  聃컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 */
VOID abdumr(INT linptr)
{
    INT i;
    if (abpmode>PREPLAY) {
        prf(" %s:",absnames[3-linptr]);
        for (i=12;i>=0;i--) {
           if (abplypto->cards[3-linptr][i]) prf(" %s",abcnames[i]);
        }
    }
    prf("\n");
}

/*靈컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
  �/B command process. (review bids)
  聃컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 */
VOID abslashb(VOID)
{
  INT i,j;
  CHAR *abbidtxt();
  if (abpmode==PREDEAL) {          /* if there is no bidding to review */
      prfmsg(AMBROOPS);
      return;
  }
  prfmsg(AMBRBID1);                         /* column headers */
  for (i=0;i<4;i++) {                       /* for each player */
     prfmsg( (j=(abdealer+i)%4),"(",")");   /* print seat label */
        abplypto=&abinplay[j];              /* point to player*/
        if (sameas(abplypto->id,"\0"))
             prf(" No one.    ");           /* if seat is empty */
        else prf(" %-11s",abplypto->id);    /* player's name */
  }
  for (i=0,j=0;j==0;i++) {                  /* run through the bid record */
     if (i%4==0) prfmsg(AMBRBID2);          /* return and align first column */
     if (abbidrec[i]==255) {                /* if after last bid */
         if(abpmode<PREPLAY) prf("(*)");    /* indicate his turn */
         j=1;                               /* terminate loop */
     }
     else  prf("%-15s",abbidtxt(abbidrec[i]));  /* display bid and continue */
  }
}

/*靈컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
  �/M command. Look at my hand.
  聃컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 */
VOID abslashm(VOID)
{
   if ((abpmode==PREDEAL)||(abpmode==POSTPLAY)) prfmsg(AMBROOPS);
   else abshowh(ambrisit);
}

/*靈컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
  �/F command. look at dummy.
  聃컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 */
VOID abslashf(VOID)
{
   if ((abpmode<=PREPLAY)||(abpmode==POSTPLAY)) prfmsg(AMBROOPS);
   else abshowh(abdummy); }

/*靈컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
  틇how a given hand.
  聃컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 */
VOID abshowh(INT which)
{
   INT i,j,abturnd;   /* general purpose */
   if (abpmode==PLAYING) abturnd=abturnp;
   else abturnd=abturn;
   abplyptr=&abinplay[which];                  /* point to PLAYER  */
   abplypto=&abintran[which];                  /* point to trainee */
   prfmsg( (which),"(",")");                   /* seat label player */
   if (sameas(abplyptr->id,"\0"))
        prf(" No one.   ");                        /* if seat is empty */
   else  prf(" %-10s",abplyptr->id);              /* player's name */
   prf("%3s",(abturnd==which ? "(*)" : ""));   /* player's turn? */
   if (sameas(abplypto->id,"\0")) prf("\n");
   else prf(" [%s]\n",abplypto->id);      
   if (abpmode!=PREDEAL) {
     for(j=0;j<4;j++) {
        prfmsg(RTCARDS1+j);
        for (i=12;i>=0;i--) {
          if (abplyptr->cards[3-j][i]) prf("%s ",abcnames[i]);
        }
        prf(" ");
     }
   }
}

/*靈컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
  틊his routine counts how many cards are in dummy's longest suit.
  聃컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 */
INT abdumln(VOID)
{
  INT i,j,tot,retval=5;
  for (i=0;i<4;i++) {
    for (j=0,tot=0;j<13;j++) {
       if (abplypto->cards[i][j]) tot++;
    }
    if (tot>retval) retval=tot;
  }
  if (retval<13) retval++;
  return(retval);
}



/*靈컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
  튲ealer command processing.
  聃컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 */
/*靈컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
  �/s command prossessing (shuffle)
  聃컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 */
VOID abslashs(VOID)
{
  abshufl();                      /* give the cards a shuffle */
  prfmsg(ABHESHUF,abplyptr->id);  /* announce that it has been done */
  absend7();                      /* send it to everyone */
  prfmsg(ABUSHUF);                /* confirm back to dealer */
}

/*靈컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
  �/d command   (deal)
  聃컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 */
VOID abslashd(VOID)
{
   INT i,j,k;
   abshufl();                          /* shuffle in case dealer forgot */
   abclrbid();                         /* clear all bids */
   abclrcrd();                         /* clear everyone's cards */
   if (abflags&ABRUBOVR) abclrsc();    /* if new rubber, clear scores */
   abpmode=BIDDING;                    /* transit to bidding mode */
   for(i=0;i<4;i++) {                  /* move cards from deck to hands */
      abplypto=&abinplay[i];           /* point to player */
      for(j=0;j<13;j++) {              /* he gets 13 cards */
         k=abdeck[i+4*j];              /* get card value from deck */
         abplypto->cards[k%4][k/4]=1;  /* set coresponging flag in hand */
      }
   }
   prfmsg(ABHEDEAL,abplyptr->id);      /* announce the deal */
   absend7();                          /* to everyone */
   prfmsg(ABUDDEAL);                   /* confirmation to dealer */
}



/*靈컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
  튯idder command processing.
  聃컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 */
/*靈컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
  틄ass processing.
  聃컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 */
VOID abbidpas(VOID)
{
   abpassno++;                                    /* increment pass counter */
   abstbid(0);                                    /* store the bid */
   if ((abhibid!=0) && (abpassno==3)) abgoplay(); /* 3 passes start play */
   else if (abpassno==4) abgopdl();               /* 4 passes new dealer */
}

/*靈컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
  튒OUBLE processing.
  聃컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 */
VOID abbiddbl(VOID)
{
   if(abhibid==0)      {prfmsg(ABNODPAS); return;} /* no bid to double */
   if(abflags&DOUBLED) {prfmsg(ABNODDBL); return;} /* cant double a bouble */
   if(abpassno==1)     {prfmsg(ABNODPAR); return;} /* can't double partner */
   abstbid(254);                             /* save the bid in the record */
   abpassno=0;                               /* set pass counter to 0 */
   abflags|=DOUBLED;                         /* set dbl flag */
}

/*靈컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
  틆edouble processing.
  聃컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 */
VOID abbidrdb(VOID)
{
   if((abflags&DOUBLED)==0)
                       {prfmsg(ABNORDBL); return;} /* cant redbl till dbl*/
   if(abflags&RDOUBLED)
                       {prfmsg(ABNORRDB); return;} /* cant redbl a rebouble */
   if(abpassno==1)     {prfmsg(ABNORPAR); return;} /* can't redble partner */
   abstbid(253);                             /* save the bid in the record */
   abpassno=0;                               /* set pass counter to 0 */
   abflags|=RDOUBLED;                        /* set redouble flag */
}

/*靈컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
  틇uit (notrump) bids and unknown commands.
  聃컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 */
VOID abbidsut(VOID)
{
   INT numb;
   numb=margv[0][1]-48;                        /* get number value of bid */
   if ( (numb <=7 ) && (numb>=1) ) {           /* is it between 1 and 7 ? */
      switch (toupper(margv[0][2])) {          /* get suit letter */
         case 'C' : abckbid(numb*10);   break; /* if letter is valid check */
         case 'D' : abckbid(numb*10+1); break; /*    to see if the BID is  */
         case 'H' : abckbid(numb*10+2); break; /*    valid. */
         case 'S' : abckbid(numb*10+3); break; /*    if so, process it */
         case 'N' : abckbid(numb*10+4); break;
         default : prfmsg(AMBROOPS);           /* invalid suit */
      }
   }
   else prfmsg(AMBROOPS);   /* invalid number or unknown slash command */
}

/*靈컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
  튰heck bid for validity. (suit or notrump)
  聃컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 */
VOID abckbid(INT bid)
{
   if (bid>abhibid) {            /* make sure bid is higher than previous */
        abhibid=bid;                   /* set new high bid */
        abhibidr=ambrisit;             /* set hi bidder */
        abstbid(bid);                  /* save the bid in the record */
        abpassno=0;                    /* set pass counter to 0 */
        abflags&=~(DOUBLED+RDOUBLED);  /* clear dbl and redbl flags */
   }
   else prfmsg(ABBADBID);              /* bid is too low, try again */
}

/*靈컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
  틇tart play (3 passes after a valid bid)
  聃컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 */
VOID abgoplay(VOID)
{
   INT i;
   CHAR *abbidtxt();
   CHAR *tmpstr;
/*靈컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
  튽ook for first player on team who bid this suit.
  聃컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 */
   for (i=(abhibidr+abdealer)%2;abdummy==NODUMMY;i+=2) {
       if ( ((abbidrec[i]%10)==(abhibid%10)) && (abbidrec[i]!=0) )
               abdummy=(i+abdealer+2)%4;       /* set dummy seat */
   }
   abplypto=&abinplay[(i=(abdummy+2)%4)];          /* announce who is playing */
   tmpstr=spr("%s (%s) will play the bid of %s",   /* and bid level */
                 abplypto->id, abseatn[i],
                 abbidtxt(abhibid)
             );
   prf("\n%s",tmpstr);
   if (abflags&RDOUBLED) prf(" Redoubled.");     /* add doubled or redoubled */
   else if (abflags&DOUBLED) prf(" Doubled.");
   else prf(".");
   outprf(usrnum);                               /* send to usrnum */
   prf("%s",tmpstr);                             /* rebuild message */
   if (abflags&RDOUBLED) prf(" Redoubled.");
   else if (abflags&DOUBLED) prf(" Doubled.");
   else prf(".");
   abpmode=PREPLAY;                              /* set mode to preplay */
   abturnp=(i+1)%4;                              /* determine who's lead */
   abturn=abturnp;
   absuitld=255;                                 /* clear suit led */
   abcplayd=0;                                   /* no cards played yet */
   absend7();                                    /* send to everyone else */
   abtrickn=0;     abtricke=0;                   /* set tricks taken to 0 */
   abschon();                                    /* check for honors */
   ambrget(1,usrnum); // was ambrget(usrnum) - i'm guessing here - RH
   if (abturn==ambrisit) prfmsg(ABULEAD);
   else absend1(abturn,ABULEAD);                 /* tell person who leads */
}

/*靈컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
  튵o to predeal state (hand thrown in)
  聃컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 */
VOID abgopdl(VOID)
{
     abclrbid();                        /* clear the bidding history */
     abpmode=PREDEAL;                   /* set mode to predeal */
     abdealer=(abdealer+1)%4;           /* move to next dealer */
     abturn=abdealer;                   /* indicate it is the dealer's turn */
     abplypto=&abinplay[abdealer];      /* get next dealer's name */
     prfmsg(ALLPASSU,abplypto->id);      /* tell player that all passed */
     outprf(usrnum);                    /* empty buffer */
     prfmsg(ALLPASS,abplypto->id);      /* tell everyone that all passed */
     absend7();                         /* tell others */
     absend1(abturn,ABUDEAL);           /* tell dealer it's his turn */
}

/*靈컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
  틇tore bid in bid record.
  聃컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 */
VOID abstbid(INT bid)
{
   CHAR *tmpstr;
   CHAR *abbidtxt();
   abturn=(abturn+1)%4;            /* increment who's turn it is to bid */
   abbidrec[abbidno]=bid;          /* copy the bid to the record */
   abbidno++;                      /* increment the record pointer */
   tmpstr=abbidtxt(bid);           /* convert the bid to standard text */
   prfmsg(ABHEBIDS,abplyptr->id);  /* announce the bid to others */
   prfmsg(NORTH+ambrisit,"(",")");
   prfmsg(ABHEBID2,tmpstr);
   absend7();                      /* send it to everyone */
   if ( ((abhibid==0) && (abpassno<4)) || (abpassno<3) )
         absend1(abturn,ABUBID);   /* tell who's turn it is */
   prfmsg(ABYOUBID,tmpstr);        /* confirm bid back to bidder */
}

/*靈컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
  튰onvert numeric bid to text string.
  聃컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 */
CHAR *abbidtxt(INT bid)
{
   switch (bid) {
     case 0:   return("Pass");      
     case 254: return("DOUBLE");
     case 253: return("Redouble");
     default:
        return( spr("%d %s%s",bid/10,absnamel[bid%10],
                    ((((bid/10)>1) && ((bid%10)!=4)) ? "s\0" : "\0" )
                )
        );
   }
}


/*靈컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
  틄lay a card comand processing.
  聃컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 */
VOID abplayit(VOID)
{
   INT numb;
   switch(toupper(margv[0][2])) {
       case 'A': numb=12; break;            /* card values for face cards */
       case 'K': numb=11; break;
       case 'Q': numb=10; break;
       case 'J': numb= 9; break;
       case '0':
       case '1': numb= 8; break;               /* card value for 10 */
       default : if ( (margv[0][2]>49) && (margv[0][2]<58))
                      numb=margv[0][2]-50;     /* card values for spots */
                 else numb=13;
   }
   if ( (numb <=12 ) && (numb>=0) ) {          /* valid card value? */
      switch (toupper(margv[0][1])) {          /* get suit letter */
         case 'C' : abckply(numb,0); break;    /* if letter is valid check */
         case 'D' : abckply(numb,1); break;    /* to see if the card is  */
         case 'H' : abckply(numb,2); break;    /* valid. */
         case 'S' : abckply(numb,3); break;    /* if so, process it */
         default : prfmsg(AMBROOPS);           /* invalid suit */
      }
   }
   else prfmsg(AMBROOPS);   /* invalid number or unknown slash command */
}

VOID abckply(INT value,INT suit)
{
   INT i;
   abplyptr=&abinplay[abturnp];                /* set pointer to hand */
   if ((absuitld<255) && (suit!=absuitld)) {   /* check for renig */
      for(i=0;i<13;i++) {
          if (abplyptr->cards[absuitld][i]) {  
              prfmsg(NORENIG);
              return;
          }
      }
   }
   if (abplyptr->cards[suit][value]) {
        abplyptr->cards[suit][value]=0;         /* remove card from hand */
        if (absuitld==255) {
            absuitld=suit;                      /* determine suit led */
            for(i=0;i<4;i++) {                  /* clear cards played */
               abplypto=&abinplay[i];
               strcpy(abplypto->card,"    ");
            }
        }
        strcpy (abplyptr->card,spr("%s-%-2s",
                absnames[suit],abcnames[value])); /* card played display */
        abplyptr->cardv=10*value+suit;
        if (abpmode==PREPLAY) abpmode=PLAYING;    /* enter playing state */
        abplyptr=&abinplay[abturn];               /* point to next player */
/*靈컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
  튮nnonce card played.
  聃컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 */
        if (abturnp==abdummy) {            /* if played from dummy */
            prfmsg(ABUUDPLY,absnamel[suit],abcnamel[value]);
            outprf(usrnum);
            prfmsg(ABDNNPLY,abplyptr->id,absnamel[suit],abcnamel[value]);
            absend7();
        }
        else {                             /* if played from own hand */
            prfmsg(ABUUPLY,absnamel[suit],abcnamel[value]);
            outprf(usrnum);
            prfmsg(ABANNPLY,abplyptr->id,absnamel[suit],abcnamel[value]);
            absend7();
        }
        if (++abcplayd==4) abhostrk();            /* who won trick? */
/*靈컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
  틇et up for next player.
  聃컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 */
        else {
           abturnp=(abturnp+1)%4;        /* determine hand */
           if (abturnp==abdummy) {       /* if dummy */
                abturn=(abturnp+2)%4;
                absend1(abturn,ABUDPLAY);
           }
           else {                        /* not dummy */
                abturn=abturnp;
                absend1(abturn,ABUPLAY);
           }
        }
   }
   else prfmsg(ABNOCARD);   /* you don't hold that card */
}

/*靈컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
  틎ho took the trick? set up for next trick.
  聃컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 */
VOID abhostrk(VOID)
{
  INT i,j,hicard=-1,hicardby=-1;
  CHAR *tmpstr;
  for (i=0;i<4;i++) {                   /* look for high trump */
      abplypto=&abinplay[i];
      if (((j=abplypto->cardv)%10==abhibid%10) && (j>hicard)) {
             hicard=j;
             hicardby=i;
      }
  }
  if (hicard<0) {                       /* look for highest of led suit */
     for (i=0;i<4;i++) {
         abplypto=&abinplay[i];
         if (((j=abplypto->cardv)%10==absuitld) && (j>hicard)) {
                hicard=j;
                hicardby=i;
         }
     }
  }
  if ((hicardby != -1) && (hicardby%2))  abtricke++;         /* increment tricks taken by team */
  else abtrickn++;
  abcplayd=0;                          /* clear trick from memory */
  absuitld=255;
  abturnp=hicardby;                    /* who's turn now? */
/*靈컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
  튮nnounce who took trick.
  聃컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 */
  if (hicardby==abdummy) {
      i=(hicardby+2)%4;
      tmpstr=", in dummy.";
  }
  else {
      i=hicardby;
      tmpstr=".";
  }
  abplypto=&abinplay[i];
  prfmsg(ABHETOOK,abplypto->id,abseatn[i],tmpstr);
  outprf(usrnum);
  absend7();
/*靈컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
  튰heck for end of hand.
  聃컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 */
  if ((abtrickn+abtricke)==13) {
    abscupd();                      /* anoounce scoring and update it */
/*靈컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
  튲etermine next dealer
  聃컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 */
    abdealer=(abdealer+1)%4;        /* determine dealer */
    abturn=abdealer;                /* set turn to dealer */
    abpmode=POSTPLAY;               /* set mode */
    abclrbid();                     /* clear bidding history */
/*靈컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
  틇ay its his deal.
  聃컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 */
    abplypto=&abinplay[abdealer];   
    prfmsg(ABNXTDLR,abplypto->id,abseatn[abdealer]);
    outprf(usrnum);
    absend7();
  }
  else {
/*靈컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
  튶and is not over, set up for next trick.
  聃컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 */
    ambrget(1,usrnum);
    if (abturnp==abdummy) {            /* determine player from seat */
        abturn=(abturnp+2)%4;          /* player is dummy's partner */
        if (abturn!=ambrisit) {
             absend1(abturn,ABUDLEAD);
        }
        else prfmsg(ABUDLEAM);         /* tell him to lead */
    }
    else {
        abturn=abturnp;                /* player is hand */
        if (abturn!=ambrisit) {
             absend1(abturn,ABULEAD);
        }
        else prfmsg(ABULEAM);          /* tell him to lead */
    }
  }
}

/*靈컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
  튰heck for 100 or 150 honors (both teams)
  聃컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 */
VOID abschon(VOID)
{
   abhonorn=abscho1(NORTH)+abscho1(SOUTH);
   abhonore=abscho1(EAST) +abscho1(WEST);
}

/*靈컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
  튰heck for 100 or 150 honors (hand)
  聃컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 */
INT abscho1(INT seat)
{
   INT i,j,k=0;
   abplypto=&abinplay[seat] ;           /* point to hand being checked */
   if ((j=abhibid%10)<4) {              /* check for suit honors */
      for(i=8;i<13;i++) {
        if (abplypto->cards[j][i]) k++; /* count honors */
      }
      if (k==4) return(100);
      if (k==5) return(150);
   }
   else {                     /* check for no trump honors */
      for(i=0;i<4;i++) {
        if (abplypto->cards[i][12]) k++; /* count aces */
      }
      if (k==4) return(150);
   }
   return(0);
}

/*靈컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
  틌pdate scorepad at end of hand
  聃컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 */
VOID abscupd(VOID)
{
     INT trbid,subid,ptsc,otworth,insult=0,trtaken,bidvuln;
     ababoven=ababoven+abhonorn;                /* add in honors bonus */
     ababovee=ababovee+abhonore;
     if (abhonorn) prfmsg(ABANNHON,"N-S",abhonorn);
     if (abhonore) prfmsg(ABANNHON,"E-W",abhonore);
     if (abdummy%2) {
          trtaken=abtricke;
          bidvuln=(abflags&EWVULN)?1:0;//bidvuln=abflags&EWVULN;
     }
     else {
          trtaken=abtrickn;
          bidvuln=(abflags&NSVULN)?1:0; //bidvuln=abflags&NSVULN;
     }
/*靈컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
  틇ee if contract was made.
  聃컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 */
     if (trtaken>=((trbid=abhibid/10)+6)){                  /* contract made */
        if ((subid=abhibid%10)<=1) ptsc=(otworth=20)*trbid; /* c or d */
        else if (subid<=3)         ptsc=(otworth=30)*trbid; /* h or s */
        else                ptsc=(otworth=30)*(trbid-1)+40; /* notrump */
        if (abflags&DOUBLED)                   /* adj values for dbl&rdbl */
                  {  insult=50; ptsc+=ptsc;  otworth=100; }
        if (abflags&RDOUBLED) { ptsc+=ptsc;  otworth=200; }
        if (abdummy%2) {                                    /* EW declarer */
           abparte+=ptsc;
           prfmsg(ABMADEIT,"E-W",abbidtxt(abhibid));
        }
        else {                                              /* NS declarer */
           abpartn+=ptsc;
           prfmsg(ABMADEIT,"N-S",abbidtxt(abhibid));
        }
        if     (abflags&RDOUBLED) prf(" Redoubled,");
        else if (abflags&DOUBLED) prf(" Doubled,");
        else prf(",");
        prfmsg(ABMADE2,ptsc);
        abplypto=&abinplay[(abdummy+2)%4];   
        prfmsg(ABWELP+trtaken-trbid-6,abplypto->id);
/*靈컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
  틃vertricks
  聃컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 */
         if (trtaken>(trbid+6)) {
           if (abdummy%2) {
               if ((abflags&DOUBLED)&&(bidvuln!=0)) otworth+=otworth;
               ptsc=otworth*(trtaken-trbid-6);
               ababovee+=ptsc;
           }
           else {
               if ((abflags&DOUBLED)&&(bidvuln!=0)) otworth+=otworth;
               ptsc=otworth*(trtaken-trbid-6);
               ababoven+=ptsc;
           }  
           prfmsg(ABOVER,trtaken-trbid-6,ptsc);
        }
/*靈컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
  틇lam and insult
  聃컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 */
        ptsc=0;
        if (trbid==6) {
          if (bidvuln)  ptsc=750;
          else ptsc=500;
          prfmsg(ABSSLAM,ptsc);
        }
        if (trbid==7) {
          if (bidvuln)  ptsc=1500;
          else ptsc=750;
          prfmsg(ABGSLAM,ptsc);
        }
        if (insult) prfmsg(INSULTM);
        if (abdummy%2) ababovee+=ptsc+insult;
        else           ababoven+=ptsc+insult;
     }
/*靈컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
  틇et
  聃컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 */
     else {
        if(bidvuln) {
           if    (abflags&RDOUBLED) { ptsc=400; otworth=600;}
           else if(abflags&DOUBLED) { ptsc=200; otworth=300;}
           else                     { ptsc=100; otworth=100;}
        }
        else {
           if    (abflags&RDOUBLED) { ptsc=200; otworth=400;}
           else if(abflags&DOUBLED) { ptsc=100; otworth=200;}
           else                     { ptsc= 50; otworth= 50;}
        }
        ptsc+=otworth*(5+trbid-trtaken);
        if (abdummy%2) {                                    /* EW declarer */
           ababoven+=ptsc;
           prfmsg(ABWASSET,"E-W",6+trbid-trtaken,
                      abbidtxt(abhibid),"N-S",ptsc);
        }
        else {                                              /* NS declarer */
           ababovee+=ptsc;
           prfmsg(ABWASSET,"N-S",6+trbid-trtaken,
                      abbidtxt(abhibid),"E-W",ptsc);
        }
     }
/*靈컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
  튰heck for game.
  聃컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 */
     if (abpartn>=100) {
         ababoven+=abpartn-100;
         ababovee+=abparte;
         prfmsg(ABTKGAME,"N-S");
         abgamen++;
         abpartn=0;
         abparte=0;
     }
     if (abparte>=100) {
         ababoven+=abpartn;
         ababovee+=abparte-100;
         prfmsg(ABTKGAME,"E-W");
         abgamee++;
         abpartn=0;
         abparte=0;
     }
/*靈컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
  튰ompute totals
  聃컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 */
     abtote=ababovee+abparte+100*abgamee;
     abtotn=ababoven+abpartn+100*abgamen;
     if (abgamen!=abgamee) {
         if      (abgamen-abgamee==2) {    ptsc=700; abflags|=ABRUBOVR; }
         else if (abgamee-abgamen==2) {    ptsc=700; abflags|=ABRUBOVR; }
         else if ((abgamen) && (abgamee))  ptsc=500;
         else                              ptsc=300;
         if (abgamen>abgamee)      abtotn+=ptsc;
         else                      abtote+=ptsc;
     }
     if (abflags&ABRUBOVR) prfmsg(ABENDRUB,abtotn,abtote);
     else                  prfmsg(ABSCSUMR,abtotn,abtote);
/*靈컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
  틃utput summary
  聃컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 */
     prf ("\n");
     outprf(usrnum);
     absend7();

}

