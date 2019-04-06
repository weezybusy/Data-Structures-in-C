#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "set.h"

void test_set(void);
void test_set_insert(void);
void test_set_remove(void);
void test_set_union(void);
void test_set_intersection(void);
void test_set_difference(void);
void test_set_is_member(void);
void test_set_is_subset(void);
void test_set_is_equal(void);

int compare(const void *value1, const void *value2);
void set_display(const set_t *set);
void set_create(set_t *set, int values[], size_t size);

int main(void)
{
        test_set();
        return EXIT_SUCCESS;
}

void test_set(void)
{
        test_set_insert();
        test_set_remove();
        test_set_union();
        test_set_intersection();
        test_set_difference();
        test_set_is_member();
        test_set_is_subset();
        test_set_is_equal();
}

void test_set_insert(void)
{
        set_t set;
        set_init(&set, compare, free);

        int *data1 = (int *) malloc(sizeof(int));
        int *data2 = (int *) malloc(sizeof(int));
        int *data3 = (int *) malloc(sizeof(int));

        assert(data1 != NULL);
        assert(data2 != NULL);
        assert(data3 != NULL);

        int val1 = 55;
        int val2 = 66;
        int val3 = 77;

        *data1 = val1;
        *data2 = val2;
        *data3 = val3;

        assert(set_size(&set) == 0);
        size_t size = set_size(&set);

        // Check adding a member to the empty set.
        assert(set_insert(&set, data1) != -1);
        assert(set_size(&set) == ++size);
        assert(*(int *) list_data(list_head(&set)) == val1);

        // Check adding member which is already in set.
        assert(set_insert(&set, data1) == 1);
        assert(set_size(&set) == size);

        // Check adding more members.
        assert(set_insert(&set, data2) != -1);
        assert(set_size(&set) == ++size);
        assert(*(int *) list_data(list_tail(&set)) == val2);

        assert(set_insert(&set, data3) != -1);
        assert(set_size(&set) == ++size);
        assert(*(int *) list_data(list_tail(&set)) == val3);

        printf("%-30s ok\n", __func__);
        set_destroy(&set);
}

void test_set_remove(void)
{
        set_t set;
        set_init(&set, compare, free);

        int *data1 = (int *) malloc(sizeof(int));
        int *data2 = (int *) malloc(sizeof(int));
        int *data3 = (int *) malloc(sizeof(int));
        int *data4 = (int *) malloc(sizeof(int));
        int *data5 = (int *) malloc(sizeof(int));

        assert(data1 != NULL);
        assert(data2 != NULL);
        assert(data3 != NULL);
        assert(data4 != NULL);
        assert(data5 != NULL);

        int val1 = 55;
        int val2 = 66;
        int val3 = 77;
        int val4 = 88;
        int val5 = 99;

        *data1 = val1;
        *data2 = val2;
        *data3 = val3;
        *data4 = val4;
        *data5 = val5;

        assert(set_size(&set) == 0);
        size_t size = set_size(&set);

        int *non_existing_data = (int *) malloc(sizeof(int));
        assert(non_existing_data != NULL);
        *non_existing_data = 11;

        // Check removing from the empty set.
        assert(set_remove(&set, NULL) == -1);

        assert(set_insert(&set, data1) != -1);
        assert(set_size(&set) == ++size);
        assert(*(int *) list_data(list_head(&set)) == val1);

        assert(set_insert(&set, data2) != -1);
        assert(set_size(&set) == ++size);
        assert(*(int *) list_data(list_tail(&set)) == val2);

        assert(set_insert(&set, data3) != -1);
        assert(set_size(&set) == ++size);
        assert(*(int *) list_data(list_tail(&set)) == val3);

        assert(set_insert(&set, data4) != -1);
        assert(set_size(&set) == ++size);
        assert(*(int *) list_data(list_tail(&set)) == val4);

        assert(set_insert(&set, data5) != -1);
        assert(set_size(&set) == ++size);
        assert(*(int *) list_data(list_tail(&set)) == val5);

        // Check removing a non-existing member.
        assert(set_remove(&set, (void **) &non_existing_data) == -1);
        assert(set_size(&set) == size);

        // Check removing valid data.
        assert(set_remove(&set, (void **) &data3) != -1);
        assert(set_size(&set) == --size);
        free(data3);

        assert(set_remove(&set, (void **) &data1) != -1);
        assert(set_size(&set) == --size);
        free(data1);

        assert(set_remove(&set, (void **) &data2) != -1);
        assert(set_size(&set) == --size);
        free(data2);

        assert(set_remove(&set, (void **) &data5) != -1);
        assert(set_size(&set) == --size);
        free(data5);

        assert(set_remove(&set, (void **) &data4) != -1);
        assert(set_size(&set) == --size);
        free(data4);

        printf("%-30s ok\n", __func__);
        free(non_existing_data);
        set_destroy(&set);
}

