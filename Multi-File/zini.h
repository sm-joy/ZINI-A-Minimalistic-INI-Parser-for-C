#ifndef ZINI_PARSER_H
#define ZINI_PARSER_H

#define MAX_SECTION_LENGTH 128
#define MAX_KEY_LENGTH 128
#define MAX_VALUE_LENGTH 128
#define MAX_LINE_LENGTH MAX_KEY_LENGTH + MAX_VALUE_LENGTH + 2

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
    int pairCount;                      /**< Number of key-value pairs in the section */
} Section;

/**
 * Represents an INI file, including all sections and their key-value pairs.
 */
typedef struct {
    Section* sections;    /**< Array of sections in the INI file */
    int sectionCount;     /**< Number of sections in the INI file */
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
const char* ZINI_FindValue(Section* section, const char* key);

/**
 * Finds the value associated with a key in any section of the INIFILE structure.
 * @param iniFile Pointer to the INIFILE structure to be searched.
 * @param key Key whose value is to be found.
 * @return Value associated with the key if found, NULL otherwise.
 */
const char* ZINI_FindValueEx(INIFILE* iniFile, const char* key);

/**
 * Cleans up and frees memory used by the INIFILE structure.
 * @param iniFile Pointer to the INIFILE structure to be cleaned.
 */
void ZINI_Clean(INIFILE *iniFile);



#endif // ZINI_PARSER_H