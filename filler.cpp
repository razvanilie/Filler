#include <iostream>
#include <graphics.h>
#include <time.h>
#include <cstdlib>
#include <cstring>
using namespace std;
int v[100],op=0,ss=0;
char ttt[20]="",mutari[100]="",txt[30]="FELICITARI!",txtt[30]="Ai castigat!";
int a[100][100],b[100][100],bb[100][100],size=0,k,sp=1,d=19,x,y,brb;
void fill(int i,int j,int k)
{

    if(a[i][j]==5 or (bb[i][j]==k and op==0) or (brb>=1 and brb<=4 and a[i][j]==brb))
    {

        a[i][j]=6;
        bb[i][j]=3; // fiecarei element din regiune ii corespunde numarul zonei
        size++;
        x=sp+(j-1)*(d+sp);
        y=sp+(i-1)*(d+sp);
        setcolor(11);
        rectangle(x,y, x+d,y+d);
        if(brb==1)
            setfillstyle(9,12);
        if(brb==2)
            setfillstyle(9,10);
        if(brb==3)
            setfillstyle(9,14);
        if(brb==4)
            setfillstyle(9,9);
        floodfill(x+3,y+3,11);
        /*verificam daca elementele alaturate pot apartine aceiasi regiuni si daca nu au fost
          inca marcate*/
        fill(i-1,j,k);
        fill(i+1,j,k);
        fill(i,j-1,k);
        fill(i,j+1,k);


    }
}