void test_set_union(void)
{
        set_t set1;
        set_t set2;
        set_t setu;
        set_t check_set;

        // Chack union of two empty sets.
        set_init(&set1, compare, free);
        set_init(&set2, compare, free);
        assert(set_union(&setu, &set1, &set2) != -1);
        assert(set_size(&setu) == 0);
        set_destroy(&set1);
        set_destroy(&set2);
        set_destroy(&setu);

        // Check union of two sets where one is empty.
        set_init(&set1, compare, free);
        set_create(&set2, (int[]){11, 22, 33}, 3);
        assert(set_union(&setu, &set1, &set2) != -1);
        set_create(&check_set, (int[]){11, 22, 33}, 3);
        assert(set_size(&setu) == set_size(&check_set));
        assert(set_is_subset(&setu, &check_set));
        set_destroy(&set1);
        set_destroy(&set2);
        set_destroy(&setu);
        set_destroy(&check_set);

        set_create(&set1, (int[]){11, 22, 33}, 3);
        set_init(&set2, compare, free);
        assert(set_union(&setu, &set1, &set2) != -1);
        set_create(&check_set, (int[]){11, 22, 33}, 3);
        assert(set_size(&setu) == set_size(&check_set));
        assert(set_is_subset(&setu, &check_set));
        set_destroy(&set1);
        set_destroy(&set2);
        set_destroy(&setu);
        set_destroy(&check_set);

        // Check union of two sets with no data in common.
        set_create(&set1, (int[]){11, 22, 33}, 3);
        set_create(&set2, (int[]){44, 55, 66, 77}, 4);
        assert(set_union(&setu, &set1, &set2) != -1);
        set_create(&check_set, (int[]){11, 22, 33, 44, 55, 66, 77}, 7);
        assert(set_size(&setu) == set_size(&check_set));
        assert(set_is_subset(&setu, &check_set));
        set_destroy(&set1);
        set_destroy(&set2);
        set_destroy(&setu);
        set_destroy(&check_set);

        // Check union of two sets with some data in common.
        set_create(&set1, (int[]){11, 22, 33}, 3);
        set_create(&set2, (int[]){11, 33, 44, 55, 66}, 5);
        assert(set_union(&setu, &set1, &set2) != -1);
        set_create(&check_set, (int[]){11, 22, 33, 44, 55, 66}, 6);
        assert(set_size(&setu) == set_size(&check_set));
        assert(set_is_subset(&setu, &check_set));
        set_destroy(&set1);
        set_destroy(&set2);
        set_destroy(&setu);
        set_destroy(&check_set);

        set_create(&set1, (int[]){11, 33, 44, 55, 66}, 5);
        set_create(&set2, (int[]){11, 22, 33}, 3);
        assert(set_union(&setu, &set1, &set2) != -1);
        set_create(&check_set, (int[]){11, 22, 33, 44, 55, 66}, 6);
        assert(set_size(&setu) == set_size(&check_set));
        assert(set_is_subset(&setu, &check_set));
        set_destroy(&set1);
        set_destroy(&set2);
        set_destroy(&setu);
        set_destroy(&check_set);

        printf("%-30s ok\n", __func__);
}

