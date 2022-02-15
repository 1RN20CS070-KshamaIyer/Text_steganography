#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<ctype.h>
struct node
{
    int check;
    FILE *cover;
    FILE *key;
    struct node *link;
};
typedef struct node *NODE;

NODE getnode()
{
    NODE x;
    x=(NODE)malloc(sizeof(struct node));
    if(x==NULL)
    {
        printf("Memory not available\n");
        exit(0);
    }
    return x;
}
void insert (NODE head,FILE *cover,FILE *key)
{
    NODE temp,cur;
    temp=getnode();
    temp->cover=cover;
    temp->key=key;
    temp->check=0;
    temp->link=NULL;
    cur=head;
    while(cur->link!=NULL)
        cur=cur->link;
    cur->link=temp;
}
/*void display(NODE head)
{
    NODE cur=head->link;
    while(cur!=NULL)
    {
        char c[100];
        fscanf(cur->cover,"%s",c);
        printf("%s\n",c);
        cur=cur->link;
    }
}*/
void hide (FILE *inputf,NODE head)
{
    FILE *fp2=fopen("file2.txt","w+");
    NODE cur=head->link;
    while(cur!=NULL && cur->check!=0)
        cur=cur->link;
    char c1,c2;
    //ASCII to binary                                                                                               
    while(!feof(inputf))
    {
         c1=fgetc(inputf);//reads each letter one by one
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
    rewind(inputf);
    rewind(fp2);
    //rewind(cur->cover);
     //Hide algorithm
    while(!feof(fp2))
    { 
        
        char c3,s,e;
        char str[100];
        fscanf(cur->cover,"%s",str);
        s=str[0];
        e=str[strlen(str)-1];
        if(s==e)
            continue;
            
        c3=fgetc(fp2);
        //printf("%d",c3);
        if(c3!=-1)
        {
            
            if(c3=='1')
                fputc(e,cur->key);
            else
                fputc(s,cur->key);
        }    
        
    }
    rewind(cur->cover);
    char c;
    c=fgetc(cur->cover);
    while(!feof(cur->cover))
    { 
        fputc(c,inputf);
        c=fgetc(cur->cover);
    }
    //rewind(cur->cover);
    //rewind(cur->key);
    fclose(inputf);
    fclose(fp2);
    cur->check=1;
}
int compareFile(FILE * fPtr1, FILE * fPtr2)
{
    char ch1, ch2;
    do
    {
        // Input character from both files
        ch1 = fgetc(fPtr1);
        ch2 = fgetc(fPtr2);
        if (ch1 != ch2)
            return -1;

    } while (ch1 != EOF && ch2 != EOF);
 /* If both files have reached end */
    if (ch1 == EOF && ch2 == EOF)
        return 0;
    else
        return -1;
    rewind(fPtr1);
    rewind(fPtr2);
}
void seek(NODE head,char *fname)
{

    int len,flag=-1;
    FILE *out=fopen("out.txt","w+");
    FILE *inputf=fopen(fname,"r");
    NODE cur=head->link;

    while(cur!=NULL )
    {
         rewind(inputf);
        rewind(cur->cover);
        flag=compareFile(inputf,cur->cover);
        if(flag==0)
            break;
        cur=cur->link;
    }
    if(flag==-1)
    {
        printf("Your file has not been encoded.\nPlease provide an encoded file.\n");
        return;
    }
    rewind(inputf);
    rewind(cur->cover);
    rewind(cur->key);
    while(!feof(cur->key))
    { 
       
        char c4,s,e;
        char str[100];
        fscanf(cur->cover,"%s",str);
        s=str[0];
        e=str[strlen(str)-1];
        //printf("\ns=%c  e=%c\n",s,e);
        if(s==e)
            continue;
        
        c4=fgetc(cur->key);
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
    fclose(inputf);
    inputf=fopen(fname,"w");
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
        fputc(bin,inputf);
        if(len==ftell(out)) 
            break;
     }
     fclose(out);
     fclose(inputf);
     cur->check=0;

}


int main()
{
    int ch;
    FILE *cover=NULL,*key=NULL;
    char fname[128],kname[128];
    NODE head=getnode();
    head->link=NULL;
    for(int i=1;i<=10;i++)
    {
        sprintf(fname,"cover_%d.txt",i);// sprintf is used for formatting the filename
        cover=fopen(fname,"r");
        sprintf(kname,"stegokey_%d.txt",i);// sprintf is used for formatting the filename
        key=fopen(kname,"w+");
        if(cover==NULL)
        {
            printf("File not opening\n");
            exit(0);
        }
        insert(head,cover,key);
    }
    //display(head);
    while(1)
    {
        printf("1.Encode a file \n2.Decode a file\n3.Exit\nEnter your choice!\n");
        scanf("%d",&ch);
        switch(ch)
        {
            case 1: printf("Enter text file name( WITHOUT .txt extension ) \n");
                    scanf("%s",fname);
                    strcat(fname,".txt");
                    FILE *inputf=NULL;
                    inputf=fopen(fname,"r+");
                    if(inputf==NULL)
                        printf("Please enter a valid filename\n");
                    else
                    {
                        hide(inputf,head);
                        printf("Your file has been ENCODED.\nPlease check your file now.\n");
                        
                    }
                    break;
            case 2: printf("Enter text file name( WITHOUT .txt extension ) \n");
                    scanf("%s",fname);
                    strcat(fname,".txt");
                    // FILE *inputf2=NULL;
                    //inputf=fopen(fname,"r+");
                   //rewind(inputf);
                   /* if(inputf==NULL)
                        printf("Please enter a valid filename\n");
                    else
                    {*/
                        seek(head,fname);
                        printf("Your file has been DECODED.\nPlease check your file now.\n");
                    //}
                    break;
            case 3: exit(0);
            default: printf("Please enter a valid input.\n");
                    
        }
    }
}