// print the contents of a wordArray
void
wordArrayPrint(WordArray w)
{
    char *key = wordArrayMinKey(w); 
    
    do {
        printf("%s %d\n", key, *wordArrayRef(w, key));
    } while(wordArrayIncKey(key) == 0);

    free(key);
}
