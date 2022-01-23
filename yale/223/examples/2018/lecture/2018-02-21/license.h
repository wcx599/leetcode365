// Unbreakable Digital Rights Management library

// No one will ever know what is in a struct license!
typedef struct license License;

// Create a new license that can be activated limit times
License *licenseCreate(int limit);

// Activate a license.
// Returns true if activation successful.
int licenseActivate(License *);

// Reclaim space used by license.
// No refunds if not fully used!
void licenseDestroy(License *);
