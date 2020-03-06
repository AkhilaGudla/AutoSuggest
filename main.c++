#include <bits/stdc++.h>
#define ALPHA_SIZE 26
using namespace std;
struct Node{
  bool isEOW;
  Node * next[ALPHA_SIZE];           //next is array whose elements are pointers, each node has 26 children

};
Node* createNode()
{
    Node* nn=(Node*)malloc(sizeof(Node));
    nn->isEOW=false;
    for(int i=0;i<ALPHA_SIZE;i++)
    {
        nn->next[i]=NULL;              //make all children as NULL default
    }
     return nn;

}
bool iswordexist(Node* root,char str[])
{
  Node* temp=root;
  for(int i=0;str[i];i++)
  {
      int idx=str[i]-'a';
      if(temp->next[idx]==NULL)
        return false;
      temp=temp->next[idx];

  }
  return temp->isEOW;
}
char path[100];
void printwords(Node* root,int pi)
{
    if(root->isEOW)
        printf("  %s\n",path);
    for(int i=0;i<ALPHA_SIZE;i++)
    {
        if(root->next[i]!=NULL)
        {
            path[pi]=i+'a';
            path[pi+1]='\0';
            printwords(root->next[i],pi+1);

        }
    }
}
void autosugest(Node* root,char pre[])
{
    Node* temp=root;
    for(int i=0;pre[i];i++)
    {
        int idx=pre[i]-'a';
        if(temp->next[idx]==NULL)
         {

          cout<<"NO WORD EXIST"<<"\n";
           return ;
         }
         temp=temp->next[idx];
    }
    strcpy(path,pre);
    printwords(temp,strlen(pre));
}
void fill(Node* root)
{
    FILE* fp=fopen("D:\dict.txt","r");
    char str[100];
    if(fp)
    {


    while(!feof(fp))
    {
        fscanf(fp,"%s",str);
        insertWord(root,str);
    }
    fclose();
    }
    else
        cout<<"file not found"<<"\n";
}

void insertWord(Node* root,char str[])
{
    Node* temp=root;
    int idx;
    for(int i=0;str[i];i++)
    {
        idx=str[i]-'a';
        if(temp->next[idx]==NULL)
        {
        temp->next[idx]=createNode();
        }
        temp=temp->next[idx];
    }
     temp->isEOW=true;
}
int showMenu()
{
    int ch;
    cout<<"Menu"<<"\n";
    cout<<"==="<<"\n";
    cout<<"1.Insert word"<<"\n";
    cout<<"2.Auto Suggest Words"<<"\n";
    cout<<"3.Print all words"<<"\n";

    cout<<"4.iswordexist"<<"\n";
     cout<<"5.Exit"<<"\n";
    cout<<"\n";
    cout<<"Enter your choice:"<<" ";
    cin>>ch;
    return ch;

}
int main()
{
    Node* root=createNode();
    fill(root);
    char str[100];
    while(1)
    {
        int n=showMenu();
        switch(n)
        {
          case 1:
              printf("Enter a word: ");
              scanf("%s",str);
              insertWord(root,str);
              break;
          case 2:
              printf("Enter prefix: ");
              scanf("%s",str);
              autosugest(root,str);
              break;
          case 3:
              printwords(root,0);
              break;
          case 4:
              printf("Enter word to search: ");
              scanf("%s",str);
              if(iswordexist(root,str))
                cout<<"====FOUND==="<<"\n";
              else
                cout<<"====NOT FOUND!=="<<"\n";

             break;
          case 5:
              return 0;
          default:
              cout<<"Wrong choice!! Try again."<<"\n";
        }
    }
    return 0;
}
