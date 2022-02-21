#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
//i can edit
void hide(FILE *inputf,FILE *cover,FILE *key)
{
    //file2 stores the binary values of the chracters stored in the input file
    FILE *fp2=fopen("file2.txt","w+");
    char c1,c2;
    //c1 gets each character for file and c2 stores either 0 or 1 to the binary file
    c1=fgetc(inputf);
    while(!feof(inputf))
    {
        for(int i=1;i<=128;i=i*2)
        {
            c2=(c1&(128/i))?'1':'0';
            fputc(c2,fp2);
        }
        c1=fgetc(inputf);
    }
    rewind(inputf);
    rewind(fp2);
    //applying HIDE algorithm
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
    rewind(cover);
    //to copy the contents of cover file to input file
    c1=fgetc(cover);
    while(!feof(cover))
    {
        fputc(c1,inputf);
        c1=fgetc(cover);
    }
    fclose(fp2);
}

void seek(FILE *inputf,FILE *key,char *fname)
{
    //out stores the binary values of characters after decoding
    FILE *out=fopen("out.txt","w+");
    int len;
    //Applying SEEK algorithm
    while(!feof(key))
    { 
        char c,s,e;
        char str[100];
        fscanf(inputf,"%s",str);
        s=str[0];
        e=str[strlen(str)-1];
        if(s==e)
            continue;
        
        c=fgetc(key);
        if(c!=-1)
        {
            if(c==s)
                fputc('0',out);
            else
                fputc('1',out);
        }
    len=ftell(out);
    }
    rewind(out);
    //to copy the binary contents of file out back to inputf
    //clear the contents of inputf and open it in write mode
    fclose(inputf);
    inputf=fopen(fname,"w");
    while(!feof(out))
    { 
         
        char string[8];
        int bin=0;
        fgets(string,9,out);
        for(int i=0;string[i]!='\0';i++)
        {
            if(string[i]-'0')
            bin=bin+pow(2,7-i);
        } 
        fputc(bin,inputf);
        if(len==ftell(out)) 
            break;
    }
    fclose(out);
}

int main()
{
    int ch;char fname[100];
    FILE *cover=fopen("story.txt","r"),*key=fopen("stegokey.txt","a+");
    while(1)
    {
        FILE *inputf=NULL;
        printf("1.Encoding\n2.Decoding\n3.Exit\nEnter your choice:");
        scanf("%d",&ch);
        switch (ch)
        {
        case 1: printf("enter text file name(Without .txt extension):");
                scanf("%s",fname);
                strcat(fname,".txt");
                inputf=fopen(fname,"r+");
                if(inputf==NULL)
                    printf("enter valid file name\n");
                else
                {
                    hide(inputf,cover,key);
                    printf("Your file is encoded.\nPlease check your file\n");
                }
                fclose(inputf);
                break;
        case 2: printf("enter text file name(Without .txt extension):");
                scanf("%s",fname);
                strcat(fname,".txt");
                inputf=fopen(fname,"r+");
                if(inputf==NULL)
                    printf("enter valid file name\n");
                else
                {
                    seek(inputf,key,fname);
                    printf("your file is decoded.\nPlease check your file\n");
                }
                fclose(inputf);
                break;
        case 3: exit(0);
        default:
            printf("Enter valid input\n");
        }
    }
}
