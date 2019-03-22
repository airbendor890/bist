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
		bst(){
			root=NULL;
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
		if(curr->left==NULL){cout<<curr->data;return curr;}
		else find_Min(curr->left);
	}
	void replace_at_parent(node* DeadChild,node* NewChild){
		//curr's parent will be temp's parent n curr will go to hell
			//node* curr=root;
			//while(DeadChild->data!=curr->data){
			//if (DeadChild->data< curr->data)curr=curr->left;
			//else curr=curr->right;}
			//if deadchild is left child
			if(DeadChild->parent->left==DeadChild){
				NewChild->parent=DeadChild->parent;
				DeadChild->parent->left=NewChild;
				delete DeadChild;
			}
			else{
				NewChild->parent=DeadChild->parent;
				DeadChild->parent->right=NewChild;
				delete DeadChild;
			}			
	}
	void DeleteNode(int value){
		node* Dnode=search(root,value);
		//1 no child
		if(Dnode->left==NULL and Dnode->right==NULL){
			cout<<"hara";if(Dnode->parent->left==Dnode){
				Dnode->parent->left=NULL;
				delete Dnode;
			}
			else{
				Dnode->parent->right=NULL;
				delete Dnode;
			}
		}
		//2. one child
		if(Dnode->left==NULL and Dnode->right!=NULL){//left child absent
			if(Dnode->parent->left==Dnode){
				Dnode->parent->left=Dnode->right;
				delete Dnode;
			}
			else{
				Dnode->parent->right=Dnode->right;
				delete Dnode;
			}
			
		}
		if(Dnode->left!=NULL and Dnode->right==NULL){//right child absent
			if(Dnode->parent->left==Dnode){
				Dnode->parent->left=Dnode->left;
				delete Dnode;
			}
			else{
				Dnode->parent->right=Dnode->left;
				delete Dnode;
			}
			
		}
		//3.both child present
		if(Dnode->left!=NULL and Dnode->right!=NULL){
			if(Dnode->parent->left==Dnode){
				Dnode->parent->left=Dnode->left;
				Dnode->left->right=Dnode->right;
				delete Dnode;
			}
			else{
				Dnode->parent->right=Dnode->left;
				Dnode->left->right=Dnode->right;
				delete Dnode;
			}
		}
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
	cout<<"enter the node you want to search"<<endl;
	int a;
	cin>>a;
	if (b1.search (b1.root,a)!=NULL) cout<<"Number is found.";
	else cout<<"Number is not found.";
	b1.find_Min(b1.root->right->right);
	b1.DeleteNode(2);
	
	b1.display();
	b1.DeleteNode(4);
	b1.display();
	return 0;
}
