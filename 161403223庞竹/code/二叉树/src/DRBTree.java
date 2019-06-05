import java.util.Scanner;

public class DRBTree<T extends Comparable<T>> {
 
 private RBNode<T> mroot;
 private static final boolean RED = false;
 private static final boolean BLACK = true;
 
 public class RBNode<T extends Comparable<T>>{
  
  private boolean color;
  private T key;
  private RBNode<T> parent;
  private RBNode leftChild;
  private RBNode rightChild;
  
  public RBNode(boolean col,T key,RBNode paret,RBNode leftChild,RBNode rightChild){
   this.color = col;
   this.key = key;
   this.parent = parent;
   this.leftChild = leftChild;
   this.rightChild = rightChild;
  }
  
  public T getKey() {
   return this.key;
  }
 }
 
 public RBNode<T> parentOf(RBNode<T> node){
  if(node!=null) {
   return node.parent;
  }
  
  return null;
 }
 
 public boolean colorOf(RBNode<T> node){
  if(node!=null) {
   return node.color;
  }
  return BLACK;
 }
 
 public void setParent(RBNode<T> node,RBNode<T> parent) {
  if(node!=null) {
   node.parent = parent;
  }
 }
 
 public void setColor(RBNode<T> node,boolean color) {
  if(node!=null) {
   node.color = color;
  }
 }
 
 public boolean isRed(RBNode<T> node) {
  return (node!=null&&node.color == RED)?true:false;
 }
 
 public boolean isBlack(RBNode<T> node) {
  return !isRed(node);
 }
 
 public void setRed(RBNode<T> node) {
   if(node!=null) { 
  node.color = RED;
   } 
 }
 
 public void setBlack(RBNode<T> node) {
  if(node!=null) {
   
   node.color = BLACK;
  }
 }
 
 //寻找为key值的节点
 public RBNode<T> search(T key,RBNode<T> node){
  
   if(node!=null) { 
  int com = key.compareTo(node.key);
  if(com<0) {
   return search(key,node.leftChild);
  }else if(com>0) {
   return search(key,node.rightChild);
  }else {
   return node;
  }
   }
   return null;
  
 }
 
 //寻找后继节点，即大于该节点的最小节点
 public RBNode<T> min(RBNode<T> node){
   if(node.leftChild == null) {
    return node;
   }
  
   while(node.leftChild!=null) {
    node = node.leftChild;
   }
  
   return node;
 }
 
 public RBNode successor(RBNode<T> node) {
  if(node.rightChild !=null) {
     return min(node.rightChild);
  }
  
  RBNode<T> y = node.parent;
  while((y!=null)&&(y.rightChild == node)) {
   node = y;
   y = y.parent;
  }
  return y;
 }

 //对某个节点进行左旋
 public void leftRonate(RBNode<T> x) {
  RBNode<T> y = x.rightChild;
  
  if(y.leftChild!=null) {
   y.leftChild.parent = x;
  }
  
  x.rightChild = y.leftChild;
     y.leftChild = x;
     y.parent = x.parent;
    
    
    
     if(x.parent!=null) {
      if(x.parent.leftChild == x) {
       x.parent.leftChild = y;
      }else {
       x.parent.rightChild = y;
      }
     }else {
      this.mroot = y;
     }
     x.parent = y;
    
 }
 
 //对某个节点进行右旋
 public void rightRonate(RBNode<T> x) {
  RBNode<T> y = x.leftChild;
  
  if(y.rightChild!=null) {
   y.rightChild.parent = x;
  }
  
  y.parent = x.parent;
  x.leftChild = y.rightChild;
  y.rightChild = x;
  
  if(x.parent!=null) {
   if(x.parent.leftChild == x) {
    x.parent.leftChild = y;
   }else {
    x.parent.rightChild = y;
   }
  }else {
   this.mroot = y;
  }
  x.parent = y;
 }
 
 
 
