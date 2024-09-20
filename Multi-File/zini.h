#ifndef ZINI_PARSER_H
#define ZINI_PARSER_H

#define MAX_SECTION_LENGTH 128
#define MAX_KEY_LENGTH 128
#define MAX_VALUE_LENGTH 128
#define MAX_LINE_LENGTH (MAX_KEY_LENGTH + MAX_VALUE_LENGTH + 2)


typedef enum {
    ZINI_SUCCESS,
    ZINI_KEY_NOT_FOUND,
    ZINI_SECTION_NOT_FOUND,
    ZINI_MEMORY_ERROR,
    ZINI_INVALID_INPUT,
    ZINI_FILE_ERROR
} ZINI_Status; // i'll add it later


/**
 * Represents a key-value pair in an INI file.
 */
typedef struct INIKeyValuePair {
    char key[MAX_KEY_LENGTH];    /**< Key of the pair */
    char value[MAX_VALUE_LENGTH]; /**< Value of the pair */
} Pair;

/**
 * Represents a section in an INI file.
 */
typedef struct INISection {
    char section[MAX_SECTION_LENGTH];   /**< Name of the section */
    Pair* pairs;                        /**< Array of key-value pairs in the section */
    size_t pairCount;                      /**< Number of key-value pairs in the section */
} Section;

/**
 * Represents an INI file, including all sections and their key-value pairs.
 */
typedef struct {
    Section* sections;    /**< Array of sections in the INI file */
    size_t sectionCount;     /**< Number of sections in the INI file */
    bool isModified;      /**< Flag indicating if the INI file has been modified */
} INIFILE;



/**
 * Initializes an INI file structure.
 * @param iniFile Pointer to the INIFILE structure to be initialized.
 */
void ZINI_Init(INIFILE *iniFile);

/**
 * Opens and reads an INI file, populating the INIFILE structure.
 * @param iniFile Pointer to the INIFILE structure to be populated.
 * @param filename Path to the INI file to be opened.
 * @return True if the file was successfully opened and read, false otherwise.
 */
bool ZINI_Open(INIFILE* iniFile, const char* filename);

/**
 * Saves the current state of the INIFILE structure to an INI file.
 * @param iniFile Pointer to the INIFILE structure to be saved.
 * @param filename Path to the INI file where the data will be saved.
 * @return True if the file was successfully saved, false otherwise.
 */
bool ZINI_Save(INIFILE* iniFile, const char* filename);

/**
 * Adds a new section to the INIFILE structure.
 * @param iniFile Pointer to the INIFILE structure to be modified.
 * @param section Name of the section to be added.
 * @return Pointer to the newly added Section structure, or NULL if an error occurred.
 */
Section* ZINI_AddSection(INIFILE* iniFile, const char* section);

/**
 * Adds a new key-value pair to a section.
 * @param section Pointer to the Section structure to be modified.
 * @param key Key of the pair to be added.
 * @param value Value of the pair to be added.
 * @return Pointer to the newly added Pair structure, or NULL if an error occurred.
 */
Pair* ZINI_AddPair(Section* section, const char* key, const char* value);

/**
 * Finds a section in the INIFILE structure.
 * @param iniFile Pointer to the INIFILE structure to be searched.
 * @param section Name of the section to find.
 * @return Pointer to the Section structure if found, NULL otherwise.
 */
Section* ZINI_FindSection(INIFILE* iniFile, const char* section);

/**
 * Finds the value associated with a key in a section.
 * @param section Pointer to the Section structure to be searched.
 * @param key Key whose value is to be found.
 * @return Value associated with the key if found, NULL otherwise.
 */
const char* ZINI_GetValue(Section* section, const char* key);

/**
 * Finds the value associated with a key in any section of the INIFILE structure.
 * @param iniFile Pointer to the INIFILE structure to be searched.
 * @param key Key whose value is to be found.
 * @return Value associated with the key if found, NULL otherwise.
 */
