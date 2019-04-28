#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "btree.h"

void test_btree(void);
void test_btree_init(void);
void test_btree_destroy(void);
void test_btree_insert_left(void);
void test_btree_insert_right(void);
void test_btree_remove_left(void);
void test_btree_remove_right(void);
void test_btree_merge(void);

void btree_fill(btree_t *tree, bt_node_t *root, size_t height);

int main(void)
{
        test_btree();
        return EXIT_SUCCESS;
}

void test_btree(void)
{
        test_btree_init();
        test_btree_destroy();
        test_btree_insert_left();
        test_btree_insert_right();
        test_btree_remove_left();
        test_btree_remove_right();
        test_btree_merge();
}

void test_btree_init(void)
{
        btree_t tree;
        btree_init(&tree, free);
        assert(tree.size == 0);
        assert(tree.destroy == free);
        assert(tree.compare == NULL);
        assert(tree.root == NULL);
        btree_destroy(&tree);

        printf("%-30s ok\n", __func__);
}

void test_btree_destroy(void)
{
        btree_t tree;
        btree_init(&tree, free);
        size_t height = 3;
        btree_fill(&tree, tree.root, height);
        btree_destroy(&tree);
        assert(tree.size == 0);
        assert(tree.destroy == NULL);
        assert(tree.compare == NULL);
        assert(tree.root == NULL);

        printf("%-30s ok\n", __func__);
}

void test_btree_insert_left(void)
{
        btree_t tree;
        int *data = NULL;
        int value = 1;

        // Check insertion into an empty list.
        btree_init(&tree, free);
        assert((data = (int *) malloc(sizeof(int))) != NULL);
        *data = value;
        assert(tree.size == 0);
        assert(btree_insert_left(&tree, NULL, data) == 0);
        assert(tree.size == 1);
        btree_destroy(&tree);

        // Check insertion in place of root.
        btree_init(&tree, free);
        assert(tree.size == 0);
        assert((data = (int *) malloc(sizeof(int))) != NULL);
        *data = value;
        assert(btree_insert_left(&tree, NULL, data) == 0);
        assert(tree.size == 1);

        assert((data = (int *) malloc(sizeof(int))) != NULL);
        *data = value;
        assert(btree_insert_left(&tree, NULL, data) != 0);
        assert(tree.size == 1);
        free(data);
        btree_destroy(&tree);

        // Check insertion of several elements.
        btree_init(&tree, free);
        assert(tree.size == 0);

        assert((data = (int *) malloc(sizeof(int))) != NULL);
        *data = value;
        assert(btree_insert_left(&tree, NULL, data) == 0);
        assert(tree.size == 1);

        assert((data = (int *) malloc(sizeof(int))) != NULL);
        *data = value;
        assert(btree_insert_left(&tree, tree.root, data) == 0);
        assert(tree.size == 2);

        assert((data = (int *) malloc(sizeof(int))) != NULL);
        *data = value;
        assert(btree_insert_left(&tree, btree_left(tree.root), data) == 0);
        assert(tree.size == 3);

        btree_destroy(&tree);

        printf("%-30s ok\n", __func__);
}

void test_btree_insert_right(void)
{
        btree_t tree;
        int *data = NULL;
        int value = 1;

        // Check insertion into an empty list.
        btree_init(&tree, free);
        assert((data = (int *) malloc(sizeof(int))) != NULL);
        *data = value;
        assert(tree.size == 0);
        assert(btree_insert_right(&tree, NULL, data) == 0);
        assert(tree.size == 1);
        btree_destroy(&tree);

        // Check insertion in place of root.
        btree_init(&tree, free);
        assert(tree.size == 0);
        assert((data = (int *) malloc(sizeof(int))) != NULL);
        *data = value;
        assert(btree_insert_right(&tree, NULL, data) == 0);
        assert(tree.size == 1);

        assert((data = (int *) malloc(sizeof(int))) != NULL);
        *data = value;
        assert(btree_insert_right(&tree, NULL, data) != 0);
        assert(tree.size == 1);
        free(data);
        btree_destroy(&tree);

        // Check insertion of several elements.
        btree_init(&tree, free);
        assert(tree.size == 0);

        assert((data = (int *) malloc(sizeof(int))) != NULL);
        *data = value;
        assert(btree_insert_right(&tree, NULL, data) == 0);
        assert(tree.size == 1);

        assert((data = (int *) malloc(sizeof(int))) != NULL);
        *data = value;
        assert(btree_insert_right(&tree, tree.root, data) == 0);
        assert(tree.size == 2);

        assert((data = (int *) malloc(sizeof(int))) != NULL);
        *data = value;
        assert(btree_insert_right(&tree, btree_right(tree.root), data) == 0);
        assert(tree.size == 3);

        btree_destroy(&tree);

        printf("%-30s ok\n", __func__);
}

