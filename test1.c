#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<ctype.h>
int main()
{
    int len;
    FILE *fp1=fopen("file1.txt","a+");
    FILE *fp2=fopen("file2.txt","w+");
    FILE *cover=fopen("story.txt","r");
    FILE *key=fopen("stegokey.txt","w+");
    FILE *out=fopen("out.txt","w+");
    if(fp1==NULL)
        printf("file not found");
    char c1,c2;
    //ASCII to binary                                                                                               
    while(!feof(fp1))
    {
        c1=fgetc(fp1);//reads each letter one by one
        if(c1!=-1)
        {
            for(int i=1;i<=128;i=i*2)
            {
                c2=(c1&(128/i))?'1':'0';
                //printf("%c",c2);
                fputc(c2,fp2);
            }
            
        }
    }
    //printf("\n");
    rewind(fp1);
    rewind(fp2);
    //Hide algorithm
    while(!feof(fp2))
    { 
        char c3,s,e;
        char str[100];
        fscanf(cover,"%s",str);
        s=str[0];
        e=str[strlen(str)-1];
        if(s==e)
            continue;
        c3=fgetc(fp2);
        if(c3!=-1)
        {
            if(c3=='1')
                fputc(e,key);
            else
                fputc(s,key);
        }    
        
    }
    rewind(key);
    rewind(cover);
    //Seek algorithm
    while(!feof(key))
    { 
        char c4,s,e;
        char str[100];
        fscanf(cover,"%s",str);
        s=str[0];
        e=str[strlen(str)-1];
        //printf("\ns=%c  e=%c\n",s,e);
        if(s==e)
            continue;
        
        c4=fgetc(key);
        //printf("%c\t",c4);
        if(c4!=-1)
        {
            if(c4==s)
                fputc('0',out);
            else
                fputc('1',out);
        }
    len=ftell(out);
    }
    
    //printf("len=%d\n",len);
    rewind(out);
    //char ch;
    //while((ch=fgetc(out)!=EOF))
    //Binary to ASCII
    while(!feof(out))
    { 
        char string[8],c5;
        int bin=0,count=0;
        fgets(string,9,out);
        //printf("%s\n",string);
        for(int i=0;string[i]!='\0';i++)
           {
               if(string[i]-'0')
                bin=bin+pow(2,7-i);
                //printf("%d\t",bin);
           } 
           
          //printf("len = %d\n",ftell(out));
           //printf("\n");
           printf("%c",bin);
            if(len==ftell(out)) 
                break;
                


    }
        
}