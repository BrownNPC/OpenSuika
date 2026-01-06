#pragma once

#include "raylib.h"
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

typedef struct { //
  // Was the save file found on disk?
  bool ExistsOnDisk;

  int HighScore;
} SaveFile;

static inline bool SaveStorageValue(const char *STORAGE_DATA_FILE,
                                    uint position, int value);
static inline int LoadStorageValue(const char *STORAGE_DATA_FILE,
                                   uint position);

// Loads save file from disk. ExistsOnDisk is false if file does not exist.
static inline SaveFile NewSaveFile(const char *path) {
  SaveFile s;
  //  ExistsOnDisk
  s.ExistsOnDisk = LoadStorageValue(path, 0);
  s.HighScore = LoadStorageValue(path, 1);
  return s;
}

static inline SaveFile SaveFile_Write(const char *path) {
  SaveFile s;
  //  ExistsOnDisk
  s.ExistsOnDisk = SaveStorageValue(path, 0, 1);
  s.HighScore = SaveStorageValue(path, 1, 0);
  return s;
}

// from raylib example
// https://github.com/raysan5/raylib/blob/master/examples/core/core_storage_values.c
//------------------------------------------------------------------------------------
// Module Functions Declaration
//------------------------------------------------------------------------------------
// Save integer value to storage file (to defined position)
// NOTE: Storage positions is directly related to file memory layout (4 bytes
// each integer)
static inline bool SaveStorageValue(const char *STORAGE_DATA_FILE,
                                    uint position, int value) {
  bool success = false;
  int dataSize = 0;
  unsigned int newDataSize = 0;
  unsigned char *fileData = LoadFileData(STORAGE_DATA_FILE, &dataSize);
  unsigned char *newFileData = NULL;

  if (fileData != NULL) {
    if (dataSize <= (position * sizeof(int))) {
      // Increase data size up to position and store value
      newDataSize = (position + 1) * sizeof(int);
      newFileData = (unsigned char *)RL_REALLOC(fileData, newDataSize);

      if (newFileData != NULL) {
        // RL_REALLOC succeded
        int *dataPtr = (int *)newFileData;
        dataPtr[position] = value;
      } else {
        // RL_REALLOC failed
        TraceLog(LOG_WARNING,
                 "FILEIO: [%s] Failed to realloc data (%u), position in bytes "
                 "(%u) bigger than actual file size",
                 STORAGE_DATA_FILE, dataSize, position * sizeof(int));

        // We store the old size of the file
        newFileData = fileData;
        newDataSize = dataSize;
      }
    } else {
      // Store the old size of the file
      newFileData = fileData;
      newDataSize = dataSize;

      // Replace value on selected position
      int *dataPtr = (int *)newFileData;
      dataPtr[position] = value;
    }

    success = SaveFileData(STORAGE_DATA_FILE, newFileData, newDataSize);
    RL_FREE(newFileData);

    TraceLog(LOG_INFO, "FILEIO: [%s] Saved storage value: %i",
             STORAGE_DATA_FILE, value);
  } else {
    TraceLog(LOG_INFO, "FILEIO: [%s] File created successfully",
             STORAGE_DATA_FILE);

    dataSize = (position + 1) * sizeof(int);
    fileData = (unsigned char *)RL_MALLOC(dataSize);
    int *dataPtr = (int *)fileData;
    dataPtr[position] = value;

    success = SaveFileData(STORAGE_DATA_FILE, fileData, dataSize);
    UnloadFileData(fileData);

    TraceLog(LOG_INFO, "FILEIO: [%s] Saved storage value: %i",
             STORAGE_DATA_FILE, value);
  }

  return success;
}

// Load integer value from storage file (from defined position)
// NOTE: If requested position could not be found, value 0 is returned
static inline int LoadStorageValue(const char *STORAGE_DATA_FILE,
                                   uint position) {
  int value = 0;
  int dataSize = 0;
  unsigned char *fileData = LoadFileData(STORAGE_DATA_FILE, &dataSize);

  if (fileData != NULL) {
    if (dataSize < ((int)(position * 4))) {
      TraceLog(LOG_WARNING, "FILEIO: [%s] Failed to find storage position: %i",
               STORAGE_DATA_FILE, position);
    } else {
      int *dataPtr = (int *)fileData;
      value = dataPtr[position];
    }

    UnloadFileData(fileData);

    TraceLog(LOG_INFO, "FILEIO: [%s] Loaded storage value: %i",
             STORAGE_DATA_FILE, value);
  }

  return value;
}