const char* ZINI_GetValueEx(INIFILE* iniFile, const char* section, const char* key); // will add a const char* section (for narrowing down the search)

/**
 * Cleans up and frees memory used by the INIFILE structure.
 * @param iniFile Pointer to the INIFILE structure to be cleaned.
 */
void ZINI_Clean(INIFILE* iniFile);

/**
 * Removes a key-value pair from a specified section.
 *
 * @param section Pointer to the `Section` structure from which the key-value pair should be removed.
 * @param key The key of the key-value pair to be removed.
 *
 * This function searches for the key in the section's key-value pairs and removes it if found.
 * Memory management for the removed key-value pair is handled within the function.
 */
void ZINI_RemovePair(Section* section, const char* key);


/**
 * Removes a key-value pair from a specified section in the INI file.
 *
 * @param iniFile Pointer to the `INIFILE` structure containing the section.
 * @param section The name of the section from which the key-value pair should be removed.
 * @param key The key of the key-value pair to be removed.
 *
 * This function locates the specified section within the INI file and then removes the key-value pair
 * from that section. Both the section and the key are required to be valid.
 */
void ZINI_RemovePairEx(INIFILE* iniFile, const char* section, const char* key);


/**
 * Updates the value associated with a specified key in a section.
 *
 * @param section Pointer to the `Section` structure where the key's value will be updated.
 * @param key The key whose value should be updated.
 * @param newValue The new value to be associated with the key.
 *
 * This function searches for the key within the section's key-value pairs and updates its value if the
 * key is found. If the key does not exist, no changes are made.
 */
void ZINI_SetValue(Section* section, const char* key, const char* newValue);


/**
 * Updates the value of a specified key in a section of the INI file.
 *
 * @param iniFile Pointer to the `INIFILE` structure containing the section.
 * @param section The name of the section where the key's value will be updated.
 * @param key The key whose value should be updated.
 * @param newValue The new value to be associated with the key.
 *
 * This function locates the specified section within the INI file and updates the key's value within
 * that section. Both the section and the key are required to be valid. If the section or key does not exist,
 * no changes are made.
 */
void ZINI_SetValueEx(INIFILE* iniFile, const char* section, const char* key, const char* newValue);


/**
 * Removes a section from the INI file.
 *
 * @param iniFile Pointer to the `INIFILE` structure from which the section should be removed.
 * @param section The name of the section to be removed.
 *
 * This function locates the specified section within the INI file and removes it along with its key-value
 * pairs. Memory allocated for the section and its pairs is freed.
 */
void ZINI_RemoveSection(INIFILE* iniFile, const char* section);


/**
 * Checks if a section exists in the INI file.
 *
 * @param iniFile Pointer to the `INIFILE` structure to be searched.
 * @param section The name of the section to be checked.
 * @return `true` if the section exists, `false` otherwise.
 *
 * This function searches for the specified section in the INI file and returns a boolean indicating its
 * presence.
 */
bool ZINI_SectionExists(INIFILE* iniFile, const char* section);


/**
 * Checks if a key exists in a section.
 *
 * @param section Pointer to the `Section` structure to be searched.
 * @param key The key to be checked.
 * @return `true` if the key exists, `false` otherwise.
 *
 * This function searches for the specified key in the section's key-value pairs and returns a boolean
 * indicating its presence.
 */
bool ZINI_KeyExists(Section* section, const char* key);


/**
 * Prints the INI file content to the specified stream.
 *
 * @param iniFile Pointer to the `INIFILE` structure to be printed.
 * @param stream Pointer to the `FILE` stream where the INI content will be written.
 *
 * This function writes the content of the INI file to the specified stream, formatted according to INI
 * file standards. The function handles sections and key-value pairs, ensuring they are printed correctly.
 */
void ZINI_Print(INIFILE* iniFile, FILE* stream);


#endif // ZINI_PARSER_H