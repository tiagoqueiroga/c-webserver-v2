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

    data->htmls = malloc(sizeof(HtmlFileArray));
    data->htmls->length = 0;

    if (data->htmls == NULL)
    {
        perror("failed to allocate memory for htmls");
        exit(EXIT_FAILURE);
    }

    for(size_t i = 0; i < MAX_HTML_FILES; i++)
    {
        data->htmls->files[i] = malloc(sizeof(HtmlFile));

        if(data->htmls->files[i] == NULL)
        {
            perror("failed to allocate memory for html file");
            exit(EXIT_FAILURE);
        }
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
