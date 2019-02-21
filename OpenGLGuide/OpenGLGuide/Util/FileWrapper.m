//
//  FileWrapper.m
//  OpenGLGuide
//
//  Created by 陈思欣 on 2019/2/18.
//  Copyright © 2019 chensx. All rights reserved.
//

#import "FileWrapper.h"
#import <Foundation/Foundation.h>

const char *GetBundleFileName( const char *fileName )
{
    NSString* fileNameNS = [NSString stringWithUTF8String:fileName];
    NSString* baseName = [fileNameNS stringByDeletingPathExtension];
    NSString* extension = [fileNameNS pathExtension];
    NSString *path = [[NSBundle mainBundle] pathForResource: baseName ofType: extension ];
    fileName = [path cStringUsingEncoding:1];
    
    return fileName;
}
