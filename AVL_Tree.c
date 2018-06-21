#include<stdio.h>
#include<stdlib.h>
 
typedef struct node
{
    int data;
    struct node *left,*right;
    int ht; // height ==> tinggi sebuah node dari leavenya
}node;
 
node *insert(node *,int);
node *Delete(node *,int);
void preorder(node *);
void inorder(node *);
int height( node *);
node *rotateright(node *);
node *rotateleft(node *);
node *RR(node *);
node *LL(node *);
node *LR(node *);
node *RL(node *);
int BF(node *);
 
int main()
{
    node *root=NULL;
    int x,n,i,op;
    
    do
    {
        printf("\n1)Create:");
        printf("\n2)Insert:");
        printf("\n3)Delete:");
        printf("\n4)Print:");
        printf("\n5)Quit:");
        printf("\n\nEnter Your Choice:");
        scanf("%d",&op); // op == option
        
        switch(op)
        {
            case 1: printf("\nEnter no. of elements:");
                    scanf("%d",&n); // n == number
                    printf("\nEnter tree data:");
                    root=NULL;
                    for(i=0;i<n;i++)
                    {
                        scanf("%d",&x);
                        root=insert(root,x);
                    }
                    break;
                
            case 2: printf("\nEnter a data:");
                    scanf("%d",&x);
                    root=insert(root,x);
                    break;
                    
            case 3: printf("\nEnter a data:");
                    scanf("%d",&x);
                    root=Delete(root,x);
                    break;
            
            case 4: printf("\nPreorder sequence:\n");
                    preorder(root);
                    printf("\n\nInorder sequence:\n");
                    inorder(root);
                    printf("\n");
                    break;            
        }
    }while(op!=5);
    
    return 0;
}
 
/* Modul : Insert
 * Modul ini mencoba mencari posisi yang null dari sebuah Tree, untuk diinputkan data baru.
 * Jika sudah mencapai null, maka modul ini akan mengalokasi memori untuk node baru berisi data inputan.
 * Setelah menemukan posisi null tersebut, selanjutnya akan di-rebalancing melalui proses pada modul : BF,RR,RL,LL,LR
 =====================================================================================================================
 * Aturan dasar yang juga perlu diingat :
 *       Parent (2)
 *         /   \
 *   Left(1)   Right (3)
 * Urutan terkecil ke terbesar : left(1) - parent(2) - right(3)
 =====================================================================================================================
 */ 
node * insert(node *T,int x)
{
    if(T==NULL) // jika ditemukan null
    {
        T=(node*)malloc(sizeof(node));
        T->data=x;
        T->left=NULL;
        T->right=NULL;
    }
    else
        if(x > T->data)        // insert in right subtree
        {
            T->right=insert(T->right,x); // beralih ke right childnya, menggunakan recursive mode
            if(BF(T)==-2) // balancing factor; maksimal selisih subtree/child kanan - kiri = 2
                if(x>T->right->data) // penentuan posisi x dari T, apakah right - right atau right - left
                    T=RR(T); 
					/* balancing module -> ketika posisi x dari T berada pada posisi T->right->right */
                else
                    T=RL(T);
                    /* balancing module -> ketika posisi x dari T berada pada posisi T->right->left */
        }
        else
            if(x < T->data)    // insert in left subtree
            {
                T->left=insert(T->left,x); // beralih ke left childnya
                if(BF(T)==2)
                    if(x < T->left->data) // penentuan posisi x dari T, apakah left - left atau left - right
                        T=LL(T); // balancing module T->left->left
                    else
                        T=LR(T); // balancing module T->left->right
            }
        
        T->ht=height(T); // mengukur tinggi dari leave terbawah
        
        return(T);
}
 
node * Delete(node *T,int x) // diperbaiki dengan menambahkan 'free'
{
    node *p; // temporary variable
    
    if(T==NULL)
    {
        return NULL;
    }
    else
        if(x > T->data)        // insert in right subtree
        {
            T->right=Delete(T->right,x);
            if(BF(T)==2)
                if(BF(T->left)>=0)
                    T=LL(T);
                else
                    T=LR(T);
        }
        else
            if(x<T->data)
            {
                T->left=Delete(T->left,x);
                if(BF(T)==-2)    // Rebalance during windup, sambil proses balancing
                    if(BF(T->right)<=0)
                        T=RR(T);
                    else
                        T=RL(T);
            }
            else
            {
                // Data to be deleted is found, data yang dicari ditemukan
                if(T->right!=NULL)
                {    // Delete its inorder succesor, urutan setelah si data dalam traversal in order
                    p=T->right;
                    
                    while(p->left!= NULL)
                        p=p->left;
                    
                    T->data=p->data;  
                    T->right=Delete(T->right,p->data);
                    
                    if(BF(T)==2)// Rebalance during windup
                        if(BF(T->left)>=0)
                            T=LL(T);
                        else
                            T=LR(T);
                }
                else {
                	node* temp = T->left;
                	free(T);
                    return(temp);	
				}
            }
    T->ht=height(T);
    return(T);
}

/* Modul : Height 
 * Mengukur ketinggian suatu node dari leaves
 */
int height(node *T)
{
    int lh,rh;
    if(T==NULL)
        return(0);
    
    if(T->left==NULL)
        lh=0;
    else
        lh=1+T->left->ht;
        
    if(T->right==NULL)
        rh=0;
    else
        rh=1+T->right->ht;
    
    if(lh>rh)
        return(lh);
    
    return(rh);
}

/* Modul : Rotate Right
 * Diputernya node sebelah kanan, yang kirinya jadi sumbu
 */
node * rotateright(node *x)
{
    node *y;
    y=x->left;
    x->left=y->right;
    y->right=x;
    x->ht=height(x);
    y->ht=height(y);
    
    return(y);
}

/* Modul : Rotate Left
 * Diputernya node sebelah kiri, yang kanannya jadi sumbu
 */
node * rotateleft(node *x)
{
    node *y;
    y=x->right;
    x->right=y->left;
    y->left=x;
    x->ht=height(x);
    y->ht=height(y);
    
    return(y);
}
 
node * RR(node *T) // right - right
{
    T=rotateleft(T);
    return(T);
}
 
node * LL(node *T) // left - left
{
    T=rotateright(T);
    return(T);
}
 
node * LR(node *T) // left - right
{
    T->left=rotateleft(T->left);
    T=rotateright(T);
    
    return(T);
}
 
node * RL(node *T) // right - left
{
    T->right=rotateright(T->right);
    T=rotateleft(T);
    return(T);
}

/* Modul : BF(Balancing Factor)
 * Mengukur selisih node antara subtree kanan - kiri; maksimal selisih antara kanan - kiri = 2
 */
int BF(node *T)
{
    int lh,rh;
    if(T==NULL)
        return(0);
 
    if(T->left==NULL)
        lh=0;
    else
        lh=1+T->left->ht;
 
    if(T->right==NULL)
        rh=0;
    else
        rh=1+T->right->ht;
 
    return(lh-rh);
}

void preorder(node *T) // modul traversal
{
    if(T!=NULL)
    {
        printf("%d(Bf=%d)",T->data,BF(T));
        preorder(T->left);
        preorder(T->right);
    }
}
 
void inorder(node *T) // modul traversal
{
    if(T!=NULL)
    {
        inorder(T->left);
        printf("%d(Bf=%d)",T->data,BF(T));
        inorder(T->right);
    }
}
