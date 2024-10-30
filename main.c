#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME "CdB"

char **addString(char **array, int *size, const char *newString);
char **removeString(char **array, int *size, int index);

int main() {
    int option;
    char data_entry[20];
    char **dataset = NULL;
    int size = 0;

    do {
        printf("Welcome to %s\n\n[1]: Insert Data\n[2]: Retrieve Data\n[3]: Remove Data\n[4]: Exit\n\n", NAME);
        printf("Enter an option: ");
        scanf("%d", &option);

        while (option != 1 && option != 2 && option != 3 && option != 4) {
            printf("Please enter a valid option.\n");
            scanf("%d", &option);
        }

        if (option == 1) {
            printf("Enter the data you want to store: ");
            scanf("%s", data_entry);
            dataset = addString(dataset, &size, data_entry);
        } else if (option == 2) {
            if (size == 0) {
                printf("\nThere is no data stored.\n");
            } else {
                printf("Current data in store:\n\n");
                for (int i = 0; i < size; i++) {
                    printf("%d: %s\n", i, dataset[i]);
                }
                printf("\n");
            }
        } else if (option == 3) {
            if (size == 0) {
                printf("\nThere is no data stored.\n");
            } else {
                printf("Current data in store:\n\n");
                for (int i = 0; i < size; i++) {
                    printf("%d: %s\n", i, dataset[i]);
                }

                int index = 0;

                do {
                    printf("\nWhich index would you like to remove?: ");
                    scanf("%d", &index);
                    if (index < 0 || index >= size) {
                        printf("\nThat index doesn't exist.\n");
                    }
                } while (index < 0 || index >= size);

                dataset = removeString(dataset, &size, index);
                printf("Done!\n\n");
            }
        }
    } while (option != 4);

    for (int i = 0; i < size; i++) {
        free(dataset[i]);
    }
    free(dataset);

    return 0;
}

char **addString(char **array, int *size, const char *newString) {
    char **temp = realloc(array, (*size + 1) * sizeof(char *));
    if (temp == NULL) {
        printf("Memory allocation failed!\n");
        return array;
    }
    array = temp;

    array[*size] = malloc(strlen(newString) + 1);
    if (array[*size] == NULL) {
        printf("Memory allocation for string failed!\n");
        return array;
    }
    strcpy(array[*size], newString);

    (*size)++;
    return array;
}

char **removeString(char **array, int *size, int index) {
    if (index < 0 || index >= *size) {
        printf("Index out of bounds!\n");
        return array;
    }

    free(array[index]);

    for (int i = index; i < *size - 1; i++) {
        array[i] = array[i + 1];
    }

    char **temp = realloc(array, (*size - 1) * sizeof(char *));
    if (temp != NULL) {
        array = temp;
    } else if (*size > 1) {
        printf("Memory allocation failed!\n");
    }

    (*size)--;

    if (*size == 0) {
        free(array);
        return NULL;
    }

    return array;
}
