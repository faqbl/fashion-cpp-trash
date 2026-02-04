#include <iostream>
#include <queue>
using namespace std;

int kth=0;
struct Node{
    int val;
    int ID;
    int height;
    int size;
    Node *father;
    Node *left;
    Node *right;
    Node(int v, int id) : val(v), ID(id),height(1),size(1), father(nullptr), left(nullptr), right(nullptr) {}
    Node():val(-1), ID(-1),height(1),size(0), father(nullptr), left(nullptr), right(nullptr) {}
};
struct AVLTree{
    Node *root;
    AVLTree() : root(nullptr) {}
    void remove(Node * locate){
        if(locate==nullptr) return;
        if(locate->left==nullptr && locate->right==nullptr){
            if(locate->father==nullptr){
                root=nullptr;
                delete locate;
                return;
            }
            Node * father=locate->father;
            if(father->left==locate) father->left=nullptr;
            else father->right=nullptr;
            delete locate;
            update(father);
            Node * current=father;
            while(current!=nullptr){
                current=balance(current);
                update(current);
                current=current->father;
            }
        }
        else if(locate->left==nullptr || locate->right==nullptr){
            Node *child=(locate->left!=nullptr)?locate->left:locate->right;
            if(locate->father==nullptr){
                root=child;
                child->father=nullptr;
                delete locate;
                return;
            }
            Node * father=locate->father;
            if(father->left==locate) father->left=child;
            else father->right=child;
            child->father=father;
            delete locate;
            update(father);
            Node * current=father;
            while(current!=nullptr){
                current=balance(current);
                update(current);
                current=current->father;
            }
        }
        else{
            Node * successor=locate->right;
            while(successor->left!=nullptr) successor=successor->left;
            locate->val=successor->val;
            locate->ID=successor->ID;
            Node * succFather=successor->father;
            Node * succChild=(successor->right!=nullptr)?successor->right:nullptr;
            if(succFather->left==successor) succFather->left=succChild;
            else succFather->right=succChild;
            if(succChild!=nullptr) succChild->father=succFather;
            delete successor;
            update(succFather);
            Node * current=succFather;
            while(current!=nullptr){
                current=balance(current);
                update(current);
                current=current->father;
            }
        }
    }
    void showKth(int k){
        Node * locate=searchKth(k);
        if(locate!=nullptr) cout<<locate->val<<"\n";
        else cout<<"Not found ";
    }
    void removeKth(int k){
        Node * locate=searchKth(k);
        kth=locate->val;
        remove(locate);
    }
    Node * search(int val){ 
        return searchRec(root,val);
    }
    Node * searchKth(int k){
        return searchKthRec(root,k);
    }
    Node *searchKthRec(Node * cur,int k){
        if(cur==nullptr) return nullptr;
        int ls=0;
        int rs=0;
        if(cur->left!=nullptr) ls=cur->left->size;
        if(cur->right!=nullptr) rs=cur->right->size;
        if(ls+1==k) return cur;
        else if(k<=ls) return searchKthRec(cur->left,k);
        else return searchKthRec(cur->right,k-ls-1);

    }
    void insert(Node * element){
        root=insertRec(root,element);
        if(root!=nullptr) root->father=nullptr;
    }
    void update(Node * node){
        if(node==nullptr) return;
        int lh=0;
        int rh=0;
        int ls=0;
        int rs=0;
        if(node->left!=nullptr){
            lh=node->left->height;
            ls=node->left->size;
        }
        if(node->right!=nullptr){
            rh=node->right->height;
            rs=node->right->size;
        }
        node->height=max(lh,rh)+1;
        node->size=ls+rs+1;
    }
    int bf(Node * node){
        if(node==nullptr) return 0;
        int lh=0;
        int rh=0;
        if(node->left!=nullptr) lh=node->left->height;
        if(node->right!=nullptr) rh=node->right->height;
        return lh-rh;
    }
    Node * balance(Node * node){
        if(node==nullptr) return nullptr;
        int balanceFactor=bf(node);
        if(balanceFactor>1){
            return rightRotate(node);
        }
        else if(balanceFactor<-1){
            return leftRotate(node);
        }
        return node;
    }
    Node * rightRotate(Node * node){
        int temp=-1;
        Node * b=node->left;
        Node * father=node->father;
        if(father!=nullptr){
            if(father->left==node) temp=0;
            else temp=1;
        }
        
        if(b->left!=nullptr&&b->right!=nullptr && b->left->height>=b->right->height){//segmentation fault here
            Node * A=b->left;
            Node * B=b->right;
            Node * C=node->right;
            b->right=node;
            node->father=b;
            node->left=B;
            if(B!=nullptr) B->father=node;
            b->father=father;
            if(temp==0) father->left=b;
            else if(temp==1) father->right=b;
            update(node);
            update(b);
            if(father!=nullptr) update(father);
            return b;
        }
        else if(b->right==nullptr){
            Node * c=b->left;
            b->right=node;
            node->father=b;
            node->left=nullptr;
            b->father=father;
            if(temp==0) father->left=b;
            else if(temp==1) father->right=b;
            update(node);
            update(b);
            if(father!=nullptr) update(father);
            return b;
        }
        else if(b->left==nullptr){
            Node * c=b->right;
            c->left=b;
            b->father=c;
            c->right=node;
            node->father=c;
            b->right=nullptr;
            node->left=nullptr;
            c->father=father;
            if(temp==0) father->left=c;
            else if(temp==1) father->right=c;
            update(b);
            update(node);
            update(c);
            if(father!=nullptr) update(father);
            return c;
        }
        else{
            Node *c=b->right;
            Node *A=b->left;
            Node *B=c->left;
            Node *C=c->right;
            Node *D=node->right;
            c->left=b;
            b->father=c;
            b->left=A;
            b->right=B;
            if(A!=nullptr) A->father=b;
            if(B!=nullptr) B->father=b;
            c->right=node;
            node->father=c;
            node->left=C;
            if(C!=nullptr) C->father=node;
            c->father=father;
            if(temp==0) father->left=c;
            else if(temp==1) father->right=c;
            update(b);
            update(node);
            update(c);
            if(father!=nullptr) update(father);
            return c;
        }
    }
    Node * leftRotate(Node * node){
        int temp=-1;
        Node * b=node->right;
        Node * father=node->father;
        if(father!=nullptr){
            if(father->left==node) temp=0;
            else temp=1;
        }
        if(b->left!=nullptr&&b->right!=nullptr&&b->left->height<=b->right->height){
            Node * A=b->right;
            Node * B=b->left;
            Node * C=node->left;
            b->left=node;
            node->father=b;
            node->right=B;
            if(B!=nullptr) B->father=node;
            b->father=father;
            if(temp==0) father->left=b;
            else if(temp==1) father->right=b;
            update(node);
            update(b);
            if(father!=nullptr) update(father);
            return b;
        }
        else if(b->left==nullptr){
            Node * c=b->right;
            b->left=node;
            node->father=b;
            node->right=nullptr;
            b->father=father;
            if(temp==0) father->left=b;
            else if(temp==1) father->right=b;
            update(node);
            update(b);
            if(father!=nullptr) update(father);
            return b;
        }
        else if(b->right==nullptr){
            Node * c=b->left;
            c->right=b;
            b->father=c;
            c->left=node;
            node->father=c;
            b->left=nullptr;
            node->right=nullptr;
            c->father=father;
            if(temp==0) father->left=c;
            else if(temp==1) father->right=c;
            update(b);
            update(node);
            update(c);
            if(father!=nullptr) update(father);
            return c;
        }
        else{
            Node *c=b->left;
            Node *A=b->right;
            Node *B=c->right;
            Node *C=c->left;
            Node *D=node->left;
            c->left=node;
            node->father=c;
            c->right=b;
            b->father=c;
            b->left=B;
            if(B!=nullptr) B->father=b;
            node->right=C;
            if(C!=nullptr) C->father=node;
            c->father=father;
            if(temp==0) father->left=c;
            else if(temp==1) father->right=c;
            update(b);
            update(node);
            update(c);
            if(father!=nullptr) update(father);
            return c;
        }
    }
    Node * searchRec(Node * node,int val){
        if(node==nullptr) return nullptr;
        if(node->val==val) return node;
        if(val<node->val) return searchRec(node->left,val);
        else return searchRec(node->right,val);
    }
    Node * insertRec(Node * node,Node *e){
        if(node==nullptr) return e;
        if(e->val<node->val){
            node->left=insertRec(node->left,e);
            if(node->left) node->left->father=node;
        }else{
            node->right=insertRec(node->right,e);
            if(node->right) node->right->father=node;
        }
        update(node);
        return balance(node);
    }
};
int main() {
    ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    int m,k;
    cin >> m >> k;
    AVLTree t;
    queue<int> q;
    int * arr=new int[m];
    int *kths=new int[m-k+1];
    for(int i=0;i<m;i++){
        cin >> arr[i];
    }
    for(int i=0;i<m-k+1;i++){
        cin>>kths[i];
    }
    for(int i=0;i<m;i++){
        q.push(arr[i]);
        Node * newNode=new Node(arr[i],i);
        t.insert(newNode);
        if(i>=k-1){
            t.showKth(kths[i-k+1]);
            t.remove(t.search(q.front()));
            q.pop();
        }

    }



    return 0;
}