void test_set_intersection(void)
{
        set_t set1;
        set_t set2;
        set_t seti;
        set_t check_set;

        // Chack intersaction of two empty sets.
        set_init(&set1, compare, free);
        set_init(&set2, compare, free);
        assert(set_intersection(&seti, &set1, &set2) != -1);
        assert(set_size(&seti) == 0);
        set_destroy(&set1);
        set_destroy(&set2);
        set_destroy(&seti);

        // Check intersection of two set where one is empty.
        set_init(&set1, compare, free);
        set_create(&set2, (int[]){55, 66,77}, 3);
        assert(set_intersection(&seti, &set1, &set2) != -1);
        assert(set_size(&seti) == 0);
        set_destroy(&set1);
        set_destroy(&set2);
        set_destroy(&seti);

        set_create(&set1, (int[]){55, 66,77}, 3);
        set_init(&set2, compare, free);
        assert(set_intersection(&seti, &set1, &set2) != -1);
        assert(set_size(&seti) == 0);
        set_destroy(&set1);
        set_destroy(&set2);
        set_destroy(&seti);

        // Check intersection of two sets with the same data.
        set_create(&set1, (int[]){55, 66, 77}, 3);
        set_create(&set2, (int[]){55, 66, 77}, 3);
        set_create(&check_set, (int[]){55, 66, 77}, 3);
        assert(set_intersection(&seti, &set1, &set2) != -1);
        assert(set_size(&seti) == set_size(&check_set));
        assert(set_is_subset(&seti, &check_set));
        set_destroy(&set1);
        set_destroy(&set2);
        set_destroy(&seti);
        set_destroy(&check_set);

        // Check intersection of two sets with different data.
        set_create(&set1, (int[]){55, 66, 77, 88}, 4);
        set_create(&set2, (int[]){33, 44, 55, 66, 77}, 5);
        set_create(&check_set, (int[]){55, 66, 77}, 3);
        assert(set_intersection(&seti, &set1, &set2) != -1);
        assert(set_size(&seti) == set_size(&check_set));
        assert(set_is_subset(&seti, &check_set));
        set_destroy(&set1);
        set_destroy(&set2);
        set_destroy(&seti);
        set_destroy(&check_set);

        set_create(&set1, (int[]){33, 44, 55, 66, 77}, 5);
        set_create(&set2, (int[]){55, 66, 88}, 3);
        set_create(&check_set, (int[]){55, 66, 77}, 2);
        assert(set_intersection(&seti, &set1, &set2) != -1);
        assert(set_size(&seti) == set_size(&check_set));
        assert(set_is_subset(&seti, &check_set));
        set_destroy(&set1);
        set_destroy(&set2);
        set_destroy(&seti);
        set_destroy(&check_set);

        printf("%-30s ok\n", __func__);
}

