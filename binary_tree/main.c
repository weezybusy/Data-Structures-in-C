#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "bitree.h"

void test_bitree(void);
void test_bitree_init(void);
void test_bitree_destroy(void);
void test_bitree_insert_left(void);
void test_bitree_insert_right(void);
void test_bitree_remove_left(void);
void test_bitree_remove_right(void);
void test_bitree_merge(void);

void bitree_fill(bitree_t *tree, btnode_t *root, size_t height);

int main(void)
{
        test_bitree();
        return EXIT_SUCCESS;
}

void test_bitree(void)
{
        test_bitree_init();
        test_bitree_destroy();
        test_bitree_insert_left();
        test_bitree_insert_right();
        test_bitree_remove_left();
        test_bitree_remove_right();
        test_bitree_merge();
}

void test_bitree_init(void)
{
        bitree_t tree;
        bitree_init(&tree, free);
        assert(tree.size == 0);
        assert(tree.destroy == free);
        assert(tree.compare == NULL);
        assert(tree.root == NULL);
        bitree_destroy(&tree);

        printf("%-30s ok\n", __func__);
}

void test_bitree_destroy(void)
{
        bitree_t tree;
        bitree_init(&tree, free);
        size_t height = 3;
        bitree_fill(&tree, tree.root, height);
        bitree_destroy(&tree);
        assert(tree.size == 0);
        assert(tree.destroy == NULL);
        assert(tree.compare == NULL);
        assert(tree.root == NULL);

        printf("%-30s ok\n", __func__);
}

void test_bitree_insert_left(void)
{
        bitree_t tree;
        int *data = NULL;
        int value = 1;

        // Check insertion into an empty list.
        bitree_init(&tree, free);
        assert((data = (int *) malloc(sizeof(int))) != NULL);
        *data = value;
        assert(tree.size == 0);
        assert(bitree_insert_left(&tree, NULL, data) == 0);
        assert(tree.size == 1);
        bitree_destroy(&tree);

        // Check insertion in place of root.
        bitree_init(&tree, free);
        assert(tree.size == 0);
        assert((data = (int *) malloc(sizeof(int))) != NULL);
        *data = value;
        assert(bitree_insert_left(&tree, NULL, data) == 0);
        assert(tree.size == 1);

        assert((data = (int *) malloc(sizeof(int))) != NULL);
        *data = value;
        assert(bitree_insert_left(&tree, NULL, data) != 0);
        assert(tree.size == 1);
        free(data);
        bitree_destroy(&tree);

        // Check insertion of several elements.
        bitree_init(&tree, free);
        assert(tree.size == 0);

        assert((data = (int *) malloc(sizeof(int))) != NULL);
        *data = value;
        assert(bitree_insert_left(&tree, NULL, data) == 0);
        assert(tree.size == 1);

        assert((data = (int *) malloc(sizeof(int))) != NULL);
        *data = value;
        assert(bitree_insert_left(&tree, tree.root, data) == 0);
        assert(tree.size == 2);

        assert((data = (int *) malloc(sizeof(int))) != NULL);
        *data = value;
        assert(bitree_insert_left(&tree, bitree_left(tree.root), data) == 0);
        assert(tree.size == 3);

        bitree_destroy(&tree);

        printf("%-30s ok\n", __func__);
}

void test_bitree_insert_right(void)
{
        bitree_t tree;
        int *data = NULL;
        int value = 1;

        // Check insertion into an empty list.
        bitree_init(&tree, free);
        assert((data = (int *) malloc(sizeof(int))) != NULL);
        *data = value;
        assert(tree.size == 0);
        assert(bitree_insert_right(&tree, NULL, data) == 0);
        assert(tree.size == 1);
        bitree_destroy(&tree);

        // Check insertion in place of root.
        bitree_init(&tree, free);
        assert(tree.size == 0);
        assert((data = (int *) malloc(sizeof(int))) != NULL);
        *data = value;
        assert(bitree_insert_right(&tree, NULL, data) == 0);
        assert(tree.size == 1);

        assert((data = (int *) malloc(sizeof(int))) != NULL);
        *data = value;
        assert(bitree_insert_right(&tree, NULL, data) != 0);
        assert(tree.size == 1);
        free(data);
        bitree_destroy(&tree);

        // Check insertion of several elements.
        bitree_init(&tree, free);
        assert(tree.size == 0);

        assert((data = (int *) malloc(sizeof(int))) != NULL);
        *data = value;
        assert(bitree_insert_right(&tree, NULL, data) == 0);
        assert(tree.size == 1);

        assert((data = (int *) malloc(sizeof(int))) != NULL);
        *data = value;
        assert(bitree_insert_right(&tree, tree.root, data) == 0);
        assert(tree.size == 2);

        assert((data = (int *) malloc(sizeof(int))) != NULL);
        *data = value;
        assert(bitree_insert_right(&tree, bitree_right(tree.root), data) == 0);
        assert(tree.size == 3);

        bitree_destroy(&tree);

        printf("%-30s ok\n", __func__);
}

