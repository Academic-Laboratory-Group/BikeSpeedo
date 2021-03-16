/**
  ******************************************************************************
  * @file    fatfs_storage.h
  * @author  MCD Application Team
  * @version V1.2.0
  * @date    11-April-2014
  * @brief   This file contains all the functions prototypes for the storage
  *          firmware driver.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FATFS_STORAGE_H
#define __FATFS_STORAGE_H

#include "MacroAndConst.h"

extern uint32_t Storage_OpenReadFile(uint8_t Xpoz, uint16_t Ypoz, const char* BmpName);
extern uint32_t Storage_CopyFile(const char* BmpName1, const char* BmpName2);
extern uint32_t Storage_GetDirectoryBitmapFiles (const char* DirName, char* Files[]);
extern uint32_t Storage_CheckBitmapFile(const char* BmpName, uint32_t *FileLen);
extern uint8_t Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength);


#endif /* __FATFS_STORAGE_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