void test_btree_remove_left(void)
{
        btree_t tree;
        int *data = NULL;
        int value = 1;
        size_t height = 0;
        size_t nodes_num = 0;

        // Check left-removing from an empty tree.
        btree_init(&tree, free);
        assert((data = (int *) malloc(sizeof(int))) != NULL);
        *data = value;
        assert(tree.size == 0);
        btree_remove_left(&tree, tree.root);
        assert(tree.size == 0);
        free(data);
        btree_destroy(&tree);

        // Check left-removing with only root in the tree.
        btree_init(&tree, free);
        height = 1;
        btree_fill(&tree, tree.root, height);
        nodes_num = (1 << height) - 1;
        assert(tree.size == nodes_num);
        btree_remove_left(&tree, NULL);
        assert(tree.size == 0);
        btree_destroy(&tree);

        // Check left-removing root->left branch.
        btree_init(&tree, free);
        height = 3;
        btree_fill(&tree, tree.root, height);
        nodes_num = (1 << height) - 1;
        assert(tree.size == nodes_num);
        btree_remove_left(&tree, tree.root);
        assert(tree.size == nodes_num / 2 + 1);
        btree_destroy(&tree);

        // Check left-removing root->left->left leaf element.
        btree_init(&tree, free);
        height = 3;
        btree_fill(&tree, tree.root, height);
        nodes_num = (1 << height) - 1;
        assert(tree.size == nodes_num);
        btree_remove_left(&tree, btree_left(tree.root));
        assert(tree.size == nodes_num - 1);
        btree_destroy(&tree);

        // Check left-removing root->right->left leaf element.
        btree_init(&tree, free);
        height = 3;
        btree_fill(&tree, tree.root, height);
        nodes_num = (1 << height) - 1;
        btree_remove_left(&tree, btree_right(tree.root));
        assert(tree.size == nodes_num - 1);
        btree_destroy(&tree);

        printf("%-30s ok\n", __func__);
}

void test_btree_remove_right(void)
{
        btree_t tree;
        int *data = NULL;
        int value = 1;
        size_t height = 0;
        size_t nodes_num = 0;

        // Check right-removing from an empty tree.
        btree_init(&tree, free);
        assert((data = (int *) malloc(sizeof(int))) != NULL);
        *data = value;
        assert(tree.size == 0);
        btree_remove_right(&tree, tree.root);
        assert(tree.size == 0);
        free(data);
        btree_destroy(&tree);

        // Check right-removing with only root in the tree.
        btree_init(&tree, free);
        height = 1;
        btree_fill(&tree, tree.root, height);
        nodes_num = (1 << height) - 1;
        assert(tree.size == nodes_num);
        btree_remove_right(&tree, NULL);
        assert(tree.size == 0);
        btree_destroy(&tree);

        // Check right-removing root->right branch.
        btree_init(&tree, free);
        height = 3;
        btree_fill(&tree, tree.root, height);
        nodes_num = (1 << height) - 1;
        assert(tree.size == nodes_num);
        btree_remove_right(&tree, tree.root);
        assert(tree.size == nodes_num / 2 + 1);
        btree_destroy(&tree);

        // Check right-removing root->left->right leaf element.
        btree_init(&tree, free);
        height = 3;
        btree_fill(&tree, tree.root, height);
        nodes_num = (1 << height) - 1;
        assert(tree.size == nodes_num);
        btree_remove_right(&tree, btree_left(tree.root));
        assert(tree.size == nodes_num - 1);
        btree_destroy(&tree);

        // Check right-removing root->right->right leaf element.
        btree_init(&tree, free);
        height = 3;
        btree_fill(&tree, tree.root, height);
        nodes_num = (1 << height) - 1;
        assert(tree.size == nodes_num);
        btree_remove_right(&tree, btree_right(tree.root));
        assert(tree.size == nodes_num - 1);
        btree_destroy(&tree);

        printf("%-30s ok\n", __func__);
}

