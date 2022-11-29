#include <iostream>
#include <stdlib.h>

using namespace std;

class node{
    public:
    int status,index;
    node *next,*prev;

    node(){
        status = 0;
    }
};

int check(const node *h,const int p[], int i){
    int fleg = 1;
    while(h!=NULL){
        int k=i;
        while(k--){
            if(h->index == k){fleg = 0;break;}
        }
        if(fleg==0)
            break;
        h = h->next;
    }
    
    if(fleg==0){return 1;}
    else{return 0;}
}

int main()
{
    node *hn[15];

    for(int i=0;i<15;i++){hn[i]=NULL;}
    
    while(1){
        char a = 'A';
        cout<<"\t";
        for(int i=1;i<=10;i++){cout<<i<<"  ";}
        cout<<endl;
        for(int i=0;i<15;i++){
            cout<<a;
            cout<<"\t";
            if(hn[i]==NULL){
                for(int j=0;j<10;j++){cout<<"O  ";}
                cout<<endl;
            }
            
            else{
                node *temp = hn[i];
                for(int j=1;j<=10;j++){
                    if(temp == NULL){cout<<"O  ";}
                    else if(temp->index == j){cout<<"X  "; temp=temp->next;}
                    else{cout<<"O  ";}
                }
                cout<<endl;
            }
            a++;
        }
        
        cout<<"-----------------All eyes here-----------------";
        int ch;
        cout<<"\n\nEnter your choice:\n";
        cout<<"1.Book a ticket\n2.Book multiple tickets\n3.Cancel booking\n4.EXIT\n";
        cin>>ch;
        switch(ch){
            case 1:{
                char r; int c;
                cout<<"Enter the seat number you want(eg E 2)";
                cin>>r>>c;
                
                if(hn[r-'A'] == NULL){
                    node *temp = new node();
                    temp->index = c;
                    temp->status = 1;
                    temp -> next = NULL;
                    temp ->prev = NULL;
                    hn[r-'A'] = temp;
                }
                
                else{
                    node *temp = hn[r-'A'], *temp1 = new node();
                    int flag=0;
                    while(temp->next!=NULL){
                        if(temp->index == c){flag=2; break;}
                        else if(temp->index > c){flag=1; break;}
                        
                        temp = temp->next;
                    }
                    
                    temp1->index = c;
                    if(flag == 2){
                        cout<<"The seat is already booked, Try another..\n";
                    }
                    
                    else if(flag==1){
                        temp1->status = 1;
                        temp1->prev = temp->prev;
                        temp->prev = temp1;
                        temp1->next = temp;
                        temp1->prev->next = temp1;
                    }
                    
                    else{
                        temp1->status = 1;
                        temp1->next = NULL;
                        temp1->prev = temp;
                        temp->next = temp1;
                    }
                }
                
                break;
            }
            
            case 2:{
                int n;
                cout<<"Enter the number of seats you want(Max 8)-";
                cin>>n;
                char r; int c[n];
                cout<<"Enter the first and last seat number(eg A 3 7)";
                cin>>r>>c[0]>>c[n-1];
                for(int k=1;k<n-1;k++){c[k] = c[0]+k;}

                if(hn[r-'A']==NULL){
                    node *temp = new node();
                    temp->index = c[0];
                    temp->status = 1;
                    temp->next = NULL;
                    temp->prev = NULL;
                    hn[r-'A'] = temp;

                    for(int k=1;k<n;k++){
                        node *temp1 = new node();
                        temp1->index = c[k];
                        temp1->status = 1;
                        temp1->next = NULL;
                        temp1->prev = temp;
                        temp->next = temp1;
                        temp = temp1;
                    }
                }

                else{
                    if(check(hn[r-'A'],c,n)==1){
                        node *temp = hn[r-'A'];
                        int flag=0;
                        while(temp->next!=NULL){
                        if(temp->index > c[0]){flag=1; break;}
                        
                        temp = temp->next;
                        }
                        
                        if(flag==1){
                            int k=0;
                            while(k!=n){
                                node *temp1 = new node();
                                temp1->index = c[k];
                                temp1->status = 1;
                                temp1->prev = temp->prev;
                                temp->prev = temp1;
                                temp1->next = temp;
                                temp1->prev->next = temp1;
                                k++;
                            }
                        }

                        else{
                            int k=0;
                            while(k!=n){
                                node *temp1 = new node();
                                temp1->index = c[k];
                                temp1->status = 1;
                                temp1->prev = temp;
                                temp->next = temp1;
                                temp1->next = NULL;
                                k++;
                            }
                        }
                    }

                    else{
                        cout<<"Some of the seats are already booked, Try another!\n";
                    }
                }

                break;
            }

            case 3:{
                char r; int c;
                cout<<"Enter your seat number(eg A 7)-";
                cin>>r>>c;
                
                if(hn[r-'A']==NULL)
                    cout<<"No such seat was booked!\n";
                
                else{
                    node *d = hn[r-'A'];
                    int flag=0;
                    while(d!=NULL){
                        if(d->index == c){flag=1; break;}
                        d = d->next;
                    }

                    if(flag==0){cout<<"No such seat was booked!\n";}

                    else{
                        if(d->prev == NULL && d->next==NULL){
                            hn[r-'A'] = NULL;
                            delete d;
                        }

                        else if(d->prev == NULL){
                            hn[r-'A'] = NULL;
                            d->next->prev = NULL;

                            delete d;
                        }

                        else if(d->next == NULL){
                            d->prev->next = NULL;

                            delete d;
                        }

                        else{
                            d->prev->next = d->next;
                            d->next->prev = d->prev;

                            delete d;
                        }
                        cout<<"Booking successfully cancelled\n";
                    }
                }

                break;
            }

            case 4:{
                cout<<"Thank you for using our service"; 
                exit(1); 
                break;}

            default: cout<<"Enter valid choice";
        }
    }

    return 0;
}