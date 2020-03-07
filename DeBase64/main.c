#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char MyInput[5];
char MyOutput[5];

FILE * Input;
FILE * Output;

void WriteToFile(int N)
{
    int I;
    for (I=0;I<=N;I++)
    {
        fprintf(Output,"%c",MyOutput[I]);
    }
}

void DecodeTranslate(int N)
{
    int I;
    for (I=0; I<=N; I++)
    {
        switch (MyInput[I])
        {
        case 'A' ... 'Z':
            MyInput[I]=MyInput[I]-'A';
            break;
        case 'a' ... 'z':
            MyInput[I]=MyInput[I]+26-'a';
            break;
        case '0' ... '9':
            MyInput[I]=MyInput[I]+52-'0';
            break;
        case '+':
            MyInput[I]=62;
            break;
        case '/':
            MyInput[I]=63;
            break;
        }
    }
}

int main()
{
    int I,C;
    Input=fopen("Input.txt","r");
    Output=fopen("Output.txt","w");
    memset(MyInput,0,4);
    while (1)
    {
        for (I=0;I<4;)
        {
            C=fread(&MyInput[I],1,1,Input);
            if (feof(Input))
                goto Out;
            if (MyInput[I]=='=')
                goto Out;
            if (MyInput[I]!='\n')
                I++;
        }
        memset(MyOutput,0,5);
        DecodeTranslate(4);
        MyOutput[0]=(MyInput[0]<<2)+(MyInput[1]>>4);
        MyOutput[1]=((MyInput[1])<<4)+((MyInput[2])>>2);
        MyOutput[2]=((MyInput[2])<<6)+((MyInput[3]));
        WriteToFile(2);
        memset(MyInput,0,5);
    }
    Out:
    if (I==2)
    {
        memset(MyOutput,0,5);
        DecodeTranslate(1);
        MyOutput[0]=(MyInput[0]<<2)+(MyInput[1]>>4);
        WriteToFile(0);
    }
    else if (I==3)
    {
        memset(MyOutput,0,5);
        DecodeTranslate(2);
        MyOutput[0]=(MyInput[0]<<2)+(MyInput[1]>>4);
        MyOutput[1]=((MyInput[1])<<4)+((MyInput[2])>>2);
        WriteToFile(1);
    }
    fclose(Input);
    fclose(Output);
    return 0;
}
