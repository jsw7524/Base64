#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char MyInput[4];
char MyOutput[5];

FILE * Input;
FILE * Output;

void WriteToFile(int N)
{
    static X=0;
    int I;
    for (I=0;I<=N;I++)
    {
        fprintf(Output,"%c",MyOutput[I]);
        X++;
        if (X==76)
        {
            fprintf(Output,"\n");
            X=0;
        }
    }
}

void Translate(int N)
{
    int I;
    for (I=0; I<=N; I++)
    {
        switch (MyOutput[I])
        {
        case 0 ... 25:
            MyOutput[I]=MyOutput[I]+'A';
            break;
        case 26 ... 51:
            MyOutput[I]=MyOutput[I]-26+'a';
            break;
        case 52 ... 61:
            MyOutput[I]=MyOutput[I]-52+'0';
            break;
        case 62:
            MyOutput[I]='+';
            break;
        case 63:
            MyOutput[I]='/';
            break;
        default:
            MyOutput[I]='=';
        }
    }
    WriteToFile(N);
}

int main()
{
    int I,C;
    Input=fopen("Input.txt","r");
    Output=fopen("Output.txt","w");
    memset(MyInput,0,4);
    while (3==(C=fread(MyInput,1,3,Input)))
    {
        memset(MyOutput,0,5);
        MyOutput[0]=(MyInput[0]&0xfc)>>2;
        MyOutput[1]=((MyInput[0]&0x03)<<4)+((MyInput[1]&0xf0)>>4);
        MyOutput[2]=((MyInput[1]&0x0f)<<2)+((MyInput[2]&0xc0)>>6);
        MyOutput[3]=((MyInput[2]&0x3f));
        Translate(3);
        memset(MyInput,0,4);
    }
    if (C==1)
    {
        memset(MyOutput,0,5);
        MyOutput[0]=(MyInput[0]&0xfc)>>2;
        MyOutput[1]=((MyInput[0]&0x03)<<4)+((MyInput[1]&0xf0)>>4);
        Translate(1);
        fprintf(Output,"==",MyOutput);
    }
    else if (C==2)
    {
        memset(MyOutput,0,5);
        MyOutput[0]=(MyInput[0]&0xfc)>>2;
        MyOutput[1]=((MyInput[0]&0x03)<<4)+((MyInput[1]&0xf0)>>4);
        MyOutput[2]=((MyInput[1]&0x0f)<<2)+((MyInput[2]&0xc0)>>6);
        Translate(2);
        fprintf(Output,"=",MyOutput);
    }
    fclose(Input);
    fclose(Output);
    return 0;
}
