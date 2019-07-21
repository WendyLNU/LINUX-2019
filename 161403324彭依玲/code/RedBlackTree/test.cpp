/**
 * C����ʵ�ֵĺ����(Red Black Tree)
 *
 * @author skywang
 * @date 2013/11/18
 */

#include <stdio.h>
#include "RedBlackTree.h"

#define CHECK_INSERT 0    // "����"�����ļ�⿪��(0���رգ�1����)
#define CHECK_DELETE 0    // "ɾ��"�����ļ�⿪��(0���رգ�1����)
#define LENGTH(a) ( (sizeof(a)) / (sizeof(a[0])) )

int main()
{
    int a[] = {10, 40, 30, 60, 90, 70, 20, 50, 80};
    int i, ilen=LENGTH(a);
    RBRoot *root=NULL;

    root = create_rbtree();
    printf("== ԭʼ����: ");
    for(i=0; i<ilen; i++)
        printf("%d ", a[i]);
    printf("\n");

    for(i=0; i<ilen; i++)
    {
        insert_rbtree(root, a[i]);
#if CHECK_INSERT
        printf("== ��ӽڵ�: %d\n", a[i]);
        printf("== ������ϸ��Ϣ: \n");
        print_rbtree(root);
        printf("\n");
#endif
    }

    printf("== ǰ�����: ");
    preorder_rbtree(root);

    printf("\n== �������: ");
    inorder_rbtree(root);

    printf("\n== �������: ");
    postorder_rbtree(root);
    printf("\n");

    if (rbtree_minimum(root, &i)==0)
        printf("== ��Сֵ: %d\n", i);
    if (rbtree_maximum(root, &i)==0)
        printf("== ���ֵ: %d\n", i);
    printf("== ������ϸ��Ϣ: \n");
    print_rbtree(root);
    printf("\n");

#if CHECK_DELETE
    for(i=0; i<ilen; i++)
    {
        delete_rbtree(root, a[i]);

        printf("== ɾ���ڵ�: %d\n", a[i]);
        if (root)
        {
            printf("== ������ϸ��Ϣ: \n");
            print_rbtree(root);
            printf("\n");
        }
    }
#endif

    destroy_rbtree(root);
return 0;
}