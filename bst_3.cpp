
#include<iostream>
using namespace std;
//node class
class node{
    public:
   	 int data;
   	 node* parent;
   	 node *left;
   	 node *right;
   	 node(int value){
   		 parent=NULL;
   		 left=NULL;
   		 right=NULL;
   		 data=value;
   	 }
};
//class binary search tree
class bist{
    public:
   	 node * root;
   	 int counter;//to keep no of nodes
   	 bist(){
   		 root=NULL;
   		 counter=0;
    	}
   	 //insert
    void insert(int value){
   	 inserthelper(root, value);
    }
    void inserthelper(node *curr, int value){
   	 //base null cases for curr or null
   	 if(curr==NULL){
   		 curr = new node(value);
   		 if(root == NULL){
   			 root = curr;
   			 return ;
   		 }
   	 }
   	 //else compare the curr data with value
   	 else if(value < curr->data){
   	 //if  value < curr data
   	 //if left is null insert it
   	 //else move left and call inserthelper
   	 if(curr->left==NULL) {
   	 curr->left = new node(value);
   	 curr->left->parent=curr;}
    	else  inserthelper(curr->left , value);
   	 }
   	 else{
   			 //else move right and call insert helper
   	  if(curr->right ==NULL) {
   	  curr->right= new node(value);
   	  curr->right->parent=curr;}
   	  else inserthelper(curr->right , value);
   	 }
    }
    //display
    void display(){
   	 display2(root);
   	 cout<<endl;
    }
    void display2(node * curr){
   	 if(curr==NULL) return;
   	 //display left
   	 display2(curr->left);
   	 //display curr
   	 cout<<curr->data<<"->";
   	 //display right
   	 display2(curr->right);
    }
    node * search(node * curr , int value){
   	     	// If reached end of tree. or value found
   		 if(curr==NULL|| curr->data==value) return curr;
   		 else if (value < curr->data) return search(curr->left,value);
   		 else return search (curr->right , value);
    }

    node* find_Min(node* curr){
   	 if(curr->left==NULL){return curr;}
   	 else find_Min(curr->left);
    }

    int nof_child(node * Dnode){
   		 if(Dnode->left==NULL and Dnode->right==NULL)return 0;
   		 else if(Dnode->left==NULL and Dnode->right!=NULL)
   		 return 11;
   		 else if(Dnode->left!=NULL and Dnode->right==NULL)
   		 return 10;
   		 else return 2;

    }
    void replace(node* DeadChild,node* NewChild){
   	 //curr's parent will be temp's parent n curr will go to hell
   		 //node* curr=root;
   		 //while(DeadChild->data!=curr->data){
   		 //if (DeadChild->data< curr->data)curr=curr->left;
   		 //else curr=curr->right;}
   		 //if deadchild is left child
   		 if(DeadChild->parent->left==DeadChild){//if left child
   			 NewChild->parent=DeadChild->parent;
   			 DeadChild->parent->left=NewChild;
   			 delete DeadChild;
   		 }
   		 else{//if right cild
   			 NewChild->parent=DeadChild->parent;
   			 DeadChild->parent->right=NewChild;
   			 delete DeadChild;
   		 }
    }
    void DeleteNode(int value){
   	 node* Dnode=search(root,value);
   	 //1 no child
   	 if(nof_child(Dnode)==0){
   		 if(Dnode->parent->left==Dnode){
   			 Dnode->parent->left=NULL;
   			 delete Dnode;
   		 }
   		 else{
   			 Dnode->parent->right=NULL;
   			 delete Dnode;
   		 }
   	 }

   	 //2. one child
   	 if(nof_child(Dnode)==11){replace(Dnode,Dnode->right);}
   	 if(nof_child(Dnode)==10){replace(Dnode,Dnode->left);}

   	 //3.both child present
   	 if(nof_child(Dnode)==2)
   	 {     //change value with the first succser ie right minimum
   		  Dnode->data=find_Min(Dnode->right)->data;
   		  //then replace right minimum eith its child or delete it
   		  node* temp=find_Min(Dnode->right);
   		  if(nof_child(temp)==0)//nochild delete it
   		      {    if(temp->parent==Dnode){
   		     		 Dnode->right=NULL;
   			      }
   			      else temp->parent->left=NULL;
   		     	 delete temp;
   			  }
   		   else replace(temp,temp->right);//replace with its child
   		  }

    }
    void count_node(node * start,int *fcounter){//does not use counter from class
    	if(start==NULL) return;
   	 //go left left
   	 count_node(start->left,fcounter);
   	 //update counter
   	 *fcounter=*fcounter+1;
   	 //go right
   	 count_node(start->right,fcounter);


    }

    void count_node(node * start){//uses counter from class
    //before using this function when not using for first time
    //take counter to zero
    	if(start==NULL) return;
   	 //go left left
   	 count_node(start->left);
   	 //update counter
   	 counter=counter+1;
   	 //go right
   	 count_node(start->right);

    }

    /*(8) int rangeSearch(int k1, int k2) ->range search: given two values k1 and k2,
     print all the elements (or keys) x in the BST such that k1 <= x <= k2.
     Also count the number of elements in the range from k1 to k2 and returns it.*/

     int rangeSearch(int k1,int k2){
    	bist b2;
    	rangeSearch_helper(k1,k2,&b2,root);
    	b2.display();
    	b2.count_node(b2.root);
    	return b2.counter;
     }

     void rangeSearch_helper(int k1,int k2,bist *br1,node * curr){
        	if(curr==NULL) return;
   	 //go left left
   	 rangeSearch_helper(k1,k2,br1,curr->left);
   	 //update counter
   	 if(curr->data<=k2 and curr->data>=k1)
   	 br1->insert(curr->data);
   	 //go right
   	 rangeSearch_helper(k1,k2,br1,curr->right);

     }

};
int main(){
    bist b1;
    b1.insert(5);
    b1.insert(2);
    b1.insert(1);
    b1.display();
    b1.insert(4);
    b1.insert(6);
	b1.insert(9);
    b1.insert(7);
    b1.insert(8);
    b1.display();
	int Ncounter=0;
    b1.count_node(b1.root,&Ncounter);


    cout<<Ncounter<<endl;
	Ncounter=0;

    b1.DeleteNode(8);
    b1.display();

	b1.count_node(b1.root,&Ncounter);

	cout<<Ncounter<<endl;

	b1.count_node(b1.root);
	cout<<b1.counter<<endl;

	b1.insert(28);
	b1.display();

	b1.counter=0;

	b1.count_node(b1.root);
	cout<<b1.counter<<endl;

	cout<<b1.rangeSearch(5,28);



    return 0;
}


