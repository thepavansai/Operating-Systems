#include<stdio.h>
#include<limits.h>
int n;
struct RAM{
  int pno;
}frame[10];
void init(){
  for(int x=0;x<n;x++){
    frame[x].pno=-1;
  }
}
void display(){
  printf("Frames in (RAM):\n");
  for(int x=0;x<n;x++){
    printf("%d \n",frame[x].pno);
  }
}
int inframe(int p){
  for(int y=0;y<n;y++){
    if(frame[y].pno==p){
      return y;
    }
  }
  return -1;
} 

int main(){
  int pf=0,np;
  int q=0;
  printf("Enter the number of Frames : ");
  scanf("%d",&n);
  printf("Enter the no of Page Requests : ");
  scanf("%d", &np);
  int pr[np];
  printf("Enter the Page Requests in Order : \n");
  for(int i=0;i<np;i++){
    scanf("%d",&pr[i]);
  }
  init();
  display();
  int pre[n];
  for(int x=0;x<np;x++){
    if(pr[x]==-1){
      break;
    }
    if(inframe(pr[x])!=-1){
      printf("\nPage Exsits \n");
    }
    else{
      pf++;
      printf("\n Page Fault %d \n",pf);
      if(q<n){
        frame[q].pno=pr[x];
        q++;
      }
      else{
        int prev[n];
        for(int i=0;i<n;i++){
          prev[i]=INT_MAX;
        }
        for(int y=0;y<n;y++){
          for(int z=x+1;z<np;z++){
            if(pr[z]==frame[y].pno){
              prev[y]=z;
              break;
            }
          }
        }
        int min=prev[0];
        int prp=0;
        for(int y=0;y<n;y++){
          if(prev[y]>min){
            min=prev[y];
            prp=y;
          }
        }
        frame[prp].pno=pr[x];
      }
    }
    display();
  }
  return 0;
}
