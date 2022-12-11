#include <stdio.h>
void fcpy(char* source, char *destination)
{ 
  FILE* fp,*tmp;
    tmp=fopen(source,"r+");
    fp= fopen(destination,"w+");
    rewind(fp);
    rewind(tmp);
    int c;
    while ((c=getc(tmp))!=EOF)
    {
        putc(c,fp);
    }
    fclose(fp);
    fclose(tmp);
}
void replacel(char *filename, char *val, int l)
{ FILE* fp,*tmp;
    fp = fopen(filename,"r+");
    tmp = fopen("./DB/tmp.txt","w+");
    int line=0,c;
    while ((c=getc(fp))!=EOF)
    { 
        if(c=='\n')
        { 
           
            if(line==l)
            {
               if(l!=0||line!=0)putc('\n',tmp);
                fprintf(tmp,"%s\n",val);
            }
            line++;
        }
        else if((l!=line)) putc(c,tmp);
    }

    fclose(tmp);
    fclose(fp);
    fcpy("./DB/tmp.txt",filename);
    
    
}