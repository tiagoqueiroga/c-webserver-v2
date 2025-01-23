#include "includes/globals.h"

Data *data = NULL; 

void init_data(void)
{
    #ifdef DEBUG
        printf("Creating data on the heap\n");
    #endif

    data = malloc(sizeof(Data));

    if (data == NULL)
    {
        perror("failed to allocate memory for data");
        exit(EXIT_FAILURE);
    }
}

void free_data(void)
{

#ifdef DEBUG
    printf("Freeing data from the heap memory\n");
#endif

    for (size_t i = 0; i < data->htmls->length; i++)
    {
        free(data->htmls->files[i]->file_text);
        free(data->htmls->files[i]);
    }

    free(data->htmls->files);
    free(data->htmls);
    free(data);
}