int main()
{
    int nl=30,nc=50,baza=100,ii;
    int i, j;
    int W=nc*(d+sp)+sp;
    int H=nl*(d+sp)+sp+baza;
    int Top=sp,Left=sp;
    initwindow(W,H,"Filler");
    settextstyle(1,0,4);



    setcolor(10);
///----GENERARE VALORI--------------
    int w;
    srand(time(NULL));
    for(i=1; i<=nl; i++)
        for(j=1; j<=nc; j++)
        {
            do
                w=rand()%4+1;
            while(v[w]==nl*nc/4+2*nl);// Generare suplimentara
            a[i][j]=w;
            if(a[i][j]==1)
            {
                b[i][j]=12;
                bb[i][j]=12;
            }
            if(a[i][j]==2)
            {
                b[i][j]=10;
                bb[i][j]=10;
            }
            if(a[i][j]==3)
            {
                b[i][j]=14;
                bb[i][j]=14;
            }
            if(a[i][j]==4)
            {
                b[i][j]=9;
                bb[i][j]=9;
            }
            v[w]++;

        }
///----GENERARE VALORI--------------
///----DESENARE CONTUR--------------
    for(i=1; i<=nl; i++)
        for(j=1; j<=nc; j++)
        {
            x=Left+(j-1)*(d+sp);
            y=Top+(i-1)*(d+sp);
            rectangle(x,y, x+d,y+d);
            if(a[i][j]==1)
            {
                setfillstyle(9,12);
                floodfill(x+3,y+3,10);
            }
            else if(a[i][j]==2)
            {
                setfillstyle(9,10);
                floodfill(x+3,y+3,10);
            }
            else if(a[i][j]==3)
            {
                setfillstyle(9,14);
                floodfill(x+3,y+3,10);
            }
            else if(a[i][j]==4)
            {
                setfillstyle(9,9);
                floodfill(x+3,y+3,10);
            }
        }
///----DESENARE CONTUR--------------
///----BAZA JOCULUI--------------
    setcolor(2);
    rectangle(0,nl*(d+sp)+sp,nc*(d+sp)+sp,nl*(d+sp)+sp+baza);
    setfillstyle(11, 2);
    floodfill(W/2, nl*(d+sp)+sp+(baza/2), 2);
    int vrp[4][2],vrpp[4][2],vrppp[5];
    for(i=1; i<=4; i++)
    {
        setcolor(13);
        x=(nc*(d+sp)+sp-4*(baza/5*3))/5*i+(baza/5*3)*(i-1);
        y=nl*(d+sp)+sp+baza/5;
        rectangle(x,y,x+baza/5*3,y+baza/5*3);
        vrp[i][1]=x;
        vrp[i][2]=y;
        vrpp[i][1]=x+baza/5*3;
        vrpp[i][2]=y+baza/5*3;
        if(i==1)
        {
            setfillstyle(9,12);
            floodfill(x+3,y+3,13);
        }
        else if(i==2)
        {
            setfillstyle(9,10);
            floodfill(x+3,y+3,13);
        }
        else if(i==3)
        {
            setfillstyle(9,14);
            floodfill(x+3,y+3,13);
        }
        else if(i==4)
        {
            setfillstyle(9,9);
            floodfill(x+3,y+3,13);
        }


    }
    setcolor(15);
        x=Left+d+sp;
        y=Top+30*(d+sp)+baza/5;
        rectangle(x,y, x+d+d,y+d+d);
        setfillstyle(1,b[nl][1]);
        floodfill(x+3,y+3,15);
        setfillstyle(9,b[nl][1]);
///----BAZA JOCULUI--------------
    int oko=1;
    if(oko==1)
    {
        a[nl][1]=5;
        for(i=1; i<=nl; i++)
            for(j=1; j<=nc; j++)
                if(a[i][j]==5)
                {
                    k=bb[i][j];
                    fill(i,j,k);


                }
        for(i=1; i<=nl; i++)
            for(j=1; j<=nc; j++)
                if(a[i][j]==6)
                {
                    a[i][j]=5;
                    bb[i][j]=b[i][j];
                }
        oko=2;

    }

///----JOCUL.RESTUL--------------
    int nrr,nrc,xo,yo;
    while(!kbhit())//atat timp cat nu am apasat o tasta
    {
        if (ismouseclick(WM_LBUTTONDOWN))
        {
            getmouseclick(WM_LBUTTONDOWN, x, y);
            if(x<W-1 && y<H-baza-1)
            {
                nrr=y/(d+sp)+1;
                nrc=x/(d+sp)+1;
                xo=(d+sp)*(nrc-1)+d/2;
                yo=(d+sp)*(nrr-1)+d/2;
                setfillstyle(9,b[nrr][nrc]);
                floodfill(xo,yo,10);

            }
            if(x<W-1 && y<H-1)
            {

                for(ii=1; ii<=4; ii++)

                    if(vrp[ii][1]<x && vrp[ii][2]<y && vrpp[ii][1]>x && vrpp[ii][2]>y)
                    {op++;
                        brb=ii;
                                setcolor(15);
        x=Left+d+sp;
        y=Top+30*(d+sp)+baza/5;
        rectangle(x,y, x+d+d,y+d+d);
        if(brb==1)
            setfillstyle(1,12);
        if(brb==2)
            setfillstyle(1,10);
        if(brb==3)
            setfillstyle(1,14);
        if(brb==4)
            setfillstyle(1,9);
        floodfill(x+3,y+3,15);
                    }
                a[nl][1]=5;
                for(i=1; i<=nl; i++)
                    for(j=1; j<=nc; j++)
                        if(a[i][j]==5)
                        {
                            size=0;
                            k=bb[i][j];
                            fill(i,j,k);


                        }
                for(i=1; i<=nl; i++)
                    for(j=1; j<=nc; j++)
                        if(a[i][j]==6)
                        {
                            a[i][j]=5;

                            bb[i][j]=b[i][j];
                        }
            }

            cout<<"op: "<<op<<endl;
            itoa(size/15,ttt,10);
            itoa(op,mutari,10);
            strcat(ttt,"%");
            if(op==1)
            strcat(mutari," mutare");
            else if(op>1 and op<20)
            strcat(mutari,"   mutari");
            else
            strcat(mutari," de mutari");
            settextstyle(1, HORIZ_DIR, 1);
            outtextxy(Left+(d+sp)*4-d/2-sp/2,Top+30*(d+sp)+baza/5,ttt);
            settextstyle(11, HORIZ_DIR, 1);
            outtextxy(Left+(d+sp)*4-d/2-sp/2,Top+30*(d+sp)+2*baza/5,mutari);
            if(size>750)
            {settextstyle(8, HORIZ_DIR, 1);
            setcolor(2);
            outtextxy(Left+d+sp,Top+30*(d+sp)+3*baza/5,txt);
            outtextxy(Left+d+sp,Top+30*(d+sp)+4*baza/5,txtt);}
            if(size==1500)
                main();

        }
    }

///----JOCUL.RESTUL--------------
    delay(60000);
    return 0;
}
