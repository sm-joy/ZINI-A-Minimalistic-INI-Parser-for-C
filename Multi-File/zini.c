#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "zini.h"

void ZINI_Init(INIFILE *iniFile) {
    if (!iniFile) return;
    iniFile->sections = NULL;
    iniFile->sectionCount = 0;
    iniFile->isModified = false;
}

bool ZINI_Open(INIFILE* iniFile, const char* filename) {
    if (!iniFile || !filename) {
        fprintf(stderr, "INI file or file name is NULL!\n");
        return false;
    }

    FILE *file = fopen(filename, "r");
    if (!file) {
        if (errno == ENOENT) return true;
        perror("Error opening INI file");
        return false;
    }

    char line[MAX_LINE_LENGTH];
    Section* currentSection = NULL;

    while (fgets(line, MAX_LINE_LENGTH, file)) {
        line[strcspn(line, "\n")] = 0;
        if (line[0] == '\0' || line[0] == ';') continue;

        if (line[0] == '[') {
            char *end = strchr(line, ']');
            if (end) {
                *end = '\0';
                Section* section = NULL;
                for (int i = 0; i < iniFile->sectionCount; i++) {
                    if (strcmp(iniFile->sections[i].section, line + 1) == 0) {
                        section = &iniFile->sections[i];
                        break;
                    }
                }

                if (!section) currentSection = ZINI_AddSection(iniFile, line+1);
                else currentSection = section;
            }
        }
        else {
            char* delimiter = strchr(line, '=');
            if (delimiter) {
                *delimiter = '\0';
                if (currentSection) {
                    ZINI_AddPair(currentSection, line, delimiter + 1);
                }
            }
        }
    }
    fclose(file);
    return true;
}

bool ZINI_Save(INIFILE* iniFile, const char* filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Error opening INI file for writing");
        return false;
    }

    for (int i = 0; i < iniFile->sectionCount; i++) {
        const Section* section = &iniFile->sections[i];
        fprintf(file, "[%s]\n", section->section);
        for (int j = 0; j < section->pairCount; j++) {
            const Pair* pair = &section->pairs[j];
            fprintf(file, "%s=%s\n", pair->key, pair->value);
        }
    }
    iniFile->isModified = false;
    fclose(file);
    return true;
}

Section* ZINI_AddSection(INIFILE* iniFile, const char* section) {
    if (!iniFile || !section) {
        fprintf(stderr, "ZINIFIle or Sections is NULL!\n");
        return NULL;
    }
    Section* newptr = (Section*)realloc(iniFile->sections, (iniFile->sectionCount+1) * sizeof(Section));
    if (!newptr) {
        perror("Failed to allocate memory for sections");
        return NULL;
    }

    iniFile->sections = newptr;
    Section *newSection = &iniFile->sections[iniFile->sectionCount++];
    strncpy(newSection->section, section, MAX_SECTION_LENGTH - 1);
    newSection->section[MAX_SECTION_LENGTH - 1] = '\0';
    newSection->pairs = NULL;
    newSection->pairCount = 0;
    iniFile->isModified = true;
    return newSection;
}

Pair* ZINI_AddPair(Section* section, const char* key, const char* value) { // didnt add code to check if it was modified
    if (!section || !key || !value) {
        fprintf(stderr, "ZINIFIle or Sections is NULL!\n");
        return NULL;
    }
    Pair* newptr = realloc(section->pairs, (section->pairCount + 1) * sizeof(Pair));
    if (!newptr) {
        perror("Failed to allocate memory for pairs");
        return NULL;
    }

    section->pairs = newptr;
    Pair* newPair = &section->pairs[section->pairCount++];
    strncpy(newPair->key, key, MAX_KEY_LENGTH - 1);
    newPair->key[MAX_KEY_LENGTH - 1] = '\0';
    strncpy(newPair->value, value, MAX_VALUE_LENGTH - 1);
    newPair->value[MAX_VALUE_LENGTH - 1] = '\0';
    return newPair;
}

Section* ZINI_FindSection(INIFILE* iniFile, const char* section) {
    if (!iniFile || !section) {
        fprintf(stderr, "INI file or section name is NULL!\n");
        return NULL;
    }

    for (int i = 0; i < iniFile->sectionCount; i++) {
        if (strcmp(iniFile->sections[i].section, section) == 0) {
            return &iniFile->sections[i];
        }
    }
    
    return NULL;
}

const char* ZINI_FindValue(Section* section, const char* key) {
    if (!section || !key) {
        fprintf(stderr, "Section or key is NULL!\n");
        return NULL;
    }

    for (int i = 0; i < section->pairCount; i++) {
        if (strcmp(section->pairs[i].key, key) == 0) {
            return section->pairs[i].value;
        }
    }
    return NULL;
}

const char* ZINI_FindValueEx(INIFILE* iniFile, const char* key) {
    if (!iniFile || !key) {
        fprintf(stderr, "INI file or key is NULL!\n");
        return NULL;
    }

    for (int i = 0; i < iniFile->sectionCount; i++) {
        const char* value = ZINI_FindValue(&iniFile->sections[i], key);
        if (value) return value;
    }
    
    return NULL;
}


void ZINI_Clean(INIFILE *iniFile) {
    if (!iniFile) return;
    if (!iniFile->isModified) printf("INI file was modified but not saved!\n");
    for (int i = 0; i < iniFile->sectionCount; ++i) {
        free(iniFile->sections[i].pairs);
    }
    free(iniFile->sections);
    iniFile->sections = NULL;
    iniFile->sectionCount = 0;
}