void test_set_difference(void)
{
        set_t set1;
        set_t set2;
        set_t setd;
        set_t check_set;

        // Chack difference of two empty sets.
        set_init(&set1, compare, free);
        set_init(&set2, compare, free);
        assert(set_difference(&setd, &set1, &set2) != -1);
        assert(set_size(&setd) == 0);
        set_destroy(&set1);
        set_destroy(&set2);
        set_destroy(&setd);

        // Check difference of two sets where one is empty.
        set_init(&set1, compare, free);
        set_create(&set2, (int[]){55, 66, 77}, 3);
        assert(set_difference(&setd, &set1, &set2) != -1);
        assert(set_size(&setd) == 0);
        set_destroy(&set1);
        set_destroy(&set2);
        set_destroy(&setd);

        set_create(&set1, (int[]){55, 66, 77}, 3);
        set_init(&set2, compare, free);
        set_create(&check_set, (int[]){55, 66, 77}, 3);
        assert(set_difference(&setd, &set1, &set2) != -1);
        assert(set_size(&setd) == set_size(&check_set));
        assert(set_is_subset(&setd, &check_set));
        set_destroy(&set1);
        set_destroy(&set2);
        set_destroy(&setd);
        set_destroy(&check_set);

        // Check difference of two identical sets.
        set_create(&set1, (int[]){55, 66, 77}, 3);
        set_create(&set2, (int[]){55, 66, 77}, 3);
        assert(set_difference(&setd, &set1, &set2) != -1);
        assert(set_size(&setd) == 0);
        set_destroy(&set1);
        set_destroy(&set2);
        set_destroy(&setd);

        // Check difference of two sets with some data in common.
        set_create(&set1, (int[]){11, 22, 55, 66, 77}, 5);
        set_create(&set2, (int[]){44, 55, 77, 88, 99}, 5);
        set_create(&check_set, (int[]){11, 22, 66}, 3);
        assert(set_difference(&setd, &set1, &set2) != -1);
        assert(set_size(&setd) == set_size(&check_set));
        assert(set_is_subset(&setd, &check_set));
        set_destroy(&set1);
        set_destroy(&set2);
        set_destroy(&setd);
        set_destroy(&check_set);

        set_create(&set1, (int[]){11, 22, 55, 66, 77}, 5);
        set_create(&set2, (int[]){55}, 1);
        set_create(&check_set, (int[]){11, 22, 66, 77}, 4);
        assert(set_difference(&setd, &set1, &set2) != -1);
        assert(set_size(&setd) == set_size(&check_set));
        assert(set_is_subset(&setd, &check_set));
        set_destroy(&set1);
        set_destroy(&set2);
        set_destroy(&setd);
        set_destroy(&check_set);

        // Check difference of two sets with no data in common.
        set_create(&set1, (int[]){11, 22, 33}, 3);
        set_create(&set2, (int[]){44, 55, 66}, 3);
        set_create(&check_set, (int[]){11, 22, 33}, 3);
        assert(set_difference(&setd, &set1, &set2) != -1);
        assert(set_size(&setd) == set_size(&check_set));
        assert(set_is_subset(&setd, &check_set));
        set_destroy(&set1);
        set_destroy(&set2);
        set_destroy(&setd);
        set_destroy(&check_set);

        printf("%-30s ok\n", __func__);
}

void test_set_is_member(void)
{
        set_t set;
        int data;
        set_create(&set, (int[]){11, 22, 33, 44}, 4);

        data = 0;
        assert(set_is_member(&set, &data) == 0);
        data = 11;
        assert(set_is_member(&set, &data) == 1);
        data = 22;
        assert(set_is_member(&set, &data) == 1);
        data = 33;
        assert(set_is_member(&set, &data) == 1);
        data = 44;
        assert(set_is_member(&set, &data) == 1);
        data = 55;
        assert(set_is_member(&set, &data) == 0);

        set_destroy(&set);
        printf("%-30s ok\n", __func__);
}

void test_set_is_subset(void)
{
        set_t set1;
        set_t set2;

        // Check if empty set is a subset of another empty set.
        set_init(&set1, compare, free);
        set_init(&set2, compare, free);
        assert(set_size(&set1) == 0);
        assert(set_size(&set2) == 0);
        assert(set_is_subset(&set1, &set2) == 1);
        set_destroy(&set1);
        set_destroy(&set2);

        // Check if empty set is a subset of not empty set.
        set_init(&set1, compare, free);
        set_create(&set2, (int[]){11, 22, 33}, 3);
        assert(set_is_subset(&set1, &set2) == 1);
        set_destroy(&set1);
        set_destroy(&set2);

        // Check if not empty set is a subset of empty set.
        set_create(&set1, (int[]){11, 22, 33}, 3);
        set_init(&set2, compare, free);
        assert(set_is_subset(&set1, &set2) == 0);
        set_destroy(&set1);
        set_destroy(&set2);

        // Check if bigger set is a subset of a smaller set.
        set_create(&set1, (int[]){11, 22, 33, 44}, 4);
        set_create(&set2, (int[]){11, 22, 33}, 3);
        assert(set_is_subset(&set1, &set2) == 0);
        set_destroy(&set1);
        set_destroy(&set2);

        // Check if set is a subset of a set containing different data.
        set_create(&set1, (int[]){11, 22, 33}, 3);
        set_create(&set2, (int[]){55, 44, 66}, 3);
        assert(set_is_subset(&set1, &set2) == 0);
        set_destroy(&set1);
        set_destroy(&set2);

        set_create(&set1, (int[]){11, 22, 33}, 3);
        set_create(&set2, (int[]){11, 55, 44, 66, 22}, 5);
        assert(set_is_subset(&set1, &set2) == 0);
        set_destroy(&set1);
        set_destroy(&set2);

        // Check if set is a subset of another set.
        set_create(&set1, (int[]){11}, 1);
        set_create(&set2, (int[]){11, 22, 33}, 3);
        assert(set_is_subset(&set1, &set2) == 1);
        set_destroy(&set1);
        set_destroy(&set2);

        set_create(&set1, (int[]){22, 33}, 2);
        set_create(&set2, (int[]){11, 22, 33}, 3);
        assert(set_is_subset(&set1, &set2) == 1);
        set_destroy(&set1);
        set_destroy(&set2);

        set_create(&set1, (int[]){11, 22, 33}, 3);
        set_create(&set2, (int[]){11, 22, 33}, 3);
        assert(set_is_subset(&set1, &set2) == 1);
        set_destroy(&set1);
        set_destroy(&set2);

        printf("%-30s ok\n", __func__);
}