 //红黑树添加修复
 public void insertFixUp(RBNode<T> node) {
  RBNode<T> parent,gparent;
  while(((parent = parentOf(node))!=null)&&isRed(parent)) {
   gparent = parentOf(parent);
   if(gparent.leftChild == parent) {
    RBNode<T> uncle = gparent.rightChild;
    if(isRed(uncle)){
     setBlack(parent);
     setBlack(uncle);
     setRed(gparent);
     
     node = gparent;
     continue;
    }else {
     if(parent.rightChild == node) {
       leftRonate(parent);
       RBNode<T> temp = node;
       node = parent;
       parent = temp;
     }
     
     setBlack(parent);
     setRed(gparent);
     rightRonate(gparent);
     
    }
   }else {
    
    RBNode<T> uncle = gparent.leftChild;
    if(isRed(uncle)) {
     setBlack(parent);
     setBlack(uncle);
     setRed(gparent);
     
     node = gparent;
     continue;
    }else {
     if(parent.leftChild == node) {
      rightRonate(parent);
      RBNode<T> temp = node;
      node = parent;
      parent = temp;
     }
     setBlack(parent);
     setRed(gparent);
     leftRonate(gparent);
    }
   }
  }
  
  if(mroot == node) {
   setBlack(node);
  }
 }
 //红黑树删除修复
 public void deleteFixUp(RBNode<T> node,RBNode<T> parent) {
     
  RBNode<T> other;
  while(isBlack(node)&&node!=this.mroot) {
      
       if(parent.leftChild == node) {
        other = parent.rightChild;
        if(isRed(other)) {
         setRed(parent);
         setBlack(other);
         leftRonate(parent);
         continue;
        }else {
         if(isBlack(other.leftChild)&&isBlack(other.rightChild)) {
          setRed(other);
          node = parent;
          parent = parentOf(node);
         
        
         }else if(isRed(other.leftChild)&&isBlack(other.rightChild)) {
          setRed(other);
          setBlack(other.leftChild);
          rightRonate(other);
         }else if(isRed(other.rightChild)) {
          setColor(other,colorOf(parent));
          setBlack(parent);
          setBlack(other.rightChild);
          leftRonate(parent);
          break;
         }
        }
       }else {
        other = parent.leftChild;
        if(isRed(other)) {
         setBlack(other);
         setRed(parent);
         rightRonate(parent);
         continue;
        }else {
         if(isBlack(other.leftChild)&&isBlack(other.rightChild)) {
          setRed(other);
          node = parent;
          parent = parentOf(node);
         
        
         }else if(isRed(other.rightChild)&&isBlack(other.leftChild)) {
          setRed(parent);
          setBlack(other.rightChild);
          leftRonate(other);
         }else if(isRed(other.leftChild)) {
          setColor(other, colorOf(parent));
          setBlack(parent);
          setBlack(other.leftChild);
          rightRonate(parent);
          break;
         }
        }
        }
  }
  
  setBlack(node);
 
 }
 
 
 //红黑树添加操作
 public void insert(RBNode<T> node) {
 
      int com;
      RBNode<T> x = this.mroot;
      RBNode<T> y = null;
      while(x!=null) {
       y = x;
       com = node.key.compareTo(x.key);
      
       if(com<0) {
       x=x.leftChild;
       }else{
       x=x.rightChild;
       }
      
      }
     
      node.parent = y;
     
      if(y!=null) {
       com = node.key.compareTo(y.key);
       if(com<0) {
        y.leftChild = node;
       }else {
        y.rightChild = node;
       }
      }else {
       this.mroot = node;
      }
      setRed(node);
      insertFixUp(node);
 }
 
     public void insert(T key) {
  
  RBNode<T> node = new RBNode<T>(BLACK,key,null,null,null);
  
  if(node!=null) {
   insert(node);
  }
  }
 
