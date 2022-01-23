/*
 * ASCII art data structure.
 *
 * This acts like an infinite two-dimensional array of chars.
 *
 * The special TRANSPARENT character is the default value for each location.
 */

#define TRANSPARENT (' ')

typedef struct image Image;

/*
 * Make a new empty image.
 * This should be passed to imageDestroy when you are done with it.
 */
Image *imageCreate(void);

/*
 * Free the space used by an image.
 */
void imageDestroy(Image *);

/*
 * Set a particular position in an image.
 *
 * If value is TRANSPARENT, has no effect.
 */
void imageSet(Image *, int row, int col, int value);

/*
 * Read the contents of a file into an image.
 *
 * Any TRANSPARENT characters in the file will not replace previous characters.
 */
void imageRead(Image *, FILE *);

/*
 * Write an image to a file.
 *
 * TRANSPARENT characters at the end of a line will be omitted.
 *
 * Any lines at the bottom of the image made up of only TRANSPARENT characters
 * will also be omitted.
 */
void imageWrite(const Image *, FILE *);

/*
 * Paste one image onto another, with top left corner at given position.
 *
 * TRANSPARENT characters will no overwrite existing characters in the target image.
 */
void imagePaste(Image *dest, int row, int col, Image *src);
