/*****************************************************************/
/*                                                               */
/*   CASIO fx-9860G SDK Library                                  */
/*                                                               */
/*   File name : [ProjectName].c                                 */
/*                                                               */
/*   Copyright (c) 2006 CASIO COMPUTER CO., LTD.                 */
/*                                                               */
/*****************************************************************/
#include "fxlib.h"
#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "string.h"

char nm[6];                                                	//stored in data file
char str[100];
unsigned short Level, AP, DP, status;              	//stored in bst
unsigned int Coin, Star;                                 	//stored in CoinS
unsigned char Place, Stage;                     	//stored in data file
char  x_axis, y_axis;                               	//stored in data file
unsigned short password;                        	//stored in data file
double HP, MHP;                                   	 	//stored in data file
unsigned int bst, CoinS;                                	//stored in data file
int EXP;                                                    	//stored in data file
unsigned short oldskill[8];                            	//stored in olddata file
unsigned char skill[8];                               	//stored in data file
unsigned char item[14], event[31];           	//stored in data file
unsigned char quest[2];                                	//stored in data file
unsigned char user[2];                                	//stored in data file
unsigned int uwin;
int handle;
int test;
unsigned int key;
int block;
int quit;
unsigned int dno;
unsigned int effitem;
FONTCHARACTER path[]={'\\','\\','f','l','s','0','\\','5','P','S',0};
FONTCHARACTER file[]={'\\','\\','f','l','s','0','\\','5','P','S','\\','D','A','T','0','0','.','e','x','t',0};
unsigned int WrtDat[]={0x401C0000,0x00000000,0x401E0000,0x00000000,0x00002710,0,0x00003D28,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
DISPBOX udisp={0,0,127,15};
DISPBOX sdisp={1,17,126,23};
DISPBOX cdisp={8,9,120,45};
unsigned int work;
int rank[200];
const int HPI[]={5,20,75,250,800,2400,6500,16000,36000,70000,120000,180000};
const char *Iname[40]={"PsnHeal","GsdHeal","ShvHeal","BrnHeal","ParHeal","SrkHeal","?-TypeA","?-TypeB","49","50","MdSport","Soda","AllorN40","Unknown1","Unknown2","Unknown3"};
const int IP[]={1000,400,1500,2000,3000,5000,10000,20000,0,0,300,400,500,713,651,848};
const int gsp[]={400,700,1000,1300,1700,2100,2500,2900,3400,3900,4400,4900,5500,6100,6700,7300,8000,8700,9400,10100,10900,11700,12500,13300,14200,15100,16000,16900,17900,19000,0};
const int cmp[]={800,1600,3200,6400,9600,12800,19200,25600,32000,38400,44800,51200,57600,64000,70400,76800,83200,89600,96000,102400,108800,115200,121600,128000,134400,140800,147200,153600,160000,170000,0};
const int dzp[]={200,400,600,800,1000,1300,1600,1900,2200,2600,3000,3400,3800,4300,4800,5300,5800,6400,7000,7600,8200,8900,9600,10300,11000,11800,12600,13400,14200,15500,0};
double dam;

int MEXP(int Lv)
{
    return (3*Lv*Lv*Lv+7*Lv*Lv+58*Lv+32)/2;
}

double SpDam(int A,int D)
{
    double result;
    if(D<0) result=(A*pow(1.01,A))-D;
    else result=(A*pow(1.01,A)-D)/pow(1.011,D);
    if(result<0.1*A) result=0.1*A;
    return result;
}

double Damage(int A, int D)
{
    double result;
    if(D<0) result=(A*pow(1.05,A))-D;
    else result=(A*pow(1.05,A)-D)/pow(1.05,D);
    if(result<.04*A) result=.04*A;
    return result;
}

unsigned int criRat(int Lv)
{
    int result=0;
    if(Lv>0) result++;
    if(Lv>=15) result++;
    if(Lv>=30) result++;
    if(Lv>=50) result++;
    if(Lv>=80) result++;
    if(Lv>=120) result++;
    if(Lv>=170) result++;
    if(Lv>=230) result++;
    if(Lv>=300) result++;
    if(Lv>=375) result++;
    if(Lv==400) result+=5;
    if(dno==99) result*=4;
    return result;
}

unsigned int criDam(int Lv)
{
    int result=0;
    if(Lv>0) result+=100;
    if(Lv>=20) result+=50;
    if(Lv>=40) result+=50;
    if(Lv>=65) result+=50;
    if(Lv>=110) result+=50;
    if(Lv>=165) result+=50;
    if(Lv>=225) result+=50;
    if(Lv>=290) result+=50;
    if(Lv>=350) result+=50;
    if(Lv==400) result+=200;
    return result;
}

unsigned int SkLv(int Lv, int no)
{
    unsigned int result;
    if(no==0)
        result=(Lv>0)+(Lv>=24)+(Lv>=56)+(Lv>=95)+(Lv>=157)+(Lv>=232)+(Lv>=320);
    if(no==1)
        result=(Lv>=5)+(Lv>=25)+(Lv>=53)+(Lv>=88)+(Lv>=144)+(Lv>=213)+(Lv>=296);
    if(no==2)
        result=(Lv>=12)+(Lv>=43)+(Lv>=82)+(Lv>=133)+(Lv>=215)+(Lv>=316)+(Lv==400);
    if(no==3)
        result=(Lv>=16)+(Lv>=32)+(Lv>=54)+(Lv>=83)+(Lv>=130)+(Lv>=196)+(Lv>=273)+(Lv>=400);
    return result+skill[no]/50;
}
unsigned int SkSt(int Lv,int no)
{
    unsigned int result;
    if(no==0)
        result=(Lv>0)+(Lv>=8)+(Lv>=24)+(Lv>=34)+(Lv>=56)+(Lv>=68)+(Lv>=95)+(Lv>=109)+(Lv>=124)+(Lv>=157)+(Lv>=174)+(Lv>=192)+(Lv>=232)+(Lv>=252)+(Lv>=273)+(Lv>=320)+(Lv>=344)+(Lv>=370)+(Lv==400);
    if(no==1)
        result=(Lv>=5)+(Lv>=10)+(Lv>=25)+(Lv>=33)+(Lv>=53)+(Lv>=63)+(Lv>=88)+(Lv>=100)+(Lv>=113)+(Lv>=144)+(Lv>=159)+(Lv>=175)+(Lv>=213)+(Lv>=231)+(Lv>=251)+(Lv>=296)+(Lv>=319)+(Lv>=344)+(Lv>=371)+(Lv==400);
    if(no==2)
        result=(Lv>=12)+(Lv>=23)+(Lv>=43)+(Lv>=55)+(Lv>=82)+(Lv>=97)+(Lv>=133)+(Lv>=150)+(Lv>=169)+(Lv>=215)+(Lv>=236)+(Lv>=259)+(Lv>=316)+(Lv>=342)+(Lv>=370);
    if(no==3)
        result=(Lv>=16)+(Lv>=20)+(Lv>=32)+(Lv>=38)+(Lv>=54)+(Lv>=62)+(Lv>=83)+(Lv>=93)+(Lv>=104)+(Lv>=130)+(Lv>=147)+(Lv>=162)+(Lv>=196)+(Lv>=213)+(Lv>=231)+(Lv>=273)+(Lv>=295)+(Lv>=319)+(Lv>=345)+(Lv>=400);
    return result+skill[no]%50;
}
unsigned int Speed()
{
    return AP+2*DP;
}

void loadOldDat(int num, int opentype)
{
    file[14]=num/10+'0';
    file[15]=num%10+'0';
    handle=Bfile_OpenFile(file,_OPENMODE_READ);
    if(handle<0)
    {
        Bfile_CreateFile(file,96);
        handle=Bfile_OpenFile(file,_OPENMODE_READWRITE);
        Bfile_SeekFile(handle,0);
        Bfile_WriteFile(handle,WrtDat,96);
    }
    Bfile_ReadFile(handle,&bst,4,16);
    Level=bst/10000000;
    Bfile_ReadFile(handle,&EXP,4,20);
    Bfile_ReadFile(handle,&Stage,2,26);
    if(opentype==0)
    {
        AP=(bst%10000000)/10000;
        DP=(bst%10000)/10;
        status=bst%10;
        Bfile_ReadFile(handle,&HP,8,0);
        Bfile_ReadFile(handle,&MHP,8,8);
        Bfile_ReadFile(handle,&Place,2,24);
        Bfile_ReadFile(handle,&y_axis,1,28);
        Bfile_ReadFile(handle,&x_axis,1,29);
        Bfile_ReadFile(handle,&CoinS,4,30);
        Coin=CoinS%16777216;
        Star=CoinS>>24;
        Bfile_ReadFile(handle,&password,2,34);
        Bfile_ReadFile(handle,oldskill,16,36);
        Bfile_ReadFile(handle,item,10,52);
        Bfile_ReadFile(handle,event,31,64);
    }
    Bfile_CloseFile(handle);
}
void loadDat(int num, int opentype)
{
    file[14]=num/10+'0';
    file[15]=num%10+'0';
    handle=Bfile_OpenFile(file,_OPENMODE_READ);
    if(handle<0)
    {
        Bfile_CreateFile(file,96);
        handle=Bfile_OpenFile(file,_OPENMODE_READWRITE);
        Bfile_SeekFile(handle,0);
        Bfile_WriteFile(handle,WrtDat,96);
    }
    Bfile_ReadFile(handle,&bst,4,16);
    Level=bst/10000000;
    Bfile_ReadFile(handle,&EXP,4,20);
    Bfile_ReadFile(handle,&Stage,1,25);
    Bfile_ReadFile(handle,nm,5,91);
    nm[5]=0;
    if(opentype==0)
    {
        AP=(bst%10000000)/10000;
        DP=(bst%10000)/10;
        status=bst%10;
        Bfile_ReadFile(handle,&HP,8,0);
        Bfile_ReadFile(handle,&MHP,8,8);
        Bfile_ReadFile(handle,&Place,1,24);
        Bfile_ReadFile(handle,&x_axis,1,26);
        Bfile_ReadFile(handle,&y_axis,1,27);
        Bfile_ReadFile(handle,&CoinS,4,28);
        Coin=CoinS%16777216;
        Star=CoinS>>24;
        Bfile_ReadFile(handle,&password,2,32);
        Bfile_ReadFile(handle,skill,8,34);
        Bfile_ReadFile(handle,item,14,42);
        Bfile_ReadFile(handle,event,31,56);
        Bfile_ReadFile(handle,quest,2,87);
        Bfile_ReadFile(handle,user,2,89);
    }
    Bfile_CloseFile(handle);
}

void saveDat(int num)
{
    int i,j,t;
    file[14]=num/10+'0';
    file[15]=num%10+'0';
    Bfile_DeleteFile(file);
    Bfile_CreateFile(file,96);
    handle=Bfile_OpenFile(file,_OPENMODE_WRITE);
    Bfile_SeekFile(handle,0);
    Bfile_WriteFile(handle,&HP,8);
    Bfile_WriteFile(handle,&MHP,8);
    bst=Level*10000000+AP*10000+DP*10+status;
    Bfile_WriteFile(handle,&bst,4);
    Bfile_WriteFile(handle,&EXP,4);
    bst=(Place<<24)+(Stage<<16)+(x_axis<<8)+y_axis;
    Bfile_WriteFile(handle,&bst,4);
    CoinS=Coin+(Star<<24);
    Bfile_WriteFile(handle,&CoinS,4);
    Bfile_WriteFile(handle,&password,2);
    for(i=0;i<8;i++)
        str[i]=skill[i];
    for(i=0;i<14;i++)
        str[i+8]=item[i];
    for(i=0;i<31;i++)
        str[i+22]=event[i];
    for(i=0;i<2;i++)
    {
        str[i+53]=quest[i];
        str[i+55]=user[i];
    }
    for(i=0;i<5;i++)
        str[i+57]=nm[i];
    Bfile_WriteFile(handle,str,62);
    Bfile_CloseFile(handle);
}
void updateDat(int num)
{
    loadOldDat(num,0);
    item[10]=item[11]=item[12]=item[13]=0;
    quest[0]=quest[1]=0;
    user[0]=user[1]=0;
    nm[0]=nm[1]=nm[2]=nm[3]=nm[4]=0;
    saveDat(num);
}

int drawUwin(int num)
{
    int i,j,t;
    Bdisp_AreaClr_VRAM(&udisp);
    Bdisp_AreaClr_VRAM(&sdisp);
    if(num!=1) PrintMini(7,18,(unsigned char*)"F1",MINI_OVER);
    else
    {
        PrintMini(2,18,(unsigned char*)"Level",MINI_OVER);
        sprintf(str,"Lv%3u %c.",Level,0x1E);
        PrintXY(0,0,(unsigned char*)str,0);
        if(EXP<=999999 && EXP>=-99999)
            sprintf(str,"%6d/",EXP);
        else
            sprintf(str,"%5dk/",EXP/1000);
        PrintXY(48,0,(unsigned char*)str,0);
        if(MEXP(Level)<=999999)
            sprintf(str,"%6u",MEXP(Level));
        else
            sprintf(str,"%5uk",MEXP(Level)/1000);
        PrintXY(90,0,(unsigned char*)str,0);
        sprintf(str,"Place %-3u  Stage %-3u",Place,Stage);
        PrintXY(0,8,(unsigned char*)str,0);
    }
    if(num!=2) PrintMini(num>1?28:29,18,(unsigned char*)"F2",MINI_OVER);
    else
    {
        PrintMini(23,18,(unsigned char*)"BStat",MINI_OVER);
        sprintf(str,"HP  %6u/%6u",(unsigned int)HP,(unsigned int)MHP);
        PrintXY(12,0,(unsigned char*)str,0);
        sprintf(str,"A:%-3u D:%-3u S:%u",AP,DP,Speed());
        PrintXY(12,8,(unsigned char*)str,0);
    }
    if(num!=3) PrintMini(num>2?49:50,18,(unsigned char*)"F3",MINI_OVER);
    else
    {
        PrintMini(45,18,(unsigned char*)"Mony",MINI_OVER);
        sprintf(str,"Coin   %7u",Coin);
        PrintXY(21,0,(unsigned char*)str,0);
        sprintf(str,"Star       %3u",Star);
        PrintXY(21,8,(unsigned char*)str,0);
    }
    if(num!=4) PrintMini(num>3?70:71,18,(unsigned char*)"F4",MINI_OVER);
    else
    {
        PrintMini(67,18,(unsigned char*)"Stat",MINI_OVER);
        if(status==0)
        {
            PrintXY(21,0,(unsigned char*)"Status: Normal",0);
        }
        else if(status==1 || status==2)
        {
            PrintXY(21,0,(unsigned char*)"Status: Poison",0);
            PrintXY(30,8,(unsigned char*)"Rest / Item",0);
        }
        else if(status==3)
        {
            PrintXY(21,0,(unsigned char*)"Status: Grassd",0);
            PrintXY(42,8,(unsigned char*)"RECOVER",0);
        }
        else if(status==4)
        {
            PrintXY(21,0,(unsigned char*)"Status: Shiver",0);
            PrintXY(30,8,(unsigned char*)"Rest / Item",0);
        }
        else if(status==5)
        {
            PrintXY(21,0,(unsigned char*)"Status:   Burn",0);
            PrintXY(51,8,(unsigned char*)"Item",0);
        }
        else if(status==6)
        {
            PrintXY(21,0,(unsigned char*)"Status: Paralz",0);
            PrintXY(30,8,(unsigned char*)"Rest / Item",0);
        }
        else if(status==7)
        {
            PrintXY(21,0,(unsigned char*)"Status: Shrink",0);
            PrintXY(51,8,(unsigned char*)"Item",0);
        }
        else
        {
            PrintXY(21,0,(unsigned char*)"Status:    ???",0);
            PrintXY(42,8,(unsigned char*)"Unknown",0);
        }
    }
    if(num!=5) PrintMini(num>4?91:92,18,(unsigned char*)"F5",MINI_OVER);
    else
    {
        PrintMini(85,18,(unsigned char*)"Quest",MINI_OVER);
        PrintXY(9,4,(unsigned char*)"No Quest available",0);
    }
    if(num!=6) PrintMini(num>5?112:113,18,(unsigned char*)"F6",MINI_OVER);
    else
    {
        if(user==0) 0;
        PrintMini(109,18,(unsigned char*)"User",MINI_OVER);
    }
    Bdisp_AreaReverseVRAM(21*num-20,17,21*num,23);

    for(i=1;i<num;i++)
        Bdisp_DrawLineVRAM(21*i,16,21*i,24);
    for(i=num;i<6;i++)
        Bdisp_DrawLineVRAM(21*i+1,16,21*i+1,24);

    Bdisp_PutDisp_DD();

    return 0;
}

void Refresh()
{
    if(HP>=1)
    {
        Bdisp_AllClr_VRAM();
        if(Place%4==0)
        {
            PrintXY(20,25,(unsigned char*)"Shop",0);
            PrintXY(83,25,(unsigned char*)"Star",0);
            PrintXY(20,56,(unsigned char*)"Rest",0);
            PrintXY(83,56,(unsigned char*)"Tell",0);
            Bdisp_DrawLineVRAM(19,24,19,33);
            Bdisp_DrawLineVRAM(19,33,45,33);
            Bdisp_DrawLineVRAM(45,24,45,33);
            Bdisp_DrawLineVRAM(82,24,82,33);
            Bdisp_DrawLineVRAM(82,33,108,33);
            Bdisp_DrawLineVRAM(108,24,108,33);
            Bdisp_DrawLineVRAM(19,54,19,63);
            Bdisp_DrawLineVRAM(19,54,45,54);
            Bdisp_DrawLineVRAM(45,54,45,63);
            Bdisp_DrawLineVRAM(82,54,82,63);
            Bdisp_DrawLineVRAM(82,54,108,54);
            Bdisp_DrawLineVRAM(108,54,108,63);
        }
        else
        {
            if(Stage<=Place)
            {
                PrintXY(61,40,(unsigned char*)"Z",0);
                if(Place==55) PrintXY(61,40,(unsigned char*)"?",0);
            }
            if(Place%4==3 && Stage-1<=Place) PrintXY(109,25,(unsigned char*)"B",0);
        }
        Bdisp_DrawLineVRAM(0,16,127,16);
        Bdisp_DrawLineVRAM(0,24,127,24);
        Bdisp_DrawLineVRAM(0,16,0,63);
        Bdisp_DrawLineVRAM(127,16,127,63);
        Bdisp_DrawLineVRAM(0,63,127,63);
        drawUwin(uwin);
    }
    else
    {
        Bdisp_AllClr_DDVRAM();
        PrintXY(36,28,(unsigned char*)"GAME OVER",0);
        Bdisp_PutDisp_DD();
        Sleep(1500);
    }
}

void LevelUp()
{
    int i,j,t;
    int temp;
    int sel=0;
    double dtemp;
    Bdisp_AllClr_DDVRAM();
    Level++;
    if(Level!=400)
    {
        PrintXY(36,8,(unsigned char*)"Level Up!",0);
        sprintf(str,"%c%cAP: %3u",0xE6,0x9B,AP);
        PrintXY(37,24,(unsigned char*)str,0);
        sprintf(str,"DP: %3u",DP);
        PrintXY(43,32,(unsigned char*)str,0);
        PrintXY(0,48,(unsigned char*)"Select A/DP for bonus",0);
        Bdisp_PutDisp_DD();
        while(IsKeyDown(KEY_CTRL_EXE))
        {
            Sleep(50);
        }
        i=0;
        while(IsKeyUp(KEY_CTRL_EXE) || i<20)
        {
            i++;
            Sleep(50);
            if(IsKeyDown(KEY_CTRL_UP) && sel==1)
            {
                sel=0;
                PrintXY(37,32,(unsigned char*)" ",0);
                sprintf(str,"%c%c",0xE6,0x9B);
                PrintXY(37,24,(unsigned char*)str,0);
                Bdisp_PutDisp_DD();
            }
            if(IsKeyDown(KEY_CTRL_DOWN) && sel==0)
            {
                sel=1;
                PrintXY(37,24,(unsigned char*)" ",0);
                sprintf(str,"%c%c",0xE6,0x9B);
                PrintXY(37,32,(unsigned char*)str,0);
                Bdisp_PutDisp_DD();
            }
        }
    }
    else
    {
        sel=2;
        PopUpWin(3);
        PrintXY(30,20,(unsigned char*)"You reached",0);
        PrintXY(30,28,(unsigned char*)"final level.",0);
        Bdisp_PutDisp_DD();
        for(i=0;i<10;i++)
        {
            if(IsKeyUp(KEY_CTRL_EXE)) break;
            Sleep(50);
        }
        while(IsKeyUp(KEY_CTRL_EXE))
        {
            Sleep(50);
        }
    }
    PopUpWin(3);
    PrintXY(24,20,(unsigned char*)"HP went up by",0);
    dtemp=pow(1.025,Level-1)+1;
    MHP+=dtemp;
    HP+=dtemp;
    temp=(int)MHP-(int)(MHP-dtemp);
    sprintf(str,"%6u",temp);
    PrintXY(66,28,(unsigned char*)str,0);
    Bdisp_PutDisp_DD();
    for(i=0;i<10;i++)
    {
        if(IsKeyUp(KEY_CTRL_EXE)) break;
        Sleep(50);
    }
    while(IsKeyUp(KEY_CTRL_EXE))
    {
        Sleep(50);
    }
    if(sel%2==0)
    {
        PopUpWin(3);
        PrintXY(18,24,(unsigned char*)"AP went up by 1",0);
        AP++;
        Bdisp_PutDisp_DD();
        for(i=0;i<10;i++)
        {
            if(IsKeyUp(KEY_CTRL_EXE)) break;
            Sleep(50);
        }
        while(IsKeyUp(KEY_CTRL_EXE))
        {
            Sleep(50);
        }
    }
    if(sel)
    {
        PopUpWin(3);
        PrintXY(18,24,(unsigned char*)"DP went up by 1",0);
        DP++;
        Bdisp_PutDisp_DD();
        for(i=0;i<10;i++)
        {
            if(IsKeyUp(KEY_CTRL_EXE)) break;
            Sleep(50);
        }
        while(IsKeyUp(KEY_CTRL_EXE))
        {
            Sleep(50);
        }
    }

    if(criRat(Level)-criRat(Level-1))
    {
        PopUpWin(3);
        PrintXY(18,16,(unsigned char*)"Critical ratio",0);
        if(Level==1)
            PrintXY(18,32,(unsigned char*)"went up to 1%",0);
        else
        {
            sprintf(str,"went up from %u%%",criRat(Level-1));
            PrintXY(18,24,(unsigned char*)str,0);
            sprintf(str,"to %u%%",criRat(Level));
            PrintXY(18,32,(unsigned char*)str,0);
        }
        Bdisp_PutDisp_DD();
        for(i=0;i<10;i++)
        {
            if(IsKeyUp(KEY_CTRL_EXE)) break;
            Sleep(50);
        }
        while(IsKeyUp(KEY_CTRL_EXE))
        {
            Sleep(50);
        }
    }

    if(criDam(Level)-criDam(Level-1))
    {
        PopUpWin(3);
        PrintXY(18,16,(unsigned char*)"Critical damage",0);
        if(Level==1)
        {
            PrintXY(18,24,(unsigned char*)"went up to",0);
            PrintXY(18,32,(unsigned char*)"+100%",0);
        }
        else
        {
            PrintXY(18,24,(unsigned char*)"went up from",0);
            sprintf(str,"+%u%% to +%u%%",criDam(Level-1),criDam(Level));
            PrintXY(18,32,(unsigned char*)str,0);
        }
        Bdisp_PutDisp_DD();
        for(i=0;i<10;i++)
        {
            if(IsKeyUp(KEY_CTRL_EXE)) break;
            Sleep(50);
        }
        while(IsKeyUp(KEY_CTRL_EXE))
        {
            Sleep(50);
        }
    }

    if(SkLv(Level,0)-SkLv(Level-1,0))
    {
        PopUpWin(3);
        if(SkLv(Level-1,0)==0)
        {
            PrintXY(16,16,(unsigned char*)"You learned",0);
            PrintXY(16,32,(unsigned char*)"Gut-Skill(AP UP)",0);
        }
        else
        {
            PrintXY(15,16,(unsigned char*)"Your Gut-Skill's",0);
            PrintXY(15,24,(unsigned char*)"level went up",0);
            sprintf(str,"to %u",SkLv(Level,0));
            PrintXY(15,32,(unsigned char*)str,0);
        }
        Bdisp_PutDisp_DD();
        for(i=0;i<10;i++)
        {
            if(IsKeyUp(KEY_CTRL_EXE)) break;
            Sleep(50);
        }
        while(IsKeyUp(KEY_CTRL_EXE))
        {
            Sleep(50);
        }
    }
    if(SkSt(Level,0)-SkSt(Level-1,0))
    {
        PopUpWin(3);
        PrintXY(13,16,(unsigned char*)"Your Gut-Skill's",0);
        PrintXY(13,24,(unsigned char*)"Max gauge went up",0);
        PrintXY(13,32,(unsigned char*)"by 1",0);
        Bdisp_PutDisp_DD();
        for(i=0;i<10;i++)
        {
            if(IsKeyUp(KEY_CTRL_EXE)) break;
            Sleep(50);
        }
        while(IsKeyUp(KEY_CTRL_EXE))
        {
            Sleep(50);
        }
    }

    if(SkLv(Level,1)-SkLv(Level-1,1))
    {
        PopUpWin(3);
        if(SkLv(Level-1,1)==0)
        {
            PrintXY(16,16,(unsigned char*)"You learned",0);
            PrintXY(16,32,(unsigned char*)"Shl-Skill(DP UP)",0);
        }
        else
        {
            PrintXY(15,16,(unsigned char*)"Your Shl-Skill's",0);
            PrintXY(15,24,(unsigned char*)"level went up",0);
            sprintf(str,"to %u",SkLv(Level,1));
            PrintXY(15,32,(unsigned char*)str,0);
        }
        Bdisp_PutDisp_DD();
        for(i=0;i<10;i++)
        {
            if(IsKeyUp(KEY_CTRL_EXE)) break;
            Sleep(50);
        }
        while(IsKeyUp(KEY_CTRL_EXE))
        {
            Sleep(50);
        }
    }
    if(SkSt(Level,1)-SkSt(Level-1,1))
    {
        PopUpWin(3);
        PrintXY(13,16,(unsigned char*)"Your Shl-Skill's",0);
        PrintXY(13,24,(unsigned char*)"Max gauge went up",0);
        PrintXY(13,32,(unsigned char*)"by 1",0);
        Bdisp_PutDisp_DD();
        for(i=0;i<10;i++)
        {
            if(IsKeyUp(KEY_CTRL_EXE)) break;
            Sleep(50);
        }
        while(IsKeyUp(KEY_CTRL_EXE))
        {
            Sleep(50);
        }
    }

    if(SkLv(Level,2)-SkLv(Level-1,2))
    {
        PopUpWin(3);
        if(SkLv(Level-1,2)==0)
        {
            PrintXY(18,16,(unsigned char*)"You learned",0);
            PrintXY(18,32,(unsigned char*)"Clm-Skill(FAP-)",0);
        }
        else
        {
            PrintXY(15,16,(unsigned char*)"Your Clm-Skill's",0);
            PrintXY(15,24,(unsigned char*)"level went up",0);
            sprintf(str,"to %u",SkLv(Level,2));
            PrintXY(15,32,(unsigned char*)str,0);
        }
        Bdisp_PutDisp_DD();
        for(i=0;i<10;i++)
        {
            if(IsKeyUp(KEY_CTRL_EXE)) break;
            Sleep(50);
        }
        while(IsKeyUp(KEY_CTRL_EXE))
        {
            Sleep(50);
        }
    }
    if(SkSt(Level,2)-SkSt(Level-1,2))
    {
        PopUpWin(3);
        PrintXY(13,16,(unsigned char*)"Your Clm-Skill's",0);
        PrintXY(13,24,(unsigned char*)"Max gauge went up",0);
        PrintXY(13,32,(unsigned char*)"by 1",0);
        Bdisp_PutDisp_DD();
        for(i=0;i<10;i++)
        {
            if(IsKeyUp(KEY_CTRL_EXE)) break;
            Sleep(50);
        }
        while(IsKeyUp(KEY_CTRL_EXE))
        {
            Sleep(50);
        }
    }

    if(SkLv(Level,3)-SkLv(Level-1,3))
    {
        PopUpWin(3);
        if(SkLv(Level-1,0)==0)
        {
            PrintXY(18,16,(unsigned char*)"You learned",0);
            PrintXY(18,32,(unsigned char*)"Diz-Skill(FDP-)",0);
        }
        else
        {
            PrintXY(15,16,(unsigned char*)"Your Diz-Skill's",0);
            PrintXY(15,24,(unsigned char*)"level went up",0);
            sprintf(str,"to %u",SkLv(Level,3));
            PrintXY(15,32,(unsigned char*)str,0);
        }
        Bdisp_PutDisp_DD();
        for(i=0;i<10;i++)
        {
            if(IsKeyUp(KEY_CTRL_EXE)) break;
            Sleep(50);
        }
        while(IsKeyUp(KEY_CTRL_EXE))
        {
            Sleep(50);
        }
    }
    if(SkSt(Level,3)-SkSt(Level-1,3))
    {
        PopUpWin(3);
        PrintXY(13,16,(unsigned char*)"Your Diz-Skill's",0);
        PrintXY(13,24,(unsigned char*)"Max gauge went up",0);
        PrintXY(13,32,(unsigned char*)"by 1",0);
        Bdisp_PutDisp_DD();
        for(i=0;i<10;i++)
        {
            if(IsKeyUp(KEY_CTRL_EXE)) break;
            Sleep(50);
        }
        while(IsKeyUp(KEY_CTRL_EXE))
        {
            Sleep(50);
        }
    }
}

void itemhelp(int ino,int prc)
{
    int bat;
    SaveDisp(SAVEDISP_PAGE2);
    Bdisp_AllClr_DDVRAM();
    Bdisp_DrawLineVRAM(7,12,120,12);
    Bdisp_DrawLineVRAM(7,35,120,35);
    Bdisp_DrawLineVRAM(7,12,7,35);
    Bdisp_DrawLineVRAM(120,12,120,35);
    PrintMini(41,10,(unsigned char*)"DISCRIPTION",MINI_OVER);
    Bdisp_DrawLineVRAM(7,42,120,42);
    Bdisp_DrawLineVRAM(7,55,120,55);
    Bdisp_DrawLineVRAM(7,42,7,55);
    Bdisp_DrawLineVRAM(120,42,120,55);
    PrintMini(54,40,(unsigned char*)"USAGE",MINI_OVER);
    if(ino<0)
    {
        if(ino>=-10)
        {
            bat=(1<<-1-ino);
            PrintXY(25,16,(unsigned char*)"Absorbs Foe's",0);
            if(ino==-10) sprintf(str,"damage by 999");
            else sprintf(str,"damage by %d",bat);
            PrintXY(25,24,(unsigned char*)str,0);
            if(ino==-10) sprintf(str,"Absorb-999");
            else sprintf(str,"Absorb-%d",bat);
        }
        else
        {
            sprintf(str,"Item");
        }
        bat=1;
    }
    else if(ino<=20)
    {
        PrintXY(16,16,(unsigned char*)"Restores your HP",0);
        sprintf(str,"by %d",HPI[ino-1]);
        PrintXY(16,24,(unsigned char*)str,0);
        sprintf(str,"HP+%d",HPI[ino-1]);
        bat=2;
    }
    else if(ino<=40)
    {
        PrintXY(10,16,(unsigned char*)"Charge 1 turn, hit",0);
        sprintf(str,"Foe with +%d'd AP",4*ino-80);
        PrintXY(10,24,(unsigned char*)str,0);
        sprintf(str,"Charge+%d",4*ino-80);
        bat=0;
    }
    else
    {
        if(ino==41)
        {
            PrintXY(22,16,(unsigned char*)"Removes Poison",0);
            PrintXY(22,24,(unsigned char*)"Status effect.",0);
        }
        if(ino==42)
        {
            PrintXY(22,16,(unsigned char*)"Removes Grassd",0);
            PrintXY(22,24,(unsigned char*)"Status effect.",0);
        }
        if(ino==43)
        {
            PrintXY(22,16,(unsigned char*)"Removes Shiver",0);
            PrintXY(22,24,(unsigned char*)"Status effect.",0);
        }
        if(ino==44)
        {
            PrintXY(22,16,(unsigned char*)"Removes Burn",0);
            PrintXY(22,24,(unsigned char*)"Status effect.",0);
        }
        if(ino==45)
        {
            PrintXY(25,16,(unsigned char*)"Recovers from",0);
            PrintXY(25,24,(unsigned char*)"Paralysis.",0);
        }
        if(ino==46)
        {
            PrintXY(10,16,(unsigned char*)"Negates the effect",0);
            PrintXY(10,24,(unsigned char*)"of Shrink Status.",0);
        }
        strcpy(str,Iname[ino-41]);
        bat=2;
    }
    if(prc)
    {
        PrintXY(6,0,(unsigned char*)str,0);
        sprintf(str,"$%d",prc);
        PrintXY(121-6*strlen(str),0,(unsigned char*)str,0);
    }
    else
    {
        PrintXY(6,0,(unsigned char*)"Item name:",0);
        PrintXY(66,0,(unsigned char*)str,0);
    }
    if(bat==0)
        PrintXY(22,46,(unsigned char*)"Only in battle",0);
    else if(bat==1)
        PrintXY(13,46,(unsigned char*)"As your equipment",0);
    else
    {
        if(bat==2)
            PrintXY(25,46,(unsigned char*)"Battle / Menu",0);
        else
            PrintXY(28,46,(unsigned char*)"Only in Menu",0);
    }
    Bdisp_PutDisp_DD();
    do{
        GetKeyWait(KEYWAIT_HALTON_TIMEROFF,0,1,&key);
    }while(IsKeyUp(KEY_CTRL_EXIT));
    RestoreDisp(SAVEDISP_PAGE2);
    Bdisp_PutDisp_DD();
    while(IsKeyDown(KEY_CTRL_EXIT))
    {
        Sleep(50);
    }
}

void Battle(double FHP, int FAP, int FDP, int FSpeed, int xp, int cn, int BType)
{
    int i,j,t=0;
    DISPBOX ldisp={3,22,60,49};
    DISPBOX rdisp={67,22,124,49};
    double damage;
    double FCHP=FHP;
    int mdg=90;
    int mfdg=90;
    int k=0;
    int BAP=AP;
    int BDP=DP;
    int MAP=0;
    int MDP=0;
    int FMAP=0;
    int FMDP=0;
    int charge=0;
    int timer=0;
    int timergoal=0;
    Bdisp_AllClr_DDVRAM();
    if(status==3) mdg=85;
    if(BType==-1)
    {
        PrintXY(12,28,(unsigned char*)"P",0);
        Bdisp_PutDisp_DD();
        Sleep(40);
        PrintXY(12,28,(unsigned char*)"Pl",0);
        Bdisp_PutDisp_DD();
        Sleep(40);
        PrintXY(12,28,(unsigned char*)"Pla",0);
        Bdisp_PutDisp_DD();
        Sleep(40);
        PrintXY(12,28,(unsigned char*)"Plac",0);
        Bdisp_PutDisp_DD();
        Sleep(40);
        PrintXY(12,28,(unsigned char*)"Place",0);
        Bdisp_PutDisp_DD();
        Sleep(80);
        PrintXY(12,28,(unsigned char*)"Place B",0);
        Bdisp_PutDisp_DD();
        Sleep(40);
        PrintXY(12,28,(unsigned char*)"Place Bo",0);
        Bdisp_PutDisp_DD();
        Sleep(40);
        PrintXY(12,28,(unsigned char*)"Place Bos",0);
        Bdisp_PutDisp_DD();
        Sleep(40);
        PrintXY(12,28,(unsigned char*)"Place Boss",0);
        Bdisp_PutDisp_DD();
        Sleep(80);
        PrintXY(12,28,(unsigned char*)"Place Boss F",0);
        Bdisp_PutDisp_DD();
        Sleep(40);
        PrintXY(12,28,(unsigned char*)"Place Boss Fi",0);
        Bdisp_PutDisp_DD();
        Sleep(40);
        PrintXY(12,28,(unsigned char*)"Place Boss Fig",0);
        Bdisp_PutDisp_DD();
        Sleep(40);
        PrintXY(12,28,(unsigned char*)"Place Boss Figh",0);
        Bdisp_PutDisp_DD();
        Sleep(40);
        PrintXY(12,28,(unsigned char*)"Place Boss Fight",0);
        Bdisp_PutDisp_DD();
        Sleep(40);
        PrintXY(12,28,(unsigned char*)"Place Boss Fight!",0);
        Bdisp_PutDisp_DD();
        Sleep(1250);
    }
    else if(BType==-2)
    {
        PrintXY(6,28,(unsigned char*)"S",0);
        Bdisp_PutDisp_DD();
        Sleep(50);
        PrintXY(6,28,(unsigned char*)"St",0);
        Bdisp_PutDisp_DD();
        Sleep(50);
        PrintXY(6,28,(unsigned char*)"Sta",0);
        Bdisp_PutDisp_DD();
        Sleep(50);
        PrintXY(6,28,(unsigned char*)"Stag",0);
        Bdisp_PutDisp_DD();
        Sleep(50);
        PrintXY(6,28,(unsigned char*)"Stage",0);
        Bdisp_PutDisp_DD();
        Sleep(100);
        PrintXY(6,28,(unsigned char*)"Stage L",0);
        Bdisp_PutDisp_DD();
        Sleep(50);
        PrintXY(6,28,(unsigned char*)"Stage Le",0);
        Bdisp_PutDisp_DD();
        Sleep(50);
        PrintXY(6,28,(unsigned char*)"Stage Lea",0);
        Bdisp_PutDisp_DD();
        Sleep(50);
        PrintXY(6,28,(unsigned char*)"Stage Lead",0);
        Bdisp_PutDisp_DD();
        Sleep(50);
        PrintXY(6,28,(unsigned char*)"Stage Leade",0);
        Bdisp_PutDisp_DD();
        Sleep(50);
        PrintXY(6,28,(unsigned char*)"Stage Leader",0);
        Bdisp_PutDisp_DD();
        Sleep(100);
        PrintXY(6,28,(unsigned char*)"Stage Leader F",0);
        Bdisp_PutDisp_DD();
        Sleep(50);
        PrintXY(6,28,(unsigned char*)"Stage Leader Fi",0);
        Bdisp_PutDisp_DD();
        Sleep(50);
        PrintXY(6,28,(unsigned char*)"Stage Leader Fig",0);
        Bdisp_PutDisp_DD();
        Sleep(50);
        PrintXY(6,28,(unsigned char*)"Stage Leader Figh",0);
        Bdisp_PutDisp_DD();
        Sleep(50);
        PrintXY(6,28,(unsigned char*)"Stage Leader Fight",0);
        Bdisp_PutDisp_DD();
        Sleep(50);
        PrintXY(6,28,(unsigned char*)"Stage Leader Fight!",0);
        Bdisp_PutDisp_DD();
        Sleep(1600);
    }
    else
    {
        PrintXY(15,28,(unsigned char*)"R",0);
        Bdisp_PutDisp_DD();
        Sleep(25);
        PrintXY(15,28,(unsigned char*)"Ro",0);
        Bdisp_PutDisp_DD();
        Sleep(25);
        PrintXY(15,28,(unsigned char*)"Row",0);
        Bdisp_PutDisp_DD();
        Sleep(25);
        PrintXY(15,28,(unsigned char*)"Row-",0);
        Bdisp_PutDisp_DD();
        Sleep(25);
        PrintXY(15,28,(unsigned char*)"Row-B",0);
        Bdisp_PutDisp_DD();
        Sleep(25);
        PrintXY(15,28,(unsigned char*)"Row-Ba",0);
        Bdisp_PutDisp_DD();
        Sleep(25);
        PrintXY(15,28,(unsigned char*)"Row-Bat",0);
        Bdisp_PutDisp_DD();
        Sleep(25);
        PrintXY(15,28,(unsigned char*)"Row-Batt",0);
        Bdisp_PutDisp_DD();
        Sleep(25);
        PrintXY(15,28,(unsigned char*)"Row-Battl",0);
        Bdisp_PutDisp_DD();
        Sleep(25);
        PrintXY(15,28,(unsigned char*)"Row-Battle",0);
        Bdisp_PutDisp_DD();
        Sleep(25);
        PrintXY(15,28,(unsigned char*)"Row-Battle F",0);
        Bdisp_PutDisp_DD();
        Sleep(50);
        PrintXY(15,28,(unsigned char*)"Row-Battle Fi",0);
        Bdisp_PutDisp_DD();
        Sleep(25);
        PrintXY(15,28,(unsigned char*)"Row-Battle Fig",0);
        Bdisp_PutDisp_DD();
        Sleep(25);
        PrintXY(15,28,(unsigned char*)"Row-Battle Figh",0);
        Bdisp_PutDisp_DD();
        Sleep(25);
        PrintXY(15,28,(unsigned char*)"Row-Battle Fight",0);
        Bdisp_PutDisp_DD();
        Sleep(600);
    }
    Bdisp_AllClr_DDVRAM();
    if(BType>=0 && BType<=3 && rand()%2==0) FCHP-=(FCHP*(rand()%16384))/163840.0;
    Bdisp_DrawLineVRAM(0,0,127,0);
    Bdisp_DrawLineVRAM(0,0,0,37);
    Bdisp_DrawLineVRAM(63,0,63,37);
    Bdisp_DrawLineVRAM(127,0,127,37);
    Bdisp_DrawLineVRAM(0,37,127,37);
    PrintXY(22,2,(unsigned char*)"YOU",0);
    if(BType>=0) PrintXY(81,2,(unsigned char*)"ENEMY",0);
    else PrintXY(84,2,(unsigned char*)"BOSS",0);
    if(BType==1)
    {
        PrintXY(120,2,(unsigned char*)"#",0);
        FCHP+=(4.5+0.5*Place)*(1+Place/4);
    }
    else if(BType==2)
    {
        PrintXY(114,2,(unsigned char*)"##",0);
        FCHP+=(8+1.1*Place)*(2+Place/4);
        if(rand()%2==0) FDP++;
    }
    else if(BType==3)
    {
        PrintXY(120,2,(unsigned char*)"$",0);
        FCHP+=Place+cn;
    }
    else if(BType==4)
    {
        PrintXY(114,2,(unsigned char*)"$$",0);
        FCHP+=2*(Place+cn);
    }
    else if(BType==5)
    {
        PrintXY(120,2,(unsigned char*)"&",0);
        FDP=11*FDP/10+1;
    }
    else if(BType==6)
    {
        PrintXY(114,2,(unsigned char*)"&&",0);
        FCHP+=(1+0.02*Place)*sqrt(xp);
        FAP++;
        FDP=8*FDP/7+1;
    }
    else if(BType==7)
        PrintXY(120,2,(unsigned char*)"*",0);
    sprintf(str,"HP %6u",(int)HP);
    PrintXY(4,13,(unsigned char*)str,0);
    sprintf(str,"AP %3u+ 0",BAP,MAP);
    PrintXY(4,21,(unsigned char*)str,0);
    sprintf(str,"DP %3u+ 0",DP,MDP);
    PrintXY(4,29,(unsigned char*)str,0);
    sprintf(str,"HP %6u",(int)FCHP);
    PrintXY(68,13,(unsigned char*)str,0);
    if(FAP) sprintf(str,"AP %3u- 0",FAP,FMAP);
    else sprintf(str,"AP   ?- 0");
    PrintXY(68,21,(unsigned char*)str,0);
    sprintf(str,"DP %3u- 0",FDP,FMDP);
    PrintXY(68,29,(unsigned char*)str,0);
    PrintXY(8,39,(unsigned char*)"F1:Attack",0);
    if(Level>0) PrintXY(68,39,(unsigned char*)"F2:Skill",0);
    PrintXY(8,47,(unsigned char*)"F3:Item   F4:Status",0);
    PrintXY(8,55,(unsigned char*)"F5:Damage F6:Run",0);
    Bdisp_PutDisp_DD();

    if(Place==58 && BType==-1|| Place==67 && BType==-2) k=1;
    if(rand()%(FSpeed)>Speed()) k=1;
    if(Level==400) k=0;

    while(HP>=1)
    {
        Sleep(50);
        if(k)
        {}
        else if(IsKeyDown(KEY_CTRL_F1))
        {
            k=1000-5*(rand()%(201-2*mdg));
            if(dno==99) k=1000;
            if(status==4) k-=250;
            if((rand()%100)<criRat(Level) && !(Place==55 && BType==-2 && FAP>0))
            {
                if(charge) k+=5*criDam(Level);
                else k+=10*criDam(Level);
                Bdisp_AreaReverseVRAM(64,1,126,36);
                Bdisp_PutDisp_DD();
                Sleep(75);
                Bdisp_AreaReverseVRAM(64,1,126,36);
                Bdisp_PutDisp_DD();
                Sleep(75);
                Bdisp_AreaReverseVRAM(64,1,126,36);
                Bdisp_PutDisp_DD();
                Sleep(75);
                Bdisp_AreaReverseVRAM(64,1,126,36);
                Bdisp_PutDisp_DD();
                Sleep(75);
            }
            Bdisp_AreaReverseVRAM(64,1,126,36);
            damage=Damage((BAP+MAP)*(20-(status==4))/20+charge,FDP-FMDP)*k/1000;
            if(damage>FCHP) damage=FCHP;
            FCHP-=damage;
            sprintf(str,"HP %6u",(int)FCHP);
            PrintXY(68,13,(unsigned char*)str,1);
            SaveDisp(SAVEDISP_PAGE1);
            Bdisp_DrawLineVRAM(66,21,125,21);
            Bdisp_DrawLineVRAM(66,21,66,50);
            Bdisp_DrawLineVRAM(125,21,125,50);
            Bdisp_DrawLineVRAM(66,50,125,50);
            Bdisp_AreaClr_VRAM(&rdisp);
            sprintf(str,"-%d",(int)(FCHP+damage)-(int)FCHP);
            PrintXY(122-6*strlen(str),24,(unsigned char*)str,0);
            if(k>1000) PrintXY(74,32,(unsigned char*)"CRITICAL",0);
            sprintf(str,"%3u.%u%%",k/10,k%10);
            PrintXY(86,40,(unsigned char*)str,0);
            Bdisp_PutDisp_DD();
            while(IsKeyDown(KEY_CTRL_EXE))
            {
                Sleep(50);
            }
            while(IsKeyUp(KEY_CTRL_EXE))
            {
                Sleep(50);
            }
            RestoreDisp(SAVEDISP_PAGE1);
            Bdisp_AreaReverseVRAM(64,1,126,36);
            Bdisp_PutDisp_DD();
            k=1;
            if(status==3 && mdg>50)
                mdg--;
            if(mdg>90)
                mdg--;
            charge=0;
        }
        else if(IsKeyDown(KEY_CTRL_F2) && Level>0)
        {
            PrintXY(68,39,(unsigned char*)"F2:Skill",1);
            SaveDisp(SAVEDISP_PAGE1);
            PopUpWin(5);
            if(SkLv(Level,0)) PrintXY(27,8,(unsigned char*)"1:Gut(AP UP)",0);
            if(SkLv(Level,1)) PrintXY(27,16,(unsigned char*)"2:Shl(DP UP)",0);
            if(SkLv(Level,2)) PrintXY(27,24,(unsigned char*)"3:Clm(FAP-)",0);
            if(SkLv(Level,3)) PrintXY(27,32,(unsigned char*)"4:Diz(FDP-)",0);
            if(skill[4] || skill[5] || skill[6] || skill[7]) PrintXY(27,40,(unsigned char*)"0:Next Page",0);
            Bdisp_PutDisp_DD();
            k=0;
            while(k<=0)
            {
                if(IsKeyDown(KEY_CHAR_0) && (skill[4] || skill[5] || skill[6] || skill[7]))
                {
                    k=-1-k;
                    if(k==0)
                    {
                        PopUpWin(5);
                        if(SkLv(Level,0)) PrintXY(27,8,(unsigned char*)"1:Gut(AP UP)",0);
                        if(SkLv(Level,1)) PrintXY(27,16,(unsigned char*)"2:Shl(DP UP)",0);
                        if(SkLv(Level,2)) PrintXY(27,24,(unsigned char*)"3:Clm(FAP-)",0);
                        if(SkLv(Level,3)) PrintXY(27,32,(unsigned char*)"4:Diz(FDP-)",0);
                        PrintXY(27,40,(unsigned char*)"0:Next Page",0);
                    }
                    else
                    {
                        PopUpWin(5);
                        if(skill[4]) PrintXY(27,8,(unsigned char*)"5:Hle(StatH)",0);
                        if(skill[5]) PrintXY(27,16,(unsigned char*)"6:Skill 6",0);
                        if(skill[6]) PrintXY(27,24,(unsigned char*)"7:Skill 7",0);
                        if(skill[7]) PrintXY(27,32,(unsigned char*)"8:Skill 8",0);
                        PrintXY(27,40,(unsigned char*)"0:Prev Page",0);
                    }
                    Bdisp_PutDisp_DD();
                    while(IsKeyDown(KEY_CHAR_0))
                    {
                        Sleep(50);
                    }
                }
                for(t=1;t<=8;t++)
                    if(IsKeyDown(KEY_CHAR_0+t) && skill[t-1]) k=t;
                if(IsKeyDown(KEY_CTRL_EXIT)) break;
                Sleep(50);
            }
            RestoreDisp(SAVEDISP_PAGE1);
            if(k==1)
            {
                MAP+=SkLv(Level,0);
                if(MAP>SkSt(Level,0)) MAP=SkSt(Level,0);
                sprintf(str,"AP %3u+%2u",BAP,MAP);
                PrintXY(4,21,(unsigned char*)str,0);
                SaveDisp(SAVEDISP_PAGE1);
                PopUpWin(3);
                sprintf(str,"AP+%u  Max:%2u",SkLv(Level,0),SkSt(Level,0));
                PrintXY(27,16,(unsigned char*)str,0);
                PrintXY(27,24,(unsigned char*)"Skill used:",0);
                sprintf(str,"%2u/%2u",MAP,SkSt(Level,0));
                PrintXY(69,32,(unsigned char*)str,0);
            }
            else if(k==2)
            {
                MDP+=SkLv(Level,1);
                if(MDP>SkSt(Level,1)) MDP=SkSt(Level,1);
                sprintf(str,"DP %3u+%2u",DP,MDP);
                PrintXY(4,29,(unsigned char*)str,0);
                SaveDisp(SAVEDISP_PAGE1);
                PopUpWin(3);
                sprintf(str,"DP+%u  Max:%2u",SkLv(Level,1),SkSt(Level,1));
                PrintXY(27,16,(unsigned char*)str,0);
                PrintXY(27,24,(unsigned char*)"Skill used:",0);
                sprintf(str,"%2u/%2u",MDP,SkSt(Level,1));
                PrintXY(69,32,(unsigned char*)str,0);
            }
            else if(k==3)
            {
                FMAP+=SkLv(Level,2);
                if(FMAP>SkSt(Level,2)) FMAP=SkSt(Level,2);
                if(FMAP>FAP && FAP>0) FMAP=FAP;
                if(FAP) sprintf(str,"AP %3u-%2u",FAP,FMAP);
                else sprintf(str,"AP   ?-%2u",FMAP);
                PrintXY(68,21,(unsigned char*)str,0);
                SaveDisp(SAVEDISP_PAGE1);
                PopUpWin(3);
                sprintf(str,"FAP-%u Max:%2u",SkLv(Level,2),SkSt(Level,2));
                PrintXY(27,16,(unsigned char*)str,0);
                PrintXY(27,24,(unsigned char*)"Skill used:",0);
                sprintf(str,"%2u/%2u",FMAP,SkSt(Level,2));
                PrintXY(69,32,(unsigned char*)str,0);
            }
            else if(k==4)
            {
                FMDP+=SkLv(Level,3);
                if(FMDP>SkSt(Level,3)) FMDP=SkSt(Level,3);
                sprintf(str,"DP %3u-%2u",FDP,FMDP);
                PrintXY(68,29,(unsigned char*)str,0);
                SaveDisp(SAVEDISP_PAGE1);
                PopUpWin(3);
                sprintf(str,"FDP-%u Max:%2u",SkLv(Level,3),SkSt(Level,3));
                PrintXY(27,16,(unsigned char*)str,0);
                PrintXY(27,24,(unsigned char*)"Skill used:",0);
                sprintf(str,"%2u/%2u",FMDP,SkSt(Level,3));
                PrintXY(69,32,(unsigned char*)str,0);
            }
            if(k>0)
            {
                Bdisp_PutDisp_DD();
                for(i=0;i<7;i++)
                {
                    if(IsKeyUp(KEY_CTRL_EXE)) break;
                    Sleep(50);
                }
                while(IsKeyUp(KEY_CTRL_EXE))
                {
                    Sleep(50);
                }
            }
            RestoreDisp(SAVEDISP_PAGE1);
            PrintXY(68,39,(unsigned char*)"F2:Skill",0);
            Bdisp_PutDisp_DD();
        }
        else if(IsKeyDown(KEY_CTRL_F3))
        {
            PrintXY(8,47,(unsigned char*)"F3:Item",1);
            SaveDisp(SAVEDISP_PAGE1);
            i=t=0;
            key=0;
            while(key==0)
            {
                PopUpWin(5);
                for(k=0;k<5;k++)
                {
                    if(item[5*t+k]==0) sprintf(str," ");
                    else if(item[5*t+k]<=20) sprintf(str,"HP+%u",HPI[item[5*t+k]-1]);
                    else if(item[5*t+k]<=40) sprintf(str,"Charge+%u",4*item[5*t+k]-80);
                    else strcpy(str,Iname[item[5*t+k]-41]);
                    PrintXY(36,8+8*k,(unsigned char*)str,0);
                    if(t)
                    {
                        sprintf(str,"%c%c",0xE6,0x9A);
                        PrintXY(15,24,(unsigned char*)str,0);
                    }
                    else
                    {
                        sprintf(str,"%c%c",0xE6,0x9B);
                        PrintXY(105,24,(unsigned char*)str,0);
                    }
                }
                Bdisp_AreaReverseVRAM(26,8+8*i,100,15+8*i);
                Bdisp_PutDisp_DD();
                j=0;
                while(key==0)
                {
                    if(k)
                    {
                        while(IsKeyDown(KEY_CTRL_EXIT))
                        {
                            Sleep(50);
                        }
                        k=0;
                    }
                    if(IsKeyDown(KEY_CTRL_RIGHT) && t==0)
                    {
                        t=1;
                        break;
                    }
                    if(IsKeyDown(KEY_CTRL_LEFT) && t)
                    {
                        t=0;
                        break;
                    }
                    if(IsKeyDown(KEY_CTRL_UP) && i>0 && j<=0)
                    {
                        i--;
                        Bdisp_AreaReverseVRAM(26,8+8*i,100,23+8*i);
                        Bdisp_PutDisp_DD();
                        j=4;
                    }
                    if(IsKeyDown(KEY_CTRL_DOWN) && i<4 && j<=0)
                    {
                        Bdisp_AreaReverseVRAM(26,8+8*i,100,23+8*i);
                        i++;
                        Bdisp_PutDisp_DD();
                        j=4;
                    }
                    if(IsKeyDown(KEY_CTRL_F1) && item[5*t+i]) itemhelp(item[5*t+i],0);
                    if(IsKeyDown(KEY_CTRL_EXIT))
                    {
                        key=1;
                        k=0;
                    }
                    if(IsKeyDown(KEY_CTRL_EXE) && item[5*t+i])
                    {
                        k=1;
                        key=1;
                        if(item[5*t+i]<=20)
                        {
                            if((MHP-HP<(double)effitem*HPI[item[5*t+i]-1]/1000) && IsKeyUp(KEY_CHAR_0))
                            {
                                SaveDisp(SAVEDISP_PAGE2);
                                RestoreDisp(SAVEDISP_PAGE1);
                                PopUpWin(4);
                                PrintXY(15,8,(unsigned char*)"It has little",0);
                                PrintXY(15,16,(unsigned char*)"effect.",0);
                                PrintXY(15,24,(unsigned char*)"To use it, press",0);
                                PrintXY(15,32,(unsigned char*)"[0]+[EXE]",0);
                                Bdisp_PutDisp_DD();
                                do
                                {
                                    GetKeyWait(KEYWAIT_HALTON_TIMEROFF,0,1,&key);
                                }while(IsKeyUp(KEY_CTRL_EXIT));
                                key=0;
                                RestoreDisp(SAVEDISP_PAGE2);
                                Bdisp_PutDisp_DD();
                            }
                            else
                            {
                                RestoreDisp(SAVEDISP_PAGE1);
                                damage=HPI[item[5*t+i]-1];
                                if(HP+damage>MHP) damage=MHP-HP;
                                HP+=damage;
                                sprintf(str,"HP %6u",(int)HP);
                                PrintXY(4,13,(unsigned char*)str,0);
                                SaveDisp(SAVEDISP_PAGE1);
                                Bdisp_DrawLineVRAM(2,21,61,21);
                                Bdisp_DrawLineVRAM(2,21,2,50);
                                Bdisp_DrawLineVRAM(61,21,61,50);
                                Bdisp_DrawLineVRAM(2,50,61,50);
                                Bdisp_AreaClr_VRAM(&ldisp);
                                sprintf(str,"+%d",(int)damage);
                                PrintXY(58-6*strlen(str),24,(unsigned char*)str,0);
                                PrintXY(34,40,(unsigned char*)"Heal",0);
                                Bdisp_PutDisp_DD();
                                while(IsKeyDown(KEY_CTRL_EXE))
                                {
                                    Sleep(50);
                                }
                                do
                                {
                                    GetKeyWait(KEYWAIT_HALTON_TIMEROFF,0,1,&j);
                                }while(IsKeyUp(KEY_CTRL_EXE));
                                RestoreDisp(SAVEDISP_PAGE1);
                            }
                        }
                        else if(item[5*t+i]<=40)
                        {
                            if(charge && IsKeyUp(KEY_CHAR_0))
                            {
                                SaveDisp(SAVEDISP_PAGE2);
                                PopUpWin(5);
                                PrintXY(15,8,(unsigned char*)"Double-Charging",0);
                                PrintXY(15,16,(unsigned char*)"is forbidden. To",0);
                                PrintXY(15,24,(unsigned char*)"cancel previous",0);
                                PrintXY(15,32,(unsigned char*)"and use, press",0);
                                PrintXY(15,40,(unsigned char*)"[0]+[EXE]",0);
                                Bdisp_PutDisp_DD();
                                do
                                {
                                    GetKeyWait(KEYWAIT_HALTON_TIMEROFF,0,1,&key);
                                }while(IsKeyUp(KEY_CTRL_EXIT));
                                key=0;
                                RestoreDisp(SAVEDISP_PAGE2);
                                Bdisp_PutDisp_DD();
                            }
                            else
                            {
                                RestoreDisp(SAVEDISP_PAGE1);
                                charge=4*item[5*t+i]-80;
                                PopUpWin(3);
                                sprintf(str,"Charge+%2u",charge);
                                PrintXY(33,16,(unsigned char*)str,0);
                                PrintXY(33,24,(unsigned char*)"Your AP:",0);
                                sprintf(str,"%3u+%2u=%3u",BAP+MAP,charge,BAP+MAP+charge);
                                PrintXY(33,32,(unsigned char*)str,0);
                                Bdisp_PutDisp_DD();
                                while(IsKeyDown(KEY_CTRL_EXE))
                                {
                                    Sleep(50);
                                }
                                do
                                {
                                    GetKeyWait(KEYWAIT_HALTON_TIMEROFF,0,1,&j);
                                }while(IsKeyUp(KEY_CTRL_EXE));
                                RestoreDisp(SAVEDISP_PAGE1);
                            }
                        }
                        else if(item[5*t+i]<=50)
                        {
                            if(!(status==1 && item[5*t+i]==41 || status==item[5*t+i]-39) && IsKeyUp(KEY_CHAR_0))
                            {
                                SaveDisp(SAVEDISP_PAGE2);
                                RestoreDisp(SAVEDISP_PAGE1);
                                PopUpWin(3);
                                PrintXY(13,16,(unsigned char*)"It has no effect.",0);
                                PrintXY(13,24,(unsigned char*)"To use it anyway,",0);
                                PrintXY(13,32,(unsigned char*)"press [0]+[EXE]",0);
                                Bdisp_PutDisp_DD();
                                do
                                {
                                    GetKeyWait(KEYWAIT_HALTON_TIMEROFF,0,1,&key);
                                }while(IsKeyUp(KEY_CTRL_EXIT));
                                key=0;
                                RestoreDisp(SAVEDISP_PAGE2);
                                Bdisp_PutDisp_DD();
                            }
                            else
                            {
                                RestoreDisp(SAVEDISP_PAGE1);
                                if(status==2 && item[5*t+i]==41)
                                {
                                    PopUpWin(3);
                                    PrintXY(24,16,(unsigned char*)"The effect of",0);
                                    PrintXY(24,24,(unsigned char*)"Poison Status",0);
                                    PrintXY(24,32,(unsigned char*)"was weakened.",0);
                                    status=1;
                                }
                                else if(status==1 && item[5*t+i]==41)
                                {
                                    PopUpWin(2);
                                    PrintXY(21,16,(unsigned char*)"You were cured",0);
                                    PrintXY(21,24,(unsigned char*)"of Poison.",0);
                                    status=0;
                                }
                                else if(status==3 && item[5*t+i]==42)
                                {
                                    PopUpWin(2);
                                    PrintXY(21,16,(unsigned char*)"You overcomed",0);
                                    PrintXY(21,24,(unsigned char*)"Grassd Status.",0);
                                    status=0;
                                    if(Place==31 && BType==-2) timergoal=timer+16;
                                    if(mdg<90) mdg=90;
                                }
                                else if(status==4 && item[5*t+i]==43)
                                {
                                    PopUpWin(2);
                                    PrintXY(21,16,(unsigned char*)"Your Shivering",0);
                                    PrintXY(21,24,(unsigned char*)"calmed down.",0);
                                    status=0;
                                }
                                else if(status==5 && item[5*t+i]==44)
                                {
                                    PopUpWin(2);
                                    PrintXY(21,16,(unsigned char*)"You cooled off",0);
                                    PrintXY(21,24,(unsigned char*)"Burned Status.",0);
                                    status=0;
                                }
                                else if(status==6 && item[5*t+i]==45)
                                {
                                    PopUpWin(2);
                                    PrintXY(21,16,(unsigned char*)"You were cured",0);
                                    PrintXY(21,24,(unsigned char*)"of Paralysis.",0);
                                    status=0;
                                }
                                else if(status==7 && item[5*t+i]==46)
                                {
                                    PopUpWin(2);
                                    PrintXY(13,16,(unsigned char*)"You got over from",0);
                                    PrintXY(13,24,(unsigned char*)"Shrink Status.",0);
                                    status=0;
                                }
                                else
                                {
                                    PopUpWin(1);
                                    PrintXY(13,24,(unsigned char*)"Nothing happened.",0);
                                }
                                Bdisp_PutDisp_DD();
                                while(IsKeyDown(KEY_CTRL_EXE))
                                {
                                    Sleep(50);
                                }
                                do
                                {
                                    GetKeyWait(KEYWAIT_HALTON_TIMEROFF,0,1,&j);
                                }while(IsKeyUp(KEY_CTRL_EXE));
                                RestoreDisp(SAVEDISP_PAGE1);
                            }
                        }
                        if(key) item[5*t+i]=0;
                    }
                    Sleep(50);
                    j--;
                    if(IsKeyUp(KEY_CTRL_UP) && IsKeyUp(KEY_CTRL_DOWN)) j=0;
                }
                if(key==1) break;
            }
            RestoreDisp(SAVEDISP_PAGE1);
            PrintXY(8,47,(unsigned char*)"F3:Item",0);
            Bdisp_PutDisp_DD();
        }
        else if(IsKeyDown(KEY_CTRL_F4))
        {
            SaveDisp(SAVEDISP_PAGE1);
            PrintXY(68,47,(unsigned char*)"F4:Status",1);
            PopUpWin(4);
            if(charge==0) PrintXY(25,8,(unsigned char*)"Discharged",0);
            else
            {
                sprintf(str,"Charged[%u]",charge);
                PrintXY(25,8,(unsigned char*)str,0);
            }
            if(status==0) PrintXY(25,16,(unsigned char*)"Status:Normal",0);
            else if(status==1 || status==2) PrintXY(25,16,(unsigned char*)"Status:Poison",0);
            else if(status==3) PrintXY(25,16,(unsigned char*)"Status:Grassd",0);
            else if(status==4) PrintXY(25,16,(unsigned char*)"Status:Shiver",0);
            else if(status==5) PrintXY(25,16,(unsigned char*)"Status:  Burn",0);
            else if(status==6) PrintXY(25,16,(unsigned char*)"Status:Paralz",0);
            else if(status==7) PrintXY(25,16,(unsigned char*)"Status:Shrink",0);
            PrintXY(25,32,(unsigned char*)"Press: [EXIT]",0);
            Bdisp_PutDisp_DD();
            while(IsKeyUp(KEY_CTRL_EXE) && IsKeyUp(KEY_CTRL_EXIT))
            {
                Sleep(50);
            }
            RestoreDisp(SAVEDISP_PAGE1);
            Bdisp_PutDisp_DD();
            k=0;
        }
        else if(IsKeyDown(KEY_CTRL_F5))
        {
            SaveDisp(SAVEDISP_PAGE1);
            PrintXY(8,55,(unsigned char*)"F5:Damage",1);
            PopUpWin(4);
            damage=Damage((BAP+MAP)*(20-(status==4))/20+charge,FDP-FMDP);
            if(damage>999999.999) damage=999999.999;
            sprintf(str,"You:%10.3f",damage);
            PrintXY(22,8,(unsigned char*)str,0);
            damage=Damage(FAP-FMAP,DP+MDP);
            if(FAP)
            {
                if(damage>999999.999) damage=999999.999;
                sprintf(str,"Foe:%10.3f",damage);
            }
            else sprintf(str,"Foe:       ???");
            PrintXY(22,16,(unsigned char*)str,0);
            sprintf(str,"Min.Ratio:%3d%%",mdg-25*(status==4));
            PrintXY(22,24,(unsigned char*)str,0);
            sprintf(str,"Max.Ratio:%3d%%",100-25*(status==4));
            PrintXY(22,32,(unsigned char*)str,0);
            Bdisp_PutDisp_DD();
            while(IsKeyUp(KEY_CTRL_EXE) && IsKeyUp(KEY_CTRL_EXIT))
            {
                Sleep(50);
            }
            RestoreDisp(SAVEDISP_PAGE1);
            Bdisp_PutDisp_DD();
            k=0;
        }
        else if(IsKeyDown(KEY_CTRL_F6))
        {
            k=0;
            if(Level)
            {
                if(Damage(BAP+MAP,FDP-FMDP)>FCHP*1.05) k=0;
                else k=(int)((FCHP*5*(rand()%50)/Damage(BAP+MAP,FDP-FMDP))*(Damage(FAP-FMAP,DP+MDP)/HP+25))/50;
                if(k>=3*Level) k=3*Level-1;
                if(k>Coin) k=Coin;
            }
            PopUpWin(3);
            PrintXY(36,16,(unsigned char*)"Run away",0);
            sprintf(str,"Coin -%u",k);
            PrintXY(36,32,(unsigned char*)str,0);
            Coin-=k;
            Bdisp_PutDisp_DD();
            while(IsKeyDown(KEY_CTRL_EXE))
            {
                Sleep(50);
            }
            while(IsKeyUp(KEY_CTRL_EXE))
            {
                Sleep(50);
            }
            break;
        }

        if(FCHP<1) break;
        if(k>0)
        {
            if(timer==timergoal)
            {
                if(Place==31 && BType==-2 && status!=3)
                {
                    status=3;
                    mdg=85;
                    SaveDisp(SAVEDISP_PAGE1);
                    for(i=0;i<4;i++)
                    {
                        Bdisp_AreaReverseVRAM(1,1,62,36);
                        Bdisp_PutDisp_DD();
                        Sleep(475);
                    }
                    PopUpWin(3);
                    PrintXY(18,16,(unsigned char*)"You became",0);
                    PrintXY(66,32,(unsigned char*)"Grassd.",0);
                    Bdisp_PutDisp_DD();
                    while(IsKeyDown(KEY_CTRL_EXE))
                    {
                        Sleep(50);
                    }
                    while(IsKeyUp(KEY_CTRL_EXE))
                    {
                        Sleep(50);
                    }
                    RestoreDisp(SAVEDISP_PAGE1);
                    Bdisp_PutDisp_DD();
                    k=-1;
                }
                if(Place==35 && BType==-2)
                {
                    SaveDisp(SAVEDISP_PAGE1);
                    PopUpWin(3);
                    PrintXY(18,16,(unsigned char*)"Boss neglects",0);
                    PrintXY(18,24,(unsigned char*)"you and is",0);
                    PrintXY(18,32,(unsigned char*)"loafing around.",0);
                    Bdisp_PutDisp_DD();
                    while(IsKeyDown(KEY_CTRL_EXE))
                    {
                        Sleep(50);
                    }
                    while(IsKeyUp(KEY_CTRL_EXE))
                    {
                        Sleep(50);
                    }
                    RestoreDisp(SAVEDISP_PAGE1);
                    Bdisp_PutDisp_DD();
                    k=-1;
                }
                if(Place==43 && BType==-2)
                {
                    if(timer==0 && status!=1)
                    {
                        status=1;
                        SaveDisp(SAVEDISP_PAGE1);
                        for(i=0;i<120;i+=2)
                        {
                            sprintf(str,"%c%c",0xE5,0x9D);
                            PrintXY(i,13,(unsigned char*)str,0);
                            PrintXY(120-i,13,(unsigned char*)str,0);
                            Bdisp_PutDisp_DD();
                            Sleep(30);
                            RestoreDisp(SAVEDISP_PAGE1);
                        }
                        PopUpWin(3);
                        PrintXY(18,16,(unsigned char*)"You became",0);
                        PrintXY(55,32,(unsigned char*)"Poisoned.",0);
                        Bdisp_PutDisp_DD();
                        while(IsKeyDown(KEY_CTRL_EXE))
                        {
                            Sleep(50);
                        }
                        while(IsKeyUp(KEY_CTRL_EXE))
                        {
                            Sleep(50);
                        }
                        RestoreDisp(SAVEDISP_PAGE1);
                        k=-1;
                    }
                    if(timer>0)
                    {
                        if(rand()%2)
                        {
                            FAP++;
                            sprintf(str,"AP %3u",FAP);
                            PrintXY(68,21,(unsigned char*)str,0);
                            SaveDisp(SAVEDISP_PAGE1);
                            Bdisp_AreaReverseVRAM(64,1,126,36);
                            PopUpWin(2);
                            PrintXY(60,24,(unsigned char*)"its AP.",0);
                        }
                        else
                        {
                            FDP++;
                            sprintf(str,"DP %3u",FDP);
                            PrintXY(68,29,(unsigned char*)str,0);
                            SaveDisp(SAVEDISP_PAGE1);
                            Bdisp_AreaReverseVRAM(64,1,126,36);
                            PopUpWin(2);
                            PrintXY(60,24,(unsigned char*)"its DP.",0);
                        }
                        PrintXY(21,16,(unsigned char*)"Boss Increased",0);
                        Bdisp_PutDisp_DD();
                        while(IsKeyDown(KEY_CTRL_EXE))
                        {
                            Sleep(50);
                        }
                        while(IsKeyUp(KEY_CTRL_EXE))
                        {
                            Sleep(50);
                        }
                        RestoreDisp(SAVEDISP_PAGE1);
                        k=-1;
                    }
                    Bdisp_PutDisp_DD();
                    timergoal+=10;
                }
                if(Place==55 && BType==-2)
                {
                    if(timer==0)
                    {
                        for(i=0;i<6;i++)
                        {
                            Bdisp_AreaReverseVRAM(0,0,127,63);
                            Bdisp_PutDisp_DD();
                            Sleep(280);
                        }
                        BAP/=2;
                        sprintf(str,"AP %3u+%2u",BAP,MAP);
                        PrintXY(4,21,(unsigned char*)str,0);
                        FCHP/=75;
                        sprintf(str,"HP %6u",(int)FCHP);
                        PrintXY(68,13,(unsigned char*)str,0);
                        FDP=20;
                        sprintf(str,"DP %3u-%2u",FDP,FMDP);
                        PrintXY(68,29,(unsigned char*)str,0);
                        FAP=80;
                        sprintf(str,"AP %3u-%2u",FAP,FMAP);
                        PrintXY(68,21,(unsigned char*)str,0);
                        SaveDisp(SAVEDISP_PAGE1);
                        PopUpWin(5);
                        PrintXY(21,8,(unsigned char*)"The boss used",0);
                        PrintXY(21,16,(unsigned char*)"its stat to",0);
                        PrintXY(21,24,(unsigned char*)"halve your AP",0);
                        PrintXY(21,32,(unsigned char*)"and remove",0);
                        PrintXY(21,40,(unsigned char*)"critical hits.",0);
                        Bdisp_PutDisp_DD();
                        while(IsKeyDown(KEY_CTRL_EXE))
                        {
                            Sleep(50);
                        }
                        while(IsKeyUp(KEY_CTRL_EXE))
                        {
                            Sleep(50);
                        }
                        RestoreDisp(SAVEDISP_PAGE1);
                        Bdisp_PutDisp_DD();
                        timergoal++;
                        k=-1;
                    }
                    else
                    {
                        SaveDisp(SAVEDISP_PAGE1);
                        PopUpWin(3);
                        PrintXY(15,16,(unsigned char*)"Press F1 Rapidly",0);
                        damage=Damage(FAP-FMAP,DP+MDP)*50;
                        sprintf(str,"Damage:   %6.0f",damage);
                        PrintXY(15,32,(unsigned char*)str,0);
                        Bdisp_PutDisp_DD();
                        k=0;
                        while(IsKeyUp(KEY_CTRL_F1))
                        {
                            Sleep(50);
                        }
                        SaveDisp(SAVEDISP_PAGE2);
                        key=0;
                        for(k=0;k<5*DP+3*MDP+5;k++)
                        {
                            RestoreDisp(SAVEDISP_PAGE2);
                            Bdisp_AreaReverseVRAM(13+100*k/(5*DP+3*MDP+5),24,113,29);
                            if(IsKeyDown(KEY_CTRL_F1))
                            {
                                if(key==0) damage/=1.04;
                                key=KEY_CTRL_F1;
                            }
                            else key=0;
                            sprintf(str,"Damage:   %6.0f",damage);
                            PrintXY(15,32,(unsigned char*)str,0);
                            Bdisp_PutDisp_DD();
                            Sleep(20);
                        }
                        RestoreDisp(SAVEDISP_PAGE1);
                        Bdisp_AreaReverseVRAM(1,1,62,36);
                        Bdisp_PutDisp_DD();
                        if(damage>HP) damage=HP;
                        HP-=damage;
                        t=(int)(HP+damage)-(int)HP;
                        sprintf(str,"HP %6u",(int)HP);
                        PrintXY(4,13,(unsigned char*)str,1);
                        SaveDisp(SAVEDISP_PAGE1);
                        Bdisp_DrawLineVRAM(2,21,61,21);
                        Bdisp_DrawLineVRAM(2,21,2,50);
                        Bdisp_DrawLineVRAM(61,21,61,50);
                        Bdisp_DrawLineVRAM(2,50,61,50);
                        Bdisp_AreaClr_VRAM(&ldisp);
                        sprintf(str,"-%d",t);
                        PrintXY(58-6*strlen(str),24,(unsigned char*)str,0);
                        sprintf(str,"%3u.%u%%",k/10,k%10);
                        PrintXY(16,40,(unsigned char*)"SPECIAL",0);
                        Bdisp_PutDisp_DD();
                        while(IsKeyDown(KEY_CTRL_EXE))
                        {
                            Sleep(50);
                        }
                        while(IsKeyUp(KEY_CTRL_EXE))
                        {
                            Sleep(50);
                        }
                        RestoreDisp(SAVEDISP_PAGE1);
                        Bdisp_AreaReverseVRAM(1,1,62,36);
                        Bdisp_PutDisp_DD();
                        timergoal+=5;
                        k=-1;
                    }
                }
                if(Place==59 && BType==-2 && status!=4)
                {
                    SaveDisp(SAVEDISP_PAGE1);
                    for(j=0;j<3;j++)
                    {
                        for(i=1;i<64;i+=3)
                        {
                            Bdisp_DrawLineVRAM(0,i,127,i);
                        }
                        Bdisp_PutDisp_DD();
                        Sleep(400);
                        RestoreDisp(SAVEDISP_PAGE1);
                        for(i=1;i<128;i+=3)
                        {
                            Bdisp_DrawLineVRAM(i,0,i,63);
                        }
                        Bdisp_PutDisp_DD();
                        Sleep(400);
                        RestoreDisp(SAVEDISP_PAGE1);
                    }
                    status=4;
                    FDP=7;
                    sprintf(str,"DP %3u-%2u",FDP,FMDP);
                    PrintXY(68,29,(unsigned char*)str,0);
                    SaveDisp(SAVEDISP_PAGE1);
                    PopUpWin(2);
                    PrintXY(15,16,(unsigned char*)"You are now in",0);
                    PrintXY(15,24,(unsigned char*)"Shivering status.",0);
                    Bdisp_PutDisp_DD();
                    while(IsKeyDown(KEY_CTRL_EXE))
                    {
                        Sleep(50);
                    }
                    while(IsKeyUp(KEY_CTRL_EXE))
                    {
                        Sleep(50);
                    }
                    RestoreDisp(SAVEDISP_PAGE1);
                    Bdisp_PutDisp_DD();
                    k=-1;
                }
            }
            if(Place==47 && BType==-2 && FCHP<3000.0 && FCHP>1.0)
            {
                Bdisp_AreaReverseVRAM(1,1,62,36);
                Bdisp_PutDisp_DD();
                Sleep(75);
                Bdisp_AreaReverseVRAM(1,1,62,36);
                Bdisp_PutDisp_DD();
                Sleep(75);
                Bdisp_AreaReverseVRAM(1,1,62,36);
                Bdisp_PutDisp_DD();
                Sleep(75);
                Bdisp_AreaReverseVRAM(1,1,62,36);
                Bdisp_PutDisp_DD();
                Sleep(75);
                Bdisp_AreaReverseVRAM(1,1,62,36);
                HP-=500.0;
                if(HP<0) HP=0;
                sprintf(str,"HP %6u",(int)HP);
                PrintXY(4,13,(unsigned char*)str,1);
                FCHP=1.0;
                sprintf(str,"HP %6u",(int)FCHP);
                PrintXY(68,13,(unsigned char*)str,0);
                SaveDisp(SAVEDISP_PAGE1);
                PopUpWin(3);
                PrintXY(23,16,(unsigned char*)"The Boss used",0);
                PrintXY(23,24,(unsigned char*)"FINAL BLOW",0);
                PrintXY(23,32,(unsigned char*)"HP-500",0);
                Bdisp_PutDisp_DD();
                while(IsKeyDown(KEY_CTRL_EXE))
                {
                    Sleep(50);
                }
                while(IsKeyUp(KEY_CTRL_EXE))
                {
                    Sleep(50);
                }
                RestoreDisp(SAVEDISP_PAGE1);
                Bdisp_PutDisp_DD();
                k=-1;
            }
            if(k)
            {
                if(k>0 || status==1)
                    Bdisp_AreaReverseVRAM(1,1,62,36);
                if(k>0)
                {
                    k=1000-5*(rand()%21);
                    if(dno==99) k=900;
                    if(charge) k=800;
                    damage=Damage(FAP-FMAP,DP+MDP)*k/1000;
                    if(damage>HP) damage=HP;
                    HP-=damage;
                    t=(int)(HP+damage)-(int)HP;
                }
                if(status==1 && k!=99)
                {
                    damage=sqrt(MHP)/40+sqrt(HP)/40;
                    if(damage>HP) damage=HP;
                    HP-=damage;
                }
                if(k>0 || status==1 && k!=99)
                {
                    sprintf(str,"HP %6u",(int)HP);
                    PrintXY(4,13,(unsigned char*)str,1);
                    SaveDisp(SAVEDISP_PAGE1);
                    Bdisp_DrawLineVRAM(2,21,61,21);
                    Bdisp_DrawLineVRAM(2,21,2,50);
                    Bdisp_DrawLineVRAM(61,21,61,50);
                    Bdisp_DrawLineVRAM(2,50,61,50);
                    Bdisp_AreaClr_VRAM(&ldisp);
                }
                if(k>0)
                {
                    sprintf(str,"-%d",t);
                    PrintXY(58-6*strlen(str),24,(unsigned char*)str,0);
                    sprintf(str,"%3u.%u%%",k/10,k%10);
                    PrintXY(22,40,(unsigned char*)str,0);
                }
                if(status==1 && k!=99)
                {
                    sprintf(str,"P-%d",(int)(HP+damage)-(int)HP);
                    PrintXY(58-6*strlen(str),32,(unsigned char*)str,0);
                }
                if(k>0 || status==1 && k!=99)
                {
                    Bdisp_PutDisp_DD();
                    while(IsKeyDown(KEY_CTRL_EXE))
                    {
                        Sleep(50);
                    }
                    while(IsKeyUp(KEY_CTRL_EXE))
                    {
                        Sleep(50);
                    }
                    RestoreDisp(SAVEDISP_PAGE1);
                    Bdisp_AreaReverseVRAM(1,1,62,36);
                    Bdisp_PutDisp_DD();
                }
            }
            k=0;
            timer++;
        }
        rand();
    }

    if(FCHP<=1)
    {
        Bdisp_AllClr_DDVRAM();
        k=rand()%4;
        if(k<3) k=2;

        if(BType>=5 && BType<=6)
        {
            if(BType==6) k=3*k+1;
            sprintf(str,"Ex.pts %8u%c%u",xp,0xA9,k);
            xp*=k;
        }
        else sprintf(str,"Ex.pts %8u",xp);
        PrintXY(18,9,(unsigned char*)str,0);
        if(BType>=3 && BType<=4)
        {
            if(BType==4) k=10;
            sprintf(str,"Coin    %7u%c%u",cn,0xA9,k);
            cn*=k;
        }
        else sprintf(str,"Coin    %7u",cn);
        PrintXY(18,24,(unsigned char*)str,0);

        if(BType>=1 && BType<=2)
        {
            if(Place<80) k=(k-1)*5*(Place/4+1);
            else k=(k-1)*10*(Place/4-9);
            if(BType==2) k=20*(Place/4+1);
            if(k%10==0)
                sprintf(str,"Max.HP went up by %u",k/10);
            else
                sprintf(str,"Max.HP went up by %u.%u",k/10,k%10);
            PrintXY(0,42,(unsigned char*)str,0);
            MHP+=k/10.0;
        }
        if(BType<0)
        {
            Stage++;
            PrintXY(30,39,(unsigned char*)"You cleared",0);
            if(BType==-1) PrintXY(30,47,(unsigned char*)"Place Boss!",0);
            else PrintXY(24,47,(unsigned char*)"Stage Leader!",0);
            x_axis+=6;
        }
        EXP+=xp;
        if(Coin+cn>2500000) cn=2500000-Coin;
        Coin+=cn;
        Bdisp_PutDisp_DD();
        while(IsKeyDown(KEY_CTRL_EXE))
        {
            Sleep(50);
        }
        while(IsKeyUp(KEY_CTRL_EXE))
        {
            Sleep(50);
        }
        if(EXP>=MEXP(Level))
        {
            EXP-=MEXP(Level);
            LevelUp();
        }
    }
    work=0;
    Refresh();
}

void SpBat(int batno)
{
    DISPBOX ldisp={3,20,60,47};
    double damage;
    double FHP[6];
    int mdg=90;
    int mfdg=90;
    int i,j,t=0;
    int k=0,l=0;
    int MAP=0;
    int MDP=0;
    int FMAP=0;
    int FMDP=0;
    int timer=0;
    int timergoal=0;
    int vars[10];
    if(batno==1)
    {
        Sleep(1000);
        SaveDisp(SAVEDISP_PAGE1);
        PopUpWin(4);
        PrintXY(27,16,(unsigned char*)"Something",0);
        PrintXY(27,24,(unsigned char*)"shines dimly.",0);
        Bdisp_PutDisp_DD();
        Sleep(500);
        while(IsKeyUp(KEY_CTRL_EXE))
        {
            Sleep(50);
        }
        RestoreDisp(SAVEDISP_PAGE1);
        PrintXY(61,40,(unsigned char*)"C",0);
        Bdisp_PutDisp_DD();
        Sleep(500);
        SaveDisp(SAVEDISP_PAGE1);
        for(i=0;i<55;i++)
        {
            RestoreDisp(SAVEDISP_PAGE1);
            PrintXY(39+i/3,25+i/7,(unsigned char*)"1",0);
            PrintXY(83-i/3,25+i/7,(unsigned char*)"2",0);
            PrintXY(122-i,40,(unsigned char*)"3",0);
            PrintXY(83-i/3,55-i/7,(unsigned char*)"4",0);
            PrintXY(39+i/3,55-i/7,(unsigned char*)"5",0);
            PrintXY(i,40,(unsigned char*)"6",0);
            Sleep(35);
            Bdisp_PutDisp_DD();
        }
        Sleep(500);
        SaveDisp(SAVEDISP_PAGE1);
        PopUpWin(5);
        PrintXY(18,8,(unsigned char*)"Sqir Guy 1:",0);
        PrintXY(18,16,(unsigned char*)"Hey, everyone.",0);
        PrintXY(18,24,(unsigned char*)"Isn't this guy",0);
        PrintXY(18,32,(unsigned char*)"likely to steal",0);
        PrintXY(18,40,(unsigned char*)"that stone?",0);
        Bdisp_PutDisp_DD();
        while(IsKeyDown(KEY_CTRL_EXE))
        {
            Sleep(50);
        }
        while(IsKeyUp(KEY_CTRL_EXE))
        {
            Sleep(50);
        }
        RestoreDisp(SAVEDISP_PAGE1);
        Bdisp_PutDisp_DD();
        Sleep(300);
        PopUpWin(4);
        PrintXY(21,8,(unsigned char*)"Sqir Guy 3:",0);
        PrintXY(21,16,(unsigned char*)"What? We",0);
        PrintXY(21,24,(unsigned char*)"kept it for a",0);
        PrintXY(21,32,(unsigned char*)"lot of time!",0);
        Bdisp_PutDisp_DD();
        while(IsKeyDown(KEY_CTRL_EXE))
        {
            Sleep(50);
        }
        while(IsKeyUp(KEY_CTRL_EXE))
        {
            Sleep(50);
        }
        RestoreDisp(SAVEDISP_PAGE1);
        Bdisp_PutDisp_DD();
        Sleep(300);
        PopUpWin(3);
        PrintXY(24,16,(unsigned char*)"Sqir Guy 4:",0);
        PrintXY(24,24,(unsigned char*)"How many days",0);
        PrintXY(24,32,(unsigned char*)"was it, bro?",0);
        Bdisp_PutDisp_DD();
        while(IsKeyDown(KEY_CTRL_EXE))
        {
            Sleep(50);
        }
        while(IsKeyUp(KEY_CTRL_EXE))
        {
            Sleep(50);
        }
        RestoreDisp(SAVEDISP_PAGE1);
        Bdisp_PutDisp_DD();
        Sleep(300);
        PopUpWin(3);
        PrintXY(21,16,(unsigned char*)"Sqir Guy 3:",0);
        PrintXY(21,24,(unsigned char*)"Hmm... let me",0);
        PrintXY(21,32,(unsigned char*)"see.",0);
        Bdisp_PutDisp_DD();
        while(IsKeyDown(KEY_CTRL_EXE))
        {
            Sleep(50);
        }
        while(IsKeyUp(KEY_CTRL_EXE))
        {
            Sleep(50);
        }
        RestoreDisp(SAVEDISP_PAGE1);
        PopUpWin(2);
        PrintXY(21,16,(unsigned char*)"Oh, I found it",0);
        PrintXY(21,24,(unsigned char*)"2 days ago!",0);
        Bdisp_PutDisp_DD();
        while(IsKeyDown(KEY_CTRL_EXE))
        {
            Sleep(50);
        }
        while(IsKeyUp(KEY_CTRL_EXE))
        {
            Sleep(50);
        }
        RestoreDisp(SAVEDISP_PAGE1);
        Bdisp_PutDisp_DD();
        Sleep(300);
        PopUpWin(4);
        PrintXY(21,8,(unsigned char*)"Sqir Guy 2:",0);
        PrintXY(21,16,(unsigned char*)"Anyway, that",0);
        PrintXY(21,24,(unsigned char*)"fellow doesn't",0);
        PrintXY(21,32,(unsigned char*)"look friendly.",0);
        Bdisp_PutDisp_DD();
        while(IsKeyDown(KEY_CTRL_EXE))
        {
            Sleep(50);
        }
        while(IsKeyUp(KEY_CTRL_EXE))
        {
            Sleep(50);
        }
        RestoreDisp(SAVEDISP_PAGE1);
        Bdisp_PutDisp_DD();
        Sleep(300);
        PopUpWin(3);
        PrintXY(18,16,(unsigned char*)"Sqir Guy 6:",0);
        PrintXY(18,24,(unsigned char*)"Yeah!",0);
        PrintXY(18,32,(unsigned char*)"Fellow, follow!",0);
        Bdisp_PutDisp_DD();
        while(IsKeyDown(KEY_CTRL_EXE))
        {
            Sleep(50);
        }
        while(IsKeyUp(KEY_CTRL_EXE))
        {
            Sleep(50);
        }
        RestoreDisp(SAVEDISP_PAGE1);
        Bdisp_PutDisp_DD();
        Sleep(300);
        PopUpWin(3);
        PrintXY(18,16,(unsigned char*)"Sqir Guy 5:",0);
        PrintXY(18,24,(unsigned char*)"Does it mean we",0);
        PrintXY(18,32,(unsigned char*)"have to fight?",0);
        Bdisp_PutDisp_DD();
        while(IsKeyDown(KEY_CTRL_EXE))
        {
            Sleep(50);
        }
        while(IsKeyUp(KEY_CTRL_EXE))
        {
            Sleep(50);
        }
        RestoreDisp(SAVEDISP_PAGE1);
        Bdisp_PutDisp_DD();
        Sleep(300);
        PopUpWin(4);
        PrintXY(21,8,(unsigned char*)"Sqir Guy 1:",0);
        PrintXY(21,16,(unsigned char*)"If we have to",0);
        PrintXY(21,24,(unsigned char*)"protect that",0);
        PrintXY(21,32,(unsigned char*)"piece of rock.",0);
        Bdisp_PutDisp_DD();
        while(IsKeyDown(KEY_CTRL_EXE))
        {
            Sleep(50);
        }
        while(IsKeyUp(KEY_CTRL_EXE))
        {
            Sleep(50);
        }
        RestoreDisp(SAVEDISP_PAGE1);
        Bdisp_PutDisp_DD();
        Sleep(300);
        PopUpWin(4);
        PrintXY(18,8,(unsigned char*)"Sqir Guy 3:",0);
        PrintXY(18,16,(unsigned char*)"That man steals",0);
        PrintXY(18,24,(unsigned char*)"my favorite",0);
        PrintXY(18,32,(unsigned char*)"stone? No way!",0);
        Bdisp_PutDisp_DD();
        while(IsKeyDown(KEY_CTRL_EXE))
        {
            Sleep(50);
        }
        while(IsKeyUp(KEY_CTRL_EXE))
        {
            Sleep(50);
        }
        RestoreDisp(SAVEDISP_PAGE1);
        Bdisp_PutDisp_DD();
        Sleep(300);
        PopUpWin(5);
        PrintXY(15,8,(unsigned char*)"Sqir Guy 4:",0);
        PrintXY(15,16,(unsigned char*)"I know that it",0);
        PrintXY(15,24,(unsigned char*)"was found near",0);
        PrintXY(15,32,(unsigned char*)"our house, so",0);
        PrintXY(15,40,(unsigned char*)"we have to keep!",0);
        Bdisp_PutDisp_DD();
        while(IsKeyDown(KEY_CTRL_EXE))
        {
            Sleep(50);
        }
        while(IsKeyUp(KEY_CTRL_EXE))
        {
            Sleep(50);
        }
        RestoreDisp(SAVEDISP_PAGE1);
        Bdisp_PutDisp_DD();
        Sleep(300);
        PopUpWin(4);
        PrintXY(21,8,(unsigned char*)"Sqir Guy 1:",0);
        PrintXY(21,16,(unsigned char*)"OK, then let's",0);
        PrintXY(21,24,(unsigned char*)"deal with this",0);
        PrintXY(21,32,(unsigned char*)"guy.",0);
        Bdisp_PutDisp_DD();
        while(IsKeyDown(KEY_CTRL_EXE))
        {
            Sleep(50);
        }
        while(IsKeyUp(KEY_CTRL_EXE))
        {
            Sleep(50);
        }

        Bdisp_AllClr_DDVRAM();
        PrintXY(21,22,(unsigned char*)"S            e",0);
        Bdisp_PutDisp_DD();
        Sleep(100);
        PrintXY(21,22,(unsigned char*)"Sp          le",0);
        Bdisp_PutDisp_DD();
        Sleep(100);
        PrintXY(21,22,(unsigned char*)"Spe        tle",0);
        Bdisp_PutDisp_DD();
        Sleep(100);
        PrintXY(21,22,(unsigned char*)"Spec      ttle",0);
        Bdisp_PutDisp_DD();
        Sleep(100);
        PrintXY(21,22,(unsigned char*)"Speci    attle",0);
        Bdisp_PutDisp_DD();
        Sleep(100);
        PrintXY(21,22,(unsigned char*)"Specia  Battle",0);
        Bdisp_PutDisp_DD();
        Sleep(100);
        PrintXY(21,22,(unsigned char*)"Special Battle",0);
        Bdisp_PutDisp_DD();
        Sleep(700);
        for(i=0;i<30;i++)
        {
            PrintXY(27,34,(unsigned char*)"1 vs 6 Fight",0);
            Bdisp_PutDisp_DD();
            Sleep(25);
            PrintXY(27,34,(unsigned char*)"            ",0);
            Bdisp_PutDisp_DD();
            Sleep(25);
        }
        PrintXY(27,34,(unsigned char*)"1 vs 6 Fight",0);
        Bdisp_PutDisp_DD();
        Sleep(1700);
        FHP[0]=999; FHP[1]=950; FHP[2]=900; FHP[3]=800; FHP[4]=750; FHP[5]=700;
        Bdisp_AllClr_DDVRAM();
        Bdisp_DrawLineVRAM(0,0,127,0);
        Bdisp_DrawLineVRAM(0,0,0,34);
        Bdisp_DrawLineVRAM(64,0,64,34);
        Bdisp_DrawLineVRAM(127,0,127,34);
        Bdisp_DrawLineVRAM(0,34,127,34);
        Bdisp_DrawLineVRAM(0,8,127,8);
        Bdisp_DrawLineVRAM(64,16,127,16);
        Bdisp_DrawLineVRAM(64,24,127,24);
        Bdisp_DrawLineVRAM(85,8,85,24);
        Bdisp_DrawLineVRAM(106,8,106,24);
        PrintMini(26,2,(unsigned char*)"YOU",MINI_OVER);
        PrintMini(78,2,(unsigned char*)"SQIR GUYS",MINI_OVER);
        sprintf(str,"HP %6u",(int)HP);
        PrintXY(5,10,(unsigned char*)str,0);
        sprintf(str,"AP %3u+ 0",AP,MAP);
        PrintXY(5,18,(unsigned char*)str,0);
        sprintf(str,"DP %3u+ 0",DP,MDP);
        PrintXY(5,26,(unsigned char*)str,0);
        for(i=0;i<6;i++)
        {
            sprintf(str,"%3u",(int)FHP[i]);
            PrintMini(70+21*(i%3),10+8*(i/3),(unsigned char*)str,0);
        }
        sprintf(str,"AP %3d",80-FMAP);
        PrintMini(68,27,(unsigned char*)str,0);
        sprintf(str,"DP %3d",5-FMDP);
        PrintMini(101,27,(unsigned char*)str,0);
        PrintMini(8,36,(unsigned char*)"F1:ATTACK  F2:SKILL  F3:ITEM",MINI_OVER);
        damage=SpDam(AP+MAP,5-FMDP);
        if(damage>999999.999) damage=999999.999;
        sprintf(str,"You:%6.0f%c%c%c",damage,0xA9,0xE6,0x40);
        PrintXY(27,44,(unsigned char*)str,0);
        damage=SpDam(80-FMAP,DP+MDP);
        if(damage>999999.999) damage=999999.999;
        sprintf(str,"Foe:%6.0f%c%c%c",damage,0xA9,0xE6,0x40);
        PrintXY(27,52,(unsigned char*)str,0);
        Bdisp_PutDisp_DD();

        while(HP>=1)
        {
            Sleep(50);
            if(IsKeyDown(KEY_CTRL_F1))
            {
                PrintMini(8,36,(unsigned char*)"F1:ATTACK",MINI_REV);
                PrintXY(21,44,(unsigned char*)"              ",0);
                PrintXY(21,52,(unsigned char*)"              ",0);
                PrintXY(27,46,(unsigned char*)"Choose Enemy",0);
                SaveDisp(SAVEDISP_PAGE1);
                for(i=0;i<6;i++)
                    if(FHP[i]) break;
                Bdisp_AreaReverseVRAM(65+21*(i%3),9+8*(i/3),84+21*(i%3),15+8*(i/3));
                do
                {
                    Bdisp_PutDisp_DD();
                    GetKeyWait(KEYWAIT_HALTON_TIMEROFF,0,1,&key);
                    if(IsKeyDown(KEY_CTRL_RIGHT))
                    {
                        do
                        {
                            i=(i+1)%6;
                        }while(FHP[i]==0);
                        RestoreDisp(SAVEDISP_PAGE1);
                        Bdisp_AreaReverseVRAM(65+21*(i%3),9+8*(i/3),84+21*(i%3),15+8*(i/3));
                    }
                    if(IsKeyDown(KEY_CTRL_LEFT))
                    {
                        do
                        {
                            i=(i+5)%6;
                        }while(FHP[i]==0);
                        RestoreDisp(SAVEDISP_PAGE1);
                        Bdisp_AreaReverseVRAM(65+21*(i%3),9+8*(i/3),84+21*(i%3),15+8*(i/3));
                    }
                    if(IsKeyDown(KEY_CTRL_UP) || IsKeyDown(KEY_CTRL_DOWN))
                    {
                        do
                        {
                            i=(i+3)%6;
                        }while(FHP[i]==0);
                        RestoreDisp(SAVEDISP_PAGE1);
                        Bdisp_AreaReverseVRAM(65+21*(i%3),9+8*(i/3),84+21*(i%3),15+8*(i/3));
                    }
                    key=0;
                    if(IsKeyDown(KEY_CTRL_EXE)) key=KEY_CTRL_EXE;
                    if(IsKeyDown(KEY_CTRL_EXIT)) key=KEY_CTRL_EXIT;
                }while(key!=KEY_CTRL_EXE && key!=KEY_CTRL_EXIT);
                PrintXY(27,46,(unsigned char*)"            ",0);
                if(key==KEY_CTRL_EXE)
                {
                    dam=damage=SpDam(AP+MAP,5-FMDP);
                    for(j=0;;j++)
                    {
                        if(damage>FHP[i]) damage=FHP[i];
                        sprintf(str,"%d Combo",j);
                        PrintXY(0,56,(unsigned char*)str,0);
                        sprintf(str,"Damage:%d",(int)damage);
                        PrintXY(66,56,(unsigned char*)str,0);
                        vars[6]=rand()%6;
                        vars[7]=rand()%5;
                        if(vars[7]>=vars[6]) vars[7]++;
                        else
                        {
                            vars[8]=vars[6];
                            vars[6]=vars[7];
                            vars[7]=vars[8];
                        }
                        sprintf(str,"Press:F%dF%d",vars[6]+1,vars[7]+1);
                        PrintXY(0,42,(unsigned char*)str,0);
                        SaveDisp(SAVEDISP_PAGE1);
                        vars[9]=(int)(200-j+200*(j==0)-damage/8);
                        for(k=0;k<vars[9];k++)
                        {
                            Bdisp_AreaReverseVRAM(126*k/vars[9],50,126,54);
                            Bdisp_PutDisp_DD();
                            for(l=0;l<6;l++)
                            {
                                if(IsKeyDown(KEY_CTRL_F1+l)) vars[l]=1;
                                else vars[l]=0;
                            }
                            RestoreDisp(SAVEDISP_PAGE1);
                            if(vars[vars[6]] && vars[vars[7]] && vars[0]+vars[1]+vars[2]+vars[3]+vars[4]+vars[5]==2) break;
                            k+=vars[0]+vars[1]+vars[2]+vars[3]+vars[4]+vars[5];
                            Sleep(10);
                        }
                        if(k>=vars[9]) break;
                        damage+=0.08*dam-0.06*dam*k/vars[9];
                    }
                    PrintXY(0,42,(unsigned char*)"          ",0);
                    PrintXY(66,56,(unsigned char*)"          ",0);
                    PrintXY(116,48,(unsigned char*)"S",0);
                    for(k=0;k<=116;k+=2)
                    {
                        PrintXY(k,48,(unsigned char*)">",0);
                        Bdisp_PutDisp_DD();
                        Sleep((100-j)/2);
                    }
                    for(k=0;k<4;k++)
                    {
                        Bdisp_AreaReverseVRAM(65+21*(i%3),9+8*(i/3),84+21*(i%3),15+8*(i/3));
                        Bdisp_PutDisp_DD();
                        Sleep(75);
                    }
                    FHP[i]-=damage;
                    if(FHP[i]<1) FHP[i]=0;
                    sprintf(str,"-%3d",(int)(FHP[i]+damage)-(int)FHP[i]);
                    PrintMini(68+21*(i%3),10+8*(i/3),(unsigned char*)str,MINI_REV);
                    Bdisp_PutDisp_DD();
                    while(IsKeyDown(KEY_CTRL_EXE))
                    {
                        Sleep(50);
                    }
                    while(IsKeyUp(KEY_CTRL_EXE))
                    {
                        Sleep(50);
                    }
                    Bdisp_AreaReverseVRAM(65+21*(i%3),9+8*(i/3),84+21*(i%3),15+8*(i/3));
                    PrintMini(68+21*(i%3),10+8*(i/3),(unsigned char*)"    ",0);
                    sprintf(str,"%3u",(int)FHP[i]);
                    PrintMini(70+21*(i%3),10+8*(i/3),(unsigned char*)str,0);
                    PrintXY(116,48,(unsigned char*)" ",0);
                    PrintXY(0,56,(unsigned char*)"         ",0);
                    Bdisp_PutDisp_DD();
                    k=1;
                }
                else
                {
                    Bdisp_AreaReverseVRAM(65+21*(i%3),9+8*(i/3),84+21*(i%3),15+8*(i/3));
                    PrintMini(8,36,(unsigned char*)"F1:ATTACK",MINI_OVER);
                    damage=SpDam(AP+MAP,5-FMDP);
                    if(damage>999999.999) damage=999999.999;
                    sprintf(str,"You:%6.0f%c%c%c",damage,0xA9,0xE6,0x40);
                    PrintXY(27,44,(unsigned char*)str,0);
                    damage=SpDam(80-FMAP,DP+MDP);
                    if(damage>999999.999) damage=999999.999;
                    sprintf(str,"Foe:%6.0f%c%c%c",damage,0xA9,0xE6,0x40);
                    PrintXY(27,52,(unsigned char*)str,0);
                    Bdisp_PutDisp_DD();
                }
            }
            else if(IsKeyDown(KEY_CTRL_F2) && Level>0)
            {
                PrintMini(51,36,(unsigned char*)"F2:SKILL",MINI_REV);
                SaveDisp(SAVEDISP_PAGE1);
                PopUpWin(5);
                if(SkLv(Level,0)) PrintXY(27,8,(unsigned char*)"1:Gut(AP UP)",0);
                if(SkLv(Level,1)) PrintXY(27,16,(unsigned char*)"2:Shl(DP UP)",0);
                if(SkLv(Level,2)) PrintXY(27,24,(unsigned char*)"3:Clm(FAP-)",0);
                if(SkLv(Level,3)) PrintXY(27,32,(unsigned char*)"4:Diz(FDP-)",0);
                if(skill[4] || skill[5] || skill[6] || skill[7]) PrintXY(27,40,(unsigned char*)"0:Next Page",0);
                Bdisp_PutDisp_DD();
                k=0;
                while(k<=0)
                {
                    if(IsKeyDown(KEY_CHAR_0) && (skill[4] || skill[5] || skill[6] || skill[7]))
                    {
                        k=-1-k;
                        if(k==0)
                        {
                            PopUpWin(4);
                            if(SkLv(Level,0)) PrintXY(27,8,(unsigned char*)"1:Gut(AP UP)",0);
                            if(SkLv(Level,1)) PrintXY(27,16,(unsigned char*)"2:Shl(DP UP)",0);
                            if(SkLv(Level,2)) PrintXY(27,24,(unsigned char*)"3:Clm(FAP-)",0);
                            if(SkLv(Level,3)) PrintXY(27,32,(unsigned char*)"4:Diz(FDP-)",0);
                        }
                        else
                        {
                            PopUpWin(5);
                            if(skill[4]) PrintXY(27,8,(unsigned char*)"5:Hle(StatH)",0);
                            if(skill[5]) PrintXY(27,16,(unsigned char*)"6:Skill 6",0);
                            if(skill[6]) PrintXY(27,24,(unsigned char*)"7:Skill 7",0);
                            if(skill[7]) PrintXY(27,32,(unsigned char*)"8:Skill 8",0);
                            PrintXY(27,40,(unsigned char*)"0:Prev Page",0);
                        }
                        Bdisp_PutDisp_DD();
                        while(IsKeyDown(KEY_CHAR_0))
                        {
                            Sleep(50);
                        }
                    }
                    for(t=1;t<=8;t++)
                        if(IsKeyDown(KEY_CHAR_0+t) && skill[t-1]) k=t;
                    if(IsKeyDown(KEY_CTRL_EXIT)) break;
                    Sleep(50);
                }
                RestoreDisp(SAVEDISP_PAGE1);
                if(k>0)
                {
                    PrintMini(8,36,(unsigned char*)"                            ",MINI_OVER);
                    PrintXY(21,44,(unsigned char*)"              ",0);
                    PrintXY(21,52,(unsigned char*)"              ",0);
                }
                if(k==1)
                {
                    MAP+=SkLv(Level,0)+1;
                    if(MAP>SkSt(Level,0)) MAP=SkSt(Level,0);
                    sprintf(str,"AP %3u+%2u",AP,MAP);
                    PrintXY(5,18,(unsigned char*)str,0);
                    SaveDisp(SAVEDISP_PAGE1);
                    PopUpWin(3);
                    sprintf(str,"AP+%u  Max:%2u",SkLv(Level,0)+1,SkSt(Level,0));
                    PrintXY(27,16,(unsigned char*)str,0);
                    PrintXY(27,24,(unsigned char*)"Skill used:",0);
                    sprintf(str,"%2u/%2u",MAP,SkSt(Level,0));
                    PrintXY(69,32,(unsigned char*)str,0);
                }
                else if(k==2)
                {
                    MDP+=SkLv(Level,1)+1;
                    if(MDP>SkSt(Level,1)) MDP=SkSt(Level,1);
                    sprintf(str,"DP %3u+%2u",DP,MDP);
                    PrintXY(5,26,(unsigned char*)str,0);
                    SaveDisp(SAVEDISP_PAGE1);
                    PopUpWin(3);
                    sprintf(str,"DP+%u  Max:%2u",SkLv(Level,1)+1,SkSt(Level,1));
                    PrintXY(27,16,(unsigned char*)str,0);
                    PrintXY(27,24,(unsigned char*)"Skill used:",0);
                    sprintf(str,"%2u/%2u",MDP,SkSt(Level,1));
                    PrintXY(69,32,(unsigned char*)str,0);
                }
                else if(k==3)
                {
                    FMAP+=SkLv(Level,2)+1;
                    if(FMAP>SkSt(Level,2)) FMAP=SkSt(Level,2);
                    sprintf(str,"AP %3d",80-FMAP);
                    PrintMini(68,27,(unsigned char*)str,0);
                    SaveDisp(SAVEDISP_PAGE1);
                    PopUpWin(3);
                    sprintf(str,"FAP-%u Max:%2u",SkLv(Level,2)+1,SkSt(Level,2));
                    PrintXY(27,16,(unsigned char*)str,0);
                    PrintXY(27,24,(unsigned char*)"Skill used:",0);
                    sprintf(str,"%2u/%2u",FMAP,SkSt(Level,2));
                    PrintXY(69,32,(unsigned char*)str,0);
                }
                else if(k==4)
                {
                    FMDP+=SkLv(Level,3)+1;
                    if(FMDP>SkSt(Level,3)) FMDP=SkSt(Level,3);
                    sprintf(str,"DP %3d",5-FMDP);
                    PrintMini(101,27,(unsigned char*)str,0);
                    SaveDisp(SAVEDISP_PAGE1);
                    PopUpWin(3);
                    sprintf(str,"FDP-%u Max:%2u",SkLv(Level,3)+1,SkSt(Level,3));
                    PrintXY(27,16,(unsigned char*)str,0);
                    PrintXY(27,24,(unsigned char*)"Skill used:",0);
                    sprintf(str,"%2u/%2u",FMDP,SkSt(Level,3));
                    PrintXY(69,32,(unsigned char*)str,0);
                }
                if(k>0)
                {
                    Bdisp_PutDisp_DD();
                    for(i=0;i<7;i++)
                    {
                        if(IsKeyUp(KEY_CTRL_EXE)) break;
                        Sleep(50);
                    }
                    while(IsKeyUp(KEY_CTRL_EXE))
                    {
                        Sleep(50);
                    }
                }
                RestoreDisp(SAVEDISP_PAGE1);
                PrintMini(51,36,(unsigned char*)"F2:SKILL",MINI_OVER);
                Bdisp_PutDisp_DD();
            }
            else if(IsKeyDown(KEY_CTRL_F3))
            {
            }
    
            if(FHP[0]+FHP[1]+FHP[2]+FHP[3]+FHP[4]+FHP[5]==0) break;
            if(k>0)
            {
                PrintMini(8,36,(unsigned char*)"                            ",MINI_OVER);
                PrintXY(12,38,(unsigned char*)"Press [EXE] Right",0);
                PrintXY(12,46,(unsigned char*)"Before being hit.",0);
                for(i=5;i>=0;i--)
                {
                    PrintXY(114,46,(unsigned char*)" 0",0);
                    if(FHP[i]==0) continue;
                    damage=SpDam(80-FMAP,DP+MDP);
                    Bdisp_AreaReverseVRAM(65+21*(i%3),9+8*(i/3),84+21*(i%3),15+8*(i/3));
                    Bdisp_AreaReverseVRAM(66+21*(i%3),10+8*(i/3),83+21*(i%3),14+8*(i/3));
                    for(k=120;k>32;k-=2)
                    {
                        PrintXY(k,54,(unsigned char*)"< ",0);
                        PrintXY(8,54,(unsigned char*)"C ",0);
                        Bdisp_PutDisp_DD();
                        Sleep(20+4*i);
                    }
                    for(j=0;j<99;j++)
                    {
                        PrintXY(8,54,(unsigned char*)"C ",0);
                        sprintf(str,"%2d",j);
                        PrintXY(114,46,(unsigned char*)str,0);
                        t=0;
                        for(k=32;k>=12;k-=2)
                        {
                            PrintXY(k,54,(unsigned char*)"< ",0);
                            if(IsKeyDown(KEY_CTRL_EXE))
                            {
                                if(k>=14) t++;
                                else if(t==0)
                                {
                                    t=2;
                                    break;
                                }
                            }
                            Bdisp_PutDisp_DD();
                            Sleep(20+4*i);
                        }
                        if(t==2) break;
                        Sleep(400);
                    }
                    Bdisp_AreaReverseVRAM(1,9,63,33);
                    damage*=(1.0+0.1*j);
                    if(damage>HP) damage=HP;
                    HP-=damage;
                    t=(int)(HP+damage)-(int)HP;
                    sprintf(str,"HP %6u",(int)HP);
                    PrintXY(5,10,(unsigned char*)str,1);
                    sprintf(str,"-%d",t);
                    PrintXY(24,54,(unsigned char*)str,0);
                    Bdisp_PutDisp_DD();
                    while(IsKeyDown(KEY_CTRL_EXE))
                    {
                        Sleep(50);
                    }
                    while(IsKeyUp(KEY_CTRL_EXE))
                    {
                        Sleep(50);
                    }
                    if(HP<1) break;
                    Bdisp_AreaReverseVRAM(1,9,63,33);
                    PrintXY(24,54,(unsigned char*)"       ",0);
                    Bdisp_AreaReverseVRAM(65+21*(i%3),9+8*(i/3),84+21*(i%3),15+8*(i/3));
                    Bdisp_AreaReverseVRAM(66+21*(i%3),10+8*(i/3),83+21*(i%3),14+8*(i/3));
                }
                if(HP<1) break;
                PrintXY(12,38,(unsigned char*)"                 ",0);
                PrintXY(12,46,(unsigned char*)"                   ",0);
                PrintXY(8,54,(unsigned char*)"  ",0);
                PrintMini(8,36,(unsigned char*)"F1:ATTACK  F2:SKILL  F3:ITEM",MINI_OVER);
                damage=SpDam(AP+MAP,5-FMDP);
                if(damage>999999.999) damage=999999.999;
                sprintf(str,"You:%6.0f%c%c%c",damage,0xA9,0xE6,0x40);
                PrintXY(27,44,(unsigned char*)str,0);
                damage=SpDam(80-FMAP,DP+MDP);
                if(damage>999999.999) damage=999999.999;
                sprintf(str,"Foe:%6.0f%c%c%c",damage,0xA9,0xE6,0x40);
                PrintXY(27,52,(unsigned char*)str,0);
                Bdisp_PutDisp_DD();
                k=0;
            }
            rand();
        }

        if(HP>=1)
        {
            Bdisp_AllClr_DDVRAM();
            k=rand()%4;
            if(k<3) k=2;
    
            PrintXY(18,9,(unsigned char*)"Ex.pts   871247",0);
            PrintXY(18,24,(unsigned char*)"Coin      12531",0);

            Stage++;
            PrintXY(30,39,(unsigned char*)"You cleared",0);
            PrintXY(33,47,(unsigned char*)"Sqir Guys!",0);
            x_axis=61;
            y_axis=40;

            EXP+=871247;
            Coin+=12531;
            if(Coin>2500000) Coin=2500000;
            Bdisp_PutDisp_DD();
            while(IsKeyDown(KEY_CTRL_EXE))
            {
                Sleep(50);
            }
            while(IsKeyUp(KEY_CTRL_EXE))
            {
                Sleep(50);
            }
            if(EXP>=MEXP(Level))
            {
                EXP-=MEXP(Level);
                LevelUp();
            }
            Refresh();
            PrintXY(61,40,(unsigned char*)"C",0);
            Bdisp_PutDisp_DD();
            Sleep(2000);
            SaveDisp(SAVEDISP_PAGE1);
            PopUpWin(3);
            PrintXY(18,16,(unsigned char*)"You dug and got",0);
            PrintXY(18,24,(unsigned char*)"the first piece",0);
            PrintXY(18,32,(unsigned char*)"of Fort-Stone.",0);
            Bdisp_PutDisp_DD();
            Sleep(500);
            while(IsKeyDown(KEY_CTRL_EXE))
            {
                Sleep(50);
            }
            while(IsKeyUp(KEY_CTRL_EXE))
            {
                Sleep(50);
            }
            RestoreDisp(SAVEDISP_PAGE1);
            Bdisp_PutDisp_DD();
            Sleep(1250);
            PopUpWin(5);
            PrintXY(18,8,(unsigned char*)"Will five of",0);
            PrintXY(18,16,(unsigned char*)"these pieces",0);
            PrintXY(18,24,(unsigned char*)"actually brings",0);
            PrintXY(18,32,(unsigned char*)"peace to the",0);
            PrintXY(18,40,(unsigned char*)"world?",0);
            Bdisp_PutDisp_DD();
            Sleep(500);
            while(IsKeyDown(KEY_CTRL_EXE))
            {
                Sleep(50);
            }
            while(IsKeyUp(KEY_CTRL_EXE))
            {
                Sleep(50);
            }
            RestoreDisp(SAVEDISP_PAGE1);
            Bdisp_PutDisp_DD();
            Sleep(1600);
            for(i=0;i<56;i++)
            {
                RestoreDisp(SAVEDISP_PAGE1);
                PrintXY(122-i,40,(unsigned char*)"7",0);
                Bdisp_PutDisp_DD();
                Sleep(24);
            }
            Sleep(500);
            PopUpWin(3);
            PrintXY(18,16,(unsigned char*)"Sqir Guy 7:",0);
            PrintXY(18,24,(unsigned char*)"Hey, everybody!",0);
            PrintXY(18,32,(unsigned char*)"What about me?",0);
            Bdisp_PutDisp_DD();
            while(IsKeyDown(KEY_CTRL_EXE))
            {
                Sleep(50);
            }
            while(IsKeyUp(KEY_CTRL_EXE))
            {
                Sleep(50);
            }
            Battle(5000,48,24,211,73665,500,7);
        }
        work=0;
        Refresh();
    }
}

int compareitem(const void *a, const void *b)
{
    unsigned char x=*(unsigned char *)a;
    unsigned char y=*(unsigned char *)b;
    if(x>y) return 1;
    else if(x<y) return -1;
    else return 0;
}

void menu(int mitem)
{
    int i,j,t;
    int k=mitem;
    while(1)
    {
        Bdisp_AllClr_DDVRAM();
        PrintXY(33,3,(unsigned char*)"Pause Menu",0);
        sprintf(str,"Lv %3u",Level);
        PrintXY(8,19,(unsigned char*)str,0);
        sprintf(str,"HP %3u%%",(int)((100*HP+0.0001)/MHP));
        PrintXY(8,27,(unsigned char*)str,0);
        sprintf(str,"AP %3u",AP);
        PrintXY(8,35,(unsigned char*)str,0);
        sprintf(str,"DP %3u",DP);
        PrintXY(8,43,(unsigned char*)str,0);
        i=100*EXP/MEXP(Level);
        if(i<0) i=0;
        if(i>100) i=100;
        sprintf(str,"EXP%3u%%",i);
        PrintXY(8,51,(unsigned char*)str,0);
        PrintXY(78,19,(unsigned char*)"ITEMS",0);
        PrintXY(78,27,(unsigned char*)"STATS",0);
        PrintXY(78,35,(unsigned char*)"SKILLS",0);
        PrintXY(78,43,(unsigned char*)"OPTIONS",0);
        PrintXY(78,51,(unsigned char*)"RECOVER",0);
        sprintf(str,"%c%c",0xE6,0x9B);
        PrintXY(72,8*k+19,(unsigned char*)str,0);
        Bdisp_PutDisp_DD();
        while(IsKeyDown(KEY_CTRL_EXIT) || IsKeyDown(KEY_CTRL_EXE))
        {
            Sleep(50);
        }
        do
        {
            GetKeyWait(KEYWAIT_HALTON_TIMEROFF,0,1,&key);
            if(IsKeyDown(KEY_CTRL_DOWN) && k<4)
            {
                PrintXY(72,8*k+19,(unsigned char*)" ",0);
                k++;
                sprintf(str,"%c%c",0xE6,0x9B);
                PrintXY(72,8*k+19,(unsigned char*)str,0);
                Bdisp_PutDisp_DD();
            }
            if(IsKeyDown(KEY_CTRL_UP) && k>0)
            {
                PrintXY(72,8*k+19,(unsigned char*)" ",0);
                k--;
                sprintf(str,"%c%c",0xE6,0x9B);
                PrintXY(72,8*k+19,(unsigned char*)str,0);
                Bdisp_PutDisp_DD();
            }
            if(IsKeyDown(KEY_CTRL_EXIT)) key=KEY_CTRL_EXIT;
            if(IsKeyDown(KEY_CTRL_EXE)) key=KEY_CTRL_EXE;
        }while(key!=KEY_CTRL_EXIT && key!=KEY_CTRL_EXE);
        if(key==KEY_CTRL_EXIT) break;
        Bdisp_AllClr_DDVRAM();
        if(k==0)
        {
            sprintf(str,"HP:%6u/%6u",(int)HP,(int)MHP);
            PrintXY(0,0,(unsigned char*)str,0);
            sprintf(str,"(%3u%%)",(int)((HP*100+0.0001)/MHP));
            PrintMini(101,2,(unsigned char*)str,MINI_OVER);
            for(t=0;t<10;t++)
            {
                if(item[t])
                {
                    if(item[t]<=20) sprintf(str,"HP+%u",HPI[item[t]-1]);
                    else if(item[t]<=40) sprintf(str,"Charge+%u",4*item[t]-80);
                    else strcpy(str,Iname[item[t]-41]);
                    PrintXY((t/5)*64+4,(t%5)*8+8,(unsigned char*)str,0);
                }
            }
            PrintXY(20,48,(unsigned char*)"Sort",0);
            PrintXY(84,48,(unsigned char*)"Move",0);
            if(item[10]>0)
            {
                sprintf(str,"Absorb-%u",1<<item[10]-1);
                PrintXY(2,56,(unsigned char*)str,0);
            }
            Bdisp_AreaReverseVRAM(0,8,63,15);
            Bdisp_PutDisp_DD();
            k=0;
            t=0;
            do
            {
                GetKeyWait(KEYWAIT_HALTON_TIMEROFF,0,1,&key);
                if(IsKeyDown(KEY_CTRL_RIGHT) && k==0)
                {
                    Bdisp_AreaReverseVRAM(0,8*t+8,63,8*t+15);
                    k=1;
                    Bdisp_AreaReverseVRAM(64,8*t+8,127,8*t+15);
                    Bdisp_PutDisp_DD();
                }
                if(IsKeyDown(KEY_CTRL_LEFT) && k==1)
                {
                    Bdisp_AreaReverseVRAM(64,8*t+8,127,8*t+15);
                    k=0;
                    Bdisp_AreaReverseVRAM(0,8*t+8,63,8*t+15);
                    Bdisp_PutDisp_DD();
                }
                if(IsKeyDown(KEY_CTRL_UP) && t>0)
                {
                    Bdisp_AreaReverseVRAM(64*k,8*t+8,64*k+63,8*t+15);
                    t--;
                    Bdisp_AreaReverseVRAM(64*k,8*t+8,64*k+63,8*t+15);
                    Bdisp_PutDisp_DD();
                }
                if(IsKeyDown(KEY_CTRL_DOWN) && t<6)
                {
                    Bdisp_AreaReverseVRAM(64*k,8*t+8,64*k+63,8*t+15);
                    t++;
                    Bdisp_AreaReverseVRAM(64*k,8*t+8,64*k+63,8*t+15);
                    Bdisp_PutDisp_DD();
                }
                if(IsKeyDown(KEY_CTRL_F1))
                {
                    if(t<5)
                        if(item[5*k+t]) itemhelp(item[5*k+t],0);
                    else if(t==6)
                        if(item[10+k]) itemhelp(-item[10+k],0);
                }
                if(IsKeyDown(KEY_CTRL_EXIT)) key=KEY_CTRL_EXIT;
                if(IsKeyDown(KEY_CTRL_EXE))
                {
                    if(t<5)
                    {
                        if(item[5*k+t] && item[5*k+t]<=20)
                        {
                            SaveDisp(SAVEDISP_PAGE1);
                            if(MHP-HP>=(double)effitem*HPI[item[5*k+t]-1]/1000)
                            {
                                PopUpWin(2);
                                PrintXY(21,16,(unsigned char*)"Use this item?",0);
                                PrintXY(21,24,(unsigned char*)"1:Yes     2:No",0);
                                Bdisp_PutDisp_DD();
                            }
                            else
                            {
                                PopUpWin(4);
                                PrintXY(21,8,(unsigned char*)"It has little",0);
                                PrintXY(21,16,(unsigned char*)"effect.",0);
                                PrintXY(21,24,(unsigned char*)"Use it anyway?",0);
                                PrintXY(21,32,(unsigned char*)"1:Yes     2:No",0);
                                Bdisp_PutDisp_DD();
                            }
                            for(key=0;key==0;)
                            {
                                GetKeyWait(KEYWAIT_HALTON_TIMEROFF,0,1,&key);
                                if(IsKeyDown(KEY_CHAR_1)) key=1;
                                if(IsKeyDown(KEY_CHAR_2) || IsKeyDown(KEY_CTRL_EXIT)) key=2;
                            }
                            if(key==1)
                            {
                                RestoreDisp(SAVEDISP_PAGE1);
                                HP+=HPI[item[5*k+t]-1];
                                if(HP>MHP) HP=MHP;
                                item[5*k+t]=0;
                                PrintXY(k*64+4,t*8+8,(unsigned char*)"         ",1);
                                sprintf(str,"HP:%6u/%6u",(int)HP,(int)MHP);
                                PrintXY(0,0,(unsigned char*)str,0);
                                sprintf(str,"(%3u%%)",(int)((HP*100+0.0001)/MHP));
                                PrintMini(101,2,(unsigned char*)str,MINI_OVER);
                            }
                            else RestoreDisp(SAVEDISP_PAGE1);
                            Bdisp_PutDisp_DD();
                        }
                        else if(item[5*k+t]>40 && item[5*k+t]<50)
                        {
                            SaveDisp(SAVEDISP_PAGE1);
                            if(status==1 && item[5*k+t]==41 || status==item[5*k+t]-39)
                            {
                                PopUpWin(2);
                                PrintXY(21,16,(unsigned char*)"Use this item?",0);
                                PrintXY(21,24,(unsigned char*)"1:Yes     2:No",0);
                                Bdisp_PutDisp_DD();
                            }
                            else
                            {
                                PopUpWin(3);
                                PrintXY(13,16,(unsigned char*)"It has no effect.",0);
                                PrintXY(13,24,(unsigned char*)"Use it anyway?",0);
                                PrintXY(13,32,(unsigned char*)"1:Yes       2:No",0);
                                Bdisp_PutDisp_DD();
                            }
                            for(key=0;key==0;)
                            {
                                GetKeyWait(KEYWAIT_HALTON_TIMEROFF,0,1,&key);
                                if(IsKeyDown(KEY_CHAR_1)) key=1;
                                if(IsKeyDown(KEY_CHAR_2) || IsKeyDown(KEY_CTRL_EXIT)) key=2;
                            }
                            if(key==1)
                            {
                                RestoreDisp(SAVEDISP_PAGE1);
                                PrintXY(k*64+4,t*8+8,(unsigned char*)"         ",1);
                                SaveDisp(SAVEDISP_PAGE1);
                                if(status==2 && item[5*k+t]==41)
                                {
                                    PopUpWin(3);
                                    PrintXY(24,16,(unsigned char*)"The effect of",0);
                                    PrintXY(24,24,(unsigned char*)"Poison Status",0);
                                    PrintXY(24,32,(unsigned char*)"was weakened.",0);
                                    status=1;
                                }
                                else if(status==1 && item[5*k+t]==41)
                                {
                                    PopUpWin(2);
                                    PrintXY(21,16,(unsigned char*)"You were cured",0);
                                    PrintXY(21,24,(unsigned char*)"of Poison.",0);
                                    status=0;
                                }
                                else if(status==3 && item[5*k+t]==42)
                                {
                                    PopUpWin(2);
                                    PrintXY(21,16,(unsigned char*)"You overcomed",0);
                                    PrintXY(21,24,(unsigned char*)"Grassd Status.",0);
                                    status=0;
                                }
                                else if(status==4 && item[5*k+t]==43)
                                {
                                    PopUpWin(2);
                                    PrintXY(21,16,(unsigned char*)"Your Shivering",0);
                                    PrintXY(21,24,(unsigned char*)"calmed down.",0);
                                    status=0;
                                }
                                else if(status==5 && item[5*k+t]==44)
                                {
                                    PopUpWin(2);
                                    PrintXY(21,16,(unsigned char*)"You cooled off",0);
                                    PrintXY(21,24,(unsigned char*)"Burned Status.",0);
                                    status=0;
                                }
                                else if(status==6 && item[5*k+t]==45)
                                {
                                    PopUpWin(2);
                                    PrintXY(21,16,(unsigned char*)"You were cured",0);
                                    PrintXY(21,24,(unsigned char*)"of Paralysis.",0);
                                    status=0;
                                }
                                else if(status==7 && item[5*k+t]==46)
                                {
                                    PopUpWin(2);
                                    PrintXY(13,16,(unsigned char*)"You got over from",0);
                                    PrintXY(13,24,(unsigned char*)"Shrink Status.",0);
                                    status=0;
                                }
                                else
                                {
                                    PopUpWin(1);
                                    PrintXY(13,24,(unsigned char*)"Nothing happened.",0);
                                }
                                item[5*k+t]=0;
                                Bdisp_PutDisp_DD();
                                do
                                {
                                    GetKeyWait(KEYWAIT_HALTON_TIMEROFF,0,1,&key);
                                }while(IsKeyUp(KEY_CTRL_EXIT) && IsKeyUp(KEY_CTRL_EXE));
                                RestoreDisp(SAVEDISP_PAGE1);
                            }
                            else RestoreDisp(SAVEDISP_PAGE1);
                            Bdisp_PutDisp_DD();
                        }
                    }
                    else if(t==5)
                    {
                        if(k==0)
                        {
                            for(i=0;i<10;i++)
                                if(item[i]==0) item[i]=255;
                            qsort(item,10,sizeof(char),compareitem);
                            for(i=0;i<10;i++)
                            {
                                PrintXY((i/5)*64+4,(i%5)*8+8,(unsigned char*)"         ",0);
                                if(item[i]==255) item[i]=0;
                                else
                                {
                                    if(item[i]<=20) sprintf(str,"HP+%u",HPI[item[i]-1]);
                                    else if(item[i]<=40) sprintf(str,"Charge+%u",4*item[i]-80);
                                    else strcpy(str,Iname[item[i]-41]);
                                    PrintXY((i/5)*64+4,(i%5)*8+8,(unsigned char*)str,0);
                                }
                            }
                            Bdisp_PutDisp_DD();
                        }
                        else
                        {
                            i=0;
                            do
                            {
                                GetKeyWait(KEYWAIT_HALTON_TIMEROFF,0,1,&key);
                                if(IsKeyDown(KEY_CTRL_DOWN) && i<9)
                                {
                                    i++;
                                }
                                if(IsKeyDown(KEY_CTRL_UP) && i>0)
                                {
                                    i--;
                                }
                                if(IsKeyDown(KEY_CTRL_RIGHT) && i<5)
                                {
                                    i+=5;
                                }
                                if(IsKeyDown(KEY_CTRL_LEFT) && i>=5)
                                {
                                    i-=5;
                                }
                            }while(IsKeyUp(KEY_CTRL_EXE));
                        }
                    }
                }
            }while(key!=KEY_CTRL_EXIT);
            k=0;
        }
        else if(k==1)
        {
            sprintf(str,"Lv%3d",Level);
            PrintXY(0,0,(unsigned char*)str,0);
            PrintXY(37,0,(unsigned char*)"A",1);
            sprintf(str,"%3d",AP);
            PrintXY(43,0,(unsigned char*)str,0);
            PrintXY(67,0,(unsigned char*)"D",1);
            sprintf(str,"%3d",DP);
            PrintXY(73,0,(unsigned char*)str,0);
            PrintXY(97,0,(unsigned char*)"S",1);
            sprintf(str,"%3d",Speed());
            PrintXY(103,0,(unsigned char*)str,0);
            sprintf(str,"HP:%14.7f",HP);
            PrintXY(0,8,(unsigned char*)str,0);
            sprintf(str,"(%3d%%)",(int)((100*HP+0.0001)/MHP));
            PrintMini(104,10,(unsigned char*)str,MINI_OVER);
            sprintf(str,"EXP:%8d/%8d",EXP,MEXP(Level));
            PrintXY(0,16,(unsigned char*)str,0);
            sprintf(str,"Place %-3d   Stage %d",Place,Stage);
            PrintXY(0,24,(unsigned char*)str,0);
            sprintf(str,"Coin %-7d Star %d",Coin,Star);
            PrintXY(0,32,(unsigned char*)str,0);
            PrintXY(0,42,(unsigned char*)"Critical",0);
            PrintMini(54,40,(unsigned char*)"RATIO:",MINI_OVER);
            PrintMini(54,46,(unsigned char*)"DAMAGE:",MINI_OVER);
            sprintf(str,"%3d%%",criRat(Level));
            PrintMini(88,40,(unsigned char*)str,MINI_OVER);
            sprintf(str,"+%3d%%",criDam(Level));
            PrintMini(84,46,(unsigned char*)str,MINI_OVER);
            if(status==0) PrintXY(0,52,(unsigned char*)"Status:Normal",0);
            else if(status==1 || status==2) PrintXY(0,52,(unsigned char*)"Status:Poison",0);
            else if(status==3) PrintXY(0,52,(unsigned char*)"Status:Grassd",0);
            else if(status==4) PrintXY(0,52,(unsigned char*)"Status:Shiver",0);
            else if(status==5) PrintXY(0,52,(unsigned char*)"Status:Burn",0);
            else if(status==6) PrintXY(0,52,(unsigned char*)"Status:Paralyzed",0);
            else if(status==7) PrintXY(0,52,(unsigned char*)"Status:Shrink",0);

            Bdisp_PutDisp_DD();
            do
            {
                GetKeyWait(KEYWAIT_HALTON_TIMEROFF,0,1,&key);
            }while(IsKeyUp(KEY_CTRL_EXIT) && IsKeyUp(KEY_CTRL_EXE));
            k=1;
        }
        else if(k==2)
        {
            rank[10]=0;
            do{
                t=0;
                if(SkLv(Level,0))
                {
                    sprintf(str,"Gut: Lv %1d Gauge %3d",SkLv(Level,0),SkSt(Level,0));
                    PrintXY(6,8*t,(unsigned char*)str,0);
                    rank[t++]=0;
                }
                if(SkLv(Level,1))
                {
                    sprintf(str,"Shl: Lv %1d Gauge %3d",SkLv(Level,1),SkSt(Level,1));
                    PrintXY(6,8*t,(unsigned char*)str,0);
                    rank[t++]=1;
                }
                if(SkLv(Level,2))
                {
                    sprintf(str,"Clm: Lv %1d Gauge %3d",SkLv(Level,2),SkSt(Level,2));
                    PrintXY(6,8*t,(unsigned char*)str,0);
                    rank[t++]=2;
                }
                if(SkLv(Level,3))
                {
                    sprintf(str,"Diz: Lv %1d Gauge %3d",SkLv(Level,3),SkSt(Level,3));
                    PrintXY(6,8*t,(unsigned char*)str,0);
                    rank[t++]=3;
                }
                if(skill[4]>0)
                {
                    sprintf(str,"Hle: Lv %1d Gauge %1d/%1d",skill[4]/100,(skill[4]%100)/10,skill[4]%10);
                    PrintXY(6,8*t,(unsigned char*)str,0);
                    rank[t++]=4;
                }
                if(skill[5]>0)
                {
                    sprintf(str,"Sk6: Lv %1d Gauge %1d/%1d",skill[5]/100,(skill[5]%100)/10,skill[5]%10);
                    PrintXY(6,8*t,(unsigned char*)str,0);
                    rank[t++]=5;
                }
                if(skill[6]>0)
                {
                    sprintf(str,"Sk7: Lv %1d Gauge %1d/%1d",skill[6]/100,(skill[6]%100)/10,skill[6]%10);
                    PrintXY(6,8*t,(unsigned char*)str,0);
                    rank[t++]=6;
                }
                if(skill[7]>0)
                {
                    sprintf(str,"Sk8: Lv %1d Gauge %1d/%1d",skill[7]/100,(skill[7]%100)/10,skill[7]%10);
                    PrintXY(6,8*t,(unsigned char*)str,0);
                    rank[t++]=7;
                }
                if(t==0)
                {
                    PrintXY(12,23,(unsigned char*)"You don't have",0);
                    PrintXY(57,33,(unsigned char*)"any Skills",0);
                    Bdisp_PutDisp_DD();
                    GetKeyWait(KEYWAIT_HALTON_TIMEROFF,0,1,&key);
                    rank[10]=9;
                }
                else
                {
                    Bdisp_AreaReverseVRAM(0,8*rank[10],127,7+8*rank[10]);
                    Bdisp_PutDisp_DD();
                    while(1)
                    {
                        GetKeyWait(KEYWAIT_HALTON_TIMEROFF,0,1,&key);
                        if(IsKeyDown(KEY_CTRL_UP) && rank[10]>0)
                        {
                            rank[10]--;
                            Bdisp_AreaReverseVRAM(0,8*rank[10],127,15+8*rank[10]);
                            Bdisp_PutDisp_DD();
                        }
                        if(IsKeyDown(KEY_CTRL_DOWN) && rank[10]<t-1)
                        {
                            Bdisp_AreaReverseVRAM(0,8*rank[10],127,15+8*rank[10]);
                            Bdisp_PutDisp_DD();
                            rank[10]++;
                        }
                        if(IsKeyDown(KEY_CTRL_EXIT))
                        {
                            rank[10]=9;
                            break;
                        }
                        if(IsKeyDown(KEY_CTRL_EXE))
                        {
                            SaveDisp(SAVEDISP_PAGE1);
                            Bdisp_AllClr_DDVRAM();
                            Bdisp_DrawLineVRAM(7,12,120,12);
                            Bdisp_DrawLineVRAM(7,35,120,35);
                            Bdisp_DrawLineVRAM(7,12,7,35);
                            Bdisp_DrawLineVRAM(120,12,120,35);
                            PrintMini(41,10,(unsigned char*)"DISCRIPTION",MINI_OVER);
                            Bdisp_DrawLineVRAM(7,42,120,42);
                            Bdisp_DrawLineVRAM(7,55,120,55);
                            Bdisp_DrawLineVRAM(7,42,7,55);
                            Bdisp_DrawLineVRAM(120,42,120,55);
                            PrintMini(54,40,(unsigned char*)"USAGE",MINI_OVER);
                            if(rank[rank[10]]==0)
                            {
                                sprintf(str,"Gut: Lv %1d Gauge %3d",SkLv(Level,0),SkSt(Level,0));
                                PrintXY(6,0,(unsigned char*)str,0);
                                PrintXY(13,16,(unsigned char*)"Increases your AP",0);
                                PrintXY(13,24,(unsigned char*)"by Skill Level.",0);
                            }
                            if(rank[rank[10]]==1)
                            {
                                sprintf(str,"Shl: Lv %1d Gauge %3d",SkLv(Level,1),SkSt(Level,1));
                                PrintXY(6,0,(unsigned char*)str,0);
                                PrintXY(13,16,(unsigned char*)"Increases your DP",0);
                                PrintXY(13,24,(unsigned char*)"by Skill Level.",0);
                            }
                            if(rank[rank[10]]==2)
                            {
                                sprintf(str,"Clm: Lv %1d Gauge %3d",SkLv(Level,2),SkSt(Level,2));
                                PrintXY(6,0,(unsigned char*)str,0);
                                PrintXY(10,16,(unsigned char*)"Decreases Foe's AP",0);
                                PrintXY(10,24,(unsigned char*)"by Skill Level.",0);
                            }
                            if(rank[rank[10]]==3)
                            {
                                sprintf(str,"Diz: Lv %1d Gauge %3d",SkLv(Level,3),SkSt(Level,3));
                                PrintXY(6,0,(unsigned char*)str,0);
                                PrintXY(10,16,(unsigned char*)"Decreases Foe's DP",0);
                                PrintXY(10,24,(unsigned char*)"by Skill Level.",0);
                            }
                            if(rank[rank[10]]==4)
                            {
                                sprintf(str,"Hle: Lv %1d Gauge %1d/%1d",skill[4]/100,(skill[4]%100)/10,skill[4]%10);
                                PrintXY(6,0,(unsigned char*)str,0);
                                PrintXY(19,16,(unsigned char*)"Recovers status",0);
                                PrintXY(19,24,(unsigned char*)"abnormalities.",0);
                            }
                            if(rank[rank[10]]==5)
                            {
                                sprintf(str,"Sk6: Lv %1d Gauge %1d/%1d",skill[5]/100,(skill[5]%100)/10,skill[5]%10);
                                PrintXY(6,0,(unsigned char*)str,0);
                            }
                            if(rank[rank[10]]==6)
                            {
                                sprintf(str,"Sk7: Lv %1d Gauge %1d/%1d",skill[6]/100,(skill[6]%100)/10,skill[6]%10);
                                PrintXY(6,0,(unsigned char*)str,0);
                            }
                            if(rank[rank[10]]==7)
                            {
                                sprintf(str,"Sk8: Lv %1d Gauge %1d/%1d",skill[7]/100,(skill[7]%100)/10,skill[7]%10);
                                PrintXY(6,0,(unsigned char*)str,0);
                            }
                            if(rank[rank[10]]<4)
                                PrintXY(22,46,(unsigned char*)"Only in battle",0);
                            else
                            {
                                PrintXY(25,46,(unsigned char*)"Battle / Menu",0);
                                PrintMini(11,57,(unsigned char*)"PRESS F6 TO USE THIS SKILL.",MINI_OVER);
                            }
                            Bdisp_PutDisp_DD();
                            while(IsKeyUp(KEY_CTRL_EXIT))
                            {
                                GetKeyWait(KEYWAIT_HALTON_TIMEROFF,0,1,&key);
                            }
                            k=0;
                            Bdisp_AllClr_DDVRAM();
                            break;
                        }
                    }
                }
            }while(rank[10]<9);
            k=2;
        }
        else if(k==3)
        {
            i=0;
            PrintXY(4,6,(unsigned char*)"Min. effect of Item:",0);
            if(effitem==0)
                sprintf(str," %5.1f%%%c%c",.1*effitem,0xE6,0x9B);
            else if(effitem==1000)
                sprintf(str,"%c%c%5.1f%% ",0xE6,0x9A,.1*effitem,0xE6);
            else
                sprintf(str,"%c%c%5.1f%%%c%c",0xE6,0x9A,.1*effitem,0xE6,0x9B);
            PrintXY(70,15,(unsigned char*)str,0);
            PrintXY(19,36,(unsigned char*)"Damage-Calc",0);
            PrintXY(19,44,(unsigned char*)"Change password",0);
            PrintXY(19,52,(unsigned char*)"Save & Quit",0);
            Bdisp_AreaReverseVRAM(0,36,127,43);
            Bdisp_PutDisp_DD();
            while(1)
            {
                Bdisp_PutDisp_DD();
                GetKeyWait(KEYWAIT_HALTON_TIMEROFF,0,1,&key);
                if(IsKeyDown(KEY_CTRL_RIGHT) && effitem<1000)
                {
                    if(effitem>=100) effitem+=10;
                    else if(effitem>=5) effitem+=5;
                    else if(effitem==1) effitem=5;
                    else effitem=1;
                    if(effitem==1000)
                        sprintf(str,"%c%c%5.1f%% ",0xE6,0x9A,.1*effitem,0xE6);
                    else
                        sprintf(str,"%c%c%5.1f%%%c%c",0xE6,0x9A,.1*effitem,0xE6,0x9B);
                    PrintXY(70,15,(unsigned char*)str,0);
                }
                if(IsKeyDown(KEY_CTRL_LEFT) && effitem>0)
                {
                    if(effitem==1) effitem=0;
                    else if(effitem==5) effitem=1;
                    else if(effitem<=100) effitem-=5;
                    else effitem-=10;
                    if(effitem==0)
                        sprintf(str," %5.1f%%%c%c",.1*effitem,0xE6,0x9B);
                    else
                        sprintf(str,"%c%c%5.1f%%%c%c",0xE6,0x9A,.1*effitem,0xE6,0x9B);
                    PrintXY(70,15,(unsigned char*)str,0);
                }
                if(i<2 && IsKeyDown(KEY_CTRL_DOWN))
                {
                    Bdisp_AreaReverseVRAM(0,36+8*i,127,51+8*i);
                    i++;
                }
                if(i>0 && IsKeyDown(KEY_CTRL_UP))
                {
                    i--;
                    Bdisp_AreaReverseVRAM(0,36+8*i,127,51+8*i);
                }
                if(IsKeyDown(KEY_CTRL_EXIT)) break;
                if(IsKeyDown(KEY_CTRL_EXE))
                {
                    SaveDisp(SAVEDISP_PAGE1);
                    if(i==0)
                    {
                        i=j=0;
                        t=0;
                        dam=0;
                        Bdisp_DrawLineVRAM(7,8,121,8);
                        Bdisp_DrawLineVRAM(7,46,121,46);
                        Bdisp_DrawLineVRAM(7,8,7,46);
                        Bdisp_DrawLineVRAM(121,8,121,46);
                        do{
                            Bdisp_AreaClr_VRAM(&cdisp);
                            sprintf(str,"Attacker's AP:%3d",i);
                            PrintXY(13,12,(unsigned char*)str,0);
                            sprintf(str,"Defender's DP:%3d",j);
                            PrintXY(13,20,(unsigned char*)str,0);
                            dam=Damage(i,j);
                            if(dam>999999.999) dam=999999.999;
                            sprintf(str,"Damage:%10.3f",dam);
                            PrintXY(13,36,(unsigned char*)str,0);
                            Bdisp_AreaReverseVRAM(10,12+8*t,118,19+8*t);
                            Bdisp_PutDisp_DD();
                            GetKeyWait(KEYWAIT_HALTON_TIMEROFF,0,1,&key);
                            if(t==0)
                            {
                                for(rank[0]=0;rank[0]<10;rank[0]++)
                                {
                                    if(IsKeyDown(KEY_CHAR_0+rank[0]) && i<100)
                                    {
                                        i=i*10+rank[0];
                                        break;
                                    }
                                }
                                if(IsKeyDown(KEY_CTRL_DEL))
                                    i/=10;
                                if(IsKeyDown(KEY_CTRL_LEFT) && i>0)
                                    i--;
                                if(IsKeyDown(KEY_CTRL_RIGHT) && i<999)
                                    i++;
                            }
                            else
                            {
                                for(rank[0]=0;rank[0]<10;rank[0]++)
                                {
                                    if(IsKeyDown(KEY_CHAR_0+rank[0]) && j<100 && j>=0)
                                    {
                                        j=j*10+rank[0];
                                        break;
                                    }
                                }
                                if(IsKeyDown(KEY_CTRL_DEL))
                                    j/=10;
                                if(IsKeyDown(KEY_CTRL_LEFT) && j>-99)
                                    j--;
                                if(IsKeyDown(KEY_CTRL_RIGHT) && j<999)
                                    j++;
                            }
                            if(IsKeyDown(KEY_CTRL_DOWN) && t==0 || IsKeyDown(KEY_CTRL_UP) && t==1)
                                t=1-t;
                        }while(IsKeyUp(KEY_CTRL_EXIT));
                        i=0;
                    }
                    else if(i==1)
                    {
                        i=0;
                        do
                        {
                            PopUpWin(3);
                            PrintXY(13,16,(unsigned char*)"Enter password of",0);
                            if(dno<10) sprintf(str,"Data 0%u: %u",dno,i);
                            else sprintf(str,"Data %u: %u",dno,i);
                            PrintXY(13,32,(unsigned char*)str,0);
                            do
                            {
                                Bdisp_PutDisp_DD();
                                GetKeyWait(KEYWAIT_HALTON_TIMEROFF,0,1,&key);
                                for(j=0;j<10;j++)
                                    if(IsKeyDown(KEY_CHAR_0+j)) key=KEY_CHAR_0+j;
                                if(key>=KEY_CHAR_0 && key<=KEY_CHAR_9 && 10*i+key-KEY_CHAR_0<=65535)
                                {
                                    i=10*i+key-KEY_CHAR_0;
                                    sprintf(str,"%u",i);
                                    PrintXY(67,32,(unsigned char*)str,0);
                                }
                                if(IsKeyDown(KEY_CTRL_DEL))
                                {
                                    i/=10;
                                    PrintXY(67,32,(unsigned char*)"     ",0);
                                    sprintf(str,"%u",i);
                                    PrintXY(67,32,(unsigned char*)str,0);
                                }
                                if(IsKeyDown(KEY_CTRL_EXE)) key=KEY_CTRL_EXE;
                                if(IsKeyDown(KEY_CTRL_EXIT)) key=KEY_CTRL_EXIT;
                            }while(key!=KEY_CTRL_EXE && key!=KEY_CTRL_EXIT);
                            if(key==KEY_CTRL_EXE)
                            {
                                RestoreDisp(SAVEDISP_PAGE1);
                                if(password==i)
                                {
                                    i=0;
                                    PopUpWin(3);
                                    PrintXY(15,16,(unsigned char*)"New password of",0);
                                    if(dno<10) sprintf(str,"Data 0%u: %u",dno,i);
                                    else sprintf(str,"Data %u: %u",dno,i);
                                    PrintXY(15,32,(unsigned char*)str,0);
                                    do
                                    {
                                        Bdisp_PutDisp_DD();
                                        GetKeyWait(KEYWAIT_HALTON_TIMEROFF,0,1,&key);
                                        for(j=0;j<10;j++)
                                            if(IsKeyDown(KEY_CHAR_0+j)) key=KEY_CHAR_0+j;
                                        if(key>=KEY_CHAR_0 && key<=KEY_CHAR_9 && 10*i+key-KEY_CHAR_0<=65535)
                                        {
                                            i=10*i+key-KEY_CHAR_0;
                                            sprintf(str,"%u",i);
                                            PrintXY(69,32,(unsigned char*)str,0);
                                        }
                                        if(IsKeyDown(KEY_CTRL_DEL))
                                        {
                                            i/=10;
                                            PrintXY(69,32,(unsigned char*)"     ",0);
                                            sprintf(str,"%u",i);
                                            PrintXY(69,32,(unsigned char*)str,0);
                                        }
                                        if(IsKeyDown(KEY_CTRL_EXE))
                                        {
                                            PopUpWin(3);
                                            password=i;
                                            PrintXY(13,24,(unsigned char*)"Password Changed.",0);
                                            Bdisp_PutDisp_DD();
                                            while(IsKeyDown(KEY_CTRL_EXE))
                                            {
                                                Sleep(50);
                                            }
                                            while(IsKeyUp(KEY_CTRL_EXE))
                                            {
                                                GetKeyWait(KEYWAIT_HALTON_TIMEROFF,0,1,&key);
                                            }
                                            break;
                                        }
                                    }while(IsKeyUp(KEY_CTRL_EXIT));
                                    break;
                                }
                                else
                                {
                                    PopUpWin(3);
                                    PrintXY(41,24,(unsigned char*)"Mismatch",0);
                                    Bdisp_PutDisp_DD();
                                    while(IsKeyDown(KEY_CTRL_EXE))
                                    {
                                        Sleep(50);
                                    }
                                    while(IsKeyUp(KEY_CTRL_EXE))
                                    {
                                        GetKeyWait(KEYWAIT_HALTON_TIMEROFF,0,1,&key);
                                    }
                                }
                            }
                        }while(key!=KEY_CTRL_EXIT);
                        i=1;
                    }
                    else
                    {
                        quit=1;
                        return;
                    }
                    RestoreDisp(SAVEDISP_PAGE1);
                }
            }
            k=3;
        }
        else if(k==4)
        {
            if(status==3)
            {
                Bdisp_AllClr_DDVRAM();
                status=0;
                PrintXY(12,22,(unsigned char*)"You were cured of",0);
                PrintXY(21,34,(unsigned char*)"Grassd Status.",0);
                Bdisp_PutDisp_DD();
                Sleep(2750);
            }
            break;
        }
    }
    Refresh();
}

int compare(const void *a, const void *b)
{
    unsigned int *x=(unsigned int *)a;
    unsigned int *y=(unsigned int *)b;
    if(x[0]/100<y[0]/100) return 1;
    else if(x[0]/100==y[0]/100)
    {
        if(x[1]<y[1]) return 1;
        else if(x[1]==y[1]) return 0;
        else return -1;
    }
    else return -1;
}

//****************************************************************************
//  AddIn_main (Sample program main function)
//
//  param   :   isAppli   : 1 = This application is launched by MAIN MENU.
//                        : 0 = This application is launched by a strip in eACT application.
//
//              OptionNum : Strip number (0~3)
//                         (This parameter is only used when isAppli parameter is 0.)
//
//  retval  :   1 = No error / 0 = Error
//
//****************************************************************************
int AddIn_main(int isAppli, unsigned short OptionNum)
{
    int i,j,k,t;
    int x,y;
    unsigned int smn;
    unsigned char temp;
    char view=1;

    Coin=0; Star=0;
    Level=0; AP=1; DP=0; EXP=0; status=0; Place=0; Stage=1; x_axis=61; y_axis=40;
    HP=7.0; MHP=7.5; password=0;
    effitem=300;

    Bfile_CreateDirectory(path);
    Bkey_Set_RepeatTime(16,3);

    dno=0;

    while(1)
    {
        uwin=1;
        smn=0;
        key=0;

        while(1)
        {
            quit=0;
            Bdisp_AllClr_DDVRAM();
            PrintXY(31,8,(unsigned char*)"Five Pieces",0);
            PrintMini(88,1,(unsigned char*)"v1.01.0053",MINI_OVER);
            PrintMini(27,18,(unsigned char*)"2007.9.25-2008.11.8",MINI_OVER);
            PrintXY(35,36,(unsigned char*)"Game Start",0);
            PrintXY(35,44,(unsigned char*)"Options",0);
            PrintXY(35,52,(unsigned char*)"Rankings",0);
            Bdisp_AreaReverseVRAM(0,36+8*smn,127,43+8*smn);
            while(1)
            {
                GetKey(&key);
                if(key==KEY_CTRL_UP && smn>0)
                {
                    smn--;
                    Bdisp_AreaReverseVRAM(0,36+8*smn,127,51+8*smn);
                }
                if(key==KEY_CTRL_DOWN && smn<2)
                {
                    Bdisp_AreaReverseVRAM(0,36+8*smn,127,51+8*smn);
                    smn++;
                }
                if(key==KEY_CTRL_EXE) break;
            }
            if(smn==0)
            {
                x=dno/10; y=dno%10;
                while(1)
                {
                    PopUpWin(3);
                    PrintXY(34,24,(unsigned char*)"Loading...",0);
                    Bdisp_PutDisp_DD();
                    Bdisp_AllClr_VRAM();
                    PrintXY(30,0,(unsigned char*)"Select Data",0);
                    for(i=0;i<=9;i++)
                    {
                        loadDat(10*x+i,1);
                        if(Stage==0)
                        {
                            if(x==0) sprintf(str,"0%u:New",10*x+i);
                            else sprintf(str,"%u:New",10*x+i);
                            PrintXY(64*(i/5)+8,8*(i%5)+14,(unsigned char*)str,0);
                        }
                        else
                        {
                            if(view==0)
                            {
                                if(x==0) sprintf(str,"0%u:Lv%3u",10*x+i,Level);
                                else sprintf(str,"%u:Lv%3u",10*x+i,Level);
                            }
                            else
                            {
                                if(x==0) sprintf(str,"0%u:%s",10*x+i,nm);
                                else sprintf(str,"%u:%s",10*x+i,nm);
                            }
                            PrintXY(64*(i/5)+8,8*(i%5)+14,(unsigned char*)str,0);
                        }
                    }
                    Bdisp_AreaReverseVRAM(64*(y/5),8*(y%5)+14,64*(y/5)+63,8*(y%5)+21);
                    PrintMini(4,58,(unsigned char*)"F1:NAME<->Lv  0~9:CHANGE PAGE",MINI_OVER);
                    while(1)
                    {
                        GetKey(&key);
                        if(key==KEY_CTRL_UP && y>0)
                        {
                            Bdisp_AreaReverseVRAM(64*(y/5),8*(y%5)+14,64*(y/5)+63,8*(y%5)+21);
                            y--;
                            Bdisp_AreaReverseVRAM(64*(y/5),8*(y%5)+14,64*(y/5)+63,8*(y%5)+21);
                        }
                        if(key==KEY_CTRL_DOWN && y<9)
                        {
                            Bdisp_AreaReverseVRAM(64*(y/5),8*(y%5)+14,64*(y/5)+63,8*(y%5)+21);
                            y++;
                            Bdisp_AreaReverseVRAM(64*(y/5),8*(y%5)+14,64*(y/5)+63,8*(y%5)+21);
                        }
                        if(key==KEY_CTRL_LEFT && y>=5)
                        {
                            Bdisp_AreaReverseVRAM(64*(y/5),8*(y%5)+14,64*(y/5)+63,8*(y%5)+21);
                            y-=5;
                            Bdisp_AreaReverseVRAM(64*(y/5),8*(y%5)+14,64*(y/5)+63,8*(y%5)+21);
                        }
                        if(key==KEY_CTRL_RIGHT && y<5)
                        {
                            Bdisp_AreaReverseVRAM(64*(y/5),8*(y%5)+14,64*(y/5)+63,8*(y%5)+21);
                            y+=5;
                            Bdisp_AreaReverseVRAM(64*(y/5),8*(y%5)+14,64*(y/5)+63,8*(y%5)+21);
                        }
                        if(key==KEY_CTRL_F1)
                        {
                            view=1-view;
                            break;
                        }
                        if(key>=KEY_CHAR_0 && key<=KEY_CHAR_9 && x!=key-KEY_CHAR_0)
                        {
                            x=key-KEY_CHAR_0;
                            break;
                        }
                        if(key==KEY_CTRL_EXIT || key==KEY_CTRL_AC)
                        {
                            dno=10*x+y;
                            break;
                        }
                        if(key==KEY_CTRL_EXE)
                        {
                            dno=10*x+y;
                            loadDat(dno,0);
                            i=0;
                            if(Stage==0)
                            {
                                SaveDisp(SAVEDISP_PAGE1);
                                PopUpWin(3);
                                PrintXY(20,16,(unsigned char*)"Enter password",0);
                                PrintXY(20,32,(unsigned char*)"[0~65535]:0",0);
                                do
                                {
                                    GetKey(&key);
                                    if(key>=KEY_CHAR_0 && key<=KEY_CHAR_9 && 10*i+key-KEY_CHAR_0<=65535)
                                    {
                                        i=10*i+key-KEY_CHAR_0;
                                        sprintf(str,"%u",i);
                                        PrintXY(80,32,(unsigned char*)str,0);
                                    }
                                    if(key==KEY_CTRL_DEL)
                                    {
                                        i/=10;
                                        PrintXY(80,32,(unsigned char*)"     ",0);
                                        sprintf(str,"%u",i);
                                        PrintXY(80,32,(unsigned char*)str,0);
                                    }
                                }while(key!=KEY_CTRL_EXE && key!=KEY_CTRL_EXIT && key!=KEY_CTRL_AC);
                                if(key==KEY_CTRL_EXIT || key==KEY_CTRL_AC) RestoreDisp(SAVEDISP_PAGE1);
                                else
                                {
                                    password=i;
                                    Stage=1;
                                    break;
                                }
                            }
                            else
                            {
                                SaveDisp(SAVEDISP_PAGE1);
                                do
                                {
                                    PopUpWin(3);
                                    PrintXY(13,16,(unsigned char*)"Enter password of",0);
                                    if(dno<10) sprintf(str,"Data 0%u: %u",dno,i);
                                    else sprintf(str,"Data %u: %u",dno,i);
                                    PrintXY(13,32,(unsigned char*)str,0);
                                    do
                                    {
                                        GetKey(&key);
                                        if(key>=KEY_CHAR_0 && key<=KEY_CHAR_9 && 10*i+key-KEY_CHAR_0<=65535)
                                        {
                                            i=10*i+key-KEY_CHAR_0;
                                            sprintf(str,"%u",i);
                                            PrintXY(67,32,(unsigned char*)str,0);
                                        }
                                        if(key==KEY_CTRL_DEL)
                                        {
                                            i/=10;
                                            PrintXY(67,32,(unsigned char*)"     ",0);
                                            sprintf(str,"%u",i);
                                            PrintXY(67,32,(unsigned char*)str,0);
                                        }
                                    }while(key!=KEY_CTRL_EXE && key!=KEY_CTRL_EXIT && key!=KEY_CTRL_AC);
                                    if(key==KEY_CTRL_EXIT || key==KEY_CTRL_AC) RestoreDisp(SAVEDISP_PAGE1);
                                    else
                                    {
                                        if(password==i) break;
                                        else
                                        {
                                            PopUpWin(3);
                                            PrintXY(41,24,(unsigned char*)"Mismatch",0);
                                            GetKey(&key);
                                            key=KEY_CTRL_EXE;
                                        }
                                    }
                                }while(key==KEY_CTRL_EXE);
                            }
                            if(key==KEY_CTRL_EXE) break;
                        }
                    }
                    if(key==KEY_CTRL_EXE || key==KEY_CTRL_EXIT || key==KEY_CTRL_AC) break;
                }
                if(key==KEY_CTRL_EXE) break;
            }
            else if(smn==1)
            {
                i=0;
                Bdisp_AllClr_DDVRAM();
                PrintXY(4,6,(unsigned char*)"Min. effect of Item:",0);
                if(effitem==0)
                    sprintf(str," %5.1f%%%c%c",.1*effitem,0xE6,0x9B);
                else if(effitem==1000)
                    sprintf(str,"%c%c%5.1f%% ",0xE6,0x9A,.1*effitem,0xE6);
                else
                    sprintf(str,"%c%c%5.1f%%%c%c",0xE6,0x9A,.1*effitem,0xE6,0x9B);
                PrintXY(70,15,(unsigned char*)str,0);
                PrintXY(26,36,(unsigned char*)"Damage-Calc",0);
                PrintXY(26,44,(unsigned char*)"Debug Mode",0);
                PrintXY(26,52,(unsigned char*)"Regulate Data",0);

                Bdisp_AreaReverseVRAM(0,36,127,43);
                while(1)
                {
                    GetKey(&key);
                    if(key==KEY_CTRL_RIGHT && effitem<1000)
                    {
                        if(effitem>=100) effitem+=10;
                        else if(effitem>=5) effitem+=5;
                        else if(effitem==1) effitem=5;
                        else effitem=1;
                        if(effitem==1000)
                            sprintf(str,"%c%c%5.1f%% ",0xE6,0x9A,.1*effitem,0xE6);
                        else
                            sprintf(str,"%c%c%5.1f%%%c%c",0xE6,0x9A,.1*effitem,0xE6,0x9B);
                        PrintXY(70,15,(unsigned char*)str,0);
                    }
                    if(key==KEY_CTRL_LEFT && effitem>0)
                    {
                        if(effitem==1) effitem=0;
                        else if(effitem==5) effitem=1;
                        else if(effitem<=100) effitem-=5;
                        else effitem-=10;
                        if(effitem==0)
                            sprintf(str," %5.1f%%%c%c",.1*effitem,0xE6,0x9B);
                        else
                            sprintf(str,"%c%c%5.1f%%%c%c",0xE6,0x9A,.1*effitem,0xE6,0x9B);
                        PrintXY(70,15,(unsigned char*)str,0);
                    }
                    if(i<2 && key==KEY_CTRL_DOWN || i && key==KEY_CTRL_UP)
                    {
                        Bdisp_AreaReverseVRAM(0,36+8*i,127,43+8*i);
                        i+=1-2*(key==KEY_CTRL_UP);
                        Bdisp_AreaReverseVRAM(0,36+8*i,127,43+8*i);
                    }
                    if(key==KEY_CTRL_AC || key==KEY_CTRL_EXIT) break;
                    if(key==KEY_CTRL_EXE)
                    {
                        SaveDisp(SAVEDISP_PAGE1);
                        if(i==0)
                        {
                            i=j=0;
                            t=0;
                            dam=0;
                            Bdisp_DrawLineVRAM(7,8,121,8);
                            Bdisp_DrawLineVRAM(7,46,121,46);
                            Bdisp_DrawLineVRAM(7,8,7,46);
                            Bdisp_DrawLineVRAM(121,8,121,46);
                            do{
                                Bdisp_AreaClr_VRAM(&cdisp);
                                sprintf(str,"Attacker's AP:%3d",i);
                                PrintXY(13,12,(unsigned char*)str,0);
                                sprintf(str,"Defender's DP:%3d",j);
                                PrintXY(13,20,(unsigned char*)str,0);
                                dam=Damage(i,j);
                                if(dam>999999.999) dam=999999.999;
                                sprintf(str,"Damage:%10.3f",dam);
                                PrintXY(13,36,(unsigned char*)str,0);
                                Bdisp_AreaReverseVRAM(10,12+8*t,118,19+8*t);
                                GetKey(&key);
                                if(key>=KEY_CHAR_0 && key<=KEY_CHAR_9 || key==KEY_CTRL_DEL || key==KEY_CTRL_LEFT || key==KEY_CTRL_RIGHT)
                                {
                                    if(t==0)
                                    {
                                        if(key>=KEY_CHAR_0 && key<=KEY_CHAR_9 && i<100)
                                            i=i*10+(key-KEY_CHAR_0);
                                        if(key==KEY_CTRL_DEL)
                                            i/=10;
                                        if(key==KEY_CTRL_LEFT && i>0 || key==KEY_CTRL_RIGHT && i<999)
                                            i+=1-2*(key==KEY_CTRL_LEFT);
                                    }
                                    else
                                    {
                                        if(key>=KEY_CHAR_0 && key<=KEY_CHAR_9 && j<100 && j>=0)
                                            j=j*10+(key-KEY_CHAR_0);
                                        if(key==KEY_CTRL_DEL)
                                            j/=10;
                                        if(key==KEY_CTRL_LEFT && j>-99 || key==KEY_CTRL_RIGHT && j<999)
                                            j+=1-2*(key==KEY_CTRL_LEFT);
                                    }
                                }
                                if(key==KEY_CTRL_DOWN && t==0 || key==KEY_CTRL_UP && t==1)
                                    t=1-t;
                            }while(key!=KEY_CTRL_EXIT && key!=KEY_CTRL_AC);
                            i=0;
                        }
                        else if(i==1)
                        {
                            i=0;
                            do
                            {
                                RestoreDisp(SAVEDISP_PAGE1);
                                PopUpWin(3);
                                PrintXY(15,16,(unsigned char*)"Enter dat.number",0);
                                sprintf(str,"%u",i);
                                PrintXY(27,32,(unsigned char*)str,0);
                                do
                                {
                                    GetKey(&key);
                                    if(key>=KEY_CHAR_0 && key<=KEY_CHAR_9 && 10*i+key-KEY_CHAR_0<=99)
                                    {
                                        i=10*i+key-KEY_CHAR_0;
                                        sprintf(str,"%u",i);
                                        PrintXY(27,32,(unsigned char*)str,0);
                                    }
                                    if(key==KEY_CTRL_DEL)
                                    {
                                        i/=10;
                                        PrintXY(27,32,(unsigned char*)"  ",0);
                                        sprintf(str,"%u",i);
                                        PrintXY(27,32,(unsigned char*)str,0);
                                    }
                                }while(key!=KEY_CTRL_EXE && key!=KEY_CTRL_EXIT && key!=KEY_CTRL_AC);
                                if(key!=KEY_CTRL_EXIT && key!=KEY_CTRL_AC)
                                {
                                    loadDat(i,0);
                                    handle=Bfile_OpenFile(file,_OPENMODE_READ);
                                    for(j=0;j<6;j++)
                                    {
                                        PopUpWin(4);
                                        for(y=0;y<4;y++)
                                        {
                                            Bfile_ReadFile(handle,&work,4,(j<<4)+(y<<2));
                                            if((j<<4)+(y<<2)<10)
                                                sprintf(str,"#0%u-",(j<<4)+(y<<2));
                                            else
                                                sprintf(str,"#%u-",(j<<4)+(y<<2));
                                            PrintXY(19,8+8*y,(unsigned char*)str,0);
                                            if((j<<4)+(y<<2)<7)
                                                sprintf(str,"0%u:",(j<<4)+(y<<2)+3);
                                            else 
                                                sprintf(str,"%u:",(j<<4)+(y<<2)+3);
                                            PrintXY(43,8+8*y,(unsigned char*)str,0);
                                            for(t=0;t<8;t++)
                                            {
                                                sprintf(str,"%X",(work&(15<<((7-t)<<2)))>>((7-t)<<2));
                                                PrintXY(61+6*t,8+8*y,(unsigned char*)str,0);
                                            }
                                        }
                                        GetKey(&key);
                                    }
                                    Bfile_CloseFile(handle);
                                }
                            }while(key==KEY_CTRL_EXE);
                            i=1;
                        }
                        else
                        {
                            PopUpWin(3);
                            PrintXY(12,24,(unsigned char*)"One Moment Please",0);
                            Bdisp_PutDisp_DD();
                            for(j=0;j<100;j++)
                            {
                                file[14]=j/10+'0';
                                file[15]=j%10+'0';
                                handle=Bfile_OpenFile(file,_OPENMODE_READ);
                                if(handle<0)
                                {
                                    Bfile_CreateFile(file,96);
                                    handle=Bfile_OpenFile(file,_OPENMODE_READWRITE);
                                    Bfile_SeekFile(handle,0);
                                    Bfile_WriteFile(handle,WrtDat,96);
                                    Bfile_CloseFile(handle);
                                }
                                else
                                {
                                    Bfile_ReadFile(handle,str,96,0);
                                    Bfile_CloseFile(handle);
                                    Bfile_DeleteFile(file);
                                    Bfile_CreateFile(file,96);
                                    handle=Bfile_OpenFile(file,_OPENMODE_WRITE);
                                    Bfile_SeekFile(handle,0);
                                    Bfile_WriteFile(handle,str,96);
                                    Bfile_CloseFile(handle);
                                }
                            }
                            PopUpWin(3);
                            PrintXY(37,24,(unsigned char*)"Complete!",0);
                            GetKey(&key);
                            i=2;
                        }
                        RestoreDisp(SAVEDISP_PAGE1);
                    }
                }
            }
            else if(smn==2)
            {
                PopUpWin(3);
                PrintXY(34,24,(unsigned char*)"Loading...",0);
                Bdisp_PutDisp_DD();
                Bdisp_AllClr_VRAM();
                for(i=0;i<99;i++)
                {
                    loadDat(i,1);
                    rank[2*i]=Level*100+i;
                    rank[2*i+1]=EXP;
                    if(Stage!=0) rank[2*i+1]++;
                }
                qsort(rank,99,sizeof(int)*2,compare);
                for(i=0;i<16;i++)
                {
                    if(rank[2*i+1])
                    {
                        loadDat(rank[2*i]%100,1);
                        if(nm[0]==0 || nm[0]==-1)
                        {
                            if(rank[2*i]%100<10) sprintf(nm,"0%d",rank[2*i]%100);
                            else sprintf(nm,"%d",rank[2*i]%100);
                        }
                        PrintXY(66*(i/8),8*(i%8),(unsigned char*)nm,0);
                        sprintf(str,"Lv%3u",rank[2*i]/100);
                        PrintXY(66*(i/8)+32,8*(i%8),(unsigned char*)str,0);
                    }
                }
                GetKey(&key);
            }
        }
        if(nm[0]==0 || nm[0]==-1)
        {
            strcpy(nm,"     ");
            Bdisp_AllClr_DDVRAM();
            PrintXY(18,4,(unsigned char*)"Input your name",0);
            PrintMini(5,16,(unsigned char*)"PRESS [ALPHA]+KEY FOR ALPHABET",MINI_OVER);
            sprintf(str,"[%c%c]:CAPITAL [%c%c]:lower",0xE6,0x9C,0xE6,0x9D);
            PrintMini(5,24,(unsigned char*)str,MINI_OVER);
            Bdisp_DrawLineVRAM(46,38,80,38);
            Bdisp_DrawLineVRAM(46,49,80,49);
            Bdisp_DrawLineVRAM(46,38,46,49);
            Bdisp_DrawLineVRAM(80,38,80,49);
            PrintXY(85,56,(unsigned char*)"[UPPER]",0);
            x=y=0;
            i=0;
            while(1)
            {
                PrintXY(48,51,(unsigned char*)"     ",0);
                sprintf(str,"%c%c",0xE6,0x92);
                PrintXY(6*i+48,51,(unsigned char*)str,0);
                GetKey(&key);
                if(key==KEY_CTRL_SHIFT)
                {
                    if(x==1)
                    {
                        x=0;
                        PrintXY(0,56,(unsigned char*)"       ",0);
                    }
                    else
                    {
                        x=1;
                        PrintXY(0,56,(unsigned char*)"[SHIFT]",0);
                    }
                }
                else if(key==KEY_CTRL_ALPHA)
                {
                    if(x==0)
                    {
                        x=2;
                        PrintXY(0,56,(unsigned char*)"[ALPHA]",0);
                    }
                    else if(x==1)
                    {
                        x=3;
                        PrintXY(0,56,(unsigned char*)"[ALOCK]",0);
                    }
                    else
                    {
                        x=0;
                        PrintXY(0,56,(unsigned char*)"       ",0);
                    }
                }
                else
                {
                    if(key==KEY_CTRL_UP)
                    {
                        y=0;
                        PrintXY(85,56,(unsigned char*)"[UPPER]",0);
                    }
                    if(key==KEY_CTRL_DOWN)
                    {
                        y=1;
                        PrintXY(85,56,(unsigned char*)"[lower]",0);
                    }
                    if(key==KEY_CTRL_LEFT)
                        i>0?i--:0;
                    if(key==KEY_CTRL_RIGHT)
                        i<4?i++:0;
                    if(x!=3)
                    { 
                        x=0;
                        PrintXY(0,56,(unsigned char*)"       ",0);
                    }
                    if(y==1 && key>=0x41 && key<=0x5A) key+=0x20;
                    else if(key==0x89) key=0x2B;
                    else if(key==0x99) key=0x2D;
                    else if(key==0xA8) key=0x5E;
                    else if(key==0x20) key=0x5F;
                    else if(key==0x7F54) key=0x8C;
                    else if(key==0xCE) key=0xD8;
                    else if(key==0x0E) key=0x2F;
                    else if(key==0xD0) key=0x7E;
                    else if(key==KEY_CTRL_DEL) key=0x20;
                    else if(key==KEY_CTRL_F1) key=0x21;
                    else if(key==KEY_CTRL_F2) key=0x40;
                    else if(key==KEY_CTRL_F3) key=0x24;
                    else if(key==KEY_CTRL_F4) key=0x25;
                    else if(key==KEY_CTRL_F5) key=0x26;
                    else if(key==KEY_CTRL_F6) key=0x2A;
                    if(key>=0x0C && key<=0x0F || key>=0x20 && key<=0x7E || key==0x86 || key==0x87 || key==0x8C || key==0xA9 || key==0xB5 || key==0xB9 || key==0xBB || key==0xD8)
                    {
                        nm[i]=key;
                        sprintf(str,"%c",nm[i]);
                        PrintXY(6*i+48,40,(unsigned char*)str,0);
                        i<4 && key!=0x20?i++:0;
                    }
                }
                if(key==KEY_CTRL_EXE && strcmp(nm,"     ")) break;
            }
        }

        work=2;
        srand(Stage<<24+x_axis<<16+y_axis<<8+Coin);
        Refresh();

        while(1)
        {
            for(i=1;i<=6;i++)
                if(IsKeyDown(KEY_CTRL_F1-1+i))
                {
                    if(uwin!=i)
                    {
                        uwin=i;
                        drawUwin(i);
                    }
                    break;
                }

            PrintXY(x_axis,y_axis,(unsigned char*)" ",0);
            j=0;
            if(IsKeyDown(KEY_CTRL_LEFT) && !(x_axis==1 && Place==0))
            {
                j++;
                x_axis-=3;
                if(x_axis==-2)
                {
                    Place--;
                    x_axis=121;
                    Refresh();
                }
            }
            if(IsKeyDown(KEY_CTRL_RIGHT))
            {
                j++;
                x_axis+=3;
                if(x_axis==124)
                {
                    Place++;
                    x_axis=1;
                    Refresh();
                }
                if(x_axis==58 && Stage<=Place)
                {
                    x_axis=55;
                    if(Place==1) Battle(25,1,1,3,40,24,-1);
                    if(Place==2) Battle(32,3,0,4,80,32,-1);
                    if(Place==3) Battle(50,3,1,5,160,48,-1);
                    if(Place==5) Battle(45,2,5,9,168,64,-1);
                    if(Place==6) Battle(70,5,0,13,395,40,-1);
                    if(Place==7) Battle(140,4,2,16,700,86,-1);
                    if(Place==9) Battle(98,2,7,25,556,125,-1);
                    if(Place==10) Battle(125,8,1,28,1407,100,-1);
                    if(Place==11) Battle(150,9,0,32,1703,100,-1);
                    if(Place==13) Battle(550,8,0,41,3701,160,-1);
                    if(Place==14) Battle(1100,8,1,46,5830,240,-1);
                    if(Place==15) Battle(573,10,9,50,8453,375,-1);
                    if(Place==17) Battle(607,13,0,59,6797,225,-1);
                    if(Place==18) Battle(625,15,0,64,8159,250,-1);
                    if(Place==19) Battle(663,17,2,68,10901,300,-1);
                    if(Place==21) Battle(640,11,16,77,8692,580,-1);
                    if(Place==22) Battle(621,11,19,81,10231,684,-1);
                    if(Place==23) Battle(607,12,21,87,12031,790,-1);
                    if(Place==25) Battle(1000,19,2,96,17779,332,-1);
                    if(Place==26) Battle(1357,20,1,101,20400,350,-1);
                    if(Place==27) Battle(961,21,7,106,25763,417,-1);
                    if(Place==29) Battle(1440,25,3,115,30942,411,-1);
                    if(Place==30) Battle(6842,21,3,120,42216,455,-1);
                    if(Place==31) Battle(9600,22,2,125,47516,500,-1);
                    if(Place==33) Battle(4763,25,12,134,65505,627,-1);
                    if(Place==34) Battle(3270,40,2,140,72347,709,-1);
                    if(Place==35) Battle(9750,29,10,144,86259,893,-1);
                    if(Place==37) Battle(462,35,21,155,25000,256,-1);
                    if(Place==38) Battle(8765,33,11,159,104784,1024,-1);
                    if(Place==39) Battle(9999,34,17,165,133308,1078,-1);
                    if(Place==41) Battle(22500,25,31,175,183058,1447,-1);
                    if(Place==42) Battle(24001,23,35,180,198114,1382,-1);
                    if(Place==43) Battle(38384,49,0,185,177153,1012,-1);
                    if(Place==45) Battle(29210,45,15,195,227545,1684,-1);
                    if(Place==46) Battle(31476,46,14,200,234801,1732,-1);
                    if(Place==47) Battle(34302,48,21,206,294974,1765,-1);
                    if(Place==49) Battle(65536,25,8,216,80000,100,-1);
                    if(Place==50) Battle(32768,50,4,220,221532,1000,-1);
                    if(Place==51) Battle(16384,75,0,226,600000,2500,-1);
                    if(Place==53) Battle(13500,82,5,236,408411,2550,-1);
                    if(Place==54) Battle(25,1,100,9999,96,48,-1);
                    if(Place==55) SpBat(1);
                    if(Place==57) Battle(10000,47,46,257,467270,1553,-1);
                    if(Place==58) Battle(250,125,12,263,500720,1663,-1);
                    if(Place==59) Battle(45000,60,28,267,538730,2067,-1);
                    if(Place==61) Battle(247400,50,13,279,440618,2411,-1);
                    if(Place==62) Battle(258220,56,23,283,603620,2755,-1);
                    if(Place==63) Battle(287000,58,33,289,759831,3073,-1);
                    if(Place==65) Battle(172210,78,0,299,585900,4000,-1);
                    if(Place==66) Battle(65432,79,1,305,540565,4000,-1);
                    if(Place==67) Battle(42316,83,13,311,759831,4000,-1);
                    if(Place==69) Battle(80,25,481,321,348818,7401,-1);
                    if(Place==70) Battle(160,35,381,327,448818,8299,-1);
                    if(Place==71) Battle(320,43,281,331,548819,8740,-1);
                }
                if(x_axis==106 && Place%4==3 && Stage-1<=Place)
                {
                    x_axis=103;
                    if(Place==3)
                    {
                        PopUpWin(2);
                        PrintXY(18,16,(unsigned char*)"I will not let",0);
                        PrintXY(18,24,(unsigned char*)"you go through!",0);
                        Bdisp_PutDisp_DD();
                        Sleep(4000);
                        Battle(75,4,0,7,517,120,-2);
                    }
                    if(Place==7)
                    {
                        PopUpWin(2);
                        PrintXY(18,16,(unsigned char*)"Don't disregard",0);
                        PrintXY(18,24,(unsigned char*)"me! I'm good!",0);
                        Bdisp_PutDisp_DD();
                        Sleep(4000);
                        Battle(69,6,3,24,1573,200,-2);
                    }
                    if(Place==11)
                    {
                        PopUpWin(2);
                        PrintXY(24,16,(unsigned char*)"Prepare to be",0);
                        PrintXY(24,24,(unsigned char*)"finished!",0);
                        Bdisp_PutDisp_DD();
                        Sleep(4000);
                        Battle(181,10,5,45,6735,415,-2);
                    }
                    if(Place==15)
                    {
                        PopUpWin(2);
                        PrintXY(18,16,(unsigned char*)"Stop! You can't",0);
                        PrintXY(18,24,(unsigned char*)"go through!",0);
                        Bdisp_PutDisp_DD();
                        Sleep(4000);
                        Battle(999,13,7,69,23815,1250,-2);
                    }
                    if(Place==19)
                    {
                        PopUpWin(3);
                        PrintXY(18,16,(unsigned char*)"This is the end",0);
                        PrintXY(18,24,(unsigned char*)"of your",0);
                        PrintXY(18,32,(unsigned char*)"adventure!",0);
                        Bdisp_PutDisp_DD();
                        Sleep(4000);
                        Battle(1932,18,5,93,41469,1600,-2);
                    }
                    if(Place==23)
                    {
                        PopUpWin(2);
                        PrintXY(18,16,(unsigned char*)"Blame your lack",0);
                        PrintXY(18,24,(unsigned char*)"of knowledge!",0);
                        Bdisp_PutDisp_DD();
                        Sleep(4000);
                        Battle(2035,15,29,118,100000,3000,-2);
                    }
                    if(Place==27)
                    {
                        PopUpWin(2);
                        PrintXY(18,16,(unsigned char*)"I'm better than",0);
                        PrintXY(18,24,(unsigned char*)"anyone before!",0);
                        Bdisp_PutDisp_DD();
                        Sleep(4000);
                        Battle(99,27,45,143,148290,4000,-2);
                    }
                    if(Place==31)
                    {
                        PopUpWin(3);
                        PrintXY(20,16,(unsigned char*)"You don't have",0);
                        PrintXY(20,24,(unsigned char*)"to say that",0);
                        PrintXY(20,32,(unsigned char*)"I'm the best!",0);
                        Bdisp_PutDisp_DD();
                        Sleep(4000);
                        Battle(16384,25,9,169,196235,4802,-2);
                    }
                    if(Place==35)
                    {
                        PopUpWin(3);
                        PrintXY(18,16,(unsigned char*)"I'm startled by",0);
                        PrintXY(18,24,(unsigned char*)"your courage to",0);
                        PrintXY(18,32,(unsigned char*)"challenge me!",0);
                        Bdisp_PutDisp_DD();
                        Sleep(4000);
                        Battle(64,43,999,195,328813,7167,-2);
                    }
                    if(Place==39)
                    {
                        PopUpWin(3);
                        PrintXY(18,16,(unsigned char*)"I can finish",0);
                        PrintXY(18,24,(unsigned char*)"you only with a",0);
                        PrintXY(18,32,(unsigned char*)"little finger!",0);
                        Bdisp_PutDisp_DD();
                        Sleep(4000);
                        Battle(26540,44,15,221,420216,8961,-2);
                    }
                    if(Place==43)
                    {
                        PopUpWin(3);
                        PrintXY(26,16,(unsigned char*)"You will be",0);
                        PrintXY(26,24,(unsigned char*)"amazed by my",0);
                        PrintXY(26,32,(unsigned char*)"magic-skill!",0);
                        Bdisp_PutDisp_DD();
                        Sleep(4000);
                        Battle(78627,27,23,248,596044,13417,-2);
                    }
                    if(Place==47)
                    {
                        PopUpWin(2);
                        PrintXY(21,16,(unsigned char*)"Beware of my",0);
                        PrintXY(21,24,(unsigned char*)"amazing skill!",0);
                        Bdisp_PutDisp_DD();
                        Sleep(4000);
                        Battle(186797,51,8,275,685609,18371,-2);
                    }
                    if(Place==51)
                    {
                        PopUpWin(2);
                        PrintXY(21,16,(unsigned char*)"Can you",0);
                        PrintXY(21,24,(unsigned char*)"one-hit KO me?",0);
                        Bdisp_PutDisp_DD();
                        Sleep(4000);
                        Battle(700,200,7,8,1073418,19032,-2);
                    }
                    if(Place==55)
                    {
                        PopUpWin(4);
                        PrintXY(18,8,(unsigned char*)"If you lose",0);
                        PrintXY(18,16,(unsigned char*)"balance, you'll",0);
                        PrintXY(18,24,(unsigned char*)"be unable to",0);
                        PrintXY(18,32,(unsigned char*)"pass me!",0);
                        Bdisp_PutDisp_DD();
                        Sleep(4500);
                        Battle(750000,0,100,338,1738849,25600,-2);
                    }
                    if(Place==59)
                    {
                        PopUpWin(2);
                        PrintXY(21,16,(unsigned char*)"I am your next",0);
                        PrintXY(21,24,(unsigned char*)"nightmare!",0);
                        Bdisp_PutDisp_DD();
                        Sleep(4000);
                        Battle(262144,72,24,359,2004265,27414,-2);
                    }
                    if(Place==63)
                    {
                        PopUpWin(2);
                        PrintXY(24,16,(unsigned char*)"Your pathetic",0);
                        PrintXY(24,24,(unsigned char*)"attacks won't",0);
                        PrintXY(24,24,(unsigned char*)"beat me!",0);
                        Bdisp_PutDisp_DD();
                        Sleep(4000);
                        Battle(156267,73,822,394,2370258,32000,-2);
                    }
                    if(Place==67)
                    {
                        PopUpWin(2);
                        PrintXY(15,16,(unsigned char*)"Haha! Let's have",0);
                        PrintXY(15,24,(unsigned char*)"a hot battle!",0);
                        Bdisp_PutDisp_DD();
                        Sleep(4000);
                        Battle(83421,94,26,415,2828912,36000,-2);
                    }
                    if(Place==71)
                    {
                        PopUpWin(3);
                        PrintXY(21,16,(unsigned char*)"I'm shocked by",0);
                        PrintXY(21,24,(unsigned char*)"your dare to",0);
                        PrintXY(21,32,(unsigned char*)"challenge me!",0);
                        Bdisp_PutDisp_DD();
                        Sleep(4000);
                        Battle(200,100,999,500,3217176,40000,-2);
                    }
                }
            }
            if(IsKeyDown(KEY_CTRL_UP) && y_axis>25)
            {
                j++;
                y_axis-=3;
            }
            if(IsKeyDown(KEY_CTRL_DOWN) && y_axis<55)
            {
                j++;
                y_axis+=3;
            }

            if((x_axis>=16 && x_axis<=43) && y_axis<=31 && Place%4==0)
            {
                key=0;
                rank[20]=0;
                while(key!=KEY_CTRL_EXIT)
                {
                    key=0;
                    PopUpWin(4);
                    PrintXY(27,8,(unsigned char*)"Healing Item",0);
                    PrintXY(27,16,(unsigned char*)"Charge Item",0);
                    PrintXY(27,24,(unsigned char*)"Status Item",0);
                    PrintXY(27,32,(unsigned char*)"Etc.",0);
                    Bdisp_AreaReverseVRAM(13,8+8*rank[20],113,15+8*rank[20]);
                    Bdisp_PutDisp_DD();
                    while(key==0)
                    {
                        GetKeyWait(KEYWAIT_HALTON_TIMEROFF,0,1,&key);
                        if(IsKeyDown(KEY_CTRL_EXIT))
                        {
                            key=KEY_CTRL_EXIT;
                            break;
                        }
                        j=0;
                        if(IsKeyDown(KEY_CTRL_DOWN) && rank[15]<3) j=1;
                        if(IsKeyDown(KEY_CTRL_UP) && rank[15]>0) j=-1;
                        if(j)
                        {
                            Bdisp_AreaReverseVRAM(13,8+8*rank[15],113,15+8*rank[15]);
                            rank[15]+=j;
                            Bdisp_AreaReverseVRAM(13,8+8*rank[15],113,15+8*rank[15]);
                            Bdisp_PutDisp_DD();
                        }
                        if(IsKeyDown(KEY_CTRL_EXE))
                        {
                            j=100;
                            rank[0]=0;
                            Bdisp_AllClr_DDVRAM();
                            rank[9]=(item[0]>0)+(item[1]>0)+(item[2]>0)+(item[3]>0)+(item[4]>0)+(item[5]>0)+(item[6]>0)+(item[7]>0)+(item[8]>0)+(item[9]>0);
                            sprintf(str,"Coin:%-8d Item:%2d",Coin,rank[9]);
                            PrintXY(0,0,(unsigned char*)str,0);
                            t=0;
                            if(rank[20]==0)
                            {
                                if(Place>=0 && Place<=20)
                                    rank[t++]=1;
                                if(Place>=12 && Place<=48)
                                    rank[t++]=2;
                                if(Place>=24 && Place<=76)
                                    rank[t++]=3;
                                if(Place>=40 && Place<=104)
                                    rank[t++]=4;
                                if(Place>=56 && Place<=132)
                                    rank[t++]=5;
                                if(Place>=76 && Place<=160)
                                    rank[t++]=6;
                                if(Place>=96 && Place<=184)
                                    rank[t++]=7;
                                if(Place>=116)
                                    rank[t++]=8;
                                if(Place>=140)
                                    rank[t++]=9;
                                if(Place>=164)
                                    rank[t++]=10;
                                if(Place>=188)
                                    rank[t++]=11;
                                if(Place>=212)
                                    rank[t++]=12;
                            }
                            else if(rank[20]==1)
                            {
                                if(Place>=0 && Place<=16)
                                    rank[t++]=21;
                                if(Place>=8 && Place<=32)
                                    rank[t++]=22;
                                if(Place>=16 && Place<=48)
                                    rank[t++]=23;
                                if(Place>=24 && Place<=64)
                                    rank[t++]=24;
                                if(Place>=32 && Place<=80)
                                    rank[t++]=25;
                                if(Place>=40 && Place<=100)
                                    rank[t++]=26;
                                if(Place>=52 && Place<=120)
                                    rank[t++]=27;
                                if(Place>=64 && Place<=140)
                                    rank[t++]=28;
                                if(Place>=76 && Place<=160)
                                    rank[t++]=29;
                                if(Place>=88 && Place<=180)
                                    rank[t++]=30;
                                if(Place>=100 && Place<=200)
                                    rank[t++]=31;
                                if(Place>=116)
                                    rank[t++]=32;
                                if(Place>=132)
                                    rank[t++]=33;
                                if(Place>=148)
                                    rank[t++]=34;
                                if(Place>=164)
                                    rank[t++]=35;
                                if(Place>=180)
                                    rank[t++]=36;
                                if(Place>=196)
                                    rank[t++]=37;
                                if(Place>=212)
                                    rank[t++]=38;
                            }
                            else if(rank[20]==2)
                            {
                                if(Place>=40)
                                    rank[t++]=41;
                                if(Place>=28)
                                    rank[t++]=42;
                                if(Place>=56)
                                    rank[t++]=43;
                                if(Place>=64)
                                    rank[t++]=44;
                                if(Place>=72)
                                    rank[t++]=45;
                                if(Place>=80)
                                    rank[t++]=46;
                                if(Place>=88)
                                    rank[t++]=47;
                                if(Place>=96)
                                    rank[t++]=48;
                            }
                            else if(rank[20]==3)
                            {
                                if(Place==28)
                                    rank[t++]=51;
                                if(Place==48)
                                    rank[t++]=53;
                                if(Place==60)
                                {
                                    rank[t++]=52;
                                    rank[t++]=54;
                                    rank[t++]=55;
                                    rank[t++]=56;
                                }
                            }
                            for(i=0;i<t;i++)
                            {
                                if(rank[i]<=20)
                                {
                                    sprintf(str,"HP+%d",HPI[rank[i]-1]);
                                    rank[i+10]=HPI[rank[i]-1]*(rank[i]+39)/10;
                                }
                                else if(rank[i]<=40)
                                {
                                    rank[8]=rank[i]-20;
                                    sprintf(str,"Charge+%d",4*rank[8]);
                                    rank[i+10]=(int)((19*rank[8]+rank[8]*rank[8])*pow(1.28,rank[8]-1)+.001);
                                }
                                else
                                {
                                    strcpy(str,Iname[rank[i]-41]);
                                    rank[i+10]=IP[rank[i]-41];
                                }
                                PrintXY(6,8*i+8,(unsigned char*)str,0);
                                rank[i+10]=rank[i+10]*j/100;
                                sprintf(str,"$%d",rank[i+10]);
                                PrintXY(120-6*strlen(str),8*i+8,(unsigned char*)str,0);
                            }
                            if(rank[0]==0)
                            {
                                PrintXY(6,28,(unsigned char*)"No Items available",0);
                                PrintXY(26,36,(unsigned char*)"in this section.",0);
                                Bdisp_PutDisp_DD();
                                while(IsKeyUp(KEY_CTRL_EXIT))
                                {
                                    GetKeyWait(KEYWAIT_HALTON_TIMEROFF,0,1,&key);
                                }
                            }
                            else
                            {
                                sprintf(str,"%c%c",0xE6,0x9B);
                                PrintXY(0,8,(unsigned char*)str,0);
                                Bdisp_PutDisp_DD();
                                i=0;
                                while(IsKeyDown(KEY_CTRL_EXE))
                                {
                                    Sleep(50);
                                }
                                while(IsKeyUp(KEY_CTRL_EXIT))
                                {
                                    GetKeyWait(KEYWAIT_HALTON_TIMEROFF,0,1,&key);
                                    j=0;
                                    if(IsKeyDown(KEY_CTRL_DOWN) && i<t-1) j=1;
                                    if(IsKeyDown(KEY_CTRL_UP) && i>0) j=-1;
                                    if(j)
                                    {
                                        PrintXY(0,8*i+8,(unsigned char*)" ",0);
                                        i+=j;
                                        PrintXY(0,8*i+8,(unsigned char*)str,0);
                                        Bdisp_PutDisp_DD();
                                    }
                                    if(IsKeyDown(KEY_CTRL_EXE))
                                    {
                                        SaveDisp(SAVEDISP_PAGE1);
                                        if(Coin<rank[i+10] || rank[9]==10)
                                        {
                                            PopUpWin(2);
                                            if(rank[9]==10)
                                            {
                                                PrintXY(18,16,(unsigned char*)"You can't carry",0);
                                                PrintXY(18,24,(unsigned char*)"more items.",0);
                                            }
                                            else
                                                PrintXY(15,20,(unsigned char*)"Not enough Coins",0);
                                            Bdisp_PutDisp_DD();
                                            do
                                            {
                                                GetKeyWait(KEYWAIT_HALTON_TIMEROFF,0,1,&key);
                                            }while(IsKeyUp(KEY_CTRL_EXE) && IsKeyUp(KEY_CTRL_EXIT));
                                            RestoreDisp(SAVEDISP_PAGE1);
                                            while(IsKeyDown(KEY_CTRL_EXIT))
                                            {
                                                Sleep(50);
                                            }
                                        }
                                        else
                                        {
                                            PopUpWin(2);
                                            PrintXY(21,16,(unsigned char*)"Buy this item?",0);
                                            PrintXY(21,24,(unsigned char*)"1:Yes     2:No",0);
                                            Bdisp_PutDisp_DD();
                                            for(key=0;key==0;)
                                            {
                                                GetKeyWait(KEYWAIT_HALTON_TIMEROFF,0,1,&key);
                                                if(IsKeyDown(KEY_CHAR_1)) key=1;
                                                if(IsKeyDown(KEY_CHAR_2) || IsKeyDown(KEY_CTRL_EXIT)) key=2;
                                            }
                                            if(key==1)
                                            {
                                                RestoreDisp(SAVEDISP_PAGE1);
                                                Coin-=rank[i+10];
                                                for(j=0;item[j];j++);
                                                item[j]=rank[i];
                                                rank[9]++;
                                                sprintf(str,"Coin:%-8d Item:%2d",Coin,rank[9]);
                                                PrintXY(0,0,(unsigned char*)str,0);
                                                sprintf(str,"%c%c",0xE6,0x9B);
                                            }
                                            else RestoreDisp(SAVEDISP_PAGE1);
                                        }
                                        Bdisp_PutDisp_DD();
                                    }
                                    if(IsKeyDown(KEY_CTRL_F1))
                                    {
                                        itemhelp(rank[i],rank[10+i]);
                                        sprintf(str,"%c%c",0xE6,0x9B);
                                    }
                                }
                            }
                            key=1;
                        }
                        if(j>5) break;
                        Sleep(50);
                    }
                }
                y_axis=34;
                Refresh();
            }
            if((x_axis>=79 && x_axis<=106) && y_axis<=31 && Place%4==0)
            {
                SaveDisp(SAVEDISP_PAGE1);
                PopUpWin(2);
                PrintXY(21,16,(unsigned char*)"Upgrade STATs",0);
                PrintXY(21,24,(unsigned char*)"Upgrade Skills",0);
                Bdisp_AreaReverseVRAM(13,16,113,23);
                i=0;
                Bdisp_PutDisp_DD();
                while(IsKeyUp(KEY_CTRL_EXIT))
                {
                    if(IsKeyDown(KEY_CTRL_UP) && i==1 || IsKeyDown(KEY_CTRL_DOWN) && i==0)
                    {
                        i=1-i;
                        Bdisp_AreaReverseVRAM(13,16,113,31);
                        Bdisp_PutDisp_DD();
                    }
                    if(IsKeyDown(KEY_CTRL_EXE))
                    {
                        Bdisp_AllClr_DDVRAM();
                        sprintf(str,"Coin($):%d",Coin);
                        PrintXY(0,0,(unsigned char*)str,0);
                        sprintf(str,"Star(*):%d",Star);
                        PrintXY(0,8,(unsigned char*)str,0);

                        if(i==0)
                        {
                            i=-1;
                            j=500*(AP+DP-Level);
                            sprintf(str,"AP:%3d   *3, $%d",AP,j);
                            PrintXY(j>=1000?9:12,24,(unsigned char*)str,0);
                            sprintf(str,"DP:%3d   *3, $%d",DP,j);
                            PrintXY(j>=1000?9:12,40,(unsigned char*)str,0);
                            Bdisp_AreaReverseVRAM(0,24,127,31);
                            Bdisp_PutDisp_DD();
                            while(IsKeyDown(KEY_CTRL_EXE))
                            {
                                Sleep(50);
                            }
                            t=0;
                            while(IsKeyUp(KEY_CTRL_EXIT))
                            {
                                if(IsKeyDown(KEY_CTRL_UP) && t==1 || IsKeyDown(KEY_CTRL_DOWN) && t==0)
                                {
                                    t=1-t;
                                    Bdisp_AreaReverseVRAM(0,24,127,31);
                                    Bdisp_AreaReverseVRAM(0,40,127,47);
                                    Bdisp_PutDisp_DD();
                                }
                                if(IsKeyDown(KEY_CTRL_EXE) && Coin>=j && Star>=3)
                                {
                                    Bdisp_AllClr_DDVRAM();
                                    Sleep(1000);
                                    Star-=3;
                                    Coin-=j;
                                    if(t==0)
                                    {
                                        AP++;
                                        sprintf(str,"AP Upgraded!");
                                    }
                                    else
                                    {
                                        DP++;
                                        sprintf(str,"DP Upgraded!");
                                    }
                                    PrintXY(28,28,(unsigned char*)str,0);
                                    Bdisp_PutDisp_DD();
                                    while(IsKeyUp(KEY_CTRL_EXE) && IsKeyUp(KEY_CTRL_EXIT))
                                    {
                                        Sleep(50);
                                    }
                                    break;
                                }
                                Sleep(50);
                            }
                        }
                        else
                        {
                            i=-1;
                            rank[0]=gsp[skill[0]%50];
                            rank[1]=gsp[skill[1]%50];
                            rank[2]=cmp[skill[2]%50];
                            rank[3]=dzp[skill[3]%50];
                            if(SkLv(Level,0))
                            {
                                if(skill[0]%50<30)
                                    sprintf(str,"Gut:%2d/30 *2,$%d",skill[0]%50,rank[0]);
                                else
                                    sprintf(str,"Gut:30/30 Max Gauge");
                                PrintXY(6,24,(unsigned char*)str,0);
                                if(SkLv(Level,1))
                                {
                                    if(skill[1]%50<30)
                                        sprintf(str,"Shl:%2d/30 *2,$%d",skill[1]%50,rank[1]);
                                    else
                                        sprintf(str,"Shl:30/30 Max Gauge");
                                    PrintXY(6,32,(unsigned char*)str,0);
                                    i=-2;
                                }
                                if(SkLv(Level,2))
                                {
                                    if(skill[2]%50<30)
                                        sprintf(str,"Clm:%2d/30 *3,$%d",skill[2]%50,rank[2]);
                                    else
                                        sprintf(str,"Clm:30/30 Max Gauge");
                                    PrintXY(6,40,(unsigned char*)str,0);
                                    i=-3;
                                }
                                if(SkLv(Level,3))
                                {
                                    if(skill[3]%50<30)
                                        sprintf(str,"Diz:%2d/30 *2,$%d",skill[3]%50,rank[3]);
                                    else
                                        sprintf(str,"Diz:30/30 Max Gauge");
                                    PrintXY(6,48,(unsigned char*)str,0);
                                    i=-4;
                                }
                                Bdisp_AreaReverseVRAM(0,24,127,31);
                                Bdisp_PutDisp_DD();
                                while(IsKeyDown(KEY_CTRL_EXE))
                                {
                                    Sleep(50);
                                }
                                t=0;
                                while(IsKeyUp(KEY_CTRL_EXIT))
                                {
                                    if(IsKeyDown(KEY_CTRL_UP) && t>0)
                                    {
                                        Bdisp_AreaReverseVRAM(0,24+8*t,127,31+8*t);
                                        t--;
                                        Bdisp_AreaReverseVRAM(0,24+8*t,127,31+8*t);
                                        Bdisp_PutDisp_DD();
                                        while(IsKeyDown(KEY_CTRL_UP))
                                        {
                                            Sleep(50);
                                        }
                                    }
                                    if(IsKeyDown(KEY_CTRL_DOWN) && t<-i-1)
                                    {
                                        Bdisp_AreaReverseVRAM(0,24+8*t,127,31+8*t);
                                        t++;
                                        Bdisp_AreaReverseVRAM(0,24+8*t,127,31+8*t);
                                        Bdisp_PutDisp_DD();
                                        while(IsKeyDown(KEY_CTRL_DOWN))
                                        {
                                            Sleep(50);
                                        }
                                    }
                                    if(IsKeyDown(KEY_CTRL_EXE) && Coin>=rank[t] && rank[t] && Star>=2+(t==2)*(1+(rank[6]==9)))
                                    {
                                        Bdisp_AllClr_DDVRAM();
                                        Sleep(1000);
                                        Star-=2+(t==2)*(1+(rank[6]==9));
                                        Coin-=rank[t];
                                        skill[t]++;
                                        if(t==0) sprintf(str,"Gut-skill Upgraded!");
                                        if(t==1) sprintf(str,"Shl-skill Upgraded!");
                                        if(t==2) sprintf(str,"Clm-skill Upgraded!");
                                        if(t==3) sprintf(str,"Diz-skill Upgraded!");
                                        PrintXY(6,28,(unsigned char*)str,0);
                                        Bdisp_PutDisp_DD();
                                        while(IsKeyUp(KEY_CTRL_EXE) && IsKeyUp(KEY_CTRL_EXIT))
                                        {
                                            Sleep(50);
                                        }
                                        break;
                                    }
                                    Sleep(50);
                                }
                            }
                            else
                            {
                                PrintXY(12,27,(unsigned char*)"You don't have",0);
                                PrintXY(57,37,(unsigned char*)"any Skills",0);
                                Bdisp_PutDisp_DD();
                                while(IsKeyDown(KEY_CTRL_EXE))
                                {
                                    Sleep(50);
                                }
                                while(IsKeyUp(KEY_CTRL_EXE) && IsKeyUp(KEY_CTRL_EXIT))
                                {
                                    Sleep(50);
                                }
                            }
                        }
                        if(i==0) RestoreDisp(SAVEDISP_PAGE1);
                        Bdisp_PutDisp_DD();
                    }
                    if(i<0) break;
                    Sleep(50);
                }
                y_axis=34;
                Refresh();
            }
            if((x_axis>=16 && x_axis<=43) && y_axis>=49 && Place%4==0)
            {
                Bdisp_AreaReverseVRAM(20,55,44,62);
                if(status==1)
                {
                    Bdisp_AreaClr_VRAM(&udisp);
                    PrintXY(15,4,(unsigned char*)"Curing Poison...",0);
                    for(i=1;i<126;i++)
                    {
                        Bdisp_AreaClr_VRAM(&sdisp);
                        Bdisp_AreaReverseVRAM(1,17,i,23);
                        Bdisp_PutDisp_DD();
                        if(IsKeyDown(KEY_CTRL_EXIT)) break;
                        Sleep(50);
                    }
                    if(i==126) status=0;
                }
                if(status==4)
                {
                    Bdisp_AreaClr_VRAM(&udisp);
                    PrintXY(15,4,(unsigned char*)"Curing Shiver...",0);
                    for(i=1;i<126;i++)
                    {
                        Bdisp_AreaClr_VRAM(&sdisp);
                        Bdisp_AreaReverseVRAM(1,17,i,23);
                        Bdisp_PutDisp_DD();
                        if(IsKeyDown(KEY_CTRL_EXIT)) break;
                        Sleep(70);
                    }
                    if(i==126) status=0;
                }
                Bdisp_AreaClr_VRAM(&udisp);
                i=0;
                sprintf(str,"%% /%10.3f",MHP);
                PrintXY(30,8,(unsigned char*)str,0);
                while(IsKeyUp(KEY_CTRL_EXIT) && IsKeyUp(KEY_CTRL_UP) && IsKeyUp(KEY_CTRL_AC))
                {
                    HP+=pow(1.01,i++)-.6;
                    if(HP>MHP) HP=MHP;
                    sprintf(str,"HP:  %10.3f",HP);
                    PrintXY(18,0,(unsigned char*)str,0);
                    sprintf(str,"%2u",(int)((100*HP+0.0001)/MHP));
                    Bdisp_AreaClr_VRAM(&sdisp);
                    Bdisp_AreaReverseVRAM(1,17,(int)((125*HP+0.0001)/MHP)+1,23);
                    PrintXY(18,8,(unsigned char*)str,0);
                    Bdisp_PutDisp_DD();
                    Sleep(50);
                }
                y_axis=46;
                Bdisp_AreaReverseVRAM(20,55,44,62);
                drawUwin(uwin);
            }
            if((x_axis>=79 && x_axis<=106) && y_axis>=49 && Place%4==0)
            {
                Bdisp_AllClr_DDVRAM();
                if(Place==0)
                {
                    PrintXY(6,8,(unsigned char*)"Press [EXE] to play",0);
                    PrintXY(6,8,(unsigned char*)"Push Much",0);


                    PopUpWin(5);
                    PrintXY(15,8,(unsigned char*)"*Push Much*",0);
                    PrintXY(15,16,(unsigned char*)"Press F1 rapidly",0);
                    SaveDisp(SAVEDISP_PAGE1);
                    for(i=3;i>=0;i--)
                    {
                        if(i)
                        {
                            sprintf(str,"Ready(%d)",i);
                            PrintXY(39,32,(unsigned char*)str,0);
                        }
                        else
                            PrintXY(36,32,(unsigned char*)"   GO!   ",0);
                        Bdisp_PutDisp_DD();
                        Sleep(725);
                    }
                    j=800+7*Level;
                    k=t=0;
                    for(i=0;i<=j;i++)
                    {
                        if(k && IsKeyDown(KEY_CTRL_F1))
                        {
                            k=0;
                            t++;
                        }
                        if(IsKeyUp(KEY_CTRL_F1))
                            k++;
                        RestoreDisp(SAVEDISP_PAGE1);
                        sprintf(str,"Press:%d",t);
                        PrintXY(38,32,(unsigned char*)str,0);
                        sprintf(str,"Coin:%d",(t+25)*t*(40+Level)/80000);
                        PrintXY(38,40,(unsigned char*)str,0);
                        Bdisp_AreaReverseVRAM(i*97/j+15,26,112,29);
                        Bdisp_PutDisp_DD();
                        Sleep(10);
                    }
                }
                if(Place>=4)
                {
                    PrintXY(20,20,(unsigned char*)"It is not",0);
                    PrintXY(20,30,(unsigned char*)"implemented yet",0);
                    Bdisp_PutDisp_DD();
                    while(IsKeyUp(KEY_CTRL_EXIT) && IsKeyUp(KEY_CTRL_EXE))
                    {
                        GetKeyWait(KEYWAIT_HALTON_TIMEROFF,0,1,&key);
                    }
                }
                y_axis=46;
                Refresh();
            }
            PrintXY(x_axis,y_axis,(unsigned char*)"C",0);
            Bdisp_PutDisp_DD();
            if(IsKeyDown(KEY_CTRL_AC))
                quit=1;
            if(rand()%70==0 && Place%4!=0 && work>17)
            {
                i=0;
                if((rand()%50)<1) i=3;
                else if(AP>1 && (rand()%7500/(1+4*(dno==99))<(120+AP)) && Level<400) i=5;
                else if(Level>=2 && (j=(rand()%1600)/(1+4*(dno==99)))<72+5*Level-4*Place && j<500 && HP<999999.999) i=1;
                else if((rand()%3000)/(1+4*(dno==99))<50+DP) i=3;
                if(i && rand()%15==1) i++;

                if(Place==1)
                    if(Level==0) Battle(3,1,0,1,2,1,0);
                    else Battle(7,1,0,1,4,1,i);
                if(Place==2) Battle(12,2,0,1,10,2,i);
                if(Place==3) Battle(11.1,2,2,1,16,3,i);
                if(Place==5) Battle(20,3,0,10,25,5,i);
                if(Place==6) Battle(40,3,0,12,46,6,i);
                if(Place==7) Battle(60,3,0,14,66,7,i);
                if(Place==9) Battle(43,4,3,20,125,8,i);
                if(Place==10) Battle(67,5,1,22,162,9,i);
                if(Place==11) Battle(48,5,5,25,211,10,i);
                if(Place==13) Battle(99,7,0,31,266,12,i);
                if(Place==14) Battle(99,7,4,34,409,13,i);
                if(Place==15) Battle(137,7,6,37,600,15,i);
                if(Place==17) Battle(160,8,2,43,525,15,i);
                if(Place==18) Battle(75,12,1,46,442,16,i);
                if(Place==19) Battle(156,9,3,49,630,17,i);
                if(Place==21) Battle(70,8,12,55,788,18,i);
                if(Place==22) Battle(81,9,13,58,986,19,i);
                if(Place==23) Battle(93,10,14,62,1214,20,i);
                if(Place==25) Battle(180,15,5,68,1281,23,i);
                if(Place==26) Battle(187,16,5,71,1397,25,i);
                if(Place==27) Battle(196,17,6,75,1621,27,i);
                if(Place==29) Battle(754,18,0,81,2106,30,i);
                if(Place==30) Battle(823,19,0,84,2306,32,i);
                if(Place==31) Battle(958,20,0,88,2583,34,i);
                if(Place==33) Battle(784,19,4,94,2832,37,i);
                if(Place==34) Battle(695,20,8,98,3456,38,i);
                if(Place==35) Battle(824,20,11,101,4167,40,i);
                if(Place==37) Battle(1821,23,7,108,5095,44,i);
                if(Place==38) Battle(250,28,3,111,2908,45,i);
                if(Place==39) Battle(2000,24,8,115,5705,48,i);
                if(Place==41) Battle(4742,16,18,122,7726,53,i);
                if(Place==42) Battle(5025,17,20,125,8682,57,i);
                if(Place==43) Battle(5310,19,19,129,9126,61,i);
                if(Place==45) Battle(4427,28,11,136,9113,62,i);
                if(Place==46) Battle(4428,29,12,139,9739,65,i);
                if(Place==47) Battle(4517,29,14,143,10451,68,i);
                if(Place==49) Battle(4567,30,16,150,11547,71,i);
                if(Place==50) Battle(4671,31,16,153,11982,74,i);
                if(Place==51) Battle(4700,33,17,157,13123,77,i);
                if(Place==53) Battle(2750,38,19,164,14389,79,i);
                if(Place==54) Battle(2400,40,20,167,15229,81,i);
                if(Place==55) Battle(2300,41,21,171,15982,83,i);
                if(Place==57) Battle(29999,29,4,178,12155,88,i);
                if(Place==58) Battle(30000,31,5,182,13288,93,i);
                if(Place==59) Battle(5000,50,8,185,16902,94,i);
                if(Place==61) Battle(3621,57,3,213,17144,98,i);
                if(Place==62) Battle(3127,58,4,216,17593,101,i);
                if(Place==63) Battle(3200,60,5,220,19103,104,i);
                if(Place==65) Battle(8750,52,10,227,21359,107,i);
                if(Place==66) Battle(12144,51,10,231,22147,110,i);
                if(Place==67) Battle(13500,53,9,235,23149,113,i);
                if(Place==69) Battle(750,73,5,5,15043,114,i);
                if(Place==70) Battle(5425,55,20,246,26870,117,i);
                if(Place==71) Battle(6715,52,25,249,29088,119,i);
            }
            if(HP<1)
            {
                Bdisp_AllClr_DDVRAM();
                HP=1.0;
                if(Coin<2*Level) i=Coin;
                else i=2*Level;
                Coin-=i;
                quit=1;
            }
            else
            {
                if(IsKeyDown(KEY_CTRL_OPTN)) menu(3);
                if(IsKeyDown(KEY_CTRL_VARS)) menu(1);
                if(IsKeyDown(KEY_CTRL_MENU)) menu(0);
            }
            if(quit==1)
            {
                saveDat(dno);
                break;
            }

            if(Place>=29 && rand()%9999==0 && status==0)
            {
                status=3;
                for(i=0;i<4;i++)
                {
                    Bdisp_AreaReverseVRAM(1,25,126,62);
                    Bdisp_PutDisp_DD();
                    Sleep(450);
                }
                Refresh();
                PopUpWin(3);
                PrintXY(18,16,(unsigned char*)"You became",0);
                PrintXY(66,32,(unsigned char*)"Grassd.",0);
                Bdisp_PutDisp_DD();
                Sleep(1750);
                Refresh();
            }
            if(Place%4!=0)
            {
                work++;
                if(rand()%99==1 && event[0]<255) event[0]++;
                if(dno==99 && rand()%4==1 && event[0]<255) event[0]++;
            }
            if(rand()%16384<(event[0]-92)/8)
            {
                PrintXY(x_axis,y_axis,(unsigned char*)"C",0);
                SaveDisp(SAVEDISP_PAGE1);
                do
                {
                    j=25+3*(rand()%11);
                }while(Place%4==0 && (j>34 && j<46));
                for(i=121;i>=x_axis;i-=3)
                {
                    PrintXY(i,j,(unsigned char*)"E",0);
                    Bdisp_PutDisp_DD();
                    Sleep(40);
                    RestoreDisp(SAVEDISP_PAGE1);
                }
                if(y_axis>j-9 && y_axis<j+9)
                {
                    PrintXY(x_axis,y_axis,(unsigned char*)" ",0);
                    if(y_axis==j-6 || y_axis==j+6) i=5;
                    else if(y_axis==j-3 || y_axis==j+3) i=10;
                    else i=25;
                    if(y_axis<j || (y_axis==j && y_axis>=40)) y_axis=j-9;
                    else y_axis=j+9;
                    if(y_axis>46)
                    {
                        y_axis=j-9;
                        i=20;
                    }
                    if(y_axis<34)
                    {
                        y_axis=j+9;
                        i=20;
                    }
                    PrintXY(x_axis,y_axis,(unsigned char*)"C",0);
                    HP=(int)HP;
                    t=(int)(5000+(rand()%5000)*i*MHP/500000.0)+1;
                    if(t>(int)(0.02*i*HP)) t=(int)(0.02*i*HP);
                    HP-=t;
                    if(uwin==2) drawUwin(2);
                    SaveDisp(SAVEDISP_PAGE1);
                    PrintXY(x_axis,j,(unsigned char*)"E",0);
                    PopUpWin(3);
                    PrintXY(21,16,(unsigned char*)"You are hit by",0);
                    PrintXY(21,24,(unsigned char*)"Evost!",0);
                    sprintf(str,"HP-%u",t);
                    PrintXY(21,32,(unsigned char*)str,0);
                    Bdisp_PutDisp_DD();
                    Sleep(500);
                    while(IsKeyUp(KEY_CTRL_EXE))
                    {
                        Sleep(50);
                    }
                    RestoreDisp(SAVEDISP_PAGE1);
                    PrintXY(x_axis,j,(unsigned char*)"E",0);
                    PopUpWin(2);
                    PrintXY(18,16,(unsigned char*)"Evost:",0);
                    PrintXY(18,24,(unsigned char*)"Oops, sorry!",0);
                    Bdisp_PutDisp_DD();
                    Sleep(500);
                    while(IsKeyUp(KEY_CTRL_EXE))
                    {
                        Sleep(50);
                    }
                    RestoreDisp(SAVEDISP_PAGE1);
                }
                PrintXY(x_axis,y_axis,(unsigned char*)"C",0);
                SaveDisp(SAVEDISP_PAGE1);
                PrintXY(x_axis,j,(unsigned char*)"E",0);
                PopUpWin(5);
                PrintXY(18,8,(unsigned char*)"Evost: Here,",0);
                PrintXY(18,16,(unsigned char*)"I'll give you a",0);
                PrintXY(18,24,(unsigned char*)"Star for",0);
                i=(int)(0.001*Stage*(rand()%10000)+4.8*pow(Stage,1.41)+pow(AP+DP,1.28)+125);
                if(i>9999) i=9999;
                sprintf(str,"%u coins!",i);
                PrintXY(18,32,(unsigned char*)str,0);
                PrintXY(18,40,(unsigned char*)"1:OK!     2:No.",0);
                Bdisp_PutDisp_DD();
                Sleep(500);
                key=0;
                do
                {
                    if(IsKeyDown(KEY_CHAR_1)) key=1;
                    else if(IsKeyDown(KEY_CHAR_2)) key=2;
                    Sleep(50);
                }while(key!=1 && key!=2);
                RestoreDisp(SAVEDISP_PAGE1);
                if(key==1)
                {
                    if(Coin<i)
                    {
                        i/=-2;
                        PrintXY(x_axis,j,(unsigned char*)"E",0);
                        PopUpWin(3);
                        PrintXY(18,16,(unsigned char*)"Oh, you don't",0);
                        PrintXY(18,24,(unsigned char*)"have enough",0);
                        PrintXY(18,32,(unsigned char*)"Coins... sorry.",0);
                        Bdisp_PutDisp_DD();
                        Sleep(500);
                        while(IsKeyUp(KEY_CTRL_EXE))
                        {
                            Sleep(50);
                        }
                        RestoreDisp(SAVEDISP_PAGE1);
                    }
                    else if(Star>=255)
                    {
                        i/=-2;
                        PrintXY(x_axis,j,(unsigned char*)"E",0);
                        PopUpWin(3);
                        PrintXY(18,16,(unsigned char*)"Oh, you maxed",0);
                        PrintXY(18,24,(unsigned char*)"out the limit",0);
                        PrintXY(18,32,(unsigned char*)"of Stars...",0);
                        Bdisp_PutDisp_DD();
                        Sleep(500);
                        while(IsKeyUp(KEY_CTRL_EXE))
                        {
                            Sleep(50);
                        }
                        RestoreDisp(SAVEDISP_PAGE1);
                    }
                    else
                    {
                        Coin-=i;
                        Star++;
                        event[0]=event[0]*7/10-70;
                        if(uwin==3) drawUwin(3);
                        SaveDisp(SAVEDISP_PAGE1);
                        PrintXY(x_axis,j,(unsigned char*)"E",0);
                        PopUpWin(3);
                        PrintXY(18,16,(unsigned char*)"Thanks! The",0);
                        PrintXY(18,24,(unsigned char*)"Star will help",0);
                        PrintXY(18,32,(unsigned char*)"you a lot!",0);
                        Bdisp_PutDisp_DD();
                        Sleep(500);
                        while(IsKeyUp(KEY_CTRL_EXE))
                        {
                            Sleep(50);
                        }
                        RestoreDisp(SAVEDISP_PAGE1);
                    }
                }
                else i/=-2;
                if(i<0)
                {
                    y=Coin;
                    Coin-=i;
                    event[0]=event[0]*9/10-35;
                    if(uwin==3) drawUwin(3);
                    SaveDisp(SAVEDISP_PAGE1);
                    PrintXY(x_axis,j,(unsigned char*)"E",0);
                    if(Coin>2500000) Coin=2500000;
                    PopUpWin(3);
                    PrintXY(18,16,(unsigned char*)"Instead, I'll",0);
                    PrintXY(18,24,(unsigned char*)"give you",0);
                    sprintf(str,"%u Coins!",Coin-y);
                    PrintXY(18,32,(unsigned char*)str,0);
                    Bdisp_PutDisp_DD();
                    Sleep(500);
                    while(IsKeyUp(KEY_CTRL_EXE))
                    {
                        Sleep(50);
                    }
                    RestoreDisp(SAVEDISP_PAGE1);
                    PrintXY(x_axis,j,(unsigned char*)"E",0);
                }
                for(i=x_axis;i>=1;i-=3)
                {
                    PrintXY(i,j,(unsigned char*)"E",0);
                    Bdisp_PutDisp_DD();
                    Sleep(40);
                    RestoreDisp(SAVEDISP_PAGE1);
                }
            }

            if(rand()%10000==0)
            {
                i=rand()%10;
                if(i<2)
                {
                }
                else if(i<7)
                {
                }
                else
                {
                }
            }
            if(status==1)
            {
                HP-=0.04;
                if(HP<1.0) HP=1.0;
                if(uwin==2 && HP-(int)HP>=0.96)
                {
                    sprintf(str,"HP  %6u/%6u",(unsigned int)HP,(unsigned int)MHP);
                    PrintXY(12,0,(unsigned char*)str,0);
                }
            }

            Sleep(50);
        }
    }
    return 1;
}




//****************************************************************************
//**************                                              ****************
//**************                 Notice!                      ****************
//**************                                              ****************
//**************  Please do not change the following source.  ****************
//**************                                              ****************
//****************************************************************************


#pragma section _BR_Size
unsigned long BR_Size;
#pragma section


#pragma section _TOP

//****************************************************************************
//  InitializeSystem
//
//  param   :   isAppli   : 1 = Application / 0 = eActivity
//              OptionNum : Option Number (only eActivity)
//
//  retval  :   1 = No error / 0 = Error
//
//****************************************************************************
int InitializeSystem(int isAppli, unsigned short OptionNum)
{
    return INIT_ADDIN_APPLICATION(isAppli, OptionNum);
}

#pragma section


