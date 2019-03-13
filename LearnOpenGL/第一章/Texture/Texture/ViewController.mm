//
//  ViewController.m
//  Texture
//
//  Created by 陈思欣 on 2019/2/28.
//  Copyright © 2019 chensx. All rights reserved.
//

#import "ViewController.h"
#import <GLKit/GLKit.h>

@interface ViewController ()

@property (weak, nonatomic) IBOutlet GLKView *textureView;

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
}

- (IBAction)renderButtonDidClicked:(id)sender {
    [self.textureView display];
}

@end