 //红黑树删除操作
 public void delete(RBNode<T> node) {
  
  RBNode<T> child,parent,replace;
  boolean color = true;
  if(node.leftChild!=null&&node.rightChild!=null) {
   replace = successor(node);
   
   parent = parentOf(replace);
   child = replace.rightChild;
   color = colorOf(replace);
   
   if(node == parentOf(replace)) {
     parent = replace;
   }else {
    if(child!=null) {
       setParent(child,parentOf(replace));
    }
    replace.parent.leftChild = child;
    replace.rightChild = node.rightChild;
    setParent(node.rightChild,replace);
   }
   
   setParent(replace, parentOf(node));
   replace.leftChild = node.leftChild;
   setParent(node.leftChild,replace);
   setColor(replace,colorOf(node));
   
   if(parentOf(node)!=null) {
    if(node.parent.leftChild==node) {
     node.parent.leftChild = replace;
    }else {
     node.parent.rightChild = replace;
    }
   }else {
    this.mroot = replace;
   } 
   
   if(color==BLACK){
       deleteFixUp(child, parent);
   }
  }else {
  
   if(node.leftChild!=null) {
    replace = node.leftChild;
   }else {
    replace = node.rightChild;
   }
   
     parent = parentOf(node);
     
     if(parent!=null) {
      if(parent.leftChild==node) {
       parent.leftChild = replace;
      }else {
       parent.rightChild = replace;
      }
     }else {
      this.mroot = replace;
     }
     setParent(replace, parent);
   
      color = colorOf(node);
      child = replace;
   if(color==BLACK) {
    deleteFixUp(child, parent);
   }
  } 
    
 }
 
 public void delete(T key) {
  RBNode<T> node;
  if((node=search(key,this.mroot))!=null) {
   delete(node);
  }
 }
 
 //前序遍历
 public void preOrder(RBNode<T> node) {
   if(node!=null) {  
  System.out.print(node.key+" ");
  preOrder(node.leftChild);
  preOrder(node.rightChild);
   } 
 }
 
 public void preOrder() {
  preOrder(this.mroot);
 }
 
 //中序遍历
 public void inOrder(RBNode<T> node) {
  if(node!=null) {
   inOrder(node.leftChild);
   System.out.print(node.key+" ");
   inOrder(node.rightChild);
  }
 }
 public void inOrder() {
  inOrder(this.mroot);
 }
 
 //后序遍历
 public void postOrder(RBNode<T> node) {
  if(node!=null) {
   postOrder(node.leftChild);
   postOrder(node.rightChild);
   System.out.print(node.key+" ");
  }
 }
 
 public void postOrder() {
  postOrder(this.mroot);
 }
 
 //打印红黑树
 public void print(RBNode<T> node,int direction) {
   if(node!=null) { 
  if(direction == 0) {
   System.out.printf("%2d(%s) is root\n",node.key,node.color==false?"R":"B");
  }else {
   System.out.printf("%2d(%s) is %s child 父节点  %2d\n",node.key,node.color==false?"R":"B",direction==-1?"left":"right",node.parent.key);
  }
  print(node.leftChild,-1);
  print(node.rightChild,1);
   } 
 }
 
 public void print() {
  print(this.mroot,0);
 }
 public static void main(String[] args) {
  
  DRBTree<Integer> tree = new DRBTree<Integer>();
  
  int[] a = {10,20,30,40,50,60,70,80,90};
  
  //红黑树添加测试
  for(int i=0;i<a.length;i++) {
   tree.insert(a[i]);
  }
  
  System.out.print("前序遍历: ");
  tree.preOrder();
  
  System.out.print("\n中序遍历: ");
  tree.inOrder();
  
  System.out.print("\n后序遍历: ");
  tree.postOrder();
  
  System.out.println();
  tree.print();
  
  System.out.print("\n输入要删除的节点:");
  Scanner scan = new Scanner(System.in);
  
  int key = scan.nextInt();
  
  //红黑树删除测试
  tree.delete(key);
  
  System.out.println();
  tree.print();
 }
}
