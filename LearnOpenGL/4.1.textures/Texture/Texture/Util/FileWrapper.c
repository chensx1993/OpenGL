//
//  FileWrapper.c
//  LearnOpenGL
//
//  Created by 陈思欣 on 2019/2/28.
//  Copyright © 2019 chensx. All rights reserved.
//

#include "FileWrapper.h"
#import <CoreFoundation/CoreFoundation.h>

const char *GetBundleFileName( const char *fileName)
{
    CFStringRef name = CFStringCreateWithCString(NULL, fileName, kCFStringEncodingUTF8);
    CFURLRef fileURL = CFBundleCopyResourceURL(CFBundleGetMainBundle(), name, NULL, NULL);//CFSTR("")
    if (fileURL) {
        CFStringRef newfilePath = CFURLCopyFileSystemPath(fileURL, kCFURLPOSIXPathStyle);
        CFStringEncoding encodingMethod = CFStringGetSystemEncoding();
        const char *path = CFStringGetCStringPtr(newfilePath, encodingMethod);
        return path;
    }
    return fileName;
}