void test_bitree_remove_left(void)
{
        bitree_t tree;
        int *data = NULL;
        int value = 1;
        size_t height = 0;
        size_t nodes_num = 0;

        // Check left-removing from an empty tree.
        bitree_init(&tree, free);
        assert((data = (int *) malloc(sizeof(int))) != NULL);
        *data = value;
        assert(tree.size == 0);
        bitree_remove_left(&tree, tree.root);
        assert(tree.size == 0);
        free(data);
        bitree_destroy(&tree);

        // Check left-removing with only root in the tree.
        bitree_init(&tree, free);
        height = 1;
        bitree_fill(&tree, tree.root, height);
        nodes_num = (1 << height) - 1;
        assert(tree.size == nodes_num);
        bitree_remove_left(&tree, NULL);
        assert(tree.size == 0);
        bitree_destroy(&tree);

        // Check left-removing root->left branch.
        bitree_init(&tree, free);
        height = 3;
        bitree_fill(&tree, tree.root, height);
        nodes_num = (1 << height) - 1;
        assert(tree.size == nodes_num);
        bitree_remove_left(&tree, tree.root);
        assert(tree.size == nodes_num / 2 + 1);
        bitree_destroy(&tree);

        // Check left-removing root->left->left leaf element.
        bitree_init(&tree, free);
        height = 3;
        bitree_fill(&tree, tree.root, height);
        nodes_num = (1 << height) - 1;
        assert(tree.size == nodes_num);
        bitree_remove_left(&tree, bitree_left(tree.root));
        assert(tree.size == nodes_num - 1);
        bitree_destroy(&tree);

        // Check left-removing root->right->left leaf element.
        bitree_init(&tree, free);
        height = 3;
        bitree_fill(&tree, tree.root, height);
        nodes_num = (1 << height) - 1;
        bitree_remove_left(&tree, bitree_right(tree.root));
        assert(tree.size == nodes_num - 1);
        bitree_destroy(&tree);

        printf("%-30s ok\n", __func__);
}

void test_bitree_remove_right(void)
{
        bitree_t tree;
        int *data = NULL;
        int value = 1;
        size_t height = 0;
        size_t nodes_num = 0;

        // Check right-removing from an empty tree.
        bitree_init(&tree, free);
        assert((data = (int *) malloc(sizeof(int))) != NULL);
        *data = value;
        assert(tree.size == 0);
        bitree_remove_right(&tree, tree.root);
        assert(tree.size == 0);
        free(data);
        bitree_destroy(&tree);

        // Check right-removing with only root in the tree.
        bitree_init(&tree, free);
        height = 1;
        bitree_fill(&tree, tree.root, height);
        nodes_num = (1 << height) - 1;
        assert(tree.size == nodes_num);
        bitree_remove_right(&tree, NULL);
        assert(tree.size == 0);
        bitree_destroy(&tree);

        // Check right-removing root->right branch.
        bitree_init(&tree, free);
        height = 3;
        bitree_fill(&tree, tree.root, height);
        nodes_num = (1 << height) - 1;
        assert(tree.size == nodes_num);
        bitree_remove_right(&tree, tree.root);
        assert(tree.size == nodes_num / 2 + 1);
        bitree_destroy(&tree);

        // Check right-removing root->left->right leaf element.
        bitree_init(&tree, free);
        height = 3;
        bitree_fill(&tree, tree.root, height);
        nodes_num = (1 << height) - 1;
        assert(tree.size == nodes_num);
        bitree_remove_right(&tree, bitree_left(tree.root));
        assert(tree.size == nodes_num - 1);
        bitree_destroy(&tree);

        // Check right-removing root->right->right leaf element.
        bitree_init(&tree, free);
        height = 3;
        bitree_fill(&tree, tree.root, height);
        nodes_num = (1 << height) - 1;
        assert(tree.size == nodes_num);
        bitree_remove_right(&tree, bitree_right(tree.root));
        assert(tree.size == nodes_num - 1);
        bitree_destroy(&tree);

        printf("%-30s ok\n", __func__);
}

