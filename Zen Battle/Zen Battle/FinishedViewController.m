//
//  FinishedViewController.m
//  Zen Battle
//
//  Created by Ryan Bigger on 1/5/14.
//  Copyright (c) 2014 Raster Media. All rights reserved.
//

#import "FinishedViewController.h"
#import "WinParticleView.h"

@interface FinishedViewController ()

@property (weak, nonatomic) IBOutlet UILabel * labelFinish;

@end

@implementation FinishedViewController

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    // Do any additional setup after loading the view from its nib.
    
    UIBarButtonItem *donebutton = [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemDone
                                                                                target:self
                                                                                action:@selector(doneWithView:)];
    self.navigationItem.leftBarButtonItem = donebutton;
    
    // Create a view for the burst animation to live in
    WinParticleView *burstView = [[WinParticleView alloc] init];
    burstView.time = 0.3;
    [burstView configurateEmmiter];
    [self.view insertSubview:burstView atIndex:1];
    [burstView setIsEmitting:YES andPoint:self.view.center];
    
    [_labelFinish setFont:[UIFont fontWithName:@"PosterBodoniBT-Roman" size:50.0]];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)doneWithView:(id)sender
{
    [self.navigationController popToRootViewControllerAnimated:YES];
}

@end