void test_btree_merge(void)
{
        btree_t tree1;
        btree_t tree2;
        btree_t merged_tree;
        int *data = NULL;
        int value = 1;
        size_t height1 = 0;
        size_t height2 = 0;
        size_t nodes_num1 = 0;
        size_t nodes_num2 = 0;

        // Check merging of two empty trees.
        btree_init(&tree1, free);
        btree_init(&tree2, free);
        assert((data = (int *) malloc(sizeof(int))) != NULL);
        *data = value;
        nodes_num1 = 1;
        btree_merge(&merged_tree, &tree1, &tree2, data);
        assert(merged_tree.size == nodes_num1);
        assert(*(int *) btree_data(merged_tree.root) == value);
        btree_destroy(&tree1);
        btree_destroy(&tree2);
        btree_destroy(&merged_tree);
        data = NULL;

        // Check merging of full and empty trees.
        btree_init(&tree1, free);
        btree_init(&tree2, free);
        assert((data = (int *) malloc(sizeof(int))) != NULL);
        *data = value;
        height1 = 3;
        nodes_num1 = (1 << height1) - 1;
        btree_fill(&tree1, tree1.root, height1);
        assert(tree1.size == nodes_num1);
        btree_merge(&merged_tree, &tree1, &tree2, data);
        assert(merged_tree.size == nodes_num1 + 1);
        btree_destroy(&tree1);
        btree_destroy(&tree2);
        btree_destroy(&merged_tree);
        data = NULL;

        // Check merging of empty and full trees.
        btree_init(&tree1, free);
        btree_init(&tree2, free);
        assert((data = (int *) malloc(sizeof(int))) != NULL);
        *data = value;
        height1 = 4;
        nodes_num1 = (1 << height1) - 1;
        btree_fill(&tree2, tree2.root, height1);
        assert(tree2.size == nodes_num1);
        btree_merge(&merged_tree, &tree1, &tree2, data);
        assert(merged_tree.size == nodes_num1 + 1);
        btree_destroy(&tree1);
        btree_destroy(&tree2);
        btree_destroy(&merged_tree);
        data = NULL;

        // Check merging of two full trees.
        btree_init(&tree1, free);
        btree_init(&tree2, free);
        assert((data = (int *) malloc(sizeof(int))) != NULL);
        *data = value;
        height1 = 4;
        height2 = 5;
        nodes_num1 = (1 << height1) - 1;
        nodes_num2 = (1 << height2) - 1;
        btree_fill(&tree1, tree1.root, height1);
        btree_fill(&tree2, tree2.root, height2);
        assert(tree1.size == nodes_num1);
        assert(tree2.size == nodes_num2);
        btree_merge(&merged_tree, &tree1, &tree2, data);
        assert(merged_tree.size == nodes_num1 + nodes_num2 + 1);
        btree_destroy(&tree1);
        btree_destroy(&tree2);
        btree_destroy(&merged_tree);
        data = NULL;

        printf("%-30s ok\n", __func__);
}

void btree_fill(btree_t *tree, bt_node_t *root, size_t height)
{
        int *data = NULL;
        int value = 1;

        if (height == 0) {
                return;
        }

        if (root == NULL) {
                assert((data = (int *) malloc(sizeof(int))) != NULL);
                *data = value;
                btree_insert_left(tree, root, data);
                btree_fill(tree, tree->root, --height);
        } else {
                int *left = (int *) malloc(sizeof(int));
                int *right = (int *) malloc(sizeof(int));
                assert(left != NULL);
                assert(right != NULL);
                *left = ++value;
                *right = ++value;
                --height;
                btree_insert_left(tree, root, (void *) left);
                btree_insert_right(tree, root, (void *) right);
                btree_fill(tree, btree_left(root), height);
                btree_fill(tree, btree_right(root), height);
        }
}