void test_bitree_merge(void)
{
        bitree_t tree1;
        bitree_t tree2;
        bitree_t merged_tree;
        int *data = NULL;
        int value = 1;
        size_t height1 = 0;
        size_t height2 = 0;
        size_t nodes_num1 = 0;
        size_t nodes_num2 = 0;

        // Check merging of two empty trees.
        bitree_init(&tree1, free);
        bitree_init(&tree2, free);
        assert((data = (int *) malloc(sizeof(int))) != NULL);
        *data = value;
        nodes_num1 = 1;
        bitree_merge(&merged_tree, &tree1, &tree2, data);
        assert(merged_tree.size == nodes_num1);
        assert(*(int *) bitree_data(merged_tree.root) == value);
        bitree_destroy(&tree1);
        bitree_destroy(&tree2);
        bitree_destroy(&merged_tree);
        data = NULL;

        // Check merging of full and empty trees.
        bitree_init(&tree1, free);
        bitree_init(&tree2, free);
        assert((data = (int *) malloc(sizeof(int))) != NULL);
        *data = value;
        height1 = 3;
        nodes_num1 = (1 << height1) - 1;
        bitree_fill(&tree1, tree1.root, height1);
        assert(tree1.size == nodes_num1);
        bitree_merge(&merged_tree, &tree1, &tree2, data);
        assert(merged_tree.size == nodes_num1 + 1);
        bitree_destroy(&tree1);
        bitree_destroy(&tree2);
        bitree_destroy(&merged_tree);
        data = NULL;

        // Check merging of empty and full trees.
        bitree_init(&tree1, free);
        bitree_init(&tree2, free);
        assert((data = (int *) malloc(sizeof(int))) != NULL);
        *data = value;
        height1 = 4;
        nodes_num1 = (1 << height1) - 1;
        bitree_fill(&tree2, tree2.root, height1);
        assert(tree2.size == nodes_num1);
        bitree_merge(&merged_tree, &tree1, &tree2, data);
        assert(merged_tree.size == nodes_num1 + 1);
        bitree_destroy(&tree1);
        bitree_destroy(&tree2);
        bitree_destroy(&merged_tree);
        data = NULL;

        // Check merging of two full trees.
        bitree_init(&tree1, free);
        bitree_init(&tree2, free);
        assert((data = (int *) malloc(sizeof(int))) != NULL);
        *data = value;
        height1 = 4;
        height2 = 5;
        nodes_num1 = (1 << height1) - 1;
        nodes_num2 = (1 << height2) - 1;
        bitree_fill(&tree1, tree1.root, height1);
        bitree_fill(&tree2, tree2.root, height2);
        assert(tree1.size == nodes_num1);
        assert(tree2.size == nodes_num2);
        bitree_merge(&merged_tree, &tree1, &tree2, data);
        assert(merged_tree.size == nodes_num1 + nodes_num2 + 1);
        bitree_destroy(&tree1);
        bitree_destroy(&tree2);
        bitree_destroy(&merged_tree);
        data = NULL;

        printf("%-30s ok\n", __func__);
}

void bitree_fill(bitree_t *tree, btnode_t *root, size_t height)
{
        int *data = NULL;
        int value = 1;

        if (height == 0) {
                return;
        }

        if (root == NULL) {
                assert((data = (int *) malloc(sizeof(int))) != NULL);
                *data = value;
                bitree_insert_left(tree, root, data);
                bitree_fill(tree, tree->root, --height);
        } else {
                int *left = (int *) malloc(sizeof(int));
                int *right = (int *) malloc(sizeof(int));
                assert(left != NULL);
                assert(right != NULL);
                *left = ++value;
                *right = ++value;
                --height;
                bitree_insert_left(tree, root, (void *) left);
                bitree_insert_right(tree, root, (void *) right);
                bitree_fill(tree, bitree_left(root), height);
                bitree_fill(tree, bitree_right(root), height);
        }
}