void test_set_is_equal(void)
{
        set_t set1;
        set_t set2;

        // Check if two empty sets are equal.
        set_init(&set1, compare, free);
        set_init(&set2, compare, free);
        assert(set_size(&set1) == 0);
        assert(set_size(&set2) == 0);
        assert(set_is_equal(&set1, &set2) == 1);
        set_destroy(&set1);
        set_destroy(&set2);

        // Check if non-empty set is equal to empty set.
        set_create(&set1, (int[]){11, 22, 33}, 3);
        set_init(&set2, compare, free);
        assert(set_is_equal(&set1, &set2) == 0);
        set_destroy(&set1);
        set_destroy(&set2);

        // Check if empty set is equal to non-empty set.
        set_init(&set1, compare, free);
        set_create(&set2, (int[]){11, 22, 33}, 3);
        assert(set_is_equal(&set1, &set2) == 0);
        set_destroy(&set1);
        set_destroy(&set2);

        // Check if two identical sets equal to each other.
        set_create(&set1, (int[]){11, 22, 33}, 3);
        set_create(&set2, (int[]){11, 22, 33}, 3);
        assert(set_is_equal(&set1, &set2) == 1);
        set_destroy(&set1);
        set_destroy(&set2);

        // Check if two different sets equal to each other.
        set_create(&set1, (int[]){11, 22, 33, 44}, 4);
        set_create(&set2, (int[]){11, 22, 33}, 3);
        assert(set_is_equal(&set1, &set2) == 0);
        set_destroy(&set1);
        set_destroy(&set2);

        set_create(&set1, (int[]){22, 33}, 2);
        set_create(&set2, (int[]){11}, 1);
        assert(set_is_equal(&set1, &set2) == 0);
        set_destroy(&set1);
        set_destroy(&set2);

        printf("%-30s ok\n", __func__);
}

int compare(const void *value1, const void *value2)
{
        int v1 = *(int *) value1;
        int v2 = *(int *) value2;

        if (v1 < v2) {
                return -1;
        } else if (v1 > v2) {
                return 1;
        } else {
                return 0;
        }
}

void set_display(const set_t *set)
{
        if (set_size(set) == 0) {
                printf("empty\n");
                return;
        }
        for (node_t *node = list_head(set); node != NULL; node = list_next(node)) {
                printf("%d ", *(int *) list_data(node));
        }
        putchar('\n');
}

void set_create(set_t *set, int values[], size_t size)
{
        int *ptr = NULL;
        set_init(set, compare, free);
        for (size_t i = 0; i < size; i++) {
                ptr = (int *) malloc(sizeof(int));
                *ptr = values[i];
                assert(ptr != NULL);
                assert(set_insert(set, (void *) ptr) != -1);
        }
}
